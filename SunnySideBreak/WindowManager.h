#pragma once
#include<map>
#include"Window.h"
#include"D3D.h"
#include<string>
/// <summary>
/// windowを複数生成できるようにするために管理するクラス。
/// mainでInstanceを作成し、addInstanceすることでウィンドウを追加することができる。
/// </summary>
class WindowManager
{
public:

	//windowクラスのインスタンスを格納するmap(ウィンドウ名、インスタンス)
	std::map<std::string,Window*> windowInstanceContainer;

	//シングルトンにするため(WindowManagerは1つ以上いらないから)GetInstance()
	static WindowManager& GetInstance();

	//mapの中に入っているすべてのwindowのInitializeを呼ぶ関数 InitializeAll()適な
	bool InitializeAllWindow(HINSTANCE _hInstance,int _nCmdShow);

	//Mapの中に入っているすべてのwindowのReleaseを呼ぶ関数	  ReleaseAll()的な
	bool ReleaseAllWindow();

	//Mapにウィンドウ名とインスタンスを格納するための関数	AddInstance()的な
	bool AddInstance(std::string _windowName,Window* _windowInstance);

};

