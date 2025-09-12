#pragma once
#include "C:\Users\mikep\OneDrive\Desktop\astolfomocha\ImGui DirectX 11 Kiero Hook\includes.h"

extern ImFont* icons;

void CombatTab()
{

	ImGui::PushFont(icons);
	ImGui::Text(ICON_FA_GUN);
	ImGui::PopFont();
	ImGui::SameLine();
	ImGui::TextDisabled("Combat Modules");

	ImGui::Separator();
	ImGui::Custom::Toggle("Rapid Fire", &globals::combat::rapidfire);
	ImGui::Custom::Toggle("Loop Fire", &globals::combat::holdtofire);
	ImGui::Custom::Toggle("No Recoil", &globals::combat::norecoil);
	ImGui::Custom::Toggle("Fast Bullets", &globals::combat::fastbullets);
	ImGui::Custom::Toggle("Custom Bullet Ammount", &globals::combat::custombullet);
	if (globals::combat::custombullet)
	{
		ImGui::SliderInt("Bullet Amount", &globals::combat::buletamount, 1, 500);
	}
}