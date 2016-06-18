#pragma once

#pragma once

const double M_PI(atan2(0.0, -1.0));

const double M_PI_2(M_PI / 2);


/*
@brief: This is a class of two-dimensional vector
@author: JoMar
@date: 2016-06-17
*/
typedef class _e2_vector
{
public:

	double x;
	double y;

	~_e2_vector();

	_e2_vector();

	_e2_vector(const _e2_vector& newObject);

	_e2_vector(double newX, double newY);

	_e2_vector& operator=(const _e2_vector& newObject);

	_e2_vector& operator+=(const _e2_vector& object);

	_e2_vector operator-() const;

	friend _e2_vector operator-(const _e2_vector& objectL, const _e2_vector& objectR);

	friend _e2_vector operator*(const _e2_vector& object, const double ratio);


	/*
	@brief: This is a func to rotate a vector by a radian around X axis.
	@note: radian system
	@param[in]: radian
	@author: JoMar
	@date: 2016-06-17
	*/
	void Roll(const double &radian);

	/*
	@brief: This is a func to rotate a vector by a radian around Y axis.
	@note: radian system
	@param[in]: radian
	@author: JoMar
	@date: 2016-06-17
	*/
	void Pitch(const double &radian);

	/*
	@brief: This is a func to rotate a vector by a radian around Z axis.
	@note: radian system
	@param[in]: radian
	@author: JoMar
	@date: 2016-06-17
	*/
	void Yaw(const double &radian);

	/*
	@brief: This is a func to rotate a vector by a rotation matrix.
	@note: rotate sequence: x->y->z
	@note: radian system
	@param[in]: r - rotate martix
	@author: JoMar
	@date: 2016-06-17
	*/
	void Rotate(const _e2_vector &r);

	/*
	@brief: This is a func to rotate a vector by a rotation matrix.
	@note: rotate sequence: z->y->x
	@note: radian system
	@param[in]: r - rotate martix
	@author: JoMar
	@date: 2016-06-17
	*/
	void InvRotate(const _e2_vector &r);

	/*
	@brief: This is a func to translation a vector by an translation marix.
	@param[in]: t - translation marix
	@author: JoMar
	@date: 2016-06-17
	*/
	void Translation(const _e2_vector &t);

	/*
	@brief: This is a func to zoom a point.
	@param[in]: t - translation marix
	@author: JoMar
	@date: 2016-06-12
	*/
	void Zoom(const double &ratio);

	/*
	@brief: This is a func to calculate the module of a vector
	@return: module
	@author: JoMar
	@date: 2016-06-17
	*/
	double Module() const;

	/*
	@brief: This is a func to calculate the quadratic sum of x, y and Z.
	@return: quadratic sum
	@author: JoMar
	@date: 2016-06-17
	*/
	double QuadraticSum() const;
}
/*
@brief: This is a class of two-dimensional vector
@author: JoMar
@date: 2016-06-17
*/
E2_VECTOR;

/*
@brief: This is a class of two-dimensional point
@author: JoMar
@date: 2016-06-17
*/
typedef E2_VECTOR E2_POINT;

/*
@brief: This is a class of two-dimensional martix
@author: JoMar
@date: 2016-06-17
*/
typedef E2_VECTOR E2_MARTIX;




