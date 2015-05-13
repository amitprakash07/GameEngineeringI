#ifndef __MEMORYMANAGER_H
#define __MEMORYMANAGER_H

#define __ENABLEALIGNMENT

#include "Descriptor.h"

//Singleton
namespace MemoryManagement
{
	class MemoryManager
	{
	public:
		static MemoryManager* getMemoryManager(void*, size_t, Alignment);
		static MemoryManager* getMemoryManager();
		static void				deleteMemoryManager();
		void * __alloc(size_t);
		void __free(void *);

	private:
		static MemoryManager * mMemoryManager;
		Memory heap;
		Memory *startAddress; //for deleting memory purpose
		Memory *freeBlockList;
		Alignment heapAlignment;
		ValidHeap heapBounds;
		HeapStatus heapStatus;
		MemoryManager(void*, size_t, Alignment);
		MemoryManager operator=(MemoryManager){};
		MemoryManager(MemoryManager&);
		MemoryManager(MemoryManager*);
		~MemoryManager();

		size_t allignedSize(size_t);
		void setMemory(Memory *, size_t, short);
		void* returnUserMemoryAddress(Memory *);
		bool checkValidBlock(Memory*, short);
		void fillMemory(Memory*, short);
		void coallesceInGarbageCollector(Memory*);
		
	};
}
#endif