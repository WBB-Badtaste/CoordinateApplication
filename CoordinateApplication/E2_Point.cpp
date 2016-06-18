#include "stdafx.h"
#include "E2_Point.h"

_e2_vector::~_e2_vector(){}

_e2_vector::_e2_vector() :x(0), y(0){}

_e2_vector::_e2_vector(const _e2_vector& newObject) : x(newObject.x), y(newObject.y){}

_e2_vector::_e2_vector(double newX, double newY) : x(newX), y(newY){}

_e2_vector& _e2_vector::operator=(const _e2_vector& newObject)
{
	x = newObject.x;
	y = newObject.y;
	return *this;
}

_e2_vector _e2_vector::operator-() const
{
	return _e2_vector(-x, -y);
}

_e2_vector operator-(const _e2_vector& objectL, const _e2_vector& objectR)
{
	return _e2_vector(objectL.x - objectR.x, objectL.y - objectR.y);
}

_e2_vector operator*(const _e2_vector& object, const double ratio)
{
	return _e2_vector(object.x * ratio, object.y * ratio);
}

_e2_vector& _e2_vector::operator+=(const _e2_vector& object)
{
	x += object.x;
	y += object.y;
	return *this;
}

// void _e2_vector::Roll(const double &radian)
// {
// 	double buffer(y * cos(radian) - z * sin(radian));
// 	z = y * sin(radian) + z * cos(radian);
// 	y = buffer;
// }
// 
// void _e2_vector::Pitch(const double &radian)
// {
// 	double buffer(z * cos(radian) - x * sin(radian));
// 	x = z * sin(radian) + x * cos(radian);
// 	z = buffer;
// }
// 
// void _e2_vector::Yaw(const double &radian)
// {
// 	double buffer(x * cos(radian) - y * sin(radian));
// 	y = x * sin(radian) + y * cos(radian);
// 	x = buffer;
// }
// 
// void _e2_vector::Rotate(const _e2_vector &r)
// {
// 	Roll(r.x);
// 	Pitch(r.y);
// 	Yaw(r.z);
// }
// 
// void _e2_vector::InvRotate(const _e2_vector &r)
// {
// 	Yaw(r.z);
// 	Pitch(r.y);
// 	Roll(r.x);
// }
// 
// void _e2_vector::Translation(const _e2_vector &t)
// {
// 	*this += t;
// }
// 
// void _e2_vector::Zoom(const double &ratio)
// {
// 	this->x *= ratio;
// 	this->y *= ratio;
// 	this->z *= ratio;
// }

double _e2_vector::Module() const
{
	return sqrt(QuadraticSum());
}

double _e2_vector::QuadraticSum() const
{
	return x * x + y * y ;
}