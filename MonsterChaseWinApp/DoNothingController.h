#ifndef __DO_NOTHING_CONTROLLER_H
#define __DO_NOTHING_CONTROLLER_H

#include "IGameObjectController.h"
#include "SharedPointer.h"
#include "GameObject.h"

class StaticController : public myEngine::IGameObjectController
{
public:
	static myEngine::IGameObjectController* getController();
	void updateGameObject(myEngine::SharedPointer<myEngine::GameObject>&) override;

private:
	static StaticController* mStaticController;
	StaticController(){};
	StaticController(StaticController&){};
};

#endif