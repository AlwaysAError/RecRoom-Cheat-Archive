#pragma once
#include "C:\Users\mikep\OneDrive\Desktop\astolfomocha\ImGui DirectX 11 Kiero Hook\includes.h"

extern ImFont* icons;

inline std::string ToLower(const char* str) {
    std::string s(str);
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

void AssetSpawnTab()
{
    ImGui::PushFont(icons);
    ImGui::Text(ICON_FA_BOX);
    ImGui::PopFont();
    ImGui::SameLine();
    ImGui::TextDisabled("Asset Spawn Modules");

    ImGui::Separator();
    // --- Search Box --- 
    static char searchBuf[128] = "";
    ImGui::InputText("Search Prefabs", searchBuf, IM_ARRAYSIZE(searchBuf));
    ImGui::Separator();

    ImGui::Text("Prefabs:");

    // Scrollable child for prefab list 
    if (ImGui::BeginChild("PrefabList", ImVec2(0, 350), true)) {
        std::string search = ToLower(searchBuf);
        for (size_t i = 0; i < IM_ARRAYSIZE(globals::network::list); i++) {
            const char* prefabName = globals::network::list[i];

            // Case-insensitive contains check 
            if (!search.empty()) {
                std::string prefabLower = ToLower(prefabName);
                if (prefabLower.find(search) == std::string::npos) {
                    continue; // skip if search text not found 
                }
            }

            if (ImGui::Selectable(prefabName, globals::network::selectedprefab == i)) {
                globals::network::selectedprefab = static_cast<int>(i);
            }
        }
        ImGui::EndChild();
    }

    // Show which prefab is selected 
    if (globals::network::selectedprefab >= 0) {
        ImGui::Text("Selected: %s", globals::network::list[globals::network::selectedprefab]);
        globals::network::selectedPrefabName = globals::network::list[globals::network::selectedprefab];
    }

    ImGui::Custom::Toggle("Custom Position", &globals::network::custompos);
    if (globals::network::custompos) {
        ImGui::SliderFloat("Position X", &globals::network::prefabpos.x, 0.0f, 100.0f);
        ImGui::SliderFloat("Position Y", &globals::network::prefabpos.y, 0.0f, 100.0f);
        ImGui::SliderFloat("Position Z", &globals::network::prefabpos.z, 0.0f, 100.0f);
    }

    ImGui::Custom::Toggle("Custom Rotation", &globals::network::customrot);
    if (globals::network::customrot) {
        ImGui::SliderFloat("Rotation X", &globals::network::prefabrot.x, -360.0f, 360.0f);
        ImGui::SliderFloat("Rotation Y", &globals::network::prefabrot.y, -360.0f, 360.0f);
        ImGui::SliderFloat("Rotation Z", &globals::network::prefabrot.z, -360.0f, 360.0f);
    }
    ImGui::Custom::Toggle("Custom Scale", &globals::network::customscale);
    if (globals::network::customscale) {
        ImGui::SliderFloat("Scale", &globals::network::prefabscale, 0.100, 100.0f);
    }

    ImGui::SliderInt("Amount", &globals::network::prefabamount, 1, 100);
    

    if (ImGui::Button("Tool Spawn")) {
        globals::network::spawnasset = true;
    }


}