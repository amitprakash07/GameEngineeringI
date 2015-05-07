#include "Object.h"
#include <assert.h>

namespace myEngine
{
	unsigned __int64 Object::mInstanceID = 0;

	Object::Object()
	{
		//++mInstanceID;
	}

	char* Object::getClassName()
	{
		return mClassName.getAsChar();
	}

	unsigned __int64 Object::getInstanceID()
	{
		return mInstanceID;
	}

	void Object::setClassName(char * i_name)
	{
		assert(i_name);
		mClassName = myEngine::typedefs::String(i_name);
	}


}