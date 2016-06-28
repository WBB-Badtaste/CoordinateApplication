#pragma once

#include "Geometric.h"

typedef enum _trajectory_type
{
	ARC,
	LINE,
	SPLINE
}TRAJECTORY_TYPE;

typedef class Trajectory
{
public:
	

	Trajectory();
	virtual ~Trajectory();
}TRAJ;

typedef class _trajectory_arc : public Trajectory
{
	double R;//radian of arc
	double rotateRadian;
	E2_POINT center;
}TRAJ_ARC;