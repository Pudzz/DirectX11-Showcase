#include "DX11.h"

DX11::DX11() : device(nullptr), context(nullptr), swapchain(nullptr), alpha_Enable(nullptr), alpha_Disable(nullptr), ds_Disabled(nullptr), ds_LessEqual(nullptr), dsv(nullptr), hr(0), 
	rs_CB(nullptr), rs_CF(nullptr), rs_CN(nullptr), rtv(nullptr), viewPort()
{
}
DX11::~DX11()
{
	device->Release();
	device = 0;
	context->Release();
	context = 0;
	swapchain->Release();
	swapchain = 0;
	alpha_Enable->Release();
	alpha_Enable = 0;
	alpha_Disable->Release();
	alpha_Disable = 0;
	ds_Disabled->Release();
	ds_Disabled = 0;
	ds_LessEqual->Release();
	ds_LessEqual = 0;
	dsv->Release();
	dsv = 0;
	rs_CB->Release();
	rs_CB = 0;
	rs_CF->Release();
	rs_CF = 0;
	rs_CN->Release();
	rs_CN = 0;
	rtv->Release();
	rtv = 0;
}

void DX11::Initialize(const Window& window)
{
	DXGI_SWAP_CHAIN_DESC swapchainDesc;
	ZeroMemory(&swapchainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapchainDesc.BufferCount = 1;
	swapchainDesc.BufferDesc.Width = window.GetWidth();
	swapchainDesc.BufferDesc.Height = window.GetHeight();
	swapchainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapchainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapchainDesc.SampleDesc.Count = 1u;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.OutputWindow = window.GetHWND();
	swapchainDesc.Windowed = true;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDesc.Flags = 0;

	UINT swapflags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef  _DEBUG
	swapflags |= D3D11_CREATE_DEVICE_DEBUG; 
#endif

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_0 };
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, swapflags, featureLevel, 1, D3D11_SDK_VERSION, &swapchainDesc, &swapchain, &device, nullptr, &context);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D* backbufferPtr;
	hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbufferPtr);
	assert(SUCCEEDED(hr));

	hr = device->CreateRenderTargetView(backbufferPtr, nullptr, &rtv);
	assert(SUCCEEDED(hr));

	backbufferPtr->Release();
	backbufferPtr = 0;

	// Depth

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthBufferDesc.Width = window.GetWidth();
	depthBufferDesc.Height = window.GetHeight();
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	ID3D11Texture2D* depthStencilBuffer;
	hr = device->CreateTexture2D(&depthBufferDesc, 0, &depthStencilBuffer);
	assert(SUCCEEDED(hr));

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;   
		
	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = device->CreateDepthStencilState(&depthStencilDesc, &ds_LessEqual);
	assert(SUCCEEDED(hr));

	// Second depth stencil state which turns off the Z buffer for 2D rendering. The only difference is 
	// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
	depthStencilDesc.DepthEnable = false;

	hr = device->CreateDepthStencilState(&depthStencilDesc, &ds_Disabled);
	assert(SUCCEEDED(hr));

	// Default mode
	context->OMSetDepthStencilState(ds_LessEqual, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	hr = device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &dsv);
	assert(SUCCEEDED(hr));

	context->OMSetRenderTargets(1, &rtv, dsv);

	depthStencilBuffer->Release();
	depthStencilBuffer = 0;


	// Rasterizer

	D3D11_RASTERIZER_DESC rasterizerStateDesc;
	ZeroMemory(&rasterizerStateDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerStateDesc.AntialiasedLineEnable = false;
	rasterizerStateDesc.MultisampleEnable = false;
	rasterizerStateDesc.ScissorEnable = false;
	rasterizerStateDesc.DepthClipEnable = true;

	rasterizerStateDesc.CullMode = D3D11_CULL_BACK;
	rasterizerStateDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerStateDesc.FrontCounterClockwise = false;

	rasterizerStateDesc.DepthBias = 0;
	rasterizerStateDesc.DepthBiasClamp = 0.0f;
	rasterizerStateDesc.SlopeScaledDepthBias = 0.0f;

	hr = device->CreateRasterizerState(&rasterizerStateDesc, &rs_CB);
	if (FAILED(hr)) {
		MessageBox(0, L"Failed to 'CreateRasterizerState'- CullBack.", L"Graphics scene Initialization Message", MB_ICONERROR);
	}

	rasterizerStateDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerStateDesc.CullMode = D3D11_CULL_FRONT;
	hr = device->CreateRasterizerState(&rasterizerStateDesc, &rs_CF);
	if (FAILED(hr)) {
		MessageBox(0, L"Failed to 'CreateRasterizerState'. - CullFront", L"Graphics scene Initialization Message", MB_ICONERROR);
	}

	rasterizerStateDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerStateDesc.CullMode = D3D11_CULL_NONE;
	hr = device->CreateRasterizerState(&rasterizerStateDesc, &rs_CN);
	if (FAILED(hr)) {
		MessageBox(0, L"Failed to 'CreateRasterizerState'. - CullNone", L"Graphics scene Initialization Message", MB_ICONERROR);
	}

	// Default rasterizer
	context->RSSetState(rs_CB);


	// Viewport

	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = static_cast<FLOAT>(window.GetWidth());
	viewPort.Height = static_cast<FLOAT>(window.GetHeight());
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewPort);


	// Blend states

	D3D11_BLEND_DESC blendStateDesc;
	ZeroMemory(&blendStateDesc, sizeof(D3D11_BLEND_DESC));
	blendStateDesc.RenderTarget[0].BlendEnable = true;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	hr = device->CreateBlendState(&blendStateDesc, &alpha_Enable);
	assert(SUCCEEDED(hr));

	blendStateDesc.RenderTarget[0].BlendEnable = false;
	hr = device->CreateBlendState(&blendStateDesc, &alpha_Disable);
	assert(SUCCEEDED(hr));

}

void DX11::BeginScene(DirectX::XMFLOAT4 rgba)
{
	float a[] = { rgba.x, rgba.y, rgba.z, rgba.w };
	context->ClearRenderTargetView(rtv, a);
}

void DX11::EndingScene()
{
	swapchain->Present(1, 0);
}
