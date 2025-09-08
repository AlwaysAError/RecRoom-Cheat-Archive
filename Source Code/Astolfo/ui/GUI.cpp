#include "GUI.h"
#include "..\globals\globals.h"
#include "..\includes.h"
#include "..\imgui\custom.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>

bool GUI::Opened = false;
ImVec2 GUI::WindowPos = ImVec2(500, 100);
ImVec2 GUI::WindowSize = ImVec2(500, 700);
ImVec2 GUI::AssetSpawnPos = ImVec2(600, 150);
ImVec2 GUI::AssetSpawnSize = ImVec2(400, 400);
ImVec2 GUI::FoodSpawnPos = ImVec2(650, 200);
ImVec2 GUI::FoodSpawnSize = ImVec2(400, 400);
bool GUI::ConfigLoaded = false;

bool GUI::IsOpened() {
    return Opened;
}

inline std::string ToLower(const char* str) {
    std::string s(str);
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

void GUI::SaveConfig(const char* filename) {
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) return;
    file << "WindowPosX " << WindowPos.x << "\n";
    file << "WindowPosY " << WindowPos.y << "\n";
    file << "WindowSizeX " << WindowSize.x << "\n";
    file << "WindowSizeY " << WindowSize.y << "\n";
    file << "AssetSpawnPosX " << AssetSpawnPos.x << "\n";
    file << "AssetSpawnPosY " << AssetSpawnPos.y << "\n";
    file << "AssetSpawnSizeX " << AssetSpawnSize.x << "\n";
    file << "AssetSpawnSizeY " << AssetSpawnSize.y << "\n";
    file << "FoodSpawnPosX " << FoodSpawnPos.x << "\n";
    file << "FoodSpawnPosY " << FoodSpawnPos.y << "\n";
    file << "FoodSpawnSizeX " << FoodSpawnSize.x << "\n";
    file << "FoodSpawnSizeY " << FoodSpawnSize.y << "\n";
    file << "Spinbot " << globals::player::spinbot << "\n";
    file << "Developer " << globals::player::developer << "\n";
    file << "FOVToggle " << globals::player::fovtoggle << "\n";
    file << "FOV " << globals::player::fov << "\n";
    file << "SpeedToggle " << globals::player::speedtoggle << "\n";
    file << "Speed " << globals::player::speed << "\n";
    file << "UnlockKeys " << globals::inventory::unlockkeys << "\n";
    file << "ShareCamera " << globals::inventory::sharecamera << "\n";
    file << "SteamerCamera " << globals::inventory::steamercamera << "\n";
    file << "ClothingCustomizer " << globals::inventory::clothingcustomizer << "\n";
    file << "Clothing " << globals::inventory::clothing << "\n";
    file << "DisableUnequip " << globals::network::disableuneqipfromslots << "\n";
    file << "DisableGoToRoom " << globals::network::disablegotoroom << "\n";
    file << "DisableBannerCV2 " << globals::network::disablebannercv2 << "\n";
    file << "DisableRAMCheer " << globals::network::disableramcrashcheer << "\n";
    file << "DisableRAMBullets " << globals::network::disableramcrashbullets << "\n";
    file << "AssetSpawn " << globals::ui::assetspawn << "\n";
    file << "FoodSpawn " << globals::ui::foodspawn << "\n";
    file << "StaticFly " << globals::movement::staticfly << "\n";
    file << "DynamicFly " << globals::movement::dynamicfly << "\n";
    file << "RapidFire " << globals::combat::rapidfire << "\n";
    file << "InfiniteAmmo " << globals::combat::infiniteammo << "\n";
    file << "NoRecoil " << globals::combat::norecoil << "\n";
    file << "FastBullets " << globals::combat::fastbullets << "\n";
    file << "HoldToFire " << globals::combat::holdtofire << "\n";
    file << "CubeOfBullets " << globals::combat::cubeofbullets << "\n";
    file << "CustomBullet " << globals::combat::custombullet << "\n";
    file << "BulletAmount " << globals::combat::buletamount << "\n";
    file << "CustomPos " << globals::network::custompos << "\n";
    file << "CustomRot " << globals::network::customrot << "\n";
    file << "CustomScale " << globals::network::customscale << "\n";
    file << "PrefabAmount " << globals::network::prefabamount << "\n";
    file << "CustomFood " << globals::network::customfood << "\n";
    file << "CustomFoodAmount " << globals::network::customfoodamount << "\n";
    file << "FoodCount " << globals::network::foodcount << "\n";
    file << "CustomFoodSize " << globals::network::customfoodsize << "\n";
    file << "FoodSize " << globals::network::foodsize << "\n";
    file << "CustomFoodPosition " << globals::network::customfoodposition << "\n";
    file << "FoodPositionX " << globals::network::foodposition.x << "\n";
    file << "FoodPositionY " << globals::network::foodposition.y << "\n";
    file << "FoodPositionZ " << globals::network::foodposition.z << "\n";
    file << "CustomFoodRotation " << globals::network::customfoodrotation << "\n";
    file << "RandomRotation " << globals::network::randomrotation << "\n";
    file << "FoodRotationX " << globals::network::foodrotation.x << "\n";
    file << "FoodRotationY " << globals::network::foodrotation.y << "\n";
    file << "FoodRotationZ " << globals::network::foodrotation.z << "\n";
    file.close();
}

