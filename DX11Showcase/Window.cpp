#include "Window.h"

Window::Window(HINSTANCE hInstance) : hInstance(hInstance)
{
	this->hwnd = 0;
	this->width = 0;
	this->height = 0;
}

Window::~Window()
{
	UnregisterClass(CLASS_NAME, hInstance);
	DestroyWindow(hwnd);
}

void Window::Open(size_t width, size_t height)
{
	this->width = width;
	this->height = height;

	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hbrBackground = nullptr;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = CLASS_NAME;

	if (!RegisterClassEx(&wndClass))
		MessageBox(hwnd, L"Failed to register class", L"Window Initialization Message", MB_ICONERROR);

	RECT windowRect = { 0,0, width, height };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
	int wWidth = windowRect.right - windowRect.left;
	int wHeight = windowRect.bottom - windowRect.top;

	hwnd = CreateWindowEx(0, CLASS_NAME, projectTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wWidth, wHeight, nullptr, nullptr, hInstance, nullptr);
	assert(hwnd);
	ShowWindow(hwnd, SW_SHOW);
}

LRESULT Window::WindowProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
	switch (umsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	return 0;
	}

	// Any other messages send to the default message handler as our application won't make use of them.
	/* Default proc */
	return DefWindowProc(hwnd, umsg, wParam, lParam);
}
