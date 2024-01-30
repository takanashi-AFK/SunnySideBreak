#include "Camera.h"

void Camera::Initialize()
{
    //èâä˙ÉJÉÅÉâ
    position_ = XMVectorSet(0, 3, -10, 0);
    target_ = XMVectorSet(0, 0, 0, 0);	

    projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_WindowWidth / g_WindowHeight, 0.1f, 100.0f);
}

void Camera::CreateViewMat()
{
    viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

void Camera::SetPosition(XMVECTOR _position)
{
    position_ = _position;
}

void Camera::SetTarget(XMVECTOR _target)
{
    target_ = _target;
}

XMMATRIX Camera::GetViewMatrix()
{
    return viewMatrix_;
}

XMMATRIX Camera::GetProjectionMatrix()
{
    return projMatrix_;
}

Camera &Camera::GetInstance()
{
    static Camera instance;
    return instance;
}

