#pragma once

#include "Point.h"
#include "Plane.h"

/*
@brief: This is a struct to store parameters of standard line-equation which in three-dimensional
@author: JoMar
@date: 2016-06-12
*/
typedef struct _standard
{
	E3_POINT point;
	E3_VECTOR direction;

	_standard(){};

	_standard(
		const double& newX0,
		const double& newY0,
		const double& newZ0,
		const double& newL,
		const double& newM,
		const double& newN) :point(newX0, newY0, newZ0), direction(newL,newM,newN){};

	_standard(const E3_POINT& newPoint, const E3_VECTOR& newDirection) :point(newPoint), direction(newDirection){};

	_standard(const _standard& newObject) : point(newObject.point), direction(newObject.direction){};

	_standard& operator=(const _standard& object)
	{
		point = object.point;
		direction = object.direction;
		return *this;
	}
}
/*
@brief: This is a struct to store parameters of standard line-equation which in three-dimensional
@author: JoMar
@date: 2016-06-12
*/
STANDARD, E3_LINE_STANDARD;

/*
@brief: This is a struct to store parameters of commonly line-equation which in three-dimensional
@author: JoMar
@date: 2016-06-12
*/
typedef struct _common
{
	E3_PLANE plane1;
	E3_PLANE plane2;

	_common(){};

	_common(
		const double& newA1,
		const double& newB1,
		const double& newC1,
		const double& newD1,
		const double& newA2,
		const double& newB2,
		const double& newC2,
		const double& newD2) : plane1(newA1, newB1, newC1, newD1), plane2(newA2,newB2,newC2,newD2){};

	_common(const _common& newObject) : plane1(newObject.plane1), plane2(newObject.plane2){};

	_common(const E3_PLANE& newPlane1, const E3_PLANE& newPlane2) :plane1(newPlane1), plane2(newPlane2){};

	_common& operator=(const _common& object)
	{
		plane1 = object.plane1;
		plane2 = object.plane2;
		return *this;
	}
}
/*
@brief: This is a struct to store parameters of commonly line-equation which in three-dimensional
@author: JoMar
@date: 2016-06-12
*/
COMMON, E3_LINE_COMMON;

/*
@brief: This is a class of three-dimensional line
@author: JoMar
@date: 2016-06-12
*/
typedef class _e3_line
{
public:
	STANDARD S;

	COMMON C;

	~_e3_line();

	_e3_line();

	_e3_line(const _e3_line& newObject);

	_e3_line(const STANDARD& newS);

	_e3_line(const COMMON& newC);

	_e3_line(const E3_POINT& point1, const E3_POINT& point2);

	_e3_line(const E3_PLANE& plane1, const E3_PLANE& plane2);

	_e3_line(
		const double& a1, const double& b1, const double& c1, const double& d1,
		const double& a2, const double& b2, const double& c2, const double& d2);

	_e3_line(
		const double& x0, const double& y0, const double& z0,
		const double& l, const double& m, const double& n);
}
/*
@brief: This is a class of three-dimensional line
@author: JoMar
@date: 2016-06-12
*/
E3_LINE;

