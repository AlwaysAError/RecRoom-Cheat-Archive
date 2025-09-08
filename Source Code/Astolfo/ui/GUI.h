#pragma once
#include "..\includes.h"
#include <string>

namespace GUI
{
    // -------------------- Main State --------------------
    extern bool Opened;
    bool IsOpened();
    extern bool ConfigLoaded;

    // -------------------- Window Position/Size --------------------
    extern ImVec2 WindowPos;
    extern ImVec2 WindowSize;

    // Extra windows
    extern ImVec2 AssetSpawnPos;
    extern ImVec2 AssetSpawnSize;
    extern ImVec2 FoodSpawnPos;
    extern ImVec2 FoodSpawnSize;

    // -------------------- Rendering --------------------
    void Render();
    void RenderExtra();

    // -------------------- Config --------------------
    void SaveConfig(const char* filename = "config.txt");
    void LoadConfig(const char* filename = "config.txt");
}
