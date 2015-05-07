#ifndef __RANDOM__H
#define __RANDOM__H

namespace myEngine{
	inline unsigned char getRandomNumber();
}

namespace myMath
{
	inline int getDigitCount(int i_num);
	inline double getRandomNumber();
	template<class T>
	T RandInRange(T i_Min, T i_Max);
}

#include "random.inl"

#endif