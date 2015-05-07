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
	switch (EngineController::GameEngine::getInputController()->getKeyPressed())
	{
	case 'W':
	case 'w':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->setPosition(i_gameObject->getPosition() + myEngine::Vector3D(0, 5, 0));
		break;
	case 'A':
	case 'a':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->setPosition(i_gameObject->getPosition() + myEngine::Vector3D(-5, 0, 0));
		break;
	case 'S':
	case 's':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->setPosition(i_gameObject->getPosition() + myEngine::Vector3D(0, -5, 0));
		break;
	case 'd':
	case 'D':
		EngineController::GameEngine::getInputController()->updateInputManager();
		i_gameObject->setPosition(i_gameObject->getPosition() + myEngine::Vector3D(5, 0, 0));
		break;
	default:
		EngineController::GameEngine::getInputController()->updateInputManager();
//		i_gameObject->resetGameObject();

		break;
	}
}
