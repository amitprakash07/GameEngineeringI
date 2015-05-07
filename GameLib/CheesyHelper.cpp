#include "CheesyHelper.h"
#include <assert.h>

namespace myEngine
{
	Cheesy::Point2D getAsCheesyDimension(float i_x, float i_y)
	{
		Cheesy::Point2D temp;
		temp.x = i_x;
		temp.y = i_y;
		return temp;
	}

	Cheesy::Point2D getAsCheesyDimension(myEngine::Vector2D i_dimension)
	{
		Cheesy::Point2D temp;
		temp.x = i_dimension.getX();
		temp.y = i_dimension.getY();
		return temp;
	}

	Cheesy::ColorRGBA getAsCheesyRGBA(float i_R, float i_G, float i_B, float i_A)
	{
		Cheesy::ColorRGBA temp;
		temp.r = static_cast<unsigned char>(i_R);
		temp.g = static_cast<unsigned char>(i_G);
		temp.b = static_cast<unsigned char>(i_B);
		temp.a = static_cast<unsigned char>(i_A);
		return temp;
	}

	Cheesy::ColorRGBA getAsCheesyRGBA(myEngine::typedefs::RGBA i_color)
	{
		Cheesy::ColorRGBA temp;
		temp.r = static_cast<unsigned char>(i_color.R);
		temp.g = static_cast<unsigned char>(i_color.G);
		temp.b = static_cast<unsigned char>(i_color.B);
		temp.a = static_cast<unsigned char>(i_color.A);
		return temp;
	}

	Cheesy::ColorRGB getAsCheesyRGB(float r, float g, float b)
	{
		Cheesy::ColorRGB temp;
		temp.r = static_cast<unsigned char>(r);
		temp.g = static_cast<unsigned char>(g);
		temp.b = static_cast<unsigned char>(b);
		return temp;
	}

	Cheesy::ColorRGB getAsCheesyRGB(myEngine::Vector3D i_color)
	{
		Cheesy::ColorRGB temp;
		temp.r = static_cast<unsigned char>(i_color.getX());
		temp.g = static_cast<unsigned char>(i_color.getY());
		temp.b = static_cast<unsigned char>(i_color.getZ());
		return temp;
	}
}