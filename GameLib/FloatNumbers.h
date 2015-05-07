#ifndef __FLOATNUMBER_H
#define __FLOATNUMBER_H

namespace myEngine{
	bool AlmostEqual2sComplement(float, float, int);
	inline bool IsInfinite(float);
	inline bool IsNan(float);
	inline int Sign(float);
	bool AlmostEqualUlpsFinal(float, float, int);
	void PrintNumber(float, int);
	void floatUnitTest();
	void swap(float&, float&);
}

#include "FloatNumber.inl"

#endif