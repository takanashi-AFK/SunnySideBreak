#include "XTexture.h"
#include <wincodec.h>

#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

using namespace DirectX;

Texture::Texture()
{
}

Texture::~Texture()
{
}

HRESULT Texture::Load(LPCWSTR fileName)
{
	D3D* pD3D = &D3D::GetInstance();
	TexMetadata metadata;
	ScratchImage image;   
	HRESULT hr;
	hr = LoadFromWICFile(fileName, WIC_FLAGS::WIC_FLAGS_NONE,&metadata, image);

	if (FAILED(hr))return S_FALSE;

	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	pD3D->GetDevice()->CreateSamplerState(&SamDesc, &pSampler_);

	//シェーダーリソースビュー

	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = CreateShaderResourceView(pD3D->GetDevice(),image.GetImages(), image.GetImageCount(), metadata, &pSRV_);

}

void Texture::Release()
{
}
