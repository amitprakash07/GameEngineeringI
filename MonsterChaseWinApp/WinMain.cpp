#include "Game.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifdef NDEBUG
#undef NDEBUG
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#define new DBG_NEW
#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	{
		Game::getGameController()->initGame();
		Game::getGameController()->startGame();
		Game::getGameController()->endGame();
	}
	Cheesy::Shutdown();
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}