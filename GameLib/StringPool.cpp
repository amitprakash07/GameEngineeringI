#include "StringPool.h"
#include "Engine.h"
#include "HashedString.h"

namespace myEngine
{
	namespace utils
	{
		StringPool* StringPool::mStringPool = nullptr;

		StringPool* StringPool::getStringPool()
		{
			if (mStringPool == nullptr)
			{
				mStringPool = EngineController::GameEngine::isEngineInitialized() ?
					new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(StringPool))) StringPool() :
					new StringPool();
			}
			
			return mStringPool;

		}//getStringPool

		StringPool::StringPool()
		{
			mStringList.reserve(200);
		}


		char* StringPool::findString(char * i_string)
		{
			size_t tempStringLength = strlen(i_string);
			bool isFound = false;
			
			for (size_t i = 0; i < mStringList.size(); i++)
			{
				if (myEngine::utils::StringHash(mStringList[i].getAsChar()) == myEngine::utils::StringHash(i_string))
					return mStringList[i].getAsChar();
			}

			return (addString(i_string));
		}//end find function


		char* StringPool::addString(char* i_String)
		{
			myEngine::typedefs::String tempString = myEngine::typedefs::String(i_String);// {i_String, strlen(i_String)};
			//tempString.mString = _strdup(i_String);
			//tempString.mStringLength = strlen(i_String);
			mStringList.push_back(tempString);
			return tempString.mString;
		}

	}//end namespace utils
}//end namespace myEngine