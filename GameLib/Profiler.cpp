#include "Profiler.h"
#include "TimeHelper.h"
#include "HeapManager.h"
#include "_assert.h"

namespace EngineController
{
	class GameEngine
	{
	public:
		static bool isEngineInitialized();
		static MemoryManagement::MemoryManager* getMemoryManager();
	};
}

namespace myEngine
{
	Profiler*	Profiler::mProfiler = nullptr;

	Profiler* Profiler::getProfiler()
	{
		if (mProfiler = nullptr)
		{
			mProfiler = EngineController::GameEngine::isEngineInitialized() ?
				new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(Profiler))) Profiler() :
				new Profiler();
		}

		return mProfiler;
	}


	void Profiler::deleteProfiler()
	{
		MessagedAssert(mProfiler != nullptr, "Either Profiler system is not instantiated or had been deleted");
		EngineController::GameEngine::isEngineInitialized() ?
			EngineController::GameEngine::getMemoryManager()->__free(mProfiler) :
			delete mProfiler;
	}


	Profiler::~Profiler()
	{
		while (s_Accumulators.size() != 0)
			s_Accumulators.erase(s_Accumulators.begin());
	}

	Profiler::Profiler()
	{
	
	}


	void Profiler::addTiming(const char * i_pName, unsigned int i_MS)
	{
		myEngine::typedefs::Accumulator & myAccumulator = s_Accumulators[const_cast<char*>(i_pName)];

		if (i_MS < myAccumulator.m_Min)
			myAccumulator.m_Min = i_MS;
		if (i_MS > myAccumulator.m_Max)
			myAccumulator.m_Max = i_MS;

		myAccumulator.m_Count++;
		myAccumulator.m_Sum += i_MS;
	}

	void Profiler::PrintAccumulators()
	{
		std::map<char*, myEngine::typedefs::Accumulator>::iterator iter = s_Accumulators.begin();

		for (iter; iter != s_Accumulators.end(); ++iter)
		{
			float AverageTicks = iter->second.m_Count ? ((float)iter->second.m_Sum) / iter->second.m_Count : 0.0f;
			float AverageMS = iter->second.m_Count ? myEngine::Timing::convertToMilliSeconds(iter->second.m_Sum / iter->second.m_Count) : 0.0f;
			/*
#ifdef _DEBUG
			DEBUG_PRINT(EngineController::GameEngine::mProperties.verbosityLvl, "[%s] Count: %d\n", iter->first.c_str(), iter->second.m_Count);
			printf(" -- Ticks: Sum: %d Min: %d Max: %d Ave: %f\n", iter->second.m_Sum, iter->second.m_Min, iter->second.m_Max, AverageTicks);
			printf(" --    ms: Sum: %f Min: %f Max: %f Ave: %f\n", Timer::TicksToMS(iter->second.m_Sum), Timer::TicksToMS(iter->second.m_Min), Timer::TicksToMS(iter->second.m_Max), AverageMS);
#endif*/
		}
	}

};