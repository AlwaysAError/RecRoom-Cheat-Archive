#pragma once

#include "C:\Users\mikep\OneDrive\Desktop\astolfomocha\ImGui DirectX 11 Kiero Hook\includes.h"

// External icon font reference
extern ImFont* icons;

void MovmentTab()
{
    // Test the top bar with icon and text
    ImGui::PushFont(icons);
    ImGui::Text(ICON_FA_PERSON_RUNNING);
    ImGui::PopFont();
    ImGui::SameLine();
    ImGui::TextDisabled("Movement Modules");

    ImGui::Separator();

    // Keep your existing basic toggles
    ImGui::Custom::Toggle("Dynamic Fly", &globals::movement::dynamicfly);
    ImGui::Custom::Toggle("Static Fly", &globals::movement::staticfly);
    ImGui::Custom::Toggle("Custom Walkspeed", &globals::player::changespeed);
    if (globals::player::changespeed)
    {
        ImGui::SliderFloat("Walkspeed", &globals::player::speed, 3.5f, 100.0f);
    }
}