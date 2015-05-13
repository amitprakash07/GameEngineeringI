#include "NonPhysicsController.h"
#include "Engine.h"
#include "Vector3D.h"

NonPhysicsGameController* NonPhysicsGameController::mNPhyController = nullptr;

myEngine::IGameObjectController* NonPhysicsGameController::getController()
{
	if (mNPhyController == nullptr)
	{
		mNPhyController = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(NonPhysicsGameController))) NonPhysicsGameController() :
			new NonPhysicsGameController();
	}
	return mNPhyController;
}


void NonPhysicsGameController::updateGameObject(myEngine::SharedPointer<myEngine::GameObject> & i_gameObject)
{
	float force_factor = 10000;
	//i_gameObject->getPhysicsComponent()->setForce(myEngine::Vector3D(0.0f, 0.0f, 0.0f));
	switch (EngineController::GameEngine::getInputController()->getKeyPressed())
	{
	case 'W':
	case 'w':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->getPhysicsComponent()->setCurrentPosition(i_gameObject->getPhysicsComponent()->getCurrentPosition() + myEngine::Vector3D(0.0f, 5.0f, 0.0f));
		i_gameObject->updateGameObject();
		break;
	case 'A':
	case 'a':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->getPhysicsComponent()->setCurrentPosition(i_gameObject->getPhysicsComponent()->getCurrentPosition() + myEngine::Vector3D(-5.0f, 0.0f, 0.0f));
		i_gameObject->updateGameObject();
		break;
	case 'S':
	case 's':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->getPhysicsComponent()->setCurrentPosition(i_gameObject->getPhysicsComponent()->getCurrentPosition() + myEngine::Vector3D(0.0f, -5.0f, 0.0f));
		i_gameObject->updateGameObject();
		break;
	case 'd':
	case 'D':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->getPhysicsComponent()->setCurrentPosition(i_gameObject->getPhysicsComponent()->getCurrentPosition() + myEngine::Vector3D(5.0f, 0.0f, 0.0f));
		i_gameObject->updateGameObject();
		break;
	default:
		EngineController::GameEngine::getInputController()->updateInputManager();
		//i_gameObject->resetGameObject();
		break;
	}
}
