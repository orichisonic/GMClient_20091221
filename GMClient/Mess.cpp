// Mess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GMClient.h"
#include "Mess.h"


// CMess �Ի���

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


// CMess ��Ϣ�������
