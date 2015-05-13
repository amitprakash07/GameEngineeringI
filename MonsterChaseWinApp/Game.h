#ifndef __GAME_H
#define __GAME_H

#include <assert.h>
#include "Cheesy.h"
#include "Engine.h"

class Game:public myEngine::IMessageHandler
{
public:
	static Game* getGameController();
	void startGame();
	void initGame();
	void endGame();
	void drawGame();
	void HandleMessage(myEngine::utils::StringHash &, void*, void*);
private:
	static Game* mGame;
	Game(){}
	
};


#endif //__GAME_H