#include "D3D.h"

D3D::D3D()
{
}

D3D::~D3D()
{
}

bool D3D::Initialize(Window * w)
{
	windowSizeW = w->GetWidth();
	windowSizeH = w->GetHeight();
	windowHandle = w->GetHandle();

	InitializeSwapChainDesc();
	if (!CreateDevContextSC())return false;
	if (!CreateRenderTargetView())return false;
	if (!ViewPortSetting())return false;
	if (!PipelineSetting())return false;

	return true;
}

bool D3D::InitializeSwapChainDesc()
{
	//とりあえず全部0
	ZeroMemory(&scDesc_, sizeof(scDesc_));

	//描画先のフォーマット
	scDesc_.BufferDesc.Width = windowSizeW;		//画面幅
	scDesc_.BufferDesc.Height = windowSizeH;	//画面高さ
	scDesc_.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 何色使えるか

	//FPS（1/60秒に1回）
	scDesc_.BufferDesc.RefreshRate.Numerator = g_FrameRate;
	scDesc_.BufferDesc.RefreshRate.Denominator = 1;

	//その他
	scDesc_.Windowed = TRUE;			//ウィンドウモードかフルスクリーンか
	scDesc_.OutputWindow = windowHandle;		//ウィンドウハンドル
	scDesc_.BufferCount = 1;			//バックバッファの枚数
	scDesc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//バックバッファの使い道＝画面に描画するために
	scDesc_.SampleDesc.Count = 1;		//MSAA（アンチエイリアス）の設定
	scDesc_.SampleDesc.Quality = 0;		//　〃

	if (sizeof(scDesc_) == 0) return false;

	return true;
}

bool D3D::CreateDevContextSC()
{
	////////////////上記設定をもとにデバイス、コンテキスト、スワップチェインを作成////////////////////////
	D3D_FEATURE_LEVEL level;
	D3D11CreateDeviceAndSwapChain(
		nullptr,				// どのビデオアダプタを使用するか？既定ならばnullptrで
		D3D_DRIVER_TYPE_HARDWARE,		// ドライバのタイプを渡す。ふつうはHARDWARE
		nullptr,				// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しないかぎりnullptr
		0,					// 何らかのフラグを指定する。（デバッグ時はD3D11_CREATE_DEVICE_DEBUG？）
		nullptr,				// デバイス、コンテキストのレベルを設定。nullptrにしとけばOK
		0,					// 上の引数でレベルを何個指定したか
		D3D11_SDK_VERSION,			// SDKのバージョン。必ずこの値
		&scDesc_,				// 上でいろいろ設定した構造体
		&pSwapChain_,				// 無事完成したSwapChainのアドレスが返ってくる
		&pDevice_,				// 無事完成したDeviceアドレスが返ってくる
		&level,					// 無事完成したDevice、Contextのレベルが返ってくる
		&pContext_);				// 無事完成したContextのアドレスが返ってくる

	if (sizeof(scDesc_) == 0)return false;

	return true;
}

bool D3D::CreateRenderTargetView()
{
	//スワップチェーンからバックバッファを取得（バックバッファ ＝ レンダーターゲット）
	ID3D11Texture2D* pBackBuffer{};
	pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	if (pBackBuffer == 0) {
		return false;
	}

	//レンダーターゲットビューを作成
	pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_);

	//一時的にバックバッファを取得しただけなので解放
	pBackBuffer->Release();

	return true;
}

bool D3D::ViewPortSetting()
{
//レンダリング結果を表示する範囲
	vp_.Width = (float)windowSizeW;	//幅
	vp_.Height = (float)windowSizeH;//高さ
	vp_.MinDepth = 0.0f;	//手前
	vp_.MaxDepth = 1.0f;	//奥
	vp_.TopLeftX = 0;	//左
	vp_.TopLeftY = 0;	//上

	if (sizeof(vp_) == 0) return false;
	return true;
}

bool D3D::PipelineSetting()
{
	//データを画面に描画するための一通りの設定（パイプライン）
	pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // データの入力種類を指定
	pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);            // 描画先を設定
	pContext_->RSSetViewports(1, &vp_);

	if (pContext_ == nullptr)return false;
	return true;
}

bool D3D::StartDraw()
{
	//背景の色
	float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };//R,G,B,A

	//画面をクリア
	pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);

	if (pContext_ == nullptr)return false;
	return true;

}

bool D3D::EndDraw()
{
	//スワップ（バックバッファを表に表示する）
	HRESULT hr = pSwapChain_->Present(0, 0);
	if(hr != S_OK)return false;
	return true;
}

void D3D::Release()
{
	SAFE_RELEASE(pRenderTargetView_);
	SAFE_RELEASE(pSwapChain_);
	SAFE_RELEASE(pContext_);
	SAFE_RELEASE(pDevice_);


}

D3D& D3D::GetInstance()
{
	static D3D instance;
	return instance;
}


