#ifndef __RANDOM__H
#define __RANDOM__H

#include "FloatNumbers.h"

namespace myEngine{
	inline unsigned char getRandomNumber();
	inline float RandInRange(float i_Min, float i_Max);
	inline float Clamp(float i_float, float i_clampValue);
}

#include "random.inl"

#endif