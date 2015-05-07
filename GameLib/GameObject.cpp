#include "GameObject.h"
#include "CheesyHelper.h"
#include "HashedString.h"
#include "FloatNumbers.h"
#include "Engine.h"

namespace myEngine
{
	namespace Rendering
	{
		class Sprite;
	}

}

namespace myEngine
{
	
	//Public - getTranslation Matrix to translate other objects in calling gameObject coordinate system
	myEngine::Matrix4x4 GameObject::getTranslationMatrix()
	{
		Matrix4x4 translationMatrix = getPositionMatrix();
		translationMatrix.invert();
		return(translationMatrix);
	}

	/**<Summary>
	* This will return 4x4 Matrix of Position of GameObject in World
	* </Summary>
	*/
	myEngine::Matrix4x4 GameObject::getPositionMatrix()
	{
		return (myEngine::Matrix4x4::getTranslationMatrix(position, myEngine::typedefs::COLUMN_MAJOR));
	}
	
	/**<Summary> 
	* Calculate the extent of the passed GamedObject 
	* in the calling GameObject Coordinate System
	* </Summary>
	*/
	Vector3D GameObject::getTransformedExtents(SharedPointer<GameObject> i_other)
	{
		Vector3D i_otherExtentInThis;
		Matrix4x4 i_otherCentrePositionInThis = getTranslationMatrix() * i_other->getPositionMatrix();


		//Tranforming the Extents coordinate of passed gameObject in calling gameObject coordinate system
		Vector3D i_otherXExtentPositionInThis = getTranslationMatrix() * Vector3D(i_other->mCollidingBox->getExtendX(), 0, 0);
		Vector3D i_otherYExtentPositionInThis = getTranslationMatrix() * Vector3D(0, i_other->mCollidingBox->getExtendY(), 0);
		Vector3D i_otherZExtentPositionInThis = getTranslationMatrix() * Vector3D(0, 0, i_other->mCollidingBox->getExtendZ());

		//Creating the passed gameObject extent Vectors in calling gameObject coordinate system
		i_otherExtentInThis.setX(
			i_otherXExtentPositionInThis.dotProduct(Vector3D(1.0f, 0.0f, 0.0f)) +
			i_otherYExtentPositionInThis.dotProduct(Vector3D(1.0f, 0.0f, 0.0f)) +
			i_otherZExtentPositionInThis.dotProduct(Vector3D(1.0f, 0.0f, 0.0f))
			);

		i_otherExtentInThis.setY(
			i_otherXExtentPositionInThis.dotProduct(Vector3D(0.0f, 1.0f, 0.0f)) +
			i_otherYExtentPositionInThis.dotProduct(Vector3D(0.0f, 1.0f, 0.0f)) +
			i_otherZExtentPositionInThis.dotProduct(Vector3D(0.0f, 1.0f, 0.0f))
			);

		i_otherExtentInThis.setZ(
			i_otherXExtentPositionInThis.dotProduct(Vector3D(0.0f, 0.0f, 1.0f)) +
			i_otherYExtentPositionInThis.dotProduct(Vector3D(0.0f, 0.0f, 1.0f)) +
			i_otherZExtentPositionInThis.dotProduct(Vector3D(0.0f, 0.0f, 1.0f))
			);

		//returning the extent of passed gameObject in calling gameObject coordinate system
		return i_otherExtentInThis;
	}

