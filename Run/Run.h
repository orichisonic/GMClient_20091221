// Run.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CRunApp:
// �йش����ʵ�֣������ Run.cpp
//

class CRunApp : public CWinApp
{
public:
	CRunApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	BOOL MoveFiles();
};

extern CRunApp theApp;
