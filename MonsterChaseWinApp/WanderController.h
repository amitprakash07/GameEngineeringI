#ifndef __WANDERCONTROLLER_H
#define __WANDERCONTROLLER_H

#include "IGameObjectController.h"
#include "GameObject.h"
#include "SharedPointer.h"

class WanderController :public myEngine::IGameObjectController
{
public:
	void													updateGameObject(myEngine::SharedPointer<myEngine::GameObject>&) override;
	static myEngine::IGameObjectController*					getController();
private:
	static WanderController*								mWanderController;
	WanderController(){};
	WanderController(WanderController&){};
};

#endif