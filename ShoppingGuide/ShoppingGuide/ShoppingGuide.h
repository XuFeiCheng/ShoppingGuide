
// ShoppingGuide.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ADO/ado.h"

// CShoppingGuideApp: 
// �йش����ʵ�֣������ ShoppingGuide.cpp
//

class CShoppingGuideApp : public CWinApp
{
public:
	CShoppingGuideApp();
	static CADODatabase staffDB;
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShoppingGuideApp theApp;