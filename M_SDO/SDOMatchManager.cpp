// SDOMatchManager.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOMatchManager.h"
#include ".\sdomatchmanager.h"


// CSDOMatchManager 对话框

IMPLEMENT_DYNAMIC(CSDOMatchManager, CDialog)
CSDOMatchManager::CSDOMatchManager(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOMatchManager::IDD, pParent)
{
}

CSDOMatchManager::~CSDOMatchManager()
{
}

void CSDOMatchManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBWEEKDAY, cmbWeekDay);
	DDX_Control(pDX, IDC_CMBSENCE, cmbSence);
	DDX_Control(pDX, IDC_CMBMODE, cmbMode);
	DDX_Control(pDX, IDC_LISTMATCH, listMatch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
}


BEGIN_MESSAGE_MAP(CSDOMatchManager, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BTOK, OnBnClickedBtok)
	ON_NOTIFY(NM_CLICK, IDC_LISTMATCH, OnNMClickListmatch)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTMATCH, OnNMDblclkListmatch)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTMATCH, OnLvnColumnclickListmatch)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
END_MESSAGE_MAP()


// CSDOMatchManager 消息处理程序

// 初始化对话框
BOOL CSDOMatchManager::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();// 初始化显示字符

	ShowMatch();

	SetProp(listMatch.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listMatch.GetSafeHwnd(),"排序顺序",(HANDLE)1);


	ServerIP = "";
//	strServer="";

	nItem=0;
	MiniuteOpen=0;
	MiniuteUnit=0;
	GCash=0;
	pageInfo = false;
	
	
	SetProp(listMatch.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listMatch.GetSafeHwnd(),"排序顺序",(HANDLE)1);

	CRect rs;
	GetClientRect(rs);; //获取对话框的大小信息


	CRect srcRect;
	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
		GrpSearch.GetWindowRect(srcRect);//获取GrpSearch的大小信息
		grpHeight = srcRect.bottom - srcRect.top;//得到GrpSearch的高度信息

		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//设置好GrpSearch的位置
	}

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//获取tbcResult的大小信息
		tbcHeight = srcRect.bottom - srcRect.top;//得到tbcResult的高度信息

		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//设置好tbcResult的位置
	}

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//获取GrpPage的大小信息
		grpPHeight = srcRect.bottom - srcRect.top;//得到GrpPage的高度信息

		newRect.top = rs.top + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listMatch.m_hWnd != NULL)
	{
		newRect.top = rs.top +4+ grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMatch.MoveWindow(newRect);
	}

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Create");//当前的状态为初始建立对话框

	if(theApp.operSDO.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 初始化显示字符
void CSDOMatchManager::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","MM_UI_MatchManager"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operSDO.ReadValue("MSDO","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operSDO.ReadValue("MSDO","UIC_UI_LblServer"));
	SetDlgItemText(IDC_BTOK,theApp.operSDO.ReadValue("MSDO","Search"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operSDO.ReadValue("MSDO","UIC_UI_Page"));

	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","AddMatch"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));

	SetDlgItemText(IDC_LBLCHECKEDSERVER,theApp.operSDO.ReadValue("MSDO","CheckedServer"));
	SetDlgItemText(IDC_LBLWEEKDAY,theApp.operSDO.ReadValue("MSDO","WeekDay"));
	SetDlgItemText(IDC_LBLMINIUTEOPEN,theApp.operSDO.ReadValue("MSDO","MiniuteOpen"));
	SetDlgItemText(IDC_LBLMINIUTEUNIT,theApp.operSDO.ReadValue("MSDO","MiniuteUnit"));
	SetDlgItemText(IDC_LBLCHARGEGCASH,theApp.operSDO.ReadValue("MSDO","ChargeGCash"));
	SetDlgItemText(IDC_LBLSENCE,theApp.operSDO.ReadValue("MSDO","Sence"));
	SetDlgItemText(IDC_LBLMODE,theApp.operSDO.ReadValue("MSDO","Mode"));

	tbcResult.InsertItem(0,theApp.operSDO.ReadValue("MSDO","MM_UI_tpgMatch"));
	tbcResult.InsertItem(1,theApp.operSDO.ReadValue("MSDO","MM_UI_tpgAddMatch"));//添加比赛信息
	tbcResult.InsertItem(2,theApp.operSDO.ReadValue("MSDO","MM_UI_tpgUpdateMatch"));//编辑比赛信息

//	WeekDay();
//	Mode();
}

// 自动改变大小
void CSDOMatchManager::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
	    newRect.top = rs.top + 4;		
	    newRect.left = rs.left +10;
	    newRect.right = rs.right - 10;
	    newRect.bottom = newRect.top + grpHeight;

	    GrpSearch.MoveWindow(newRect);//设置好GrpSearch的位置
	}

	if(tbcResult.m_hWnd != NULL)
	{
	    newRect.top = rs.top + 4 + grpHeight;
	    newRect.bottom = newRect.top + tbcHeight;
	    newRect.left = rs.left +10;
    	newRect.right = rs.right - 10;

	    tbcResult.MoveWindow(newRect);//设置好tbcResult的位置
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listMatch.m_hWnd != NULL)
	{
		newRect.top = rs.top +4+ grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMatch.MoveWindow(newRect);
	}
}

