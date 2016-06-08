#include "stdafx.h"
#include "PalletOperator.h"


CPalletOperator::CPalletOperator(CCoordinateOperator *pCoordinateOperator)
{
	m_pCoordinateOperator = pCoordinateOperator;
	m_iter = m_pallets.begin();
}


CPalletOperator::~CPalletOperator()
{
}

unsigned CPalletOperator::SetPallet(unsigned &palletId, const unsigned &coordinateId, const double &xLenght, const double &yLenght, unsigned zoneNum1, unsigned zoneNum2)
{
	if (xLenght <= 0 || yLenght <= 0)
		return 1;//Have to be modify

	if (zoneNum1 < 2 || zoneNum2 < 2)
		return 1;//Have to be modify
	
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (iter->id_pallet == palletId)
		{
			iter->Reset(coordinateId, xLenght, yLenght, zoneNum1, zoneNum2);
			return 0;
		}
	}

	palletId = GetNewIdOfPallet();

	//Create a new martix base on the auto id.
	PALLET pallet(palletId, coordinateId, xLenght, yLenght, zoneNum1, zoneNum2);
	m_pallets.push_back(pallet);

	return 0;
}

unsigned CPalletOperator::SetPallet(unsigned &palletId, const DOBOT_POSITION& p1, const DOBOT_POSITION &p2, const DOBOT_POSITION p3, const unsigned &zoneNum1, const unsigned &zoneNum2)
{
	if (zoneNum1 < 2 || zoneNum2 < 2)
	{
		return 1;//Have to modify
	}

	double xLenght((p2.position - p1.position).Module());
	double yLenght((p3.position - p1.position).Module());

	if (xLenght <= 0 || yLenght <=0)
	{
		return 1;//Have to modify
	}

	unsigned coordinateId(0);

	TCHAR *str(_T("ÍÐÅÌ×ø±êÏµ"));
	if (m_pCoordinateOperator->SetCoordinate(coordinateId, p1, p2, p3, str, _tcslen(str)))
		return 1;//Have to be modify

	SetPallet(palletId, coordinateId, xLenght, yLenght, zoneNum1, zoneNum2);

	return 0;
}

unsigned CPalletOperator::SetPallet(unsigned &palletId, const unsigned& coordinteIdofPallet, const unsigned& originPalletId)
{
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (iter->id_pallet == originPalletId)
			break;
	}

	if (iter == m_pallets.end())
		return 1;//Have to be modify.

	const E3_VECTOR &point(iter->user_points[iter->zoneNumX - 1][iter->zoneNumY - 1].position);

	SetPallet(palletId, coordinteIdofPallet, point.x, point.y, iter->zoneNumX, iter->zoneNumY);
	return 0;
}

unsigned CPalletOperator::GetPalletCell(const unsigned &palletId, const unsigned &zoneNum1, const unsigned &zoneNum2, DOBOT_POSITION &position)
{
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (palletId == iter->id_pallet)
			break;
	}

	if (iter == m_pallets.begin() )
		return 1;//Have to be modified.

	DOBOT_POSITION buffer;
	buffer = iter->user_points[zoneNum1][zoneNum2];

	m_pCoordinateOperator->ConvertCoordinate(buffer, position);

	return 0;
}

unsigned CPalletOperator::GetPallet(const unsigned &palletId, PALLET &pallet)
{
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (palletId == iter->id_pallet)
		{
			pallet = *iter;
			return 0;
		}
	}
	return 1;//Have to be modify
}

unsigned CPalletOperator::GetPalletId(const unsigned &index, unsigned& palletId)
{
	unsigned i(0);
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter, ++i)
	{
		if (i == index)
		{
			palletId = iter->id_pallet;
			return 0;
		}
	}
	return 1;//Have to be modify
}

unsigned CPalletOperator::GetPalletByIndex(const unsigned &index, PALLET &pallet)
{
	std::vector<PALLET>::iterator iter;
	unsigned i(0);
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter, ++i)
	{
		if (i == index)
		{
			pallet = *iter;
			return 0;
		}
	}
	return 1;//Have to be modify
}


unsigned CPalletOperator::ErgodicAllPallet(PALLET &pallet, bool reStart /* = false */)
{
	unsigned palletAmount(m_pallets.size());
	if (palletAmount < 1)
		return 1;//have to be modify

	if (reStart)
		m_iter = m_pallets.begin();
	else
		++m_iter;

	if (m_iter == m_pallets.end())
		return 1;//have to be modify

	pallet = *m_iter;

	return 0;
}

unsigned CPalletOperator::GetNewIdOfPallet()
{
	if (m_pallets.size() < 1)
		return 0;//the vector of transition martix is empty, return 0.
	else
		return (m_pallets.end() - 1)->id_pallet + 1;//the vector of transition martix isn't empty, return (id + 1) of last element.

}

