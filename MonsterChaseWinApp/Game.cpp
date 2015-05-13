#include "Game.h"
#include "DoNothingController.h"
#include "WalkController.h"
#include "NonPhysicsController.h"
#include "ThreadedFileProcessor.h"
#include "LoadFile.h"
#include "WanderController.h"


void Game::initGame()
{
	EngineController::GameEngine::startGameEngine();
	
	//Handlers for messaging system
	EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("GameObjectCreated"),Game::getGameController(),myEngine::typedefs::HIGH);
	EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("WelcomeScreenDone"), Game::getGameController(), myEngine::typedefs::HIGH);
	EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("loadingScreenDone"), Game::getGameController(), myEngine::typedefs::HIGH);
	EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("Key Down"), Game::getGameController(), myEngine::typedefs::HIGH);
	EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("Key Pressed"), Game::getGameController(), myEngine::typedefs::HIGH);
	EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("GameOver"), Game::getGameController(), myEngine::typedefs::HIGH);

	//Static Controller registering with the engine
	EngineController::GameEngine::registerGameObjectController(StaticController::getController(), EngineController::GameEngine::getStringPool()->findString("Static"));
	EngineController::GameEngine::registerGameObjectController(StaticController::getController(), EngineController::GameEngine::getStringPool()->findString("static"));
	EngineController::GameEngine::registerGameObjectController(StaticController::getController(), EngineController::GameEngine::getStringPool()->findString("StaticController"));
	EngineController::GameEngine::registerGameObjectController(StaticController::getController(), EngineController::GameEngine::getStringPool()->findString("staticcontroller"));
	EngineController::GameEngine::registerGameObjectController(WanderController::getController(), EngineController::GameEngine::getStringPool()->findString("Wander"));
	EngineController::GameEngine::registerGameObjectController(WanderController::getController(), EngineController::GameEngine::getStringPool()->findString("wander"));
	EngineController::GameEngine::registerGameObjectController(WanderController::getController(), EngineController::GameEngine::getStringPool()->findString("WanderController"));
	EngineController::GameEngine::registerGameObjectController(WanderController::getController(), EngineController::GameEngine::getStringPool()->findString("wandercontroller"));
	EngineController::GameEngine::registerGameObjectController(WalkController::getController(), EngineController::GameEngine::getStringPool()->findString("Walk"));
	EngineController::GameEngine::registerGameObjectController(WalkController::getController(), EngineController::GameEngine::getStringPool()->findString("walk"));
	EngineController::GameEngine::registerGameObjectController(WalkController::getController(), EngineController::GameEngine::getStringPool()->findString("WalkController"));
	EngineController::GameEngine::registerGameObjectController(WalkController::getController(), EngineController::GameEngine::getStringPool()->findString("walkcontroller"));
	EngineController::GameEngine::registerGameObjectController(WalkController::getController(), EngineController::GameEngine::getStringPool()->findString("Player"));
	EngineController::GameEngine::getStringPool()->findString("Configuration.lua");

	

	//WelcomeScreen
	myEngine::SharedPointer<myEngine::GameObject> mGameScreen = myEngine::GameObject::CreateGameObject(myEngine::Vector3D(0.0f, 0.0f, 0.0f));
	mGameScreen->initializeSprite("..\\Resources\\loading_new.png", myEngine::getAsCheesyDimension(1920, 1080), myEngine::getAsCheesyRGBA(255, 255, 255, 255));
	EngineController::GameEngine::getRenderingSystemController()->addToRenderables(mGameScreen);
	
	while (!EngineController::GameEngine::welcomeScreenDone)
	{
		EngineController::GameEngine::getRenderingSystemController()->drawRenderables();
		EngineController::GameEngine::getInputController()->updateInputManager();
		//drawGame();
	}
		
		
	EngineController::GameEngine::getRenderingSystemController()->removeFromRenderables(mGameScreen);
	
	////Loading Screen
	//myEngine::SharedPointer<myEngine::GameObject> mLoadScreen = myEngine::GameObject::CreateGameObject(myEngine::Vector3D(0.0f, 0.0f, 0.0f));
	//mLoadScreen->initializeSprite("..\\Resources\\loading_new.png", myEngine::getAsCheesyDimension(640, 640), myEngine::getAsCheesyRGBA(255, 255, 255, 255));
	//EngineController::GameEngine::getRenderingSystemController()->addToRenderables(mLoadScreen);

	myEngine::LoadTask* mLoadTask = new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(myEngine::LoadTask))) myEngine::LoadTask(EngineController::GameEngine::getStringPool()->findString("Configuration.lua"));
	mLoadTask->addFileProcessingHandler(new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(myEngine::LoadFile))) myEngine::LoadFile());
	myEngine::ThreadedFileProcessor::getInstance().addToLoadQueue(*mLoadTask);

	while (!myEngine::ThreadedFileProcessor::getInstance().shutdown())
	{
		
	}

}


void Game::drawGame()
{
	Cheesy::Service(EngineController::GameEngine::cheesyServiceQuit);
	if (Cheesy::BeginFrame(myEngine::getAsCheesyRGBA(EngineController::GameEngine::getWorldController()->getWindowColor())))
	{
		EngineController::GameEngine::getRenderingSystemController()->drawRenderables();
		EngineController::GameEngine::getInputController()->updateInputManager();
		Cheesy::EndFrame();
	}
}


void Game::startGame()
{
	bool bquit = false;
	
	while (!EngineController::GameEngine::gameOver)
	{
		EngineController::GameEngine::getWorldController()->updateWorld();
		EngineController::GameEngine::getInputController()->updateInputManager();
		//drawGame();
	}
	
}


void Game::HandleMessage(myEngine::utils::StringHash & i_message, void * i_sender, void* i_messageData)
{
	if (myEngine::utils::StringHash("GameObjectCreated") == i_message)
	{
		EngineController::GameEngine::gameObjectsCreatedFromFile = true;
	}
	
	if (myEngine::utils::StringHash("loadingScreenDone") == i_message)
	{
		EngineController::GameEngine::loadingScreenDone = true;
	}
		
	if (myEngine::utils::StringHash("Key Down") == i_message)
	{
		EngineController::GameEngine::welcomeScreenDone = true;
	}

	if (myEngine::utils::StringHash("GameOver") == i_message)
	{
		EngineController::GameEngine::gameOver = true;
	}
}



Game* Game::mGame = nullptr;

Game* Game::getGameController()
{
	if (mGame == nullptr)
	{
		mGame = EngineController::GameEngine::isEngineInitialized() ?
			new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(Game))) Game() :
			new Game();
	}

	return mGame;
}


void Game::endGame()
{
	EngineController::GameEngine::stopGameEngine();
}