void GUI::LoadConfig(const char* filename) {
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;
        if (key == "WindowPosX") iss >> WindowPos.x;
        else if (key == "WindowPosY") iss >> WindowPos.y;
        else if (key == "WindowSizeX") iss >> WindowSize.x;
        else if (key == "WindowSizeY") iss >> WindowSize.y;
        else if (key == "AssetSpawnPosX") iss >> AssetSpawnPos.x;
        else if (key == "AssetSpawnPosY") iss >> AssetSpawnPos.y;
        else if (key == "AssetSpawnSizeX") iss >> AssetSpawnSize.x;
        else if (key == "AssetSpawnSizeY") iss >> AssetSpawnSize.y;
        else if (key == "FoodSpawnPosX") iss >> FoodSpawnPos.x;
        else if (key == "FoodSpawnPosY") iss >> FoodSpawnPos.y;
        else if (key == "FoodSpawnSizeX") iss >> FoodSpawnSize.x;
        else if (key == "FoodSpawnSizeY") iss >> FoodSpawnSize.y;
        else if (key == "Spinbot") iss >> globals::player::spinbot;
        else if (key == "Developer") iss >> globals::player::developer;
        else if (key == "FOVToggle") iss >> globals::player::fovtoggle;
        else if (key == "FOV") iss >> globals::player::fov;
        else if (key == "SpeedToggle") iss >> globals::player::speedtoggle;
        else if (key == "Speed") iss >> globals::player::speed;
        else if (key == "UnlockKeys") iss >> globals::inventory::unlockkeys;
        else if (key == "ShareCamera") iss >> globals::inventory::sharecamera;
        else if (key == "SteamerCamera") iss >> globals::inventory::steamercamera;
        else if (key == "ClothingCustomizer") iss >> globals::inventory::clothingcustomizer;
        else if (key == "Clothing") iss >> globals::inventory::clothing;
        else if (key == "DisableUnequip") iss >> globals::network::disableuneqipfromslots;
        else if (key == "DisableGoToRoom") iss >> globals::network::disablegotoroom;
        else if (key == "DisableBannerCV2") iss >> globals::network::disablebannercv2;
        else if (key == "DisableRAMCheer") iss >> globals::network::disableramcrashcheer;
        else if (key == "DisableRAMBullets") iss >> globals::network::disableramcrashbullets;
        else if (key == "AssetSpawn") iss >> globals::ui::assetspawn;
        else if (key == "FoodSpawn") iss >> globals::ui::foodspawn;
        else if (key == "StaticFly") iss >> globals::movement::staticfly;
        else if (key == "DynamicFly") iss >> globals::movement::dynamicfly;
        else if (key == "RapidFire") iss >> globals::combat::rapidfire;
        else if (key == "InfiniteAmmo") iss >> globals::combat::infiniteammo;
        else if (key == "NoRecoil") iss >> globals::combat::norecoil;
        else if (key == "FastBullets") iss >> globals::combat::fastbullets;
        else if (key == "HoldToFire") iss >> globals::combat::holdtofire;
        else if (key == "CubeOfBullets") iss >> globals::combat::cubeofbullets;
        else if (key == "CustomBullet") iss >> globals::combat::custombullet;
        else if (key == "BulletAmount") iss >> globals::combat::buletamount;
        else if (key == "CustomPos") iss >> globals::network::custompos;
        else if (key == "CustomRot") iss >> globals::network::customrot;
        else if (key == "CustomScale") iss >> globals::network::customscale;
        else if (key == "PrefabAmount") iss >> globals::network::prefabamount;
        else if (key == "CustomFood") iss >> globals::network::customfood;
        else if (key == "CustomFoodAmount") iss >> globals::network::customfoodamount;
        else if (key == "FoodCount") iss >> globals::network::foodcount;
        else if (key == "CustomFoodSize") iss >> globals::network::customfoodsize;
        else if (key == "FoodSize") iss >> globals::network::foodsize;
        else if (key == "CustomFoodPosition") iss >> globals::network::customfoodposition;
        else if (key == "FoodPositionX") iss >> globals::network::foodposition.x;
        else if (key == "FoodPositionY") iss >> globals::network::foodposition.y;
        else if (key == "FoodPositionZ") iss >> globals::network::foodposition.z;
        else if (key == "CustomFoodRotation") iss >> globals::network::customfoodrotation;
        else if (key == "RandomRotation") iss >> globals::network::randomrotation;
        else if (key == "FoodRotationX") iss >> globals::network::foodrotation.x;
        else if (key == "FoodRotationY") iss >> globals::network::foodrotation.y;
        else if (key == "FoodRotationZ") iss >> globals::network::foodrotation.z;
    }
    file.close();
    ConfigLoaded = true;
}

