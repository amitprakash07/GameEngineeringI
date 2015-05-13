#ifndef __SCOPED_TIMER_H
#define __SCOPED_TIMER_H

#include <stdint.h>
#include "Engine.h"
#include "ConsolePrint.h"
#include "TimeHelper.h"

namespace myEngine
{
	class ScopedTimer
	{
		const char *		m_pScopeName;
		uint64_t			m_Start;

	public:
		ScopedTimer(const char * i_pName) :
			m_Start(myEngine::Timing::Clock::getCurrentTick()),
			m_pScopeName(i_pName)
		{
#if defined(_DEBUG)
			DEBUG_PRINT(EngineController::GameEngine::mProperties.verbosityLvl, "Scoped Timer %s started at Tick %lld\n", m_pScopeName ? m_pScopeName : "Unnamed", m_Start);
#endif
			assert(i_pName);
		}

		~ScopedTimer()
		{
			uint64_t end = myEngine::Timing::Clock::getCurrentTick();

#if defined(_DEBUG)
			DEBUG_PRINT(EngineController::GameEngine::mProperties.verbosityLvl, "Scoped Timer %s ended at Tick %lld ran for %fms \n", m_pScopeName ? m_pScopeName : "Unnamed", 	end, myEngine::Timing::convertToMilliSeconds(myEngine::Timing::getTimeDiff(m_Start,end)));
#endif

			EngineController::GameEngine::getProfilerSystem()->addTiming(m_pScopeName, myEngine::Timing::getTickDifference(m_Start, end));
			delete m_pScopeName;
		}

	};

}


#if defined( ENABLE_PROFILING )
#define PROFILE_CONCAT_HELPER(left, right) left##right   //this will not exactly expand the directive and will only concat __LINE__ to the __Timer rather than exact line - it's how c++ directive works
#define PROFILE_CONCAT(left, right) PROFILE_CONCAT_HELPER(left, right) //this will actually concat the __LINE__ to the __Timer 

#define PROFILE_SCOPE_BEGIN(str)	{ Profiling::ScopedTimer PROFILE_CONCAT(__Timer, __LINE__)( str );
#define PROFILE_SCOPE_END()			}

#define PROFILE_UNSCOPED(str)		Profiling::ScopedTimer PROFILE_CONCAT(__Timer, __LINE__)( str );
#define PROFILE_PRINT_RESULTS()		Profiling::g_Profiler.PrintAccumulators();
#else
#define PROFILE_SCOPE_BEGIN(str)	__noop
#define PROFILE_SCOPE_END			__noop
#define PROFILE_UNSCOPED(str)		__noop
#define PROFILE_PRINT_RESULTS()		__noop
#endif // ENABLE_PROFILING

#endif