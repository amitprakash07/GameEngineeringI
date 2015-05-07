namespace myEngine{
	inline bool IsInfinite(float A)
	{
		const int kInfAsInt = 0x7F800000;

		// An infinity has an exponent of 255 (shift left 23 positions) and
		// a zero mantissa. There are two infinities - positive and negative.
		if ((*(int*)&A & 0x7FFFFFFF) == kInfAsInt)
			return true;
		return false;
	}

	inline bool IsNan(float A)
	{
		// A NAN has an exponent of 255 (shifted left 23 positions) and
		// a non-zero mantissa.
		int exp = *(int*)&A & 0x7F800000;
		int mantissa = *(int*)&A & 0x007FFFFF;
		if (exp == 0x7F800000 && mantissa != 0)
			return true;
		return false;
	}

	inline int Sign(float A)
	{
		// The sign bit of a number is the high bit.
		return (*(int*)&A) & 0x80000000;
	}
}