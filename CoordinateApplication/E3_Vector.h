#pragma once

const double M_PI(atan2(0.0, -1.0));

const double M_PI_2(M_PI / 2);

/*
@brief: This is a class of three-dimensional vector
@param[in]: radian
@author: JoMar
@date: 2016-06-08
*/
typedef class _e3_vector
{
public:

	double x;
	double y;
	double z;

	~_e3_vector();

	_e3_vector();

	_e3_vector(const _e3_vector& newObject);

	_e3_vector(double newX, double newY, double newZ) ;

	_e3_vector& operator=(const _e3_vector& newObject);

	_e3_vector& operator+=(const _e3_vector& object);

	_e3_vector operator-();

	friend _e3_vector operator-(const _e3_vector& objectL, const _e3_vector& objectR);

	friend _e3_vector operator*(const _e3_vector& objectL, const _e3_vector& objectR);


	/*
	@brief: This is a func to rotate a vector by a radian around X axis.
	@note: radian system
	@param[in]: radian
	*/
	void Roll(const double &radian);

	/*
	@brief: This is a func to rotate a vector by a radian around Y axis.
	@note: radian system
	@param[in]: radian
	*/
	void Pitch(const double &radian);

	/*
	@brief: This is a func to rotate a vector by a radian around Z axis.
	@note: radian system
	@param[in]: radian
	*/
	void Yaw(const double &radian);

	/*
	@brief: This is a func to rotate a vector by a rotation matrix.
	@note: rotate sequence: x->y->z
	@note: radian system
	@param[in]: r - rotate martix
	*/
	void Rotate(const _e3_vector &r);

	/*
	@brief: This is a func to rotate a vector by a rotation matrix.
	@note: rotate sequence: z->y->x
	@note: radian system
	@param[in]: r - rotate martix
	*/
	void InvRotate(const _e3_vector &r);

	/*
	@brief: This is a func to translation a vector by an translation marix.
	@param[in]: t - translation marix
	*/
	void Translation(const _e3_vector &t);

	/*
	@brief: This is a func to calculate the module of a vector
	@return: module
	*/
	double Module() const;
}
/*
@brief: This is a class of three-dimensional vector
@param[in]: radian
@author: JoMar
@date: 2016-06-08
*/
E3_VECTOR;

/*
@brief: This is a class of three-dimensional point
@param[in]: radian
@author: JoMar
@date: 2016-06-08
*/
typedef E3_VECTOR E3_POINT;

/*
@brief: This is a class of three-dimensional martix
@param[in]: radian
@author: JoMar
@date: 2016-06-08
*/
typedef E3_VECTOR E3_MARTIX;


