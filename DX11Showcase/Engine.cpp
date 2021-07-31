#include "Engine.h"

Engine::Engine(HINSTANCE hInstance) : window(hInstance)
{
	running = false;
	window.Open(800, 600);

	// D3D11
	dx11.Initialize(window);
}

Engine::~Engine()
{
}

void Engine::Run()
{
	running = true;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (running)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				Exit();
		}
		else
		{
			dx11.BeginScene(DirectX::XMFLOAT4(0.8, 0.3, 0, 1));
			dx11.EndingScene();
		}
	}
}

void Engine::Exit()
{
	running = false;
}
