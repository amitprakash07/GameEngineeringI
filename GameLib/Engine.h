#ifndef __GAMEENGINE_H
#define __GAMEENGINE_H

#include "SharedPointer.h"
#include "InputController.h"
#include "WorldScene.h"
#include "PhysicsSystem.h"
#include "Renderable.h"
#include "FrameTime.h"
#include "HeapManager.h"
#include "CollisionSystem.h"
#include "StringPool.h"
#include "IGameObjectController.h"
#include "HashedString.h"


namespace EngineController
{
	namespace typedefs
	{
		struct __GameObjectController
		{
			myEngine::IGameObjectController *									mGameObjectController;
			myEngine::utils::StringHash											mHash;
		};
		typedef __GameObjectController	GameObjectController;
	}

	class GameEngine
	{
	public:
		static void																startGameEngine();
		static bool																isEngineInitialized();
		static void																stopGameEngine();
		static void																registerGameObjectController(myEngine::IGameObjectController*, char*);

		static MemoryManagement::MemoryManager*									getMemoryManager();
		static myEngine::InputController*										getInputController();
		static myEngine::SharedPointer<myEngine::Timing::Clock>					getEngineClock();
		static myEngine::World*													getWorldController();
		static myEngine::Rendering::Renderables*								getRenderingSystemController();
		static myEngine::Physics::PhysicsSystem*								getPhysicsSystemController();
		static myEngine::Physics::CollisionSystem *								getCollisionSystemController();
		static myEngine::utils::StringPool *									getStringPool();
		static myEngine::IGameObjectController*									getGameObjectController(char*);
				

	private:
		//static myEngine::World*									mWorld;
		GameEngine();
		static bool																engineInitialized;
		static myEngine::SharedPointer<myEngine::Timing::Clock>					engineClock;
		static std::vector<EngineController::typedefs::GameObjectController>	gameObjectControllerList;
		
	};
}

#endif