void GUI::Render() {
    if (!Opened) return;
    ImGuiCond condition = ConfigLoaded ? ImGuiCond_Always : ImGuiCond_FirstUseEver;
    ImGui::SetNextWindowPos(WindowPos, condition);
    ImGui::SetNextWindowSize(WindowSize, condition);
    ImGui::SetNextWindowSizeConstraints(ImVec2(345, 455), ImGui::GetIO().DisplaySize);
    ImGui::SetNextWindowBgAlpha(0.8f);
    ImGui::Begin("astolfo.wtf");
    if (!ConfigLoaded) {
        WindowPos = ImGui::GetWindowPos();
        WindowSize = ImGui::GetWindowSize();
    }
    else {
        ConfigLoaded = false;
    }
    ImGui::Text("Player");
    ImGui::Separator();
    ImGui::Custom::Toggle("Spinbot", &globals::player::spinbot);
    ImGui::Custom::Toggle("Developer", &globals::player::developer);
    ImGui::Custom::Toggle("FOV Toggle", &globals::player::fovtoggle);
    if (globals::player::fovtoggle)
        ImGui::SliderFloat("FOV", &globals::player::fov, 30.0f, 150.0f);
    ImGui::Separator();
    ImGui::Text("Inventory");
    ImGui::Custom::Toggle("Unlock Keys", &globals::inventory::unlockkeys);
    ImGui::Custom::Toggle("Share Camera", &globals::inventory::sharecamera);
    ImGui::Custom::Toggle("Steamer Camera", &globals::inventory::steamercamera);
    ImGui::Custom::Toggle("Clothing Customizer", &globals::inventory::clothingcustomizer);
    ImGui::Custom::Toggle("Clothing", &globals::inventory::clothing);
    ImGui::Separator();
    ImGui::Text("Network");
    ImGui::Custom::Toggle("Disable Unequip From Slots", &globals::network::disableuneqipfromslots);
    ImGui::Custom::Toggle("Disable Go To Room", &globals::network::disablegotoroom);
    ImGui::Custom::Toggle("Disable Banner CV2", &globals::network::disablebannercv2);
    ImGui::Custom::Toggle("Disable RAM Crash Cheer", &globals::network::disableramcrashcheer);
    ImGui::Custom::Toggle("Disable RAM Crash Bullets", &globals::network::disableramcrashbullets);
    ImGui::Custom::Toggle("Asset Spawn Window", &globals::ui::assetspawn);
    ImGui::Custom::Toggle("Food Spawn Window", &globals::ui::foodspawn);
    ImGui::Custom::Toggle("Playerlist Window", &globals::ui::playerlistwindow);
    ImGui::Separator();
    ImGui::Text("Movement");
    ImGui::Custom::Toggle("Static Fly", &globals::movement::staticfly);
    ImGui::Custom::Toggle("Dynamic Fly", &globals::movement::dynamicfly);
    ImGui::Custom::Toggle("Speed Toggle", &globals::player::speedtoggle);
    if (globals::player::speedtoggle) {
        if (ImGui::SliderFloat("Speed", &globals::player::speed, 3.5f, 100.0f))
            globals::player::changespeed = true;
    }
    ImGui::Separator();
    ImGui::Text("Combat");
    ImGui::Custom::Toggle("Rapid Fire", &globals::combat::rapidfire);
    ImGui::Custom::Toggle("Infinite Ammo", &globals::combat::infiniteammo);
    ImGui::Custom::Toggle("No Recoil", &globals::combat::norecoil);
    ImGui::Custom::Toggle("Fast Bullets", &globals::combat::fastbullets);
    ImGui::Custom::Toggle("Hold To Fire", &globals::combat::holdtofire);
    ImGui::Custom::Toggle("Cube Of Bullets", &globals::combat::cubeofbullets);
    ImGui::Custom::Toggle("Custom Bullet Amount", &globals::combat::custombullet);
    ImGui::SliderInt("Bullet Amount", &globals::combat::buletamount, 1, 100);
    ImGui::Separator();
    if (ImGui::Button("Save Config"))
        SaveConfig("config.txt");
    if (ImGui::Button("Load Config"))
        LoadConfig("config.txt");
    ImGui::End();
}

