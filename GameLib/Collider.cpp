#include "Colliders.h"

namespace myEngine
{
	namespace Physics
	{
		Collider::Collider()
		{
			mBoundingBox.height = 0;
			mBoundingBox.width = 0;
			mBoundingBox.depth = 0;
			mBoundingBox.position = Vector3D(0, 0, 0);
			mCollidingCategory.reserve(5);
			mCollisionHandler = nullptr;
		}

		
		
		void Collider::setCollisionHandler(ICollisionHandler* i_collisionHandler)
		{
			///assert(i_collisionHandler != nullptr);
			mCollisionHandler = i_collisionHandler;
		}


		void Collider::addToCollideWith(char * i_name)
		{
			assert(!myEngine::utils::StringHash(i_name).isNil());
			mCollidingCategory.push_back(myEngine::utils::StringHash(i_name));
		}


		
		bool Collider::canCollideWith(char * i_name)
		{
			assert(!myEngine::utils::StringHash(i_name).isNil());
			for (unsigned __int16 i = 0; i < mCollidingCategory.size(); i++)
			{
				if (mCollidingCategory[i] == myEngine::utils::StringHash(i_name))
					return true;
			}
			return false;
		}



		ICollisionHandler* Collider::getCollisionHandler()
		{
			return mCollisionHandler;
		}

		
		
		myEngine::typedefs::BoundingBox Collider::getBoundingBox() const
		{
			return mBoundingBox;
		}

		
		float Collider::getExtendX() const
		{
			return (abs(mBoundingBox.width / 2));
		}

		
		float Collider::getExtendY() const
		{
			return (abs(mBoundingBox.height / 2));
		}

		
		
		float Collider::getExtendZ() const
		{
			return (abs(mBoundingBox.depth / 2));
		}

		
		
		void Collider::setBoundingBox(const Vector3D i_posiiton, const float i_width, const float i_height, const float i_depth)
		{
			mBoundingBox.position = i_posiiton;
			mBoundingBox.height = static_cast<float> (abs(i_height));
			mBoundingBox.width = static_cast<float> (abs(i_width));
			mBoundingBox.depth = static_cast<float> (abs(i_depth));
		}

		
		
		void Collider::setBoundingBoxPosition(const Vector3D i_position)
		{
			mBoundingBox.position = i_position;
		}

		
		
		
		void Collider::setBoundingBoxWidth(const float i_width)
		{
			mBoundingBox.width = static_cast<float> (abs(i_width));
		}

		
		
		void Collider::setBoundingBoxHeight(const float i_height)
		{
			mBoundingBox.height = static_cast<float> (abs(i_height));
		}

		

		void Collider::setBoundingBoxDepth(const float i_depth)
		{
			mBoundingBox.depth = static_cast<float> (abs(i_depth));
		}

		
		
		void Collider::setBoundingBox(const myEngine::typedefs::BoundingBox i_boundingBox)
		{
			mBoundingBox = i_boundingBox;
		}
	}


}