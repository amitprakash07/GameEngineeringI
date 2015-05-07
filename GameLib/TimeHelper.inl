#include "TimeHelper.h"

namespace myEngine
{
	namespace Time
	{
		inline uint64_t convertToMilliSeconds(const uint64_t i_seconds)
		{
			return (i_seconds * 1000);
		}

		inline uint64_t convertToSeconds(const uint64_t i_milliseconds)
		{
			return (i_milliseconds / 1000);
		}

		inline uint32_t getTimeDiff(uint64_t startTick, uint64_t endTick)
		{
			return static_cast<uint32_t>((endTick - startTick));
		}
	}//namespace Time
}//namespcae myEngine