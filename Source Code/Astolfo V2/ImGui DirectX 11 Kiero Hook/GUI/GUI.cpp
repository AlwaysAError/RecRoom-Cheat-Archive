#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "GUI.h"
#include "..\utils\globals.h"
#include <vector>
#include <algorithm>
#include "Robot.h"
#include <winsock2.h>
#include "Font.h"
#include "IconsFontAwesome6.h"
#include "IconsFontAwesome6Brands.h"
#include "fabrands400.h"
#include "faregular400.h"
#include "fasolid900.h"
#include "..\imgui\imgui_internal.h"
#include "Tabs/AntiExploits.h"
#include "Tabs/Combat.h"
#include "Tabs/Movement.h"
#include "Tabs/Misc.h"
#include <iostream>
#include "Tabs/Visuals.h"
#include "Tabs/Exploits.h"
#include "Tabs/AssetSpawn.h"
#include "Tabs/Settings.h"
#pragma comment(lib, "ws2_32.lib")


ImFont* icons = nullptr;
ImFont* iconsBrands = nullptr;
ImFont* bigFont = nullptr;

ImVec4 InterpolateColor1(const ImVec4& color1, const ImVec4& color2, float t)
{
    float inverse_t = 1.0f - t;
    return ImVec4(
        inverse_t * color1.x + t * color2.x,
        inverse_t * color1.y + t * color2.y,
        inverse_t * color1.z + t * color2.z,
        color1.w);
}


void GradientText1(const char* text, float speed, const ImVec4& color1, const ImVec4& color2, ImVec2* position = nullptr)
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

        ImVec4 color = InterpolateColor1(color1, color2, t);

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::Text("%c", text[i]);
        ImGui::SameLine(0, 0);
        ImGui::PopStyleColor();
    }
    ImGui::NewLine();
} // i f

// We use an enum to make the tab integer more readable and less error-prone.
enum MenuTab {
    TAB_COMBAT,
    TAB_MOVEMENT,
    TAB_MISC,
    TAB_VISUALS,
    TAB_ANTI_EXPLOITS,
    TAB_EXPLOITS,
    TAB_ASSETS_SPAWN,
    TAB_ITEMS_SPAWN,
    TAB_THEMES,
    TAB_SETTINGS
};

// Static variable to store the current tab. It's static to retain its value between calls to Render().
static int currentTab = TAB_COMBAT;


static void SeparatorText(const char* label)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;
    ImGuiStyle& style = g.Style;

    ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    float line_y = window->DC.CursorPos.y + label_size.y * 0.5f + style.FramePadding.y * 0.5f;

    // Draw label
    ImGui::TextDisabled("%s", label);
    ImGui::SameLine();

    // Draw line starting after label
    ImVec2 start = ImVec2(window->DC.CursorPos.x + style.ItemSpacing.x, line_y);
    ImVec2 end = ImVec2(window->Pos.x + window->Size.x - style.WindowPadding.x, line_y);

    ImGui::GetWindowDrawList()->AddLine(start, end, ImGui::GetColorU32(ImGuiCol_Separator));

    // Move cursor below the line
    ImGui::Dummy(ImVec2(0.0f, label_size.y * 0.5f));
}




// New function to create a sidebar button with an icon and text
// This function is modified to take a tab ID and a pointer to the current tab.
bool SidebarButton(const char* icon, const char* label, int tabId, int* currentTab)
{
    // Define the colors for the button states
    ImVec4 activeColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White
    ImVec4 disabledColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Gray
    ImVec4 hoverColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Lighter gray for hover

    // Set the color based on whether the button is the currently active tab
    if (*currentTab == tabId) {
        ImGui::PushStyleColor(ImGuiCol_Text, activeColor);
    }
    else {
        ImGui::PushStyleColor(ImGuiCol_Text, disabledColor);
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, ImGui::GetStyle().FramePadding.y));
    ImGui::PushID(label);

    bool clicked = false;

    // Begin a group to handle the button logic
    ImGui::BeginGroup();

    // Manually render the icon and text
    ImGui::PushFont(icons);
    ImGui::TextUnformatted(icon);
    ImGui::PopFont();

    ImGui::SameLine();
    ImGui::TextUnformatted(label);

    ImGui::EndGroup();

    // Check if the group was clicked
    if (ImGui::IsItemClicked()) {
        clicked = true;
        *currentTab = tabId; // Update the current tab when clicked
    }
    else if (ImGui::IsItemHovered() && *currentTab != tabId) {
        // Change text color on hover if it's not the active tab
        ImGui::PopStyleColor(); // Pop the old color
        ImGui::PushStyleColor(ImGuiCol_Text, hoverColor);
    }


    ImGui::PopID();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    return clicked;
}


