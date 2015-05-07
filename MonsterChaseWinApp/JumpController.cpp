#include "JumpController.h"
#include "Vector3D.h"
#include "Engine.h"

JumpController* JumpController::mJumpController = nullptr;

void JumpController::updateGameObject(myEngine::SharedPointer<myEngine::GameObject> &i_gameObject)//, unsigned int i_key)
{
		myEngine::Vector3D olDirection = i_gameObject->getDirection();
		i_gameObject->setDirection(myEngine::Vector3D(0, 10, 0));
		i_gameObject->updateVelocity();
		i_gameObject->updatePosition();
		i_gameObject->setDirection(olDirection);
		i_gameObject->updateVelocity();
}


myEngine::IGameObjectController* JumpController::getController()
{
	if (mJumpController == nullptr)
	{		
		mJumpController = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(JumpController))) JumpController() :
			new JumpController();

		EngineController::GameEngine::registerGameObjectController(mJumpController, EngineController::GameEngine::getStringPool()->findString("Jump"));
		EngineController::GameEngine::registerGameObjectController(mJumpController, EngineController::GameEngine::getStringPool()->findString("jump"));
		EngineController::GameEngine::registerGameObjectController(mJumpController, EngineController::GameEngine::getStringPool()->findString("JumpController"));
		EngineController::GameEngine::registerGameObjectController(mJumpController, EngineController::GameEngine::getStringPool()->findString("jumpcontroller"));
	}
	return mJumpController;
}
