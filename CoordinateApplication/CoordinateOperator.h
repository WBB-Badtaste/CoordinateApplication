#pragma once

#include "CoordinateOperatorDefine.h"
#include <vector>
#include <algorithm>

#include "DobotStatusHandle.h"

/*
@brief: This is a class witch operating the whole coordinate system.
@author: JoMar
@date: 2016-06-12
*/
class CCoordinateOperator
{
public:
	CCoordinateOperator();
	virtual ~CCoordinateOperator();

	/*
	@brief: This is a func convert a position between two coordinate.
	@param[in]: origin - it's a coordinate preparing to convert.
	@param[in|out]: target - it's a coordinate convert to. The martix id of target have to be defined.
	@return: dobot status code. Use "DobotGetStatusString" function to translate the status code.
	@author: JoMar
	@date: 2016-06-12
	*/
	DOBOT_STATUS ConvertPosition(const DOBOT_POSITION &origin, DOBOT_POSITION &target);

	/*
	@brief: This is a func to modify the coordinate. If the coordinate isn't existence, it will create a new one.
	@note: Transition martix is base on the world coordinate. The convert sequence: translation->roll->ptich->yaw->zoom
	@param[in|out]: id - coordinate id. Func will renturn a new Id, when the id isn't existence in vector;
	@param[in]: t - translation martix.
	@param[in]: r - rotation martix.
	@param[in]: zoom
	@param[in]: str - string of note
	@param[in]: strSize - the size of string
	@return:  dobot status code. Use "DobotGetStatusString" function to translate the status code.
	@author: JoMar
	@date: 2016-06-12
	*/
	DOBOT_STATUS SetCoordinate(unsigned &id, const E3_VECTOR &t, const E3_VECTOR &r, const double &zoom, const TCHAR* const str, const unsigned &strSize);

	/*
	@brief: This is a func to modify the coordinate by using 3 special point. If the coordinate isn't existence, it will create a new one.
	@param[in|out]: id - coordinate id. Func will renturn a new Id, when the id isn't existence in vector;
	@param[in]: p1_b - the point1 in base coordinate
	@param[in]: p2_b - the point2 in base coordinate
	@param[in]: p3_b - the point3 in base coordinate
	@param[in]: str - string of note
	@param[in]: strSize - the size of string
	@param[in]: bParallelX - if user wanna the porjection of X-axis of target coordinate parallel to X-axis of base coordinate, input true; else, input false.
	@note: if bParallelX equal to false, that mean the vector<p2_b, p1_b> is the X-axis dirrection of target coordinate
	@return:  dobot status code. Use "DobotGetStatusString" function to translate the status code.
	@author: JoMar
	@date: 2016-06-12
	*/
	DOBOT_STATUS SetCoordinate(unsigned &id, const DOBOT_POSITION &p1_base, const DOBOT_POSITION &p2_base, const DOBOT_POSITION &p3_base, const TCHAR* const str, const unsigned &strSize, const bool& bParallelX = false);

	/*
	@brief: This is a func to delete the coordinate 
	@param[in]: id - coordinate id. 
	@return:  dobot status code. Use "DobotGetStatusString" function to translate the status code.
	@author: JoMar
	@date: 2016-06-12
	*/
	DOBOT_STATUS DeleteCoordinate(const unsigned& id);

	/*
	@brief: This is a func to ergodic all coordinate in vector. 
	@param[out]: coordinate
	@param[in]: reStart
	@return: dobot status code. Use "DobotGetStatusString" function to translate the status code.
	@author: JoMar
	@date: 2016-06-12
	*/
	DOBOT_STATUS ErgodicAllCoordinate(COORDINATE &coordinate, bool reStart = false);

	/*
	@brief: This is a func to get the id and type of the coordinate.
	@param[in]: index - index of the coordinate in vector
	@param[out]: id - id of the coordinate
	@param[out]: type - type of the coordinate
	@return: dobot status code. Use "DobotGetStatusString" function to translate the status code.
	@author: JoMar
	@date: 2016-06-12
	*/
	DOBOT_STATUS GetCoordianteIdAndNote(const unsigned &index, unsigned &id, TCHAR* str, unsigned &strSize);

	/*
	@brief: This is a func to get the id of the coordinate.
	@param[in]: index - index of the coordinate in vector
	@param[out]: id - id of the coordinate
	@return: dobot status code. Use "DobotGetStatusString" function to translate the status code.
	@author: JoMar
	@date: 2016-06-12
	*/
	DOBOT_STATUS GetCoordianteId(const unsigned &index, unsigned &id);

private:
	/*
	@brief: the vector storing transition martixs.
	@author: JoMar
	@date: 2016-06-12
	*/
	std::vector<COORDINATE> m_vector_TM;	

	/*
	@brief: a point witch pointing the vector used in ergodicing
	@author: JoMar
	@date: 2016-06-12
	*/
	std::vector<COORDINATE>::const_iterator m_iter;

	/*
	@brief: This is a func to get a new ID base on the vector.
	@return: A new ID base on the martix vector.
	@author: JoMar
	@date: 2016-06-12
	*/
	inline unsigned GetNewIdOfTransitionMartix();

	/*
	@brief: This is a callback function to ascending sort the vector by id
	@author: JoMar
	@date: 2016-06-12
	*/
	static bool AscendingSortById(const COORDINATE& coordinate1, const COORDINATE& coordinate2);
};

