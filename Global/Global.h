// Global.h : Global DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "EnumCore.h"
#include "resource.h"		// 主符号

// CGlobalApp
// 有关此类实现的信息，请参阅 Global.cpp
//

class __declspec(dllexport) CGlobalApp : public CWinApp
{
public:
	CGlobalApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
