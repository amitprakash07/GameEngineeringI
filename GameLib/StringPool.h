#ifndef __STRING_POOL_H
#define __STRING_POOL_H


#include <vector>
#include "additionaltypes.h"

namespace myEngine
{
	namespace utils
	{
		class StringPool
		{
		public:
			static StringPool*							getStringPool();
			char*										findString(char*);

		private:
			static StringPool*							mStringPool;
			std::vector<myEngine::typedefs::String>		mStringList;
			char*										addString(char *);
			StringPool();
			StringPool(StringPool&);
		};//end-StringPool
	}//end namespace utils
}//end namespace myEngine

#endif //__STRING_POOL_H