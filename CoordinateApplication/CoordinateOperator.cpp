#include "stdafx.h"
#include "CoordinateOperator.h"
#include <math.h>


CCoordinateOperator::CCoordinateOperator()
{
	m_iter = m_vector_TM.begin();
	E3_VECTOR t;
	E3_VECTOR r;
	double zoom(1.0);
	unsigned id;

	TCHAR *str(_T("世界坐标系"));
	SetCoordinate(id, t, r, zoom, str, _tcslen(str));
}

CCoordinateOperator::~CCoordinateOperator()
{
}

unsigned CCoordinateOperator::GetNewIdOfTransitionMartix()
{
	if (m_vector_TM.size() < 1)
		return 0;//the vector of transition martix is empty, return 0.
	else
		return (m_vector_TM.end() - 1)->coordinate_id + 1;//the vector of transition martix isn't empty, return (id + 1) of last element.
														  //There is a bug when the id is too big.
}

unsigned CCoordinateOperator::SetCoordinate
(unsigned &id
,const E3_VECTOR &t
, const E3_VECTOR &r
, const double &zoom
, const TCHAR* const str
, const unsigned &strSize)
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
				iter->Reset(t, r, zoom, note);
				return 0;
			}
		}
	}

	id = GetNewIdOfTransitionMartix();

	//Create a new martix base on the auto id.
    COORDINATE coordinate(t, r, id, zoom, note);
	m_vector_TM.push_back(coordinate);

	return 0;
}

unsigned CCoordinateOperator::SetCoordinate
( unsigned &id
, const DOBOT_POSITION &p1_base
, const DOBOT_POSITION &p2_base
, const DOBOT_POSITION &p3_base
, const TCHAR* const str
, const unsigned &strSize)
{
	if (p1_base.coordinate_id != p2_base.coordinate_id || p1_base.coordinate_id != p3_base.coordinate_id)
		return 1;//Have to be modify.

	double a(CalRadian(p2_base.position - p1_base.position, p3_base.position - p1_base.position));
	if (CalRadian(p2_base.position - p1_base.position, p3_base.position - p1_base.position) != M_PI_2)
		return 1;//Have to be modify

	//calculate the position of 3 points in the world coordinate.
	DOBOT_POSITION p1_buffer(WORLD_COORDINATE_ID);
	DOBOT_POSITION p2_buffer(WORLD_COORDINATE_ID);
	DOBOT_POSITION p3_buffer(WORLD_COORDINATE_ID);
	ConvertCoordinate(p1_base, p1_buffer);
	ConvertCoordinate(p2_base, p2_buffer);
	ConvertCoordinate(p3_base, p3_buffer);

	//calculate the position of 3 points in the target coordinate.
	//It have be defined that point1 is the origin, point2 on x axis and point3 on y axis. 
	E3_VECTOR position1_target(0, 0, 0);
	E3_VECTOR position2_target((p2_buffer.position - p1_buffer.position).Module(), 0, 0);
	E3_VECTOR position3_target(0, (p3_buffer.position - p1_buffer.position).Module(), 0);

	E3_MARTIX t_target;
	t_target = -p1_buffer.position;

	p1_buffer.position.Translation(t_target);
	p2_buffer.position.Translation(t_target);
	p3_buffer.position.Translation(t_target);

 	//solve the normal Vector of plane with p2_buffer, p3_buffer and origin.
	E3_VECTOR normalVector(p2_buffer.position * p3_buffer.position);

	E3_MARTIX r_target;

	//rotate the normal Vector to parallel to z axis by an angle. And this angle is the x angle of the rotation martix.
	//!!pay attention to let normalVector on xz-plane of world coordinate
	r_target.x = M_PI_2 - atan2(normalVector.z, normalVector.y);
	normalVector.Roll(r_target.x);
	p2_buffer.position.Roll(r_target.x);

	//rotate the normal Vector to parallel to z axis by an angle. And this angle is the y angle of the rotation martix.
	//!!pay attention to let normalVector on Z axis of world coordinate
	r_target.y = -atan2(normalVector.x, normalVector.z);
	p2_buffer.position.Pitch(r_target.y);

	//rotate the normal Vector to parallel to z axis by an angle. And this angle is the z angle of the rotation martix.
	//!!pay attention to let p2_buffer on x axis of target coordinate
	r_target.z = -atan2(p2_buffer.position.y, p2_buffer.position.x);

	return SetCoordinate(id, t_target, r_target, COORDINATE_DEFAULT_ZOOM, str, strSize );
}

