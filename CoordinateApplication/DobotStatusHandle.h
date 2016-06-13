#pragma once

#include "DobotStatusDefine.h"

/*
@brief: This is a function to check the dobot status code
@param[in]: dobotStatus - status code
@return: if success, return true;else, return false
@author: JoMar
@date: 2016-06-12
*/
bool DobotSuccess(const DOBOT_STATUS& dobotStatus);


/*
@brief: This is a function to check the dobot status code
@param[in]: dobotStatus - status code
@return: if error, return true;else, return false
@author: JoMar
@date: 2016-06-12
*/
bool DobotError(const DOBOT_STATUS& dobotStatus);

/*
@brief: This is a function to check the dobot status code
@param[in]: dobotStatus - status code
@return: if warn, return true;else, return false
@author: JoMar
@date: 2016-06-12
*/
bool DobotWarn(const DOBOT_STATUS& dobotStatus);

/*
@brief: This is a function to translate status code to string
@param[in]: dobotStatus - status code
@return: if error, return true;else, return false
@author: JoMar
@date: 2016-06-13
*/
const TCHAR* DobotGetStatusString(const DOBOT_STATUS& dobotStatus);