#include <stdarg.h>		// for va_<xxx>
#include <stdio.h>		// for vsprintf_s()
#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff
#include "ConsolePrint.h"
#include "Engine.h"

myEngine::typedefs::LOG_LEVEL myEngine::Properties::verbosityLvl = myEngine::typedefs::DEBUG_WARNING_ERROR_LOG;

namespace myEngine
{
	void ConsolePrint(const myEngine::typedefs::LOG_LEVEL lvl, const char * i_fmt, ...)
	{
		const size_t lenTemp = 256;
		char strTemp[lenTemp] = "";
		if ((myEngine::Properties::verbosityLvl & lvl) == 0)
		{
			return;
		}

		if ((myEngine::typedefs::DEBUG_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "LOG: ");
		}
		if ((myEngine::typedefs::WARNING_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "WARNING: ");
		}
		if ((myEngine::typedefs::ERROR_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "ERROR: ");
		}
		/*switch (lvl)
		{
		case DEBUG_LOG:
			strcat_s(strTemp, "LOG: ");
			break;
		case WARNING_LOG:
			strcat_s(strTemp, "WARNING: ");
			break;
		case ERROR_LOG:
			strcat_s(strTemp, "ERROR: ");
			break;
		default:
			strcat_s(strTemp, "UNDEFINED: ");
			break;
		}*/

		strcat_s(strTemp, i_fmt);

		const size_t lenOutput = lenTemp + 32;

		char strOutput[lenOutput];

		// define a variable argument list variable 
		va_list args;
	
		// initialize it. second parameter is variable immediately
		// preceeding variable arguments
		va_start(args, i_fmt);

		// (safely) print our formatted string to a char buffer
		vsprintf_s(strOutput, lenOutput, strTemp, args);

		va_end(args);

		OutputDebugStringA(strOutput);
	}

	void ConsoleSystemName(const myEngine::typedefs::LOG_LEVEL lvl, const char * systemName, const char * i_fmt, ...)
	{
		const size_t lenTemp = 256;
		char strTemp[lenTemp] = "";
		if ((myEngine::Properties::verbosityLvl & lvl) == 0)
		{
			return;
		}

		if ((myEngine::typedefs::DEBUG_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "LOG: ");
		}
		if ((myEngine::typedefs::WARNING_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "WARNING: ");
		}
		if ((myEngine::typedefs::ERROR_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "ERROR: ");
		}
		
		strcat_s(strTemp, systemName);

		strcat_s(strTemp, "\t");

		strcat_s(strTemp, i_fmt);

		const size_t lenOutput = lenTemp + 32;

		char strOutput[lenOutput];

		// define a variable argument list variable 
		va_list args;

		// initialize it. second parameter is variable immediately
		// preceeding variable arguments
		va_start(args, i_fmt);

		// (safely) print our formatted string to a char buffer
		vsprintf_s(strOutput, lenOutput, strTemp, args);

		va_end(args);

		OutputDebugStringA(strOutput);
	}

	void ConsolePrintLocation(const myEngine::typedefs::LOG_LEVEL lvl, const char* file, const int line, const char * i_fmt, ...)
	{
		const size_t lenTemp = 256 + 16;
		char strTemp[lenTemp] = "";
		if ((myEngine::Properties::verbosityLvl & lvl) == 0)
		{
			return;
		}

		if ((myEngine::typedefs::DEBUG_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "LOG: ");
		}
		if ((myEngine::typedefs::WARNING_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "WARNING: ");
		}
		if ((myEngine::typedefs::ERROR_LOG & lvl) > 0)
		{
			strcat_s(strTemp, "ERROR: ");
		}
		/*switch (lvl)
		{
		case DEBUG_LOG:
			strcat_s(strTemp, "LOG:\t");
			break;
		case WARNING_LOG:
			strcat_s(strTemp, "WARNING:\t");
			break;
		case ERROR_LOG:
			strcat_s(strTemp, "ERROR:\t");
			break;
		default:
			strcat_s(strTemp, "UNDEFINED:\t");
			break;
		}*/

		strcat_s(strTemp, file);

		char lineNum[16];
		sprintf_s(lineNum, ":\t%d ", line);

		strcat_s(strTemp, lineNum);

		strcat_s(strTemp, i_fmt);

		const size_t lenOutput = lenTemp + 32;

		char strOutput[lenOutput];

		// define a variable argument list variable 
		va_list args;

		// initialize it. second parameter is variable immediately
		// preceeding variable arguments
		va_start(args, i_fmt);

		// (safely) print our formatted string to a char buffer
		vsprintf_s(strOutput, lenOutput, strTemp, args);

		va_end(args);

		OutputDebugStringA(strOutput);
	}
} // namespace Engine