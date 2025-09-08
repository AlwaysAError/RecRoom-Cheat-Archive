#pragma once
#include "../../includes.h"
#include <ranges>
#include "../../Util/natives.h"
#include <algorithm>
#include "inc.h"
void FoodTab() 
{
    GradientText("FoodSploit", 0.7f, lightBlue, darkBlue);
    ImGui::Separator();
    ImGui::SliderInt("Food Amount", &UI::FoodExploit::FoodInt, 1, 1000);
    ImGui::SameLine();
    if (ImGui::Button("Reset##FoodInt")) { UI::FoodExploit::FoodInt = 1; }

    ImGui::SliderFloat("Food Scale", &UI::FoodExploit::FoodScale, 0.1f, 99.0f);
    ImGui::SameLine();
    if (ImGui::Button("Reset##FoodScale")) { UI::FoodExploit::FoodScale = 1.0f; }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Text("Food Selector");
    ImGui::InputText("##SearchFood", UI::FoodExploit::searchBuffer, IM_ARRAYSIZE(UI::FoodExploit::searchBuffer));



    ImGui::BeginChild("FoodScroll", ImVec2(0, 500), true);
    for (int i = 0; i < ARRAYSIZE(Guid); ++i) {
        std::string itemLower = Guid[i].frie;
        std::string searchLower = UI::FoodExploit::searchBuffer;
        std::transform(itemLower.begin(), itemLower.end(), itemLower.begin(), ::tolower);
        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        if (searchLower.empty() || itemLower.find(searchLower) != std::string::npos) {
            bool isSelected = (UI::FoodExploit::selectedIndex == i);
            if (ImGui::Selectable(Guid[i].frie, isSelected)) {
                UI::FoodExploit::selectedIndex = i;
                SelectedFood = Guid[i].guid;
                UI::FoodExploit::searchBuffer[0] = '\0'; // clear search
            }
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
    }
    ImGui::EndChild();
}