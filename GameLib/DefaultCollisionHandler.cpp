#include "DefaultCollisionHandler.h"
#include "Engine.h"
#include "random.h"

namespace myEngine
{
	namespace Physics
	{
		GenereicCollisionHandler::GenereicCollisionHandler()
		{
		
		}

		void GenereicCollisionHandler::responseToCollision(myEngine::SharedPointer<myEngine::GameObject> &i_gameObjectA, myEngine::SharedPointer<myEngine::GameObject> &  i_gameObjectB,float &i_collisionTime)
		{
			if ((myEngine::utils::StringHash(i_gameObjectA->getType()) == myEngine::utils::StringHash("Player"))
				&& (myEngine::utils::StringHash(i_gameObjectB->getType()) == myEngine::utils::StringHash("Monster")))
			{
				EngineController::GameEngine::getMessagsingSystem()->sendMessage(myEngine::utils::StringHash("Player Died"), this);
			}

			
			
			if (!EngineController::GameEngine::gameOver)
			{
				if ((myEngine::utils::StringHash(i_gameObjectA->getType()) == myEngine::utils::StringHash("Monster"))
					&& (myEngine::utils::StringHash(i_gameObjectB->getType()) == myEngine::utils::StringHash("Monster")))
				{
					i_gameObjectA->setDirection(i_gameObjectA->getVelocity().getNormalizeVector());
					i_gameObjectA->getDirection().negate();

					i_gameObjectB->setDirection(i_gameObjectB->getVelocity().getNormalizeVector());
					i_gameObjectB->getDirection().negate();

					i_gameObjectA->setPosition(i_gameObjectA->getPosition() + (myEngine::Vector3D(i_gameObjectA->getDirection()) * 1));
					i_gameObjectB->setPosition(i_gameObjectB->getPosition() + (myEngine::Vector3D(i_gameObjectB->getDirection()) * 1));

					i_gameObjectA->updateGameObject();
					i_gameObjectB->updateGameObject();
				}
			}

		}
	}
}