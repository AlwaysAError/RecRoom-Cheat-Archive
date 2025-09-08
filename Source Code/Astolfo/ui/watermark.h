#pragma once
#include "../imgui/imgui.h"
#include <string>
#include "../includes.h"
#include <functional>  
#include <cstdlib>    





const char* buildver = "dev"; //add checks to it i dont care at this point -25.10.2021


const std::string watermark = "astolfo.wtf | " + std::string(buildver);
ImVec2 watermarkSize{ 0, 40 };



bool firstexec = false;
std::size_t watermarkHash = 0;


std::size_t CalculateDevHash(const std::string& input) {
    return std::hash<std::string>{}(input);
}

ImVec4 InterpolateColor(const ImVec4& color1, const ImVec4& color2, float t)
{
    float inverse_t = 1.0f - t;
    return ImVec4(
        inverse_t * color1.x + t * color2.x,
        inverse_t * color1.y + t * color2.y,
        inverse_t * color1.z + t * color2.z,
        color1.w);
}


void GradientText(const char* text, float speed, const ImVec4& color1, const ImVec4& color2, ImVec2* position = nullptr)
{
    if (position) {
        ImGui::SetCursorPos(*position);
    }

    float time = ImGui::GetTime() * speed;
    float gradientStep = 1.0f / strlen(text);

    for (int i = 0; i < strlen(text); ++i)
    {
        float t = fmodf(time - i * gradientStep, 2.0f);

        if (t > 1.0f)
            t = 2.0f - t;

        ImVec4 color = InterpolateColor(color1, color2, t);

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::Text("%c", text[i]);
        ImGui::SameLine(0, 0);
        ImGui::PopStyleColor();
    }
    ImGui::NewLine();
} // i f

void WaterMark() {

    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiStyle backup_style = style;
    ImVec4* colors = style.Colors;
    ImVec4 backup_colors[ImGuiCol_COUNT];
    memcpy(backup_colors, colors, sizeof(backup_colors));


    style.WindowPadding = ImVec2(8, 8);
    style.FramePadding = ImVec2(6, 4);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.WindowRounding = 6.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;

    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.14f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.11f, 0.14f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.30f, 0.60f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.22f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.20f, 0.35f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.28f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.20f, 0.90f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.25f, 0.35f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.70f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.26f, 0.41f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.31f, 0.46f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.35f, 0.85f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.35f, 0.45f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.45f, 0.55f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.35f, 0.85f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.35f, 0.45f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.45f, 0.55f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.28f, 0.85f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.35f, 0.35f, 0.45f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.30f, 0.38f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.30f, 0.30f, 0.35f, 0.75f);
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.45f, 0.45f, 0.50f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.16f, 0.95f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.19f, 0.26f, 0.80f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.28f, 0.25f, 0.35f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.34f, 0.30f, 0.42f, 1.00f);


    if (!firstexec)
    {
        watermarkHash = CalculateDevHash(watermark);
        firstexec = true;
    }
    else
    {
        if (watermarkHash != CalculateDevHash(watermark))
            exit(-1);
    }

    if (watermarkSize.x == 0.0f && watermarkSize.y == 0.0f) {
        watermarkSize = ImGui::CalcTextSize(watermark.c_str());
    }

    ImGui::SetNextWindowSize(watermarkSize);
    ImGui::SetNextWindowBgAlpha(0.75f);
    ImGui::SetNextWindowPos({ 0.5, 0 });
    ImGui::Begin("watermark", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoBringToFrontOnFocus);


    // Matching the UI's pink/purple style
    ImVec4 lightPink = ImVec4(0.988f, 0.619f, 1.0f, 1.0f);  // #FC9EFF-ish, matches buttons/headers
    ImVec4 darkPink = ImVec4(0.991f, 0.451f, 0.941f, 1.0f);  // #FB73F0-ish, deeper pink/purple



    GradientText(watermark.c_str(), 0.7f, lightPink, darkPink);


    ImGui::End();

    memcpy(colors, backup_colors, sizeof(backup_colors));
    style = backup_style;
    ImGui::SetNextWindowPos(ImVec2(0.5, 0));
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("dvd watermark window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar);

    ImGui::End();
}