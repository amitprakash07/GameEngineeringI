#ifndef __PROFILER_H
#define __PROFILER_H

#include <map>
#include "additionaltypes.h"


namespace myEngine
{
	class Profiler
	{
	public:
		static Profiler* getProfiler();
		static void deleteProfiler();
		void addTiming(const char * i_pName, unsigned int i_MS);
		void PrintAccumulators();
	private:
		static Profiler*	mProfiler;
		std::map<char*, myEngine::typedefs::Accumulator> s_Accumulators;
		Profiler();
		~Profiler();
	};
	//extern Profiler g_Profiler;
}


#endif // __PROFILER_H