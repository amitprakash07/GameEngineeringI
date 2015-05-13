#ifndef __ICOLLISION_HANDLER_H
#define __ICOLLISION_HANDLER_H

#include "SharedPointer.h"
#include "GameObject.h"

namespace myEngine
{
	namespace Physics
	{
		class ICollisionHandler
		{
		public:
			ICollisionHandler();
			~ICollisionHandler();
			virtual void responseToCollision(SharedPointer<GameObject>&, myEngine::SharedPointer<myEngine::GameObject> &, float&) = 0;
		};
	}
}

#endif