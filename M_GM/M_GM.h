// M_GM.h : M_GM DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "OperationGM.h"
#include "PopedomManage.h"
#include "ModiUserPwd.h"
#include "UpdateUserMAC.h"

// CM_GMApp
// �йش���ʵ�ֵ���Ϣ������� M_GM.cpp
//

class CM_GMApp : public CWinApp
{
public:
	CM_GMApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public://��Ŀ�е�ȫ�ֱ���

	//�޸��û�����
	CModiUserPwd modiUserPwd;

	//�����û�Ȩ�޵���
	CPopedomManage popedomManage;

	//�����û�Mac����
	CUpdateUserMAC updateUserMac;

	//���ڷ��ͽ�������
	OperationGM operGM;

	//���ڷ������ݵ�SOCKET����¼��ʱ���Ѿ�ȷ��
	//SOCKET mSocket;

	//ʹ��GMClient���ߵĲ���ԱID����¼��ʱ���Ѿ�ȷ��
	int UserByID;

	//ʹ��GMClient���ߵĲ���Ա���ƣ���¼��ʱ���Ѿ�ȷ��
	CString userName;

	//���ص�Message_Tag_ID���������´�������
	CEnumCore::Message_Tag_ID m_tag_id;

	//���ø����
	HWND mHwndParent;
};

extern CM_GMApp theApp;
