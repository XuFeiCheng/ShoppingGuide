
// Management.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ADO/ado.h"

// CManagementApp: 
// �йش����ʵ�֣������ Management.cpp
//

class CManagementApp : public CWinApp
{
public:
	CManagementApp();

// ��д
public:
	virtual BOOL InitInstance();
	//���徲̬DB
	static CADODatabase MarketDB;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CManagementApp theApp;