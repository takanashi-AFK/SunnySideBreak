//�C���N���[�h
#include <Windows.h>
#include"Application.h"

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Application* app = &Application::GetInstance();
	
	if (app->Initialize(hInstance, nCmdShow)) {
		app->Run();
	}
	app->Release();

	return 0;
}


