#include <assert.h>
#include "Mutex.h"
#include "Semaphore.h"
#include "ThreadedFileProcessor.h"
#include "Engine.h"


namespace myEngine
{
	ThreadedFileProcessor * ThreadedFileProcessor::m_ThreadFileProcessor = nullptr;

	ThreadedFileProcessor::ThreadedFileProcessor(HANDLE i_LoadThreadHandle, HANDLE i_ProcessThreadHandle) :
		m_ShutdownRequestEvent("ShutdownRequestEvent", false),
		m_LoadThreadHandle(i_LoadThreadHandle),
		m_ProcessThreadHandle(i_ProcessThreadHandle),
		m_LoadQueueSemaphore("LoadQueueSemaphore", 0, 100),
		m_LoadQueueMutex("LoadQueueMutex"),
		m_ProcessQueueSemaphore("ProcessQueueSemaphore", 0, 100),
		m_ProcessQueueMutex("ProcessQueueMutex")
	{

	}

	
	void ThreadedFileProcessor::deleteThreadFileProcessor()
	{
//		MessagedAssert(m_ThreadFileProcessor != nullptr, "Thread File Process is either not instantiated or had been deleted");
		EngineController::GameEngine::isEngineInitialized() ?
			EngineController::GameEngine::getMemoryManager()->__free(m_ThreadFileProcessor) :
			delete m_ThreadFileProcessor;

		m_ThreadFileProcessor = nullptr;
	}


	
	ThreadedFileProcessor::~ThreadedFileProcessor()
	{
		while (!m_LoadQueue.empty())
		{
			LoadTask* temp = m_LoadQueue.front();
			m_LoadQueue.pop();
			delete temp;
		}

		while (!m_ProcessQueue.empty())
		{
			LoadTaskData*  temp = m_ProcessQueue.front();
			m_ProcessQueue.pop();
			delete temp;
		}
			
	}


	ThreadedFileProcessor & ThreadedFileProcessor::getInstance()
	{
		if (m_ThreadFileProcessor == NULL)
		{
			//DWORD ThreadID = 0;
			
			//LP - stands for Long Pointer - Hungarian Notation
			/*HANDLE WINAPI CreateThread(
			*	_In_opt_  LPSECURITY_ATTRIBUTES  lpThreadAttributes, - can bu NULL
			*	_In_      SIZE_T                 dwStackSize, - stack size i.e size of the stack to be used by thread for processing
			*	_In_      LPTHREAD_START_ROUTINE lpStartAddress, - address of the thread function i.e. function which thread is gonna run
			*	_In_opt_  LPVOID                 lpParameter, - optional can be NULL
			*	_In_      DWORD                  dwCreationFlags, - flag to be given while creating the thread i.e. 0 - Run Immediately
			SUSPENDED - starts when ResumeThread() gets called
			*	_Out_opt_ LPDWORD                lpThreadId - ID of the thread created
			*	);
			*/

			//Create thread in suspended mode
			HANDLE LoadThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadedFileProcessor::loadThreadFunction, NULL, CREATE_SUSPENDED, NULL);
			assert(LoadThreadHandle != NULL);

			//Create thread in suspended mode
			HANDLE ProcessThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadedFileProcessor::processThreadFunction, NULL, CREATE_SUSPENDED, NULL);
			assert(ProcessThreadHandle != NULL);

