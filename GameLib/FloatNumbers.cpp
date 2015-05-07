#include "FloatNumbers.h"
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>

namespace myEngine
{
	// Usable AlmostEqual function
	bool AlmostEqual2sComplement(float A, float B, int maxUlps)
	{
		// Make sure maxUlps is non-negative and small enough that the
		// default NAN won't compare as equal to anything.
		assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
		int aInt = *(int*)&A;
		// Make aInt lexicographically ordered as a twos-complement int
		if (aInt < 0)
			aInt = 0x80000000 - aInt;
		// Make bInt lexicographically ordered as a twos-complement int
		int bInt = *(int*)&B;
		if (bInt < 0)
			bInt = 0x80000000 - bInt;
		int intDiff = abs(aInt - bInt);
		if (intDiff <= maxUlps)
			return true;
		return false;
	}

	bool AlmostEqualUlpsFinal(float A, float B, int maxUlps)
	{
		if (IsInfinite(A) || IsInfinite(B))
			return A == B;

		if (IsNan(A) || IsNan(B))
			return false;

		if (Sign(A) != Sign(B))
			return A == B;

		int aInt = *(int*)&A;
		// Make aInt lexicographically ordered as a twos-complement int
		if (aInt < 0)
			aInt = 0x80000000 - aInt;
		// Make bInt lexicographically ordered as a twos-complement int
		int bInt = *(int*)&B;
		if (bInt < 0)
			bInt = 0x80000000 - bInt;

		// Now we can compare aInt and bInt to find out how far apart A and B
		// are.
		int intDiff = abs(aInt - bInt);
		if (intDiff <= maxUlps)
			return true;
		return false;
	}

	void floatUnitTest()
	{
		float garfageFloat = 0.0f;
		std::cout << "\nIs a/FLT_EPSILON is NaN??" << (IsNan(10.0f / FLT_EPSILON) ? "Yes, It is NaN" : "It is a valid number");
		assert(!IsNan(10.0f / FLT_EPSILON));
		std::cout << "\nIs sqrt(-1) is NaN ? " << (IsNan(sqrt(-1.0f)) ? "Yes, It is NaN" : "It is a valid number");
		std::cout << "\nIs 1.0f/Zero is Infinity ?" << (IsInfinite(1.0f / garfageFloat) ? " Yes it is an infinite Number" : "No it is not a infinte number");
		std::cout << "\n10.0f/EPSILON =" << 10.0f / FLT_EPSILON;
		std::cout << "\nIs 2.0f == 2.0??" << (AlmostEqualUlpsFinal(2.0f, 2.0, (int)FLT_EPSILON) ? " True" : " False");
	}

	// Function to print a number and its representation, in hex and decimal
	void PrintNumber(float f, int offset)
	{
		(*((int*)&f)) += offset;
		printf("%+1.8g,0x%08lX,%d\n", f, *(int*)&f, *(int*)&f);
	}

	void swap(float &i_A, float &i_B)
	{
		float temp;
		temp = i_A;
		i_A = i_B;
		i_B = temp;
	}
}