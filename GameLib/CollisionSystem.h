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
			static void									deleteCollisionSystem();
			void										addToCollisionsystem(SharedPointer<GameObject> &);
			bool										removeFromCollisionSystem(SharedPointer<GameObject> &);
			bool										isGameObjectCollidable(SharedPointer<GameObject> &, size_t &);
			void										updateCollisionSystem();
			
			
			
		private:
			static	CollisionSystem*					mCollisionSystem;
			std::vector<SharedPointer<GameObject>>		mCollidingEnabledGameObjectList;
			bool										isColliding(SharedPointer<GameObject>&, SharedPointer<GameObject>&, float &, float &, myEngine::typedefs::Axis&);
			void										responseToCollision(SharedPointer<GameObject>&, SharedPointer<GameObject>&, float &, float&, myEngine::typedefs::Axis&);
			bool										checkCollision();
			bool										toggleScreen;
			CollisionSystem();
			~CollisionSystem();

		};
	}
}

#endif