			m_ThreadFileProcessor = EngineController::GameEngine::isEngineInitialized() ? 
				new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(ThreadedFileProcessor))) ThreadedFileProcessor(LoadThreadHandle, ProcessThreadHandle) :
				new ThreadedFileProcessor(LoadThreadHandle, ProcessThreadHandle);

			//Resume Thread - will call ThreadedFileProcessor::loadThreadFunction
			ResumeThread(LoadThreadHandle);
			
			//Resume Thread - ThreadedFileProcessor::processThreadFunction
			ResumeThread(ProcessThreadHandle);
		}

		assert(m_ThreadFileProcessor != NULL);
		return *m_ThreadFileProcessor;
	}



	bool ThreadedFileProcessor::shutdown(void)
	{
		//Attempt to shutdown the thread
		if (m_ThreadFileProcessor != nullptr)
		{
				HANDLE ThreadHandles[] = { m_ThreadFileProcessor->m_LoadThreadHandle, m_ThreadFileProcessor->m_ProcessThreadHandle };
				DWORD Result = WaitForMultipleObjects(sizeof(ThreadHandles) / sizeof(ThreadHandles[0]), ThreadHandles, TRUE, INFINITE);

				m_ThreadFileProcessor->m_ShutdownRequestEvent.Signal();
				EngineController::GameEngine::isEngineInitialized() ?
					EngineController::GameEngine::getMemoryManager()->__free(m_ThreadFileProcessor) :
					delete m_ThreadFileProcessor;

				m_ThreadFileProcessor = nullptr;
				return true;
		}
		return true;		
	}

	void ThreadedFileProcessor::addToLoadQueue(LoadTask & i_LoadTask)
	{
		m_LoadQueueMutex.Lock();
		m_LoadQueue.push(&i_LoadTask);
		m_LoadQueueMutex.Release();
		m_LoadQueueSemaphore.Increment();
	}


	void ThreadedFileProcessor::addToProcessQueue(LoadTaskData & i_LoadTaskData)
	{
		m_ProcessQueueMutex.Lock();
		m_ProcessQueue.push(&i_LoadTaskData);
		m_ProcessQueueMutex.Release();
		m_ProcessQueueSemaphore.Increment();
	}


	LoadTask * ThreadedFileProcessor::getFromLoadQueue()
	{
		LoadTask * pLoadTask = nullptr;
		m_LoadQueueMutex.Lock();
		if (!m_LoadQueue.empty())
		{
			pLoadTask = m_LoadQueue.front();
			m_LoadQueue.pop();
		}
		m_LoadQueueMutex.Release();
		return pLoadTask;
	}

	
	LoadTaskData * ThreadedFileProcessor::getFromProcessQueue(void)
	{
		LoadTaskData * pLoadTaskData = nullptr;
		m_ProcessQueueMutex.Lock();
		if (!m_ProcessQueue.empty())
		{
			pLoadTaskData = m_ProcessQueue.front();
			m_ProcessQueue.pop();
		}

		m_ProcessQueueMutex.Release();
		return pLoadTaskData;
	}

	
	DWORD WINAPI ThreadedFileProcessor::loadThreadFunction(void * i_pThreadData)
	{
		//ThreadedFileProcessor & Me = ThreadedFileProcessor::getInstance();
		OVERLAPPED FileOverlapped;
		FileOverlapped.Offset = FileOverlapped.OffsetHigh = 0;

		/*
		*HANDLE WINAPI CreateEvent(
		*_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes, //If NULL - child process cannot inherit
		*_In_     BOOL                  bManualReset, //if TRUE - manual resest is required:  FALSE - system will reset automatically once the signal is sent
		*_In_     BOOL                  bInitialState, // FALSE - signal is not sent: TRUE - signal is true when event created
		*_In_opt_ LPCTSTR               lpName // name of the event object - can bu null, if name is not null and already present in the system - it will inherit other parameters from the parent event process
		*	);
		*/

		FileOverlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		HANDLE LoadHandles[] = { m_ThreadFileProcessor->m_ShutdownRequestEvent.GetHandle(), m_ThreadFileProcessor->m_LoadQueueSemaphore.GetHandle() };
		HANDLE ReadHandles[] = { m_ThreadFileProcessor->m_ShutdownRequestEvent.GetHandle(), FileOverlapped.hEvent };

		
		bool bDone = false;
		while (!bDone)
		{
			// Me.m_LoadQueueSemaphore.WaitAndDecrement();

			/*
			DWORD WINAPI WaitForMultipleObjects(
			_In_       DWORD  nCount,  // Count of handles - should not be zero
			_In_ const HANDLE *lpHandles, //array of handles to be waited for
			_In_       BOOL   bWaitAll, //TRUE - should wait for all handles to be signalled, FALSE - if any one handle is signalled wait is over
			_In_       DWORD  dwMilliseconds //TimeOUt for waiting
			);
			*/

			DWORD LQResult = WaitForMultipleObjects(sizeof(LoadHandles) / sizeof(LoadHandles[0]), LoadHandles, FALSE, INFINITE);

			if (LQResult == WAIT_OBJECT_0)
			{
				bDone = true;
			}
			else if (LQResult == WAIT_OBJECT_0 + 1)
			{
				LoadTask * pLoadTask = m_ThreadFileProcessor->getFromLoadQueue();

				if (pLoadTask)
				{
					const char * pFileName = pLoadTask->getFileName(); //To-Do
					MessagedAssert(pFileName != nullptr, "File Name is Null");

#ifdef _DEBUG
					myEngine::ConsolePrint(EngineController::GameEngine::mProperties.verbosityLvl, "Processing %s\n", pFileName);
#endif

					/*
					HANDLE WINAPI CreateFile(
					_In_     LPCTSTR               lpFileName, // file name
					_In_     DWORD                 dwDesiredAccess, // GENERIC_READ, GENERIC_WRITE
					_In_     DWORD                 dwShareMode, //sharing Mode
					_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, //optional can be NULL
					_In_     DWORD                 dwCreationDisposition, //opening mode
					_In_     DWORD                 dwFlagsAndAttributes,
					_In_opt_ HANDLE                hTemplateFile //can be NULL
					);
					*/

					HANDLE FileHandle = CreateFileA(pFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);


					if (FileHandle == INVALID_HANDLE_VALUE)
					{
#ifdef _DEBUG
						myEngine::ConsolePrint(EngineController::GameEngine::mProperties.verbosityLvl, "Error Opening File %s : %d", pLoadTask, GetLastError());
#endif
						EngineController::GameEngine::isEngineInitialized() ? 
							EngineController::GameEngine::getMemoryManager()->__free(pLoadTask) : delete pLoadTask;
					}
					else
					{
						DWORD FileSize = GetFileSize(FileHandle, NULL);
						assert(FileSize != INVALID_FILE_SIZE);

						uint8_t * pFileBuffer = new uint8_t[FileSize];
						assert(pFileBuffer != NULL);

						BOOL RFResult = ReadFile(FileHandle, pFileBuffer, FileSize, NULL, &FileOverlapped);
						if ((RFResult != TRUE) && (GetLastError() != ERROR_IO_PENDING))
						{
#ifdef _DEBUG						
							myEngine::ConsolePrint(EngineController::GameEngine::mProperties.verbosityLvl, "Failed reading %s : %d", pFileName, GetLastError());
#endif
							EngineController::GameEngine::isEngineInitialized() ?
								EngineController::GameEngine::getMemoryManager()->__free(pLoadTask) : delete pLoadTask;
						}
						else
						{
							DWORD RResult = WaitForMultipleObjects(sizeof(ReadHandles) / sizeof(ReadHandles[0]), ReadHandles, FALSE, INFINITE);

							if (RResult == WAIT_OBJECT_0) //WAIT_OBJECT_0 is the index of the first element of the handle array
							{
								CancelIo(FileHandle);
								EngineController::GameEngine::isEngineInitialized() ?
									EngineController::GameEngine::getMemoryManager()->__free(pLoadTask) : delete pLoadTask;
								bDone = true;
							}
							else if (RResult == WAIT_OBJECT_0 + 1)
							{
								DWORD BytesRead = 0;
								BOOL GORResult = GetOverlappedResult(FileHandle, &FileOverlapped, &BytesRead, FALSE);
								MessagedAssert(GORResult == TRUE, "Incomplete File IO Operation");
								LoadTaskData * pNewLoadTaskData = new LoadTaskData(pFileBuffer, BytesRead, pLoadTask);
								bDone = true;
								m_ThreadFileProcessor->addToProcessQueue(*pNewLoadTaskData);
								
							}
							
						}
					}
				}
			}
		}

		CloseHandle(FileOverlapped.hEvent);
		return 0;
	}

	DWORD WINAPI ThreadedFileProcessor::processThreadFunction(void * i_pThreadData)
	{
		//ThreadedFileProcessor & Me = ThreadedFileProcessor::getInstance();
		HANDLE WaitHandles[] = { m_ThreadFileProcessor->m_ShutdownRequestEvent.GetHandle(), m_ThreadFileProcessor->m_ProcessQueueSemaphore.GetHandle() };
		bool bDone = false;

		while (!bDone)
		{
			//Me.m_ProcessQueueSemaphore.WaitAndDecrement();
			DWORD result = WaitForMultipleObjects(sizeof(WaitHandles) / sizeof(WaitHandles[0]), WaitHandles, FALSE, INFINITE);

			if (result == WAIT_OBJECT_0)
			{
				bDone = true;
			}
			else if (result == (WAIT_OBJECT_0 + 1))
			{
				LoadTaskData * pLoadData = m_ThreadFileProcessor->getFromProcessQueue();

				if (pLoadData)
				{
					pLoadData->m_pLoadTask->getProcessFile()->processFileContents(pLoadData->m_pFileContents, pLoadData->m_FileContentsSize);
					EngineController::GameEngine::isEngineInitialized() ?
						EngineController::GameEngine::getMemoryManager()->__free(pLoadData->m_pLoadTask) : delete pLoadData->m_pLoadTask;
					delete[] pLoadData->m_pFileContents;
					delete pLoadData;
					bDone = true;
				}
			}
			else
			{
				assert(false);
			}
		}

		return 0;
	}

} // namespace Engine