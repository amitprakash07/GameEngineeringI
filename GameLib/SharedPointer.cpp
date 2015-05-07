#include "SharedPointer.h"

namespace myEngine
{
	template<typename T>
	SharedPointer<T>::SharedPointer()
	{
		m_WrappingObject = new T;
		m_referenceCount = new unsigned int;
		*m_referenceCount = 1;
	}


	//template<typename T>
	/*T* SharedPointer<T>::CreateObject()
	{
		SharedPointer <T> temp = new SharedPointer<T>();
		//if (temp->

			m_referenceCount++;

	}*/

	template<typename T>
	SharedPointer<T>::~SharedPointer()
	{
		deleteObject();
	}


	template<typename T>
	SharedPointer<T>::SharedPointer(SharedPointer<T> & i_other)
	{
		m_WrappingObject = i_other.m_WrappingObject;
		m_referenceCount = i_other.m_referenceCount;
		(*(m_referenceCount))++;
	}


	template<typename T>
	SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T> &i_other)
	{
		if (this != i_other)
		{
			deleteObject();
			m_WrappingObject = i_other.m_WrappingObject;
			assert(m_referenceCount);
			m_referenceCount = i_other.m_referenceCount;
			(*(m_referenceCount))++;
		}
		return *(this);
	}


	template<typename T>
	T& SharedPointer<T>::operator*()
	{
		assert(m_WrappingObject);
		return *m_WrappingObject;
	}

	template<typename T>
	T* SharedPointer<T>::operator->()
	{
		assert(m_WrappingObject);
		return m_WrappingObject
	}

	template<typename T>
	bool SharedPointer<T>::deleteObject()
	{
		assert(m_WrappingObject);
		if (--(*m_referenceCount) == 0)
		{
			delete m_referenceCount;
			delete m_WrappingObject;
		}

		(*m_referenceCount)--;
	}
	


} //myEngine