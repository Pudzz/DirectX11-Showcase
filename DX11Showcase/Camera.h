#pragma once

#include "DX11.h"	// Shift when input 


class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(float x, float y, float z);
	void SetTargetPosition(float x, float y, float z);
	void SetUpvector(float x, float y, float z);
	DirectX::XMFLOAT3 GetLookAt();
	DirectX::XMFLOAT3 GetPosition();
	void SetViewMatrix(DirectX::XMVECTOR eye, DirectX::XMVECTOR lookAt, DirectX::XMVECTOR upVec);
	void GetViewMatrix(DirectX::XMMATRIX&);

	//void GetInputs(Inputs* input);
	//void DetectInputs(double deltaTime);
	void UpdateCamera();

private:
	//Inputs* input;
	//IDirectInput8* directInput;
	//IDirectInputDevice8* keyboard;
	//IDirectInputDevice8* mouse;

	//DIMOUSESTATE mouseLastState;

	DirectX::XMMATRIX viewMatrix;
	DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f);
	DirectX::XMVECTOR lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR upVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DirectX::XMVECTOR DefaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR DefaultRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR camForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR camRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMMATRIX camRotationMatrix;

	float camYaw = 0.0f;
	float camPitch = 0.0f;

	/* For movement */
	//float moveLeftRight = 0.0f;
	//float moveBackForward = 0.0f;
};