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
#include "DefaultCollisionHandler.h"
#include "MessagingSystem.h"
#include "additionaltypes.h"
#include "Profiler.h"
#include "ConsolePrint.h"
#include "Text.h"



namespace myEngine
{
	class Properties
	{
	public:
		static myEngine::typedefs::LOG_LEVEL verbosityLvl;
	};
}

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

		struct _CollisionHandler
		{
			myEngine::Physics::ICollisionHandler*								mHandler;
			myEngine::utils::StringHash											mStringHash;
		};
		typedef _CollisionHandler CollisionHandler;
	}

	class GameEngine:public myEngine::IMessageHandler
	{
	public:
		static bool																isThreadingEnabled();
		static void																startGameEngine();
		static bool																isEngineInitialized();
		static void																stopGameEngine();
		static void																registerGameObjectController(myEngine::IGameObjectController*, char*);
		static void																registerCollisionHandler(myEngine::Physics::ICollisionHandler*, char*);

		static MemoryManagement::MemoryManager*									getMemoryManager();
		static myEngine::InputController*										getInputController();
		static myEngine::SharedPointer<myEngine::Timing::Clock>					getEngineClock();
		static myEngine::World*													getWorldController();
		static myEngine::Rendering::Renderables*								getRenderingSystemController();
		static myEngine::Physics::PhysicsSystem*								getPhysicsSystemController();
		static myEngine::Physics::CollisionSystem *								getCollisionSystemController();
		static myEngine::utils::StringPool *									getStringPool();
		static myEngine::MessagingSystem*										getMessagsingSystem();
		static myEngine::IGameObjectController*									getGameObjectController(char*);
		static myEngine::Physics::ICollisionHandler*							getCollisionHandler(char*);
		static myEngine::Profiler*												getProfilerSystem();
		static myEngine::Properties												mProperties;
		static bool																gameObjectsCreatedFromFile;
		static bool																loadingScreenDone;
		static bool																welcomeScreenDone;
		static bool																cheesyServiceQuit;
		static Cheesy::Point2D													SSTextUL;
		static Cheesy::Point2D													SSTextLR;
		static Cheesy::ColorRGBA												White;
		static bool																gameOver;
		
				

	private:
		//static myEngine::World*									mWorld;
		GameEngine();
		static bool																engineInitialized;
		static myEngine::SharedPointer<myEngine::Timing::Clock>					engineClock;
		static std::vector<EngineController::typedefs::GameObjectController>	gameObjectControllerList;
		static std::vector<EngineController::typedefs::CollisionHandler>		mCollisionHandlerList;
		static myEngine::Physics::GenereicCollisionHandler*						mCollisionHandler;
		static bool																mThreadingEnabled;
		
		
	};
}

#endif