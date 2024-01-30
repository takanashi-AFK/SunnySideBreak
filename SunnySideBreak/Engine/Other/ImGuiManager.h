#pragma once
#include"../Draw/D3D.h"
//ImGui関連データのインクルード
#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_impl_dx11.h"
#include "../../ImGui/imgui_impl_win32.h"
class ImGuiManager
{
public:
	static ImGuiManager& GetInstance();

	bool Initialize(HWND _hWnd);
	bool UpDate();
	bool Draw();
	bool Feature();
	bool Release();



};

