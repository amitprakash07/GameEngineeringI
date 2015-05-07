#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

namespace myEngine{
	template<class T>
	class RingBuffer
	{
	public:
		void addItem(const T);
		T operator[](int);

		RingBuffer() :
			m_maxSize(100),
			resetFlag(false),
			m_currentItemIndex(-1)
		{
			items = new T[size];
		}

		RingBuffer(int i_count) :
			m_maxSize(i_count),
			resetFlag(false),
			m_currentItemIndex(-1)
		{
			items = new T[i_count];
		}

		RingBuffer(RingBuffer<T> * i_ringBuffer)
		{
			items = i_ringBuffer->items;
			m_maxSize = i_ringBuffer->m_maxSize;
			resetFlag = i_ringBuffer->resetFlag;
			m_currentItemIndex = i_ringBuffer->m_currentItemIndex;
			//
		}

		~RingBuffer()
		{
			delete items;
		}

		int count();
		int maxSize();

		static void ringBufferUnitTest();

	private:
		T * items;
		int m_maxSize;
		int m_currentItemIndex;
		//int m_currentInsertItemIndex;
		bool resetFlag;
	};
}

#include "RingBuffer.inl"

#endif