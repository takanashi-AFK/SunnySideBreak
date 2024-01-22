#pragma once
#include <Windows.h>
#include<string>
#include "Global.h"

/// <summary>
/// window�N���X�̍쐬�A�������A
/// ��Xprocedure�N���X����addProc�֐��I�Ȃ̂�����Ċe�E�B���h�E��proc��V�����K�p������悤�ɂ�����
/// addproc(���b�Z�[�W,�g���֐�)�݂����Ȃ��
/// </summary>

class Window
{
public:
	Window();
	Window(const char* _name);
	Window(const char* _name,int _windowSizeW,int _windowSizeH);
	~Window() ;
	//�v���g�^�C�v�錾
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool Initialize(HINSTANCE _hInstance,int _nCmdShow);
	bool Release();

	int GetWidth() const { return width; };
	int GetHeight() const { return height; };
	HWND GetHandle() const { return hWnd_; };
	
	
private:
	//variable
	HWND hWnd_;
	int width;
	int height;
	const char* windowName;

	//method
	bool CreateWindowClass(HINSTANCE hInstance);

};

