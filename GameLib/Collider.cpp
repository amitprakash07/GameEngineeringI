#include "Colliders.h"

namespace myEngine
{
	namespace Physics
	{
		BoundingBox::BoundingBox()
		{
			mBoundingBox.height = 0;
			mBoundingBox.width = 0;
			mBoundingBox.depth = 0;
			mBoundingBox.position = Vector3D(0, 0, 0);
		}

		myEngine::typedefs::BoundingBox BoundingBox::getBoundingBox() const
		{
			return mBoundingBox;
		}

		float BoundingBox::getExtendX() const
		{
			return mBoundingBox.width;
		}

		float BoundingBox::getExtendY() const
		{
			return mBoundingBox.height;
		}

		float BoundingBox::getExtendZ() const
		{
			return mBoundingBox.depth;
		}

		void BoundingBox::setBoundingBox(const Vector3D i_posiiton, const float i_width, const float i_height, const float i_depth)
		{
			mBoundingBox.position = i_posiiton;
			mBoundingBox.height = static_cast<unsigned __int16> (abs(i_height));
			mBoundingBox.width = static_cast<unsigned __int16> (abs(i_width));
			mBoundingBox.depth = static_cast<unsigned __int16> (abs(i_depth));
		}

		void BoundingBox::setBoundingBoxPosition(const Vector3D i_position)
		{
			mBoundingBox.position = i_position;
		}

		void BoundingBox::setBoundingBoxWidth(const float i_width)
		{
			mBoundingBox.width = static_cast<unsigned __int16> (abs(i_width));
		}

		void BoundingBox::setBoundingBoxHeight(const float i_height)
		{
			mBoundingBox.height = static_cast<unsigned __int16> (abs(i_height));
		}

		void BoundingBox::setBoundingBoxDepth(const float i_depth)
		{
			mBoundingBox.depth = static_cast<unsigned __int16> (abs(i_depth));
		}

		void BoundingBox::setBoundingBox(const myEngine::typedefs::BoundingBox i_boundingBox)
		{
			mBoundingBox = i_boundingBox;
		}
	}


}