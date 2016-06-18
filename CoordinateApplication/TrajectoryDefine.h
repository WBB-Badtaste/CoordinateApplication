#pragma once

#include "E2_Point.h"

typedef struct _traj_arc
{
	double R;
	double rotateRadian;
	E2_POINT center;
	_traj_arc() : R(0.0), rotateRadian(0){};
	_traj_arc(const _traj_arc& object) : R(object.R), rotateRadian(0), center()
	{
		R = object.R;
		rotateRadian = object.rotateRadian;
		center = object.center;
	}
	~_traj_arc();
	_traj_arc& operator=(const _traj_arc& object)
	{
		R = object.R;
		rotateRadian = object.rotateRadian;
		center = object.center;
	}

}TRAJ_ARC;