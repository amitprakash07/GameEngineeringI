#ifndef __INPUT_CONTROLLER_H
#define __INPUT_CONTROLLER_H

#include "IMessageHandler.h"
//Helper class for utilizing/wrapping Cheesy functionality into game engine
//Singleton
namespace myEngine
{
	class InputController
	{
	public:
		static InputController*				getInputManager();
		static void							deleteInputController();
		unsigned int						getKeyPressed();
		unsigned int						getKeyDown();
		bool								isKeyPressed(unsigned int i_keyInput);
		bool								isKeyDown(unsigned int i_keyDown);
		void								updateInputManager();
		void								setKeyPress(unsigned int);
		void								setKeyDown(unsigned int);
		
	private:
		static InputController*				mInputController;
		unsigned int						mKeyDown;
		unsigned int						mKeyPressed;
		
		InputController();
		InputController(InputController&);
		~InputController();
	};


	namespace EngineInputController
	{
		void onKeyDown(unsigned int);
		void onKeyPressed(unsigned int);
	}

}

#endif