namespace myEngine
{
	inline const float Vector2D::getX(){ return x; }

	inline const float Vector2D::getY(){ return y; }

	inline void Vector2D::setX(const float i_x){ x = i_x; }

	inline void Vector2D::setY(const float i_y){ y = i_y; }

	inline void Vector2D::displayVector(){
		std::cout << "[" << x << "," << y << "]";
	}
}