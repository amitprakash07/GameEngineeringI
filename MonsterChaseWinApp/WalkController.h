#ifndef __WALKCONTROLLER_H
#define __WALKCONTROLLER_H

#include "IGameObjectController.h"
#include "GameObject.h"
#include "SharedPointer.h"


class WalkController :public myEngine::IGameObjectController
{
public:
	void													updateGameObject(myEngine::SharedPointer<myEngine::GameObject>&) override;
	static myEngine::IGameObjectController*					getController();

private:
	static WalkController*									mWalkController;
	WalkController(){};
	WalkController(WalkController&){};
};

#endif