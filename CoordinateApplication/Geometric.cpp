#include "stdafx.h"
#include "Geometric.h"


double CalLenght(const E3_POINT &point1, const E3_POINT &point2)
{
	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) + (point1.z - point2.z) * (point1.z - point2.z));
}

double Dot(const E3_VECTOR &vector1, const E3_VECTOR &vector2)
{

	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

double CalRadian(const E3_VECTOR &vector1, const E3_VECTOR &vector2)
{
	return acos(Dot(vector1, vector2) / vector1.Module() / vector2.Module());
}

double CalRadian(const E3_VECTOR& vector, const E3_PLANE& plane)
{
	double radian(CalRadian(vector, plane.NormalVector()));
	if (radian > M_PI_2)
		radian -= M_PI_2;
	return M_PI_2 - radian;
}

double CalRadian(const E3_PLANE& plane1, const E3_PLANE& plane2)
{
	double radian(CalRadian(plane1.NormalVector(), plane2.NormalVector()));
	if (radian > M_PI_2)
		radian -= M_PI_2;
	return radian;
}

double Angle2Radian(const double &angle)
{
	return angle / 180.0 * M_PI;
}


double Radian2Angle(const double &radian) 
{
	return radian / M_PI * 180.0;
}