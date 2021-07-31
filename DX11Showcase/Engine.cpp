#include "Engine.h"

Engine::Engine(HINSTANCE hInstance) : window(hInstance)
{
	running = false;
	window.Open(800, 600);

	dx11.Initialize(window);

	Logger::Open();
	Logger::Write(LOG_LEVEL::Info, "Testing text output");

	AddScene(0, new TestScene());
	AddScene(1, new TestScene2());
	SwitchScene(0);
}

Engine::~Engine()
{
	for (int i = 0; i < scenes.size(); i++)
	{
		if (scenes[i])
			delete scenes[i];
	}

	Logger::Close();
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
			if (activeScene != nullptr)
			{
				activeScene->Update(fpsTimer.DeltaTime());
				activeScene->Render();
			}
			
		}
	}
}

void Engine::Exit()
{
	running = false;
}

void Engine::AddScene(size_t sceneID, Scene* scene)
{
	auto sceneIt = this->scenes.find(sceneID);
	assert(sceneIt == scenes.end(), "Conflicting scene IDs");

	scene->SetDependencies(&dx11);
	scene->Initialize();
	scenes[sceneID] = scene;
}

void Engine::RemoveScene(size_t sceneID)
{
	auto sceneIt = this->scenes.find(sceneID);
	if (sceneIt != scenes.end())
		scenes.erase(sceneIt);
}

void Engine::SwitchScene(size_t sceneID)
{
	auto sceneIt = this->scenes.find(sceneID);
	assert(sceneIt != scenes.end(), "No scene with ID " + std::to_string(sceneID));

	if (activeScene != nullptr)
		activeScene->OnDeactivate();

	activeScene = (*sceneIt).second;
	activeScene->OnActivate();
}