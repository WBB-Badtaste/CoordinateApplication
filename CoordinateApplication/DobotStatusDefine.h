#pragma once

typedef unsigned DOBOT_STATUS;

const unsigned UINT_BIT = 32;

/*
@brief: define the result mask
@author: JoMar
@note: up to 3 bits
@date: 2016-06-12
*/

const unsigned DOBOT_RESULT_SHIFT		= (UINT_BIT - 4);
const unsigned DOBOT_ERROR_MASK			= (0x00000000 << DOBOT_RESULT_SHIFT);
const unsigned DOBOT_SUCCESS_MASK		= (0x00000001 << DOBOT_RESULT_SHIFT);
const unsigned DOBOT_WARN_MASK			= (0x00000002 << DOBOT_RESULT_SHIFT);
const unsigned DOBOT_CHECK_RESULT_MASK	= (0xffffffff << DOBOT_RESULT_SHIFT);

//default value
const unsigned DOBOT_OK = 0;


/*
@brief: define the subsystem mask
@author: JoMar
@note: up to 5 bits
@date: 2016-06-12
*/

const unsigned DOBOT_SUBSYS_SHIFT		= (DOBOT_RESULT_SHIFT - 5);
const unsigned COORDINATE_SUBSYS_MASK	= (0x00000000 << DOBOT_SUBSYS_SHIFT);
const unsigned PALLET_SUBSYS_MASK		= (0x00000001 << DOBOT_SUBSYS_SHIFT);

/*
@brief: define the coordinate subsystem error status
@author: JoMar
@date: 2016-06-12
*/

const unsigned DOBOT_ERR_COORD_MASK							= (DOBOT_ERROR_MASK | COORDINATE_SUBSYS_MASK);
const unsigned DOBOT_ERR_COORD_SET_MULTI_BASE				= ((DOBOT_STATUS)(DOBOT_ERR_COORD_MASK + 0)); //using points witch made sense in difference coordinate to setup another coordinate
const unsigned DOBOT_ERR_COORD_DEL_ID_NONEXISTENT			= ((DOBOT_STATUS)(DOBOT_ERR_COORD_MASK + 1)); //the ID witch being gone to delete is not existent
const unsigned DOBOT_ERR_COORD_CONVERT_ORIGIN_NONEXISTENT	= ((DOBOT_STATUS)(DOBOT_ERR_COORD_MASK + 2)); //the origin coordinate used for converting is not existent
const unsigned DOBOT_ERR_COORD_CONVERT_TARGET_NONEXISTENT	= ((DOBOT_STATUS)(DOBOT_ERR_COORD_MASK + 3)); //the target coordinate used for converting is not existent
const unsigned DOBOT_ERR_COORD_ERGODIC_EMPTY				= ((DOBOT_STATUS)(DOBOT_ERR_COORD_MASK + 4)); //there is not any coordinate for ergodicing
const unsigned DOBOT_ERR_COORD_GET_ID_NOTE					= ((DOBOT_STATUS)(DOBOT_ERR_COORD_MASK + 5)); //the Index for coordinate in the vector is not existent
const unsigned DOBOT_ERR_COORD_GET_ID						= ((DOBOT_STATUS)(DOBOT_ERR_COORD_MASK + 6)); //the Index for coordinate in the vector is not existent

/*
@brief: define the coordinate subsystem success status
@author: JoMar
@date: 2016-06-12
*/

const unsigned DOBOT_SUC_COORD_MASK			= (DOBOT_SUCCESS_MASK | COORDINATE_SUBSYS_MASK);
const unsigned DOBOT_SUC_COORD_CREATE		= ((DOBOT_STATUS)(DOBOT_SUC_COORD_MASK + 0)); //success to create a coordinate
const unsigned DOBOT_SUC_COORD_MODIFY		= ((DOBOT_STATUS)(DOBOT_SUC_COORD_MASK + 1)); //success to modify a coordinate
const unsigned DOBOT_SUC_COORD_DEL			= ((DOBOT_STATUS)(DOBOT_SUC_COORD_MASK + 2)); //success to delete a coordinate
const unsigned DOBOT_SUC_COORD_CONVERT		= ((DOBOT_STATUS)(DOBOT_SUC_COORD_MASK + 3)); //success to convert two DOBOT_POSITION
const unsigned DOBOT_SUC_COORD_ERGODIC		= ((DOBOT_STATUS)(DOBOT_SUC_COORD_MASK + 4)); //success to get a coordinate dealing ergodic
const unsigned DOBOT_SUC_COORD_GET_ID_NOTE	= ((DOBOT_STATUS)(DOBOT_SUC_COORD_MASK + 5)); //success to get ID and note of a coordinate by index
const unsigned DOBOT_SUC_COORD_GET_ID		= ((DOBOT_STATUS)(DOBOT_SUC_COORD_MASK + 6)); //success to get ID of a coordinate by index


/*
@brief: define the coordinate subsystem warn status
@author: JoMar
@date: 2016-06-12
*/

