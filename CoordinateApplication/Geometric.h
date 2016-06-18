#pragma once

#include "E3_Point.h"
#include "E3_Line.h"
#include "E3_Plane.h"

/*
@brief: This is a func to calculate the lenght between two e3_point
@param[in]: point1
@param[in]: point2
@return: lenght
@author: JoMar
@date: 2016-06-08
*/
double CalLenght(const E3_POINT &point1, const E3_POINT &point2);

/*
@brief: This is a func to calculate the dot product of two e3_vector
@param[in]: vector1
@param[in]: vector2
@return: dot product
@author: JoMar
@date: 2016-06-08
*/
double Dot(const E3_VECTOR &vector1, const E3_VECTOR &vector2);

/*
@brief: This is a func to calculate the angle between two e3_vector
@note: Radian system
@note: The return value is a principal value between 0 and +pi
@param[in]: vector1
@param[in]: vector2
@return: radian
@author: JoMar
@date: 2016-06-08
*/
double CalRadian(const E3_VECTOR &vector1, const E3_VECTOR &vector2);

/*
@brief: This is a func to calculate the angle between e3_vector and e3_plane
@note: Radian system
@note: The return value is a principal value between 0 and +pi
@param[in]: vector
@param[in]: plane
@return: radian
@author: JoMar
@date: 2016-06-12
*/
double CalRadian(const E3_VECTOR &vector, const E3_PLANE& plane);

/*
@brief: This is a func to calculate the angle between two e3_plane
@note: Radian system
@note: The return value is a principal value between 0 and +pi
@param[in]: plane1
@param[in]: plane2
@return: radian
@author: JoMar
@date: 2016-06-12
*/
double CalRadian(const E3_PLANE& plane1, const E3_PLANE& plane2);

/*
@brief: This is a func to convert the angle to radian
@param[in]: angle
@return: radian
@author: JoMar
@date: 2016-06-08
*/
double Angle2Radian(const double &angle);

/*
@brief: This is a func to convert the radian to angle
@param[in]: radian
@return: angle
@author: JoMar
@date: 2016-06-08
*/
double Radian2Angle(const double &radian);


/*
@brief: Calculate the crossover point of three e3_plane
@param[in]: radian
@return: crossover point
@author: JoMar
@date: 2016-06-17
*/
E3_POINT CrossvoerPointOfPlanes(const E3_PLANE& plane1, const E3_PLANE& plane2, const E3_PLANE& plane3);
