// M_XD.h : M_XD DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "OperationXD.h"

// CM_XDApp
// �йش���ʵ�ֵ���Ϣ������� M_XD.cpp
//

class CM_XDApp : public CWinApp
{
public:
	CM_XDApp();
	//���ø����
	HWND mHwndParent;
	//���ڷ��ͽ�������
	OperationXD operXD;
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
extern CM_XDApp theApp;
