namespace myEngine
{
	inline Vector3D GameObject::getPosition()
	{
		return physicsComponent->getCurrentPosition();
	}

	inline void GameObject::setPosition(const Vector3D i_position)
	{
		physicsComponent->setCurrentPosition(i_position);
	}

	inline void GameObject::setRandomPosition()
	{
		physicsComponent->setCurrentPosition(Vector3D(myEngine::getRandomNumber(), myEngine::getRandomNumber(), myEngine::getRandomNumber()));
	}

	inline Vector3D GameObject::getDirection()
	{
		return physicsComponent->getCurrentDirection();
	}

	inline void GameObject::setDirection(const Vector3D i_direction)
	{
		physicsComponent->setCurrentDirection(i_direction);
	}

	inline float GameObject::getSpeed()
	{
		return physicsComponent->getCurrentVelocity().length();
	}

	inline void GameObject::setSpeed(const float i_speed)
	{
		physicsComponent->setCurrentVelocity(physicsComponent->getCurrentVelocity().getNormalizeVector() * i_speed);
	}

	inline Vector3D GameObject::getVelocity()
	{
		return physicsComponent->getCurrentVelocity();
	}

	inline void GameObject::setVelocity(Vector3D &i_velocity)
	{
		physicsComponent->setCurrentVelocity(i_velocity);
	}

	inline const char * GameObject::getName()
	{
		return name;
	}

	inline void GameObject::setName(char * i_name)
	{
		name = _strdup(i_name);
	}

	inline bool GameObject::Movable()
	{
		return isMovable;
	}

	inline bool GameObject::isAlive()
	{
		return isDead;
	}

	inline void GameObject::displayPosition()
	{
		getPosition().displayVector();
	}

	inline bool	GameObject::isPhysicsObject()
	{
		return physicsObject;
	}

	inline void GameObject::setPhysicsObject(bool i_isPhysics)
	{
		physicsObject = i_isPhysics;
	}

	inline void	GameObject::updateGameObject()
	{
		physicsComponent->updatePhysics();
	}
	

}