	/**
	*<Summary>
	* Returns translated passed position in calling GameObject Coorinate system
	*</Summary>
	*/
	Vector3D GameObject::getTranslatedPosition(Vector3D i_position)
	{
		return((getTranslationMatrix()* Matrix4x4(i_position)).getPositionFromMatrix4x4());
	}

	
	
	
	/**
	*<summary>
	* Check separation Axis test between passed GameObject(A) and calling GameObject(B)
	* You may need to call it twice - for checking collision of B in A's coordinate system
	*</Summary>
	*/
	bool GameObject::separationAxisTest(SharedPointer<GameObject> i_other, float& o_collisionTime, float & o_separationTime) //Move to Collsion System to make it better - To-Do
	{
		bool isColliding = false;
		
		float tCollisionInX = 0.0f;
		float tSeparationInX = 0.0f;
		float tCollisionInY = 0.0f;
		float tSeparationInY = 0.0f;
		float tCollisionInZ = 0.0f;
		float tSeparationInZ = 0.0f;

		//Position of other GameObject in this
		Vector3D i_otherCenterPositionInThis = getTranslatedPosition(i_other->position);

		//Extent of other gameObject in this
		Vector3D i_otherExtentInThis = getTransformedExtents(i_other);

		//Transformed velocity of calling gamobject in its own coordiante system
		Vector3D thisVelocityInThis = getTranslationMatrix() * i_other->physicsComponent->getCurrentVelocity();

		//Velocity of other GameObject in calling gameObject coordinate system
		Vector3D i_otherVelocityInThis = getTranslationMatrix() * i_other->physicsComponent->getCurrentVelocity();

		//Relative velocity of other gamObject in freezed gameObject coordinate system i.e. in calling gameObject coordiante system
		Vector3D i_otherChangedVelocityInThis = i_otherVelocityInThis - thisVelocityInThis;

		//Expanding the extents of calling gameObject
		float thisChangedXExtent = getCollisionBoundingBox()->getExtendX() + i_otherExtentInThis.getX();
		float thisChangedYExtent = getCollisionBoundingBox()->getExtendY() + i_otherExtentInThis.getY();
		float thisChangedZExtent = getCollisionBoundingBox()->getExtendZ() + i_otherExtentInThis.getZ();

		//Swept collision for each axes

		//Checking in X-Axis
		switch (i_otherCenterPositionInThis.getX() >= 0)
		{
		case true:
			if (i_otherCenterPositionInThis.getX() <= thisChangedXExtent)
			{
				//To-Do - time of collision - Done but need testing
				if (i_otherChangedVelocityInThis.getX() != 0)
				{
					tCollisionInX = ((0 + thisChangedXExtent) - i_otherCenterPositionInThis.getX()) / i_otherChangedVelocityInThis.getX();
					tSeparationInX = (i_otherCenterPositionInThis.getX() - (0 - thisChangedXExtent)) / i_otherChangedVelocityInThis.getX();
					o_collisionTime = tCollisionInX;
					o_separationTime = tSeparationInX;
				}
			}
			else return false;
			break;
		case false:
			if (abs(i_otherCenterPositionInThis.getX()) <= thisChangedXExtent)
			{
				//To-Do - time of collision - Done but need testing
				if (i_otherChangedVelocityInThis.getX() != 0)
				{
					tCollisionInX = (i_otherCenterPositionInThis.getX() - (0 - thisChangedXExtent)) / i_otherChangedVelocityInThis.getX();
					tSeparationInX = ((0 + thisChangedXExtent) - i_otherCenterPositionInThis.getX()) / i_otherChangedVelocityInThis.getX();
					o_collisionTime = tCollisionInX;
					o_separationTime = tSeparationInX;
				}				
			}
			else return false;
			break;
		}


		//Check in Y-axis in case X-Axis collision is true
		switch (i_otherCenterPositionInThis.getY() >= 0)
		{
		case true:
			if (i_otherCenterPositionInThis.getY() <= thisChangedYExtent)
			{
				//To-Do - time of collision -Done but need testing
				if (i_otherChangedVelocityInThis.getY() != 0)
				{
					tCollisionInY = ((0 + thisChangedYExtent) - i_otherCenterPositionInThis.getY()) / i_otherChangedVelocityInThis.getY();
					tSeparationInY = (i_otherCenterPositionInThis.getY() - (0 - thisChangedYExtent)) / i_otherChangedVelocityInThis.getY();
					
					if (tCollisionInY < o_collisionTime)
						o_collisionTime = tCollisionInY;
					if (tSeparationInY > o_separationTime)
						o_separationTime = tSeparationInY;
				}
			}
			else return false;
			break;
		case false:
			if (abs(i_otherCenterPositionInThis.getY()) <= thisChangedYExtent)
			{
				//To-Do - time of collision - Done but need testing
				if (i_otherChangedVelocityInThis.getY() != 0)
				{
					tCollisionInY = (i_otherCenterPositionInThis.getY() - (0 - thisChangedYExtent)) / i_otherChangedVelocityInThis.getY();
					tSeparationInY = ((0 + thisChangedYExtent) - i_otherCenterPositionInThis.getY()) / i_otherChangedVelocityInThis.getY();
					
					if (tCollisionInY < o_collisionTime)
						o_collisionTime = tCollisionInY;
					if (tSeparationInY > o_separationTime)
						o_separationTime = tSeparationInY;
				}
			}
			else return false;
			break;
		}


		//Check in Z-axis in case X-Axis and Y-Axis collision is true
		switch (i_otherCenterPositionInThis.getZ() >= 0)
		{
		case true:
			if (i_otherCenterPositionInThis.getZ() <= thisChangedZExtent)
			{
				//To-Do - time of collision - Done but need testing
				if (i_otherChangedVelocityInThis.getZ() != 0)
				{
					tCollisionInZ = ((0 + thisChangedZExtent) - i_otherCenterPositionInThis.getZ()) / i_otherChangedVelocityInThis.getZ();
					tSeparationInZ = (i_otherCenterPositionInThis.getZ() - (0 - thisChangedZExtent)) / i_otherChangedVelocityInThis.getZ();

					if (tCollisionInY < o_collisionTime)
						o_collisionTime = tCollisionInY;
					if (tSeparationInY > o_separationTime)
						o_separationTime = tSeparationInY;
				}
			}
			else return false;
			break;
		case false:
			if (abs(i_otherCenterPositionInThis.getZ()) <= thisChangedZExtent)
			{
				//To-Do - time of collision - Done but need testing
				if (i_otherChangedVelocityInThis.getZ() != 0)
				{
					tCollisionInZ = (i_otherCenterPositionInThis.getZ() - (0 - thisChangedZExtent)) / i_otherChangedVelocityInThis.getZ();
					tSeparationInZ = ((0 + thisChangedZExtent) - i_otherCenterPositionInThis.getZ()) / i_otherChangedVelocityInThis.getZ();

					if (tCollisionInY < o_collisionTime)
						o_collisionTime = tCollisionInY;
					if (tSeparationInY > o_separationTime)
						o_separationTime = tSeparationInY;
				}
			}
			else return false;
			break;
		}

		
		//returning if all if's are false i.e. collsion occured in this coordinate system
		return true;
	}

	
	
	
	myEngine::Physics::BoundingBox* GameObject::getCollisionBoundingBox()
	{
		return mCollidingBox;
	}

