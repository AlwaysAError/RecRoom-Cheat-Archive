#pragma once
#include "C:\Users\mikep\OneDrive\Desktop\astolfomocha\ImGui DirectX 11 Kiero Hook\includes.h"
#include <fstream>
#include <sstream>
#include <iomanip>

extern ImFont* icons;

/* ---------- tiny reflection engine ---------- */
namespace config
{
    /* add every variable you want to persist here.
       syntax:  STORE(name, value)            – for primitives
               STORE_VEC(name, x, y, z)       – for float3
               STORE_VEC4(name, x, y, z, w)   – for float4  */
#define CONFIG_LIST(_)                                                          \
        /* Combat */                                                                \
        _(bool, globals::combat::rapidfire)                                         \
        _(bool, globals::combat::holdtofire)                                        \
        _(bool, globals::combat::norecoil)                                          \
        _(bool, globals::combat::fastbullets)                                       \
        _(bool, globals::combat::custombullet)                                      \
        _(int , globals::combat::buletamount)                                       \
                                                                                    \
        /* Movement */                                                              \
        _(bool, globals::movement::dynamicfly)                                      \
        _(bool, globals::movement::staticfly)                                       \
        _(bool, globals::player::changespeed)                                       \
        _(float, globals::player::speed)                                            \
                                                                                    \
        /* Visual */                                                                \
        _(bool, globals::player::fovtoggle)                                         \
        _(float, globals::player::fov)                                              \
                                                                                    \
        /* Misc */                                                                  \
        _(bool, globals::inventory::clothing)                                       \
        _(bool, globals::inventory::unlockkeys)                                     \
        _(bool, globals::inventory::sharecamera)                                    \
        _(bool, globals::inventory::clothingcustomizer)                             \
        _(bool, globals::inventory::steamercamera)                                  \
        _(bool, globals::player::developer)                                         \
                                                                                    \
        /* Exploits */                                                              \
        /* (buttons are fire-and-forget – we do NOT store them) */                  \
                                                                                    \
        /* Anti-Exploits */                                                         \
        _(bool, globals::network::disableuneqipfromslots)                           \
        _(bool, globals::network::disablegotoroom)                                  \
        _(bool, globals::network::disablebannercv2)                                 \
        _(bool, globals::network::disableramcrashcheer)                             \
        _(bool, globals::network::disableramcrashbullets)                           \
                                                                                    \
        /* Asset spawn */                                                           \
        _(int , globals::network::selectedprefab)                                   \
        _(bool, globals::network::custompos)                                        \
        _(bool, globals::network::esp)                                              \
        _(float, globals::network::prefabpos.x)                                     \
        _(float, globals::network::prefabpos.y)                                     \
        _(float, globals::network::prefabpos.z)                                     \
        _(bool, globals::network::customrot)                                        \
        _(float, globals::network::prefabrot.x)                                     \
        _(float, globals::network::prefabrot.y)                                     \
        _(float, globals::network::prefabrot.z)                                     \
        _(bool, globals::network::customscale)                                      \
        _(float, globals::network::prefabscale)                                     \
        _(int , globals::network::prefabamount)                                     \

               /* ---------- generic save ---------- */
    inline void save(const std::string& path)
    {
        std::ofstream out(path);
        out << std::fixed << std::setprecision(6);

#define _(type, var)  out << #var << " = " << (var) << '\n';
        CONFIG_LIST(_)
#undef _

            out.close();
    }

    /* ---------- generic load ---------- */
    inline void load(const std::string& path)
    {
        std::ifstream in(path);
        if (!in.is_open()) return;

        std::string line;
        while (std::getline(in, line))
        {
            std::istringstream iss(line);
            std::string name, dummy;
            iss >> name >> dummy;          // consume " = "

#define _(type, var)                                        \
                if (name == #var) {                                     \
                    type val{}; iss >> val; var = val; continue;       \
                }
            CONFIG_LIST(_)
#undef _
        }
    }
}

/* ---------- ImGui tab ---------- */
void SettingsTab()
{
    ImGui::PushFont(icons);
    ImGui::Text(ICON_FA_GEAR);
    ImGui::PopFont();
    ImGui::SameLine();
    ImGui::TextDisabled("Settings");

    ImGui::Separator();

    if (ImGui::Button("Save Config"))
    {
        config::save("config.txt");
    }
    ImGui::SameLine();
    if (ImGui::Button("Load Config"))
    {
        config::load("config.txt");
    }

}