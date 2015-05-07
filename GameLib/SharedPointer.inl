namespace myEngine
{
	template <typename T>
	SharedPointer<T>::SharedPointer()
	{
		m_WrappingObject = nullptr;
		m_referenceCount = new unsigned int;
		*m_referenceCount = 0;
	}

	template<typename T>
	SharedPointer<T>::SharedPointer(T* i_ptr)
	{
		assert(i_ptr != nullptr);
		m_WrappingObject = i_ptr;
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
	SharedPointer<T>::SharedPointer(const SharedPointer<T> & i_other)
	{
		m_WrappingObject = i_other.m_WrappingObject;
		m_referenceCount = i_other.m_referenceCount;
		(*(m_referenceCount))++;
	}

	template<typename T>
	SharedPointer<T>::SharedPointer(SharedPointer<T> * i_other)
	{
		m_WrappingObject = i_other.m_WrappingObject;
		m_referenceCount = i_other.m_referenceCount;
		(*(m_referenceCount))++;
	}

	template<typename T>
	SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T> &i_other)
	{
		if (!isEqual( i_other))
		{
			deleteObject();
			m_WrappingObject = i_other.m_WrappingObject;
			assert(m_referenceCount);
			m_referenceCount = i_other.m_referenceCount;
			(*(m_referenceCount))++;
		}
		return *(this);
	}

	/*template<typename T>
	SharedPointer<T>& SharePointer<T>::operator==(SharedPointer<T>& i_other)
	{
	}*/

	template<typename T>
	bool SharedPointer<T>::isEqual(SharedPointer<T> &i_other)
	{
		if (m_WrappingObject == i_other.m_WrappingObject)
			return true;
		return false;
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
		//assert(m_WrappingObject);
		if (!this->isNull())
			return m_WrappingObject;
		return nullptr;
	}

	template<typename T>
	bool SharedPointer<T>::deleteObject()
	{
		//assert(m_WrappingObject);
		if (!this->isNull())
		{
			if ((*m_referenceCount-1) == 0)
			{
				delete m_referenceCount;
				delete m_WrappingObject;
			}

			(*m_referenceCount)--;
			return true;
		}
		return true;
	}

	template<typename T>
	bool SharedPointer<T>::isNull()
	{
		if (m_WrappingObject == nullptr)//|| m_WrappingObject == null)
			return true;
		else return false;
	}
} //myEngine