void GUI::InitializeFonts()
{
    ImGuiIO& io = ImGui::GetIO();


    io.Fonts->AddFontFromMemoryTTF(poppinsmedium, sizeof(poppinsmedium), 17.9f);


    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    static const ImWchar icons_ranges_brands[] = { ICON_MIN_FAB, ICON_MAX_16_FAB, 0 };

    ImFontConfig fa_config;
    fa_config.MergeMode = false;
    fa_config.PixelSnapH = true;
    icons = io.Fonts->AddFontFromMemoryTTF(fasolid900, sizeof(fasolid900), 16.0f, &fa_config, icons_ranges);
    io.Fonts->AddFontFromMemoryTTF(igot400regulargirlsand400regularguysonymdick, sizeof(igot400regulargirlsand400regularguysonymdick), 16.0f, &fa_config, icons_ranges);
    iconsBrands = io.Fonts->AddFontFromMemoryTTF(igot400bands, sizeof(igot400bands), 16.0f, &fa_config, icons_ranges_brands);
    bigFont = io.Fonts->AddFontFromMemoryTTF(poppinsmedium, sizeof(poppinsmedium), 18.0f);
}

void GUI::Render()
{
    ImGuiStyle& style = ImGui::GetStyle();

    const float SideBarWidth = 144;
    static ImVec2 MenuSize = ImVec2(570, 726);

    // Center the window
    ImVec2 MenuPos = ImVec2(
        (ImGui::GetIO().DisplaySize.x - MenuSize.x) * 0.5f,
        (ImGui::GetIO().DisplaySize.y - MenuSize.y) * 0.5f
    );

    ImGui::SetNextWindowSize(MenuSize, ImGuiCond_Once);
    ImGui::SetNextWindowPos(MenuPos, ImGuiCond_Once);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("menu", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoMove); // <-- Add this flagv
    ImGui::PopStyleVar(2);

    // Background split drawing
    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    ImVec2 rect1_max = ImVec2(pos.x + SideBarWidth, pos.y + size.y);
    drawList->AddRectFilled(pos, rect1_max,
        ImGui::GetColorU32(ImGuiCol_WindowBg),
        style.WindowRounding, ImDrawCornerFlags_Left);

    ImVec2 rect2_min = ImVec2(pos.x + SideBarWidth, pos.y);
    ImVec2 rect2_max = ImVec2(pos.x + size.x, pos.y + size.y);
    drawList->AddRectFilled(rect2_min, rect2_max,
        ImGui::GetColorU32(ImGuiCol_PopupBg),
        style.WindowRounding, ImDrawCornerFlags_Right);

    // Sidebar
    ImGui::BeginChild("SideBar", ImVec2(SideBarWidth, 0), true, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("LogoRect", ImVec2(0, ImGui::GetFontSize() + style.WindowPadding.y * 2), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::PopStyleColor();

    // Centered "Astolfo dev" with gradient
    {
        const char* projectName = "Astolfo";
        const char* commitHash = "v2";
        ImVec4 lightGray = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // A light gray
        ImVec4 darkGray = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);  // A dark gray

        ImVec2 textSize = ImGui::CalcTextSize(projectName);
        ImVec2 hashSize = ImGui::CalcTextSize(commitHash);
        float totalWidth = textSize.x + hashSize.x + ImGui::GetStyle().ItemSpacing.x;

        float cursorX = (ImGui::GetWindowWidth() - totalWidth) * 0.5f;
        ImGui::SetCursorPosX(cursorX);
        ImGui::SetCursorPosY(ImGui::GetStyle().WindowPadding.y);

        ImGui::BeginGroup();
        GradientText1(projectName, 2.0f, lightGray, darkGray);

        ImGui::SameLine();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);
        ImGui::TextDisabled(commitHash);
        ImGui::EndGroup();
    }
    ImGui::EndChild(); // LogoRect

    // Section header
    SeparatorText("PLAYER");
    {
        SidebarButton(ICON_FA_GUN, "Combat", TAB_COMBAT, &currentTab);
        SidebarButton(ICON_FA_PERSON_RUNNING, "Movement", TAB_MOVEMENT, &currentTab);
        SidebarButton(ICON_FA_CUBE, "Misc", TAB_MISC, &currentTab);
        SidebarButton(ICON_FA_EYE, "Visuals", TAB_VISUALS, &currentTab);
    }
    SeparatorText("NETWORK");
    {
        SidebarButton(ICON_FA_SHIELD_HALVED, "Anti-Exploits", TAB_ANTI_EXPLOITS, &currentTab);
        SidebarButton(ICON_FA_TRIANGLE_EXCLAMATION, "Exploits", TAB_EXPLOITS, &currentTab);
        SidebarButton(ICON_FA_BOX, "Assets Spawn", TAB_ASSETS_SPAWN, &currentTab);
    }
    SeparatorText("SETTINGS");
    {
        SidebarButton(ICON_FA_GEAR, "Settings", TAB_SETTINGS, &currentTab);
    }


    ImGui::EndChild(); // SideBar

    // Main content panel
    ImGui::SameLine();
    ImGui::BeginChild("MainContent", ImVec2(0, 0), true);

    // This is where you'd put the content for each tab.
    // The content is shown based on the value of 'currentTab'.
    switch (currentTab) {
    case TAB_COMBAT:
        CombatTab();
        break;
    case TAB_MOVEMENT:
        MovmentTab();
        break;
    case TAB_MISC:
        MiscTab();
        break;
    case TAB_VISUALS:
        VisualsTab();
        break;
    case TAB_ANTI_EXPLOITS:
        AntiExploitsTab();
        break;
    case TAB_EXPLOITS:
        ExploitsTab();
        break;
    case TAB_ASSETS_SPAWN:
        AssetSpawnTab();
        break;
    case TAB_SETTINGS:
         SettingsTab();
        break;
    default:
        ImGui::Text("Select a tab from the sidebar.");
        break;
    }

    ImGui::EndChild(); // MainContent
    ImGui::End(); // menu
}

