#include "Game.h"
#include "DoNothingController.h"
#include "WalkController.h"
#include "NonPhysicsController.h"



void Game::startGame()
{
	bool bQuit = false;
	EngineController::GameEngine::startGameEngine();
	
	//Static Controller registering with the engine
	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("Static"));
	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("static"));
	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("StaticController"));
	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("staticcontroller"));

	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("Walk"));
	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("walk"));
	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("WalkController"));
	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("walkcontroller"));

	EngineController::GameEngine::registerGameObjectController(NonPhysicsGameController::getController(), EngineController::GameEngine::getStringPool()->findString("Player"));

	bool bkeyPressed = false;
	EngineController::GameEngine::getWorldController()->createGameObjects("Configuration.lua");
	
		
	do
	{
		Cheesy::Service(bQuit);
		if (Cheesy::BeginFrame(myEngine::getAsCheesyRGBA( EngineController::GameEngine::getWorldController()->getWindowColor())))
		{
			//Engine::Controller::GameEngine::getInputController()->updateInputManager();
			EngineController::GameEngine::getWorldController()->updateWorld();
			EngineController::GameEngine::getRenderingSystemController()->drawRenderables();
			Cheesy::EndFrame();			
		} //end - if
	} while (!bkeyPressed); //end do-while
	Cheesy::Shutdown();
}