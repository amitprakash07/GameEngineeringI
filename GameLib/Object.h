#ifndef __OBJECT_H
#define __OBJECT_H

#include "additionaltypes.h"

namespace myEngine
{
	/**<Summary>
	*This class is to keep track of all classes and unique instance IDs for each object instantiation
	*Inherit this to all classes but make sure don't include to the classes which are inheritating from other classes or interface
	* </Summary>
	*/
	class Object
	{
	public:
		unsigned __int64					getInstanceID() ;
		char *								getClassName() ;
		void								setClassName(char*); //Assign the class name in the definition
		Object();
	

	private:
		static unsigned __int64				mInstanceID;
		myEngine::typedefs::String			mClassName;
				
	};
}//namespace myEngine
#endif