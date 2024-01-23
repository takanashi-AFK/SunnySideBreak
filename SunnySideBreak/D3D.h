#pragma once
#include <d3d11.h>
#include"Global.h"
#include "Window.h"
#include "ShaderManager.h"
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace ShaderManager;
class D3D
{
public:
	D3D();
	~D3D();
	// 初期化
	bool Initialize(Window* w);
	bool InitShader();
	// 初期化の中身色々
	bool InitializeSwapChainDesc();
	bool CreateDevContextSC();
	bool CreateRenderTargetView();
	bool ViewPortSetting();
	bool PipelineSetting();

	bool StartDraw();

	bool EndDraw();

	void Release();

	static D3D &GetInstance();

	void StringToLPCWSTR(const std::string& str , std::wstring& src);

private:

	HWND windowHandle;
	int windowSizeW, windowSizeH;
	Cull_Setting cs;

	//D3Dを初期化する変数群

	ID3D11Device* pDevice_;
	ID3D11DeviceContext* pContext_;
	IDXGISwapChain* pSwapChain_;
	ID3D11RenderTargetView* pRenderTargetView_;
	DXGI_SWAP_CHAIN_DESC scDesc_;
	D3D11_VIEWPORT vp_;
	
	//shaderInitialize Valiable
	ID3D11VertexShader* pVertexShader_;
	ID3D11PixelShader* pPixelShader_;
	ID3D11InputLayout* pVertexLayout_;	
	ID3D11RasterizerState* pRasterizerState_;
	vector<D3D11_INPUT_ELEMENT_DESC>layout_;




};

