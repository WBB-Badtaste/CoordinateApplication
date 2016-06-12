#pragma once

#include "E3_Point.h"
#include "Geometric.h"

/*
@brief: This is a class of three-dimensional plane
@author: JoMar
@date: 2016-06-12
*/
typedef class _e3_plane
{
public:
	_e3_plane();
	_e3_plane(const _e3_plane& newObject);
	_e3_plane(const E3_POINT& point1, const E3_POINT& point2, const E3_POINT& point3);
	~_e3_plane();

	_e3_plane& operator=(const _e3_plane& object);

	E3_VECTOR NormalVector();

	double a;
	double b;
	double c;
	double d;
}
/*
@brief: This is a class of three-dimensional plane
@author: JoMar
@date: 2016-06-12
*/
E3_PLANE;

