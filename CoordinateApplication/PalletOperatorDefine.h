#pragma once

typedef struct _pallet
{
	_pallet() :id_pallet(0), zoneNumX(0), zoneNumY(0), user_points(nullptr){};
	_pallet(const _pallet& newPallet)
		: id_pallet(newPallet.id_pallet)
		, zoneNumX(newPallet.zoneNumX)
		, zoneNumY(newPallet.zoneNumY)
		, user_points(nullptr)
	{
		AllocMemory();
		CopyPoints(newPallet.user_points);
	}

	_pallet(const unsigned &newPalletId, const unsigned &newCoordinateId, const double &xLenght, const double &yLenght, const unsigned &newZoneNumX, const unsigned &newZoneNumY)
	: id_pallet(newPalletId)
	, zoneNumX(newZoneNumX)
	, zoneNumY(newZoneNumY)
	, user_points(nullptr)
	{
		AllocMemory();
		CreatePoints(newCoordinateId, xLenght, yLenght);
	};

	virtual ~_pallet()
	{
		FreeMemory();
		user_points = nullptr;
		zoneNumX = 0;
		zoneNumY = 0;
	};

	_pallet& operator=(const _pallet& newPallet)
	{
		FreeMemory();

		id_pallet = newPallet.id_pallet;
		zoneNumX = newPallet.zoneNumX;
		zoneNumY = newPallet.zoneNumY;

		AllocMemory();
		
		CopyPoints(newPallet.user_points);
		
		return *this;
	}

	void Reset(const unsigned& newCoordinateId, const double &xLenght, const double &yLenght, const unsigned &newZoneNumX, const unsigned &newZoneNumY)
	{
		FreeMemory();
		zoneNumX = newZoneNumX;
		zoneNumY = newZoneNumY;

		AllocMemory();

		CreatePoints(newCoordinateId, xLenght, yLenght);
	};

	unsigned id_pallet;
	unsigned zoneNumX;
	unsigned zoneNumY;
	DOBOT_POSITION **user_points;

private:
	inline void FreeMemory()
	{
		if (user_points)
		{
			for (unsigned index = 0; index < zoneNumX; ++index)
			{
				if (user_points[index])
					delete[] user_points[index];
			}
			delete[] user_points;
		}
	};

	inline void AllocMemory()
	{
		user_points = new DOBOT_POSITION*[zoneNumX]();
		for (unsigned index = 0; index < zoneNumX; ++index)
		{
			user_points[index] = new DOBOT_POSITION[zoneNumY]();
		}
	};

	inline void CopyPoints(DOBOT_POSITION** const points)
	{
		for (unsigned i = 0; i < zoneNumX; ++i)
		for (unsigned j = 0; j < zoneNumY; ++j)
		{
			user_points[i][j].coordinate_id = points[i][j].coordinate_id;
			user_points[i][j].position = points[i][j].position;
		}
	};

	inline void CreatePoints(const unsigned& newCoordinateId, const double &xLenght, const double &yLenght)
	{
		for (unsigned i = 0; i < zoneNumX; ++i)
		for (unsigned j = 0; j < zoneNumY; ++j)
		{
			user_points[i][j].coordinate_id = newCoordinateId;
			user_points[i][j].position.x = xLenght / (zoneNumX - 1) * i;
			user_points[i][j].position.y = yLenght / (zoneNumY - 1) * j;
			user_points[i][j].position.z = 0;
		}
	}


}PALLET;