#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

namespace myEngine
{
	namespace utils
	{
		template<typename T>
		class Array
		{
		public:
			Array();
			void add(T&);
			void add(T&, size_t);
			void remove();
			void remove(size_t);
			void reserve(size_t);
			size_t size();
			T& operator[](size_t);

		private:
			T **mObjects;
			size_t mObjectCount;
			size_t addIndex;

			size_t findNullPosition();
			bool resize(size_t);
		};
	} // namespace utils
} //namespace myEngne

#endif //__ARRAYLIST_H