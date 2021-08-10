#pragma once

#include "DX11.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"

class Shader
{
private:
	__declspec(align(16))
		struct cBufferPerObject
	{
		cBufferPerObject() { ZeroMemory(this, sizeof(this)); }

		DirectX::XMMATRIX worldViewProj;
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX InverseWorld;
	};

	__declspec(align(16))
		struct cBufferCamera {

		DirectX::XMFLOAT3 cameraPosition;
		float padding;
	};

	__declspec(align(16))
		struct cBufferLight
	{
		DirectX::XMFLOAT4 ambientLightColor;
		DirectX::XMFLOAT4 diffuseLightColor;
		DirectX::XMFLOAT4 specularLightColor;
		DirectX::XMFLOAT3 lightPosition;
		float lightRange;

		DirectX::XMFLOAT3 lightAttenuation;
		float padding;
	};

public:
	Shader(ID3D11Device* device);
	~Shader();

	void InitializeShaders(ID3D11Device* device, HWND hwnd, LPCWSTR vsFilename, LPCWSTR psFilename, LPCSTR entryVS, LPCSTR entryPS);

	void Shutdown();
	void CreateDefaultInputLayout(ID3D11Device* device);
	void Render(ID3D11DeviceContext* context, Model* model, DirectX::XMMATRIX view, DirectX::XMMATRIX projection, Camera* camera, Light* light, ID3D11SamplerState* sampler);

private:
	void ShutdownShader();
	void SetCBuffers(ID3D11DeviceContext* context, Model* model, DirectX::XMMATRIX view, DirectX::XMMATRIX projection, Camera* camera, Light* light);
	void RenderShader(ID3D11DeviceContext* context, int indexcount, ID3D11SamplerState* sampler);

private:
	HRESULT hr;
	ID3D11VertexShader* vertexShader;
	ID3D11GeometryShader* geometryShader;
	ID3D11PixelShader* pixelShader;

	ID3D11InputLayout* inputLayout;

	ID3DBlob* ErrorBlob;
	ID3DBlob* VSBlob;
	ID3DBlob* GSBlob;
	ID3DBlob* PSBlob;

	cBufferPerObject cbPerObject;
	cBufferCamera cbPerCamera;
	cBufferLight cbPerLight;
	//cBufferMaterial cbPerMaterial;

	ID3D11Buffer* bufferPerObject;
	ID3D11Buffer* cameraBuffer;
	ID3D11Buffer* lightBuffer;
	//ID3D11Buffer* materialBuffer;

	ID3D11ShaderResourceView* texture;

	ID3D11Device* device;
};
