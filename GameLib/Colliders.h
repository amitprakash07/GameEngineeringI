#ifndef __COLLIDER_H
#define __COLLIDER_H

#include "additionaltypes.h"
#include "Matrix.h"
#include "HashedString.h"
#include <vector>


namespace myEngine
{
	namespace Physics
	{
		class ICollisionHandler;
		
		class Collider
		{
		public:
			Collider();
			myEngine::typedefs::BoundingBox					getBoundingBox() const;
			void											setBoundingBox(const Vector3D,const float,const float,const float);
			float											getExtendX() const;
			float											getExtendY() const;
			float											getExtendZ() const;
			void											setBoundingBoxWidth(const float);
			void											setBoundingBoxHeight(const float);
			void											setBoundingBoxDepth(const float);
			void											setBoundingBoxPosition(const Vector3D); //rarely gonna get used
			void											setBoundingBox(const myEngine::typedefs::BoundingBox);
			void											setCollisionHandler(ICollisionHandler*);
			ICollisionHandler*								getCollisionHandler();
			void											addToCollideWith(char *);
			bool											canCollideWith(char*);
						 
		private:
			myEngine::typedefs::BoundingBox					mBoundingBox;
			ICollisionHandler*								mCollisionHandler;
			std::vector<myEngine::utils::StringHash>		mCollidingCategory;
		};
	}
}//namespace myEngine


#endif