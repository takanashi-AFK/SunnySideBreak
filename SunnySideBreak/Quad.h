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

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
public:
	Quad();
	~Quad();
	void Initialize();
	void Draw();
	void Release();
};

