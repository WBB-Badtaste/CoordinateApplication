#pragma once

//There is a only one world coordinate, it has a special ID witch is 0.
const unsigned WORLD_COORDINATE_ID(0);

const double COORDINATE_DEFAULT_ZOOM(1.0);

const double M_PI(3.14159265358979323846);

const double M_PI_2(M_PI / 2);

//the struct of vector
typedef struct _e3_vector
{
	_e3_vector() :x(0), y(0), z(0){};

	_e3_vector(const _e3_vector& newObject) : x(newObject.x), y(newObject.y), z(newObject.z){};

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
	unsigned coordinate_id;
	E3_VECTOR position;

	_dobot_position() :coordinate_id(0){};

	_dobot_position(const _dobot_position& newObject) :coordinate_id(newObject.coordinate_id), position(newObject.position){};

	_dobot_position(const E3_VECTOR &point) :coordinate_id(0), position(point){};

	_dobot_position(const unsigned &id) :coordinate_id(id){};

	_dobot_position& operator=(const _dobot_position& newObject)
	{
		coordinate_id = newObject.coordinate_id;
		position = newObject.position;
		return *this;
	};

	
}DOBOT_POSITION;


typedef struct _note
{
	unsigned sizeOfStr;
	TCHAR *str;

	_note() :sizeOfStr(0), str(nullptr){};

	_note(const _note& newObject): sizeOfStr(newObject.sizeOfStr)
	{
		str = new TCHAR[sizeOfStr + 1]();
		unsigned i(0);
		for (; i < sizeOfStr; ++i)
		{
			str[i] = newObject.str[i];
		}
		str[i] = '\0';
	};

	_note(const unsigned &newSize, const TCHAR* const newStr) : sizeOfStr(newSize)
	{
		str = new TCHAR[sizeOfStr + 1]();
		unsigned i(0);
		for (; i < sizeOfStr; ++i)
		{
			str[i] = newStr[i];
		}
		str[i] = '\0';
	};

	_note& operator=(const _note& newObject) 
	{
		this->~_note();
		sizeOfStr = newObject.sizeOfStr;
		str = new TCHAR[sizeOfStr + 1]();
		unsigned i(0);
		for (; i < sizeOfStr; ++i)
		{
			str[i] = newObject.str[i];
		}
		str[i] = '\0';
		return *this;
	};

	~_note()
	{
		if (str)
			delete[] str;
		str = nullptr;
		sizeOfStr = 0;
	};

}NOTE;

//the strust of coodinate
typedef struct _coordinate
{
	

	unsigned coordinate_id;
	E3_VECTOR t;
	E3_VECTOR r;
	double zoom;
	NOTE note;

	_coordinate() :coordinate_id(0), zoom(1.0){};

	_coordinate(const _coordinate & newObject)
		: coordinate_id(newObject.coordinate_id)
		, t(newObject.t)
		, r(newObject.r)
		, zoom(newObject.zoom)
		, note(newObject.note){};

	_coordinate& operator=(const _coordinate & newObject)
	{
		coordinate_id = newObject.coordinate_id;
		t = newObject.t;
		r = newObject.r;
		zoom = newObject.zoom;
		note = newObject.note;
		return *this;
	};


	_coordinate
		(const E3_VECTOR &newT
		, const E3_VECTOR &newR
		, const unsigned &newId
		, const double &newZoom
		, const NOTE &newNote) : t(newT), r(newR), coordinate_id(newId), zoom(newZoom), note(newNote)
	{};

	void Reset(E3_VECTOR newT, E3_VECTOR newR, double newZoom, const NOTE& newNote)
	{
		t = newT;
		r = newR;
		zoom = newZoom;
		note = newNote;
	};

	
}COORDINATE;