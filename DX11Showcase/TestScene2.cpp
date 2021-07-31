#include "TestScene2.h"
TestScene2::TestScene2()
{
}

TestScene2::~TestScene2()
{
}

void TestScene2::SetDependencies(DX11* dx11)
{
	this->dx11 = dx11;
}

void TestScene2::Initialize()
{
	InitializeObjects();
	InitializeGUI();
}

void TestScene2::InitializeObjects()
{
}

void TestScene2::InitializeGUI()
{
}

void TestScene2::OnActivate()
{
}

void TestScene2::OnDeactivate()
{
}

void TestScene2::Update(const float& deltaTime)
{
}

void TestScene2::FixedUpdate(const float& fixedDeltaTime)
{
}

void TestScene2::Render()
{
	dx11->BeginScene(DirectX::XMFLOAT4(0.8f, 0.0f, 0.f, 1.f));
	dx11->EndingScene();
}
