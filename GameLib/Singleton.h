#ifndef __SINGLETON_H
#define __SINGLETON_H

namespace myEngine
{
	template <typename T>
	class Singleton
	{
	public:
		static T* CreateObject();
		static void destroyObject();
		~Singleton();
	private:
		Singleton();
		Singleton(Singleton &T);
		Singleton* operator =(Singleton *);
		static T* m_WrappingObject;
	}; //End Singleton class
}//namespace myEngine
#endif //header guard