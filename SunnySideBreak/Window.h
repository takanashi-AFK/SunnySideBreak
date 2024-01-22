#pragma once
#include <Windows.h>
#include<string>
#include "Global.h"

/// <summary>
/// windowクラスの作成、初期化、
/// 後々procedureクラス内にaddProc関数的なのを作って各ウィンドウにprocを新しく適用させるようにしたい
/// addproc(メッセージ,使う関数)みたいなやつ
/// </summary>

class Window
{
public:
	Window();
	Window(const char* _name);
	Window(const char* _name,int _windowSizeW,int _windowSizeH);
	~Window() ;
	//プロトタイプ宣言
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

