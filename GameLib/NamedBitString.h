#ifndef __NAMED_BIT_SET_H
#define __NAMED_BIT_SET_H

#include "HashedString.h"
#include <vector>


namespace myEngine
{
	namespace utils
	{
		template<typename T>
		class NamedBitSet
		{
		public:
			unsigned __int8 getBitIndex(myEngine::utils::StringHash);
			T getBitMask(const myEngine::utils::StringHash);
			NamedBitSet();
		private:
			static size_t mBitCount; // number of bits-should be in between 8 and 64
			static std::vector<StringHash> mNamedBits;
			void addHashString(myEngine::utils::StringHash &);
		};
	}//end namespace utils
}//end namespace myEngine

#endif // __NAMED_BIT_SET_H