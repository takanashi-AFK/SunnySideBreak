#pragma once

#include <DirectXMath.h>
#include"../Draw/D3D.h"
#include "Camera.h"
#include "../Draw/XTexture.h"
#include "Transform.h"

using namespace DirectX;

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matNormal;
};

struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
	XTexture* pTexture_;
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ


public:
	Quad();
	~Quad();
	void Initialize();
	void Draw(XMMATRIX& _worldMatrix);
	void Release();
};

