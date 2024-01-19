#include "Window.h"
#include "Global.h"

Window::Window() :
	hWnd_(nullptr)
{
}

Window::Window(const char* name)
{
	windowName = name;
}

Window::~Window()
{
}

LRESULT Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool Window::Initialize(HINSTANCE _hInstance,int _nCmdShow)
{	
	CreateWindowClass(_hInstance);
	ShowWindow(hWnd_, _nCmdShow);
	return true;
}

void Window::Execute()
{
	MessageLoop();
}

bool Window::Release()
{
	DestroyWindow(hWnd_);
	return true;
}

bool Window::CreateWindowClass(HINSTANCE _hInstance)
{
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = _hInstance;                  //インスタンスハンドル
	wc.lpszClassName = windowName;				//ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc);  //クラスを登録

	if (sizeof(wc) == 0) {
		return false;
	}

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, g_WindowWidth, g_WindowHeight };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ


	//ウィンドウを作成
	hWnd_ = CreateWindow(
		windowName,        //ウィンドウクラス名
		windowName,    //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,       //ウィンドウ幅
		winH,      //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		_hInstance,          //インスタンス
		NULL                 //パラメータ（なし）
	);

	if (hWnd_ == nullptr) {
		return false;
	}

	return true;

}

void Window::MessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT){
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else{
			//ゲームの処理
		}
	}
}
