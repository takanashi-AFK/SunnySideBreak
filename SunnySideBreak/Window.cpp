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
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = _hInstance;                  //�C���X�^���X�n���h��
	wc.lpszClassName = windowName;				//�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
	RegisterClassEx(&wc);  //�N���X��o�^

	if (sizeof(wc) == 0) {
		return false;
	}

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, width, height };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����


	//�E�B���h�E���쐬
	hWnd_ = CreateWindow(
		windowName,        //�E�B���h�E�N���X��
		windowName,    //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,       //�E�B���h�E��
		winH,      //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		_hInstance,          //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	if (hWnd_ == nullptr) {
		return false;
	}

	return true;

}

