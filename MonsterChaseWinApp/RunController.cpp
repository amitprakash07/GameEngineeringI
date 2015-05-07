#include "RunController.h"
#include "Engine.h"


RunController* RunController::mRunController = nullptr;

void RunController::updateGameObject(myEngine::SharedPointer<myEngine::GameObject> &i_gameObject)//, unsigned int i_key)
{
	float tempSpeed = i_gameObject->getSpeed();
	i_gameObject->setSpeed(i_gameObject->getSpeed() + 5);
	i_gameObject->updateVelocity();
	i_gameObject->updatePosition();
	i_gameObject->setSpeed(tempSpeed);
	i_gameObject->updateVelocity();
}


myEngine::IGameObjectController* RunController::getController()
{
	if (mRunController == nullptr)
	{
		mRunController = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(RunController))) RunController() :
			new RunController();

		EngineController::GameEngine::registerGameObjectController(mRunController, EngineController::GameEngine::getStringPool()->findString("Run"));
		EngineController::GameEngine::registerGameObjectController(mRunController, EngineController::GameEngine::getStringPool()->findString("run"));
		EngineController::GameEngine::registerGameObjectController(mRunController, EngineController::GameEngine::getStringPool()->findString("RunController"));
		EngineController::GameEngine::registerGameObjectController(mRunController, EngineController::GameEngine::getStringPool()->findString("runcontroller"));
	}
	return mRunController;
}