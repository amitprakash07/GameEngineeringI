#include "Array.h"

namespace myEngine
{
	namespace utils
	{
		template <typename T>
		Array<T>::Array()
		{
			mObjects = malloc(sizeof(T*) * 20);
			mObjectCount = 20;
			addIndex = 0;
			for (size_t i = 0; i < mObjectCount; i++)
				mObjects[i] = nullptr;
		}//end constructor

		template<typename T>
		void Array<T>::reserve(size_t i_newCount)
		{
			if (mObjectCount < i_newCount)
			{
				T** tempObjectList = malloc(sizeof(T*)*i_newCount);
				for (size_t i = 0; i < mObjectCount; i++)
					tempObjectList[i] = mObjects[i];

				delete mObjects;
				mObjects = tempObjectList;
				mObjectCount = i_newCount;
			}//end-if
		}//end-reserve

		template<typename T>
		bool Array<T>::resize(size_t i_newCount)
		{
			if (i_newCount > mObjectCount)
			{
				reserve(i_newCount);
			}//end-if
		}//end-resize

		template<typename T>
		void Array<T>::add(T& i_object, size_t i_position)
		{
			size_t tempAddIndex = findNullPosition();

			while (tempAddIndex > i_position)
			{
				mObjects[tempAddIndex] = mObjects[tempAddIndex - 1];
				--tempAddIndex;
			}//end-while

			mObjects[i_position] = i_object;
			++addIndex;
		} //end-add

		template<typename T>
		void Array<T>::add(T& i_object)
		{
			add(i_object, findNullPosition());
		}//end-add

		template<typename T>
		size_t Array<T>::findNullPosition()
		{
			size_t tempPosition = 0;
			if (addIndex > mObjectCount)
			{
				this->resize(mObjectCount + 10);
			}//end-if

			return addIndex;
		}//findNullPosition

		template<typename T>
		void Array<T>::remove(size_t i_position)
		{
			assert(mObjects[i_position] != nullptr);
			while (i_position < addIndex)
			{
				mObjects[i_position] = mObjects[i_position + 1];
				++i_position;
			}//end-while

			mObjects[--addIndex] = nullptr;
		}//end-remove

		template<typename T>
		void Array<T>::remove()
		{
			remove(addIndex - 1);
		}//end-remove

		template<typename T>
		size_t Array<T>::size()
		{
			return addIndex;
		}

		template<typename T>
		T& Array<T>::operator[](size_t i_position)
		{
			assert(i_position < addIndex);
			return mObjects[i_position];
		}//end-operator[]
	}//namespace utils
}//namespace myEngine