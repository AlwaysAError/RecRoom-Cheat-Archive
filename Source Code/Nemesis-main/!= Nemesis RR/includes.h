#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <thread>
#include <string>
#include <iostream>
#include "Util/xorstr.hpp"
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;


uintptr_t ModuleGA = (uintptr_t)GetModuleHandleA(_("GameAssembly.dll"));
uintptr_t UEP = (uintptr_t)GetModuleHandleA(_("UnityPlayer.dll")); //idk if its the real one but who cares

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};

ImVec4 InterpolateColor(const ImVec4& color1, const ImVec4& color2, float t)
{
	float inverse_t = 1.0f - t;
	return ImVec4(
		inverse_t * color1.x + t * color2.x,
		inverse_t * color1.y + t * color2.y,
		inverse_t * color1.z + t * color2.z,
		color1.w);
}


void GradientText(const char* text, float speed, const ImVec4& color1, const ImVec4& color2, ImVec2* position = nullptr)
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

		ImVec4 color = InterpolateColor(color1, color2, t);

		ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::Text("%c", text[i]);
		ImGui::SameLine(0, 0);
		ImGui::PopStyleColor();
	}
	ImGui::NewLine(); 
} // i fucking hate this

