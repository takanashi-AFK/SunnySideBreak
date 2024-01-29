#pragma once
#include <d3d11.h>
#include "string"
#include "D3D.h"

class Texture
{
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;

public:
	Texture();
	~Texture();
	HRESULT Load(LPCWSTR fileName);
	void Release();

	ID3D11SamplerState* GetSampler();
	ID3D11ShaderResourceView* GetSRV();

};
