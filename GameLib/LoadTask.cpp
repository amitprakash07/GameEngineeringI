#include "_assert.h"
#include "LoadTask.h"
#include <iostream>

namespace myEngine
{	
	LoadTask::LoadTask(const char* i_filename)
	{
		MessagedAssert(i_filename != nullptr, "File Name is NULL");
		m_FileName = _strdup(i_filename);
		m_ProcessFile = nullptr;
	}

	const char* LoadTask::getFileName()
	{
		return m_FileName;
	}

	IFileProcessHandler* LoadTask::getProcessFile()
	{
		return m_ProcessFile;
	}

	void LoadTask::addFileProcessingHandler(IFileProcessHandler* i_process)
	{
		MessagedAssert(i_process != nullptr, "File Processing Handler is Null");
		m_ProcessFile = i_process;
	}

	LoadTask::~LoadTask()
	{
		if (m_FileName != nullptr)
		{
			delete m_FileName;
			m_FileName = nullptr;
		}

		if (m_ProcessFile != nullptr)
		{
			delete m_ProcessFile;
			m_ProcessFile = nullptr;
		}
			

	}
}

