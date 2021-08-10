#include "Shader.h"

Shader::Shader(ID3D11Device* device)
{
	this->hr = 0;
	this->vertexShader = 0;
	this->pixelShader = 0;
	this->geometryShader = 0;
	this->inputLayout = 0;

	this->device = device;
	this->bufferPerObject = 0;
	this->cameraBuffer = 0;
	this->lightBuffer = 0;

	this->VSBlob = 0;
	this->PSBlob = 0;
	this->GSBlob = 0;
	this->ErrorBlob = 0;

	this->texture = 0;

	ZeroMemory(&cbPerCamera, sizeof(cBufferCamera));
	ZeroMemory(&cbPerLight, sizeof(cBufferLight));
	ZeroMemory(&cbPerObject, sizeof(cBufferPerObject));
}

Shader::~Shader()
{
}

void Shader::Shutdown()
{
	ShutdownShader();
}

void Shader::InitializeShaders(ID3D11Device* device, HWND hwnd, LPCWSTR vsFilename, LPCWSTR psFilename, LPCSTR entryVS, LPCSTR entryPS)
{
	/*
		COMPILE VERTEX AND PIXEL SHADERS, THEN CREATE THEM
	*/

	hr = D3DCompileFromFile(vsFilename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryVS, "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, NULL, &VSBlob, &ErrorBlob);
	if (FAILED(hr)) {
		if (ErrorBlob) {
			OutputDebugStringA((char*)ErrorBlob->GetBufferPointer());
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
			ReleasePtr(ErrorBlob);
		}

		if (VSBlob) {
			ReleasePtr(VSBlob);
		}
		assert(false);
	}

	hr = D3DCompileFromFile(psFilename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPS, "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, NULL, &PSBlob, &ErrorBlob);
	if (FAILED(hr)) {
		if (ErrorBlob) {
			OutputDebugStringA((char*)ErrorBlob->GetBufferPointer());
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
			ReleasePtr(ErrorBlob);
		}

		if (PSBlob) {
			ReleasePtr(PSBlob);
		}
		assert(false);
	}

	// Create Vertexshader
	hr = device->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), nullptr, &this->vertexShader);
	assert(hr);

	// Create pixelshader
	hr = device->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), nullptr, &this->pixelShader);
	assert(hr);


	/*
		CONSTANT BUFFER , CBPEROBJECT/Camerabuffer/Lightbuffer
	*/

	D3D11_BUFFER_DESC cBufferDescription;
	ZeroMemory(&cBufferDescription, sizeof(D3D11_BUFFER_DESC));
	cBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	cBufferDescription.ByteWidth = static_cast<uint32_t>(sizeof(cBufferPerObject) + (16 - (sizeof(cBufferPerObject) % 16)));
	cBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDescription.CPUAccessFlags = 0;
	cBufferDescription.MiscFlags = 0;
	cBufferDescription.StructureByteStride = 0;

	hr = device->CreateBuffer(&cBufferDescription, NULL, &bufferPerObject);
	assert(hr);


	ZeroMemory(&cBufferDescription, sizeof(cBufferDescription));
	cBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	cBufferDescription.ByteWidth = static_cast<uint32_t>(sizeof(cBufferCamera) + (16 - (sizeof(cBufferCamera) % 16)));
	cBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDescription.CPUAccessFlags = 0;
	cBufferDescription.MiscFlags = 0;
	cBufferDescription.StructureByteStride = 0;

	hr = device->CreateBuffer(&cBufferDescription, NULL, &cameraBuffer);
	assert(hr);


	ZeroMemory(&cBufferDescription, sizeof(cBufferDescription));
	cBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	cBufferDescription.ByteWidth = static_cast<uint32_t>(sizeof(cBufferLight) + (16 - (sizeof(cBufferLight) % 16)));
	cBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDescription.CPUAccessFlags = 0;
	cBufferDescription.MiscFlags = 0;
	cBufferDescription.StructureByteStride = 0;

	hr = device->CreateBuffer(&cBufferDescription, NULL, &lightBuffer);
	assert(hr);	
}

