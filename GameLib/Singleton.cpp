#include "Singleton.h"

namespace myEngine
{
	template <typename T>
	T* Singleton<T>::m_WrappingObject = nullptr;

	template<typename T>
	Singleton<T>::~Singleton()
	{
		destroyObject();
	}

	template<typename T>
	T* Singleton<T>::CreateObject()
	{
		if (m_WrappingObject == nullptr)
			m_WrappingObject = new T;
		return m_WrappingObject;
	}

	template<typename T>
	void Singleton<T>::destroyObject()
	{
		if (m_WrappingObject != nullptr)
			delete m_WrappingObject;
	}
}//namespace myEngine