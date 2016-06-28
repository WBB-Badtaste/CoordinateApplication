#include "stdafx.h"
#include "Plane.h"


_e3_plane::_e3_plane() :a(0), b(0), c(0), d(0){}

_e3_plane::_e3_plane(const _e3_plane& newObject) : a(newObject.a), b(newObject.b), c(newObject.c), d(newObject.d){}

_e3_plane::_e3_plane(const double& newA, const double& newB, const double& newC, const double& newD) : a(newA), b(newB), c(newC), d(newD){}

_e3_plane::_e3_plane(const E3_POINT& point, const E3_VECTOR& vector1, const E3_VECTOR& vector2)
{
	E3_VECTOR normalVector(vector1 * vector2);

	a = normalVector(0);
	b = normalVector(1);
	c = normalVector(2);
	d = -(a * point(0) + b * point(1) + c * point(2));
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

E3_VECTOR _e3_plane::NormalVector() const
{
	return E3_VECTOR(a, b, c);
}

_e3_plane::_e3_plane(const E3_POINT& point1, const E3_POINT& point2)
{
	E3_POINT buffer(point2 - point1);
	a = buffer(0);
	b = buffer(1);
	c = buffer(2);
	d = (point1.dot(point1) - point2.dot(point2)) / 2.0;
}