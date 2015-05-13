#ifndef __PHYSICS_COMPONENT_H
#define __PHYSICS_COMPONENT_H

#include "Vector3D.h"


namespace myEngine
{
	namespace Physics
	{
		class PhysicsComponent
		{
		public:
			//Initialize Physics Component
			static PhysicsComponent* init(float, Vector3D, float, float);
			static bool isPhysicsClockInitialized();

			//getters
			inline Vector3D									getForce();
			inline float									getMass();
			inline float									getMaxAcceleration();
			inline float									getMinAcceleration();
			inline float									getMaxForceMagnitude();
			inline Vector3D									getAcceleration();
			inline Vector3D									getCurrentPosition();
			inline Vector3D									getCurrentVelocity();
			inline Vector3D									getCurrentDirection();
			
			
			//setters
			inline void										setForce(Vector3D);
			inline void										setMass(float);
			inline void										setMaxAcceleration(float);
			inline void										setMinAcceleration(float);
			inline void										setPreviousPosition(Vector3D);
			inline void										setCurrentPosition(Vector3D);
			inline void										setCurrentVelocity(Vector3D);
			inline void										setCurrentDirection(Vector3D);
			void											updatePhysics();
			void											updatePhysics(float);
			//functionalities
			void											addForce(Vector3D);
			
			


		private:
			float											mMass;
			Vector3D										mForce;
			Vector3D										mPreviousPosition;
			Vector3D										mCurrentPosition;
			Vector3D										mCurrentVelocity;
			Vector3D										mCurrentdirection;
			float											mMaxAcceleration;
			float											mMinAcceleration;
						
			//Constructors
			PhysicsComponent(float, Vector3D, float, float);
						
		}; //PhysicsComponent
	} //namespace Physics
}//namespace myEngine

#include "PhysicsComponent.inl"

#endif //__PHYSICS_COMPONENT_H