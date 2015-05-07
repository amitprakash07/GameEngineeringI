#include "CollisionSystem.h"
#include "Engine.h"

namespace myEngine
{
	namespace Physics
	{
		CollisionSystem * CollisionSystem::mCollisionSystem = nullptr;

		CollisionSystem* CollisionSystem::getCollisionSystem()
		{
			if (mCollisionSystem == nullptr)
			{
				if (EngineController::GameEngine::isEngineInitialized())
					mCollisionSystem = new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(CollisionSystem))) CollisionSystem();
				else
					mCollisionSystem = new CollisionSystem();
			}

			return mCollisionSystem;			
		}

		CollisionSystem::CollisionSystem()
		{
			mCollidingEnabledGameObjectList.reserve(200);
			toggleScreen = false;
		}
		
		void CollisionSystem::addToCollisionsystem(SharedPointer<GameObject>& i_GameObject)
		{
			size_t stubIndex;
			assert(!i_GameObject.isNull());
			if (i_GameObject->isCollidable() && !isGameObjectCollidable(i_GameObject,stubIndex))
				mCollidingEnabledGameObjectList.push_back(i_GameObject);
		}

		void CollisionSystem::removeFromCollisionSystem(SharedPointer<GameObject>& i_GameObject)
		{
			size_t objectIndex;
			if (!i_GameObject.isNull() && isGameObjectCollidable(i_GameObject, objectIndex))
				mCollidingEnabledGameObjectList.erase(mCollidingEnabledGameObjectList.begin() + objectIndex);
		}

		bool CollisionSystem::isGameObjectCollidable(SharedPointer<GameObject>& i_gameObject, size_t& o_objectIndex)
		{
			assert(!i_gameObject.isNull());

			for (unsigned __int16 i = 0; i < mCollidingEnabledGameObjectList.size(); i++)
			{
				if (mCollidingEnabledGameObjectList[i].isEqual(i_gameObject))
				{
					o_objectIndex = i;
					return true;
				}
			}

			return false;
		}


		bool CollisionSystem::isColliding(SharedPointer<GameObject>& i_GameObject_A, SharedPointer<GameObject>& i_GameObject_B, float& o_collisionTime, float& o_separationTime)
		{
			//To-Do - Done but need testing
			assert(!i_GameObject_A.isNull() && !i_GameObject_B.isNull());
			float collisionTimeA = 0.0f;
			float collisionTimeB = 0.0f;
			float separationTimeA = 0.0f;
			float separationTimeB = 0.0f;

			if (i_GameObject_A->separationAxisTest(i_GameObject_B, collisionTimeA, separationTimeA) 
				&& i_GameObject_B->separationAxisTest(i_GameObject_A, collisionTimeB,separationTimeB))
			{
				o_collisionTime = collisionTimeA < collisionTimeB ? collisionTimeA : collisionTimeB;
				o_separationTime = separationTimeA > separationTimeB ? separationTimeA : separationTimeB;
				return true;
			}
			
			return false;
		}

		//To Do - Almost Done but need Testing
		void CollisionSystem::checkAndResponseCollision()
		{
			float collisionTime;
			float separationTime;

			for (unsigned __int16 i= 0; i < mCollidingEnabledGameObjectList.size(); i++)
			{
				for (unsigned __int16 j = i; j < mCollidingEnabledGameObjectList.size(); j++)
				{
					if (isColliding(mCollidingEnabledGameObjectList[i], mCollidingEnabledGameObjectList[j], collisionTime, separationTime))
						responseToCollision(mCollidingEnabledGameObjectList[i], mCollidingEnabledGameObjectList[j], collisionTime, separationTime);
				}
			}
		}


		//To-Do Complete- Making it a stub
		void CollisionSystem::responseToCollision(SharedPointer<GameObject>&, SharedPointer<GameObject>&, float &, float&)
		{
			myEngine::typedefs::RGBA mColor1 = { 255.0f, 255.0f, 255.0f, 0.0f };
			myEngine::typedefs::RGBA mColor2 = { 50.0f, 50.0f, 255.0f, 0.0f };
			//Stub
			switch (toggleScreen)
			{
			case true:
				EngineController::GameEngine::getWorldController()->setWindowColor(mColor1);
				toggleScreen = false;
				break;
			case false:
				EngineController::GameEngine::getWorldController()->setWindowColor(mColor2);
				toggleScreen = true;
				break;
			}
		}




	}
}