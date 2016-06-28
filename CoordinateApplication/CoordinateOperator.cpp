#include "stdafx.h"
#include "CoordinateOperator.h"
#include <math.h>


CCoordinateOperator::CCoordinateOperator()
{
	m_iter = m_vector_TM.begin();
	unsigned id;
	COORDINATE_MATRIX invMatrix;
	invMatrix <<
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	COORDINATE_MATRIX forMatrix(invMatrix.inverse());
	TCHAR *str(_T("世界坐标系"));
	SetCoordinate(id, forMatrix, invMatrix, str, _tcslen(str));
}

CCoordinateOperator::~CCoordinateOperator()
{
}

unsigned CCoordinateOperator::GetNewIdOfTransitionMartix()
{
	if (m_vector_TM.size() < 1)
		return 0;//the vector of transition martix is empty, return 0.
	else
	{
		unsigned id(0);
		std::vector<COORDINATE>::const_iterator iter;
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter, ++id)
		{
			if (id != iter->coordinate_id)
				break;
		}
		return id;
	}
}

DOBOT_STATUS CCoordinateOperator::SetCoordinate
( unsigned &id
, const COORDINATE_MATRIX &forwordMartix
, const COORDINATE_MATRIX &inverseMartix
, const TCHAR* const str
, const unsigned &strSize
)
{
	NOTE note(strSize, str);

	if (id)
	{
		//if user input the id, check the martix is in the vector or not.
		std::vector<COORDINATE>::iterator iter;
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
		{
			if (iter->coordinate_id == id)
			{
				iter->Reset(note, forwordMartix, inverseMartix);
				return DOBOT_SUC_COORD_MODIFY;
			}
		}
	}

	id = GetNewIdOfTransitionMartix();

	//Create a new martix base on the auto id.
	COORDINATE coordinate(id, note, forwordMartix, inverseMartix);
	m_vector_TM.push_back(coordinate);

	//sort the vector
	std::sort(m_vector_TM.begin(), m_vector_TM.end(), AscendingSortById);

	return DOBOT_SUC_COORD_CREATE;
}

/*
DOBOT_STATUS CCoordinateOperator::SetCoordinate
( unsigned &id
, const DOBOT_POSITION &p1_base
, const DOBOT_POSITION &p2_base
, const DOBOT_POSITION &p3_base
, const TCHAR* const str
, const unsigned &strSize
, const bool& bParallelX)
{
	if (p1_base.coordinate_id != p2_base.coordinate_id || p1_base.coordinate_id != p3_base.coordinate_id)
		return DOBOT_ERR_COORD_SET_MULTI_BASE;

	//calculate the position of 3 points in the world coordinate.
	DOBOT_POSITION p1_buffer(WORLD_COORDINATE_ID);
	DOBOT_POSITION p2_buffer(WORLD_COORDINATE_ID);
	DOBOT_POSITION p3_buffer(WORLD_COORDINATE_ID);
	ConvertPosition(p1_base, p1_buffer);
	ConvertPosition(p2_base, p2_buffer);
	ConvertPosition(p3_base, p3_buffer);

	E3_MARTIX t_target;
	t_target = -p1_buffer.position;

	p2_buffer.position.Translation(t_target); 
	p3_buffer.position.Translation(t_target);

	//solve the normal Vector of plane with p2_buffer, p3_buffer and origin.
	//p1_buffer become (0,0,0) after translate
	E3_VECTOR normalVector(p2_buffer.position * p3_buffer.position);

	E3_MARTIX r_target;

	//rotate the normal Vector to parallel to xz-plane by an angle. And this angle is the x angle of the rotation martix.
	r_target.x = M_PI_2 - atan2(normalVector.z, normalVector.y);
	normalVector.Roll(r_target.x);

	//rotate the normal Vector to parallel to z axis by an angle. And this angle is the y angle of the rotation martix.
	r_target.y = -atan2(normalVector.x, normalVector.z);

	p2_buffer.position.Roll(r_target.x);
	p2_buffer.position.Pitch(r_target.y);

	if (bParallelX)
	{
		//rotate the x Vector to parallel to x axis by an angle. And this angle is the z angle of the rotation martix.
		DOBOT_POSITION xDirection(p1_base.coordinate_id, E3_VECTOR(1,0,0));
		xDirection.position.Roll(r_target.x);
		xDirection.position.Pitch(r_target.y);
		r_target.z = -atan2(p2_buffer.position.y - xDirection.position.y, p2_buffer.position.x- xDirection.position.x);
	}
	else
	{
		//rotate the x Vector to parallel to x axis by an angle. And this angle is the z angle of the rotation martix.
		r_target.z = -atan2(p2_buffer.position.y, p2_buffer.position.x);
	}
	
	return SetCoordinate(id, t_target, r_target, COORDINATE_DEFAULT_ZOOM, str, strSize);
}
*/

