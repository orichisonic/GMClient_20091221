// M_PAL.h : M_PAL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "OperationPAL.h"

// CM_PALApp
// �йش���ʵ�ֵ���Ϣ������� M_PAL.cpp
//

class CM_PALApp : public CWinApp
{
public:
	CM_PALApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public:

	//���ڷ��ͽ�������
	OperationPAL operPAL;

	//����ͨѶ��ʹ�õ�SOCKET
	//SOCKET mSocket;

	//������ID
	int UserByID;

	//�������û���
	CString userName;

	//����˷��͹�����Message_Tag_ID
	CEnumCore::Message_Tag_ID m_TagID;

	//���ø����
	HWND mHwndParent;
};

extern CM_PALApp theApp;