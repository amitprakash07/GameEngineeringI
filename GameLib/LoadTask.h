#ifndef __LOAD_TASK_H
#define __LOAD_TASK_H

#include "ProcessFile.h"
#include "_assert.h"

namespace myEngine
{
	class LoadTask
	{
	public:
		const char*								getFileName();
		IFileProcessHandler*					getProcessFile();
		void									addFileProcessingHandler(IFileProcessHandler*);
		
		LoadTask(const char*);
		~LoadTask();
		
	private:
		IFileProcessHandler *					m_ProcessFile;
		const char *							m_FileName;
	};

}


namespace myEngine
{
	typedef struct _LoadTaskData
	{
		uint8_t *								m_pFileContents;
		uint32_t 								m_FileContentsSize;
		LoadTask *								m_pLoadTask;

		_LoadTaskData(uint8_t * i_pFileContents, uint32_t i_FileContentsSize, LoadTask * i_pLoadTask) :
			m_pFileContents(i_pFileContents),
			m_FileContentsSize(i_FileContentsSize),
			m_pLoadTask(i_pLoadTask)
		{
			MessagedAssert(i_pFileContents != nullptr, "FileContent is NULL");
			MessagedAssert(i_FileContentsSize > 0, "There is no content in file");
			MessagedAssert(i_pLoadTask != nullptr, "Load Task is NULL");
		}

	}LoadTaskData;
}

#endif