//Have not be finlished.
unsigned CCoordinateOperator::SetCoordinate(const DOBOT_POSITION &p1_base, const DOBOT_POSITION &p2_base, const DOBOT_POSITION &p3_base, DOBOT_POSITION &p1_target, DOBOT_POSITION &p2_target, DOBOT_POSITION &p3_target)
{
	if (p1_base.coordinate_id != p2_base.coordinate_id || p1_base.coordinate_id != p3_base.coordinate_id)
		return 1;//Have to be modify.

	if (p1_target.coordinate_id != p2_target.coordinate_id || p1_target.coordinate_id != p3_target.coordinate_id)
		return 1;//Have to be modify.

	//calculate the position of 3 points in the world coordinate.
	DOBOT_POSITION p1_world(WORLD_COORDINATE_ID), p2_world(WORLD_COORDINATE_ID), p3_world(WORLD_COORDINATE_ID);

	ConvertCoordinate(p1_base, p1_world);
	ConvertCoordinate(p2_base, p2_world);
	ConvertCoordinate(p3_base, p3_world);

// 	//calculate the transfer martix of the plane consist of 3 points. It's a buffer transfer martix.
// 	E3_VECTOR t_plane;
// 	t_plane = p1_world.position;
// 
// 	E3_VECTOR r_plane;
// 	r_plane.x = atan2(p3_world.position.z - p1_world.position.z, p3_world.position.y - p1_world.position.y);
// 	Roll(p1_world, r_plane.x);
// 	Roll(p2_world, r_plane.x);
// 	r_plane.y = atan2(p3_world.position.z - p1_world.position.z, p3_world.position.x - p1_world.position.x);
// 	r_plane.z = 0;
// 
// 	double zoom(1.0);//cause of using 3 points in world coordinate to calculate the plane coordinate, zoom have to be 1.0;
// 	unsigned planeCoordinateId(0);
// 		 
// 	SetCoordinate(planeCoordinateId, PLANE_COORDINATE, t_plane, r_plane, zoom);


	//calculate the transfer martix of the target coordinate.

	//calculate the zoom
	double lenght1_world((p1_world.position - p2_world.position).Module());
	double lenght2_world((p1_world.position - p3_world.position).Module());
	double lenght3_world((p2_world.position - p3_world.position).Module());

	double lenght1_target((p1_target.position - p2_target.position).Module());
	double lenght2_target((p1_target.position - p3_target.position).Module());
	double lenght3_target((p2_target.position - p3_target.position).Module());

	double zoom_target((lenght1_target + lenght2_target + lenght3_target) / (lenght1_world + lenght2_world + lenght3_world));

	DOBOT_POSITION buffer1, buffer2, buffer3;
	buffer1 = p1_target;
	buffer2 = p2_target;
	buffer3 = p3_target;

	buffer1.position.x /= zoom_target;
	buffer1.position.y /= zoom_target;
	buffer1.position.z /= zoom_target;
	buffer2.position.x /= zoom_target;
	buffer2.position.y /= zoom_target;
	buffer2.position.z /= zoom_target;
	buffer3.position.x /= zoom_target;
	buffer3.position.y /= zoom_target;
	buffer3.position.z /= zoom_target;

	E3_VECTOR r_target;
	r_target.z = 0;

//	r_target.y = atan2()

		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	//修改目标坐标系ID

	return 0;
}


unsigned CCoordinateOperator::ConvertCoordinate(const DOBOT_POSITION &origin, DOBOT_POSITION &target)
{
	if (origin.coordinate_id == target.coordinate_id)
	{
		target = origin;
		return 0;
	}

	DOBOT_POSITION buffer;
	buffer.position = origin.position;

	std::vector<COORDINATE>::iterator iter;

	//Convert to world coordinate first.
	if (origin.coordinate_id != WORLD_COORDINATE_ID)
	{
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
			if (iter->coordinate_id == origin.coordinate_id)
				break;
		
		if (iter == m_vector_TM.end())
			return 1;//Have to be modified.

		//zoom
		buffer.position.x /= iter->zoom;
		buffer.position.y /= iter->zoom;
		buffer.position.z /= iter->zoom;

		//Rotate
		buffer.position.InvRotate(-(iter->r));

		//translation
		buffer.position.Translation(-(iter->t));
	}

	target.position = buffer.position;

	//Convert to target coordinate.
	if (target.coordinate_id != WORLD_COORDINATE_ID)
	{
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
			if (iter->coordinate_id == target.coordinate_id)
				break;

		if (iter == m_vector_TM.end())
			return 1;//Have to be modified.

		//translation
		target.position.Translation(iter->t);

		//Rotate
		target.position.Rotate(iter->r);

		//zoom
		target.position.x *= iter->zoom;
		target.position.y *= iter->zoom;
		target.position.z *= iter->zoom;
	}

	return 0;
}

unsigned CCoordinateOperator::ErgodicAllCoordinate(COORDINATE &coordinate, bool reStart/* = false*/)
{
	if (m_vector_TM.size() < 1)
		return 1;//have to be modify

	if (reStart)
		m_iter = m_vector_TM.begin();
	else
		++m_iter;

	if (m_iter == m_vector_TM.end())
		return 1;//have to be modify

	coordinate = *m_iter;
	
	return 0;
}

unsigned CCoordinateOperator::GetCoordianteIdAndNote(const unsigned &index, unsigned &id, TCHAR* str, unsigned &strSize)
{
	std::vector<COORDINATE>::iterator iter;
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
			return 0;
		}
	}
	return 1;//have to be modify

}

unsigned CCoordinateOperator::GetCoordianteId(const unsigned &index, unsigned &id)
{
	std::vector<COORDINATE>::iterator iter;
	unsigned i(0);
	for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter, ++i)
	{
		if (i == index)
		{
			id = iter->coordinate_id;
			return 0;
		}
	}
	return 1;//have to be modify
}

// void CCoordinateOperator::SolPlaneEquation(const E3_VECTOR &p1, const E3_VECTOR &p2, const E3_VECTOR &p3, double &A, double &B, double &C, double &D)
// {
// 	E3_VECTOR p1p2(p2 - p1);
// 	E3_VECTOR p1p3(p3 - p1);
// 
// 	E3_VECTOR normalVector(p1p2 * p1p3);
// 
// 	A = normalVector.x;
// 	B = normalVector.y;
// 	C = normalVector.z;
// 	D = -p1.x * normalVector.x - p1.y * normalVector.y - p1.z * normalVector.z;
// }