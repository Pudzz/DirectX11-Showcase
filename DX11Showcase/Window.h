#pragma once
#define WIN32_LEAN_AND_MEAN
#include <assert.h>
#include <Windows.h> 

class Window
{
	const LPCWSTR CLASS_NAME = L"EngineClass";
	const LPCWSTR projectTitle = L"Dx11Showcase v0.1";

public:
	Window(HINSTANCE hInstance);
	~Window();

	void Open(size_t width, size_t height);
	size_t GetWidth() const { return this->width; };
	size_t GetHeight()const { return this->height; };
	float GetWindowAspect() const { return static_cast<float>(this->width) / static_cast<float>(this->height); }

	HWND GetHWND() const { return this->hwnd; }
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInstance;
	size_t width, height;
	HWND hwnd;
};
