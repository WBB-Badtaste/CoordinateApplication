#include "stdafx.h"
#include "DobotStatusHandle.h"


bool DobotSuccess(const DOBOT_STATUS& dobotStatus)
{
	if ((dobotStatus & DOBOT_CHECK_RESULT_MASK) == DOBOT_SUCCESS_MASK)
		return true;
	else 
		return false;
}

bool DobotError(const DOBOT_STATUS& dobotStatus)
{
	if ((dobotStatus & DOBOT_CHECK_RESULT_MASK) == DOBOT_ERROR_MASK)
		return true;
	else 
		return false;
}

bool DobotWarn(const DOBOT_STATUS& dobotStatus)
{
	if ((dobotStatus & DOBOT_CHECK_RESULT_MASK) == DOBOT_WARN_MASK)
		return true;
	else 
		return false;
}


const TCHAR* DobotGetStatusString(const DOBOT_STATUS& dobotStatus)
{
	switch (dobotStatus)
	{
	default:
		return _T("DOBOT_ERR_SYSTEM_STATUS_CODE");
		
	/*
	@brief: define the coordinate subsystem error status
	@author: JoMar
	@date: 2016-06-12
	*/

	case DOBOT_ERR_COORD_SET_MULTI_BASE:              return _T("DOBOT_ERR_COORD_SET_MULTI_BASE");
	case DOBOT_ERR_COORD_DEL_ID_NONEXISTENT:		  return _T("DOBOT_ERR_COORD_DEL_ID_NONEXISTENT");
	case DOBOT_ERR_COORD_CONVERT_ORIGIN_NONEXISTENT:  return _T("DOBOT_ERR_COORD_CONVERT_ORIGIN_NONEXISTENT");
	case DOBOT_ERR_COORD_CONVERT_TARGET_NONEXISTENT:  return _T("DOBOT_ERR_COORD_CONVERT_TARGET_NONEXISTENT");
	case DOBOT_ERR_COORD_ERGODIC_EMPTY:				  return _T("DOBOT_ERR_COORD_ERGODIC_EMPTY");
	case DOBOT_ERR_COORD_GET_ID_NOTE:				  return _T("DOBOT_ERR_COORD_GET_ID_NOTE");
	case DOBOT_ERR_COORD_GET_ID:					  return _T("DOBOT_ERR_COORD_GET_ID");

	/*
	@brief: define the coordinate subsystem success status
	@author: JoMar
	@date: 2016-06-12
	*/

	case DOBOT_SUC_COORD_CREATE:        return _T("DOBOT_SUC_COORD_CREATE");
	case DOBOT_SUC_COORD_MODIFY:		return _T("DOBOT_SUC_COORD_MODIFY");
	case DOBOT_SUC_COORD_DEL:			return _T("DOBOT_SUC_COORD_DEL");
	case DOBOT_SUC_COORD_CONVERT:		return _T("DOBOT_SUC_COORD_CONVERT");
	case DOBOT_SUC_COORD_ERGODIC:		return _T("DOBOT_SUC_COORD_ERGODIC");
	case DOBOT_SUC_COORD_GET_ID_NOTE:	return _T("DOBOT_SUC_COORD_GET_ID_NOTE");
	case DOBOT_SUC_COORD_GET_ID:		return _T("DOBOT_SUC_COORD_GET_ID");


	/*
	@brief: define the coordinate subsystem warn status
	@author: JoMar
	@date: 2016-06-12
	*/

	case DOBOT_WAR_COORD_CONVERT_SAME: 	return _T("DOBOT_WAR_COORD_CONVERT_SAME");
	case DOBOT_WAR_COORD_ERGODIC_END:	return _T("DOBOT_WAR_COORD_ERGODIC_END");


	/*
	@brief: define the pallet subsystem error status
	@author: JoMar
	@date: 2016-06-12
	*/

	case DOBOT_ERR_PALLET_SET_NONLENGHT:                       return _T("DOBOT_ERR_PALLET_SET_NONLENGHT");
	case DOBOT_ERR_PALLET_SET_ZONE_LESS:					   return _T("DOBOT_ERR_PALLET_SET_ZONE_LESS");
	case DOBOT_ERR_PALLET_SET_CREATE_COORD:					   return _T("DOBOT_ERR_PALLET_SET_CREATE_COORD");
	case DOBOT_ERR_PALLET_SET_ORIGIN_NONEXISTENT:			   return _T("DOBOT_ERR_PALLET_SET_ORIGIN_NONEXISTENT");
	case DOBOT_ERR_PALLET_DEL_NONEXISTENT:					   return _T("DOBOT_ERR_PALLET_DEL_NONEXISTENT");
	case DOBOT_ERR_PALLET_GETCELL_PALLET_NONEXISTENT:		   return _T("DOBOT_ERR_PALLET_GETCELL_PALLET_NONEXISTENT");
	case DOBOT_ERR_PALLET_GETCELL_ZONE_OVER:				   return _T("DOBOT_ERR_PALLET_GETCELL_ZONE_OVER");
	case DOBOT_ERR_PALLET_GETCELL_CONVERT:					   return _T("DOBOT_ERR_PALLET_GETCELL_CONVERT");
	case DOBOT_ERR_PALLET_GETPALLET_NONEXISTENT:			   return _T("DOBOT_ERR_PALLET_GETPALLET_NONEXISTENT");
	case DOBOT_ERR_PALLET_GETPALLETID_NONEXISTENT:			   return _T("DOBOT_ERR_PALLET_GETPALLETID_NONEXISTENT");
	case DOBOT_ERR_PALLET_GETPALLETID_BYINDEX_NONEXISTENT:	   return _T("DOBOT_ERR_PALLET_GETPALLETID_BYINDEX_NONEXISTENT");
	case DOBOT_ERR_PALLET_ERGODIC_EMPTY:					   return _T("DOBOT_ERR_PALLET_ERGODIC_EMPTY");



	/*
	@brief: define the pallet subsystem success status
	@author: JoMar
	@date: 2016-06-12
	*/

	case DOBOT_SUC_PALLET_MODIFY:             return _T("DOBOT_SUC_PALLET_MODIFY");
	case DOBOT_SUC_PALLET_CREATE:			  return _T("DOBOT_SUC_PALLET_CREATE");
	case DOBOT_SUC_PALLET_DEL:				  return _T("DOBOT_SUC_PALLET_DEL");
	case DOBOT_SUC_PALLET_GETCELL:			  return _T("DOBOT_SUC_PALLET_GETCELL");
	case DOBOT_SUC_PALLET_GETPALLET:		  return _T("DOBOT_SUC_PALLET_GETPALLET");
	case DOBOT_SUC_PALLET_GETPALLETID:		  return _T("DOBOT_SUC_PALLET_GETPALLETID");
	case DOBOT_SUC_PALLET_GETPALLET_BYINDEX:  return _T("DOBOT_SUC_PALLET_GETPALLET_BYINDEX");
	case DOBOT_SUC_PALLET_ERGODIC:			  return _T("DOBOT_SUC_PALLET_ERGODIC");

		 /*
		 @brief: define the pallet subsystem warn status
		 @author: JoMar
		 @date: 2016-06-12
		 */

	case DOBOT_WAR_PALLET_ERGODIC_END :		  return _T("DOBOT_WAR_PALLET_ERGODIC_END");

	}
}