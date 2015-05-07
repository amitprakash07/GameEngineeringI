#ifndef __NON_PHYSICS_CONTROLLER_H
#define __NON_PHYSICS_CONTROLLER_H

#include "IGameObjectController.h"
#include "SharedPointer.h"
#include "GameObject.h"

class NonPhysicsGameController :public myEngine::IGameObjectController
{
public:
	static myEngine::IGameObjectController*									getController();
	void																	updateGameObject(myEngine::SharedPointer<myEngine::GameObject>&) override;
private:
	static NonPhysicsGameController*										mNPhyController;
	NonPhysicsGameController(){};
	NonPhysicsGameController(NonPhysicsGameController &){};
};

#endif