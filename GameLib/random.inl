#include <stdlib.h>
#include <time.h>

namespace myMath
{
	inline int getDigitCount(int i_num)
	{
		int temp = i_num;
		int count = 0;
		while ((int)temp / 10 != 0)
		{
			++count;
			temp /= 10;
		}
		return ++count;
	}

	inline double getRandomNumber()
	{
		//srand(time(NULL));
		double realNum = rand();
		int count = getDigitCount(static_cast<int>(realNum));
		while (count != 0)
		{
			realNum = realNum / 10;
			--count;
		}
		return realNum;
	}

	template<class T>
	T RandInRange(T i_Min, T i_Max)
	{
		if (static_cast<int>(i_Min) == static_cast<int>(i_Max)) return (static_cast<T>(i_Max));
		double randomNumber = myMath::getRandomNumber();
		int count = myMath::getDigitCount(static_cast<int>(i_Max));
		T max = i_Max;
		T min = i_Min;
		while (count != 0)
		{
			randomNumber *= 10;
			--count;
		}
		if (static_cast<T> (randomNumber) > max) randomNumber -= max;
		if (static_cast<T> (randomNumber) < min) randomNumber += min;

		return (static_cast<T>(randomNumber));
	}
}

namespace myEngine
{
	inline unsigned char getRandomNumber()
	{
		return ((unsigned char)rand());
	}
}