#include "WanderController.h"
#include "random.h"
#include "Engine.h"

WanderController* WanderController::mWanderController = nullptr;

void WanderController::updateGameObject(myEngine::SharedPointer<myEngine::GameObject> &i_gameObject)//, unsigned int i_key)
{
	i_gameObject->setPosition(myEngine::Vector3D(myEngine::Vector3D(myMath::RandInRange<float>(50, 2 * 50), myMath::RandInRange<float>(50, 2 * 50), 0)));
}

myEngine::IGameObjectController* WanderController::getController()
{
	if (mWanderController == nullptr)
	{
		mWanderController = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(WanderController))) WanderController() :
			new WanderController();

		EngineController::GameEngine::registerGameObjectController(mWanderController, EngineController::GameEngine::getStringPool()->findString("Wander"));
		EngineController::GameEngine::registerGameObjectController(mWanderController, EngineController::GameEngine::getStringPool()->findString("wander"));
		EngineController::GameEngine::registerGameObjectController(mWanderController, EngineController::GameEngine::getStringPool()->findString("WanderController"));
		EngineController::GameEngine::registerGameObjectController(mWanderController, EngineController::GameEngine::getStringPool()->findString("wandercontroller"));
	}
	return mWanderController;
}
