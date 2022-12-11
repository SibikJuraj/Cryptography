#include "ImGUI.h"

#include <memory>
#include <iostream>
#include <imgui.h>
#include <implot.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <vector>
#include <ImGuiFileDialog.h>
#include <Text/TextLoader.h>

#include <Class Cryptography/Cryptography.h>

ImGUI::ImGUI(int width, int height) 
    : GUI(width, height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, "Kryptografia a bezpecnost", NULL, NULL);

    // glfw window creation
    // --------------------
    if (!m_Window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return; //-1;
    }

    glfwMakeContextCurrent(m_Window);
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

    io.Fonts->AddFontFromFileTTF("vendor\\submodules\\imgui\\misc\\fonts\\arialbd.ttf", c_FontSize);

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

}

ImGUI::~ImGUI()
{
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    glfwTerminate();
}

void ImGUI::render()
{
    glfwPollEvents();

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    imGuiRender();
    fileWindowRender();

    for (std::unique_ptr<IGUIElement>& element : m_Elements)
        element->draw();

    // render
    // ------
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_Window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(m_Window);

    //int selectedCipher{ 0 };
    //auto iText = std::make_unique<Text>("texts/vigenere/text4_enc.txt");
    //Text oText{ *iText.get() };
    //bool fineTuning{ false };
    //bool enLanguage{ false };
    //std::vector<const char*> items{ "Affine", "Caesar" };
    //const char* curItem{ items[0]};

    //ImGui::Begin("Ciphers");
    //// render loop
    //// -----------
    //if (ImGui::BeginCombo("Cipher", curItem))
    //{
    //    for (int i{ 0 }; i < items.size(); ++i)
    //    {
    //        bool is_selected = (curItem == items[i]);
    //        if (ImGui::Selectable(items[i], is_selected))
    //        {
    //            curItem = items[i];
    //            selectedCipher = i;
    //            Application::getInstance().createCipherClass(selectedCipher);
    //        }
    //        if (is_selected)
    //        {
    //            ImGui::SetItemDefaultFocus();
    //        }
    //    }
    //    ImGui::EndCombo();
    //}

    //if (ImGui::Button("Decrypt"))
    //    oText = cipher.decrypt(oText, fineTuning);
    //if (ImGui::Button("Encrypt"))
    //    oText = cipher.encrypt(oText, fineTuning);

    //ImGui::Checkbox("English", &enLanguage);
    //ImGui::Checkbox("Fine Tuning", &fineTuning);
    //if (fineTuning)
    //{
    //    const char* keyNames[]{ "Key 1", "Key 2", "Key 3", "Key 4", "Key 5",
    //                        "Key 6", "Key 7", "Key 8", "Key 9", "Key 10",
    //                        "Key 11", "Key 12", "Key 13", "Key 14", "Key 15",
    //                        "Key 16", "Key 17", "Key 18", "Key 19", "Key 20",
    //                        "Key 21", "Key 22", "Key 23", "Key 24", "Key 25",
    //                        "Key 26", "Key 27", "Key 28", "Key 29", "Key 30",
    //    };
    //    for (int i{ 0 }; i < cipher.getKeys().size(); ++i)
    //    {
    //        ImGui::InputInt(keyNames[i], &(cipher.getKeys()[i]));
    //    }
    //    //m_Cipher->setKey();
    //}
    //Application::getInstance().setLanguage(enLanguage);

    //ImGui::End();
    //ImGui::Begin("Text");
    //ImGui::TextWrapped(iText->textWithSpaces().data());
    //ImGui::End();
    //ImGui::Begin("Output");
    //ImGui::TextWrapped(oText.textWithSpaces().data());
    //ImGui::End();

    //ImGui::Begin("FrekvencnaAnalyza Text");
    //if (ImPlot::BeginPlot("Text"))
    //{
    //    ImPlot::SetupAxisFormat(ImAxis_X1, "%g");
    //    ImPlot::SetupAxisTicks(ImAxis_X1, 0, 25, 26);
    //    ImPlot::PlotBars("", iText->getTextAnalysis().getLetters().data(), 26);
    //    ImPlot::EndPlot();
    //}
    //ImGui::End();
    //ImGui::Begin("FrekvencnaAnalyza Output");
    //if (ImPlot::BeginPlot("Output"))
    //{
    //    ImPlot::SetupAxisFormat(ImAxis_X1, "%g");
    //    ImPlot::SetupAxisTicks(ImAxis_X1, 0, 25, 26);
    //    ImPlot::PlotBars("", oText.getTextAnalysis().getLetters().data(), 26);
    //    ImPlot::EndPlot();
    //}
    //ImGui::End();
}

bool ImGUI::isRunning()
{
    return !glfwWindowShouldClose(m_Window);
}

void ImGUI::addElement(std::unique_ptr<IGUIElement>&& element)
{
    m_Elements.emplace_back(std::move(element));
}

std::unique_ptr<IGUIElementsFactory> ImGUI::getElementFactory()
{
    return std::make_unique<ImGUIElementsFactory>();
}

void ImGUI::imGuiRender()
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

void ImGUI::openSaveWindow()
{
    ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".txt", ".");
}

void ImGUI::openLoadWindow()
{
    ImGuiFileDialog::Instance()->OpenDialog("LoadFileDlgKey", "Load File", ".txt", ".");
}

void ImGUI::fileWindowRender()
{
    // display
    if (ImGuiFileDialog::Instance()->Display(ImGuiFileDialog::Instance()->GetOpenedKey()))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            if (ImGuiFileDialog::Instance()->GetOpenedKey() == "SaveFileDlgKey")
                TextLoader::saveText(filePathName, Cryptography::getInstance().getOutputText());
            else
                Cryptography::getInstance().setInputText(TextLoader::loadText(filePathName));
        }
        // close
        ImGuiFileDialog::Instance()->Close();
    }
}