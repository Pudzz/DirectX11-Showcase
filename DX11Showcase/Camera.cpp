#include "Camera.h"

Camera::Camera()
{
	this->camRotationMatrix = DirectX::XMMatrixIdentity();
	this->viewMatrix = DirectX::XMMatrixIdentity();
}

Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	eyePosition.m128_f32[0] = x;
	eyePosition.m128_f32[1] = y;
	eyePosition.m128_f32[2] = z;
}

void Camera::SetTargetPosition(float x, float y, float z)
{
	this->lookAt = DirectX::XMVectorSet(x, y, z, 1.0f);
}

void Camera::SetUpvector(float x, float y, float z)
{
	this->upVector = DirectX::XMVectorSet(x, y, z, 0.0f);
}

DirectX::XMFLOAT3 Camera::GetLookAt()
{
	return DirectX::XMFLOAT3(lookAt.m128_f32[0], lookAt.m128_f32[1], lookAt.m128_f32[2]);
}

DirectX::XMFLOAT3 Camera::GetPosition()
{
	return DirectX::XMFLOAT3(eyePosition.m128_f32[0], eyePosition.m128_f32[1], eyePosition.m128_f32[2]);
}

void Camera::SetViewMatrix(DirectX::XMVECTOR eye, DirectX::XMVECTOR lookAt, DirectX::XMVECTOR upVec)
{
	this->viewMatrix = DirectX::XMMatrixLookAtLH(eye, lookAt, upVec);
}

void Camera::GetViewMatrix(DirectX::XMMATRIX&)
{
	viewMatrix = this->viewMatrix;
}

void Camera::UpdateCamera()
{
	/* Fix after input */
}
