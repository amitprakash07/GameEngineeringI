

namespace myEngine
{
	inline const float Vector3D::getX() const { return x; }

	inline const float Vector3D::getY() const { return y; }

	inline const float Vector3D::getZ() const { return z; }

	inline void Vector3D::setX(const float i_x){ x = i_x; }

	inline void Vector3D::setY(const float i_y){ y = i_y; }

	inline void Vector3D::setZ(const float i_z){ z = i_z; }

	inline void Vector3D::displayVector(){
		std::cout << "[" << x << "," << y << "," << z << "]";
	}
}