#include "PhysicsSystem.h"
#include "Engine.h"

namespace myEngine
{
	namespace Physics
	{
		PhysicsSystem*										PhysicsSystem::mPhysicsSystem = nullptr;
		SharedPointer<myEngine::Timing::Clock>				physicsClock;
		
		PhysicsSystem::PhysicsSystem()
		{
			mPhysicsGameObjectList.reserve(200);
			if (!EngineController::GameEngine::isEngineInitialized())
				EngineController::GameEngine::startGameEngine();
			physicsClock = EngineController::GameEngine::getEngineClock();
		}

		PhysicsSystem* PhysicsSystem::getPhysicsSystem()
		{
			if (mPhysicsSystem == nullptr)
			{
				if (EngineController::GameEngine::isEngineInitialized())
					mPhysicsSystem = new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(PhysicsSystem))) PhysicsSystem();
				else
					mPhysicsSystem = new PhysicsSystem();
			}
			return mPhysicsSystem;
		}

		void PhysicsSystem::deletePhysicsSystem()
		{
			MessagedAssert(mPhysicsSystem != nullptr, "Physics System is either not instantiated or had been deleted");
			EngineController::GameEngine::isEngineInitialized() ?
				EngineController::GameEngine::getMemoryManager()->__free(mPhysicsSystem) :
				delete mPhysicsSystem;
		}


		PhysicsSystem::~PhysicsSystem()
		{	
			while (mPhysicsGameObjectList.size() != 0)
			{
				mPhysicsGameObjectList.erase(mPhysicsGameObjectList.begin());
			}

			if (!physicsClock.isNull())
				physicsClock.deleteObject();
		}


		void PhysicsSystem::addToPhysicsSystem(SharedPointer<GameObject> & i_gameObject)
		{
			size_t stubIndex;
			assert(!i_gameObject.isNull());
			if (i_gameObject->isPhysicsObject() && !isGameObjectPhysicsEnabled(i_gameObject,stubIndex))
				mPhysicsGameObjectList.push_back(i_gameObject);
		}

		bool PhysicsSystem::removeFromPhysicsSystem(SharedPointer<GameObject> & i_gameObject)
		{
			size_t objectIndex = 0x0f0f0f0f;
			if (!i_gameObject.isNull() && isGameObjectPhysicsEnabled(i_gameObject, objectIndex) && (objectIndex != 0x0f0f0f0f))
			{
				mPhysicsGameObjectList.erase(mPhysicsGameObjectList.begin() + objectIndex);
				return true;
			}
			return false;
		}

		bool PhysicsSystem::isGameObjectPhysicsEnabled(SharedPointer<GameObject> &i_gameObject, size_t & o_index)
		{
			assert(!i_gameObject.isNull());
			for (unsigned __int16 i = 0; i < mPhysicsGameObjectList.size(); i++)
			{
				if (mPhysicsGameObjectList[i].isEqual(i_gameObject))
				{
					o_index = i;
					return true;
				}
			}
			return false;
		}

		void PhysicsSystem::updatePhysicsSystem()
		{
			for (unsigned __int16 i = 0; i < mPhysicsGameObjectList.size(); i++)
			{
				mPhysicsGameObjectList[i]->getGameObjectController()->updateGameObject(mPhysicsGameObjectList[i]);
			}
		}

		SharedPointer<myEngine::Timing::Clock> PhysicsSystem::getPhysicsClock()
		{
			assert(!physicsClock.isNull());
			return physicsClock;				
		}

	}//namespace Physics
}//namespace myEngine