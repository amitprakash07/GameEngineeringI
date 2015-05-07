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
		for (unsigned __int16 i = 0; i < mGameObjectList.size(); i++)
		{
			if (!mGameObjectList[i].isNull())
				mGameObjectList[i].deleteObject();
		}
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
		//initialized = true;
	}



	void World::addToWorld(SharedPointer<GameObject> & ipGameObject)
	{
		if (!ipGameObject.isNull())
			mGameObjectList.push_back(ipGameObject);
	}


	SharedPointer<GameObject> World::getNearestGameObject(Vector3D iPosiiton)
	{
		SharedPointer<GameObject> nearestGameObject = myEngine::GameObject::CreateGameObject(Vector3D(0, 0, 0)); //= mGameObjectList[0];
		float nearestDistance = (nearestGameObject->getPosition() - iPosiiton).length();

		assert(mGameObjectList.size() > 0);
		for (size_t i = 1; i < mGameObjectList.size(); i++)
		{
			if ((mGameObjectList[i]->getPosition() - iPosiiton).length() < nearestDistance)
				nearestGameObject.isEqual(mGameObjectList[i]);

			return nearestGameObject;
		}//end-for

	}//end-getNearestGameObject


	SharedPointer<GameObject> World::getNearestGameObjectWithPointer(Vector3D iPosiiton)
	{
		SharedPointer<GameObject> nearestGameObject = myEngine::GameObject::CreateGameObject(Vector3D(0, 0, 0)); //= mGameObjectList[0];
		float nearestDistance = (nearestGameObject->getPosition() - iPosiiton).length();

		assert(mGameObjectList.size() > 0);
		for (size_t i = 1; i < mGameObjectList.size(); i++)
		{
			if ((mGameObjectList[i]->getPosition() - iPosiiton).length() < nearestDistance)
				nearestGameObject.isEqual(mGameObjectList[i]);

			return nearestGameObject;
		}//end-for
		
	}//end-getNearestGameObjectWithPointer



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
		EngineController::GameEngine::getCollisionSystemController()->checkAndResponseCollision();
	}


	bool World::removeFromWorld(SharedPointer<GameObject>& i_gameObject)
	{
		//To-Do
		return true;
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

