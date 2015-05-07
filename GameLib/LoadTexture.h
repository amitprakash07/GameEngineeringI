#ifndef __LOAD_TEXTURE_H
#define __LOAD_TEXTURE_H

#include "Texture.h"

namespace myEngine
{
	namespace Rendering
	{
		class GameObjectTexture
		{
		public:
			static Cheesy::Texture * getTexture(char *);
		};
	}//Rendering
} //myEngine

#endif /*__LOAD_TEXTURE_H*/