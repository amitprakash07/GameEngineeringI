#include <stdlib.h>
#include <math.h>




namespace myEngine
{
	inline unsigned char getRandomNumber()
	{
		return ((unsigned char)rand());
	}

	inline float RandInRange(float i_min, float i_max)
	{
		return (static_cast<float> ((rand() / (RAND_MAX + 1)) * (i_max - i_min) + i_min));
	}

	inline float Clamp(float i_float, float i_clampValue)
	{
		if (i_float < 0)
		{
			if (abs((float)i_float) > i_clampValue)
				return (-1 * i_clampValue);
			return i_float;
		}
		else if (i_float > 0)
		{
			if (i_float > i_clampValue)
				return i_clampValue;
			return i_float;
		}
		else return 0.0f;
	}

}