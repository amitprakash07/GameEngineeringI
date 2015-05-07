#ifndef __VECTOR3D__H
#define __VECTOR3D__H

#include <iostream>

namespace myEngine
{
	class Vector3D
	{
	private:
		float																					x;
		float																					y;
		float																					z;
	public:
		Vector3D();
		Vector3D(float, float, float);
		Vector3D(Vector3D *);
		inline const float																		getX() const;
		inline const float																		getY() const;
		inline const float																		getZ() const;
		inline void																				setX(const float);
		inline void																				setY(const float);
		inline void																				setZ(const float);
		Vector3D																				operator +(const Vector3D);
		Vector3D																				operator -(const Vector3D);
		Vector3D																				operator +(const float);
		Vector3D																				operator -(const float);
		Vector3D																				operator /(const float); // To DO
		void																					operator =(const Vector3D);
		Vector3D																				operator *(const float);
		inline void																				displayVector();
		void																					setRandomVector();
		static Vector3D																			getRandomVector();
		static Vector3D																			GenerateRandomVector(Vector3D &, Vector3D &);
		void																					normalizeVector();
		Vector3D																				getNormalizeVector();
		float																					length();
		float																					dotProduct(const Vector3D);
		Vector3D																				crossProduct(const Vector3D);
		static Vector3D																			getZeroVector();
		static Vector3D																			getUnitVector();
		
	};
}

#include "Vector3D.inl"

#endif
