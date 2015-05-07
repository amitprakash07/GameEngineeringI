#ifndef __COLLISION_SYSTEM_H
#define __COLLISION_SYSTEM_H

#include "SharedPointer.h"
#include "GameObject.h"

namespace myEngine
{
	namespace Physics
	{
		class CollisionSystem
		{
		public:
			static CollisionSystem *					getCollisionSystem();
			void										addToCollisionsystem(SharedPointer<GameObject> &);
			void										removeFromCollisionSystem(SharedPointer<GameObject> &);
			bool										isGameObjectCollidable(SharedPointer<GameObject> &, size_t &);
			void										checkAndResponseCollision();
			
		private:
			static	CollisionSystem*					mCollisionSystem;
			std::vector<SharedPointer<GameObject>>		mCollidingEnabledGameObjectList;
			bool										isColliding(SharedPointer<GameObject>&, SharedPointer<GameObject>&, float &, float &);
			void										responseToCollision(SharedPointer<GameObject>&, SharedPointer<GameObject>&, float &, float&);
			bool										toggleScreen;
			CollisionSystem();

		};
	}
}

#endif