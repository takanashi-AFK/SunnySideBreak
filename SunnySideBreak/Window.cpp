#include "Window.h"

Window::Window() :
	hWnd_(nullptr), windowName(g_GameTitle), width(g_WindowWidth), height(g_WindowHeight)
{
}

Window::Window(const char* _name):
	hWnd_(nullptr), windowName(_name), width(g_WindowWidth), height(g_WindowHeight)
{
}

Window::Window(const char* _name, int _windowSizeW, int _windowSizeH):
	hWnd_(nullptr), windowName(_name), width(_windowSizeW), height(_windowSizeH)
{
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
	RECT winRect = { 0, 0, width, height };
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

