// M_WA.h : M_WA DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "OperationWA.h"

// CM_WAApp
// �йش���ʵ�ֵ���Ϣ������� M_WA.cpp
//

class CM_WAApp : public CWinApp
{
public:
	CM_WAApp();
	//���ø����
	HWND mHwndParent;
	//���ڷ��ͽ�������
	OperationWA operWA;
	//������ID
	int UserByID;

	//�������û���
	CString userName;

	//����˷��͹�����Message_Tag_ID
	CEnumCore::Message_Tag_ID m_TagID;

	// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
extern CM_WAApp theApp;