void GUI::RenderExtra() {
    ImGuiCond condition = ConfigLoaded ? ImGuiCond_Always : ImGuiCond_FirstUseEver;

    if (globals::ui::foodspawn) {
        ImGui::SetNextWindowPos(FoodSpawnPos, condition);
        ImGui::SetNextWindowSize(FoodSpawnSize, condition);
        ImGui::SetNextWindowBgAlpha(0.8f);
        ImGui::Begin("Foodsploit Config Window");
        if (!ConfigLoaded) {
            FoodSpawnPos = ImGui::GetWindowPos();
            FoodSpawnSize = ImGui::GetWindowSize();
        }
        static int currentFood = 0;
        const char* currentLabel = globals::network::Guid[currentFood].frie;
        const char* foodGuid = globals::network::Guid[currentFood].guid;
        ImGui::Custom::Toggle("Foodsploit", &globals::network::foodsploit);
        if (globals::network::foodsploit) {
            ImGui::Custom::Toggle("Custom Food", &globals::network::customfood);
            if (globals::network::customfood) {
                if (ImGui::BeginCombo("Select Food", globals::network::Guid[currentFood].frie)) {
                    for (int i = 0; i < globals::network::GuidCount; i++) {
                        bool isSelected = (currentFood == i);
                        if (ImGui::Selectable(globals::network::Guid[i].frie, isSelected)) {
                            currentFood = i;
                            globals::network::foodGuid = globals::network::Guid[i].guid;
                        }
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            }
            ImGui::Custom::Toggle("Custom Food Amount", &globals::network::customfoodamount);
            if (globals::network::customfoodamount)
                ImGui::SliderInt("Food Amount", &globals::network::foodcount, 1, 500);
            ImGui::Custom::Toggle("Custom Food Size", &globals::network::customfoodsize);
            if (globals::network::customfoodsize)
                ImGui::SliderFloat("Food Size", &globals::network::foodsize, 0.1f, 100.0f);
            ImGui::Custom::Toggle("Custom Food Position", &globals::network::customfoodposition);
            if (globals::network::customfoodposition) {
                ImGui::SliderFloat("Position X##1", &globals::network::foodposition.x, 0.1f, 100.0f);
                ImGui::SliderFloat("Position Y##2", &globals::network::foodposition.y, 0.1f, 100.0f);
                ImGui::SliderFloat("Position Z##3", &globals::network::foodposition.z, 0.1f, 100.0f);
            }
            ImGui::Custom::Toggle("Custom Food Rotation", &globals::network::customfoodrotation);
            if (globals::network::customfoodrotation) {
                ImGui::SliderFloat("Rotation X##4", &globals::network::foodrotation.x, 0.0f, 360.0f);
                ImGui::SliderFloat("Rotation Y##5", &globals::network::foodrotation.y, 0.0f, 360.0f);
                ImGui::SliderFloat("Rotation Z##6", &globals::network::foodrotation.z, 0.0f, 360.0f);
            }
            ImGui::Custom::Toggle("Random Rotation", &globals::network::randomrotation);
        }
        ImGui::End();
    }

    if (globals::ui::assetspawn) {
        ImGui::SetNextWindowPos(AssetSpawnPos, condition);
        ImGui::SetNextWindowSize(AssetSpawnSize, condition);
        ImGui::SetNextWindowBgAlpha(0.8f);
        ImGui::Begin("Asset Spawn Config Window");

        if (!ConfigLoaded) {
            AssetSpawnPos = ImGui::GetWindowPos();
            AssetSpawnSize = ImGui::GetWindowSize();
        }

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

        if (ImGui::Button("Spawn")) {
            globals::network::spawnasset = true;
        }

        if (ImGui::Button("Force Equip")) {
            globals::network::forceequip = true;
        }

        ImGui::End();
    }

    if (globals::ui::playerlistwindow) {
        ImGui::SetNextWindowPos(ImVec2(750, 250), condition);
        ImGui::SetNextWindowSize(ImVec2(250, 400), condition);
        ImGui::SetNextWindowBgAlpha(0.8f);
        ImGui::Begin("Player List");

        // Search box for filtering players
        static char playerSearchBuf[128] = "";
        ImGui::InputText("Search Players", playerSearchBuf, IM_ARRAYSIZE(playerSearchBuf));
        ImGui::Separator();

        // Display player count
        ImGui::Text("Players Online: %d", (int)globals::network::playerList.size());
        ImGui::Separator();

        // List of special IDs that should get the [VMOD] tag
        static const std::vector<int> vmodIds = { 1852, 34641, 88815, 347497, 277089, 31469, 1126, 11675, 19517, 3560,
    79211, 439000, 68758, 10665, 16270, 620745, 78666, 366937, 159154, 515033,
    638796, 319444, 170583, 1312288, 272386, 14940, 546806, 2312859, 203474, 481690,
    316681, 715200, 2527663, 418933, 805144, 2539447, 372074, 1424966, 733388, 1117791,
    1110889, 1751132, 447263, 2172278, 5731079, 2395704, 2881818, 659865, 156085, 493146,
    534186, 4080515, 1469774, 613951, 487637, 68792, 3912774, 1479520, 1210785, 872257, 699089,
    276676, 2290395, 1457431, 835842, 310916, 1232317, 395439, 655687, 2049822, 1832582, 7906190,
    195175, 3976829, 1671309, 860253, 2859795, 329824, 3710329, 311311, 9409892, 2135398, 1236914,
    6078720, 314074, 791214, 582917, 3083253, 678296, 622743, 6445187, 3254059, 2208153, 410754,
    1155163, 1736331, 2393578, 6597567, 1773739, 2004491, 4412145, 1697550, 4710826, 913154, 358788,
    1195466, 2331343, 352738, 10874001, 929446, 6328685, 228577, 4213153, 570960, 3179695, 39099,
    9775057, 1861473, 1304945, 1230392, 1052288, 4453911, 5326881, 4105018, 1460431, 1416963, 527321,
    48366317, 2057143, 64462359, 882822, 45098274, 1467035, 1311378, 156228, 1268602, 15184888, 224166,
    4121601, 3747531, 402301, 1634926, 555477, 1242268, 9526391, 132126, 4168358, 8493879, 12805529,
    144256, 8073816, 672036, 586891, 9310239, 287195, 1990632, 686783, 551129, 3294426, 885181, 79245113,
    14861915, 4795658, 21457774, 525133315, 11440809, 26875312, 56177294, 65151521, 35341784, 2312978,
    206193, 1164707769, 1854809, 9916, 121916, 1142357, 271562, 179907, 1717035, 1259740, 1563266, 489899,
    22187222, 13100926, 1461494, 47520, 8618408, 30816030, 254959, 1888434, 3161996, 3946295, 9942509,
    6615476, 11065378, 389368, 14465533, 386806, 17698129, 27886495, 31033344, 36810857, 32564489, 1276474,
    42336157, 59750188, 638716, 2129166, 334909, 5469781, 8359555, 13990274, 1925135981, 611024799, 1714923,
    485186, 6532522, 19890837, 37408764, 4468918, 786607, 1690275, 1732198, 8886115, 1835229688, 22385053,
    13, 80262228, 1819275, 12287016, 10527015, 103888, 16216953, 7904855, 9786604, 2175882, 20317778,
    5208215, 2052959, 556971, 6888038, 2908891, 21309981, 1172265, 1845925, 1649158, 64753088, 18530946,
    71737020, 10360396, 1977430, 1180899, 193935, 1814884, 2157695, 12003416, 1532281, 14520681, 18565040,
    1879954758, 19462921, 561663, 2618641, 256147, 279673, 1237535808, 2116276575, 53208, 27867014,
    369920562, 653078, 488146, 1901757890, 31827274, 75791266, 538365, 128016, 2651133, 1 };

        // Scrollable child for player list
        if (ImGui::BeginChild("PlayerList", ImVec2(0, 350), true)) {
            std::string search = ToLower(playerSearchBuf);

            for (size_t i = 0; i < globals::network::playerList.size(); i++) {
                const auto& player = globals::network::playerList[i];

                // Case-insensitive contains check for player name
                if (!search.empty()) {
                    std::string playerNameLower = ToLower(player.name.c_str());
                    if (playerNameLower.find(search) == std::string::npos) {
                        continue; // skip if search text not found
                    }
                }

                // Build player info string
                std::string playerInfo = player.name + " (ID: " + std::to_string(player.playerId) + ")";

                // Add [VMOD] tag if in the special ID list
                if (std::find(vmodIds.begin(), vmodIds.end(), player.playerId) != vmodIds.end()) {
                    playerInfo += " [VMOD]";
                }

                // Display player info with selectable item
                if (ImGui::Selectable(playerInfo.c_str())) {
                    globals::network::selectedPlayerName = player.name;
                    globals::network::selectedPlayerId = player.playerId;
                }

                // Right-click context menu for player actions
                if (ImGui::BeginPopupContextItem()) {
                    ImGui::Text("Player: %s", player.name.c_str());
                    ImGui::Text("ID: %d", player.playerId);
                    ImGui::Separator();

                    if (ImGui::MenuItem("Teleport To Player")) {
                        globals::network::teleportToPlayer = true;
                        globals::network::targetPlayerId = player.playerId;
                    }
                    if (ImGui::MenuItem("Projectile Orbit")) {
                        globals::network::witchorbit = true;
                        globals::network::targetPlayerId = player.playerId;
                    }
                    if (ImGui::MenuItem("Disarm Player")) {
                        globals::network::disarm = true;
                        globals::network::targetPlayerId = player.playerId;
                    }
                    if (ImGui::MenuItem("Bring Player")) {
                        globals::network::bring = true;
                        globals::network::targetPlayerId = player.playerId;
                    }

                    if (ImGui::MenuItem("Ram Crash")) {
                        globals::network::ramcrash = true;
                        globals::network::targetPlayerId = player.playerId;
                    }

                    if (ImGui::MenuItem("Copy Player Name")) {
                        ImGui::SetClipboardText(player.name.c_str());
                    }
                    if (ImGui::MenuItem("Copy Player ID")) {
                        std::string idStr = std::to_string(player.playerId);
                        ImGui::SetClipboardText(idStr.c_str());
                    }

                    ImGui::EndPopup();
                }

                // Tooltip with additional info
                if (ImGui::IsItemHovered()) {
                    ImGui::BeginTooltip();
                    ImGui::Text("Player: %s", player.name.c_str());
                    ImGui::Text("ID: %d", player.playerId);
                    ImGui::Text("Player Address: 0x%p", player.playerAddress);
                    ImGui::Text("Photon Address: 0x%p", player.photonPlayerAddress);
                    ImGui::Text("Networked View: 0x%p", player.networkedViewAddress);
                    ImGui::Text("Right-click for options");
                    ImGui::EndTooltip();
                }
            }
            ImGui::EndChild();
        }



        // Clear selection button
        ImGui::SameLine();
        if (ImGui::Button("Clear Selection")) {
            globals::network::selectedPlayerName = "";
            globals::network::selectedPlayerId = -1;
        }

        // Display selected player info
        if (ImGui::Button("Disarm All"))
        {
            globals::network::disarmall = true;
        }

        ImGui::End();
    }
}