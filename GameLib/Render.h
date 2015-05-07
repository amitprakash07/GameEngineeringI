#ifndef __RENDER_H
#define __RENDER_H

#include "Cheesy.h"
#include "Sprite.h"
#include "LoadTexture.h"
#include "Vector2D.h"
#include "Vector3D.h"

namespace myEngine
{
	namespace Rendering
	{
		class Sprite
		{
		public:
			static Sprite*										init(char*,Vector3D,	Cheesy::Point2D,Cheesy::ColorRGBA);

			//setter and getters
			inline myEngine::Vector2D							getDimension();
			inline void											setDimension(myEngine::Vector2D);
			inline												Cheesy::ColorRGBA getColor();
			inline void											setColor(Cheesy::ColorRGBA);
			inline char *										getFileName();
			inline Cheesy::Point2D								getOffset();
			inline void											setOffset(Vector2D);
			inline float										getRotation();
			inline void											setRotation(float);

			//draw method
			void												draw(Vector3D);
			void												draw();
		private:
			//Cheesy::Point2D spriteCenter;
			Cheesy::Point2D										dimension;
			Cheesy::ColorRGBA									color;
			Cheesy::Texture *									texture;
			Cheesy::Sprite*										sprite;
			Cheesy::UVSet										UVs;
			char *												filename;
			Cheesy::Point2D										offset;
			float												rotation;

			//constructor
			Sprite(char*,Vector3D,Cheesy::Point2D,Cheesy::ColorRGBA);
			bool												generateSprite();
		};
	} //Rendering
} //myEngine

#include "Render.inl"

#endif /*__RENDER_H*/