#include <iostream>

#include "Application.h"
#include "Ciphers/Caesar.h"
#include "Ciphers/Affine.h"
#include "Ciphers/Viegener.h"

#include "Engine/GUI/ImGUI.h"

Application::Application() : 
    m_GUI{ std::make_unique<ImGUI>(1600, 900) }, m_CurrentCipher{ 0 },
    m_Language{ std::make_unique<AnalysisOfSKLang>() }
{
    //TODO 
    //VYTVOR GUI JAK MA VYZERAT + NAPLN CO MA EXECUTOVAT KOMANDY ... CO SA MA VYKONAVAT
}

void Application::run()
{
    m_Text = std::make_unique<Text>("texts/vigenere/text4_enc.txt");

    std::vector<const char*> cipherNames{"Affine", "Caesar"};

    const char* curItem{ cipherNames[0]};

    Text oText{ *m_Text.get() };
    bool fineTuning{ false };
    bool enLanguage{ false };

    while (m_GUI->isRunning())
    {
        m_GUI->preRun();
        m_GUI->run(cipherNames, curItem, m_CurrentCipher, *m_Text.get(), oText, fineTuning, enLanguage);
        m_GUI->postRun();
    }
}

Application::~Application()
{
}


void Application::createCipherClass(int selectedOption)
{
    switch (selectedOption)
    {
       /* case 0:
            m_Cipher = std::move(std::make_unique<Caesar>());
            break;
        case 1:
            m_Cipher = std::move(std::make_unique<Affine>());
            break;
        case 2:
            m_Cipher = std::move(std::make_unique<Viegener>());
            break;*/
    }
}

const AnalysisOfLang& Application::getLanguage() const
{
    return *m_Language;
}

void Application::setLanguage(bool english)
{
    if (english)
        m_Language = std::move(std::make_unique<AnalysisOfENLang>());
    else
        m_Language = std::move(std::make_unique<AnalysisOfSKLang>());
}

int Application::getAlphabetLength() const
{
    return m_Language->getAlphabetLength();
}
