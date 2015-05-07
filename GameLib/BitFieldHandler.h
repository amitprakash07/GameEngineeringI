#ifndef __BitFieldHandler_H
#define __BitFieldHandler_H

#include "Object.h"

namespace MemoryManagement
{
	class BitFieldHandler: public myEngine::Object
	{
	public:
		BitFieldHandler();
		BitFieldHandler(BitFieldHandler &);
		~BitFieldHandler();

		void							setBit(const int);
		void							freeBit(const int);
		size_t							getFirstUnUsedBit();
		void							displayBits()const;
		bool							isBitSet(const unsigned __int32);
		const unsigned __int32			getBits();
		void							operator=(BitFieldHandler);
		void*							operator new (size_t);
		void*							operator new[](size_t);
		void							operator delete (void*);
		void							operator delete[](void *);
		void							BitFieldHandler::operator=(BitFieldHandler *);
		static void						BitFieldHandlerUnitTest();
		static void						BitFieldHandlerUnitTest(BitFieldHandler i_bitFieldHandler);

	private:
		unsigned __int32				bits;
		unsigned __int32				getFreeBitMask(const unsigned __int32);
		unsigned __int32				getSetBitMask(const unsigned __int32);
	};
}

#endif