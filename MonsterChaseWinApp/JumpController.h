#ifndef  __JUMPCONTROLLER_H
#define  __JUMPCONTROLLER_H

#include "IGameObjectController.h"
#include "GameObject.h"
#include "SharedPointer.h"

class JumpController :public myEngine::IGameObjectController
{
public:
	static myEngine::IGameObjectController*								getController();
	void																updateGameObject(myEngine::SharedPointer<myEngine::GameObject>&) override;
private:
	static JumpController* mJumpController;
	JumpController(){};
	JumpController(JumpController &){};
};
#endif