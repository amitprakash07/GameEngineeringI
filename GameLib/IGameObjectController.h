#ifndef __IGAMEOBJECTCONTROLLER__H
#define __IGAMEOBJECTCONTROLLER__H

#include "Vector3D.h"
#include "SharedPointer.h"

namespace myEngine
{
	class GameObject;

	class IGameObjectController
	{
	public:
		IGameObjectController();
		~IGameObjectController();
		virtual void updateGameObject(myEngine::SharedPointer<GameObject>&) = 0;//, unsigned int) = 0;
	};
}

#endif
