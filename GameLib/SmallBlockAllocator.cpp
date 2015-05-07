#include "SmallBlockAllocator.h"
#include <iostream>
#include <assert.h>
#include "Engine.h"
#include "BitField.h"

namespace MemoryManagement
{
	SmallBlockAllocator* SmallBlockAllocator::CreateMemoryPool(size_t i_memoryBlockSize, size_t i_count)
	{
		size_t tempCount = i_count;

		if ((i_count % 32) != 0) tempCount = (tempCount / 32) + 1;
		else tempCount /= 32;

#ifndef __GAMEENGINE
		void * i_ptr_address = malloc(i_memoryBlockSize * i_count);
#else
		void *i_ptr_address = MemoryManagement::MemoryManager::getMemoryManager()->__alloc(i_memoryBlockSize * i_count);
#endif

		if (i_ptr_address == NULL) return 0;

		BitField * i_ptr_mem_track = BitField::CreateBitField(tempCount);

		if (i_ptr_mem_track == NULL)
		{
			free(i_ptr_address);
			return 0;
		}

#ifndef __GAMEENGINE
		return (new SmallBlockAllocator(i_memoryBlockSize,
			i_count,
			i_ptr_address,
			i_ptr_mem_track));
#else
		return (new(MemoryManagement::MemoryManager::getMemoryManager()->__alloc(sizeof(SmallBlockAllocator)))
			SmallBlockAllocator(i_memoryBlockSize,
			i_count,
			i_ptr_address,
			i_ptr_mem_track));
#endif
	}

	SmallBlockAllocator::SmallBlockAllocator(size_t i_memoryBlockSize, size_t i_blockCount, void * i_ptrMemoryPoolStartAddress, BitField * i_ptrMemoryTracker) :
		memoryBlockSize(i_memoryBlockSize),
		blockCounts(i_blockCount),
		memoryPoolStartAddress(i_ptrMemoryPoolStartAddress),
		memoryTracker(i_ptrMemoryTracker)
	{
		
	}

	SmallBlockAllocator::~SmallBlockAllocator()
	{
		free(memoryPoolStartAddress);
		free(memoryTracker);
	}

	void SmallBlockAllocator::displayMemoryAddress()const
	{
		std::cout << memoryPoolStartAddress;
	}

	void* SmallBlockAllocator::__allocMemory(size_t i_blockSize)
	{
		if (memoryBlockSize != i_blockSize)
			return malloc(i_blockSize);
		else
		{
			size_t freeBitIndex;
			if (memoryTracker->getFirstUnUsedBit(freeBitIndex))
			{
				memoryTracker->setBit(freeBitIndex);
				return
					(
					reinterpret_cast<void*>
					(
					reinterpret_cast<uintptr_t>(memoryPoolStartAddress)+(freeBitIndex * i_blockSize)
					)
					);
			}

			else
			{
				return malloc(i_blockSize);
			}
		}
	}

	void SmallBlockAllocator::__freeMemory(void *i_ptrMemory)
	{
		if (!isContained(i_ptrMemory))
		{
			free(i_ptrMemory);
		}
		else
		{
			uintptr_t freeMem = reinterpret_cast<uintptr_t> (i_ptrMemory);
			size_t memIndex = (freeMem - reinterpret_cast<uintptr_t>(memoryPoolStartAddress)) / memoryBlockSize;
			//bool isbitfree = memoryTracker[0][memIndex];
			if ((*memoryTracker)[memIndex])
			{
				memoryTracker[0].freeBit(memIndex);   //m_bitField->SetBit(index, false);
			}
			else
			{
				assert("Wrong Memory");
			}
		}
	}

	bool SmallBlockAllocator::isContained(void * i_ptrMemory)
	{
		uintptr_t checkMem = reinterpret_cast<uintptr_t>(i_ptrMemory);
		uintptr_t maxMem = reinterpret_cast <uintptr_t> (memoryPoolStartAddress)+(memoryBlockSize * blockCounts);

		if (
			checkMem >= reinterpret_cast<uintptr_t>(memoryPoolStartAddress)
			&&
			checkMem <= maxMem
			) return true;

		return false;
	}

	void SmallBlockAllocator::smallBlockAllocatorTest()
	{
		SmallBlockAllocator *size8 = SmallBlockAllocator::CreateMemoryPool(8, 100);
		std::cout << "\ncount" << size8->memoryTracker[0].getCount();
		std::cout << "\nMemoryPoolStartAddress" << size8->memoryPoolStartAddress;

		unsigned __int8 *myPoolMem = reinterpret_cast<unsigned __int8*> (size8->__allocMemory(8));

		*myPoolMem = 10;
		std::cout << "\nValue " << *myPoolMem;

		//trying to free unallocated memory
		size8->__freeMemory(reinterpret_cast<void*>(reinterpret_cast<uintptr_t> (myPoolMem)+8));

		/**trying to free allocated memory twice */

		//genuine free
		size8->__freeMemory(reinterpret_cast<void *> (myPoolMem));

		//freeing second time
		size8->__freeMemory(reinterpret_cast<void *> (myPoolMem));
	}
}//namespace MemoryManagement

