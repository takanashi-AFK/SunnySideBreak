#pragma once
#include <Windows.h>

/// <summary>
/// window�N���X�̍쐬�A�������A
/// </summary>

class Window
{
public:
	 Window() {};
	~Window() {};
	//�v���g�^�C�v�錾
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Initialize(HINSTANCE _hInstance,int _nCmdShow);
	void Execute();

private:

	HWND hWnd_;
	bool CreateWindowClass(HINSTANCE hInstance);
	void MessageLoop();

};

