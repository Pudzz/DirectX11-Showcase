#pragma once
#include <d3d11_1.h>
#include <dxgi.h> 
#include <assert.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "Window.h"

#pragma comment(lib, "gdi32")
#pragma comment(lib, "d3d11") 
#pragma comment( lib, "dxgi" )   
#pragma comment(lib, "d3dcompiler.lib")

class DX11
{
	const float blendfactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

public:
	DX11();
	~DX11();
	void Initialize(const Window& window);
	void BeginScene(DirectX::XMFLOAT4 rgba);
	void EndingScene();

	ID3D11Device* GetDevice() { return this->device; }
	ID3D11DeviceContext* GetContext() { return this->context; }
	IDXGISwapChain* GetSwapchain() { return this->swapchain; }

	void CullBackRasterizer() { context->RSSetState(rs_CB); }
	void CullFrontRasterizer() { context->RSSetState(rs_CF); }
	void CullNoneRasterizer() { context->RSSetState(rs_CN); }
	void EnableAlphaBlending() { context->OMSetBlendState(alpha_Enable, blendfactor, 0xffffffff); }
	void DisableAlphaBlending() { context->OMSetBlendState(alpha_Disable, blendfactor, 0xffffffff); }

	void TurnZBufferOn() { context->OMSetDepthStencilState(ds_LessEqual, 1); }
	void TurnZBufferOff() { context->OMSetDepthStencilState(ds_Disabled, 1); }

private:
	HRESULT hr;
	IDXGISwapChain* swapchain;
	ID3D11Device* device;
	ID3D11DeviceContext* context;

	D3D11_VIEWPORT viewPort;
	ID3D11RenderTargetView* rtv;

	ID3D11DepthStencilState* ds_LessEqual;
	ID3D11DepthStencilState* ds_Disabled;
	ID3D11DepthStencilView* dsv;

	ID3D11RasterizerState* rs_CB;
	ID3D11RasterizerState* rs_CF;
	ID3D11RasterizerState* rs_CN;

	ID3D11BlendState* alpha_Enable;
	ID3D11BlendState* alpha_Disable;
};