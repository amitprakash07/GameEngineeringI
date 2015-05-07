#include <assert.h>
#include "Vector3D.h"

namespace myEngine
{
	template<class T>
	void RingBuffer<T>::addItem(const T i_item)
	{
		if ((m_currentItemIndex + 1) == m_maxSize)
		{
			resetFlag = true;
			m_currentItemIndex = -1;
		}
		items[++m_currentItemIndex] = i_item;
	}

	template<class T>
	T RingBuffer<T>::operator[](int i_index)
	{
		//assert (i_index < m_maxSize );
		if (i_index < m_maxSize && i_index > 0)
		{
			if (!resetFlag)
			{
				//assert((i_index - 1) <= m_currentItemIndex);
				if ((i_index - 1) <= m_currentItemIndex)
				{
					int returnIndex = m_currentItemIndex;
					int count = 1;
					while (count != i_index)
					{
						++count;
						--returnIndex;
					}
					return items[returnIndex];
				}
				return 0;
			}
			else
			{
				int returnIndex = m_currentItemIndex;
				int count = 1;
				while (count != i_index)
				{
					++count;
					--returnIndex;
					if (returnIndex == 0) returnIndex = m_maxSize - 1;
				}
				return items[returnIndex];
			}
		}
		return 0;
	}

	template<>
	inline Vector3D RingBuffer<Vector3D>::operator[](int i_index)
	{
		//assert (i_index < m_maxSize );
		if (i_index < m_maxSize && i_index > 0)
		{
			if (!resetFlag)
			{
				//assert((i_index - 1) <= m_currentItemIndex);
				if (((i_index - 1) < m_currentItemIndex) || ((i_index - 1) == m_currentItemIndex))
				{
					int returnIndex = m_currentItemIndex;
					int count = 1;
					while (count != i_index)
					{
						++count;
						--returnIndex;
					}
					return items[returnIndex];
				}
				return nullptr;
			}
			else
			{
				int returnIndex = m_currentItemIndex;
				int count = 1;
				while (count != i_index)
				{
					++count;
					--returnIndex;
					if (returnIndex == 0) returnIndex = m_maxSize - 1;
				}
				return items[returnIndex];
			}
		}
		return nullptr;
	}

	template<class T>
	int RingBuffer<T>::count()
	{
		if (!resetFlag) return (m_currentItemIndex + 1);
		return m_maxSize;
	}

	template<class T>
	int RingBuffer<T>::maxSize()
	{
		return m_maxSize;
	}

	template<class T>
	void RingBuffer<T>::ringBufferUnitTest()
	{
		RingBuffer<int> *intRingBuffer = new RingBuffer<int>(5);
		for (int i = 0; i < 10; i++)
			intRingBuffer->addItem(i);
		cout << endl << (*intRingBuffer)[1];

		using namespace myEngine;
		delete intRingBuffer;
		RingBuffer<Vector3D> *vector3DRingBuffer = new RingBuffer<Vector3D>(10);
		for (int i = 0; i < 20; i++)
		{
			vector3DRingBuffer->addItem(Vector3D(static_cast<float>(i), static_cast<float>(i + 1), static_cast<float>(i + 2)));
		}
		cout << endl;
		(*vector3DRingBuffer)[1].displayVector();
		cout << endl;
		delete vector3DRingBuffer;
	}
}