// M_GTOWN.h : M_GTOWN DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "OperationGtown.h"


// CM_GTOWNApp
// �йش���ʵ�ֵ���Ϣ������� M_GTOWN.cpp
//

class CM_GTOWNApp : public CWinApp
{
public:
	CM_GTOWNApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	
	//���ڷ��ͽ�������
	OperationGTOWN operGTOWN;

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
extern CM_GTOWNApp theApp;
