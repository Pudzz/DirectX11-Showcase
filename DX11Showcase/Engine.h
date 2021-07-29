#pragma once
#include "Window.h"

class Engine
{
public:
	Engine(HINSTANCE hInstance);
	~Engine();

	void Run();
	void Exit();
	bool IsRunning() const { return this->running; }

	// Scenes

private:
	bool running;
	Window window;
};
