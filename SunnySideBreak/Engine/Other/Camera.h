#pragma once
#include"../Draw/D3D.h"
#include "../Other/Global.h"
#include <DirectXMath.h>
using namespace DirectX;
class Camera
{
public:
	void Initialize();

	void CreateViewMat();

	void SetPosition(XMVECTOR _position) ;

	void SetTarget(XMVECTOR _target);

	XMMATRIX GetViewMatrix();

	XMMATRIX GetProjectionMatrix();

	static Camera &GetInstance();
private:
	XMVECTOR position_;
	XMVECTOR target_;
	XMMATRIX viewMatrix_;
	XMMATRIX projMatrix_;
};

