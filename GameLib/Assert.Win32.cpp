#include <stdio.h>
#include <Windows.h>
#include "additionaltypes.h"
#include "ConsolePrint.h"

namespace myEngine
{
	bool _MessagedAssert(const char * i_pExp, const char * i_pMessage, const char * i_pFile, unsigned int i_LineNo)
	{
		const size_t sizeMessage = 1024;
		char Message[sizeMessage];

		sprintf_s(Message, sizeMessage, "ASSERT: %s\n\nFile: %s Line: %d\n\nMessage: %s\n\nShould we try to continue ?",
			i_pExp, i_pFile, i_LineNo, i_pMessage);

		int result = MessageBoxA(NULL, Message, "Oh crap!", MB_YESNO);

		switch (result)
		{
		case IDYES:
			DEBUG_PRINT_LOCATION(myEngine::typedefs::WARNING_LOG, i_pFile, i_LineNo, "Condition: %s\n", i_pExp);
			DEBUG_PRINT(myEngine::typedefs::WARNING_LOG, "Message: %s\n", i_pMessage);
			return true;
		default:
			return false;
		}
	}

} // namespace myEngine