#ifndef __ADD_TYPES_H
#define __ADD_TYPES_H

#include "Vector3D.h"

namespace myEngine
{
	namespace typedefs
	{
		enum _Alignment
		{
			ALIGNMENT_2 = 2,
			ALIGNMENT_4 = 4,
			ALIGNMENT_8 = 8,
			ALIGNMENT_16 = 16,
			ALIGNMENT_32 = 32,
			ALIGNMENT_64
		};
		typedef _Alignment Alignment;

		struct _String
		{
			char *mString;
			size_t mStringLength;// = strlen(mString);

			_String()
			{
				mString = nullptr;
				mStringLength = 0;
			}

			_String(char * i_char)
			{
				mString = i_char;
				mStringLength = strlen(mString);
			}
			
			char * getAsChar()
			{
				return mString;
			}

			size_t getLength()
			{
				return mStringLength;
			}
		};
		typedef _String String;

		

		struct _boundingbox
		{
			Vector3D position;
			unsigned __int16 width;
			unsigned __int16 height;
			unsigned __int16 depth;
		};
		typedef _boundingbox BoundingBox;

		struct _RGBA
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
		typedef _RGBA RGBA;

		enum __MatrixMajor
		{
			COLUMN_MAJOR = 0,
			ROW_MAJOR = 1
		};
		typedef __MatrixMajor MatrixMajor;
	}//namespace typedefs
}//namespace myEngine

#endif //__TYPES_H
