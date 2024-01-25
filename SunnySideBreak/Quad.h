#pragma once

#include <DirectXMath.h>
#include "D3D.h"
#include "Camera.h"


using namespace DirectX;

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

class Quad
{

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
public:
	Quad();
	~Quad();
	void Initialize();
	void Draw();
	void Release();
};

