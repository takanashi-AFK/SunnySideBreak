#pragma once
//インクルード
#include <Windows.h>
#include "../Window/Window.h"
#include"../Window/WindowManager.h"
#include"../Draw/D3D.h"
#include"../Other/Global.h"
#include "Quad.h"
#include "ImGuiManager.h"
#include "Camera.h"

class Application
{
public:
	Application() ;

	/// <summary>
	/// 各種アプリケーションの初期化処理
	/// 現在はD3D、Windowの初期化と表示を行う
	/// </summary>
	/// <param name="_hInstance">WinMainのargsで取ったhInstance</param>
	/// <param name="_nCmdShow">Winmainのargsで取った_nCmdShow</param>
	/// <returns></returns>
	bool Initialize(HINSTANCE _hInstance, int _nCmdShow);

	/// <summary>
	/// メッセージループを行う関数
	/// </summary>
	void Run();

	/// <summary>
	/// 各アプリケーションの解放処理
	/// </summary>
	void Release();

	/// <summary>
	/// シングルトン用のインスタンスを取得する関数
	/// </summary>
	/// <returns>Applicationのインスタンス</returns>
	static Application& GetInstance();
private:
	
};

