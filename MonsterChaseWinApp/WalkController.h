#ifndef __WALKCONTROLLER_H
#define __WALKCONTROLLER_H

#include "IGameObjectController.h"
#include "GameObject.h"
#include "SharedPointer.h"
#include "IMessageHandler.h"

enum _Direction
{
	NOMOVE =0,
	UP =  1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};
typedef _Direction Direction;

class WalkController :public myEngine::IMessageHandler ,public myEngine::IGameObjectController
{
public:
	void													updateGameObject(myEngine::SharedPointer<myEngine::GameObject>&) override;
	static myEngine::IGameObjectController*					getController();
	void													HandleMessage(myEngine::utils::StringHash & i_message, void * i_sender, void* i_messageData) override;


private:
	static WalkController*									mWalkController;
	Direction												mWalkDirection;
	WalkController(){};
	WalkController(WalkController&){};
};

#endif