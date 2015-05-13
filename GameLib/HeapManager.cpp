#include "HeapManager.h"
#include <assert.h>
#include <iostream>

namespace MemoryManagement
{
	MemoryManager* MemoryManager::mMemoryManager = nullptr;

	MemoryManager * MemoryManager::getMemoryManager(void * i_HeapAddress, size_t memorySize, Alignment i_alignment)
	{
		if (mMemoryManager == nullptr)
			mMemoryManager = new MemoryManager(i_HeapAddress, memorySize, i_alignment);
		return mMemoryManager;
	}

	
	MemoryManager * MemoryManager::getMemoryManager()
	{
		if (mMemoryManager == nullptr)
			mMemoryManager = MemoryManagement::MemoryManager::getMemoryManager(
			_aligned_malloc(TOTALBYTES(1024 * 1024), 4),
			TOTALBYTES(1024 * 1024),
			MemoryManagement::ALIGNMENT_4);
		return mMemoryManager;
	}

	void MemoryManager::deleteMemoryManager()
	{
		if (mMemoryManager!=nullptr)
			delete mMemoryManager;
	}

	//Constructing the Memory Manager
	MemoryManager::MemoryManager(void * i_heapAddress, size_t heapSize, Alignment i_alignment)
	{
		freeBlockList = reinterpret_cast <Memory*> (i_heapAddress);
		startAddress = reinterpret_cast<Memory*>(i_heapAddress);
		size_t freeByteSize = heapSize - (HEADERBYTES + TRAILERBYTES);
		freeBlockList->size = freeByteSize;
		freeBlockList->next = freeBlockList;
#ifdef _DEBUG
		fillMemory(freeBlockList, FREEFLAG);
#endif

		heapBounds = { i_heapAddress, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(i_heapAddress)+heapSize), 0 };
		setMemory(freeBlockList, freeByteSize, FREEFLAG);
		heapStatus = { freeByteSize, 1, freeByteSize, 0, 0, 0, 0 };
		heapAlignment = i_alignment;
	}

	MemoryManager::~MemoryManager()
	{
		free(startAddress);
		startAddress = nullptr;
		freeBlockList = nullptr;
	}

	//Memory Allocation from the heap
	void * MemoryManager::__alloc(size_t i_size)
	{
		assert(i_size != 0);
		Memory *traverse = nullptr;
		Memory *previousPtr = nullptr;
		bool success = false;

		if (i_size == 0)
		{
#ifdef _ENGINE_DEBUG
			std::cout << "\nYou are trying to allocate zero byte memory. Not possible. Program Crashing\n";
#endif
			return nullptr;
		} //end if

		if (i_size > heapStatus.heapSize)
		{
#ifdef _ENGINE_DEBUG
			std::cout << "\nInsuficient memory in heap\n";
			return nullptr;
#endif
		} //end if

		previousPtr = freeBlockList;

		// First Allocation
		if (previousPtr == nullptr)
		{
			heap.next = previousPtr = freeBlockList = &heap;
			heap.size = 0;
		}

		for (traverse = previousPtr->next;; previousPtr = traverse, traverse = traverse->next)
		{
			if (traverse != freeBlockList)
			{
				if (!checkValidBlock(traverse, FREEFLAG))
				{
#ifdef _ENGINE_DEBUG
					std::cout << "\nWrong garbage patterns for free memory. Block corrupted\n";
#endif
					return nullptr;
				}
			}

			if (traverse->size == allignedSize(TOTALBYTES(i_size))) //exact match
			{
				previousPtr->next = traverse->next; //delinking from the free list
				setMemory(traverse, allignedSize(i_size), MALLOCFLAG);

#ifdef _ENGINE_DEBUG
				fillMemory(traverse, MALLOCFLAG);
#endif
				success = true;
			}//end if - exact match

			if (traverse->size >= allignedSize(TOTALBYTES(i_size))) //reducing the size of the free block and allocating memory at the end
			{
				traverse->size -= TOTALBYTES(allignedSize(i_size));
				setMemory(traverse, traverse->size, FREEFLAG);
				traverse = reinterpret_cast<Memory*>(reinterpret_cast<uintptr_t>(traverse)+TOTALBYTES(traverse->size));
				setMemory(traverse, allignedSize(i_size), MALLOCFLAG);

#ifdef _ENGINE_DEBUG
				fillMemory(traverse, MALLOCFLAG);
#endif

				success = true;
			}

			if (success)
			{
				freeBlockList = previousPtr;

				//Updating the Heap Status
				heapStatus.usedBlocks++;
				heapStatus.usedBytes += traverse->size;
				heapStatus.freeBlocks--;
				heapStatus.freeBytes -= traverse->size;
				heapStatus.totalAllocations++;
				if (heapBounds.allocatedBlock == 0) heapBounds.allocatedBlock = 1;
				return (returnUserMemoryAddress(traverse));
			}

			if (traverse == freeBlockList)
			{
#ifdef _ENGINE_DEBUG
				std::cout << "\nInsufficient Memory in Heap. Returning Null\n";
#endif
				return nullptr;
			}
		}//end for
	}//end of function

	//Deallocation
	void MemoryManager::__free(void* i_ptr)
	{
		if (!i_ptr)
		{
#ifdef _ENGINE_DEBUG
			std::cout << "\nNULL Pointer. Exiting\n";
#endif
			return;
		}

		Memory * freeingMemory = reinterpret_cast<Memory*>(reinterpret_cast<uintptr_t>(i_ptr)-HEADERBYTES);

		/* Enable if Alignment is enabled*/
#ifdef __ENABLEALIGNMENT
		if (reinterpret_cast<uintptr_t>(freeingMemory) % heapAlignment != 0)
		{
#ifdef _ENGINE_DEBUG
			std::cout << "\nInvalid Pointer. Not Aligned- Not in Heap\n";
#endif
			return;
		}
#endif

		//Checking pointer within the heap
		if (freeingMemory > heapBounds.HeapEndAddress || freeingMemory < heapBounds.HeapStartAddress)
		{
#ifdef _ENGINE_DEBUG
			std::cout << "\nAddress not within the Heap limits\n";
#endif
			return;
		}

		//Checking is memory allocated or not
		if (!checkValidBlock(freeingMemory, MALLOCFLAG))
		{
#ifdef _ENGINE_DEBUG
			std::cout << "\nTrying to free either non allocated memory or freed memory\n";
#endif
			return;
		}

		/*Valid Memory Ready to link with Free block List*/

		//Update Heap Status
		heapStatus.usedBlocks--;
		heapStatus.usedBytes -= freeingMemory->size;
		heapStatus.freeBlocks++;
		heapStatus.freeBytes += freeingMemory->size;

		//Need to coallesce/garbage collect on every free
		coallesceInGarbageCollector(freeingMemory);
	}//End of function

	//Garbage Collector
	void MemoryManager::coallesceInGarbageCollector(Memory* i_freeingMemory)
	{
		Memory * traverse;
		/*Finding where block can fit into*/
		for (traverse = freeBlockList;
			!(i_freeingMemory > traverse && i_freeingMemory < traverse->next); traverse = traverse->next)
		{
			/*Checking if freeing Memory is after the free list or before the free list */
			if (traverse >= traverse->next && (i_freeingMemory > traverse || i_freeingMemory < traverse->next))
				break;
		}

		//Checking for Upper Coallescing
		//If block is before traverse and contigous
		if (
			(reinterpret_cast<uintptr_t>(i_freeingMemory)+TOTALBYTES(i_freeingMemory->size))
			== reinterpret_cast<uintptr_t>(traverse->next)
			)
		{
			i_freeingMemory->size += TOTALBYTES(traverse->next->size);
			i_freeingMemory->next->next;
			setMemory(i_freeingMemory, i_freeingMemory->size, FREEFLAG);

#ifdef _ENGINE_DEBUG
			fillMemory(i_freeingMemory, FREEFLAG);
#endif
		}
		else
		{
			//if Block is before Traverse but not contigous
			setMemory(i_freeingMemory, i_freeingMemory->size, FREEFLAG);
			i_freeingMemory->next = traverse->next;

#ifdef _ENGINE_DEBUG
			fillMemory(i_freeingMemory, FREEFLAG);
#endif
		}

		//Checking for lower coallescing
		//If freeing block is after traverse and contigous
		if (reinterpret_cast<uintptr_t>(traverse)+TOTALBYTES(traverse->size) == reinterpret_cast<uintptr_t> (i_freeingMemory))
		{
			traverse->size += TOTALBYTES(i_freeingMemory->size);
			traverse->next = i_freeingMemory->next;
			setMemory(traverse, traverse->size, FREEFLAG);
#ifdef _ENGINE_DEBUG
			fillMemory(traverse, FREEFLAG);
#endif
		}

		//If freeing block is after traverse but not contigous - link to freeList
		else
		{
			traverse->next = i_freeingMemory;

#ifdef _ENGINE_DEBUG
			fillMemory(i_freeingMemory, FREEFLAG);
#endif
		}

		freeBlockList = traverse;
	}//End of Garbage Collector

	//Storing the Guard bands and creating the format for the new allocation or deallocation
	void MemoryManager::setMemory(Memory * address, size_t memSize, short flag)
	{
		address->guard = (flag ? MALLOC : FREE);
		address->size = memSize;
		uint8_t *eptr;
		eptr = reinterpret_cast<uint8_t*> (reinterpret_cast<uintptr_t>(address)+TRAILEROFFSET(memSize));
		*eptr = (flag ? MALLOC : FREE);
	}

	//Filling the memory with either allocation pattern or deallocation pattern
	void MemoryManager::fillMemory(Memory * i_mem, short flag)
	{
		uint8_t * startAddress = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(i_mem)+HEADERBYTES);
		for (size_t i = 0; i < i_mem->size; ++i)
		{
			if (i % 2 == 0) //For writing alternate codes for malloc and free
				*(startAddress + i) = flag ? MALLOC_1 : FREE_1;
			else
				*(startAddress + i) = flag ? MALLOC_2 : FREE_2;
		}
	}

	//Required User Memory is always from header block + header size
	void* MemoryManager::returnUserMemoryAddress(Memory * i_ptr)
	{
		return (reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(i_ptr)+HEADERBYTES));
	}

	//Checking the validity of the block - if guards are same, it is valid
	bool MemoryManager::checkValidBlock(Memory* i_userMemory, short flag)
	{
		Memory * checkMem = i_userMemory; // reinterpret_cast<Memory *>(reinterpret_cast<uintptr_t>(i_userMemory)-HEADERBYTES);
		uint8_t * eptr = reinterpret_cast<uint8_t *> (reinterpret_cast<uintptr_t>(checkMem)+TRAILEROFFSET(checkMem->size));
		uint8_t validPattern = flag ? MALLOC : FREE;
		return (checkMem->guard == validPattern && (*eptr) == validPattern);
	}

	//Returning the size in multiple of the alignment - TO DO
	size_t MemoryManager::allignedSize(size_t i_size)
	{
		size_t alignedSize;

#ifdef __ENABLEALIGNMENT
		if (i_size%heapAlignment != 0)
			alignedSize = (heapAlignment - (i_size%heapAlignment) + i_size);
		else
			alignedSize = i_size;

		return alignedSize;
#else
		return i_size;
#endif
	}

}//namespace MemoryManagement


