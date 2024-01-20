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


