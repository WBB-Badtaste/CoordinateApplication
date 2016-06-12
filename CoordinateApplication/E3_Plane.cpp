#include "stdafx.h"
#include "E3_Plane.h"


_e3_plane::_e3_plane() :a(0), b(0), c(0), d(0){}

_e3_plane::_e3_plane(const _e3_plane& newObject) : a(newObject.a), b(newObject.b), c(newObject.c), d(newObject.d){}

_e3_plane::_e3_plane(const E3_POINT& point1, const E3_POINT& point2, const E3_POINT& point3)
{
	E3_VECTOR v1(point2 - point1);
	E3_VECTOR v2(point3 - point1);
	E3_VECTOR normalVector(v1 * v2);
	E3_VECTOR dz(0, 0, 1);
	if (CalRadian(dz, normalVector) > M_PI_2)
		normalVector = -normalVector;

	a = normalVector.x;
	b = normalVector.y;
	c = normalVector.z;
	d = -(a * point1.x + b * point1.y + c * point1.z);
}

_e3_plane::~_e3_plane(){}

_e3_plane& _e3_plane::operator=(const _e3_plane& object)
{
	a = object.a;
	b = object.b;
	c = object.c;
	d = object.d;
	return *this;
}

_e3_vector _e3_plane::NormalVector()
{
	return E3_VECTOR(a, b, c);
}