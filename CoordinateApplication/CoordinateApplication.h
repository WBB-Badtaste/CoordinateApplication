
// CoordinateApplication.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCoordinateApplicationApp: 
// �йش����ʵ�֣������ CoordinateApplication.cpp
//

class CCoordinateApplicationApp : public CWinApp
{
public:
	CCoordinateApplicationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCoordinateApplicationApp theApp;