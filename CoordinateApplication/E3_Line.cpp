#include "stdafx.h"
#include "E3_Line.h"


_e3_Line::~_e3_Line(){}

_e3_Line::_e3_Line(){}

_e3_Line::_e3_Line(const _e3_Line& newObject) :S(newObject.S), C(newObject.C){}

_e3_Line::_e3_Line(const STANDARD& newS) :S(newS)
{

}