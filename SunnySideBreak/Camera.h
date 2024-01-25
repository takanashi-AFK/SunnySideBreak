#pragma once
#include "D3D.h"
#include "Global.h"
#include <DirectXMath.h>
using namespace DirectX;
class Camera
{
	void Initialize();

	void CreateViewMat();

	void SetPosition(XMVECTOR _position) { position_ = _position; };

	void SetTarget(XMVECTOR _target) { target_ = _target; };

	XMMATRIX GetViewMatrix() { return viewMatrix_; };

	XMMATRIX GetProjectionMatrix() { return projMatrix_; };

public:
	XMVECTOR position_;
	XMVECTOR target_;
	XMMATRIX viewMatrix_;
	XMMATRIX projMatrix_;
};

