#pragma once

#include <imgui.h>
#include <implot.h>

#include <vector>
#include "GUIElements.h"

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

class ImGUIButton : public Button
{
public:
	ImGUIButton(const char* label, ICommand* command) : Button(label, command){}

	virtual void draw() override
	{
		if (ImGui::Button(m_Label))
			m_Command->execute();
	}
};

class ImGUICombobox : public Combobox
{
public:
	ImGUICombobox(const char* label, const std::vector<const char*>& items, ICommand* command)
		: Combobox(label, items, command) {}
	virtual void draw() override
	{
		const char* curItem{ m_Items[m_SelectedValue] };
		if (ImGui::BeginCombo(m_Label, curItem))
		{
			for (int i{ 0 }; i < m_Items.size(); ++i)
			{
				bool is_selected = (curItem == m_Items[i]);
				if (ImGui::Selectable(m_Items[i], is_selected))
				{
					m_SelectedValue = i;
					curItem = m_Items[m_SelectedValue];
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
	ImGUITextbox(const char* text)
		: Textbox(text) {}
	virtual void draw() override
	{
		ImGui::TextWrapped(m_Text);
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
			ImPlot::PlotBars("", m_Data, m_Count);
			ImPlot::EndPlot();
		}
	}
};