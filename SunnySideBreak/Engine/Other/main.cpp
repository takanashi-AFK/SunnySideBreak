//�C���N���[�h
#include <Windows.h>
#include"Application.h"

//�������̂Ȃ����߂ɂ��Ă̑Ώ��͕K�v�Ȃ����ߗ}��
#pragma warning(disable : 28251)

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


