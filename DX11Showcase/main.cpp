#define _CRTDBG_MAP_ALLOC

#include "Engine.h"
#include <crtdbg.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Use this to search for memory leak locations
	//_crtBreakAlloc = 650485;
		
	Engine engine(hInstance);
	engine.Run();

	return 0;
}