const unsigned DOBOT_WAR_COORD_MASK			= (DOBOT_WARN_MASK | COORDINATE_SUBSYS_MASK);
const unsigned DOBOT_WAR_COORD_CONVERT_SAME = ((DOBOT_STATUS)(DOBOT_WAR_COORD_MASK + 0)); //the coordinates used for converting are the same
const unsigned DOBOT_WAR_COORD_ERGODIC_END	= ((DOBOT_STATUS)(DOBOT_WAR_COORD_MASK + 1)); //get a end signal of coordinate vector dealing ergodic


/*
@brief: define the pallet subsystem error status
@author: JoMar
@date: 2016-06-12
*/

const unsigned DOBOT_ERR_PALLET_MASK							= (DOBOT_ERROR_MASK | PALLET_SUBSYS_MASK);
const unsigned DOBOT_ERR_PALLET_SET_NONLENGHT					= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 0));  //x lenght or y lenght is 0
const unsigned DOBOT_ERR_PALLET_SET_ZONE_LESS					= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 1));  //x zone or y zone less than 2
const unsigned DOBOT_ERR_PALLET_SET_CREATE_COORD				= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 2));  //the coordinate can not be created for a new pallet
const unsigned DOBOT_ERR_PALLET_SET_ORIGIN_NONEXISTENT			= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 3));  //the coordinate of the points witch used for setting up pallet is not existent
const unsigned DOBOT_ERR_PALLET_DEL_NONEXISTENT					= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 4));  //the ID of pallet witch being gone to delete is not existent
const unsigned DOBOT_ERR_PALLET_GETCELL_PALLET_NONEXISTENT		= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 5));  //the pallet is not existent dealing getting cell of pallet
const unsigned DOBOT_ERR_PALLET_GETCELL_ZONE_OVER				= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 6));  //the x zone or y zone number of cell is bigger than the pallet size
const unsigned DOBOT_ERR_PALLET_GETCELL_CONVERT					= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 7));  //it can not convert the position of cell in target coordinate
const unsigned DOBOT_ERR_PALLET_GETPALLET_NONEXISTENT			= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 8));  //the ID of pallet witch being got is not existent
const unsigned DOBOT_ERR_PALLET_GETPALLETID_NONEXISTENT			= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 9));  //the index of pallet witch being got is not existent
const unsigned DOBOT_ERR_PALLET_GETPALLETID_BYINDEX_NONEXISTENT = ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 10)); //the index of pallet witch being got is not existent
const unsigned DOBOT_ERR_PALLET_ERGODIC_EMPTY					= ((DOBOT_STATUS)(DOBOT_ERR_PALLET_MASK + 11)); //there is not any pallet for ergodicing



/*
@brief: define the pallet subsystem success status
@author: JoMar
@date: 2016-06-12
*/

const unsigned DOBOT_SUC_PALLET_MASK				= (DOBOT_SUCCESS_MASK | PALLET_SUBSYS_MASK);
const unsigned DOBOT_SUC_PALLET_MODIFY				= ((DOBOT_STATUS)(DOBOT_SUC_PALLET_MASK + 0)); //success to modify the pallet
const unsigned DOBOT_SUC_PALLET_CREATE				= ((DOBOT_STATUS)(DOBOT_SUC_PALLET_MASK + 1)); //success to create the pallet
const unsigned DOBOT_SUC_PALLET_DEL					= ((DOBOT_STATUS)(DOBOT_SUC_PALLET_MASK + 2)); //success to delete the pallet
const unsigned DOBOT_SUC_PALLET_GETCELL				= ((DOBOT_STATUS)(DOBOT_SUC_PALLET_MASK + 3)); //success to get cell of the pallet
const unsigned DOBOT_SUC_PALLET_GETPALLET			= ((DOBOT_STATUS)(DOBOT_SUC_PALLET_MASK + 4)); //success to get the pallet
const unsigned DOBOT_SUC_PALLET_GETPALLETID			= ((DOBOT_STATUS)(DOBOT_SUC_PALLET_MASK + 5)); //success to get id of the pallet
const unsigned DOBOT_SUC_PALLET_GETPALLET_BYINDEX	= ((DOBOT_STATUS)(DOBOT_SUC_PALLET_MASK + 6)); //success to get the pallet by index
const unsigned DOBOT_SUC_PALLET_ERGODIC				= ((DOBOT_STATUS)(DOBOT_SUC_PALLET_MASK + 7)); //success to get a pallet dealing ergodic

/*
@brief: define the pallet subsystem warn status
@author: JoMar
@date: 2016-06-12
*/

const unsigned DOBOT_WAR_PALLET_MASK		= (DOBOT_WARN_MASK | PALLET_SUBSYS_MASK);
const unsigned DOBOT_WAR_PALLET_ERGODIC_END = ((DOBOT_STATUS)(DOBOT_WAR_PALLET_MASK + 0)); //get a end signal of pallet vector dealing ergodic
