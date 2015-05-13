#ifndef __DEFAULT_COLLISON_HANDLER
#define __DEFAULT_COLLISON_HANDLER

#include "ICollisionHandler.h"

namespace myEngine
{
	namespace Physics
	{
		class GenereicCollisionHandler: public myEngine::Physics::ICollisionHandler
		{
		public:
			GenereicCollisionHandler();
			void responseToCollision(myEngine::SharedPointer<myEngine::GameObject> &, myEngine::SharedPointer<myEngine::GameObject> &, float&) override;
		};
	}
}

#endif