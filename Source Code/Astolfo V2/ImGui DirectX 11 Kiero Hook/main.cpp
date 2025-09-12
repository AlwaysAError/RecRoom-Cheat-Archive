#include <windows.h>
#include <shellapi.h>
#include <thread>
#include "includes.h"
#include "GUI/GUI.h"
#include "utils/globals.h"
#include "GUI/Themes.h"
#include "GUI/watermark.h"
#include "utils/hooks.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

// Initialize ImGui
void InitImGui()
{
    ImGui::CreateContext();
    ApplyThemes();
    GUI::InitializeFonts();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}

// Custom WndProc for input blocking
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    bool blockInput = globals::ui::mainui || !globals::network::passedverification || globals::network::radioopen;

    if (blockInput)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            return 0;

        switch (uMsg)
        {
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_CHAR:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
        case WM_INPUT:
            return 0;
        }
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;

// Present hook
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;

            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();

            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();

            // Run Hooks() in a separate thread
            std::thread([]() {
                Hooks(); // setup hundreds of hooks without blocking present
                }).detach();

            init = true;
        }
        else
        {
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
    }

    // Start ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    WaterMark();

    // Toggle menu with Insert/Delete
    if ((GetAsyncKeyState(VK_INSERT) & 1) || (GetAsyncKeyState(VK_DELETE) & 1))
    {
        globals::ui::mainui = !globals::ui::mainui;
        ImGui::GetIO().MouseDrawCursor = globals::ui::mainui;
        ShowCursor(globals::ui::mainui);
    }

    if (globals::network::passedverification)
    {
        ClipCursor(NULL);
        if (globals::ui::mainui)
        {
            GUI::Render();
            GUI::RenderExtra();
        }
        else if (globals::network::radioopen)
        {
            ImGui::GetIO().MouseDrawCursor = true;
            GUI::RenderEsp();
        }
        else
        {
            GUI::RenderEsp();
        }
    }
    else
    {
        ClipCursor(NULL);
        ImGui::GetIO().MouseDrawCursor = true;
        GUI::AntiSkid();
    }

    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

// Thread to setup kiero and hook Present
DWORD WINAPI HookThread(LPVOID lpReserved)
{
    while (true)
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            break; // exit once hooked
        }
        Sleep(100); // prevent CPU spike
    }
    return 0;
}

// DLL entry
BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);

        AllocConsole();
        {
            FILE* fOut;
            FILE* fErr;
            freopen_s(&fOut, "CONOUT$", "w", stdout);
            freopen_s(&fErr, "CONOUT$", "w", stderr);
        }

        // Open Discord invite once
        ShellExecuteA(NULL, "open", "https://discord.gg/astolfolovers", NULL, NULL, SW_SHOWNORMAL);

        // Start hook setup on a separate thread
        CreateThread(nullptr, 0, HookThread, hMod, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        kiero::shutdown();
        FreeConsole();
        break;
    }
    return TRUE;
}
