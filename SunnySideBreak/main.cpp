//インクルード
#include <Windows.h>
#include "Window.h"
#include"WindowManager.h"

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Window* w = new Window("aaa");
	Window* a = new Window("bbb");

	WindowManager& wm = WindowManager::GetInstance();

	wm.AddInstance("FirstWindow", w);
	wm.AddInstance("SecondWindow", a);

	wm.InitializeAllWindow(hInstance,nCmdShow);
	wm.MessageLoop();
	wm.ReleaseAllWindow();

	
	return 0;
}


