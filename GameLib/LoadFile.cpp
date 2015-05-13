#include "LoadFile.h"
#include "Engine.h"

namespace myEngine
{
	void LoadFile::processFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes)
	{
		if (EngineController::GameEngine::isEngineInitialized())
		{
			char * buffer = reinterpret_cast<char*>(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(char)* (i_BufferBytes + 1)));
			memcpy(buffer, i_pBuffer, i_BufferBytes);
			buffer[i_BufferBytes] = 0;
			EngineController::GameEngine::getWorldController()->createGameObjects(buffer);
			EngineController::GameEngine::getMessagsingSystem()->sendMessage(myEngine::utils::StringHash("GameObjectCreated"), this);
			EngineController::GameEngine::getMemoryManager()->__free(buffer);
			buffer = nullptr;
		}
	}
}