#ifndef __DESCRIPTOR_H
#define __DESCRIPTOR_H

#include <stdio.h>
#include <stdint.h>

namespace MemoryManagement
{
	//GuardBands Macros
#define MALLOC 0x1212
#define FREE 0x2323

	//Flags for checking memory block status
#define MALLOCFLAG 1
#define FREEFLAG 0

	//Macros for calculating addresses for manipulation
#define HEADERBYTES sizeof(MemoryManagement::Memory)
#define TRAILERBYTES sizeof(unsigned int)
#define TRAILEROFFSET(s) (HEADERBYTES + s)
#define TOTALBYTES(s) (HEADERBYTES + TRAILERBYTES + s)

	//MACROS for filling memory with garbage
#define MALLOC_1 0xbe	//1 byte
#define MALLOC_2 0xef	//1 byte
#define FREE_1 0xde		//1 byte
#define FREE_2 0xad		//1 byte

	enum _Alignment
	{
		ALIGNMENT_2 = 2,
		ALIGNMENT_4 = 4,
		ALIGNMENT_8 = 8,
		ALIGNMENT_16 = 16,
		ALIGNMENT_32 = 32,
		ALIGNMENT_64
	};
	typedef _Alignment Alignment;

	struct Memory
	{
		uint8_t guard;
		Memory * next;
		unsigned size;
	};

	typedef struct Memory Memory;

	struct ValidHeap
	{
		void * HeapStartAddress;
		void * HeapEndAddress;
		unsigned short allocatedBlock;
	};
	typedef struct ValidHeap ValidHeap;

	struct HeapStatus
	{
		unsigned int heapSize;
		unsigned int freeBlocks;
		unsigned int freeBytes;
		unsigned int usedBlocks;
		unsigned int usedBytes;
		unsigned int totalAllocations;
		unsigned int totalDeAllocations;
	};
	typedef struct HeapStatus HeapStatus;
}

#endif