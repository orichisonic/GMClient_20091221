// M_XD.h : M_XD DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// 主符号
#include "OperationXD.h"

// CM_XDApp
// 有关此类实现的信息，请参阅 M_XD.cpp
//

class CM_XDApp : public CWinApp
{
public:
	CM_XDApp();
	//设置父句柄
	HWND mHwndParent;
	//用于发送接收数据
	OperationXD operXD;
	//操作者ID
	int UserByID;

	//操作者用户名
	CString userName;

	//服务端发送过来的Message_Tag_ID
	CEnumCore::Message_Tag_ID m_TagID;

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
extern CM_XDApp theApp;
