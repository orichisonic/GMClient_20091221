// M_JW2.h : M_JW2 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "OperationJW2.h"


// CM_JW2App
// �йش���ʵ�ֵ���Ϣ������� M_JW2.cpp
//

class CM_JW2App : public CWinApp
{
public:
	CM_JW2App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public:
	//���ڷ��ͽ�������
	OperationJW2 operJW2;

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
extern CM_JW2App theApp;
