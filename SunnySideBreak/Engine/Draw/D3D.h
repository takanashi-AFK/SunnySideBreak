#pragma once
#include <d3d11.h>
#include"../Other/Global.h"
#include "../Window/Window.h"
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
	// ‰Šú‰»
	bool Initialize(Window* w);
	bool InitShader();
	// ‰Šú‰»‚Ì’†gFX
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

	ID3D11Device* GetDevice() { return pDevice_; };
	ID3D11DeviceContext* GetContext() { return pContext_; };



private:

	HWND windowHandle;
	//D3D‚ğ‰Šú‰»‚·‚é•Ï”ŒQ

	ID3D11Device* pDevice_;
	ID3D11DeviceContext* pContext_;
	IDXGISwapChain* pSwapChain_;
	ID3D11RenderTargetView* pRenderTargetView_;
	DXGI_SWAP_CHAIN_DESC scDesc_;
	D3D11_VIEWPORT vp_;
	int windowSizeW, windowSizeH;
	Cull_Setting cs;
	
	//shaderInitialize Valiable
	ID3D11VertexShader* pVertexShader_;
	ID3D11PixelShader* pPixelShader_;
	ID3D11InputLayout* pVertexLayout_;	
	ID3D11RasterizerState* pRasterizerState_;
	vector<D3D11_INPUT_ELEMENT_DESC>layout_;




};

