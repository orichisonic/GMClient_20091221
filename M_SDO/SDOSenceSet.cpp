// SDOSenceSet.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOSenceSet.h"
#include ".\sdosenceset.h"


// CSDOSenceSet 对话框

IMPLEMENT_DYNAMIC(CSDOSenceSet, CDialog)
CSDOSenceSet::CSDOSenceSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOSenceSet::IDD, pParent)
{
}

CSDOSenceSet::~CSDOSenceSet()
{
}

void CSDOSenceSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_LISTSENCE, listSence);
}


BEGIN_MESSAGE_MAP(CSDOSenceSet, CDialog)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTSENCE, OnLvnColumnclickListsence)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTSENCE, OnNMClickListsence)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTSENCE, OnNMDblclkListsence)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
END_MESSAGE_MAP()


// CSDOSenceSet 消息处理程序

// 初始化对话框
BOOL CSDOSenceSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();

	nItem=0;
	SenceID=0;
	SenceName="";

	ShowSence();

	CRect rs;
	GetClientRect(rs);; //获取对话框的大小信息


	CRect srcRect;
	CRect newRect;

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//获取tbcResult的大小信息
		tbcHeight = srcRect.bottom - srcRect.top;//得到tbcResult的高度信息

		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//设置好tbcResult的位置
	}

	if(listSence.m_hWnd != NULL)
	{
		newRect.top = rs.top +4+ tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listSence.MoveWindow(newRect);
	}

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Create");//当前的状态为初始建立对话框

	SenceInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 初始化显示字符
void CSDOSenceSet::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","SenceSet"));

	SetDlgItemText(IDC_LBLSENCEID,theApp.operSDO.ReadValue("MSDO","SenceID"));
	SetDlgItemText(IDC_LBLSENCENAME,theApp.operSDO.ReadValue("MSDO","SenceName"));
	
	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","AddSence"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));

	tbcResult.InsertItem(0,theApp.operSDO.ReadValue("MSDO","SenceQuery"));//场景查询
	tbcResult.InsertItem(1,theApp.operSDO.ReadValue("MSDO","AddSence"));
	tbcResult.InsertItem(2,theApp.operSDO.ReadValue("MSDO","UpdateSence"));
}

//显示场景列表信息
void CSDOSenceSet::ShowSence()
{
	GetDlgItem(IDC_LISTSENCE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLSENCEID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSENCENAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSENCEID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSENCENAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDSEARCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
}

//显示其它界面
void CSDOSenceSet::ShowOther()
{
	GetDlgItem(IDC_LISTSENCE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSENCEID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSENCENAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSENCEID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSENCENAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDSEARCH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
}

//单击列表头排序
void CSDOSenceSet::OnLvnColumnclickListsence(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listSence,pNMHDR,pResult);
}

// 自动改变大小
void CSDOSenceSet::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rs;
	GetClientRect(rs);

	CRect newRect;
	if(tbcResult.m_hWnd != NULL)
	{
	    newRect.top = rs.top + 4 ;
	    newRect.bottom = newRect.top + tbcHeight;
	    newRect.left = rs.left +10;
    	newRect.right = rs.right - 10;

	    tbcResult.MoveWindow(newRect);//设置好tbcResult的位置
	}

	if(listSence.m_hWnd != NULL)
	{
		newRect.top = rs.top +4+ tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listSence.MoveWindow(newRect);
	}
}

//设置背景颜色
HBRUSH CSDOSenceSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//处理快捷键响应函数
BOOL CSDOSenceSet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listSence.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listSence);				
				}
				
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listSence.m_hWnd)
				{
					for(int i=0; i<listSence.GetItemCount(); i++)
					{
					    listSence.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listSence.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

//关闭
void CSDOSenceSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//关闭窗体	
	DestroyWindow();
	CDialog::OnClose();
}

void CSDOSenceSet::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemInt(IDC_ETSENCEID,0);
	SetDlgItemText(IDC_ETSENCENAME,"");
}


//发送场景信息
void CSDOSenceSet::SenceInfo()
{
	try
	{		
		CIni mIni;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_QUERY))//比赛场景
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//切换tabCtrl
void CSDOSenceSet::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel()==0)
	{
		ShowSence();
		SenceInfo();
	}
	else if(tbcResult.GetCurSel()==1)//添加
	{
		ShowOther();
		SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","AddSence"));
		SetDlgItemInt(IDC_ETSENCEID,0);
		SetDlgItemText(IDC_ETSENCENAME,"");

	}
	else if(tbcResult.GetCurSel()==2)//编辑
	{
		ShowOther();
		SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","UpdateSence"));
		SetDlgItemInt(IDC_ETSENCEID,SenceID);
		SetDlgItemText(IDC_ETSENCENAME,SenceName);
		
	}
	*pResult = 0;
}

//单击场景列表框
void CSDOSenceSet::OnNMClickListsence(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 0)
	{
		if(listSence.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listSence.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listSence.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			SenceID=atoi(theApp.operSDO.GetValueByColName(&listSence, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SenceID")));
			SenceName=theApp.operSDO.GetValueByColName(&listSence, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Sence"));

		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

//添加或者编辑场景
void CSDOSenceSet::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		UpdateData(true);

		CString SenceOp = "";
		GetDlgItemText(IDSEARCH, SenceOp);

		if(SenceOp == theApp.operSDO.ReadValue("MSDO","AddSence"))
		{
			AddSence();
		}
		else if(SenceOp == theApp.operSDO.ReadValue("MSDO","UpdateSence"))
		{
			UpdateSence();
		}
	}
	catch(...)
	{
	}
}

//添加场景
void CSDOSenceSet::AddSence()
{
	try
	{
		CIni mIni;
		SenceID=GetDlgItemInt(IDC_ETSENCEID);
		GetDlgItemText(IDC_ETSENCENAME,SenceName);

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		int UserByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));
		
		_itoa(UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		///_itoa(SenceID,strInt,10);
		///socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//WeekDay

		

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_CREATE))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//编辑场景
void CSDOSenceSet::UpdateSence()
{

	try
	{
		CIni mIni;
		SenceID=GetDlgItemInt(IDC_ETSENCEID);
		GetDlgItemText(IDC_ETSENCENAME,SenceName);

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		int UserByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));

		_itoa(UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		_itoa(SenceID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//WeekDay



		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_UPDATE))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}

}
//双击场景列表删除
void CSDOSenceSet::OnNMDblclkListsence(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;

		UpdateData(true);
		CString strMsg = theApp.operSDO.ReadValue("MSDO","SS_UI_DelSence");
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
		{
			return;
		}
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有9个参数：开始时间、结束时间、时间间隔、公告内容、大区IP、操作员ID、公告状态、公告ID、服务器IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));
		
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		_itoa(SenceID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_DELETE))//
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// 接收返回信息
LRESULT CSDOSenceSet::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;
	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operSDO.ReadValue("MSDO","Main_UI_SENDDATAERROR"),theApp.operSDO.ReadValue("MSDO","ERROR"),0);//Main_UI_ParseData		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;
	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_QUERY_RESP:////查询场景
		{
			theApp.operSDO.BuildDataTable(&socketdata,&listSence,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_DELETE_RESP://SDO_CHALLENGE_SCENE_DELETE
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_CREATE_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operSDO.ShowResult(result);//显示操作结果
		}
		break;
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}