void GUI::RenderExtra()
{
    static bool showPlayerList = true;
    static bool noCloseButton = true; // Flag to control X button

    if (showPlayerList)
    {
        float playerListWidth = 450.0f;
        float playerListHeight = 726.0f;
        ImVec2 playerListSize(playerListWidth, playerListHeight);

        ImVec2 mainMenuPos = ImVec2(
            (ImGui::GetIO().DisplaySize.x - 570) * 0.5f,
            (ImGui::GetIO().DisplaySize.y - 726) * 0.5f
        );
        ImVec2 playerListPos = ImVec2(mainMenuPos.x + 570 + 10, mainMenuPos.y);

        ImGui::SetNextWindowSize(playerListSize, ImGuiCond_Always);
        ImGui::SetNextWindowPos(playerListPos, ImGuiCond_Always);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGui::GetStyle().Colors[ImGuiCol_PopupBg]);

        // Pass nullptr if we want no close button
        bool* p_open = noCloseButton ? nullptr : &showPlayerList;

        if (ImGui::Begin("Player List", p_open,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings))
        {
            ImVec4 blue = ImVec4(0.2f, 0.5f, 0.9f, 1.0f);
            ImVec4 blueHovered = ImVec4(0.3f, 0.6f, 1.0f, 1.0f);
            ImVec4 blueActive = ImVec4(0.2f, 0.55f, 1.0f, 1.0f);

            ImGui::PushStyleColor(ImGuiCol_Header, blue);
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, blueHovered);
            ImGui::PushStyleColor(ImGuiCol_HeaderActive, blueActive);
            for (auto& player : globals::network::playerList)
            {
                if (!player.playerAddress) continue;

                ImGui::PushID(player.playerId);

                // Base dropdown label
                std::string dropdownLabel = "[" + std::to_string(player.playerindex + 1) + "] " + player.name.c_str() +
                    " (" + std::to_string(player.playerping) + "ms)";

                // VMOD list
                std::vector<int> vmodList = { 1852, 34641, 88815, 347497, 277089, 31469, 1126, 11675, 19517, 3560,
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
                if (std::find(vmodList.begin(), vmodList.end(), player.playerId) != vmodList.end())
                {
                    // Append VMOD tag
                    dropdownLabel += " ";
                    dropdownLabel += "[VMOD]";
                }

                // Draw collapsing header
                if (ImGui::CollapsingHeader(dropdownLabel.c_str()))
                {
                    ImGui::Separator();

                    if (ImGui::Button("Teleport To")) {
                        globals::network::targetPlayerId = player.playerId;
                        globals::network::teleportToPlayer = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Disarm Player")) {
                        globals::network::targetPlayerId = player.playerId;
                        globals::network::disarm = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Witch Orbit")) {
                        globals::network::targetPlayerId = player.playerId;
                        globals::network::witchorbit = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Force Equip Asset")) {
                        globals::network::targetPlayerId = player.playerId;
                        globals::network::forceequip = true;
                    }
                    if (ImGui::Button("Ram Crash")) {
                        globals::network::targetPlayerId = player.playerId;
                        globals::network::ramcrash = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Bring Plr (ROOMS 2.0)")) {
                        globals::network::targetPlayerId = player.playerId;
                        globals::network::bringplr = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Void Plr (ROOMS 2.0)")) {
                        globals::network::targetPlayerId = player.playerId;
                        globals::network::voidplayers = true;
                    }
                    if (ImGui::Button("Fuck Plr")) {
                        globals::network::targetPlayerId = player.playerId;
                        globals::network::test = true;
                    }
                    

                }

                ImGui::PopID();
            }


            ImGui::PopStyleColor(3);
        }
        ImGui::End();

        ImGui::PopStyleColor();
    }
}

