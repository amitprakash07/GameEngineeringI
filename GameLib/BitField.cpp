#include "BitField.h"
#include <iostream>
#include <assert.h>
#include "Engine.h"

namespace MemoryManagement
{
	BitField* BitField::CreateBitField(size_t i_count)
	{
		BitFieldHandler *i_tempHandler = nullptr;
		if (EngineController::GameEngine::isEngineInitialized())
		{
			i_tempHandler = reinterpret_cast<BitFieldHandler*>(MemoryManagement::MemoryManager::getMemoryManager()->__alloc(sizeof(BitFieldHandler)*i_count));
			if (i_tempHandler != nullptr)
				return new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(BitField))) BitField(i_count, i_tempHandler);
		}
		else
		{
			i_tempHandler = new BitFieldHandler[i_count];
			if (i_tempHandler != nullptr)
				return new BitField(i_count, i_tempHandler);
		}

		return nullptr;
	}


	size_t BitField::getCount()
	{
		return count;
	}

	BitField::BitField(size_t i_count, BitFieldHandler * i_bitFieldHandler)
	{
		bitFieldHandler = i_bitFieldHandler;
		count = i_count;
		//free(i_bitFieldHandler);
	}

	BitField::~BitField()
	{
		assert(bitFieldHandler);
		if (EngineController::GameEngine::isEngineInitialized())
			EngineController::GameEngine::getMemoryManager()->__free(bitFieldHandler);
		else
			delete(bitFieldHandler);
	}


	size_t BitField::getBitFieldHandlerIndex(size_t index)
	{
		return static_cast<unsigned __int32>(index / 32);
	}

	bool BitField::operator[](size_t i_index)
	{
		//assert((i_index > (count * 32)));

		if (i_index > (count * 32))
		{
			std::cout << "\nIndex is out of range";
#ifdef _DEBUG
			__debugbreak();
#endif
			return false;
		}

		size_t temp_index = getBitFieldHandlerIndex(i_index);
		return (bitFieldHandler[temp_index].isBitSet(i_index - (temp_index * 32)));
	}

	bool BitField::getFirstUnUsedBit(size_t &i_index)
	{
		size_t counter;
		for (counter = 0; counter < count; counter++)
		{
			if (bitFieldHandler[counter].getBits() != 0xFFFFFFFF) break;
		}

		//assert((counter > count));

		if (counter > count)
		{
			std::cout << "\nMemory Pool is full";
#ifdef _DEBUG
			__debugbreak();
#endif
			return false;
		}

		i_index = ((counter * 32) + bitFieldHandler[counter].getFirstUnUsedBit());
		return true;
	}

	bool BitField::setBit(size_t i_index)
	{
		size_t temp_index = getBitFieldHandlerIndex(i_index);

		if (bitFieldHandler[temp_index].isBitSet(i_index))
		{
			std::cout << "\nAccessed Memory is not free";

#ifdef _DEBUG
			__debugbreak();
#endif
			return false;
		}

		bitFieldHandler[temp_index].setBit(i_index);
		return true;
	}

	bool BitField::freeBit(size_t i_index)
	{
		size_t temp_index = getBitFieldHandlerIndex(i_index);

		if (!bitFieldHandler[temp_index].isBitSet(i_index - (temp_index * 32)))
		{
			std::cout << "\nYou are trying to free unused memory";

#ifdef _DEBUG
			__debugbreak();
#endif
			return false;
		}

		bitFieldHandler[temp_index].freeBit(i_index - (temp_index * 32));
		return true;
	}

	void BitField::bitFieldUnitTest()
	{
		BitField * testBitField = BitField::CreateBitField(100);
		std::cout << "No of BitFieldHandler Created" << testBitField->count;

		std::cout << "BitFieldHandler Index for index 54 is " << testBitField->getBitFieldHandlerIndex(54);
		BitFieldHandler::BitFieldHandlerUnitTest((testBitField->getBitFieldHandler())[(testBitField->getBitFieldHandlerIndex(54))]);
	}
}


