// TEMP.h : TEMP DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CTEMPApp
// �йش���ʵ�ֵ���Ϣ������� TEMP.cpp
//

class CTEMPApp : public CWinApp
{
public:
	CTEMPApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