bool ValidateKey(const std::string& key)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return false;
    }

    // Server info (HTTP, plain port 80)
    const std::string host = "niger.com";
    const int port = 80;

    hostent* remoteHost = gethostbyname(host.c_str());
    if (!remoteHost) {
        closesocket(sock);
        WSACleanup();
        return false;
    }

    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = *((unsigned long*)remoteHost->h_addr);

    if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) != 0) {
        closesocket(sock);
        WSACleanup();
        return false;
    }

    // Build HTTP POST request
    std::string body = "{\"key\":\"" + key + "\"}";
    std::string request =
        "POST /validate HTTP/1.1\r\n"
        "Host: " + host + "\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n\r\n" +
        body;

    send(sock, request.c_str(), static_cast<int>(request.size()), 0);

    // Receive response
    char buffer[4096];
    std::string response;
    int bytesReceived = 0;
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        response.append(buffer, bytesReceived);
    }

    closesocket(sock);
    WSACleanup();

    // Simple HTTP body extraction
    size_t pos = response.find("\r\n\r\n");
    if (pos != std::string::npos) {
        std::string body = response.substr(pos + 4);

        if (body == "Key valid") return true;
        else return false; // invalid or expired
    }

    return false;
}


void GUI::AntiSkid()
{
    static char inputBuffer[128] = {};
    static bool verified = false;

    if (verified)
        return; // Already verified

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 displaySize = io.DisplaySize;
    ImVec2 windowSize(450, 180);
    ImVec2 windowPos((displaySize.x - windowSize.x) * 0.5f,
        (displaySize.y - windowSize.y) * 0.5f);

    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.5f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);

    if (ImGui::Begin("key verification", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::TextWrapped("Please Enter Your Key:");
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.2f, 1.0f), "\"Get Your Key From discord.gg/astolfolovers\"");
        ImGui::Spacing();

        // Darker InputText background
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
        ImGui::InputText("##AntiSkidInput", inputBuffer, sizeof(inputBuffer));
        ImGui::PopStyleColor(2); // restore colors

        ImGui::Spacing();

        // Dark buttons
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));

        if (ImGui::Button("Enter") || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
        {
            std::string inputStr(inputBuffer);

            // Call your network key validation
            if (ValidateKey(inputStr))
            {
                globals::network::passedverification = true;
                verified = true;
                memset(inputBuffer, 0, sizeof(inputBuffer));
            }
            else
            {
                // Optional: notify user the key is invalid
                ImGui::OpenPopup("Invalid Key");
            }
        }

        ImGui::PopStyleColor(3);

        // Invalid key popup
        if (ImGui::BeginPopupModal("Invalid Key", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("The key you entered is invalid.");
            if (ImGui::Button("OK"))
            {
                ImGui::CloseCurrentPopup();
                memset(inputBuffer, 0, sizeof(inputBuffer));
            }
            ImGui::EndPopup();
        }
    }

    ImGui::End();
    ImGui::PopStyleVar(2);
}


struct Vector3 {
    float x;
    float y;
    float z;

    // Constructors
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}              // Default to (0,0,0)
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {} // Custom values

    // Operator overloads for convenience
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Check if zero vector
    bool isZero() const {
        return x == 0.0f && y == 0.0f && z == 0.0f;
    }
};


