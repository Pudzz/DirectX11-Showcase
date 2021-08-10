#pragma once
#include "Scene.h"
#include "Logger.h"

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	void SetDependencies(DX11* dx11); 

	void Initialize() override;
	void InitializeObjects() override;
	void InitializeGUI() override;

	void OnActivate() override;
	void OnDeactivate() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& fixedDeltaTime) override;
	void Render() override;

	float VRamUsage();
	float RamUsage();

private:
	DX11* dx11;
	Timer fpsTimer;
	Camera* mainCamera;
	int m_fps, m_count;
	int m_startTime;
};
