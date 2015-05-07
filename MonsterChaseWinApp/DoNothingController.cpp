#include "DoNothingController.h"
#include "Engine.h"

StaticController* StaticController::mStaticController = nullptr;

myEngine::IGameObjectController* StaticController::getController()
{
	if (mStaticController == nullptr)
	{
		mStaticController = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(StaticController))) StaticController() :
			new StaticController();
	}
	return mStaticController;
}

void StaticController::updateGameObject(myEngine::SharedPointer<myEngine::GameObject> &i_gameObject)//, unsigned int i_key)
{
		//Do nothing
}