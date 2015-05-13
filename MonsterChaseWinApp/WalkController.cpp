#include "WalkController.h"
#include "Vector3D.h"
#include "Engine.h"
#include <iostream>
#include <windows.h>


WalkController* WalkController::mWalkController = nullptr;

myEngine::IGameObjectController* WalkController::getController()
{
	if (mWalkController == nullptr)
	{
		mWalkController = EngineController::GameEngine::isEngineInitialized() ?
			new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(WalkController))) WalkController() :
			new WalkController();

		EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("Key Down"), mWalkController, myEngine::typedefs::HIGH);
		EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("Key Pressed"), mWalkController, myEngine::typedefs::HIGH);
		EngineController::GameEngine::getMessagsingSystem()->addMessageHandler(myEngine::utils::StringHash("Player Died"), mWalkController, myEngine::typedefs::HIGH);
	}
	return mWalkController;
}



void WalkController::HandleMessage(myEngine::utils::StringHash & i_message, void * i_sender, void* i_messageData)
{
	if (myEngine::utils::StringHash(i_message) == myEngine::utils::StringHash("Key Down"))
	{
		unsigned int *key = reinterpret_cast<unsigned int*>(i_messageData);
		switch (*key)
		{
		case 'W':
		case 'w':
			mWalkDirection = UP;
			break;
		case 'A':
		case 'a':
			mWalkDirection = LEFT;
			break;
		case 'S':
		case 's':
			mWalkDirection = DOWN;
			break;			
		case 'd':
		case 'D':
			mWalkDirection = RIGHT;
			break;
		default:
			mWalkDirection = NOMOVE;
			break;
		}
	}

	if (myEngine::utils::StringHash(i_message) == myEngine::utils::StringHash("Player Died"))
	{
		bool bQuit = false;
		//Cheesy::Service(bQuit);

		if (!bQuit)
		{
			// We must call Cheesy::BeginFrame() when we want to start making draw requests
			if (Cheesy::BeginFrame(myEngine::getAsCheesyRGBA(EngineController::GameEngine::getWorldController()->getWindowColor())))
			{

				Cheesy::Text::BeginText();
				Cheesy::Text::DrawText("GameOver", EngineController::GameEngine::SSTextUL, EngineController::GameEngine::SSTextLR, EngineController::GameEngine::White);
				Cheesy::Text::EndText();
				// We must call Cheesy::EndFrame() when we're doing making draw requests.
				Cheesy::EndFrame();
				Sleep(1000 * 2);
			}
		}
		
	}
}



void WalkController::updateGameObject(myEngine::SharedPointer<myEngine::GameObject> &i_gameObject)//, unsigned int i_key)
{
	switch (mWalkDirection)
	{
	case UP:
		i_gameObject->getPhysicsComponent()->setCurrentPosition(i_gameObject->getPhysicsComponent()->getCurrentPosition() + myEngine::Vector3D(0.0f, 50.0f, 0.0f));
		i_gameObject->updateGameObject();
		break;
	case DOWN:
		i_gameObject->getPhysicsComponent()->setCurrentPosition(i_gameObject->getPhysicsComponent()->getCurrentPosition() + myEngine::Vector3D(0.0f, -50.0f, 0.0f));
		i_gameObject->updateGameObject();
		break;
	case LEFT:
		i_gameObject->getPhysicsComponent()->setCurrentPosition(i_gameObject->getPhysicsComponent()->getCurrentPosition() + myEngine::Vector3D(-50.0f, 0.0f, 0.0f));
		i_gameObject->updateGameObject();
		break;
	case RIGHT:
		i_gameObject->getPhysicsComponent()->setCurrentPosition(i_gameObject->getPhysicsComponent()->getCurrentPosition() + myEngine::Vector3D(50.0f, 0.0f, 0.0f));
		i_gameObject->updateGameObject();
		break;
	default:
		break;
	}
	mWalkDirection = NOMOVE;
}
