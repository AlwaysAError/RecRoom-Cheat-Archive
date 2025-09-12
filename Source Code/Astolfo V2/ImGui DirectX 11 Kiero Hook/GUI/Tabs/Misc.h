#pragma once
#include "C:\Users\mikep\OneDrive\Desktop\astolfomocha\ImGui DirectX 11 Kiero Hook\includes.h"
extern ImFont* icons;

void MiscTab()
{
	ImGui::PushFont(icons);
	ImGui::Text(ICON_FA_CUBE);
	ImGui::PopFont();
	ImGui::SameLine();
	ImGui::TextDisabled("Misc Modules");

	ImGui::Separator();
	ImGui::Custom::Toggle("Trial Clothing", &globals::inventory::clothing);
	ImGui::Custom::Toggle("Unlock Keys", &globals::inventory::unlockkeys);
	ImGui::Custom::Toggle("Share Camera", &globals::inventory::sharecamera);
	ImGui::Custom::Toggle("Clothing Customizer", &globals::inventory::clothingcustomizer);
	ImGui::Custom::Toggle("Streamer Camera", &globals::inventory::steamercamera);
	ImGui::Custom::Toggle("Developer", &globals::player::developer);

}
