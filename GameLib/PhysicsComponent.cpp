#include "PhysicsComponent.h"


#include "FrameTime.h"
#include "SharedPointer.h"
#include "Engine.h"

namespace myEngine
{
	namespace Physics
	{
		PhysicsComponent* PhysicsComponent::init(float i_Mass = 0.05f,
			Vector3D i_Force = Vector3D(0.0f, 0.0f, 0.0f),
			float i_maxAcceleration = 20.0f,
			float i_minAcceleration = -20.0f)
		{
			if (!EngineController::GameEngine::isEngineInitialized())
			{
				EngineController::GameEngine::startGameEngine();
			}
			return (new PhysicsComponent(i_Mass, i_Force, i_maxAcceleration, i_minAcceleration));
		}

		
		PhysicsComponent::PhysicsComponent(
			float i_Mass = 10.0f,
			Vector3D i_Force = Vector3D(0.0f, 0.0f, 0.0f),
			float i_maxAcceleration = 20.0f,
			float i_minAcceleration = -20.0f) :
			mMass(i_Mass),
			mForce(i_Force),
			mMaxAcceleration(i_maxAcceleration),
			mMinAcceleration(i_minAcceleration)
		{
			mPreviousPosition = Vector3D(0.0f, 0.0f, 0.0f);
			mCurrentPosition = Vector3D(0.0f, 0.0f, 0.0f);
			mCurrentVelocity = Vector3D(0.0f, 0.0f, 0.0f);
			mCurrentdirection = Vector3D(0.0f, 0.0f, 0.0f);
		}


		//Call before calling any getters
		void PhysicsComponent::updatePhysics()
		{
			Vector3D tempPosition;
			if (!EngineController::GameEngine::isEngineInitialized())
			{
				EngineController::GameEngine::startGameEngine();
			}
			float time_diff = EngineController::GameEngine::getEngineClock()->getdeltaTime();
			tempPosition = ((mCurrentPosition * 2) - mPreviousPosition)
				+ (getAcceleration() * static_cast<float>(pow(time_diff, 2)));
			mPreviousPosition = mCurrentPosition;
			mCurrentPosition = tempPosition;
			if (!AlmostEqualUlpsFinal(time_diff, 0.0f, 2))
				mCurrentVelocity = ((mCurrentPosition - mPreviousPosition) * 0.5) / time_diff;
			else
				mCurrentVelocity = Vector3D::getZeroVector();
		}


		//Call to advance object physics component on collision
		void PhysicsComponent::updatePhysics(float i_deltaTime)
		{
			Vector3D tempPosition = ((mCurrentPosition * 2) - mPreviousPosition)
				+ (getAcceleration() * static_cast<float>(pow(i_deltaTime, 2)));
			mPreviousPosition = mCurrentPosition;
			mCurrentPosition = tempPosition;
			mCurrentVelocity = ((mCurrentPosition - mPreviousPosition) * 0.5) / i_deltaTime;
		}

		
		//Adds Force to the physics component
		void	PhysicsComponent::addForce(Vector3D i_force)
		{
			mForce = mForce + i_force;
			mCurrentdirection = mForce.getNormalizeVector();
		}


	}//namespace Physics
}//namespace myEngine