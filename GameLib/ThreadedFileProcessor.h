#ifndef __THREADED_FILE_PROCESSOR_H
#define __THREADED_FILE_PROCESSOR_H

#include <stdint.h>
#include <queue>
#include <Windows.h>
#include "Event.h"
#include "Mutex.h"
#include "Semaphore.h"
#include "LoadTask.h"


namespace myEngine
{
	class ThreadedFileProcessor
	{
	public:
		void							addToLoadQueue(LoadTask & i_LoadTask);
		static ThreadedFileProcessor&   getInstance(void);
		static bool						shutdown(void);
		static void						deleteThreadFileProcessor();

	private:
		static ThreadedFileProcessor*	m_ThreadFileProcessor;
		HANDLE							m_LoadThreadHandle; //fileLoadingThread handler
		HANDLE							m_ProcessThreadHandle; //FileProcessing Thread Handler
		ManualResetEvent				m_ShutdownRequestEvent; //Event to Manage Threads
		Semaphore						m_LoadQueueSemaphore; //For Loading File
		Mutex							m_LoadQueueMutex; //For Loading File
		Semaphore						m_ProcessQueueSemaphore; //For Processing File
		Mutex							m_ProcessQueueMutex; //For Processing File
		std::queue<LoadTask *>			m_LoadQueue;
		std::queue<LoadTaskData *>		m_ProcessQueue;
		void							addToProcessQueue(LoadTaskData & i_LoadTaskData);
		LoadTask *						getFromLoadQueue(void);
		LoadTaskData *					getFromProcessQueue(void);
		static DWORD WINAPI				loadThreadFunction(void * i_pThreadData); //Loading ThreadFunction
		static DWORD WINAPI				processThreadFunction(void * i_pThreadData); //ProcessingThread Function
		ThreadedFileProcessor(HANDLE i_LoadThreadHandle, HANDLE i_ProcessThreadHandle);
		~ThreadedFileProcessor();
	};

} // namespace Engine

#endif // __THREADED_FILE_PROCESSOR_H
