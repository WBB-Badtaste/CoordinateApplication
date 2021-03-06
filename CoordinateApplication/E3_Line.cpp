#include "stdafx.h"
#include "E3_Line.h"


_e3_line::~_e3_line(){}

_e3_line::_e3_line(){}

_e3_line::_e3_line(const _e3_line& newObject) :S(newObject.S), C(newObject.C){}

_e3_line::_e3_line(const STANDARD& newS) :S(newS)
{
	
	C.plane1.a = S.direction.y;
	C.plane1.b = -S.direction.x;
	C.plane1.c = 0;
	C.plane1.d = S.direction.x * S.point.y - S.direction.y * S.point.x;

	C.plane2.a = 0;
	C.plane2.b = S.direction.z;
	C.plane2.c = -S.direction.y;
	C.plane2.d = S.direction.y * S.point.z - S.direction.z * S.point.y;
}

_e3_line::_e3_line(const COMMON& newC) :C(newC)
{
	S.direction = C.plane1.NormalVector() * C.plane2.NormalVector();

	S.point.x = (C.plane2.d - C.plane1.d * C.plane2.b / C.plane1.b) / (C.plane1.a * C.plane2.b / C.plane1.b - C.plane2.a);
	S.point.y = -(S.point.x * C.plane1.a + C.plane1.d) / C.plane1.b;
	S.point.z = 0;
}

_e3_line::_e3_line(const E3_POINT& point1, const E3_POINT& point2)
{
	_e3_line(STANDARD(point1, point2 - point1));
}

_e3_line::_e3_line(const E3_PLANE& plane1, const E3_PLANE& plane2)
{
	_e3_line(COMMON(plane1, plane2));
}

_e3_line::_e3_line(
	const double& a1, const double& b1, const double& c1, const double& d1,
	const double& a2, const double& b2, const double& c2, const double& d2)
{
	_e3_line(COMMON(a1, b1, c1, d1, a2, b2, c2, d2));
}

_e3_line::_e3_line(
	const double& x0, const double& y0, const double& z0, 
	const double& l, const double& m, const double& n)
{
	_e3_line(STANDARD(x0, y0, z0, l, m, n));
}