	//static CreateGameoBject function
	SharedPointer<GameObject> GameObject::CreateGameObject(Vector3D i_position)
	{
		return (SharedPointer<GameObject>(new GameObject(i_position)));
	}


	//To create GameObjects using Lua file generated LuaActors
	SharedPointer<GameObject> GameObject::CreateGameObject(LuaUtilityHelper::LuaActor i_luaActor)
	{
		SharedPointer<GameObject> temp = CreateGameObject(i_luaActor.position);
		temp->setName(i_luaActor.name);
		temp->setGameObjectController(EngineController::GameEngine::getGameObjectController(EngineController::GameEngine::getStringPool()->findString(i_luaActor.gameController)));
		temp->getPhysicsComponent()->setMaxAcceleration(i_luaActor.velocity.length());
		temp->getPhysicsComponent()->setMass(i_luaActor.mass);
		temp->getCollisionBoundingBox()->setBoundingBox(i_luaActor.collisionBox);
		temp->type = i_luaActor.category;

		//Ask -- only this value is not able to read from Lua file
		if (myEngine::utils::StringHash(i_luaActor.category) == myEngine::utils::StringHash( "Player"))
		{
			temp->initializeSprite(myEngine::World::getWorld()->getGameConfiguration().playerTexture,
				myEngine::getAsCheesyDimension(i_luaActor.spriteSize.getX(), i_luaActor.spriteSize.getY()),
				myEngine::getAsCheesyRGBA(i_luaActor.color));

		}
		else 
			temp->initializeSprite(myEngine::World::getWorld()->getGameConfiguration().monsterTexture,
			myEngine::getAsCheesyDimension(i_luaActor.spriteSize.getX(), i_luaActor.spriteSize.getY()),
			myEngine::getAsCheesyRGBA(i_luaActor.color));

		return temp;
	}


	//private - default constructor
	GameObject::GameObject() :
		position(Vector3D(0, 0, 0)),
		direction(Vector3D(0, 0, 0)),
		speed(10.0f),
		isMovable(false),
		isDead(false),
		renderable(true),
		physicsObject(false),
		collidable(false),
		physicsComponent(nullptr),
		mSprite(nullptr),
		mGameObjectController(nullptr),
		mCollidingBox(nullptr)
	{
		name = _strdup('\0');
		velocity = direction * speed;
		initializePhysicsComponent();
		initializeBoundingBox();
	}


	//private - parameterized constructor
	GameObject::GameObject(Vector3D i_position) :
		position(i_position),
		direction(Vector3D(0, 0, 0)),
		speed(10.0f),
		isMovable(false),
		isDead(false),
		collidable(false),
		renderable(true),
		physicsObject(false),
		mSprite(nullptr),
		physicsComponent(nullptr),
		mGameObjectController(nullptr),
		mCollidingBox(nullptr)
	{
		name = _strdup('\0');
		velocity = direction * speed;
		initializePhysicsComponent();
		initializeBoundingBox();

	}



	//private - copy constructor
	GameObject::GameObject(SharedPointer<GameObject>& i_gameObject)
	{
		position = i_gameObject->position;
		direction = i_gameObject->direction;
		speed = i_gameObject->speed;
		isMovable = i_gameObject->isMovable;
		isDead = i_gameObject->isDead;
		collidable = i_gameObject->collidable;
		name = _strdup(i_gameObject->name);
		velocity = i_gameObject->velocity;
		renderable = i_gameObject->renderable;
		mSprite = i_gameObject->mSprite;
		physicsComponent = i_gameObject->physicsComponent;
		physicsObject = i_gameObject->physicsObject;
		mCollidingBox = i_gameObject->mCollidingBox;
		mGameObjectController = i_gameObject->mGameObjectController;
	}


