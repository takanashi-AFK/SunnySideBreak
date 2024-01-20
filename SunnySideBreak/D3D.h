#pragma once
#include <d3d11.h>
#include"Global.h"
#include "Window.h"

#pragma comment(lib, "d3d11.lib")


class D3D
{
public:
	D3D();
	~D3D();
	// èâä˙âª
	bool Initialize(Window* w);
	// èâä˙âªÇÃíÜêgêFÅX
	bool InitializeSwapChainDesc();
	bool CreateDevContextSC();
	bool CreateRenderTargetView();
	bool ViewPortSetting();
	bool PipelineSetting();

	bool StartDraw();

	bool EndDraw();

	void Release();

	static D3D &GetInstance();

private:
	HWND windowHandle;
	int windowSizeW, windowSizeH;

	ID3D11Device* pDevice_;
	ID3D11DeviceContext* pContext_;
	IDXGISwapChain* pSwapChain_;
	ID3D11RenderTargetView* pRenderTargetView_;

	DXGI_SWAP_CHAIN_DESC scDesc_;

	D3D11_VIEWPORT vp_;

};

