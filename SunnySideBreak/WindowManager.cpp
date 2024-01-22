#include "WindowManager.h"

WindowManager& WindowManager::GetInstance()
{
    static WindowManager instance;

    return instance;
}

bool WindowManager::InitializeAllWindow(HINSTANCE _hInstance, int _nCmdShow)
{
	 bool success = true;
    for (const auto& e : windowInstanceContainer)
        if (!e.second->Initialize(_hInstance, _nCmdShow)) {
            return false;
        }
    return success;
}

bool WindowManager::ReleaseAllWindow()
{
	for (const auto& e : windowInstanceContainer)
		delete e.second;
	
	windowInstanceContainer.clear();

    return true;
}

bool WindowManager::AddInstance(std::string _windowName, Window* _windowInstance)
{
	windowInstanceContainer[_windowName] = _windowInstance;
	if (windowInstanceContainer[_windowName] == nullptr) {
		return false;
	}
	return true;
}

