

#pragma once
#include "../Util/natives.h"
#include "../imgui/imgui.h"
#include "../includes.h"
#include "tab/main.h"
#include "tab/food.h"





void Help(const char* text) {
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(text);
        ImGui::EndTooltip();
	}
}
void RenderTabButton(const char* label, int tabIndex, float width = 100.0f, float height = 40.0f) {
    if (UI::tab == tabIndex)
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.45f, 0.45f, 0.55f, 1.00f));
    else
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); 

    if (ImGui::Button(label, ImVec2(width, height)))
        UI::tab = tabIndex;

    ImGui::PopStyleColor();
}



void Menu()
{

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(750, 650));
    ImGui::Begin("Nemesis Rec Room", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::BeginChild("Sidebar", ImVec2(120, 0), true);
    {
        RenderTabButton("Main", 0);
        RenderTabButton("Visuals", 2);
        RenderTabButton("Food", 3);
        RenderTabButton("Settings", 4);
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("Content", ImVec2(0, 0), true);
    {
        switch (UI::tab) {
        case 0:

            MainTab();

            break;
        case 2:




            GradientText("Visual", 0.7f, lightBlue, darkBlue); //nothing yet not making an sdk or even trying to make a player cache its rec room who cares
            ImGui::Separator();



            break;
        case 3:
            FoodTab();



            break;
        case 4:




            GradientText("Settings", 0.7f, lightBlue, darkBlue);
            ImGui::Separator();
            if (ImGui::Button("Free VBucks"))
            {
                kiero::shutdown();
            }
            Help("Uninject From The Game!");


			if (ImGui::Button("Free Robux")) 
            {
                exit(0);
            }
            Help("Easily Crash Youre game!");




            break;
        }
    }
    ImGui::EndChild();

    ImGui::End();

}