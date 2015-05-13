#ifndef __LOAD_FILE_H
#define __LOAD_FILE_H

#include "ProcessFile.h"

namespace myEngine
{
	class LoadFile: public myEngine::IFileProcessHandler
	{
	public:
		void processFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes) override;
		~LoadFile(){}
	};
}


#endif