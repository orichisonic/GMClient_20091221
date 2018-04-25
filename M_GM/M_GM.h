// M_GM.h : M_GM DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// 主符号
#include "OperationGM.h"
#include "PopedomManage.h"
#include "ModiUserPwd.h"
#include "UpdateUserMAC.h"

// CM_GMApp
// 有关此类实现的信息，请参阅 M_GM.cpp
//

class CM_GMApp : public CWinApp
{
public:
	CM_GMApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public://项目中的全局变量

	//修改用户密码
	CModiUserPwd modiUserPwd;

	//分配用户权限的类
	CPopedomManage popedomManage;

	//重置用户Mac的类
	CUpdateUserMAC updateUserMac;

	//用于发送接收数据
	OperationGM operGM;

	//用于发送数据的SOCKET，登录的时候已经确定
	//SOCKET mSocket;

	//使用GMClient工具的操作员ID，登录的时候已经确定
	int UserByID;

	//使用GMClient工具的操作员名称，登录的时候已经确定
	CString userName;

	//返回的Message_Tag_ID，用于向下传递数据
	CEnumCore::Message_Tag_ID m_tag_id;

	//设置父句柄
	HWND mHwndParent;
};

extern CM_GMApp theApp;
