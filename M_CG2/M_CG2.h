// M_CG2.h : M_CG2 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "OperationCG2.h"

// CM_CG2App
// �йش���ʵ�ֵ���Ϣ������� M_CG2.cpp
//

class CM_CG2App : public CWinApp
{
public:
	CM_CG2App();

	// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public:

	//���ڷ��ͽ�������
	OperationCG2 operCG2;

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

extern CM_CG2App theApp;