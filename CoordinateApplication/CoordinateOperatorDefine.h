#pragma once

#include "Geometric.h"

/*
@brief: There is a only one world coordinate, it has a special ID witch is 0.
@author: JoMar
@date: 2016-06-08
*/
const unsigned WORLD_COORDINATE_ID(0);

/*
@brief: There is a default zoom ratio of coordinate.
@author: JoMar
@date: 2016-06-08
*/
const double COORDINATE_DEFAULT_ZOOM(1.0);

/*
@brief: There is a struct of Dobot position
@note: coordinate_id is the id of coordinate witch the position made sense in
@author: JoMar
@date: 2016-06-08
*/
typedef struct _dobot_position
{
	unsigned coordinate_id;
	E3_POINT position;

	_dobot_position() :coordinate_id(0){};

	_dobot_position(const _dobot_position& newObject) :coordinate_id(newObject.coordinate_id), position(newObject.position){};

	_dobot_position(const E3_POINT &point) :coordinate_id(0), position(point){};

	_dobot_position(const unsigned &id) :coordinate_id(id){};

	_dobot_position(const unsigned &id, const E3_POINT& point) :coordinate_id(id), position(point){};

	_dobot_position& operator=(const _dobot_position& newObject)
	{
		coordinate_id = newObject.coordinate_id;
		position = newObject.position;
		return *this;
	};

	
}
/*
@brief: There is a struct of Dobot position
@note: coordinate_id is the id of coordinate witch the position made sense in
@author: JoMar
@date: 2016-06-08
*/
DOBOT_POSITION;

/*
@brief: There is a struct of note of coordinate
@author: JoMar
@date: 2016-06-08
*/
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

}
/*
@brief: There is a struct of note of coordinate
@author: JoMar
@date: 2016-06-08
*/
NOTE;


/*
@brief: There is a matrix witch used for convert position between two coordinate
@author: JoMar
@date: 2016-06-20
*/
typedef Eigen::Matrix<double, 4, 4> COORDINATE_MATRIX;

/*
@brief: There is a vector witch used for convert position between two coordinate
@author: JoMar
@date: 2016-06-22
*/
typedef Eigen::Matrix<double, 1, 4> CONVERT_VECTOR;


/*
@brief: There is a struct of coordinate
@note: Transition martix is base on the world coordinate.
@author: JoMar
@date: 2016-06-22
*/
typedef struct _coordinate
{
	
	unsigned coordinate_id;
	NOTE note;
	COORDINATE_MATRIX forwordMartix;
	COORDINATE_MATRIX inverseMartix;

	_coordinate() :coordinate_id(0){};

	
	_coordinate(const _coordinate & object)
		: coordinate_id(object.coordinate_id)
		, note(object.note)
		, forwordMartix(object.forwordMartix)
		, inverseMartix(object.inverseMartix){};
		

	_coordinate& operator=(const _coordinate & object)
	{
		coordinate_id = object.coordinate_id;
		note = object.note;
		forwordMartix = object.forwordMartix;
		inverseMartix = object.inverseMartix;
		return *this;
	};


	_coordinate
		(
		  const unsigned &newId
		, const NOTE &newNote
		, const COORDINATE_MATRIX &newForwordMartix
		, const COORDINATE_MATRIX &newInverseMartix) : coordinate_id(newId), note(newNote), inverseMartix(newInverseMartix), forwordMartix(newForwordMartix)
	{};

	/*
	@brief: it a function to reset the paramers of coordinate
	@param[in]: newForwordMartix - translation martix used for forword converting
	@param[in]: newInverseMartix - translation martix used for inverse converting
	@param[in]: newZoom - zoom ratio
	@param[in]: newNote - note
	@author: JoMar
	@date: 2016-06-12
	*/
	void Reset(const NOTE& newNote, const COORDINATE_MATRIX &newForwordMartix, const COORDINATE_MATRIX &newInverseMartix)
	{
		note = newNote;
		forwordMartix = newForwordMartix;
		inverseMartix = newInverseMartix;
	};

	
}
/*
@brief: There is a struct of coordinate
@note: Transition martix is base on the world coordinate.
@author: JoMar
@date: 2016-06-22
*/
COORDINATE;