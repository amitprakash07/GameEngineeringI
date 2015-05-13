#ifndef __CONSOLE_PRINT_H
#define __CONSOLE_PRINT_H
#include "additionaltypes.h"

namespace myEngine
{
	void ConsolePrint(const myEngine::typedefs::LOG_LEVEL lvl, const char * i_fmt, ... );
	void ConsoleSystemName(const myEngine::typedefs::LOG_LEVEL lvl, const char * systemName, const char * i_fmt, ...);
	void ConsolePrintLocation(const myEngine::typedefs::LOG_LEVEL lvl, const char* file, const int line, const char * i_fmt, ...);

} // Namespace Azra

// This is how we handle variable argument pre-processor macros
// This is only supported by compilers that support the C99 standard
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_PRINT)
#define DEBUG_PRINT(lvl,fmt,...) myEngine::ConsolePrint((lvl),(fmt),__VA_ARGS__)
#define DEBUG_PRINT_SYSTEM(lvl,systemName,fmt,...) myEngine::ConsoleSystemName((lvl),(systemName),(fmt),__VA_ARGS__)
#define DEBUG_PRINT_LOCATION(lvl,file,line,fmt,...) myEngine::ConsolePrintLocation((lvl),(file),(line),(fmt),__VA_ARGS__)
#else
// This is one way we create a do nothing (NO OP) macro that doesn't
// generate a compiler warning or error
#define DEBUG_PRINT(lvl,fmt,...) void(0)
#define DEBUG_PRINT_SYSTEM(lvl,systemName,fmt,...) void(0)
#define DEBUG_PRINT_LOCATION(lvl,file,line,fmt,...) void(0)
#endif


#endif // __CONSOLE_PRINT_H