#pragma once
#include <memory>
#include "CipherPanel.h"

class CipherPanelFactory
{
public:
	virtual std::unique_ptr<CaesarPanel> createCaesarPanel() = 0;
	virtual std::unique_ptr<AffinePanel> createAffinePanel() = 0;
	virtual std::unique_ptr<VigenerePanel> createVigenerePanel() = 0;
	virtual std::unique_ptr<HillPanel> createHillPanel() = 0;
	virtual std::unique_ptr<StreamPanel> createStreamPanel() = 0;
	virtual std::unique_ptr<RSAPanel> createRSAPanel() = 0;
	virtual std::unique_ptr<PwdAuthPanel> createPwdAuthPanel() = 0;
};

/// <summary>
/// ImGUI Cipher Panels Factory
/// </summary>
#include "GUI/ImGUI/ImGUICipherPanel.h"
class ImGUIPanelFactory : public CipherPanelFactory
{
public:
	virtual std::unique_ptr<CaesarPanel> createCaesarPanel() override
	{
		return std::make_unique<ImGUICaesarPanel>();
	}
	virtual std::unique_ptr<AffinePanel> createAffinePanel() override
	{
		return std::make_unique<ImGUIAffinePanel>();
	}
	virtual std::unique_ptr<VigenerePanel> createVigenerePanel() override
	{
		return std::make_unique<ImGUIVigenerePanel>();
	}
	virtual std::unique_ptr<HillPanel> createHillPanel() override
	{
		return std::make_unique<ImGUIHillPanel>();
	}
	virtual std::unique_ptr<StreamPanel> createStreamPanel() override
	{
		return std::make_unique<ImGUIStreamPanel>();
	}
	virtual std::unique_ptr<RSAPanel> createRSAPanel() override
	{
		return std::make_unique<ImGUIRSAPanel>();
	}
	virtual std::unique_ptr<PwdAuthPanel> createPwdAuthPanel() override
	{
		return std::make_unique<ImGUIPwdAuthPanel>();
	}
};