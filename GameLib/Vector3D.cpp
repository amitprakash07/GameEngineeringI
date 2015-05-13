#include <stdlib.h>
#include "Vector3D.h"
#include "random.h"
#include <math.h>


using namespace std;

namespace myEngine
{
	Vector3D::Vector3D() :
		x(0),
		y(0),
		z(0)
	{
		
	}

	Vector3D::Vector3D(float i_x, float i_y, float i_z) :
		x(i_x),
		y(i_y),
		z(i_z)
	{
		
	}

	Vector3D::Vector3D(Vector3D * i_vector)
	{
		x = i_vector->x;
		y = i_vector->y;
		z = i_vector->z;
	}

	
	Vector3D Vector3D::operator *(const float i_float)
	{
		Vector3D temp;
		temp.x = x * i_float;
		temp.y = y * i_float;
		temp.z = z * i_float;
		return temp;
	}

	Vector3D Vector3D::operator/(const float i_float)
	{
		return(Vector3D(x / i_float, y / i_float, z / i_float));
	}

	Vector3D Vector3D::operator +(const Vector3D i_vector)
	{
		return(Vector3D(x + i_vector.x,
			y + i_vector.y,
			z + i_vector.z)
			);
	}


	Vector3D Vector3D::operator -(const Vector3D i_vector){
		Vector3D temp;
		temp.x = x - i_vector.x;
		temp.y = y - i_vector.y;
		temp.z = z - i_vector.z;
		return temp;
	}


	Vector3D Vector3D::operator +(const float i_num){
		Vector3D temp;
		temp.x += i_num;
		temp.y += i_num;
		temp.z += i_num;
		return temp;
	}

	Vector3D Vector3D::operator -(const float i_num){
		Vector3D temp;
		temp.x -= i_num;
		temp.y -= i_num;
		temp.z -= i_num;
		return temp;
	}

	void Vector3D::operator =(const Vector3D i_vector){
		x = i_vector.x;
		y = i_vector.y;
		z = i_vector.z;
	}


	bool Vector3D::operator <(const Vector3D i_other) const
	{
		return (length() < i_other.length() ? true : false);
	}
	
	bool Vector3D::operator >(const Vector3D i_other) const
	{
		return (length() > i_other.length() ? true : false);
	}

	void Vector3D::setRandomVector(){
		//unsigned char randNum;
		x = getRandomNumber();
		y = getRandomNumber();
		z = getRandomNumber();
	}

	void Vector3D::normalizeVector()
	{
		float m_length = length();
		if (AlmostEqualUlpsFinal(m_length, 0.0f, 100))
		{
			x = y = z = 0;
		}
		x = x / m_length;
		y = y / m_length;
		z = z / m_length;
	}

	Vector3D Vector3D::getNormalizeVector(){
		float temp_x = x / length();
		float temp_y = y / length();
		float temp_z = z / length();
		return Vector3D(temp_x, temp_y, temp_z);
	}

	Vector3D Vector3D::GenerateRandomVector(Vector3D & i_Min, Vector3D & i_Max)
	{
		return Vector3D(
			RandInRange(i_Min.getX(), i_Max.getX()),
			RandInRange(i_Min.getY(), i_Max.getY()),
			RandInRange(i_Min.getZ(), i_Max.getZ()));
	}

	float Vector3D::length() const
	{
		if (!myEngine::IsNan(x) && !myEngine::IsNan(y) && !myEngine::IsNan(z))
			return(static_cast<float>((sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)))));
		return 0.0f;
	}

	float Vector3D::dotProduct(const Vector3D i_other)
	{
		return((x*i_other.x) + (y* i_other.y) + (z*i_other.z));
	}

	Vector3D Vector3D::crossProduct(const Vector3D i_other)
	{
		return(Vector3D(
			y * i_other.z - z*i_other.y,
			z*i_other.x - x*i_other.z,
			x * i_other.y -y*i_other.x));
	}

	Vector3D Vector3D::getZeroVector()
	{
		return (Vector3D(0.0f, 0.0f, 0.0f));
	}

	Vector3D Vector3D::getUnitVector()
	{
		return Vector3D(1.0f, 1.0f, 1.0f);
	}


	void Vector3D::negate()
	{
		x = -x;
		y = -x;
		z = -z;
	}
	
	Vector3D Vector3D::getNegatedVector(Vector3D i_other)
	{
		return (Vector3D(-i_other.x, -i_other.y, -i_other.z));
	}
}