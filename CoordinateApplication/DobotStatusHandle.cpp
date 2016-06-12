#include "stdafx.h"
#include "DobotStatusHandle.h"


bool DobotSuccess(const DOBOT_STATUS& dobotStatus)
{
	if (dobotStatus & (0x0001 << DOBOT_RESULT_SHIFT))
		return true;
	else false;
}

bool DobotError(const DOBOT_STATUS& dobotStatus)
{
	if (dobotStatus & (0x0001 << DOBOT_RESULT_SHIFT))
		return false;
	else true;
}