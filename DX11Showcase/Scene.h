#pragma once
#include "DX11.h"
#include "Timer.h"
#include "Camera.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual void SetDependencies(DX11* dx11) = 0;

	virtual void Initialize() = 0;
	virtual void InitializeObjects() = 0;
	virtual void InitializeGUI() = 0;

	virtual void OnActivate() = 0;
	virtual void OnDeactivate() = 0;

	virtual void Update(const float& deltaTime) = 0;
	virtual void FixedUpdate(const float& fixedDeltaTime) = 0;
	virtual void Render() = 0;

private:
	DX11* dx11;
};