#include "TestScene.h"

#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <psapi.h>
#pragma comment(lib, "winmm.lib")

TestScene::TestScene() : dx11(nullptr)
{
	m_startTime = timeGetTime();
}

TestScene::~TestScene()
{
}

void TestScene::SetDependencies(DX11* dx11)
{
	this->dx11 = dx11;
}

void TestScene::Initialize()
{
	InitializeObjects();
	InitializeGUI();
}

void TestScene::InitializeObjects()
{
}

void TestScene::InitializeGUI()
{
}

void TestScene::OnActivate()
{
}

void TestScene::OnDeactivate()
{
}

void TestScene::Update(const float& deltaTime)
{
	m_count++;
	if (timeGetTime() >= (m_startTime + 1000))
	{
		std::cout << "FPS: " << m_count << std::endl;

		m_fps = m_count;
		m_count = 0;
		m_startTime = timeGetTime();
	}
}

void TestScene::FixedUpdate(const float& fixedDeltaTime)
{
}

void TestScene::Render()
{
	dx11->BeginScene(DirectX::XMFLOAT4(0.8f, 0.3f, 0.f, 1.f));
	
	//Logger::Write(LOG_LEVEL::Info, std::to_string(VRamUsage()));
	//Logger::Write(LOG_LEVEL::Info, std::to_string(RamUsage()));

	dx11->EndingScene();
}

float TestScene::VRamUsage()
{
	IDXGIFactory* dxgifactory = nullptr;
	HRESULT ret_code = ::CreateDXGIFactory(
		__uuidof(IDXGIFactory),
		reinterpret_cast<void**>(&dxgifactory));

	float memoryUsage = 0;

	if (SUCCEEDED(ret_code))
	{
		IDXGIAdapter* dxgiAdapter = nullptr;

		if (SUCCEEDED(dxgifactory->EnumAdapters(0, &dxgiAdapter)))
		{
			IDXGIAdapter4* dxgiAdapter4 = NULL;
			if (SUCCEEDED(dxgiAdapter->QueryInterface(__uuidof(IDXGIAdapter4), (void**)&dxgiAdapter4)))
			{
				DXGI_QUERY_VIDEO_MEMORY_INFO info;

				if (SUCCEEDED(dxgiAdapter4->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &info)))
				{
					memoryUsage = float(info.CurrentUsage / 1024.0 / 1024.0); //MiB

					/*char msg[100];
					sprintf_s(msg, "%.2f MiB used", memoryUsage);
					MessageBoxA(0, msg, "VRAM", 0);*/
				};

				dxgiAdapter4->Release();
			}
			dxgiAdapter->Release();
		}
		dxgifactory->Release();
	}

	return memoryUsage;
}

float TestScene::RamUsage()
{
	DWORD currentProcessID = GetCurrentProcessId();

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, currentProcessID);

	if (NULL == hProcess)
		return 0.0f;

	float memoryUsage = 0;

	PROCESS_MEMORY_COUNTERS pmc{};
	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		//PagefileUsage is the:
		//The Commit Charge value in bytes for this process.
		//Commit Charge is the total amount of memory that the memory manager has committed for a running process.

		memoryUsage = float(pmc.PagefileUsage / 1024.0 / 1024.0); //MiB
	}

	CloseHandle(hProcess);

	return memoryUsage;
}
