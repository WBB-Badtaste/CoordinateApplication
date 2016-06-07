#include "stdafx.h"
#include "CoordinateOperator.h"
#include <math.h>


CCoordinateOperator::CCoordinateOperator()
{
	m_iter = m_vector_TM.begin();
	E3_VECTOR t;
	E3_VECTOR r;
	double zoom(1.0);
	COORDINATE_TYPE type(WORLD_COORDINATE);
	unsigned id;
	SetCoordinate(id, WORLD_COORDINATE, t, r, zoom);
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

unsigned CCoordinateOperator::SetCoordinate(unsigned &id, const COORDINATE_TYPE &type, const E3_VECTOR &t, const E3_VECTOR &r, const double &zoom)
{
	if (id)
	{
		//if user input the id, check the martix is in the vector or not.
		std::vector<TRANSITION_MATRIX>::iterator iter;
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
		{
			if (iter->coordinate_id == id)
			{
				iter->Rest(type, t, r, zoom);
				return 0;
			}
		}
	}

	id = GetNewIdOfTransitionMartix();

	if (id && type == WORLD_COORDINATE)
		return 1;//Have to modify. the world coordinate is only one.

	//Create a new martix base on the auto id.
    TRANSITION_MATRIX transition_martix(type, t, r, id, zoom);
	m_vector_TM.push_back(transition_martix);

	return 0;
}

unsigned CCoordinateOperator::SetCoordinate(unsigned &id, const COORDINATE_TYPE &type, const DOBOT_POSITION &p1_base, const DOBOT_POSITION &p2_base, const DOBOT_POSITION &p3_base)
{
	if (p1_base.coordinate_id != p2_base.coordinate_id || p1_base.coordinate_id != p3_base.coordinate_id)
		return 1;//Have to be modify.

	//calculate the position of 3 points in the world coordinate.
	DOBOT_POSITION p1_buffer(WORLD_COORDINATE_ID, WORLD_COORDINATE);
	DOBOT_POSITION p2_buffer(WORLD_COORDINATE_ID, WORLD_COORDINATE);
	DOBOT_POSITION p3_buffer(WORLD_COORDINATE_ID, WORLD_COORDINATE);
	ConvertCoordinate(p1_base, p1_buffer);
	ConvertCoordinate(p2_base, p2_buffer);
	ConvertCoordinate(p3_base, p3_buffer);

	//calculate the position of 3 points in the target coordinate.
	//It have be defined that point1 is the origin, point2 on x axis and point3 on y axis. 
	E3_VECTOR position1_target(0, 0, 0);
	E3_VECTOR position2_target(CalculateLenght(p2_buffer.position, p1_buffer.position), 0, 0);
	E3_VECTOR position3_target(0, CalculateLenght(p3_buffer.position, p1_buffer.position), 0);

	E3_VECTOR t_target;
	t_target = -p1_buffer.position;

	Translation(p1_buffer.position, t_target);
	Translation(p2_buffer.position, t_target);
	Translation(p3_buffer.position, t_target);

 	//solve the normal Vector of plane with p2_buffer, p3_buffer and origin.
	E3_VECTOR normalVector(p2_buffer.position * p3_buffer.position);

	E3_VECTOR r_target;

	//rotate the normal Vector to parallel to z axis by an angle. And this angle is the x angle of the rotation martix.
	//!!pay attention to let normalVector on xz-plane of world coordinate
	r_target.x = M_PI_2 - atan2(normalVector.z, normalVector.y);
	Roll(normalVector, r_target.x);
	Roll(p2_buffer.position, r_target.x);

	//rotate the normal Vector to parallel to z axis by an angle. And this angle is the y angle of the rotation martix.
	//!!pay attention to let normalVector on Z axis of world coordinate
	r_target.y = -atan2(normalVector.x, normalVector.z);
	Pitch(p2_buffer.position, r_target.y);

	//rotate the normal Vector to parallel to z axis by an angle. And this angle is the z angle of the rotation martix.
	//!!pay attention to let p2_buffer on x axis of target coordinate
	r_target.z = -atan2(p2_buffer.position.y, p2_buffer.position.x);

	return SetCoordinate(id, type, t_target, r_target, COORDINATE_DEFAULT_ZOOM);
}

//Have not be finlished.
unsigned CCoordinateOperator::SetCoordinate(const DOBOT_POSITION &p1_base, const DOBOT_POSITION &p2_base, const DOBOT_POSITION &p3_base, DOBOT_POSITION &p1_target, DOBOT_POSITION &p2_target, DOBOT_POSITION &p3_target)
{
	if (p1_base.coordinate_id != p2_base.coordinate_id || p1_base.coordinate_id != p3_base.coordinate_id)
		return 1;//Have to be modify.

	if (p1_target.coordinate_id != p2_target.coordinate_id || p1_target.coordinate_id != p3_target.coordinate_id)
		return 1;//Have to be modify.

	//calculate the position of 3 points in the world coordinate.
	DOBOT_POSITION p1_world, p2_world, p3_world;
	p1_world.coordinate_id = p2_world.coordinate_id = p3_world.coordinate_id = 0;
	p1_world.type = p2_world.type = p3_world.type = WORLD_COORDINATE;

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
	double lenght1_world(CalculateLenght(p1_world.position, p2_world.position));
	double lenght2_world(CalculateLenght(p1_world.position, p3_world.position));
	double lenght3_world(CalculateLenght(p2_world.position, p3_world.position));

	double lenght1_target(CalculateLenght(p1_target.position, p2_target.position));
	double lenght2_target(CalculateLenght(p1_target.position, p3_target.position));
	double lenght3_target(CalculateLenght(p2_target.position, p3_target.position));

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

void CCoordinateOperator::Roll(E3_VECTOR &point, const double &angle)
{
	double buffer(0.0);

	 buffer = point.y * cos(angle) - point.z * sin(angle);
	point.z = point.y * sin(angle) + point.z * cos(angle);
	point.y = buffer;
}

void CCoordinateOperator::Pitch(E3_VECTOR &point, const double &angle)
{
	double buffer(0.0);
	 buffer = point.z * cos(angle) - point.x * sin(angle);
	point.x = point.z * sin(angle) + point.x * cos(angle);
	point.z = buffer;
}

void CCoordinateOperator::Yaw(E3_VECTOR &point, const double &angle)
{
	double buffer(0.0);
	 buffer = point.x * cos(angle) - point.y * sin(angle);
	point.y = point.x * sin(angle) + point.y * cos(angle);
	point.x = buffer;
}

void CCoordinateOperator::Translation(E3_VECTOR &point, const E3_VECTOR &t)
{
	point += t;
}

double CCoordinateOperator::CalculateVectorModule(const E3_VECTOR &vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

double CCoordinateOperator::CalculateLenght(const E3_VECTOR &point1, const E3_VECTOR &point2)
{
	return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) + (point1.z - point2.z) * (point1.z - point2.z));
}

unsigned CCoordinateOperator::ConvertCoordinate(const DOBOT_POSITION &origin, DOBOT_POSITION &target)
{
	if (origin.type == target.type)
	{
		target = origin;
		return 0;
	}

	DOBOT_POSITION buffer;
	buffer.position = origin.position;
	buffer.type = WORLD_COORDINATE;

	std::vector<TRANSITION_MATRIX>::iterator iter;

	//Convert to world coordinate first.
	if (origin.type != WORLD_COORDINATE)
	{
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
			if (iter->coordinate_id == origin.coordinate_id)
				break;
		
		if (iter == m_vector_TM.end() || iter->type != origin.type)
			return 1;//Have to be modified.

		//zoom
		buffer.position.x /= iter->zoom;
		buffer.position.y /= iter->zoom;
		buffer.position.z /= iter->zoom;

		//Rotate
		Yaw(buffer.position, -iter->r.z);
		Pitch(buffer.position, -iter->r.y);
		Roll(buffer.position, -iter->r.x);

		//translation
		Translation(buffer.position, -(iter->t));
	}

	target.position = buffer.position;
	target.type = WORLD_COORDINATE;

	//Convert to target coordinate.
	if (target.type != WORLD_COORDINATE)
	{
		for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter)
			if (iter->coordinate_id == target.coordinate_id)
				break;

		if (iter == m_vector_TM.end())
			return 1;//Have to be modified.

		target.type = iter->type;

		//translation
		Translation(buffer.position, iter->t);

		//Rotate
		Roll(target.position, iter->r.x);
		Pitch(target.position, iter->r.y);
		Yaw(target.position, iter->r.z);

		//zoom
		target.position.x *= iter->zoom;
		target.position.y *= iter->zoom;
		target.position.z *= iter->zoom;
	}

	return 0;
}

unsigned CCoordinateOperator::ErgodicAllCoordinate(TRANSITION_MATRIX &coordinate, bool reStart)
{
	unsigned coordinateAmount(m_vector_TM.size());
	if (coordinateAmount < 1)
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

unsigned CCoordinateOperator::GetCoordianteIdAndType(const unsigned &index, unsigned &id, COORDINATE_TYPE &type)
{
	std::vector<TRANSITION_MATRIX>::iterator iter;
	unsigned i(0);
	for (iter = m_vector_TM.begin(); iter != m_vector_TM.end(); ++iter, ++i)
	{
		if (i == index)
		{
			id = iter->coordinate_id;
			type = iter->type;
			return 0;
		}
	}
	return 1;//have to be modify

}

unsigned CCoordinateOperator::GetCoordianteId(const unsigned &index, unsigned &id)
{
	std::vector<TRANSITION_MATRIX>::iterator iter;
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