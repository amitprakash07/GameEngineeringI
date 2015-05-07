#ifndef __DETERMINANT_H
#define __DETERMINANT_H

namespace myEngine
{
	namespace Maths
	{
		inline float getDeterminant2x2(const float, const float, const float, const float);
		inline float getDeterminant3x3(
			const float, const float, const float,
			const float, const float, const float,
			const float, const float, const float);
		inline float getDerteminant4x4(
			const float, const float, const float,const float,
			const float, const float, const float, const float,
			const float, const float, const float, const float,
			const float, const float, const float, const float);

	}//namespace Maths
}//namespace myEngine

#include "Determinant.inl"
#endif
