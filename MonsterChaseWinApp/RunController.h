#ifndef __RUNCONTROLLER_H
#define __RUNCONTROLLER_H

#include "IGameObjectController.h"
#include "GameObject.h"
#include "SharedPointer.h"

class RunController : public myEngine::IGameObjectController
{
public:
	void										updateGameObject(myEngine::SharedPointer<myEngine::GameObject>&) override;
	static myEngine::IGameObjectController*		getController();
private:
	static RunController*						mRunController;
	RunController(){};
	RunController(RunController&){};
};

#endif