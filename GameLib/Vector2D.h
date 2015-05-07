#ifndef __Vector2D__H
#define __Vector2D__H

#include <iostream>

namespace myEngine
{
	class Vector2D
	{
	private:
		float x;
		float y;

	public:
		Vector2D();
		Vector2D(float, float);
		Vector2D(Vector2D &);
		inline const float getX();
		inline const float getY();

		inline void setX(const float);
		inline void setY(const float);

		Vector2D operator +(const Vector2D);

		Vector2D operator -(const Vector2D);

		Vector2D operator +(const float);

		Vector2D operator -(const float);

		void operator =(const Vector2D);

		bool operator ==(const Vector2D);

		Vector2D operator *(const float);

		inline void displayVector();

		void setRandomVector();

		static Vector2D getRandomVector();

		void normalizeVector();

		//void* operator new (Vector2D);
		// operator new (Vector2D);
		//	friend istream& operator >> (istream & , Vector2D &);
		//friend ostream& operator << (ostream & , Vector2D &);
		//friend Vector2D operator - (Vector2D, Vector2D);
	};
}

#include "Vector2D.inl"

#endif
