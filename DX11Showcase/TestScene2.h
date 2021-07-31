#pragma once
#include "Scene.h"

class TestScene2 : public Scene
{
public:
	TestScene2();
	virtual ~TestScene2();

	void SetDependencies(DX11* dx11);

	void Initialize() override;
	void InitializeObjects() override;
	void InitializeGUI() override;

	void OnActivate() override;
	void OnDeactivate() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& fixedDeltaTime) override;
	void Render() override;

private:
	DX11* dx11;
};
