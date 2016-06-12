#include "stdafx.h"
#include "E3_Line.h"


_e3_line::~_e3_line(){}

_e3_line::_e3_line(){}

_e3_line::_e3_line(const _e3_line& newObject) :S(newObject.S), C(newObject.C){}

_e3_line::_e3_line(const STANDARD& newS) :S(newS)
{
	C.a1 = S.m;
	C.b1 = -S.l;
	C.c1 = 0;
	C.d1 = S.l * S.y0 - S.m * S.x0;

	C.a2 = 0;
	C.b2 = S.n;
	C.c2 = -S.m;
	C.d2 = S.m * S.z0 - S.n * S.y0;
}

_e3_line::_e3_line(const COMMON& newC) :C(newC)
{
	//two normal vector of planes
	E3_VECTOR nv1(C.a1, C.b1, C.c1);
	E3_VECTOR nv2(C.a2, C.b2, C.c2);

	//direction vector of line
	E3_VECTOR dv(nv1 * nv2);

	S.l = dv.x;
	S.m = dv.y;
	S.n = dv.z;
	
	S.x0 = (C.d2 - C.d1 * C.b2 / C.b1) / (C.a1 * C.a2 / C.b1 - C.a2);
	S.y0 = -(S.x0 * C.a1 + C.d1) / C.b1;
	S.z0 = 0;
}

_e3_line::_e3_line(const E3_POINT& point1, const E3_POINT& point2)
{
	_e3_line(STANDARD(point1.x, point1.y, point1.z, point1.x - point2.x, point1.y - point2.y, point1.z - point2.z));
}