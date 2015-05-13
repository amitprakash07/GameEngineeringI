#include "PhysicsComponent.h"
#include "FloatNumbers.h"

namespace myEngine
{
	namespace Physics
	{
		inline Vector3D PhysicsComponent::getForce()
		{
			return mForce;
		}

		inline float PhysicsComponent::getMass()
		{
			return mMass;
		}

		inline float PhysicsComponent::getMaxAcceleration()
		{
			return mMaxAcceleration;
		}

		inline float PhysicsComponent::getMinAcceleration()
		{
			return mMinAcceleration;
		}

		inline float PhysicsComponent::getMaxForceMagnitude()
		{
			return (mForce.getNormalizeVector() * (mMaxAcceleration * mMass)).length();
		}

		inline Vector3D PhysicsComponent::getAcceleration()
		{
			if (myEngine::IsNan(mForce.length()))
				return Vector3D(0.0f, 0.0f, 0.0f);
			if (myEngine::AlmostEqualUlpsFinal(abs(mForce.length()), 0.0f, 2))
				return Vector3D(0.0f, 0.0f, 0.0f);
			return(mForce * (1 / mMass));
		}

		inline void PhysicsComponent::setForce(Vector3D i_mForce)
		{
			mForce = i_mForce;
			mCurrentdirection = mForce.getNormalizeVector();
		}

		inline void PhysicsComponent::setMass(float i_mMass)
		{
			mMass = i_mMass;
		}

		inline void PhysicsComponent::setMaxAcceleration(float i_mMaxAcceleration)
		{
			mMaxAcceleration = i_mMaxAcceleration;
		}

		inline void PhysicsComponent::setMinAcceleration(float i_mMinAcceleration)
		{
			mMinAcceleration = i_mMinAcceleration;
		}

		inline void	PhysicsComponent::setPreviousPosition(Vector3D i_position)
		{
			mPreviousPosition = i_position;
		}

		inline void	PhysicsComponent::setCurrentPosition(Vector3D i_position)
		{
			mCurrentPosition = i_position;
			mPreviousPosition = i_position;
		}

		//returns current velocity - call after calling updatePhysics() to get current result
		inline Vector3D PhysicsComponent::getCurrentPosition()
		{
			return mCurrentPosition;
		}

		//returns current velocity - call after calling updatePhysics() to get current result
		inline Vector3D PhysicsComponent::getCurrentVelocity()
		{
			return mCurrentVelocity;
		}

		inline Vector3D PhysicsComponent::getCurrentDirection()
		{
			return mCurrentdirection;
		}


		inline void PhysicsComponent::setCurrentDirection(Vector3D i_direction)
		{
			mCurrentdirection = i_direction.getNormalizeVector();
			mForce = mCurrentdirection * mForce.length();
		}

		//sets the velocity - use cautiously
		inline void PhysicsComponent::setCurrentVelocity(Vector3D i_velocity)
		{
			mCurrentVelocity = i_velocity;
		}
	}//namespace Physics
}//namespace myEngine