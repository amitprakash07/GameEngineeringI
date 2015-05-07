#include <stdlib.h>
#include <iostream>
#include "Vector2D.h"
#include "random.h"
#include <math.h>


using namespace std;
using namespace myEngine;

Vector2D::Vector2D()
	:x(0),
	y(0)
{
	
}

Vector2D::Vector2D(float i_x, float i_y)
	: x(i_x),
	y(i_y)
{
	
}

Vector2D::Vector2D(Vector2D & i_vector)
{
	x = i_vector.x;
	y = i_vector.y;
}

/*Vector2D operator - (Vector2D op1, Vector2D op2){
Vector2D temp;
temp.setX(op2.x-op1.getX());
}*/

Vector2D Vector2D::operator *(const float i_float)
{
	Vector2D temp;
	temp.x = x * i_float;
	temp.y = y * i_float;
	return temp;
}

Vector2D Vector2D::operator +(const Vector2D i_vector)
{
	Vector2D temp;
	temp.x = x + i_vector.x;
	temp.y = y + i_vector.y;
	return temp;
}

Vector2D Vector2D::operator -(const Vector2D i_vector)
{
	Vector2D temp;
	temp.x = x - i_vector.x;
	temp.y = y - i_vector.y;
	return temp;
}

Vector2D Vector2D::operator +(const float i_num)
{
	Vector2D temp;
	temp.x += i_num;
	temp.y += i_num;
	return temp;
}

Vector2D Vector2D::operator -(const float i_num)
{
	Vector2D temp;
	temp.x -= i_num;
	temp.y -= i_num;
	return temp;
}

void Vector2D::operator =(const Vector2D i_vector)
{
	x = i_vector.x;
	y = i_vector.y;
}

bool Vector2D::operator==(const Vector2D i_vector)
{
	if ((this->x == i_vector.x) && (this->y == i_vector.y)) return true;
	return false;
}

// operator new (Vector2D);
/*istream & operator >> (istream & i_cin, Vector2D &i_vector){
i_cin >> i_vector.x;
i_cin >> i_vector.y;
i_cin >> i_vector.z;
return i_cin;
}

ostream & Vector2D<T>::operator << (ostream & i_cout){
i_cout << "(" << x << "," << y << "," << z << ")";
}*/

void Vector2D::setRandomVector()
{
	//unsigned char randNum;
	x = getRandomNumber();
	y = getRandomNumber();
}

void Vector2D::normalizeVector()
{
	x = (unsigned char)(x / (sqrt(pow(x, 2) + pow(x, 2))));
	y = (unsigned char)(y / (sqrt(pow(x, 2) + pow(x, 2))));
}