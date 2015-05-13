#include "WorldScene.h"
#include "HeapManager.h"
#include "Renderable.h"
#include "Engine.h"
#include "LuaPlus.h"
#include "LuaUtilityHelper.h"


namespace myEngine
{	
	World* World::mWorld = nullptr;

	World* World::getWorld()
	{
		if (mWorld == nullptr)
		{
			mWorld = (EngineController::GameEngine::isEngineInitialized()) ?
				new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(World))) World() :
				new World();
		}
			
		return mWorld;
	}


	std::vector<SharedPointer<GameObject>> World::getGameObjectList()
	{
		return mGameObjectList;
	}

	void World::deleteWorld()
	{
		MessagedAssert(mWorld != nullptr, "World Controller is either deleted or not instaniated");
		EngineController::GameEngine::isEngineInitialized() ?
			EngineController::GameEngine::getMemoryManager()->__free(mWorld) :
			delete mWorld;
	}


	World::~World()
	{
		if (mGameObjectList.size() > 0)
		{
			while (mGameObjectList.size() != 0)
				mGameObjectList.erase(mGameObjectList.begin());
		}
		
		if (mGameName != nullptr)
			delete mGameName;
	}


	World::World()
	{
		mGameObjectList.reserve(200);
		mGameName = _strdup(EngineController::GameEngine::getStringPool()->findString("MonsterChaseGame"));
		mGameWindow = Vector2D(1024.0f, 768.0f);
		mGameWindowColor.R = 50;
		mGameWindowColor.G = 50;
		mGameWindowColor.B = 255;
		mGameWindowColor.A = 0;
		EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("Player Died"), this, myEngine::typedefs::HIGH);
		//initialized = true;
	}



	void World::addToWorld(SharedPointer<GameObject> & ipGameObject)
	{
		if (!ipGameObject.isNull())
			mGameObjectList.push_back(ipGameObject);
	}


	void World::HandleMessage(myEngine::utils::StringHash & i_message, void *i_MessageSender, void* i_pMessageData)
	{
		if (i_message == myEngine::utils::StringHash("Player Died"))
		{
			while (mGameObjectList.size() > 0)
				removeFromWorld(mGameObjectList.at(0));
			EngineController::GameEngine::getMessagsingSystem()->sendMessage(myEngine::utils::StringHash("GameOver"), this);
		}
	}


	SharedPointer<GameObject> World::getNearestGameObject(Vector3D iPosiiton)
	{
		SharedPointer<GameObject> nearestGameObject = mGameObjectList.at(0); //= mGameObjectList[0];
		float nearestDistance = (nearestGameObject->getPosition() - iPosiiton).length();
		float tempDistance;
		assert(mGameObjectList.size() > 0);
		for (size_t i = 1; i < mGameObjectList.size(); i++)
		{
			tempDistance = (mGameObjectList[i]->getPosition() - iPosiiton).length();
			if (AlmostEqualUlpsFinal(nearestDistance, 0.0f, 10))
			{
				nearestDistance = tempDistance;
				continue;
			}			
			if (( !AlmostEqualUlpsFinal(tempDistance, 0.0f, 10) && tempDistance < nearestDistance))
				nearestGameObject = mGameObjectList[i];
		}//end-for
		return nearestGameObject;
	}//end-getNearestGameObject


	SharedPointer<GameObject> World::getNearestGameObjectWithPointer(Vector3D iPosiiton)
	{
		SharedPointer<GameObject> nearestGameObject = mGameObjectList.at(0); //= mGameObjectList[0];
		float nearestDistance = (nearestGameObject->getPosition() - iPosiiton).length();

		assert(mGameObjectList.size() > 0);
		for (size_t i = 1; i < mGameObjectList.size(); i++)
		{
			if ((mGameObjectList[i]->getPosition() - iPosiiton).length() < nearestDistance)
				nearestGameObject = mGameObjectList[i];
		}//end-for
		return nearestGameObject;
		
	}//end-getNearestGameObjectWithPointer

	SharedPointer<GameObject> World::getPlayer()
	{
		for (unsigned __int16 i = 0; i < mGameObjectList.size(); i++)
		{
			if (myEngine::utils::StringHash(mGameObjectList[i]->getType()) == myEngine::utils::StringHash("Player"))
				return mGameObjectList[i];
		}
	}



	void World::createGameObjects(char * i_configuration)
	{
		LuaPlus::LuaObject player;
				
		if (LuaUtilityHelper::getGlobalLuaObject(i_configuration, EngineController::GameEngine::getStringPool()->findString("Settings"), player)
			&& LuaUtilityHelper::getGameSettings(player, gameConfiguration))
		{
			LuaUtilityHelper::LuaActor playerActor;
			if (LuaUtilityHelper::getGlobalLuaObject(gameConfiguration.actorFile, EngineController::GameEngine::getStringPool()->findString("Player"), player)
				&& LuaUtilityHelper::getLuaActor(player, playerActor))
			{
				SharedPointer<myEngine::GameObject> mPlayer = GameObject::CreateGameObject(playerActor);
				this->addToWorld(mPlayer);
				EngineController::GameEngine::getPhysicsSystemController()->addToPhysicsSystem(mPlayer);
				EngineController::GameEngine::getCollisionSystemController()->addToCollisionsystem(mPlayer);
				EngineController::GameEngine::getRenderingSystemController()->addToRenderables(mPlayer);
			}

			LuaPlus::LuaObject monsters;
			if (LuaUtilityHelper::getGlobalLuaObject(gameConfiguration.actorFile, EngineController::GameEngine::getStringPool()->findString("Monsters"), monsters)
				&& monsters.IsTable())
			{
				for (LuaPlus::LuaTableIterator it(monsters); it; it.Next())
				{
					LuaUtilityHelper::LuaActor monster;
					LuaUtilityHelper::getLuaActor(it.GetValue(), monster);
					SharedPointer<GameObject> tempMonster = GameObject::CreateGameObject(monster);
					this->addToWorld(tempMonster);
					EngineController::GameEngine::getPhysicsSystemController()->addToPhysicsSystem(tempMonster);
					EngineController::GameEngine::getCollisionSystemController()->addToCollisionsystem(tempMonster);
					EngineController::GameEngine::getRenderingSystemController()->addToRenderables(tempMonster);
				}
			}

		}
	}//end function



	LuaUtilityHelper::Settings World::getGameConfiguration()
	{
		return gameConfiguration;	
	}



	void World::updateWorld()
	{
		EngineController::GameEngine::getPhysicsSystemController()->updatePhysicsSystem();
		EngineController::GameEngine::getCollisionSystemController()->updateCollisionSystem();
		EngineController::GameEngine::getEngineClock()->updateDeltaTime();
		EngineController::GameEngine::getRenderingSystemController()->drawRenderables();
	}


	bool World::removeFromWorld(SharedPointer<GameObject>& i_gameObject)
	{
		if (EngineController::GameEngine::getRenderingSystemController()->removeFromRenderables(i_gameObject) &&
			EngineController::GameEngine::getCollisionSystemController()->removeFromCollisionSystem(i_gameObject) &&
			EngineController::GameEngine::getPhysicsSystemController()->removeFromPhysicsSystem(i_gameObject))
		{
			unsigned __int16 index = 0x0f0f0f0f;
			if (inWorld(i_gameObject, index) && (index != 0x0f0f0f0f))
			{
				mGameObjectList.erase(mGameObjectList.begin() + index);
				return true;
			}
		}
		return false;
	}

	bool World::inWorld(SharedPointer<GameObject> & i_gameObject, unsigned __int16 & o_index)
	{
		MessagedAssert(!i_gameObject.isNull(), "Passed Game Object Pointer is null");
		for (unsigned __int16 i = 0; i < mGameObjectList.size(); i++)
		{
			if (mGameObjectList.at(i).isEqual(i_gameObject))
			{
				o_index = i;
				return true;
			}			
		}
		return false;
	}

	char* World::getGameName() const
	{
		return mGameName;
	}

	void World::setGameName(char * i_name)
	{
		mGameName = _strdup(i_name);
	}

	myEngine::typedefs::RGBA World::getWindowColor() const
	{
		return mGameWindowColor;
	}

	void World::setWindowColor(myEngine::typedefs::RGBA i_rgba)
	{
		mGameWindowColor = i_rgba;
	}

	Vector2D World::getWindowSize() 
	{
		return mGameWindow;
	}

	void World::setWindowSize(Vector2D i_windowSize)
	{
		mGameWindow = i_windowSize;
	}




}//myEngine

