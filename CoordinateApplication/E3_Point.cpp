#include "stdafx.h"
#include "E3_Point.h"

_e3_vector::~_e3_vector(){}

_e3_vector::_e3_vector() :x(0), y(0), z(0){}

_e3_vector::_e3_vector(const _e3_vector& newObject) : x(newObject.x), y(newObject.y), z(newObject.z){}

_e3_vector::_e3_vector(double newX, double newY, double newZ) : x(newX), y(newY), z(newZ){}

_e3_vector& _e3_vector::operator=(const _e3_vector& newObject)
{
	x = newObject.x;
	y = newObject.y;
	z = newObject.z;
	return *this;
}

_e3_vector _e3_vector::operator-() const
{
	return _e3_vector(-x, -y, -z);
}

_e3_vector operator-(const _e3_vector& objectL, const _e3_vector& objectR)
{
	return _e3_vector(objectL.x - objectR.x, objectL.y - objectR.y, objectL.z - objectR.z);
}

_e3_vector operator*(const _e3_vector& objectL, const _e3_vector& objectR)
{
	return _e3_vector
		( objectL.y * objectR.z - objectL.z * objectR.y
		, objectL.z * objectR.x - objectL.x * objectR.z
		, objectL.x * objectR.y - objectL.y * objectR.x);
}

_e3_vector operator*(const _e3_vector& object, const double ratio)
{
	return _e3_vector(object.x * ratio, object.y * ratio, object.z * ratio);
}

_e3_vector& _e3_vector::operator+=(const _e3_vector& object)
{
	x += object.x;
	y += object.y;
	z += object.z;
	return *this;
}

void _e3_vector::Roll(const double &radian)
{
	double buffer(y * cos(radian) - z * sin(radian));
	z = y * sin(radian) + z * cos(radian);
	y = buffer;
}

void _e3_vector::Pitch(const double &radian)
{
	double buffer(z * cos(radian) - x * sin(radian));
	x = z * sin(radian) + x * cos(radian);
	z = buffer;
}

void _e3_vector::Yaw(const double &radian)
{
	double buffer(x * cos(radian) - y * sin(radian));
	y = x * sin(radian) + y * cos(radian);
	x = buffer;
}

void _e3_vector::Rotate(const _e3_vector &r)
{
	Roll(r.x);
	Pitch(r.y);
	Yaw(r.z);
}

void _e3_vector::InvRotate(const _e3_vector &r)
{
	Yaw(r.z);
	Pitch(r.y);
	Roll(r.x);
}

void _e3_vector::Translation(const _e3_vector &t)
{
	*this += t;
}

void _e3_vector::Zoom(const double &ratio)
{
	this->x *= ratio;
	this->y *= ratio;
	this->z *= ratio;
}

double _e3_vector::Module() const
{
	return sqrt(QuadraticSum());
}

double _e3_vector::QuadraticSum() const
{
	return x * x + y * y + z * z;
}