#include "Engine.h"
#include "HashedString.h"


#define HEAPSIZE    (1024*1024)

namespace EngineController
{
	
	bool GameEngine::engineInitialized = false;
	myEngine::SharedPointer<myEngine::Timing::Clock>  GameEngine::engineClock;
	std::vector<EngineController::typedefs::GameObjectController> GameEngine::gameObjectControllerList;
	

	void GameEngine::startGameEngine()
	{
		engineInitialized = true;
#ifdef _ENGINE_DEBUG
		std::cout << TOTALBYTES(1024 * 1024);
#endif
		if (engineClock.isNull())
			engineClock = myEngine::SharedPointer<myEngine::Timing::Clock>(myEngine::Timing::Clock::createAndStart());
		Cheesy::Create(getWorldController()->getGameName(), 
			static_cast<unsigned int>( getWorldController()->getWindowSize().getX()), 
			static_cast<unsigned int>(getWorldController()->getWindowSize().getY()), false);
	}

	
	GameEngine::GameEngine()
	{
		engineInitialized = false;
		gameObjectControllerList.reserve(20);
	}


	void GameEngine::registerGameObjectController(myEngine::IGameObjectController* mGameObjectController, char* i_name)
	{
		assert(mGameObjectController != nullptr);
		assert(i_name != nullptr);
		EngineController::typedefs::GameObjectController tempController = { mGameObjectController, i_name };
		gameObjectControllerList.push_back(tempController);		
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