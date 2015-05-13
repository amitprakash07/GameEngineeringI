#ifndef __MESSAGING_SYSTEM_H
#define __MESSAGING_SYSTEM_H

#include "IMessageHandler.h"
#include "HashedString.h"
#include <map>
#include <vector>
#include <assert.h>


namespace myEngine
{
	class MessagingSystem
	{
	public:
		static MessagingSystem*	getMessagingSystem();
		static void				deleteMessagingSystem();
		void addMessageHandler(myEngine::utils::StringHash &, IMessageHandler *, myEngine::typedefs::Priority);
		bool removeMessageHandler(myEngine::utils::StringHash&, IMessageHandler*);
		void sendMessage(myEngine::utils::StringHash &, void *, void* message_data = nullptr);
		

	private:
		static MessagingSystem * mMessagingSystem;
		std::map< myEngine::utils::StringHash, std::vector<myEngine::MessageHandle>> 	m_MessageHandlers;
		MessagingSystem();
		~MessagingSystem();
	};
}


#endif