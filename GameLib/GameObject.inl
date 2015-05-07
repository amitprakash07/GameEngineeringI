namespace myEngine
{
	inline Vector3D GameObject::getPosition()
	{
		return position;
	}

	inline void GameObject::setPosition(const Vector3D i_position)
	{
		position = i_position;
	}

	inline void GameObject::setRandomPosition()
	{
		position.setRandomVector();
	}

	inline Vector3D GameObject::getDirection()
	{
		return direction;
	}

	inline void GameObject::setDirection(const Vector3D i_direction)
	{
		direction = i_direction;
	}

	inline float GameObject::getSpeed()
	{
		return speed;
	}

	inline void GameObject::setSpeed(const float i_speed)
	{
		speed = i_speed;
	}

	inline Vector3D GameObject::getVelocity()
	{
		return velocity;
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
		position.displayVector();
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
		this->updatePosition();
		this->updateVelocity();
	}

}