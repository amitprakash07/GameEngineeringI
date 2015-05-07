#include "BitFieldHandler.h"
#include <math.h>
#include <iostream>
#include <assert.h>
#include "Engine.h"

namespace MemoryManagement
{

	BitFieldHandler::BitFieldHandler()
	{
		setClassName(EngineController::GameEngine::getStringPool()->findString("BitFieldHandler"));
		bits = 0x00000000;
	}

	BitFieldHandler::~BitFieldHandler()
	{
	}

	BitFieldHandler::BitFieldHandler(BitFieldHandler & i_bitField)
	{
		bits = i_bitField.bits;
	}

	void BitFieldHandler::operator=(BitFieldHandler i_bitField)
	{
		bits = i_bitField.bits;
	}

	void BitFieldHandler::operator=(BitFieldHandler * i_bitField)
	{
		bits = i_bitField->bits;
	}

	void* BitFieldHandler::operator new (size_t i_size)
	{
		void * pBitFieldArrayMem = nullptr;
		if (EngineController::GameEngine::isEngineInitialized())
			pBitFieldArrayMem = EngineController::GameEngine::getMemoryManager()->__alloc(i_size);
		else
			pBitFieldArrayMem = _aligned_malloc(i_size, 32);

		return pBitFieldArrayMem;

	}

		void * BitFieldHandler::operator new[](size_t i_size)
	{
		void * pBitFieldArrayMem = nullptr;
		if (EngineController::GameEngine::isEngineInitialized())
			pBitFieldArrayMem = EngineController::GameEngine::getMemoryManager()->__alloc(i_size);
		else
			pBitFieldArrayMem = _aligned_malloc(i_size, 32);

		return pBitFieldArrayMem;
	}


		void BitFieldHandler::operator delete (void* i_addr)
	{
		assert(i_addr);
		if (EngineController::GameEngine::isEngineInitialized())
			EngineController::GameEngine::getMemoryManager()->__free(i_addr);
		else
			_aligned_free(i_addr);
	}

	void BitFieldHandler::operator delete[](void * i_addr)
	{
		assert(i_addr);
		assert(i_addr);
		if (EngineController::GameEngine::isEngineInitialized())
			EngineController::GameEngine::getMemoryManager()->__free(i_addr);
		else
			_aligned_free(i_addr);

	}

		void BitFieldHandler::displayBits() const
	{
		unsigned __int32 temp;
		for (int i = 32; i >= 1; i--)
		{
			temp = bits;
			temp = temp << (32 - i);
			temp = temp >> 31;
			std::cout << temp;
		}
	}

	size_t BitFieldHandler::getFirstUnUsedBit()
	{
		unsigned __int32 value = bits;

		for (size_t i = 0; i < 32; i++)
		{
			if (!(value & (1 << i)))	// if i th bit != 1
				return i;
		}

		return -1;
	}

	void BitFieldHandler::setBit(const int i_index)
	{
		bits |= (1 << i_index);
	}

	void BitFieldHandler::freeBit(const int i_index)
	{
		bits &= ~(1 << i_index);
	}

	unsigned __int32 BitFieldHandler::getFreeBitMask(const unsigned __int32 i_index)
	{
		return (~static_cast<unsigned __int32>((1 * (pow<unsigned __int32>(2, i_index - 1)))));
	}

	unsigned __int32 BitFieldHandler::getSetBitMask(const unsigned __int32 i_index)
	{
		return (0x00000000 | (int)pow(2.0f, (float)i_index - 1));
	}

	bool BitFieldHandler::isBitSet(const unsigned __int32 i_index)
	{
		unsigned __int32 temp = bits;
		temp = temp << (32 - (i_index + 1));
		temp = temp >> 31;
		if (temp == 0x00000000) return false;
		else return true;
	}

	const unsigned __int32 BitFieldHandler::getBits()
	{
		return static_cast<unsigned __int32>(bits);
	}

	void BitFieldHandler::BitFieldHandlerUnitTest()
	{
		using namespace std;
		BitFieldHandler First;
		std::cout << "Bit Field: ";
		First.displayBits();
		std::cout << endl;

		First.setBit(10);
		std::cout << "Bit Field after setting bit 10: ";
		First.displayBits();
		std::cout << endl;

		First.setBit(1);
		std::cout << "Bit Field after setting bit 1: ";
		First.displayBits();
		std::cout << endl;

		First.freeBit(1);
		std::cout << "Bit Field after freeing bit 1: ";
		First.displayBits();
		std::cout << endl;

		First.freeBit(10);
		std::cout << "Bit Field after freeing bit 10: ";
		First.displayBits();
		//First.displayBits();
		std::cout << endl;
		First.setBit(2);
		First.setBit(3);
		First.displayBits();

		std::cout << endl << First.getFirstUnUsedBit();
		std::cout << endl << First.isBitSet(1);
		std::cout << endl << First.isBitSet(2);
		std::cout << endl << First.isBitSet(3);
		std::cout << endl << First.isBitSet(4);
		std::cout << endl << First.isBitSet(8);
		std::cout << endl;
	}

	void BitFieldHandler::BitFieldHandlerUnitTest(BitFieldHandler i_bitFieldHandler)
	{
		using namespace std;
		BitFieldHandler First = i_bitFieldHandler;
		std::cout << "Bit Field: ";
		First.displayBits();
		std::cout << endl;

		First.setBit(10);
		std::cout << "Bit Field after setting bit 10: ";
		First.displayBits();
		std::cout << endl;

		First.setBit(1);
		std::cout << "Bit Field after setting bit 1: ";
		First.displayBits();
		std::cout << endl;

		First.freeBit(1);
		std::cout << "Bit Field after freeing bit 1: ";
		First.displayBits();
		std::cout << endl;

		First.freeBit(10);
		std::cout << "Bit Field after freeing bit 10: ";
		First.displayBits();
		//First.displayBits();
		std::cout << endl;
		First.setBit(2);
		First.setBit(3);
		First.displayBits();

		std::cout << endl << First.getFirstUnUsedBit();
		std::cout << endl << First.isBitSet(1);
		std::cout << endl << First.isBitSet(2);
		std::cout << endl << First.isBitSet(3);
		std::cout << endl << First.isBitSet(4);
		std::cout << endl << First.isBitSet(8);
		std::cout << endl;
	}

}//namespace MemoryManagement

