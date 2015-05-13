#ifndef __PROCESS_FILE_H
#define __PROCESS_FILE_H

#include <stdint.h>

namespace myEngine
{
	class IFileProcessHandler
	{
	public:
		virtual void			processFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes) = 0;
		IFileProcessHandler(){};
		virtual ~IFileProcessHandler(){};
	};
}


#endif