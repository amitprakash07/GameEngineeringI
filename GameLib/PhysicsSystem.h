#ifndef __PHYSICS_SYSTEM_H
#define __PHYSICS_SYSTEM_H

#include <vector>
#include "GameObject.h"
#include "SharedPointer.h"
#include "FrameTime.h"

//Singleton
namespace myEngine
{
	namespace Physics
	{
		class PhysicsSystem
		{
		public:
			static PhysicsSystem*								getPhysicsSystem();
			SharedPointer<myEngine::Timing::Clock>				getPhysicsClock();
			void												addToPhysicsSystem(SharedPointer<GameObject> &);
			void												removeFromPhysicsSystem(SharedPointer<GameObject> &);
			bool												isGameObjectPhysicsEnabled(SharedPointer<GameObject>&, size_t &);
			void												updatePhysicsSystem();
		private:
			static PhysicsSystem*								mPhysicsSystem;
			std::vector<SharedPointer<GameObject>>				mPhysicsGameObjectList;
			SharedPointer<myEngine::Timing::Clock>				physicsClock;
			PhysicsSystem();
		};
	}//namespace Physics
}//namespcae myEngine

#endif