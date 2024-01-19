#pragma once
#include <Windows.h>
#include<string>
/// <summary>
/// window�N���X�̍쐬�A�������A
/// </summary>

class Window
{
public:
	Window();
	Window(const char* name);
	~Window() ;
	//�v���g�^�C�v�錾
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Initialize(HINSTANCE _hInstance,int _nCmdShow);
	void Execute();
	bool Release();

private:

	HWND hWnd_;
	const char* windowName;
	bool CreateWindowClass(HINSTANCE hInstance);
	void MessageLoop();

};

