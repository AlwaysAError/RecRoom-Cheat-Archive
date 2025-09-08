#include "includes.h"
#include "Util/natives.h"
#include "Util/Hooks.h"
#include <chrono>
#include <algorithm>  
#include <string>     
#include "menu/menu.hpp"
#include "menu/watermark.h"
#include "Util/Font.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;




bool init = false;



void DrawCustomCursor()
{
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();
    ImVec2 mouse_pos = io.MousePos;
    ImU32 red_color = IM_COL32(255, 255, 255, 255);
    float size = 8.0f; 
    draw_list->AddLine(ImVec2(mouse_pos.x - size, mouse_pos.y),
        ImVec2(mouse_pos.x + size, mouse_pos.y),
        red_color, 2.0f); 
    draw_list->AddLine(ImVec2(mouse_pos.x, mouse_pos.y - size),
        ImVec2(mouse_pos.x, mouse_pos.y + size),
        red_color, 2.0f); 
}

void CreateConsole()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    SetConsoleTitleA("´Nemesis Console");
	system("cls");
    Log::log("Console Created");
    Log::log("Console Allocated");

}

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange | ImGuiConfigFlags_NavEnableKeyboard;


    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    ImGui::GetStyle().Alpha = 1.0f;
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

 
    ImVec4 lightBlue = ImVec4(0.337f, 0.627f, 0.953f, 1.0f);
    ImVec4 darkBlue = ImVec4(0.035f, 0.149f, 0.498f, 1.0f);

    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.14f, 1.00f); 
    colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.11f, 0.14f, 1.00f); 
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.30f, 0.60f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.22f, 1.00f); 
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.25f, 0.45f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.35f, 0.60f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.20f, 0.90f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.20f, 0.35f, 1.00f); 
    colors[ImGuiCol_CheckMark] = lightBlue; 
    colors[ImGuiCol_SliderGrab] = ImVec4(0.20f, 0.30f, 0.50f, 1.00f); 
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 0.35f, 0.55f, 1.00f); 
    colors[ImGuiCol_Button] = ImVec4(0.15f, 0.20f, 0.35f, 0.85f); 
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.30f, 0.45f, 1.00f); 
    colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.35f, 0.55f, 1.00f); 
    colors[ImGuiCol_Header] = ImVec4(0.15f, 0.20f, 0.35f, 0.85f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.30f, 0.45f, 1.00f); 
    colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.35f, 0.55f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.20f, 0.30f, 0.85f); 
    colors[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.30f, 0.45f, 1.00f); 
    colors[ImGuiCol_TabActive] = ImVec4(0.18f, 0.25f, 0.38f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.35f, 0.75f); 
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.45f, 0.45f, 0.50f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.16f, 0.95f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.15f, 0.20f, 0.30f, 0.80f); 
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.20f, 0.25f, 0.35f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.25f, 0.30f, 0.40f, 1.00f);
    ImFontConfig font;
    font.FontDataOwnedByAtlas = false;

    io.Fonts->AddFontFromMemoryTTF((void*)rawData, sizeof(rawData), 22.5f, &font); // Huge Ass font
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);

}

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_KEYUP && wParam == VK_INSERT) 
        UI::show = !UI::show;
    if (uMsg == WM_KEYUP && wParam == VK_DELETE)
        UI::show = !UI::show;

    if (UI::show && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {   
		// dead ass  this is a bad way for debugging crashes, but it works for now
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            Hooks();
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;
        }
        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    if (UI::Engine::FOV)
    {
        if (GetAsyncKeyState('R') & 0x8000)
        {
            UI::Engine::PlayerFOV = 20.0f;
        }
        else
        {
            UI::Engine::PlayerFOV = UI::Engine::RealFOV;
        }
    }

    if (UI::Engine::EnableAirstuck)
    {
        if (GetAsyncKeyState('Y') & 0x8000)
        {
            UI::Engine::Airstuck = true;
        }
        else
        {
            UI::Engine::Airstuck = false;
        }

    }


    WaterMark();
    if (UI::show)
    {
        DrawCustomCursor();
        Menu();
    }

    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    CreateConsole(); 
    if (MH_Initialize() != MH_OK)
    {
        MessageBox(NULL, "MinHook failed", "Error!!!", MB_OK);
        return 0;
    }

    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
        }
    } while (!init_hook);
    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        std::thread(MainThread, hMod).detach(); 
        break;                                  
    case DLL_PROCESS_DETACH:
        kiero::shutdown();
        MH_Uninitialize();
        break;
    }
    return TRUE;
}
