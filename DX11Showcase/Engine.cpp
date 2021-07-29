#include "Engine.h"

Engine::Engine(HINSTANCE hInstance) : window(hInstance)
{
	running = false;
	window.Open(800, 600);

	// D3D11
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

		}
	}
}

void Engine::Exit()
{
	running = false;
}
