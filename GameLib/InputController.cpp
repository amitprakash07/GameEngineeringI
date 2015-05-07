#include "InputController.h"
#include "Cheesy.h"
#include "Engine.h"

namespace myEngine
{

	InputController* InputController::mInputController = nullptr;


	InputController* InputController::getInputManager()
	{
		if (mInputController == nullptr)
		{
			mInputController = EngineController::GameEngine::isEngineInitialized() ?
				new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(InputController))) InputController() :
				new InputController();
		}
		return mInputController;
	}


	InputController::InputController()
	{
		Cheesy::setKeyDownCallback(myEngine::EngineInputController::onKeyDown);
		Cheesy::setKeyPressCallback(myEngine::EngineInputController::onKeyPressed);
	}

	void InputController::setKeyDown(unsigned int i_key)
	{
		mKeyDown = i_key;
	}

	void InputController::setKeyPress(unsigned int i_key)
	{
		mKeyPressed = i_key;
	}	

	
	//generic function to check which key is down
	bool InputController::isKeyDown(unsigned int i_key)
	{
		return (mKeyDown == i_key);
	}

	//generic function to check which key is pressed
	bool InputController::isKeyPressed(unsigned int i_key)
	{
		return (mKeyPressed == i_key);
	}


	//returning key pressed
	unsigned int InputController::getKeyPressed()
	{
		return mKeyPressed;
	}


	//returning key down
	unsigned int InputController::getKeyDown()
	{
		return mKeyDown;
	}


	//resetting the keyboard input values
	void InputController::updateInputManager()
	{
		mKeyDown = 0;
		mKeyPressed = 0;
	}



	namespace EngineInputController
	{
		//Private - wrapping up with Cheesy helper function
		void onKeyDown(unsigned int i_key)
		{
			EngineController::GameEngine::getInputController()->setKeyDown(i_key);
		}


		//Private - wrapping up with Cheesy helper function
		void onKeyPressed(unsigned int i_key)
		{
			EngineController::GameEngine::getInputController()->setKeyPress(i_key);
		}
	}
	

}