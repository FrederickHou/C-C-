
// LINK_DATABASE.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLINK_DATABASEApp: 
// �йش����ʵ�֣������ LINK_DATABASE.cpp
//

class CLINK_DATABASEApp : public CWinApp
{
public:
	CLINK_DATABASEApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLINK_DATABASEApp theApp;