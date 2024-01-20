//インクルード
#include <Windows.h>
#include"Application.h"

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	Application* app = &Application::GetInstance();
	
	if (app->Initialize(hInstance, nCmdShow)) {
		app->Run();
	}
	app->Release();

	return 0;
}