	//destructor
	GameObject::~GameObject()
	{
		free(name);
	}


	bool GameObject::isCollidable()
	{
		return collidable;
	}


	//Assignment Operator
	void GameObject::operator = (myEngine::SharedPointer<GameObject>& i_gameObject)
	{
		position = i_gameObject->position;
		direction = i_gameObject->direction;
		velocity = i_gameObject->velocity;
		speed = i_gameObject->speed;
		name = _strdup(i_gameObject->name);
		isMovable = i_gameObject->isMovable;
		isDead = i_gameObject->isDead;
		collidable = i_gameObject->collidable;
		renderable = i_gameObject->renderable;
		mSprite = i_gameObject->mSprite;
		physicsComponent = i_gameObject->physicsComponent;
		physicsObject = i_gameObject->physicsObject;
		mCollidingBox = i_gameObject->mCollidingBox;
		mGameObjectController = i_gameObject->mGameObjectController;
	}


	//Update position of the object 
	void GameObject::updatePosition()
	{
		if (physicsObject)
		{
			assert(physicsComponent);
			physicsComponent->updatePhysics();
			position = physicsComponent->getCurrentPosition();
		}
		else
			position = position + velocity;
	}

	

	//update velocity of the object
	void GameObject::updateVelocity()
	{
		if (physicsObject)
		{
			assert(physicsComponent);
			physicsComponent->updatePhysics();
			velocity = physicsComponent->getCurrentVelocity();
		}
		else
			velocity = direction * speed;
	}

	
	//Setter -Direction
	void GameObject::setRandomDirection()
	{
		direction.setRandomVector();
		direction.normalizeVector();
	}

	

	//Rendering function - to initalize sprites
	void GameObject::initializeSprite(char* i_filename, Cheesy::Point2D i_dimension, Cheesy::ColorRGBA i_color)
	{
		if (mSprite == nullptr)
		{
			mSprite = myEngine::Rendering::Sprite::init(i_filename, position, i_dimension, i_color);
			if (mSprite)
			{
				renderable = true;
				initializeBoundingBox();
			}
			
		}
	}

	
	//Getter - sprite
	myEngine::Rendering::Sprite * GameObject::getSprite()
	{
		return mSprite;
	}

	
	//Getter - renderable
	bool GameObject::isRenderable()
	{
		return renderable;
	}

	
	//Initialize Physics
	void GameObject::initializePhysicsComponent()
	{
		if (!physicsObject && physicsComponent == nullptr)
		{
			physicsComponent = myEngine::Physics::PhysicsComponent::init(
				10.0f,
				Vector3D(0.0f, 0.0f, 0.0f),
				20.0f,
				-20.0f);
			assert(physicsComponent);
			physicsObject = true;
			physicsComponent->setCurrentPosition(position);
		}
	}

	//Initialize Collision: Private: To initialize Collision Bounding Box
	void GameObject::initializeBoundingBox()
	{
		if (!collidable && mCollidingBox == nullptr)
		{
			mCollidingBox = EngineController::GameEngine::isEngineInitialized() ?
				new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(myEngine::Physics::BoundingBox))) myEngine::Physics::BoundingBox() :
				new myEngine::Physics::BoundingBox();
			collidable = true;
			mCollidingBox->setBoundingBox(position, 0, 0, 0);
		}
		
	}

	
	//Getter - Physics Component
	myEngine::Physics::PhysicsComponent* GameObject::getPhysicsComponent()
	{
		if (physicsObject)
		{
			if (physicsComponent == nullptr)
				initializePhysicsComponent();
		}
		return physicsComponent;
	}

	
	//Getter gameController
	myEngine::IGameObjectController* GameObject::getGameObjectController()
	{
		return mGameObjectController;
	}


	//Setter - gameController -
	// @ mGameController - will decide the behavior of the gameObject in the game
	void GameObject::setGameObjectController(myEngine::IGameObjectController *i_controller)
	{
		mGameObjectController = i_controller;
	}

	
	//To reset the gameObject - especially physics component
	void GameObject::resetGameObject()
	{
		if (physicsObject)
		{
			assert(physicsComponent);
			physicsComponent->setForce(Vector3D(0.0f, 0.0f, 0.0f));
			physicsComponent->updatePhysics();
			position = physicsComponent->getCurrentPosition();
			velocity = physicsComponent->getCurrentVelocity();
		}
		
	}

}//namespace myEngine