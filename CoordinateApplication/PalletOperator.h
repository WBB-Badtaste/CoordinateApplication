#pragma once
#include "CoordinateOperator.h"
#include "PalletOperatorDefine.h"

/*
@brief: This is a class witch operating the pallet.
@author: JoMar
@date: 2016-06-08
*/
class CPalletOperator
{
public:
	CPalletOperator(CCoordinateOperator *);
	virtual ~CPalletOperator();

	/*
	@brief: This is a func to modify the pallet. If the coordinate isn't existence, it will create a new one.
	@param[in|out]: palletId - the id of pallet.Func will renturn a new Id, when the id isn't existence in vector
	@param[in]: coordinateId - the id of coordinate witch the pallet base on.
	@param[in]: xLenght - the lenght of x axis
	@param[in]: yLenght - the lenght of y axis
	@param[in]: zoneNum1 - the zone number of p1 to p2
	@param[in]: zoneNum2 - the zone number of p1 to p3
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-08
	*/
	unsigned SetPallet(unsigned &palletId, const unsigned &coordinateId, const double &xLenght, const double &yLenght, unsigned zoneNum1, unsigned zoneNum2);

	/*
	@brief: This is a func to modify the pallet by using 3 special point. If the coordinate isn't existence, it will create a new one.
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in|out]: palletId - the id of pallet.Func will renturn a new Id, when the id isn't existence in vector
	@param[in]: p1 - the position of point 1
	@param[in]: p2 - the position of point 2
	@param[in]: p3 - the position of point 3
	@param[in]: zoneNum1 - the zone number of p1 to p2 
	@param[in]: zoneNum2 - the zone number of p1 to p3
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-08
	*/
	unsigned SetPallet(unsigned &palletId, const DOBOT_POSITION& p1, const DOBOT_POSITION &p2, const DOBOT_POSITION p3, const unsigned &zoneNum1, const unsigned &zoneNum2);

	/*
	@brief: This is a func to modify the pallet by copying another pallet. If the coordinate isn't existence, it will create a new one.
	@param[in|out]: palletId - the id of pallet. Func will renturn a new Id, when the id isn't existence in vector
	@param[in]: coordinteIdofPallet - the coordinate id of target pallet
	@param[in]: originPalletId - the id of origin pallet
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-08
	*/
	unsigned SetPallet(unsigned &palletId, const unsigned& coordinteIdofPallet, const unsigned& originPalletId);

	/*
	@brief: This is a func to delete the pallet
	@param[in]: id - pallet id.
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-12
	*/
	unsigned DeletePallet(const unsigned& id);

	/*
	@brief: This is a func to get the position of a cell on the pallet.
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: palletId - the id of pallet
	@param[in]: zoneIndex1 - X index
	@param[in]: zoneIndex2 - Y index
	@param[out]: position
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-08
	*/
	unsigned GetPalletCell(const unsigned &palletId, const unsigned &zoneIndex1, const unsigned &zoneIndex2, DOBOT_POSITION &position);

	/*
	@brief: This is a func to get the pallet in vector.
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: palletId - the id of pallet
	@param[out]: pallet
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-08
	*/
	unsigned GetPallet(const unsigned &palletId, PALLET &pallet);

	/*
	@brief: This is a func to get the pallet in vector.
	@author: JoMar
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: index - the index of pallet in vector
	@param[out]: pallet
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-08
	*/
	unsigned GetPalletByIndex(const unsigned &index, PALLET &pallet);


	/*
	@brief: This is a func to get the pallet id by using index of vector.
	@note: p1 is the origin of pallet; p2 is on X axis; p3 is on Y axis
	@param[in]: index - the index of pallet in vector
	@param[out]: palletId - the id of pallet
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-08
	*/
	unsigned GetPalletId(const unsigned &index, unsigned& palletId);

	/*
	@brief: This is a func to ergodic all pallet in vector.
	@param[out]: pallet
	@param[in]: reStart
	@return: if it is success, return 0; else, return a error code.
	@author: JoMar
	@date: 2016-06-08
	*/
	unsigned ErgodicAllPallet(PALLET &pallet, bool reStart = false);


private:
	/*
	@brief: This is a point of coordinate operator.
	@author: JoMar
	@date: 2016-06-08
	*/
	CCoordinateOperator *m_pCoordinateOperator;

	/*
	@brief: This is a vector storing pallets.
	@author: JoMar
	@date: 2016-06-08
	*/
	std::vector<PALLET> m_pallets;

	/*
	@brief: a point witch pointing the vector used in ergodicing
	@author: JoMar
	@date: 2016-06-08
	*/
	std::vector<PALLET>::iterator m_iter;

	/*
	@brief: This is a func to get a new ID base on the vector.
	@return: A new ID base on the pallet vector.
	@author: JoMar
	@date: 2016-06-08
	*/
	inline unsigned GetNewIdOfPallet();

	/*
	@brief: This is a callback function to ascending sort the vector by id
	@author: JoMar
	@date: 2016-06-12
	*/
	static bool AscendingSortById(const PALLET& pallet1, const PALLET& pallet2);
};

