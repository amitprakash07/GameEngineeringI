#include "WalkController.h"
#include "Vector3D.h"
#include "Engine.h"

WalkController* WalkController::mWalkController = nullptr;

myEngine::IGameObjectController* WalkController::getController()
{
	if (mWalkController == nullptr)
	{
		mWalkController = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(WalkController))) WalkController() :
			new WalkController();
	}
	return mWalkController;
}


void WalkController::updateGameObject(myEngine::SharedPointer<myEngine::GameObject> &i_gameObject)//, unsigned int i_key)
{
	switch (EngineController::GameEngine::getInputController()->getKeyPressed())
	{
	case 'W':
	case 'w':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->resetGameObject();
		i_gameObject->getPhysicsComponent()->addForce(myEngine::Vector3D(0, 1000000000, 0));
		i_gameObject->updatePosition();
		break;
	case 'A':
	case 'a':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->resetGameObject();
		i_gameObject->getPhysicsComponent()->addForce(myEngine::Vector3D(-1000000000, 0, 0));
		i_gameObject->updatePosition();
		break;
	case 'S':
	case 's':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->resetGameObject();
		i_gameObject->getPhysicsComponent()->addForce(myEngine::Vector3D(0, -1000000000, 0));
		i_gameObject->updatePosition();
		break;
	case 'd':
	case 'D':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->resetGameObject();
		i_gameObject->getPhysicsComponent()->addForce(myEngine::Vector3D(1000000000, 0, 0));
		i_gameObject->updatePosition();
		break;
	default:
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->resetGameObject();

		break;
	}

}
