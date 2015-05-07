#include "Render.h"

namespace myEngine
{
	namespace Rendering
	{
		Sprite* Sprite::init(char* i_filename, Vector3D i_position, Cheesy::Point2D i_dimension, Cheesy::ColorRGBA i_color)
		{
			assert(i_filename);
			return (new Sprite(i_filename, i_position,
				i_dimension, i_color));
		}

		Sprite::Sprite(char* i_filename, Vector3D i_position, Cheesy::Point2D i_dimension, Cheesy::ColorRGBA i_color)
		{
			filename = i_filename;
			texture = GameObjectTexture::getTexture(filename);
			assert(texture);
			dimension = i_dimension;
			color = i_color;
			UVs[0] = Cheesy::UV(0.0f, 0.0f);
			UVs[1] = Cheesy::UV(1.0f, 0.0f);
			UVs[2] = Cheesy::UV(0.0f, 1.0f);
			UVs[3] = Cheesy::UV(1.0f, 1.0f);
			offset = Cheesy::Point2D(0, 0);
			rotation = 0.0f;
		}

		void Sprite::draw(Vector3D i_position = Vector3D(0, 0, 0))
		{
			Cheesy::Point2D temp(i_position.getX(), i_position.getY());
			sprite = Cheesy::Sprite::Create
				(
				temp,
				i_position.getZ(),
				dimension,
				color,
				*texture,
				UVs
				);
			assert(sprite);
			sprite->Draw(offset, rotation);
		}

		void Sprite::draw()
		{
			draw(Vector3D(0, 0, 0));
		}
	}//Rendering
}//myEngine