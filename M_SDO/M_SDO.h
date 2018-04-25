// M_SDO.h : M_SDO DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "OperationSDO.h"

// CM_SDOApp
// �йش���ʵ�ֵ���Ϣ������� M_SDO.cpp
//

class CM_SDOApp : public CWinApp
{
public:
	CM_SDOApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public:

	//���ڷ��ͽ�������
	OperationSDO operSDO;

	//����ͨѶ��ʹ�õ�SOCKET
	SOCKET mSocket;

	//������ID
	int UserByID;

	//�������û���
	CString userName;

	//����˷��͹�����Message_Tag_ID
	CEnumCore::Message_Tag_ID m_TagID;

	//���ø����
	HWND mHwndParent;
};
extern CM_SDOApp theApp;
