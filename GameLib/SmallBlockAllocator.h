#ifndef __SMALLBLOACKALLOCATOR_H
#define __SMALLBLOACKALLOCATOR_H

namespace MemoryManagement{
	class BitField;

	class SmallBlockAllocator
	{
	public:
		static SmallBlockAllocator * CreateMemoryPool(size_t, size_t);
		void* __allocMemory(size_t);
		void __freeMemory(void *);
		bool isContained(void *);
		void displayMemoryAddress() const;
		void static smallBlockAllocatorTest();
		size_t blocksFreeCount();
		~SmallBlockAllocator();

	private:
		void * memoryPoolStartAddress;
		BitField* memoryTracker;
		size_t memoryBlockSize;
		size_t blockCounts;

		SmallBlockAllocator(size_t, size_t, void*, BitField*);
	};
}

#endif
