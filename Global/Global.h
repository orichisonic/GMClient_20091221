// Global.h : Global DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "EnumCore.h"
#include "resource.h"		// ������

// CGlobalApp
// �йش���ʵ�ֵ���Ϣ������� Global.cpp
//

class __declspec(dllexport) CGlobalApp : public CWinApp
{
public:
	CGlobalApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
