#pragma once
#include "CoordinateOperator.h"
#include "PalletOperatorDefine.h"


class CPalletOperator
{
public:
	CPalletOperator(CCoordinateOperator *);
	virtual ~CPalletOperator();

	/*
	@brief: This is a func to create a pallet.
	@author: JoMar
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: palletId - the id of pallet
	@param[in]: coordinateId - the id of coordinate witch the pallet base on.
	@param[in]: xLenght - the lenght of x axis
	@param[in]: yLenght - the lenght of y axis
	@param[in]: zoneNum1 - the zone number of p1 to p2
	@param[in]: zoneNum2 - the zone number of p1 to p3
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned CreatePallet(unsigned &palletId, const unsigned &coordinateId, const double &xLenght, const double &yLenght, unsigned zoneNum1, unsigned zoneNum2);

	/*
	@brief: This is a func to create a pallet and coordinate.
	@author: JoMar
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: palletId - the id of pallet
	@param[in]: p1 - the position of point 1
	@param[in]: p2 - the position of point 2
	@param[in]: p3 - the position of point 3
	@param[in]: zoneNum1 - the zone number of p1 to p2 
	@param[in]: zoneNum2 - the zone number of p1 to p3
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned CreatePallet(unsigned &palletId, const DOBOT_POSITION& p1, const DOBOT_POSITION &p2, const DOBOT_POSITION p3, const unsigned &zoneNum1, const unsigned &zoneNum2);

	/*
	@brief: This is a func to get the position of a cell on the pallet.
	@author: JoMar
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: palletId - the id of pallet
	@param[in]: zoneIndex1 - X index
	@param[in]: zoneIndex2 - Y index
	@param[out]: position
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned GetPalletCell(const unsigned &palletId, const unsigned &zoneIndex1, const unsigned &zoneIndex2, DOBOT_POSITION &position);

	/*
	@brief: This is a func to get the pallet in vector.
	@author: JoMar
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: palletId - the id of pallet
	@param[out]: pallet
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned GetPallet(const unsigned &palletId, PALLET &pallet);

	/*
	@brief: This is a func to get the pallet in vector.
	@author: JoMar
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: index - the index of pallet in vector
	@param[out]: pallet
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned GetPalletByIndex(const unsigned &index, PALLET &pallet);

	/*
	@brief: This is a func to ergodic all pallet in vector.
	@author: JoMar
	@param[out]: pallet
	@param[in]: reStart
	@return: if it is success, return 0; else, return a error code.
	*/
	unsigned ErgodicAllPallet(PALLET &pallet, bool reStart = false);


private:
	CCoordinateOperator *m_pCoordinateOperator;

	std::vector<PALLET> m_pallets;
	std::vector<PALLET>::iterator m_iter;

	/*
	@brief: This is a func to get a new ID base on the vector.
	@author: JoMar
	@return: A new ID base on the pallet vector.
	*/
	inline unsigned GetNewIdOfPallet();
};

