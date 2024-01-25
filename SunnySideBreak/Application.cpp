#include "Application.h"

Application::Application()
{
}


bool Application::Initialize(HINSTANCE _hInstance, int _nCmdShow)
{
	WindowManager* wm = &WindowManager::GetInstance();
	D3D* d3d = &D3D::GetInstance();
	ImGuiManager* pImgui = &ImGuiManager::GetInstance();

	Window* w = new Window("aaa");
	if(!wm->AddInstance("FirstWindow", w))return false;

	/*Window* a = new Window("bbb", 400, 200);
	if(!wm->AddInstance("SecondWindow", a))return false;*/

	if(!wm->InitializeAllWindow(_hInstance, _nCmdShow))return false;

	if (!d3d->Initialize(w))return false; 

	if (!pImgui->Initialize(w->GetHandle()))return false;

	return true;
}

void Application::Run()
{
	D3D* d3d = &D3D::GetInstance();
	ImGuiManager* pImgui = &ImGuiManager::GetInstance();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			d3d->StartDraw();
			pImgui->UpDate();
			pImgui->Feature();

			{//Quad
			Quad* q = new Quad;
			q->Initialize();
			q->Draw();
			}

			pImgui->Draw();
			d3d->EndDraw();
		}
	}
}

void Application::Release()
{
	WindowManager* wm = &WindowManager::GetInstance();
	ImGuiManager* pImgui = &ImGuiManager::GetInstance();

	wm->ReleaseAllWindow();
	D3D* d3d = &D3D::GetInstance();
	d3d->Release();

}

Application& Application::GetInstance()
{
	static Application instance;
	return instance;
}
