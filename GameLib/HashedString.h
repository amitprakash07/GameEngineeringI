#ifndef __HASHED_STRING_H
#define __HASHED_STRING_H

namespace myEngine
{
	namespace utils
	{
		class StringHash
		{
		public:
			StringHash();
			StringHash(const char*);
			StringHash(const StringHash &);

			unsigned __int32 getHash();
			StringHash & operator=(const StringHash &);

			bool operator==(const StringHash &) const;

			static unsigned __int32 Hash(const char *);
			static unsigned __int32 Hash(const void *, size_t);

		private:
			unsigned __int32 mHash;
#ifdef _ENGINE_DEBUG
			char *mString;
#endif
		};
	}//namespace utils
}//namespace myEngine

#endif //__HASHED_STRING_H