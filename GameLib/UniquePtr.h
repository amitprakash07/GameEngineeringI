#ifndef __UNIQUE_PTR
#define __UNIQUE_PTR


namespace myEngine
{
	template<typename T>
	class UniquePtr
	{
	public:
		//static T* CreateObject();
		UniquePtr();
		bool deleteObject();
		~UniquePtr();
		UniquePtr(UniquePtr &);
		UniquePtr& operator=(UniquePtr &);
		T& operator*();
		T* operator->();
	private:

		T* m_WrappingObject;
	}; //UniquePtr
}// namespace myEngine
#endif //header guard