//设置背景颜色
HBRUSH CSDOMatchManager::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 关闭对话框
void CSDOMatchManager::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//关闭窗体	

	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!SenceList.IsEmpty())
	{
		SenceList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//处理快捷键响应函数
BOOL CSDOMatchManager::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listMatch.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listMatch);				
				}
				
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listMatch.m_hWnd)
				{
					for(int i=0; i<listMatch.GetItemCount(); i++)
					{
					    listMatch.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listMatch.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

void CSDOMatchManager::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_ETCHECKSERVER,"");
	cmbWeekDay.SetCurSel(0);
	SetDlgItemText(IDC_ETMINIUTEOPEN,"");
	SetDlgItemText(IDC_ETMINIUTEUNIT,"");
	SetDlgItemText(IDC_ETCHARGEGCASH,"");
	cmbSence.SetCurSel(0);
	cmbMode.SetCurSel(0);
}

//显示比赛信息
void CSDOMatchManager::ShowMatch()
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTMATCH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLCHECKEDSERVER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLWEEKDAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMINIUTEOPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMINIUTEUNIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCHARGEGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMODE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_ETCHECKSERVER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBWEEKDAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMINIUTEOPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMINIUTEUNIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCHARGEGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBMODE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDSEARCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);//
}

//显示其它信息
void CSDOMatchManager::ShowOther()
{
	GetDlgItem(IDC_LISTMATCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLCHECKEDSERVER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLWEEKDAY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLMINIUTEOPEN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLMINIUTEUNIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLCHARGEGCASH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSENCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLMODE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_ETCHECKSERVER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBWEEKDAY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETMINIUTEOPEN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETMINIUTEUNIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETCHARGEGCASH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBSENCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBMODE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDSEARCH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);

	WeekDay();
	Mode();


}

// 切换选项卡进行查询
void CSDOMatchManager::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel()==0)
	{
		ShowMatch();
	}
	else if(tbcResult.GetCurSel()==1)//添加
	{
		ShowOther();
		SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","AddMatch"));
		SetDlgItemText(IDC_ETCHECKSERVER,ServerName);
		GetDlgItem(IDC_ETCHECKSERVER)->EnableWindow(false);

		SetDlgItemInt(IDC_ETMINIUTEOPEN,0);
		SetDlgItemInt(IDC_ETMINIUTEUNIT,0);
		SetDlgItemInt(IDC_ETCHARGEGCASH,0);

		SenceQuery();
		
	}
	else if(tbcResult.GetCurSel()==2)//编辑
	{
		ShowOther();
		SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","UpdateMatch"));

		SetDlgItemText(IDC_ETCHECKSERVER,ServerName);
		GetDlgItem(IDC_ETCHECKSERVER)->EnableWindow(false);

		SetDlgItemInt(IDC_ETMINIUTEOPEN,MiniuteOpen);
		SetDlgItemInt(IDC_ETMINIUTEUNIT,MiniuteUnit);
		SetDlgItemInt(IDC_ETCHARGEGCASH,GCash);

		SenceQuery();
	}
	*pResult = 0;
}

////查询比赛信息
void CSDOMatchManager::OnBnClickedBtok()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;

		int index = theApp.operSDO.ReadIntValue("MSDO","index");//查询第一页的信息
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		pageInfo=false;
		cmbPage.ResetContent();
		while(listMatch.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			
		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_SelectServer"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
	
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

//添加或者编辑比赛
void CSDOMatchManager::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		UpdateData(true);

		CString MatchOp = "";
		GetDlgItemText(IDSEARCH, MatchOp);

		if(MatchOp == theApp.operSDO.ReadValue("MSDO","AddMatch"))//添加比赛
		{
			AddMatch();
		}
		else if(MatchOp == theApp.operSDO.ReadValue("MSDO","UpdateMatch"))//编辑比赛
		{
			UpdateMatch();
		}
	}
	catch(...)
	{
	}
}

