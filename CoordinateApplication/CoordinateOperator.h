#pragma once

#include "CoordinateOperatorDefine.h"
#include <vector>

class CCoordinateOperator
{
public:
	CCoordinateOperator();
	virtual ~CCoordinateOperator();

	/*
	@brief: This is a func to rotate a point by an angle around X axis.
	@author: JoMar
	@param[in|out]: point
	@param[in]: angle
	*/
	inline void Roll(E3_VECTOR &point, const double &angle);

	/*
	@brief: This is a func to rotate a point by an angle around Y axis.
	@author: JoMar
	@param[in|out]: point
	@param[in]: angle
	*/
	inline void Pitch(E3_VECTOR &point, const double &angle);

	/*
	@brief: This is a func to rotate a point by an angle around Z axis.
	@author: JoMar
	@param[in|out]: point
	@param[in]: angle
	*/
	inline void Yaw(E3_VECTOR &point, const double &angle);

	/*
	@brief: This is a func to translation a point by an translation marix.
	@author: JoMar
	@param[in|out]: point
	@param[in]: t - translation marix
	*/
	inline void Translation(E3_VECTOR &point, const E3_VECTOR &t);

	/*
	@brief: This is a func to calculate the module of a vector
	@author: JoMar
	@param[in]: vector
	@return: module
	*/
	double CalculateVectorModule(const E3_VECTOR &vector);

	/*
	@brief: This is a func to calculate the lenght two e3_point
	@author: JoMar
	@param[in]: point1
	@param[in]: point2
	@return: lenght
	*/
	inline double CalculateLenght(const E3_VECTOR &point1, const E3_VECTOR &point2);

	/*
	@brief: This is a func convert two coordinate.
	@author: JoMar
	@param[in]: origin - it's a coordinate preparing to convert.
	@param[in|out]: target - it's a coordinate convert to. The martix id of target have to be defined.
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned ConvertCoordinate(const DOBOT_POSITION &origin, DOBOT_POSITION &target);

	/*
	@brief: This is a func to modify the coordinate. If the coordinate isn't existence, it will create a new one.
	@note: Transition martix is base on the world coordinate. The convert sequence: translation->roll->ptich->yaw->zoom
	@author: JoMar
	@param[in|out]: id - coordinate id. Func will renturn a new Id, when the id isn't existence in vector;
	@param[in]: t - translation martix.
	@param[in]: r - rotation martix.
	@param[in]: zoom
	@param[in]: str - string of note
	@param[in]: strSize - the size of string
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned SetCoordinate(unsigned &id, const E3_VECTOR &t, const E3_VECTOR &r, const double &zoom, const TCHAR* const str, const unsigned &strSize);

	/*
	@brief: This is a func to modify the coordinate by using 3 special point. If the coordinate isn't existence, it will create a new one.
	@note: Transition martix is base on the world coordinate. The convert sequence: translation->roll->ptich->yaw->zoom
	@author: JoMar
	@param[in|out]: id - coordinate id. Func will renturn a new Id, when the id isn't existence in vector;
	@param[in]: p1_b - the point1 in base coordinate
	@param[in]: p2_b - the point2 in base coordinate
	@param[in]: p3_b - the point3 in base coordinate
	@param[in]: str - string of note
	@param[in]: strSize - the size of string
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned SetCoordinate(unsigned &id, const DOBOT_POSITION &p1_base, const DOBOT_POSITION &p2_base, const DOBOT_POSITION &p3_base, const TCHAR* const str, const unsigned &strSize);

	/*
	@brief: This is a func to modify the coordinate by using 3 special point. If the coordinate isn't existence, it will create a new one.
	@note: Transition martix is base on the world coordinate. The convert sequence: translation->roll->ptich->yaw->zoom
	@author: JoMar
	@param[in]: p1_b - the point1 in base coordinate
	@param[in]: p2_b - the point2 in base coordinate
	@param[in]: p3_b - the point3 in base coordinate
	@param[in|out]: p1_t - the point1 in target coordinate. Func will renturn a new coordinate id to p1_t, when the id isn't existence;
	@param[in|out]: p2_t - the point2 in target coordinate. Func will renturn a new coordinate id to p2_t, when the id isn't existence;
	@param[in|out]: p3_t - the point3 in target coordinate. Func will renturn a new coordinate id to p3_t, when the id isn't existence;
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned SetCoordinate(const DOBOT_POSITION &p1_base, const DOBOT_POSITION &p2_base, const DOBOT_POSITION &p3_base, DOBOT_POSITION &p1_target, DOBOT_POSITION &p2_target, DOBOT_POSITION &p3_target);

	/*
		@brief: This is a func to ergodic all coordinate in vector. 
		@author: JoMar
		@param[out]: coordinate
		@param[in]: reStart
		@return: if it is success, return 0; else, return a error code.
	*/
	unsigned ErgodicAllCoordinate(COORDINATE &coordinate, bool reStart = false);

	/*
	@brief: This is a func to get the id and type of the coordinate.
	@author: JoMar
	@param[in]: index - index of the coordinate in vector
	@param[out]: id - id of the coordinate
	@param[out]: type - type of the coordinate
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned GetCoordianteIdAndNote(const unsigned &index, unsigned &id, TCHAR* str, unsigned &strSize);

	/*
	@brief: This is a func to get the id of the coordinate.
	@author: JoMar
	@param[in]: index - index of the coordinate in vector
	@param[out]: id - id of the coordinate
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned GetCoordianteId(const unsigned &index, unsigned &id);

private:
	std::vector<COORDINATE> m_vector_TM;	//the vector of transition martixs.

	std::vector<COORDINATE>::iterator m_iter;//point to vector to Ergodic

	/*
	@brief: This is a func to get a new ID base on the vector.
	@author: JoMar
	@return: A new ID base on the martix vector.
	*/
	inline unsigned GetNewIdOfTransitionMartix();

// 	/*
// 	@brief: This is a func to solve the equation of a plane base on 3 point.
// 	@note: Ax+By+Cz+D=0
// 	@author: JoMar
// 	@param[in]: p1
// 	@param[in]: p2
// 	@param[in]: p3
// 	@param[out]: A
// 	@param[out]: B
// 	@param[out]: C
// 	@param[out]: D
// 	*/
// 	inline void SolPlaneEquation(const E3_VECTOR &p1, const  E3_VECTOR &p2, const E3_VECTOR &p3, double &A, double &B, double &C, double &D);




};

