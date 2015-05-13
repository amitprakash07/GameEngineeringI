#include "GameObject.h"
#include "CheesyHelper.h"
#include "HashedString.h"
#include "FloatNumbers.h"
#include "Engine.h"
#include "FloatNumbers.h"


namespace myEngine
{
	namespace Rendering
	{
		class Sprite;
	}

}

namespace myEngine
{

	void GameObject::updateGameObject(float i_deltaTime)
	{
		getPhysicsComponent()->updatePhysics(i_deltaTime);
	}
	
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
		return (myEngine::Matrix4x4::getTranslationMatrix(getPosition(), myEngine::typedefs::COLUMN_MAJOR));
	}
	
	/**<Summary> 
	* Calculate the extent of the passed GamedObject 
	* in the calling GameObject Coordinate System
	* </Summary>
	*/
	Vector3D GameObject::getTransformedExtents(SharedPointer<GameObject> i_other)
	{
		Vector3D i_otherExtentInThis;
		Matrix4x4 i_otherCentrePositionInThis = Matrix4x4(getTranslatedPosition(i_other->getPosition()));


		//Tranforming the Extents coordinate of passed gameObject in calling gameObject coordinate system
		Vector3D i_otherXExtentPositionInThis = getTranslatedPosition(i_other->getPosition() + Vector3D(i_other->mCollidingBox->getExtendX(), 0, 0));
		Vector3D i_otherYExtentPositionInThis = getTranslatedPosition(i_other->getPosition() + Vector3D(0, i_other->mCollidingBox->getExtendY(), 0));
		Vector3D i_otherZExtentPositionInThis = getTranslatedPosition(i_other->getPosition() + Vector3D(0, 0, i_other->mCollidingBox->getExtendZ()));

		Vector3D i_otherXExtentVectorInThis = i_otherXExtentPositionInThis - i_otherCentrePositionInThis.getPositionFromMatrix4x4();
		Vector3D i_otherYExtentVectorInThis = i_otherYExtentPositionInThis - i_otherCentrePositionInThis.getPositionFromMatrix4x4();
		Vector3D i_otherZExtentVectorInThis = i_otherZExtentPositionInThis - i_otherCentrePositionInThis.getPositionFromMatrix4x4();

		//Creating the passed gameObject extent Vectors in calling gameObject coordinate system
		i_otherExtentInThis.setX(abs(
			i_otherXExtentVectorInThis.dotProduct(Vector3D(1.0f, 0.0f, 0.0f)) +
			i_otherYExtentVectorInThis.dotProduct(Vector3D(1.0f, 0.0f, 0.0f)) +
			i_otherZExtentVectorInThis.dotProduct(Vector3D(1.0f, 0.0f, 0.0f))
			));

		i_otherExtentInThis.setY(abs(
			i_otherXExtentVectorInThis.dotProduct(Vector3D(0.0f, 1.0f, 0.0f)) +
			i_otherYExtentVectorInThis.dotProduct(Vector3D(0.0f, 1.0f, 0.0f)) +
			i_otherZExtentVectorInThis.dotProduct(Vector3D(0.0f, 1.0f, 0.0f))
			));

		i_otherExtentInThis.setZ(abs(
			i_otherXExtentVectorInThis.dotProduct(Vector3D(0.0f, 0.0f, 1.0f)) +
			i_otherYExtentVectorInThis.dotProduct(Vector3D(0.0f, 0.0f, 1.0f)) +
			i_otherZExtentVectorInThis.dotProduct(Vector3D(0.0f, 0.0f, 1.0f))
			));

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
	bool GameObject::separationAxisTest(SharedPointer<GameObject> i_other, float& o_collisionTime, float & o_separationTime, myEngine::typedefs::Axis &o_collisionAxis) //Move to Collsion System to make it better - To-Do
	{
		bool isColliding = false;
		float tCollisionInX = 0.0f;
		float tSeparationInX = 0.0f;
		float tCollisionInY = 0.0f;
		float tSeparationInY = 0.0f;
		float tCollisionInZ = 0.0f;
		float tSeparationInZ = 0.0f;

		//Position of other GameObject in this
		Vector3D i_otherCenterPositionInThis = getTranslatedPosition(i_other->getPosition());

		//Extent of other gameObject in this
		Vector3D i_otherExtentInThis = getTransformedExtents(i_other);

		//Transformed velocity of calling gamobject in its own coordiante system
		Vector3D thisVelocityInThis = getTranslationMatrix() *physicsComponent->getCurrentVelocity();

		//Velocity of other GameObject in calling gameObject coordinate system
		Vector3D i_otherVelocityInThis = getTranslationMatrix() * i_other->physicsComponent->getCurrentVelocity();

		//Relative velocity of other gamObject in freezed gameObject coordinate system i.e. in calling gameObject coordiante system
		Vector3D i_otherChangedVelocityInThis = i_otherVelocityInThis - thisVelocityInThis;

		//Expanding the extents of calling gameObject
		float thisChangedXExtent = getCollider()->getExtendX() + i_otherExtentInThis.getX();
		float thisChangedYExtent = getCollider()->getExtendY() + i_otherExtentInThis.getY();
		float thisChangedZExtent = getCollider()->getExtendZ() + i_otherExtentInThis.getZ();
		
		bool finalCollisionTimeInitialized = false;

		//Swept collision for each axes

		//Checking in X-Axis
		switch (i_otherCenterPositionInThis.getX() >= 0 )
		{
		case true:
			if (i_otherCenterPositionInThis.getX() <= thisChangedXExtent)
			{
				//To-Do - time of collision - Done but need testing
				if (i_otherChangedVelocityInThis.getX() != 0)
				{
					tCollisionInX = abs(((0 + thisChangedXExtent) - i_otherCenterPositionInThis.getX()) / i_otherChangedVelocityInThis.getX());
					tSeparationInX = abs((i_otherCenterPositionInThis.getX() - (0 - thisChangedXExtent)) / i_otherChangedVelocityInThis.getX());
					o_collisionTime = tCollisionInX;
					o_separationTime = tSeparationInX;
					o_collisionAxis = myEngine::typedefs::XAxis;
					finalCollisionTimeInitialized = true;
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
					tCollisionInX = abs((i_otherCenterPositionInThis.getX() - (0 - thisChangedXExtent)) / i_otherChangedVelocityInThis.getX());
					tSeparationInX = abs(((0 + thisChangedXExtent) - i_otherCenterPositionInThis.getX()) / i_otherChangedVelocityInThis.getX());
					o_collisionTime = tCollisionInX;
					o_separationTime = tSeparationInX;
					o_collisionAxis = myEngine::typedefs::XAxis;
					finalCollisionTimeInitialized = true;
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
					tCollisionInY = abs(((0 + thisChangedYExtent) - i_otherCenterPositionInThis.getY()) / i_otherChangedVelocityInThis.getY());
					tSeparationInY = abs((i_otherCenterPositionInThis.getY() - (0 - thisChangedYExtent)) / i_otherChangedVelocityInThis.getY());
					
					if (!finalCollisionTimeInitialized)
					{
						o_collisionTime = tCollisionInY;
						o_separationTime = tSeparationInY;
						o_collisionAxis = myEngine::typedefs::YAxis;
					}
					else
					{
						if (tCollisionInY < o_collisionTime)
						{
							o_collisionTime = tCollisionInY;
							o_collisionAxis = myEngine::typedefs::YAxis;

						}

						if (tSeparationInY < o_separationTime)
							o_separationTime = tSeparationInY;
					}
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
					tCollisionInY = abs((i_otherCenterPositionInThis.getY() - (0 - thisChangedYExtent)) / i_otherChangedVelocityInThis.getY());
					tSeparationInY = abs(((0 + thisChangedYExtent) - i_otherCenterPositionInThis.getY()) / i_otherChangedVelocityInThis.getY());
					
					if (!finalCollisionTimeInitialized)
					{
						o_collisionTime = tCollisionInY;
						o_separationTime = tSeparationInY;
						o_collisionAxis = myEngine::typedefs::YAxis;
					}
					else
					{

						if (tCollisionInY < o_collisionTime)
						{
							o_collisionTime = tCollisionInY;
							o_collisionAxis = myEngine::typedefs::YAxis;
						}

						if (tSeparationInY < o_separationTime)
							o_separationTime = tSeparationInY;
					}
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
					tCollisionInZ = abs(((0 + thisChangedZExtent) - i_otherCenterPositionInThis.getZ()) / i_otherChangedVelocityInThis.getZ());
					tSeparationInZ = abs((i_otherCenterPositionInThis.getZ() - (0 - thisChangedZExtent)) / i_otherChangedVelocityInThis.getZ());

					if (!finalCollisionTimeInitialized)
					{
						o_collisionTime = tCollisionInZ;
						o_separationTime = tSeparationInZ;
						o_collisionAxis = myEngine::typedefs::ZAxis;
					}
					else
					{

						if (tCollisionInY < o_collisionTime)
						{
							o_collisionTime = tCollisionInZ;
							o_collisionAxis = myEngine::typedefs::ZAxis;
						}

						if (tSeparationInY < o_separationTime)
							o_separationTime = tSeparationInZ;
					}
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
					tCollisionInZ = abs((i_otherCenterPositionInThis.getZ() - (0 - thisChangedZExtent)) / i_otherChangedVelocityInThis.getZ());
					tSeparationInZ = abs(((0 + thisChangedZExtent) - i_otherCenterPositionInThis.getZ()) / i_otherChangedVelocityInThis.getZ());

					if (!finalCollisionTimeInitialized)
					{
						o_collisionTime = tCollisionInZ;
						o_separationTime = tSeparationInZ;
						o_collisionAxis = myEngine::typedefs::ZAxis;
					}
					else
					{
						if (tCollisionInY < o_collisionTime)
						{
							o_collisionTime = tCollisionInZ;
							o_collisionAxis = myEngine::typedefs::ZAxis;
						}
						if (tSeparationInY < o_separationTime)
							o_separationTime = tSeparationInZ;
					}
				}
			}
			else return false;
			break;
		}

		
		//returning if all if's are false i.e. collsion occured in this coordinate system
		return true;
	}

	
	//Returns Collision Component of the gameObject
	myEngine::Physics::Collider* GameObject::getCollider()
	{
		return mCollidingBox;
	}
	
	
	//Returns Bounding Box
	myEngine::typedefs::BoundingBox GameObject::getCollisionBoundingBox()
	{
		return (mCollidingBox->getBoundingBox());
	}

	
	
	//static CreateGameoBject function
	SharedPointer<GameObject> GameObject::CreateGameObject(Vector3D i_position)
	{
		return (SharedPointer<GameObject>(new (EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(GameObject))) GameObject(i_position)));
	}


	//To create GameObjects using Lua file generated LuaActors
	SharedPointer<GameObject> GameObject::CreateGameObject(LuaUtilityHelper::LuaActor i_luaActor)
	{
		SharedPointer<GameObject> temp = CreateGameObject(i_luaActor.position);
		temp->setName(i_luaActor.name);
		
		temp->setGameObjectController(EngineController::GameEngine::getGameObjectController(EngineController::GameEngine::getStringPool()->findString(i_luaActor.gameController)));
		
		if (i_luaActor.collisionHandler != "\0")
			temp->getCollider()->setCollisionHandler(EngineController::GameEngine::getCollisionHandler(EngineController::GameEngine::getStringPool()->findString(i_luaActor.collisionHandler)));
		else 
			temp->getCollider()->setCollisionHandler(EngineController::GameEngine::getCollisionHandler(EngineController::GameEngine::getStringPool()->findString("Default")));

		
		for (unsigned __int16 i = 0; i < i_luaActor.collidingWith.size(); i++)
			temp->getCollider()->addToCollideWith(EngineController::GameEngine::getStringPool()->findString(i_luaActor.collidingWith[i]));
				temp->getPhysicsComponent()->setMaxAcceleration(i_luaActor.velocity.length());

		temp->getPhysicsComponent()->setMass(i_luaActor.mass);
		temp->getCollider()->setBoundingBox(i_luaActor.collisionBox);
		temp->type = i_luaActor.category;

		
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
		initializePhysicsComponent();
		setPosition(Vector3D(0.0f,0.0f,0.0f));
		initializeBoundingBox();
	}


	//private - parameterized constructor
	GameObject::GameObject(Vector3D i_position) :
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
		initializePhysicsComponent();
		setPosition(i_position);
		initializeBoundingBox();

	}



	//private - copy constructor
	GameObject::GameObject(SharedPointer<GameObject>& i_gameObject)
	{
		isMovable = i_gameObject->isMovable;
		isDead = i_gameObject->isDead;
		collidable = i_gameObject->collidable;
		name = _strdup(i_gameObject->name);
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
		delete mGameObjectController;
		delete name;
		delete type;
		delete mSprite;
		delete physicsComponent;
		delete mCollidingBox;
	}


	bool GameObject::isCollidable()
	{
		return collidable;
	}


	//Assignment Operator
	void GameObject::operator = (myEngine::SharedPointer<GameObject>& i_gameObject)
	{
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
		}
		else
			setPosition(getPosition() + getVelocity());
	}

	

	//update velocity of the object
	void GameObject::updateVelocity()
	{
		assert(physicsComponent);
		physicsComponent->updatePhysics();
	}

	
	//Setter -Direction
	void GameObject::setRandomDirection()
	{
		physicsComponent->getCurrentDirection().setRandomVector();
	}

	

	//Rendering function - to initalize sprites
	void GameObject::initializeSprite(char* i_filename, Cheesy::Point2D i_dimension, Cheesy::ColorRGBA i_color)
	{
		if (mSprite == nullptr)
		{
			mSprite = myEngine::Rendering::Sprite::init(i_filename, getPosition(), i_dimension, i_color);
			if (mSprite)
			{
				renderable = true;
				initializeBoundingBox();
			}
			
		}
	}

	char* GameObject::getType()
	{
		return type;
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
		}
	}

	//Initialize Collision: Private: To initialize Collision Bounding Box
	void GameObject::initializeBoundingBox()
	{
		if (!collidable && mCollidingBox == nullptr)
		{
			mCollidingBox = EngineController::GameEngine::isEngineInitialized() ?
				new(EngineController::GameEngine::getMemoryManager()->__alloc(sizeof(myEngine::Physics::Collider))) myEngine::Physics::Collider() :
				new myEngine::Physics::Collider();
			collidable = true;
			mCollidingBox->setBoundingBox(getPosition(), 0, 0, 0);
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
			physicsComponent->setCurrentDirection(Vector3D(0.0f, 0.0f, 0.0f));
			physicsComponent->setCurrentPosition(Vector3D(0.0f, 0.0f, 0.0f));
			physicsComponent->setCurrentVelocity(Vector3D(0.0f, 0.0f, 0.0f));			
		}
		
	}

}//namespace myEngine