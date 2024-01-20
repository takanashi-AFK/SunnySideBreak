#pragma once
//インクルード
#include <Windows.h>
#include "Window.h"
#include"WindowManager.h"
#include"D3D.h"
#include"Global.h"

class Application
{
public:
	Application() ;

	bool Initialize(HINSTANCE _hInstance, int _nCmdShow);
	void Run();
	void Release();
	static Application& GetInstance();
private:
	
};