//添加比赛
void CSDOMatchManager::AddMatch()
{
	try
	{
		CIni mIni;
		CString strMode="";
		int iPos=((CComboBox*)GetDlgItem(IDC_CMBMODE))->GetCurSel();//当前选中的行
		if(iPos==0)
			strMode="10";
		else if(iPos==1)
			strMode="13";
		else if(iPos==2)
			strMode="12";
		else if(iPos==3)
			strMode="11";

		int nDay=((CComboBox*)GetDlgItem(IDC_CMBWEEKDAY))->GetCurSel();//当前选中的行

		CString strSence="";
		GetDlgItemText(IDC_CMBSENCE,strSence);

		MiniuteOpen=GetDlgItemInt(IDC_ETMINIUTEOPEN);
		MiniuteUnit=GetDlgItemInt(IDC_ETMINIUTEUNIT);
		GCash=GetDlgItemInt(IDC_ETCHARGEGCASH);

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		int UserByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_IsBattle,CEnumCore::TagFormat::TLV_STRING,strlen(strMode),(unsigned char *)mIni.wcharToChar(strMode));//mode
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(strSence),(unsigned char *)mIni.wcharToChar(strSence));//sence

		_itoa(UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		_itoa(nDay,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_WeekDay,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//WeekDay

		_itoa(MiniuteOpen,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_StPtMin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(MiniuteUnit,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_MatPtMin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(GCash,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_GCash,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_INSERT))
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

//编辑比赛
void CSDOMatchManager::UpdateMatch()
{
	try
	{
		CIni mIni;
		CString strMode="";
		int iPos=((CComboBox*)GetDlgItem(IDC_CMBMODE))->GetCurSel();//当前选中的行
		if(iPos==0)
			strMode="10";
		else if(iPos==1)
			strMode="13";
		else if(iPos==2)
			strMode="12";
		else if(iPos==3)
			strMode="11";

		int nDay=((CComboBox*)GetDlgItem(IDC_CMBWEEKDAY))->GetCurSel();//当前选中的行

		MiniuteOpen=GetDlgItemInt(IDC_ETMINIUTEOPEN);//开放分钟数
		MiniuteUnit=GetDlgItemInt(IDC_ETMINIUTEUNIT);//撮合分钟数
		GCash=GetDlgItemInt(IDC_ETCHARGEGCASH);

		CSocketData socketdata;	
		socketdata.InitCreate(1,11);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		int UserByID=theApp.UserByID;
		int SenceID1=0;

		SenceList.Lookup(cmbSence.GetCurSel()+1,SenceID1);
		CString strSence="";
		GetDlgItemText(IDC_CMBSENCE,strSence);

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_IsBattle,CEnumCore::TagFormat::TLV_STRING,strlen(strMode),(unsigned char *)mIni.wcharToChar(strMode));//mode

		_itoa(SenceID1,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//sence

		_itoa(UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		_itoa(nDay,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_WeekDay,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//WeekDay

		_itoa(MiniuteOpen,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_StPtMin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(MiniuteUnit,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_MatPtMin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(GCash,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_GCash,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(SenceID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_UPDATE))
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

//切换翻页框
void CSDOMatchManager::OnCbnSelchangeCmbpage()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//每页显示50条记录

			while(listMatch.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();

			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_QUERY))//
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
			}


			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Error_Page"),theApp.operSDO.ReadValue("MSDO","Error"),0);
	}
}


//导入星期数
void CSDOMatchManager::WeekDay()
{
	cmbWeekDay.ResetContent();
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Sun"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Mon"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Tues"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Wens"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Thus"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Fri"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Sat"));
	cmbWeekDay.SetCurSel(0);
}

//导入比赛模式
void CSDOMatchManager::Mode()
{
	cmbMode.ResetContent();
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type1"));//普通大赛
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type2"));//Showtime
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type3"));//道具战大赛
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type4"));//反键大赛
	cmbMode.SetCurSel(0);
}


//查询比赛场景
void CSDOMatchManager::SenceQuery()
{
	try
	{		
		CIni mIni;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		

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

// 接收返回信息
LRESULT CSDOMatchManager::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询服务器列表信息的回应
		{
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operSDO.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_QUERY_RESP:////查询场景
		{
			if(!SenceList.IsEmpty())
			{
				SenceList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int nItem = StrToInt((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::SDO_SenceID).lpdata);//得到服务器IP
				SenceList.SetAt(i,nItem);//
			}

			theApp.operSDO.BuildComboxScene(&socketdata,&cmbSence);
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_QUERY_RESP:////查询比赛信息
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listMatch,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listMatch,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
					cmbPage.ResetContent();
					while(listMatch.DeleteColumn(0)){}
				}
				else
				{
					cmbPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);
					}
					cmbPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageInfo = false;
					}
					else
					{
						pageInfo = true;
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_INSERT_RESP:
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_DELETE_RESP:
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


//单击比赛信息列表框
void CSDOMatchManager::OnNMClickListmatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 0)
	{
		if(listMatch.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listMatch.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listMatch.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			SenceID=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SenceID")));

			MiniuteOpen=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_StPtMin")));
			MiniuteUnit=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_MatPtMin")));
			GCash=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GCash")));
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

//双击比赛信息列表框删除
void CSDOMatchManager::OnNMDblclkListmatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		if(listMatch.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listMatch.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listMatch.SubItemHitTest(&lvinfo);//

			if(nItem >= 0)
			{
				SenceID=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SenceID")));
				DelMatch();

			}
		}
		else
		{
			nItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

//删除比赛信息
void CSDOMatchManager::DelMatch()
{
	try
	{
		CIni mIni;

		UpdateData(true);
		CString strMsg = theApp.operSDO.ReadValue("MSDO","MM_UI_DelMatch");
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
		{
			return;
		}
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有9个参数：开始时间、结束时间、时间间隔、公告内容、大区IP、操作员ID、公告状态、公告ID、服务器IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		_itoa(SenceID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

//		_itoa(UserID,strInt,10);
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//家族ID

//		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_DELETE))//
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//单击列名排序
void CSDOMatchManager::OnLvnColumnclickListmatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listMatch,pNMHDR,pResult);
}

