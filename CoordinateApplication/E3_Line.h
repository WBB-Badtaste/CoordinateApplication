#pragma once

#include "E3_Point.h"

/*
@brief: This is a struct to store parameters of standard line-equation which in three-dimensional
@author: JoMar
@date: 2016-06-08
*/
typedef struct _standard
{
	double x0, y0, z0;
	double l, m, n;

	_standard() : x0(0), y0(0), z0(0), l(0), m(0), n(0){};

	_standard(
		const double& newX0,
		const double& newY0,
		const double& newZ0,
		const double& newL,
		const double& newM,
		const double& newN) :x0(newX0), y0(newY0), z0(newZ0), l(newL), m(newM), n(newN){};

	_standard(const _standard& newObject) : x0(newObject.x0), y0(newObject.y0), z0(newObject.z0), l(newObject.l), m(newObject.m), n(newObject.n){};

	_standard& operator=(const _standard& object)
	{
		x0 = object.x0;
		y0 = object.y0;
		z0 = object.z0;
		l = object.l;
		m = object.m;
		n = object.n;
		return *this;
	}
}
/*
@brief: This is a struct to store parameters of standard line-equation which in three-dimensional
@author: JoMar
@date: 2016-06-08
*/
STANDARD, E3_LINE_STANDARD;

/*
@brief: This is a struct to store parameters of commonly line-equation which in three-dimensional
@author: JoMar
@date: 2016-06-08
*/
typedef struct _common
{
	double a1, b1, c1, d1;
	double a2, b2, c2, d2;

	_common() : a1(0), b1(0), c1(0), d1(0), a2(0), b2(0), c2(0), d2(0){};

	_common(
		const double& newA1,
		const double& newB1,
		const double& newC1,
		const double& newD1,
		const double& newA2,
		const double& newB2,
		const double& newC2,
		const double& newD2) : a1(newA1), b1(newB1), c1(newC1), d1(newD1), a2(newA2), b2(newB2), c2(newC2), d2(newD2){};

	_common(const _common& newObject) : a1(newObject.a1), b1(newObject.b1), c1(newObject.c1), d1(newObject.d1), a2(newObject.a2), b2(newObject.b2), c2(newObject.c2), d2(newObject.d2){};

	_common& operator=(const _common& object)
	{
		a1 = object.a1;
		b1 = object.b1;
		c1 = object.c1;
		d1 = object.d1;
		a2 = object.a2;
		b2 = object.b2;
		c2 = object.c2;
		d2 = object.d2;
		return *this;
	}
}
/*
@brief: This is a struct to store parameters of commonly line-equation which in three-dimensional
@author: JoMar
@date: 2016-06-08
*/
COMMON, E3_LINE_COMMON;

/*
@brief: This is a class of three-dimensional line
@author: JoMar
@date: 2016-06-08
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

}
/*
@brief: This is a class of three-dimensional line
@author: JoMar
@date: 2016-06-08
*/
E3_LINE;

