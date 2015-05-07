#include "NamedBitString.h"

namespace myEngine
{
	namespace utils
	{
		template<typename T>
		size_t NamedBitSet<T>::mBitCount;

		template<typename T>
		//myEngine::utils::Array<StringHash> NamedBitSet<T>::mNamedBits;
		std::vector<StringHash> NamedBitSet<T>::mNamedBits;

		template<typename T>
		NamedBitSet<T>::NamedBitSet()
		{
			mBitCount = sizeof(T) * 8;
			mNamedBits.reserve(mBitCount);
		}//end constructor

		template<typename T>
		unsigned __int8 NamedBitSet<T>::getBitIndex(myEngine::utils::StringHash i_stringHash)
		{
			for (size_t i = 0; i < mNamedBits.size(); i++)
			{
				if (mNamedBits[i] == nullptr)
				{
					addHashString(i_stringHash);
					return i;
				}

				if (mNamedBits[i] == i_stringHash)
					return i;
			}
		}//end getBitIndex

		template<typename T>
		T NamedBitSet<T>::getBitMask(myEngine::utils::StringHash i_stringHash)
		{
			return 1 << (getBitIndex(i_stringHash));
		}//end getBitMask

		template<typename T>
		void NamedBitSet<T>::addHashString(myEngine::utils::StringHash i_stringhash)
		{
			mNamedBits.push_back(i_stringhash);
			//mNamedBits.add(i_stringhash);
		}//end addHashString
	}//end namespace utils
}//end namespace myEngine