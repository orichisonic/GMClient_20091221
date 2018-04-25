// Mess.cpp : 实现文件
//

#include "stdafx.h"
#include "GMClient.h"
#include "Mess.h"


// CMess 对话框

IMPLEMENT_DYNAMIC(CMess, CDialog)
CMess::CMess(CWnd* pParent /*=NULL*/)
	: CDialog(CMess::IDD, pParent)
{
}

CMess::~CMess()
{
}

void CMess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMess, CDialog)
END_MESSAGE_MAP()


// CMess 消息处理程序
