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

DOBOT_STATUS CPalletOperator::SetPallet(unsigned &palletId, const unsigned &coordinateId, const double &xLenght, const double &yLenght, unsigned zoneNum1, unsigned zoneNum2)
{
	if (xLenght <= 0 || yLenght <= 0)
		return DOBOT_ERR_PALLET_SET_NONLENGHT;

	if (zoneNum1 < 2 || zoneNum2 < 2)
		return DOBOT_ERR_PALLET_SET_ZONE_LESS;
	
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (iter->id_pallet == palletId)
		{
			iter->Reset(coordinateId, xLenght, yLenght, zoneNum1, zoneNum2);
			return DOBOT_SUC_PALLET_MODIFY;
		}
	}

	palletId = GetNewIdOfPallet();

	//Create a new martix base on the auto id.
	PALLET pallet(palletId, coordinateId, xLenght, yLenght, zoneNum1, zoneNum2);
	m_pallets.push_back(pallet);

	//sort the vector
	std::sort(m_pallets.begin(), m_pallets.end(), AscendingSortById);

	return DOBOT_SUC_PALLET_CREATE;
}

DOBOT_STATUS CPalletOperator::SetPallet(unsigned &palletId, const DOBOT_POSITION& p1, const DOBOT_POSITION &p2, const DOBOT_POSITION p3, const unsigned &zoneNum1, const unsigned &zoneNum2)
{
	if (zoneNum1 < 2 || zoneNum2 < 2)
	{
		return DOBOT_ERR_PALLET_SET_ZONE_LESS;
	}

	double xLenght((p2.position - p1.position).Module());
	double yLenght((p3.position - p1.position).Module());

	if (xLenght <= 0 || yLenght <=0)
	{
		return DOBOT_ERR_PALLET_SET_NONLENGHT;//Have to modify
	}

	unsigned coordinateId(0);

	DOBOT_STATUS dobotStatus(DOBOT_OK);
	TCHAR *str(_T("ÍÐÅÌ×ø±êÏµ"));

	if (DobotError(m_pCoordinateOperator->SetCoordinate(coordinateId, p1, p2, p3, str, _tcslen(str))))
		return DOBOT_ERR_PALLET_SET_CREATE_COORD;

	return SetPallet(palletId, coordinateId, xLenght, yLenght, zoneNum1, zoneNum2);
}

DOBOT_STATUS CPalletOperator::SetPallet(unsigned &palletId, const unsigned& coordinteIdofPallet, const unsigned& originPalletId)
{
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (iter->id_pallet == originPalletId)
			break;
	}

	if (iter == m_pallets.end())
		return DOBOT_ERR_PALLET_SET_ORIGIN_NONEXISTENT;

	const E3_VECTOR &point(iter->user_points[iter->zoneNumX - 1][iter->zoneNumY - 1].position);

	return SetPallet(palletId, coordinteIdofPallet, point.x, point.y, iter->zoneNumX, iter->zoneNumY);
}

DOBOT_STATUS CPalletOperator::DeletePallet(const unsigned& id)
{
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (id == iter->id_pallet)
		{
			m_pallets.erase(iter);
			m_iter = m_pallets.begin();

			std::sort(m_pallets.begin(), m_pallets.end(), AscendingSortById);

			return DOBOT_SUC_PALLET_DEL;
		}
	}
	return DOBOT_ERR_PALLET_DEL_NONEXISTENT;
}

DOBOT_STATUS CPalletOperator::GetPalletCell(const unsigned &palletId, const unsigned &zoneNum1, const unsigned &zoneNum2, DOBOT_POSITION &position)
{
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (palletId == iter->id_pallet)
			break;
	}

	if (iter == m_pallets.end())
		return DOBOT_ERR_PALLET_GETCELL_PALLET_NONEXISTENT;

	if (zoneNum1 >= iter->zoneNumX || zoneNum2 >= iter->zoneNumY)
		return DOBOT_ERR_PALLET_GETCELL_ZONE_OVER;

	if (DobotError(m_pCoordinateOperator->ConvertPosition(iter->user_points[zoneNum1][zoneNum2], position)))
		return DOBOT_ERR_PALLET_GETCELL_CONVERT;

	return DOBOT_SUC_PALLET_GETCELL;
}

DOBOT_STATUS CPalletOperator::GetPallet(const unsigned &palletId, PALLET &pallet)
{
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter)
	{
		if (palletId == iter->id_pallet)
		{
			pallet = *iter;
			return DOBOT_SUC_PALLET_GETPALLET;
		}
	}
	return DOBOT_ERR_PALLET_GETPALLET_NONEXISTENT;
}

DOBOT_STATUS CPalletOperator::GetPalletId(const unsigned &index, unsigned& palletId)
{
	unsigned i(0);
	std::vector<PALLET>::iterator iter;
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter, ++i)
	{
		if (i == index)
		{
			palletId = iter->id_pallet;
			return DOBOT_SUC_PALLET_GETPALLETID;
		}
	}
	return DOBOT_ERR_PALLET_GETPALLETID_NONEXISTENT;
}

DOBOT_STATUS CPalletOperator::GetPalletByIndex(const unsigned &index, PALLET &pallet)
{
	std::vector<PALLET>::iterator iter;
	unsigned i(0);
	for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter,++i)
	{
		if (i == index)
		{
			pallet = *iter;
			return DOBOT_SUC_PALLET_GETPALLET_BYINDEX;
		}
	}
	return DOBOT_ERR_PALLET_GETPALLETID_BYINDEX_NONEXISTENT;
}

DOBOT_STATUS CPalletOperator::ErgodicAllPallet(PALLET &pallet, bool reStart /* = false */)
{
	unsigned palletAmount(m_pallets.size());
	if (palletAmount < 1)
		return DOBOT_ERR_PALLET_ERGODIC_EMPTY;

	if (reStart)
		m_iter = m_pallets.begin();
	else
		++m_iter;

	if (m_iter == m_pallets.end())
		return DOBOT_WAR_PALLET_ERGODIC_END;

	pallet = *m_iter;

	return DOBOT_SUC_PALLET_ERGODIC;
}

unsigned CPalletOperator::GetNewIdOfPallet()
{
	if (m_pallets.size() < 1)
		return 0;//the vector of transition martix is empty, return 0.
	else
	{
		unsigned id(0);
		std::vector<PALLET>::iterator iter;
		for (iter = m_pallets.begin(); iter != m_pallets.end(); ++iter, ++id)
		{
			if (id != iter->id_pallet)
				break;
		}
		return id;
	}

}

bool CPalletOperator::AscendingSortById(const PALLET& pallet1, const PALLET& pallet2)
{
	return pallet1.id_pallet < pallet2.id_pallet;
}