void Shader::CreateDefaultInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC INPUT_LAYOUT_V_UV_N_T[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,	 D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",	 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"BONEWEIGHTS", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"BONEINDICES", 0, DXGI_FORMAT_R32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},

	};

	hr = device->CreateInputLayout(INPUT_LAYOUT_V_UV_N_T, ARRAYSIZE(INPUT_LAYOUT_V_UV_N_T), VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), &inputLayout);
	assert(hr);
		
	ReleasePtr(VSBlob);
	ReleasePtr(PSBlob);
}

void Shader::Render(ID3D11DeviceContext* context, Model* model, DirectX::XMMATRIX view, DirectX::XMMATRIX projection, Camera* camera, Light* light, ID3D11SamplerState* sampler)
{
	SetCBuffers(context, model, view, projection, camera, light);
	RenderShader(context, model->GetIndexCount(), sampler);
}

void Shader::ShutdownShader()
{	
	// Release the constant buffers.
	if (lightBuffer)
	{
		lightBuffer->Release();
		lightBuffer = 0;
	}

	if (cameraBuffer)
	{
		cameraBuffer->Release();
		cameraBuffer = 0;
	}

	if (bufferPerObject)
	{
		bufferPerObject->Release();
		bufferPerObject = 0;
	}

	// Release the layout.
	if (inputLayout)
	{
		inputLayout->Release();
		inputLayout = 0;
	}

	// Release the pixel shader.
	if (pixelShader)
	{
		pixelShader->Release();
		pixelShader = 0;
	}

	// Release the vertex shader.
	if (vertexShader)
	{
		vertexShader->Release();
		vertexShader = 0;
	}

	// Release the geometry shader.
	if (geometryShader)
	{
		geometryShader->Release();
		geometryShader = 0;
	}

	if (ErrorBlob)
	{
		ReleasePtr(ErrorBlob);
	}

	if (VSBlob)
	{
		ReleasePtr(VSBlob);
	}

	if (PSBlob)
	{
		ReleasePtr(PSBlob);
	}

	if (GSBlob)
	{
		ReleasePtr(GSBlob);
	}
}

void Shader::SetCBuffers(ID3D11DeviceContext* context, Model* model, DirectX::XMMATRIX view, DirectX::XMMATRIX projection, Camera* camera, Light* light)
{
	DirectX::XMMATRIX worldViewProjection;
	worldViewProjection = model->GetWorldMatrix() * view * projection;

	cbPerObject.worldViewProj = DirectX::XMMatrixTranspose(worldViewProjection);
	cbPerObject.world = DirectX::XMMatrixTranspose(model->GetWorldMatrix());
	cbPerObject.InverseWorld = DirectX::XMMatrixInverse(nullptr, model->GetWorldMatrix());

	context->UpdateSubresource(bufferPerObject, 0, nullptr, &cbPerObject, 0, 0);
	context->VSSetConstantBuffers(0, 1, &bufferPerObject);		

	/*
		Set Camera buffer	// To Vertexshader
	*/
	cbPerCamera.cameraPosition = camera->GetPosition();

	context->UpdateSubresource(cameraBuffer, 0, nullptr, &cbPerCamera, 0, 0);
	context->VSSetConstantBuffers(1, 1, &cameraBuffer);

	/*
		Set Light buffer	// To Pixelshader
	*/
	cbPerLight.ambientLightColor = light->GetAmbientColor();
	cbPerLight.diffuseLightColor = light->GetDiffuseColor();
	cbPerLight.specularLightColor = light->GetSpecularColor();
	cbPerLight.lightPosition = light->GetLightPosition();
	cbPerLight.lightRange = light->GetLightRange();
	cbPerLight.lightAttenuation = light->GetLightAttenuation();

	context->UpdateSubresource(lightBuffer, 0, nullptr, &cbPerLight, 0, 0);
	context->PSSetConstantBuffers(0, 1, &lightBuffer);	
}

void Shader::RenderShader(ID3D11DeviceContext* context, int indexcount, ID3D11SamplerState* sampler)
{
	// sets the vertex shader and layout
	context->IASetInputLayout(inputLayout);

	// Sets pixel and vertex shader
	context->VSSetShader(vertexShader, 0, 0);
	context->GSSetShader(geometryShader, 0, 0);
	context->PSSetShader(pixelShader, 0, 0);

	// Set the sampler state in the pixel shader.
	context->PSSetSamplers(0, 1, &sampler);

	context->DrawIndexed(indexcount, 0, 0);
}
