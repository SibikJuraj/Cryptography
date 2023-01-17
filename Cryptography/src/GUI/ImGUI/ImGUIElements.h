#pragma once

#include <imgui.h>
#include <implot.h>

#include <vector>
#include <string>
#include "GUI/GUIElements.h"
#include "Text/Class base64/base64.h"
#include <ImGuiFileDialog.h>

class ImGUIPanel : public Panel
{
public:
	ImGUIPanel(const char* label) : Panel(label) {}

	virtual void draw() override
	{
		ImGui::Begin(m_Label);

		for (int i{ 0 }; i < m_Elements.size(); ++i)
			m_Elements[i]->draw();

		ImGui::End();
	}
};


class ImGUIFileLoaderPanel : public ImGUIPanel
{
public:
	ImGUIFileLoaderPanel(const char* label, std::string& input, std::string& output) 
		: ImGUIPanel(label), m_Input{ input }, m_Output{ output }
	{}

	virtual void draw() override
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
					TextLoader::saveText(filePathName, m_Output);
				else
					m_Input = TextLoader::loadText(filePathName);
			}
			// close
			ImGuiFileDialog::Instance()->Close();
		}
	}
private:
	std::string& m_Input;
	std::string& m_Output;
};

class ImGUIButton : public Button
{
public:
	ImGUIButton(const char* label, const ICommand& command) : Button(label, command){}

	virtual void draw() override
	{
		if (ImGui::Button(m_Label))
			m_Command->execute();
	}
};

class ImGUICombobox : public Combobox
{
public:
	ImGUICombobox(const char* label, const std::vector<const char*>& items, int& selected, const ICommand& command)
		: Combobox(label, items, selected, command) {}

	virtual void draw() override
	{
		const char* curItem{ m_Items[m_Selected] };
		if (ImGui::BeginCombo(m_Label, curItem))
		{
			for (int i{ 0 }; i < m_Items.size(); ++i)
			{
				bool is_selected = (curItem == m_Items[i]);
				if (ImGui::Selectable(m_Items[i], is_selected))
				{
					m_Selected = i;
					curItem = m_Items[m_Selected];
					m_Command->execute();
				}
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
};

class ImGUICheckbox : public Checkbox
{
public:
	ImGUICheckbox(const char* label, bool& value)
		: Checkbox(label, value) {}
	virtual void draw() override
	{
		ImGui::Checkbox(m_Label, &m_Value);
	}
};

class ImGUITextbox : public Textbox
{
public:
	ImGUITextbox(const char* label, std::string& text)
		: Textbox(label, text) {}
	virtual void draw() override
	{
		ImGui::TextWrapped(m_Text.c_str());
	}
};

class ImGUIInputInt : public InputInt
{
public:
	ImGUIInputInt(const char* label, int& value, const ICommand& command, const std::pair<int, int> range)
		: m_LastVal{ value }, InputInt(label, value, command, range)  {}
	~ImGUIInputInt() = default;

	virtual void draw() override
	{
		if (m_Value < m_Range.first)
			m_Value = m_Range.first;
		if (m_Value > m_Range.second)
			m_Value = m_Range.second;

		if (m_LastVal != m_Value)
		{
			m_Command->execute();
			m_LastVal = m_Value;
		}
		ImGui::InputInt(m_Label, &m_Value);
	}
private:
	int m_LastVal;
};

class ImGUIInputText : public InputText
{
public:
	ImGUIInputText(const char* label, char* value, size_t size, const ICommand& command)
		: InputText(label, value, size, command) {}
	~ImGUIInputText() = default;

	virtual void draw() override
	{
		ImGui::InputTextMultiline(m_Label, m_Value, m_Size);
	}
};

class ImGUIPlot : public Plot
{
public:
	ImGUIPlot(const char* label, const char* data, int count)
		: Plot(label, data, count) {}
};

class ImGUIPlotAnalysis : public ImGUIPlot
{
public:
	ImGUIPlotAnalysis(const char* label, const char* data, int count)
		: ImGUIPlot(label, data, count) {}

	virtual void draw() override
	{
		if (ImPlot::BeginPlot(m_Label))
		{
			ImPlot::SetupAxisFormat(ImAxis_X1, "%g");
			ImPlot::SetupAxisTicks(ImAxis_X1, 0, m_Count - 1, m_Count);
			//ImPlot::PlotBars("", m_Data, m_Count);
			ImPlot::EndPlot();
		}
	}
};
