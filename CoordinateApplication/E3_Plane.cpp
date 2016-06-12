#include "stdafx.h"
#include "E3_Plane.h"


_e3_plane::_e3_plane() :a(0), b(0), c(0), d(0){}

_e3_plane::_e3_plane(const _e3_plane& newObject) : a(newObject.a), b(newObject.b), c(newObject.c), d(newObject.d){}

_e3_plane::_e3_plane(const double& newA, const double& newB, const double& newC, const double& newD) : a(newA), b(newB), c(newC), d(newD){}

_e3_plane::_e3_plane(const E3_POINT& point, const E3_VECTOR& vector1, const E3_VECTOR& vector2)
{
	E3_VECTOR normalVector(vector1 * vector2);

	a = normalVector.x;
	b = normalVector.y;
	c = normalVector.z;
	d = -(a * point.x + b * point.y + c * point.z);
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

_e3_vector _e3_plane::NormalVector() const
{
	return E3_VECTOR(a, b, c);
}