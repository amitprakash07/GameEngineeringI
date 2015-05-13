#ifndef __I_MESSAGE_HANDLER_H
#define __I_MESSAGE_HANDLER_H

#include "HashedString.h"
#include "additionaltypes.h"
#include "_assert.h"

namespace myEngine
{	
	class IMessageHandler
	{
	public: 
		virtual void HandleMessage(myEngine::utils::StringHash &, void *i_MessageSender, void* i_pMessageData)=0;
		virtual  ~IMessageHandler(){};
		IMessageHandler(){};
		
	};

	struct _IMessageHandle
	{
		IMessageHandler * mHandler;
		myEngine::typedefs::Priority mMessagePriority;

		_IMessageHandle(IMessageHandler* i_handler, myEngine::typedefs::Priority i_priority)
		{
			MessagedAssert(i_handler != nullptr, "Handle Pointer is NUll");
			mHandler = i_handler;
			mMessagePriority = i_priority;
		}

		bool operator<(_IMessageHandle i_other)
		{
			return(mMessagePriority < i_other.mMessagePriority ? true : false);
		}
	};
	typedef _IMessageHandle MessageHandle;
}

#endif