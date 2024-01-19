#include "WindowManager.h"

WindowManager& WindowManager::GetInstance()
{
    static WindowManager instance;
    return instance;
}

bool WindowManager::InitializeAllWindow(HINSTANCE _hInstance, int _nCmdShow)
{
    for (const auto& e : windowInstanceContainer)
        if (e.second->Initialize(_hInstance, _nCmdShow)) {
            return true;
        }
    return false;
}

bool WindowManager::ReleaseAllWindow()
{
    return false;
}

bool WindowManager::AddInstance(std::string _windowName, Window* _windowInstance)
{
	windowInstanceContainer[_windowName] = _windowInstance;
	if (windowInstanceContainer[_windowName] == nullptr) {
		return false;
	}
	return true;
}

void WindowManager::MessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else {
			//ゲームの処理
		}
	}

}