void GUI::RenderEsp() {
    if (!globals::network::esp)
        return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    ImVec2 screenSize = ImGui::GetIO().DisplaySize;
    ImVec2 screenCenter = ImVec2(screenSize.x * 0.5f, screenSize.y * 0.5f);

    // Static variables for tracking the currently hovered player
    static int hoveredPlayerId = -1;
    static ImVec2 hoveredPlayerScreenPos = ImVec2(0, 0);
    static float minDistance = 99999.0f;

    // Static variables to lock the position when 'R' is pressed
    static int lockedPlayerId = -1;
    static ImVec2 lockedPlayerScreenPos = ImVec2(0, 0);

    // Reset for the new frame
    hoveredPlayerId = -1;
    minDistance = 99999.0f;

    // Generic zero check
    auto isZero = [](const auto& v) {
        return v.x == 0.0f && v.y == 0.0f && v.z == 0.0f;
        };

    for (const auto& pos : globals::network::playerPoses) {
        if (isZero(pos.worldposition))
            continue;

        if (pos.screenposition.z <= 0)
            continue;

        // Correct Y inversion
        float correctedY = screenSize.y - pos.screenposition.y;
        ImVec2 headScreenPos = ImVec2(pos.screenposition.x, correctedY);

        // Find matching player in playerList by playerId
        auto it = std::find_if(
            globals::network::playerList.begin(),
            globals::network::playerList.end(),
            [&](const auto& p) { return p.playerId == pos.playerid; }
        );
        if (it == globals::network::playerList.end())
            continue;

        const std::string& playerName = it->name;

        // --- Hover scaling ---
        float distance = sqrtf(
            powf(screenCenter.x - headScreenPos.x, 2) +
            powf(screenCenter.y - headScreenPos.y, 2)
        );
        float maxHoverDistance = 50.0f; // pixels for hover effect
        float scale = 1.0f;

        // Check for hover and find the player with the minimum distance
        if (distance < maxHoverDistance) {
            scale = 1.0f + (maxHoverDistance - distance) / maxHoverDistance * 0.5f;

            if (distance < minDistance) {
                minDistance = distance;
                hoveredPlayerId = pos.playerid;
                hoveredPlayerScreenPos = headScreenPos;
            }
        }

        // Scaled text size
        ImVec2 textSizeOrig = ImGui::CalcTextSize(playerName.c_str());
        ImVec2 textSize = ImVec2(textSizeOrig.x * scale, textSizeOrig.y * scale);

        // Center text on head
        ImVec2 textPos = ImVec2(
            headScreenPos.x - textSize.x * 0.5f,
            headScreenPos.y - textSize.y - 10.0f
        );

        // Scaled background padding
        ImVec2 padding = ImVec2(4.0f * scale, 2.0f * scale);
        ImVec2 bgMin = ImVec2(textPos.x - padding.x, textPos.y - padding.y);
        ImVec2 bgMax = ImVec2(textPos.x + textSize.x + padding.x, textPos.y + textSize.y + padding.y);

        // Draw background and outline
        drawList->AddRectFilled(bgMin, bgMax, IM_COL32(20, 20, 20, 180), 4.0f * scale);
        drawList->AddRect(bgMin, bgMax, IM_COL32(255, 255, 255, 200), 4.0f * scale);

        // Draw text
        drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), playerName.c_str());

        drawList->AddLine(
            screenCenter,
            headScreenPos,
            IM_COL32(0, 255, 0, 200),  // tracer color (you can change)
            1.5f                       // thickness
        );
    }

    // --- Radio Wheel Logic ---
    bool rKeyHeld = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;


    if (rKeyHeld && !globals::network::radioopen) {
        // Lock the position and open the wheel on the first frame of the press
        if (hoveredPlayerId != -1) {
            lockedPlayerId = hoveredPlayerId;
            lockedPlayerScreenPos = hoveredPlayerScreenPos;
            globals::network::radioopen = true;
            ImGui::GetIO().MousePos = lockedPlayerScreenPos;
        }
    }

    if (globals::network::radioopen) {
        // Define radio wheel properties
        float innerRadius = 60.0f;
        float outerRadius = 160.0f;
        int numSegments = 30; // For a smooth circle

        // Define menu items
        struct MenuItem {
            const char* name;
            bool* flag;
        };
        MenuItem menuItems[] = {
            {"Ram Crash", &globals::network::ramcrash},
            {"Disarm Player", &globals::network::disarm},
            {"Equip Asset", &globals::network::forceequip},
            {"Goto Player", &globals::network::teleportToPlayer},
            {"Witch Orbit", &globals::network::witchorbit},
            {"Bring Player", &globals::network::bringplr},
            {"Void Player", &globals::network::voidplayers},
            {"Fuck Player", &globals::network::test}
            
        };
        int itemCount = IM_ARRAYSIZE(menuItems);
        float segmentAngle = 360.0f / itemCount;

        ImVec2 mousePos = ImGui::GetIO().MousePos;
        ImVec2 toMouseVec = ImVec2(mousePos.x - lockedPlayerScreenPos.x, mousePos.y - lockedPlayerScreenPos.y);
        float mouseDist = sqrtf(toMouseVec.x * toMouseVec.x + toMouseVec.y * toMouseVec.y);
        float mouseAngle = atan2(toMouseVec.y, toMouseVec.x) * 180.0f / 3.14159f;
        if (mouseAngle < 0) mouseAngle += 360.0f;

        int hoveredItem = -1;
        if (mouseDist > innerRadius && mouseDist < outerRadius) {
            hoveredItem = (int)(mouseAngle / segmentAngle);
            if (hoveredItem >= itemCount) hoveredItem = itemCount - 1;
        }

        for (int i = 0; i < itemCount; ++i) {
            float startAngle = i * segmentAngle;
            float endAngle = (i + 1) * segmentAngle;

            ImU32 segmentColor = IM_COL32(15, 15, 15, 200);
            ImU32 segmentOutline = IM_COL32(255, 255, 255, 255);

            if (i == hoveredItem) {
                segmentColor = IM_COL32(50, 50, 50, 200);
            }

            // Draw segment
            drawList->PathClear();
            drawList->PathLineTo(lockedPlayerScreenPos);
            for (int j = 0; j <= numSegments; ++j) {
                float angle = (startAngle + (endAngle - startAngle) * j / numSegments) * 3.14159f / 180.0f;
                ImVec2 pos = ImVec2(lockedPlayerScreenPos.x + outerRadius * cosf(angle), lockedPlayerScreenPos.y + outerRadius * sinf(angle));
                drawList->PathLineTo(pos);
            }
            drawList->PathFillConvex(segmentColor);

            // Draw segment outline
            drawList->PathClear();
            drawList->PathLineTo(lockedPlayerScreenPos);
            for (int j = 0; j <= numSegments; ++j) {
                float angle = (startAngle + (endAngle - startAngle) * j / numSegments) * 3.14159f / 180.0f;
                ImVec2 pos = ImVec2(lockedPlayerScreenPos.x + outerRadius * cosf(angle), lockedPlayerScreenPos.y + outerRadius * sinf(angle));
                drawList->PathLineTo(pos);
            }
            drawList->PathStroke(segmentOutline, true, 1.5f);

            // Draw text label
            // The text is now positioned in the middle of the segment
            float textRadius = (innerRadius + outerRadius) * 0.5f;
            float textAngle = (startAngle + endAngle) * 0.5f * 3.14159f / 180.0f;
            ImVec2 textPos = ImVec2(lockedPlayerScreenPos.x + textRadius * cosf(textAngle), lockedPlayerScreenPos.y + textRadius * sinf(textAngle));
            ImVec2 textSize = ImGui::CalcTextSize(menuItems[i].name);
            drawList->AddText(ImVec2(textPos.x - textSize.x * 0.5f, textPos.y - textSize.y * 0.5f), IM_COL32(255, 255, 255, 255), menuItems[i].name);
        }

        // Draw inner circle and outline
        drawList->AddCircleFilled(lockedPlayerScreenPos, innerRadius, IM_COL32(15, 15, 15, 200), numSegments);
        drawList->AddCircle(lockedPlayerScreenPos, innerRadius, IM_COL32(255, 255, 255, 255), numSegments, 1.5f);


        if (!rKeyHeld) {
            if (hoveredItem != -1 && lockedPlayerId != -1) {
                *menuItems[hoveredItem].flag = true;
                globals::network::targetPlayerId = lockedPlayerId;
            }

            // Radio wheel closes, restore cursor properly
            globals::network::radioopen = false;
            ImGui::GetIO().MouseDrawCursor = globals::ui::mainui; // only draw cursor if menu is open
            if (!globals::ui::mainui) {
                // Lock the cursor back to the game window if menu is closed
                ClipCursor(NULL);
                ShowCursor(FALSE); // optional: hide if the menu isn’t open
            }
        }

    }
}

void GUI::RadioWheel()
{

}