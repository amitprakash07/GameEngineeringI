#include "WanderController.h"
#include "random.h"
#include "Engine.h"

WanderController* WanderController::mWanderController = nullptr;

void WanderController::updateGameObject(myEngine::SharedPointer<myEngine::GameObject> &i_gameObject)//, unsigned int i_key)
{
	//i_gameObject->getPhysicsComponent()->setForce(myEngine::Vector3D::getUnitVector() * 10000);
	i_gameObject->setDirection(EngineController::GameEngine::getWorldController()->getPlayer()->getPosition() - i_gameObject->getPosition());
	i_gameObject->setPosition(i_gameObject->getPosition() + (myEngine::Vector3D(i_gameObject->getDirection()) * 0.1));
	i_gameObject->updateGameObject();
}

myEngine::IGameObjectController* WanderController::getController()
{
	if (mWanderController == nullptr)
	{
		mWanderController = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(WanderController))) WanderController() :
			new WanderController();		
	}
	return mWanderController;
}
