#pragma once
#include "Window.h"
#include "DX11.h"

class Engine
{
public:
	Engine(HINSTANCE hInstance);
	~Engine();

	void Run();
	void Exit();
	bool IsRunning() const { return this->running; }

	void Update(const float& deltaTime);
	void Render();

	// Scenes

private:
	bool running;
	Window window;
	DX11 dx11;
};
