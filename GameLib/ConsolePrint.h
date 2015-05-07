#ifndef __CONSOLE_PRINT_H
#define __CONSOLE_PRINT_H

namespace myEngine
{
	enum LOG_LEVEL
	{
		NO_LOG = 0,
		DEBUG_LOG = 1,
		WARNING_LOG = 2,
		ERROR_LOG = 4,
		// Compare only, should not use
		DEBUG_WARNING_LOG = 3,
		DEBUG_ERROR_LOG = 5,
		WARNING_ERROR_LOG = 6,
		DEBUG_WARNING_ERROR_LOG = 7
	};

	void ConsolePrint(const LOG_LEVEL lvl, const char * i_fmt, ...);
	void ConsoleSystemName(const LOG_LEVEL lvl, const char * systemName, const char * i_fmt, ...);
	void ConsolePrintLocation(const LOG_LEVEL lvl, const char* file, const int line, const char * i_fmt, ...);
} // Namespace myEngine

// This is how we handle variable argument pre-processor macros
// This is only supported by compilers that support the C99 standard
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_PRINT)
#define DEBUG_PRINT(lvl,fmt,...) Engine::ConsolePrint((lvl),(fmt),__VA_ARGS__)
#define DEBUG_PRINT_SYSTEM(lvl,systemName,fmt,...) Engine::ConsoleSystemName((lvl),(systemName),(fmt),__VA_ARGS__)
#define DEBUG_PRINT_LOCATION(lvl,file,line,fmt,...) Engine::ConsolePrintLocation((lvl),(file),(line),(fmt),__VA_ARGS__)
#else
// This is one way we create a do nothing (NO OP) macro that doesn't
// generate a compiler warning or error
#define DEBUG_PRINT(lvl,fmt,...) void(0)
#define DEBUG_PRINT_SYSTEM(lvl,systemName,fmt,...) void(0)
#define DEBUG_PRINT_LOCATION(lvl,file,line,fmt,...) void(0)
#endif

#endif // __CONSOLE_PRINT_H