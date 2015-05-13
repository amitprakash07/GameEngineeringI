#include "Engine.h"
#include "HashedString.h"
#include "StringPool.h"
#include "DefaultCollisionHandler.h"
#include <stdlib.h>
#include <wtypes.h>
#include "ThreadedFileProcessor.h"


#define HEAPSIZE    (1024*1024)

namespace EngineController
{
	
	bool GameEngine::engineInitialized = false;
	myEngine::SharedPointer<myEngine::Timing::Clock>					GameEngine::engineClock;
	std::vector<EngineController::typedefs::GameObjectController>		GameEngine::gameObjectControllerList;
	std::vector<EngineController::typedefs::CollisionHandler>			GameEngine::mCollisionHandlerList;
	myEngine::Physics::GenereicCollisionHandler*						GameEngine::mCollisionHandler = new(getMemoryManager()->__alloc(sizeof(myEngine::Physics::GenereicCollisionHandler))) myEngine::Physics::GenereicCollisionHandler();
	myEngine::Properties												GameEngine::mProperties;
	bool																GameEngine::mThreadingEnabled = true;
	bool																GameEngine::gameObjectsCreatedFromFile = false;
	bool																GameEngine::loadingScreenDone = false;
	bool																GameEngine::welcomeScreenDone = false;
	bool																GameEngine::cheesyServiceQuit = false;
	Cheesy::Point2D														GameEngine::SSTextUL(900, 500);
	Cheesy::Point2D														GameEngine::SSTextLR(1000, 540);
	Cheesy::ColorRGBA													GameEngine::White(255, 255, 255, 255);
	bool																GameEngine::gameOver = false;



	GameEngine::GameEngine()
	{
		engineInitialized = false;
		mThreadingEnabled = false;
		gameObjectControllerList.reserve(20);
	}

	bool GameEngine::isThreadingEnabled()
	{
		return mThreadingEnabled;
	}


	void GameEngine::startGameEngine()
	{
		engineInitialized = true;
		if (engineClock.isNull())
			engineClock = myEngine::SharedPointer<myEngine::Timing::Clock>(myEngine::Timing::Clock::createAndStart());
		



		srand(10);
		RECT desktop;
		const HWND screen = GetDesktopWindow();
		GetWindowRect(screen, &desktop);
		getWorldController()->setWindowSize(myEngine::Vector2D(static_cast<float>(desktop.right), static_cast<float>(desktop.bottom)));
		registerCollisionHandler(mCollisionHandler, "Default");
		Cheesy::Create(getWorldController()->getGameName(), static_cast<unsigned int>(getWorldController()->getWindowSize().getX()), static_cast<unsigned int>(getWorldController()->getWindowSize().getY()), false);

	}

	
	void GameEngine::stopGameEngine()
	{
		
		EngineController::GameEngine::getCollisionSystemController()->deleteCollisionSystem();
		EngineController::GameEngine::getPhysicsSystemController()->getPhysicsSystem()->deletePhysicsSystem();
		EngineController::GameEngine::getWorldController()->deleteWorld();
		EngineController::GameEngine::getRenderingSystemController()->deleteRenderingSystem();
		myEngine::ThreadedFileProcessor::deleteThreadFileProcessor();
	}


	void GameEngine::registerGameObjectController(myEngine::IGameObjectController* mGameObjectController, char* i_name)
	{
		assert(mGameObjectController != nullptr);
		assert(i_name != nullptr);
		EngineController::typedefs::GameObjectController tempController = { mGameObjectController, i_name };
		gameObjectControllerList.push_back(tempController);		
	}


	void GameEngine::registerCollisionHandler(myEngine::Physics::ICollisionHandler* i_collisionHandler, char* i_name)
	{
		assert(i_collisionHandler != nullptr);
		assert(i_name != nullptr);
		EngineController::typedefs::CollisionHandler tempCollisionHandler = { i_collisionHandler, getStringPool()->findString(i_name) };
		mCollisionHandlerList.push_back(tempCollisionHandler);
	}

	
	myEngine::IGameObjectController* GameEngine::getGameObjectController(char * i_gameController)
	{
		assert(i_gameController!= nullptr);
		for (unsigned __int16 i = 0; i < gameObjectControllerList.size(); i++)
		{
			if (gameObjectControllerList[i].mHash == myEngine::utils::StringHash(getStringPool()->findString( i_gameController)))
				return gameObjectControllerList[i].mGameObjectController;
		}
		return nullptr;
	}


	myEngine::Physics::ICollisionHandler* GameEngine::getCollisionHandler(char * i_collisionHandler)
	{
		assert(!myEngine::utils::StringHash(i_collisionHandler).isNil());
		for (unsigned __int16 i = 0; i < mCollisionHandlerList.size(); i++)
		{
			if (mCollisionHandlerList[i].mStringHash == myEngine::utils::StringHash(getStringPool()->findString(i_collisionHandler)))
				return mCollisionHandlerList[i].mHandler;
		}
		return nullptr;
	}


	myEngine::Profiler* GameEngine::getProfilerSystem()
	{
		return (myEngine::Profiler::getProfiler());
	}


	bool GameEngine::isEngineInitialized()
	{
		return engineInitialized;
	}


	MemoryManagement::MemoryManager* GameEngine::getMemoryManager()
	{
		return (MemoryManagement::MemoryManager::getMemoryManager());
	}

	
	
	myEngine::utils::StringPool* GameEngine::getStringPool()
	{
		return myEngine::utils::StringPool::getStringPool();
	}

	
	
	myEngine::InputController* GameEngine::getInputController()
	{
		return(myEngine::InputController::getInputManager());
	}

	
	
	myEngine::Physics::PhysicsSystem* GameEngine::getPhysicsSystemController()
	{
		return (myEngine::Physics::PhysicsSystem::getPhysicsSystem());
	}

	
	
	
	myEngine::Physics::CollisionSystem* GameEngine::getCollisionSystemController()
	{
		return(myEngine::Physics::CollisionSystem::getCollisionSystem());
	}

	
	myEngine::MessagingSystem* GameEngine::getMessagsingSystem()
	{
		return(myEngine::MessagingSystem::getMessagingSystem());
	}
	
	myEngine::SharedPointer<myEngine::Timing::Clock> GameEngine::getEngineClock()
	{
		if (engineClock.isNull())
			engineClock = myEngine::SharedPointer<myEngine::Timing::Clock>(myEngine::Timing::Clock::createAndStart());
		return engineClock;
	}

	
	
	myEngine::Rendering::Renderables* GameEngine::getRenderingSystemController()
	{
		return (myEngine::Rendering::Renderables::getRenderingSystem());
	}

	
	
	myEngine::World* GameEngine::getWorldController()
	{
		return myEngine::World::getWorld();
	}
	
}