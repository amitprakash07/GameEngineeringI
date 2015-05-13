#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#define MAX_NAME_SIZE 30

#include "Vector3D.h"
#include "PhysicsComponent.h"
#include "Render.h"
#include "IGameObjectController.h"
#include "LuaStructure.h"
#include "Colliders.h"
#include "Matrix.h"
#include "random.h"

namespace myEngine
{
	class GameObject
	{
	public:
		static SharedPointer<GameObject>										CreateGameObject(Vector3D);
		static SharedPointer<GameObject>										CreateGameObject(LuaUtilityHelper::LuaActor);
		inline Vector3D															getPosition();
		inline void																setPosition(const Vector3D);
		inline void																setRandomPosition();
		inline Vector3D															getDirection();
		inline void																setDirection(const Vector3D);
		inline float															getSpeed();
		inline void																setSpeed(const float);
		inline Vector3D															getVelocity();
		inline void																setVelocity(Vector3D &);
		inline const char *														getName();
		inline void																setName(char *);
		void																	resetGameObject();
		inline bool																Movable();
		inline bool																isAlive();
		inline void																displayPosition();
		void																	operator = (SharedPointer<GameObject>&);
		void																	updatePosition();
		void																	updateVelocity();
		void																	setRandomDirection();
		void																	initializeSprite(char* i_filename, Cheesy::Point2D i_dimension, Cheesy::ColorRGBA i_color);
		char*																	getType();
		void																	initializePhysicsComponent();
		myEngine::Rendering::Sprite *											getSprite();
		myEngine::Physics::PhysicsComponent*									getPhysicsComponent();
		bool																	isRenderable();
		myEngine::IGameObjectController*										getGameObjectController();
		void																	setGameObjectController(myEngine::IGameObjectController*);
		inline bool																isPhysicsObject();
		inline void																setPhysicsObject(bool);
		inline void																updateGameObject();
		myEngine::Matrix4x4														getTranslationMatrix();
		myEngine::Matrix4x4														getPositionMatrix();
		Vector3D																getTransformedExtents(SharedPointer<GameObject>);
		myEngine::Physics::Collider*											getCollider();
		myEngine::typedefs::BoundingBox											getCollisionBoundingBox();
		bool																	separationAxisTest(SharedPointer<GameObject>, float&,float&, myEngine::typedefs::Axis&);
		Vector3D																getTranslatedPosition(Vector3D);
		bool																	isCollidable();
		void																	updateGameObject(float);
				
		
		~GameObject();

	private:
		//Constructor
		GameObject();
		GameObject(Vector3D);
		GameObject(SharedPointer<GameObject>&);
		void																	initializeBoundingBox();
		
		IGameObjectController *													mGameObjectController;
		char *																	name;
		char *																	type;
		bool																	isMovable;
		bool																	isDead;
		bool																	collidable;
		//Rendering
		bool																	renderable;
		myEngine::Rendering::Sprite *											mSprite;

		//Physics
		bool																	physicsObject;
		myEngine::Physics::PhysicsComponent *									physicsComponent;
		myEngine::Physics::Collider*											mCollidingBox;
		
	};
}

#include "GameObject.inl"

#endif
