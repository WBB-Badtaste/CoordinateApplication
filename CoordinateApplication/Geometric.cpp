#include "stdafx.h"
#include "Geometric.h"


double CalLenght(const E3_POINT &point1, const E3_POINT &point2)
{
	E3_VECTOR vP12(point2 - point1);
	return sqrt(vP12.dot(vP12));
}

double CalRadian(const E3_VECTOR &vector1, const E3_VECTOR &vector2)
{
	return acos(vector1.dot(vector2) / sqrt(vector1.dot(vector1)) / sqrt(vector2.dot(vector2)));
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

E3_POINT CrossvoerPointOfPlanes(const E3_PLANE& plane1, const E3_PLANE& plane2, const E3_PLANE& plane3)
{
	Eigen::Matrix<double, 3, 3>  matrix;
	matrix << plane1.a, plane1.b, plane1.c
			, plane2.a, plane2.b, plane2.c
			, plane3.a, plane3.b, plane3.c;
	Eigen::Vector3d vector(plane1.d, plane2.d, plane3.d);
	Eigen::Vector3d result;

	result = -(matrix.inverse() * vector);

	return E3_POINT(result(0), result(1), result(2));
}