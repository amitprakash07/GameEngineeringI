#include "LoadTexture.h"
#include <assert.h>
#include "Sprite.h"
#include <stdio.h>

namespace myEngine
{
	namespace Rendering
	{
		Cheesy::Texture* GameObjectTexture::getTexture(char * textureFile)
		{
			assert(textureFile);

			assert(textureFile != NULL);

			FILE * pFile = NULL;

			errno_t fopenError = fopen_s(&pFile, textureFile, "rb");
			if (fopenError != 0)
				return NULL;

			assert(pFile != NULL);

			int FileIOError = fseek(pFile, 0, SEEK_END);
			assert(FileIOError == 0);

			long FileSize = ftell(pFile);
			assert(FileSize >= 0);

			FileIOError = fseek(pFile, 0, SEEK_SET);
			assert(FileIOError == 0);

			char * pBuffer = new char[FileSize];
			assert(pBuffer);

			long FileRead = fread(pBuffer, 1, FileSize, pFile);
			assert(FileRead == FileSize);

			fclose(pFile);

			Cheesy::Texture * pTexture = Cheesy::Texture::CreateFromData(pBuffer, FileSize);

			delete[] pBuffer;

			return pTexture;
		}
	}//Rendering
}//myEngine