// M_PAL.h : M_PAL DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// 主符号
#include "OperationPAL.h"

// CM_PALApp
// 有关此类实现的信息，请参阅 M_PAL.cpp
//

class CM_PALApp : public CWinApp
{
public:
	CM_PALApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public:

	//用于发送接收数据
	OperationPAL operPAL;

	//整个通讯中使用的SOCKET
	//SOCKET mSocket;

	//操作者ID
	int UserByID;

	//操作者用户名
	CString userName;

	//服务端发送过来的Message_Tag_ID
	CEnumCore::Message_Tag_ID m_TagID;

	//设置父句柄
	HWND mHwndParent;
};

extern CM_PALApp theApp;