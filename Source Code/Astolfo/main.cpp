#include "includes.h"
#include "ui/Themes/Themes.h"
#include "ui/Font/Roboto.h"
#include "globals/globals.h"
#include "ui/GUI.h"
#include "util/hooks.h"
#include "ui/watermark.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void CreateConsole()
{
	// Allocate a new console for the process
	AllocConsole();

	// Redirect standard streams to the new console
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);  // stdout -> console
	freopen_s(&fp, "CONOUT$", "w", stderr);  // stderr -> console
	freopen_s(&fp, "CONIN$", "r", stdin);    // stdin  -> console

	// Optional: set a nice title
	SetConsoleTitleA("Debug Console");

	// Optional: move window to top-left and resize
	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow) {
		MoveWindow(consoleWindow, 100, 100, 800, 600, TRUE);
	}

	std::cout << "[+] Console created successfully!" << std::endl;
}

void InitImGui()
{
	ImGui::CreateContext();
	ApplyThemes();
	ImGui::GetIO().Fonts->AddFontFromMemoryTTF(Roboto_Regular, sizeof(Roboto_Regular), 18.0f);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {


	if (GUI::Opened) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return 0;



		// Block all keyboard and mouse input events when ImGui window is open?
		if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_CHAR ||
			uMsg == WM_MOUSEMOVE || uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP ||
			uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONDOWN ||
			uMsg == WM_MBUTTONUP || uMsg == WM_MOUSEWHEEL || uMsg == WM_MOUSEHWHEEL || uMsg == WM_INPUT) {
			return 0;
		}
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			CreateConsole();
			Hooks();

			
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
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
	WaterMark();

	if (GetAsyncKeyState(VK_INSERT) & 1 || GetAsyncKeyState(VK_DELETE) & 1) {
		GUI::Opened = !GUI::Opened;
		ImGui::GetIO().MouseDrawCursor = GUI::Opened;
	}

	if (GUI::Opened) {
		ClipCursor(NULL);
		GUI::Render();
		GUI::RenderExtra();

	}


	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
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
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}