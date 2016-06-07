#pragma once

//There is a only one world coordinate, it has a special ID witch is 0.
const unsigned WORLD_COORDINATE_ID(0);

const double COORDINATE_DEFAULT_ZOOM(1.0);

const double M_PI(3.14159265358979323846);

const double M_PI_2(M_PI / 2);

// //the enum of coordinate types
// typedef enum _coordinate_type
// {
// 	WORLD_COORDINATE,		//The base coordinate of whole coordinate system.
// 	KINEMATIC_COORDINATE,	//The coordinate of kinematic.
// 	PALLET_COORDINATE,		//The coordinate of a plane.
// }COORDINATE_TYPE;

//the struct of vector
typedef struct _e3_vector
{
	_e3_vector() :x(0), y(0), z(0){};
	_e3_vector(double newX, double newY, double newZ) : x(newX), y(newY), z(newZ){};

	_e3_vector& operator=(const _e3_vector& newObject)
	{
		x = newObject.x;
		y = newObject.y;
		z = newObject.z;
		return *this;
	};

	_e3_vector operator-()
	{
		return _e3_vector(-x, -y, -z);
	};

	friend _e3_vector operator-(const _e3_vector& newObjectL, const _e3_vector& newObjectR)
	{
		return _e3_vector(newObjectL.x - newObjectR.x, newObjectL.y - newObjectR.y, newObjectL.z - newObjectR.z);
	};

	friend _e3_vector operator*(const _e3_vector& newObjectL, const _e3_vector& newObjectR)
	{
		return _e3_vector
			(newObjectL.y * newObjectR.z - newObjectL.z * newObjectR.y
			,newObjectL.z * newObjectR.x - newObjectL.x * newObjectR.z
			,newObjectL.x * newObjectR.y - newObjectL.y * newObjectR.x);
	};

	_e3_vector& operator+=(const _e3_vector& newObject)
	{
		x += newObject.x;
		y += newObject.y;
		z += newObject.z;
		return *this;
	};

	double x;
	double y;
	double z;

}E3_VECTOR;

//the strust of position
typedef struct _dobot_position
{
	_dobot_position() :coordinate_id(0),type(WORLD_COORDINATE){};

	_dobot_position(const E3_VECTOR &point) :coordinate_id(0), type(WORLD_COORDINATE), position(point){};

	_dobot_position(const unsigned &id, const COORDINATE_TYPE &type) :coordinate_id(id), type(type){};

	_dobot_position& operator=(const _dobot_position& newObject)
	{
		this->coordinate_id = newObject.coordinate_id;
		this->type = newObject.type;
		this->position = newObject.position;
		return *this;
	};

	unsigned coordinate_id;
	COORDINATE_TYPE type;
	E3_VECTOR position;
}DOBOT_POSITION;

//the strust of transition matrix
typedef struct _transition_matrix
{
	_transition_matrix() :coordinate_id(0), type(WORLD_COORDINATE), zoom(1.0){};
	_transition_matrix(const COORDINATE_TYPE &newType, const E3_VECTOR &newT, const E3_VECTOR &newR, const unsigned &newId, const double &newZoom) :type(newType), t(newT), r(newR), coordinate_id(newId), zoom(newZoom){};

	void Rest(COORDINATE_TYPE newType, E3_VECTOR newT, E3_VECTOR newR, double newZoom)
	{
		type = newType;
		t = newT;
		r = newR;
		zoom = newZoom;
	};

	unsigned coordinate_id;
	COORDINATE_TYPE type;
	E3_VECTOR t;
	E3_VECTOR r;
	double zoom;
}TRANSITION_MATRIX;