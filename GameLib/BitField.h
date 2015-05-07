#ifndef __BITFIELD_H
#define __BITFIELD_H

#include "BitFieldHandler.h"


namespace MemoryManagement
{
	class BitField
	{
	public:
		static BitField*								CreateBitField(size_t);
		bool											operator[](size_t);
		size_t											getBitFieldHandlerIndex(size_t index);
		bool											getFirstUnUsedBit(size_t &);
		size_t											getCount();
		bool											setBit(size_t);
		bool											freeBit(size_t);
		static void										bitFieldUnitTest();
		BitFieldHandler*								getBitFieldHandler(){ return bitFieldHandler; }
		~BitField();
		
		
		

	private:
		BitFieldHandler *bitFieldHandler;
		size_t count;
		BitField(size_t, BitFieldHandler*);
	};
}

#endif