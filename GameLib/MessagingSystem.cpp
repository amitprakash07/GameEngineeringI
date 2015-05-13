#include "MessagingSystem.h"
#include "Engine.h"
#include <algorithm>

namespace myEngine
{
	MessagingSystem* MessagingSystem::mMessagingSystem = nullptr;	
	
	MessagingSystem* MessagingSystem::getMessagingSystem()
	{
		if (mMessagingSystem == nullptr)
		{
			mMessagingSystem = EngineController::GameEngine::isEngineInitialized() ?
				new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(MessagingSystem))) MessagingSystem() :
				new MessagingSystem();
		}

		return mMessagingSystem;
	}

	void MessagingSystem::deleteMessagingSystem()
	{
		MessagedAssert(mMessagingSystem != nullptr, "Either Messaging system is not instantiated or it has been already deleted");
		EngineController::GameEngine::isEngineInitialized() ?
			EngineController::GameEngine::getMemoryManager()->__free(mMessagingSystem) :
			delete mMessagingSystem;
	}


	MessagingSystem::MessagingSystem()
	{
		//Nothing Required
	}

	MessagingSystem::~MessagingSystem()
	{
		//Nothing Required
	}

	void MessagingSystem::addMessageHandler(myEngine::utils::StringHash & i_message, IMessageHandler* i_pMessageHandler, myEngine::typedefs::Priority i_priority)
	{
		assert(i_pMessageHandler != nullptr);
		//assert(!i_message.isNil());
		MessageHandle temp { i_pMessageHandler, i_priority };
		m_MessageHandlers[i_message].push_back(temp);
		std::vector<MessageHandle> tempList = m_MessageHandlers[i_message];
		std::sort(tempList.begin(), tempList.end());
	}

	
	void MessagingSystem::sendMessage(myEngine::utils::StringHash & i_message, void * i_messageSender, void* message_data)
	{
		assert(i_messageSender);
		//assert(!i_message.isNil());
		std::vector<MessageHandle> tempList = m_MessageHandlers[i_message];
		unsigned __int16 handleCount = tempList.size();
		for (unsigned __int16 i = 0; i < handleCount; i++)
		{
			tempList[i].mHandler->HandleMessage(i_message,  i_messageSender, message_data);
		}
	}

	bool MessagingSystem::removeMessageHandler(myEngine::utils::StringHash & i_message, IMessageHandler* i_messageHandler)
	{
		MessagedAssert(i_messageHandler != nullptr, "Null Message Handler - Removal not possible");
		std::vector<myEngine::MessageHandle> temp = m_MessageHandlers[i_message];
		for (unsigned __int16 i = 0; i < temp.size(); i++)
		{
			if (temp[i].mHandler = i_messageHandler)
			{
				temp.erase(temp.begin() + i);
				return true;
			}
		}
		return false;
	}


}

