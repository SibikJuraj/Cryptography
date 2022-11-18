#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <imgui.h>
#include <implot.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <vector>

#include "Application.h"
#include "Ciphers/Caesar.h"
#include "Ciphers/Affine.h"
#include "Ciphers/Viegener.h"

void imGuiRender();

Application::Application() : 
    m_Cipher{ std::make_unique<Caesar>() }, 
    m_Language{ std::make_unique<AnalysisOfSKLang>()}, m_SelectedOption{ 0 }
{
    // glfw: initialize and configure
   // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    m_Window = std::make_unique<OpenGLWindow>(1600, 900);
    glfwMakeContextCurrent(m_Window->getWindow());
    glfwSwapInterval(1); //Enable vsync

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext(); 
    ImPlot::CreateContext();
    
    ImGui::StyleColorsDark();
    ImGuiIO& io{ ImGui::GetIO() };
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(m_Window->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}


void Application::run()
{
    m_Text = std::make_unique<Text>("texts/vigenere/text4_enc.txt");

    std::vector<const char*> items { "Caesar", "Affine", "Viegener" };
    const char* current_item = items[m_SelectedOption];

    Text oText{*m_Text.get()};
    bool fineTuning{ false };
    bool enLanguage{ false };

    // render loop
    // -----------
    while (!glfwWindowShouldClose(m_Window->getWindow()))
    {
        glfwPollEvents();

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        imGuiRender();
        //Update();
        {
            ImGui::Begin("Ciphers");
                if (ImGui::BeginCombo("Cipher", current_item)) 
                {
                    for (int i{ 0 }; i < items.size(); ++i)
                    {
                        bool is_selected = (current_item == items[i]);
                        if (ImGui::Selectable(items[i], is_selected))
                        {
                            current_item = items[i];
                            m_SelectedOption = i;
                            createCipherClass();
                        }
                        if (is_selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }
                
                if (ImGui::Button("Decrypt"))
                    oText = m_Cipher->decrypt(*m_Text.get(), fineTuning);
                if (ImGui::Button("Encrypt"))
                    oText = m_Cipher->encrypt(*m_Text.get(), fineTuning);

                ImGui::Checkbox("English", &enLanguage);
                ImGui::Checkbox("Fine Tuning", &fineTuning);
                if (fineTuning)
                {
                    const char* keyNames[]{ "Key 1", "Key 2", "Key 3", "Key 4", "Key 5",
                                        "Key 6", "Key 7", "Key 8", "Key 9", "Key 10",
                                        "Key 11", "Key 12", "Key 13", "Key 14", "Key 15",
                                        "Key 16", "Key 17", "Key 18", "Key 19", "Key 20",
                                        "Key 21", "Key 22", "Key 23", "Key 24", "Key 25",
                                        "Key 26", "Key 27", "Key 28", "Key 29", "Key 30",
                    };
                    for (int i{ 0 }; i < m_Cipher->getKeys().size(); ++i)
                    {
                        ImGui::InputInt(keyNames[i], &(m_Cipher->getKeys()[i]));
                    }
                }
                if (enLanguage)
                    m_Language = std::move(std::make_unique<AnalysisOfENLang>());
                else
                    m_Language = std::move(std::make_unique<AnalysisOfSKLang>());

                
                oText.analyzeText();

            ImGui::End();
            ImGui::Begin("Text");
                ImGui::TextWrapped(m_Text->textWithSpaces().data());
            ImGui::End();
            ImGui::Begin("Output");
                ImGui::TextWrapped(oText.textWithSpaces().data());
            ImGui::End();

            ImGui::Begin("FrekvencnaAnalyza Text");
            if (ImPlot::BeginPlot("Text"))
            {
                ImPlot::PlotBars("", m_Text->getTextAnalysis().getLetters().data(), 26);
                ImPlot::EndPlot();
            }
            ImGui::End();
            ImGui::Begin("FrekvencnaAnalyza Output");
            if (ImPlot::BeginPlot("Output"))
            {
                ImPlot::PlotBars("", oText.getTextAnalysis().getLetters().data(), 26);
                ImPlot::EndPlot();
            }
            ImGui::End();
        }

        // render
        // ------
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_Window->getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_Window->getWindow());
    }
}

Application::~Application()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwTerminate();
}

void imGuiRender()
{
    static bool dockspaceOpen = true;

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
}

void Application::createCipherClass()
{
    switch (m_SelectedOption)
    {
        case 0:		
            m_Cipher = std::move(std::make_unique<Caesar>());
            break;
        case 1:		
            m_Cipher = std::move(std::make_unique<Affine>());
            break;
        case 2:
            m_Cipher = std::move(std::make_unique<Viegener>());
            break;
    }
}

const AnalysisOfLang& Application::getLanguage() const
{
    return *m_Language;
}

int Application::getAlphabetLength() const
{
    return m_Language->getAlphabetLength();
}
