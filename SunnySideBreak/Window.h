#pragma once
#include <Windows.h>

/// <summary>
/// windowクラスの作成、初期化、
/// </summary>

class Window
{
public:
	 Window() {};
	~Window() {};
	//プロトタイプ宣言
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Initialize(HINSTANCE _hInstance,int _nCmdShow);
	void Execute();

private:

	HWND hWnd_;
	bool CreateWindowClass(HINSTANCE hInstance);
	void MessageLoop();

};

