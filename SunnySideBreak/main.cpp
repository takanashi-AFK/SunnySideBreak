//�C���N���[�h
#include <Windows.h>
#include "Window.h"
#include"WindowManager.h"



//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Window* w = new Window();

	WindowManager& wm = WindowManager::GetInstance();

	wm.AddInstance("NewWindow", w);
	wm.InitializeAllWindow(hInstance,nCmdShow);
	wm.MessageLoop();
	return 0;
}


