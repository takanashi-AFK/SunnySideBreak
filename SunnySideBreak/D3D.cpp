#include "D3D.h"
#include <d3dcompiler.h>
D3D::D3D():
	windowHandle(nullptr),windowSizeW(-1),windowSizeH(-1),
	pDevice_(nullptr),pContext_(nullptr),pSwapChain_(nullptr),pRenderTargetView_(nullptr),
	scDesc_{}, vp_{},
	pVertexShader_(nullptr),pPixelShader_(nullptr),pVertexLayout_(nullptr), pRasterizerState_(nullptr)
{
}

D3D::~D3D()
{
}

void D3D::StringToLPCWSTR(const std::string& str , std::wstring& src) {
	string temp = str + ".hlsl";
	std::wstring wstr(temp.begin(), temp.end());
	src = wstr;
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
	ShaderManager::AddShader("Simple3D");
	if (!InitShader())return false;

	return true;
}

bool D3D::InitShader()
{

	for (auto i = 0u; i < ShaderManager::shaderKinds_.size(); i++)
	{
	ID3DBlob* pCompileVS = nullptr;
	ID3DBlob* pCompilePS = nullptr;

	wstring str = {};
	StringToLPCWSTR(ShaderManager::shaderKinds_[i] , str);

	//VertexShaderInitialize
	//	D3DCompileFromFile��E_FAIL��Ԃ�����(���s������)
	if(FAILED(D3DCompileFromFile(str.c_str(), nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL)))return false;
	if (FAILED(pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader_)))return false;
	

	//VertexInputRayout
	if (str == L"Simple3D.hlsl")
		layout_ = ShaderManager::SetVertexInputLayout();


	UINT layoutSize = layout_.size();
	if (FAILED(pDevice_->CreateInputLayout(layout_.data(), layoutSize, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout_)))return false;

	pCompileVS->Release();

	//PixelShaderInitialize
	if (FAILED(D3DCompileFromFile(str.c_str(), nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL)))return false;
	if (FAILED(pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader_)))return false;
	pCompilePS->Release();

	if (ShaderManager::shaderKinds_[i] == "Simple3D") {
	cs = ShaderManager::AddRasterizer(D3D11_CULL_NONE,D3D11_FILL_SOLID,false);
	}

	//CreateRasterizer
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = cs.cullSetting;
	rdc.FillMode = cs.fillSetting;
	rdc.FrontCounterClockwise = cs.clockWise;
	if (FAILED(pDevice_->CreateRasterizerState(&rdc, &pRasterizerState_)))return false;

	//���ꂼ����f�o�C�X�R���e�L�X�g�ɃZ�b�g
	pContext_->VSSetShader(pVertexShader_, NULL, 0);
	pContext_->PSSetShader(pPixelShader_, NULL, 0);
	pContext_->IASetInputLayout(pVertexLayout_);	
	pContext_->RSSetState(pRasterizerState_);	
	}
	return true;
}

bool D3D::InitializeSwapChainDesc()
{
	//�Ƃ肠�����S��0
	ZeroMemory(&scDesc_, sizeof(scDesc_));

	//�`���̃t�H�[�}�b�g
	scDesc_.BufferDesc.Width = windowSizeW;		//��ʕ�
	scDesc_.BufferDesc.Height = windowSizeH;	//��ʍ���
	scDesc_.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

	//FPS�i1/60�b��1��j
	scDesc_.BufferDesc.RefreshRate.Numerator = g_FrameRate;
	scDesc_.BufferDesc.RefreshRate.Denominator = 1;

	//���̑�
	scDesc_.Windowed = TRUE;			//�E�B���h�E���[�h���t���X�N���[����
	scDesc_.OutputWindow = windowHandle;		//�E�B���h�E�n���h��
	scDesc_.BufferCount = 1;			//�o�b�N�o�b�t�@�̖���
	scDesc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�o�b�N�o�b�t�@�̎g��������ʂɕ`�悷�邽�߂�
	scDesc_.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
	scDesc_.SampleDesc.Quality = 0;		//�@�V

	if (sizeof(scDesc_) == 0) return false;

	return true;
}

bool D3D::CreateDevContextSC()
{
	////////////////��L�ݒ�����ƂɃf�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C�����쐬////////////////////////
	D3D_FEATURE_LEVEL level;
	D3D11CreateDeviceAndSwapChain(
		nullptr,				// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr��
		D3D_DRIVER_TYPE_HARDWARE,		// �h���C�o�̃^�C�v��n���B�ӂ���HARDWARE
		nullptr,				// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵�Ȃ�������nullptr
		0,					// ���炩�̃t���O���w�肷��B�i�f�o�b�O����D3D11_CREATE_DEVICE_DEBUG�H�j
		nullptr,				// �f�o�C�X�A�R���e�L�X�g�̃��x����ݒ�Bnullptr�ɂ��Ƃ���OK
		0,					// ��̈����Ń��x�������w�肵����
		D3D11_SDK_VERSION,			// SDK�̃o�[�W�����B�K�����̒l
		&scDesc_,				// ��ł��낢��ݒ肵���\����
		&pSwapChain_,				// ������������SwapChain�̃A�h���X���Ԃ��Ă���
		&pDevice_,				// ������������Device�A�h���X���Ԃ��Ă���
		&level,					// ������������Device�AContext�̃��x�����Ԃ��Ă���
		&pContext_);				// ������������Context�̃A�h���X���Ԃ��Ă���

	if (sizeof(scDesc_) == 0)return false;

	return true;
}

bool D3D::CreateRenderTargetView()
{
	//�X���b�v�`�F�[������o�b�N�o�b�t�@���擾�i�o�b�N�o�b�t�@ �� �����_�[�^�[�Q�b�g�j
	ID3D11Texture2D* pBackBuffer{};
	pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	if (pBackBuffer == 0) {
		return false;
	}

	//�����_�[�^�[�Q�b�g�r���[���쐬
	pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_);

	//�ꎞ�I�Ƀo�b�N�o�b�t�@���擾���������Ȃ̂ŉ��
	pBackBuffer->Release();

	return true;
}

bool D3D::ViewPortSetting()
{
	//�����_�����O���ʂ�\������͈�
	vp_.Width = (float)windowSizeW;	//��
	vp_.Height = (float)windowSizeH;//����
	vp_.MinDepth = 0.0f;	//��O
	vp_.MaxDepth = 1.0f;	//��
	vp_.TopLeftX = 0;	//��
	vp_.TopLeftY = 0;	//��

	if (sizeof(vp_) == 0) return false;
	return true;
}

bool D3D::PipelineSetting()
{
	//�f�[�^����ʂɕ`�悷�邽�߂̈�ʂ�̐ݒ�i�p�C�v���C���j
	pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // �f�[�^�̓��͎�ނ��w��
	pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);            // �`����ݒ�
	pContext_->RSSetViewports(1, &vp_);

	if (pContext_ == nullptr)return false;
	return true;
}

bool D3D::StartDraw()
{
	//�w�i�̐F
	float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };//R,G,B,A

	//��ʂ��N���A
	pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);

	if (pContext_ == nullptr)return false;
	return true;

}

bool D3D::EndDraw()
{
	//�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
	HRESULT hr = pSwapChain_->Present(0, 0);
	if(hr != S_OK)return false;
	return true;
}

void D3D::Release()
{
	SAFE_RELEASE(pRasterizerState_);
	SAFE_RELEASE(pVertexLayout_);
	SAFE_RELEASE(pPixelShader_);
	SAFE_RELEASE(pVertexShader_);

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