DOBOT_STATUS CCoordinateOperator::SetCoordinate
(unsigned &id
, const DOBOT_POSITION &p1_base
, const DOBOT_POSITION &p2_base
, const DOBOT_POSITION &p3_base
, const TCHAR* const str
, const unsigned &strSize
, const bool& bParallelX/* = false*/)
{
	if (p1_base.coordinate_id != p2_base.coordinate_id || p1_base.coordinate_id != p3_base.coordinate_id)
		return DOBOT_ERR_COORD_SET_MULTI_BASE;

	//calculate the position of 3 points in the world coordinate.
	DOBOT_POSITION p1_world(WORLD_COORDINATE_ID);
	DOBOT_POSITION p2_world(WORLD_COORDINATE_ID);
	DOBOT_POSITION p3_world(WORLD_COORDINATE_ID);
	ConvertPosition(p1_base, p1_world);
	ConvertPosition(p2_base, p2_world);
	ConvertPosition(p3_base, p3_world);

	E3_PLANE plane1(p1_world.position, p2_world.position - p1_world.position, p3_world.position - p1_world.position);
	E3_PLANE plane2(p2_world.position, p1_world.position);
	E3_PLANE plane2(p3_world.position, p1_world.position);

	E3_VECTOR zVector(plane1.NormalVector());
	E3_VECTOR xVector(plane2.NormalVector());

	E3_VECTOR zDireCos(zVector / zVector.dot(zVector));
	E3_VECTOR xDireCos(xVector / xVector.dot(xVector));
	E3_VECTOR yDireCos(zDireCos.cross(xVector));

	COORDINATE_MATRIX invMatrix;
	invMatrix << 
		xDireCos(0), xDireCos(1), xDireCos(2), 0,
		yDireCos(0), yDireCos(1), yDireCos(2), 0,
		zDireCos(0), zDireCos(1), zDireCos(2), 0,
		p1_world.position(0), p1_world.position(1), p1_world.position(2), COORDINATE_DEFAULT_ZOOM;

	COORDINATE_MATRIX forMatrix(invMatrix.inverse());

	return SetCoordinate(id, forMatrix, invMatrix, str, strSize);
}

DOBOT_STATUS CCoordinateOperator::DeleteCoordinate(const unsigned& id)
{
	std::vector<COORDINATE>::const_iterator iter;
	for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
	{
		if (id == iter->coordinate_id)
		{
			m_vector_TM.erase(iter);
			m_iter = m_vector_TM.begin();

			std::sort(m_vector_TM.begin(), m_vector_TM.end(), AscendingSortById);

			return DOBOT_SUC_COORD_DEL;
		}
	}
	return DOBOT_ERR_COORD_DEL_ID_NONEXISTENT;
}

DOBOT_STATUS CCoordinateOperator::ConvertPosition(const DOBOT_POSITION &origin, DOBOT_POSITION &target)
{
	if (origin.coordinate_id == target.coordinate_id)
	{
		target = origin;
		return DOBOT_WAR_COORD_CONVERT_SAME;
	}
	
	E3_POINT worldPosition(origin.position);

	std::vector<COORDINATE>::const_iterator iter;

	//Convert to world coordinate first.
	if (origin.coordinate_id != WORLD_COORDINATE_ID)
	{
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
			if (iter->coordinate_id == origin.coordinate_id)
				break;
		
		if (iter == m_vector_TM.end())
			return DOBOT_ERR_COORD_CONVERT_ORIGIN_NONEXISTENT;

		//inverse convert
		CONVERT_VECTOR vOrigin, vTarget;
		vOrigin << origin.position(0), origin.position(1), origin.position(2), 1.0;

		vTarget = iter->inverseMartix * vOrigin;

		worldPosition(0) = vTarget(0) / vTarget(3);
		worldPosition(1) = vTarget(1) / vTarget(3);
		worldPosition(2) = vTarget(2) / vTarget(3);
	}

	target.position = worldPosition;

	//Convert to target coordinate.
	if (target.coordinate_id != WORLD_COORDINATE_ID)
	{
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
			if (iter->coordinate_id == target.coordinate_id)
				break;

		if (iter == m_vector_TM.end())
			return DOBOT_ERR_COORD_CONVERT_TARGET_NONEXISTENT;

		//forword convert
		CONVERT_VECTOR vOrigin, vTarget;
		vOrigin << worldPosition(0), worldPosition(1), worldPosition(2), 1.0;

		vTarget = iter->forwordMartix * vOrigin;

		target.position(0) = vTarget(0) / vTarget(3);
		target.position(1) = vTarget(1) / vTarget(3);
		target.position(2) = vTarget(2) / vTarget(3);
	}

	return DOBOT_SUC_COORD_CONVERT;
}

DOBOT_STATUS CCoordinateOperator::ErgodicAllCoordinate(COORDINATE &coordinate, bool reStart/* = false*/)
{
	if (m_vector_TM.size() < 1)
		return DOBOT_ERR_COORD_ERGODIC_EMPTY;

	if (reStart)
		m_iter = m_vector_TM.begin();
	else
		++m_iter;

	if (m_iter == m_vector_TM.end())
		return DOBOT_WAR_COORD_ERGODIC_END;

	coordinate = *m_iter;
	
	return DOBOT_SUC_COORD_ERGODIC;
}

DOBOT_STATUS CCoordinateOperator::GetCoordianteIdAndNote(const unsigned &index, unsigned &id, TCHAR* str, unsigned &strSize)
{
	std::vector<COORDINATE>::const_iterator iter;
	unsigned i(0);
	for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter, ++i)
	{
		if (i == index)
		{
			id = iter->coordinate_id;
			strSize = iter->note.sizeOfStr;
			unsigned i(0);
			for (; i < strSize; ++i)
			{
				*(str + i) = *(iter->note.str + i);
			}
			*(str + i) = '\0';
			return DOBOT_SUC_COORD_GET_ID_NOTE;
		}
	}
	return DOBOT_ERR_COORD_GET_ID_NOTE;

}

DOBOT_STATUS CCoordinateOperator::GetCoordianteId(const unsigned &index, unsigned &id)
{
	std::vector<COORDINATE>::const_iterator iter;
	unsigned i(0);
	for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter, ++i)
	{
		if (i == index)
		{
			id = iter->coordinate_id;
			return DOBOT_SUC_COORD_GET_ID;
		}
	}
	return DOBOT_ERR_COORD_GET_ID;
}

bool CCoordinateOperator::AscendingSortById(const COORDINATE& coordinate1, const COORDINATE& coordinate2)
{
	return coordinate1.coordinate_id < coordinate2.coordinate_id;
}