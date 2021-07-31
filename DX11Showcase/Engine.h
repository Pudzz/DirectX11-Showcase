#pragma once

#include <unordered_map>
#include "Window.h"
#include "Scene.h"
#include "Timer.h"

#include "Logger.h"

#include "TestScene.h"
#include "TestScene2.h"

class Engine
{
public:
	Engine(HINSTANCE hInstance);
	~Engine();

	void Run();
	void Exit();
	bool IsRunning() const { return this->running; }

	Scene* GetActiveScene() const { return this->activeScene; };
	void AddScene(size_t sceneID, Scene* scene);
	void RemoveScene(size_t sceneID);
	void SwitchScene(size_t sceneID);
	
private:
	bool running;
	std::unordered_map<size_t, Scene*> scenes;
	Scene* activeScene;

	Window window;
	DX11 dx11;
	Timer fpsTimer;
};
