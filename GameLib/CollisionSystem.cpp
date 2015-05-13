#include "CollisionSystem.h"
#include "Engine.h"
#include "FloatNumbers.h"

namespace myEngine
{
	namespace Physics
	{
		CollisionSystem * CollisionSystem::mCollisionSystem = nullptr;

		
		//retuns instance of collision system
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



		void CollisionSystem::deleteCollisionSystem()
		{
			MessagedAssert(mCollisionSystem, "Collision sytem is either deleted or not created");
			EngineController::GameEngine::isEngineInitialized() ?
				EngineController::GameEngine::getMemoryManager()->__free(mCollisionSystem) :
				delete mCollisionSystem;
		}


		CollisionSystem::~CollisionSystem()
		{
			mCollidingEnabledGameObjectList.clear();
		}
		
		
		
		CollisionSystem::CollisionSystem()
		{
			mCollidingEnabledGameObjectList.reserve(200);
			toggleScreen = false;
		}
		
		
		
		//Add collidable object to Collision System
		void CollisionSystem::addToCollisionsystem(SharedPointer<GameObject>& i_GameObject)
		{
			size_t stubIndex;
			assert(!i_GameObject.isNull());
			if (i_GameObject->isCollidable() && !isGameObjectCollidable(i_GameObject,stubIndex))
				mCollidingEnabledGameObjectList.push_back(i_GameObject);
		}


		//Remove from Collision system
		bool CollisionSystem::removeFromCollisionSystem(SharedPointer<GameObject>& i_GameObject)
		{
			size_t objectIndex = 0x0f0f0f0f;
			if (!i_GameObject.isNull() && isGameObjectCollidable(i_GameObject, objectIndex) && (objectIndex != 0x0f0f0f0f))
			{
				mCollidingEnabledGameObjectList.erase(mCollidingEnabledGameObjectList.begin() + objectIndex);
				return true;
			}		
			return false;
		}


		//Check object present in collision system and if found returns the index of it in the list
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



		//Checks two gameObjects are colliding or not
		bool CollisionSystem::isColliding(SharedPointer<GameObject>& i_GameObject_A, SharedPointer<GameObject>& i_GameObject_B, float& o_collisionTime, float& o_separationTime, myEngine::typedefs::Axis &o_CollisionAxis)
		{
			//To-Do - Done but need testing
			assert(!i_GameObject_A.isNull() && !i_GameObject_B.isNull());
			float collisionTimeA = 0.0f;
			float collisionTimeB = 0.0f;
			float separationTimeA = 0.0f;
			float separationTimeB = 0.0f;
			myEngine::typedefs::Axis collisionAxisA;
			myEngine::typedefs::Axis collisionAxisB;

			if (i_GameObject_A->separationAxisTest(i_GameObject_B, collisionTimeA, separationTimeA, collisionAxisA) 
				&& i_GameObject_B->separationAxisTest(i_GameObject_A, collisionTimeB,separationTimeB,collisionAxisB))
			{
				
				if (collisionTimeA < collisionTimeB)
				{
					o_collisionTime = collisionTimeA;
					o_CollisionAxis = collisionAxisA;
				}
				else
				{
					o_collisionTime = collisionTimeB;
					o_CollisionAxis = collisionAxisB;
				}

				o_separationTime = separationTimeA < separationTimeB ? separationTimeA : separationTimeB;

				float deltaTime = EngineController::GameEngine::getEngineClock()->getdeltaTime();
				
				//Checking if collision Time or separation time is out of the frame
				//if (o_collisionTime > deltaTime || o_separationTime > deltaTime)
					//return false;
				//Checking if collision 
				//if (o_collisionTime < deltaTime)
				//	return false;
				if (o_collisionTime > o_separationTime)
					myEngine::swap(o_collisionTime, o_separationTime);
				
				return true;
			}
			
			return false;
		}



		//updates the collision system until the collsion resolves
		void CollisionSystem::updateCollisionSystem()
		{
			bool collision = true;
			while (collision)
				collision = collision && checkCollision();
		}




		//Checks collsion between all objects
		bool CollisionSystem::checkCollision()
		{
			float collisionTime = 0.0f;
			float separationTime = 0.0f;
			bool noCollision = true;
			unsigned __int16 gameObjectAIndex = 0;
			unsigned __int16 gameObjectBIndex = 0;
			myEngine::typedefs::Axis collisionAxis;
			float firstCollisionTimeInSystem = 1.0f;
			float firstSeparationTimeInSystem = 1.0f;
			myEngine::typedefs::Axis finalCollidingAxis = myEngine::typedefs::XAxis;
			unsigned __int16 i = 0, j = 0;
			
			for (i= 0; i < mCollidingEnabledGameObjectList.size(); i++)
			{
				for (j = i + 1; j < mCollidingEnabledGameObjectList.size(); j++)
				{
					if (isColliding(mCollidingEnabledGameObjectList[i], mCollidingEnabledGameObjectList[j], collisionTime, separationTime, collisionAxis))
					{
						if (collisionTime <= firstCollisionTimeInSystem)
						{
							firstCollisionTimeInSystem = collisionTime;
							finalCollidingAxis = collisionAxis;
							gameObjectAIndex = i;
							gameObjectBIndex = j;
						}

						if (separationTime <= firstSeparationTimeInSystem)
							firstCollisionTimeInSystem = separationTime;
						noCollision = false;
					}
						
				}
			}

			if (!noCollision)
			{
				responseToCollision(
					mCollidingEnabledGameObjectList[gameObjectAIndex], 
					mCollidingEnabledGameObjectList[gameObjectBIndex],
					firstCollisionTimeInSystem, 
					firstSeparationTimeInSystem,
					finalCollidingAxis);
				noCollision = true;
				return true;
			}
				
			return false;;
		}




		//To-Do Complete- Making it a stub
		void CollisionSystem::responseToCollision(SharedPointer<GameObject>& i_GameObjectA, SharedPointer<GameObject>& i_GameObjectB, float & i_collisionTime, float &i_separationTime, myEngine::typedefs::Axis &i_axis)
		{
			if (!EngineController::GameEngine::gameOver)
			{

				for (unsigned __int16 i = 0; i < mCollidingEnabledGameObjectList.size(); i++)
					mCollidingEnabledGameObjectList[i]->updateGameObject(i_collisionTime);

				i_GameObjectA->getCollider()->getCollisionHandler()->responseToCollision(i_GameObjectA, i_GameObjectB, i_collisionTime);
			}
			
		}
		
	}
}