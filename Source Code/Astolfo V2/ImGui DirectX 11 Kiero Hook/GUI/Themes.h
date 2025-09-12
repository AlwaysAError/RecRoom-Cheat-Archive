#pragma once
#include "..\includes.h"

void ApplyThemes() {

    ImGuiStyle& style = ImGui::GetStyle();

    style.TabRounding = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding = 7;
    style.GrabRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ChildRounding = 4;

    auto HexToImVec4 = [](int hex, float alpha = 1.0f) -> ImVec4 {
        float r = ((hex >> 16) & 0xFF) / 255.0f;
        float g = ((hex >> 8) & 0xFF) / 255.0f;
        float b = (hex & 0xFF) / 255.0f;
        return ImVec4(r, g, b, alpha);
        };

    // Backgrounds
    style.Colors[ImGuiCol_WindowBg] = HexToImVec4(0x1F1F1F);
    style.Colors[ImGuiCol_PopupBg] = HexToImVec4(0x272727);
    style.Colors[ImGuiCol_ChildBg] = HexToImVec4(0x2F2F2F);

    // Text
    style.Colors[ImGuiCol_Text] = HexToImVec4(0xFFFFFF);
    style.Colors[ImGuiCol_TextDisabled] = HexToImVec4(0xA2A2A2);
    style.Colors[ImGuiCol_TextSelectedBg] = HexToImVec4(0xd8a1fc);

    // CheckMark
    style.Colors[ImGuiCol_CheckMark] = HexToImVec4(0xFFFFFF);

    // Sliders
    style.Colors[ImGuiCol_SliderGrab] = HexToImVec4(0xd8a1fc);
    style.Colors[ImGuiCol_SliderGrabActive] = HexToImVec4(0xb67fdf);

    // Scrollbars
    style.Colors[ImGuiCol_ScrollbarGrab] = HexToImVec4(0x2F2F2F);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = HexToImVec4(0x2F2F2F);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = HexToImVec4(0x2F2F2F);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0, 0, 0, 0);

    // Borders
    style.Colors[ImGuiCol_Border] = HexToImVec4(0x272727);
    style.Colors[ImGuiCol_Separator] = HexToImVec4(0x272727);

    // Buttons
    style.Colors[ImGuiCol_Button] = HexToImVec4(0x1F1F1F);
    style.Colors[ImGuiCol_ButtonHovered] = HexToImVec4(0x2A2A2A); // Distinct hover color
    style.Colors[ImGuiCol_ButtonActive] = HexToImVec4(0x1F1F1F, 0.5f);

    // Frames
    style.Colors[ImGuiCol_FrameBg] = HexToImVec4(0x1F1F1F);
    style.Colors[ImGuiCol_FrameBgHovered] = HexToImVec4(0x2A2A2A); // Distinct hover color
    style.Colors[ImGuiCol_FrameBgActive] = HexToImVec4(0x1F1F1F, 0.5f);

    // Headers (affecting Selectable)
    style.Colors[ImGuiCol_Header] = HexToImVec4(0x2F2F2F);
    style.Colors[ImGuiCol_HeaderHovered] = HexToImVec4(0x3A3A3A); // This is the key change for Selectable hover
    style.Colors[ImGuiCol_HeaderActive] = HexToImVec4(0x2F2F2F, 0.5f);
}