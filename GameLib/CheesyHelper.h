#ifndef __CHEESY_HELPER_H
#define __CHEESY_HELPER_H

#include "Cheesy.h"
#include "additionaltypes.h"
#include "Vector2D.h"
#include "Vector3D.h"


namespace myEngine
{
	Cheesy::Point2D getAsCheesyDimension(float,float);
	Cheesy::Point2D getAsCheesyDimension(myEngine::Vector2D);

	Cheesy::ColorRGBA getAsCheesyRGBA(float, float, float, float);
	Cheesy::ColorRGBA getAsCheesyRGBA(myEngine::typedefs::RGBA);

	Cheesy::ColorRGB getAsCheesyRGB(float, float, float);
	Cheesy::ColorRGB getAsCheesyRGB(myEngine::Vector3D);

}

#endif