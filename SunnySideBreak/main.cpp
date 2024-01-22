//インクルード
#include <Windows.h>
#include"Application.h"

//整合性のない注釈についての対処は必要ないため抑制
#pragma warning(disable : 28251)

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


