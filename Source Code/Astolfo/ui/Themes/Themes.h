#pragma once


void ApplyThemes() {
	ImGuiStyle& style = ImGui::GetStyle();

	style.TabRounding = 4;
	style.ScrollbarRounding = 9;
	style.WindowRounding = 7;
	style.GrabRounding = 3;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ChildRounding = 4;
	style.FramePadding = ImVec2(6.0f, 6.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.0f, 1.0f, 1.0f, 0.3605149984359741f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.206007182598114f, 0.2060065567493439f, 0.2060086131095886f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2588235437870026f, 0.2588235437870026f, 0.2588235437870026f, 0.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 0.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.2352941185235977f, 0.2352941185235977f, 0.2352941185235977f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.9885146617889404f, 0.6180257797241211f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.9882352948188782f, 0.6196078658103943f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.9843056797981262f, 0.4935622215270996f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.991466224193573f, 0.725321888923645f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.991466224193573f, 0.725321888923645f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.4509803950786591f, 1.0f, 0.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 0.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}