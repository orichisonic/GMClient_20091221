// WAPlayerInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_WA.h"
#include "WAPlayerInfo.h"


// CWAPlayerInfo 对话框

IMPLEMENT_DYNAMIC(CWAPlayerInfo, CDialog)
CWAPlayerInfo::CWAPlayerInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CWAPlayerInfo::IDD, pParent)
{
}

CWAPlayerInfo::~CWAPlayerInfo()
{
}

void CWAPlayerInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBBASIC, cmbBasic);
	DDX_Control(pDX, IDC_CMBRESULT, cmbResult);	

	DDX_Control(pDX, IDC_LISTBASIC, listBasic);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);

	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
}


BEGIN_MESSAGE_MAP(CWAPlayerInfo, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTBASIC, OnNMClickListbasic)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBASIC, OnNMDblclkListbasic)
	ON_CBN_SELCHANGE(IDC_CMBRESULT, OnCbnSelchangeCmbresult)
	ON_CBN_SELCHANGE(IDC_CMBBASIC, OnCbnSelchangeCmbbasic)
END_MESSAGE_MAP()


// CWAPlayerInfo 消息处理程序

// 初始化对话框
BOOL CWAPlayerInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符	
	nItem = -1;
	pageBasic = false;
	pageResult = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//初始化一些私有变量

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

		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listBasic.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listBasic.MoveWindow(newRect);//设置好listBasic的位置

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//设置好listResult的位置，listResult和listBasic的位置完全重叠
		}
	}


	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//当前的状态为初始建立对话框
	if(theApp.operWA.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
	}
	return TRUE;
}

// 初始化显示字符
void CWAPlayerInfo::InitUI()
{
	SetWindowText(theApp.operWA.ReadValue("MWA","PI_UI_PlayerInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLNAME,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","PI_UI_SkillInfo"));
	tbcResult.InsertItem(2,theApp.operWA.ReadValue("MWA","PI_UI_TaskInfo"));
	//tbcResult.InsertItem(2,theApp.operWA.ReadValue("MWA","PI_UI_FinishedTask"));
	//tbcResult.InsertItem(3,theApp.operWA.ReadValue("MWA","PI_UI_UnfinishedTask"));
}

// 自动改变大小
void CWAPlayerInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
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
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listBasic.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listBasic.MoveWindow(newRect);//设置好listBasic的位置

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//设置好listResult的位置
		}
	}
}

//设置背景颜色
HBRUSH CWAPlayerInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询基本资料信息
void CWAPlayerInfo::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//基本资料列表没有选定项
		pageBasic = false;//基本资料列表不能翻页	
		cmbBasic.ResetContent();//清除基本资料列表翻页的复选框
		while(listBasic.DeleteColumn(0)){}//清除基本资料列表中的所有内容
	
		ShowResultInfo(SW_HIDE);
		ShowBasicInfo(SW_SHOW);

		UpdateData(true);			

		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家帐号
		GetDlgItemText(IDC_EDITNICK,UserNick);//获取玩家昵称
		if((UserName == "") && (UserNick == ""))//玩家帐号和玩家昵称不能同时为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_InputAccount"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BasicInfo();// 查询基本资料信息
	}
	catch(...)
	{
	}
}

// 查询基本资料信息
void CWAPlayerInfo::BasicInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operWA.ReadIntValue("MWA","index");//查询第一页的信息
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

		nItem = -1;//基本资料列表没有选定项
		pageBasic = false;//基本资料列表不能翻页	
		cmbBasic.ResetContent();//清除基本资料列表翻页的复选框
		while(listBasic.DeleteColumn(0)){}//清除基本资料列表中的所有内容

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//服务器IP、玩家账号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query);//发送查询基本资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_BasicInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 翻页查询基本资料信息
void CWAPlayerInfo::OnCbnSelchangeCmbbasic()
{	
	try
	{	
		if(pageBasic)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbBasic.GetCurSel() + 1;//页数为cmbBasic当前的索引值加1，也就是cmbBasic中当前显示的值
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

			while(listBasic.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query );//发送查询基本资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 单击基本资料信息保存当前行号
void CWAPlayerInfo::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listBasic.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listBasic.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listBasic.SubItemHitTest(&lvinfo);//保存在基本资料信息列表中选中的行号
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// 双击基本资料信息进行查询
void CWAPlayerInfo::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listBasic.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listBasic.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;
			nItem = listBasic.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nItem >= 0)
			{
				pageResult = false;
				cmbResult.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				ShowBasicInfo(SW_HIDE);
				ShowResultInfo(SW_SHOW);	

				UserName = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
				UserID = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
				UserNick = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称

				tbcResult.SetCurSel(1);

				//查询相关资料信息
				ResultInfo();
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}


// 切换选项卡进行查询
void CWAPlayerInfo::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	if(tbcResult.GetCurSel() == 0)//选中的是基本资料信息选项卡
	{	
		ShowResultInfo(SW_HIDE);
		ShowBasicInfo(SW_SHOW);
	}
	else
	{
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_SHOW);

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			UserName = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
			UserID = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// 保存选中的玩家ID
			UserNick = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家昵称

			//查询相关资料信息
			ResultInfo();
		}
	}
	*pResult = 0;
}

//查询相关资料信息
void CWAPlayerInfo::ResultInfo()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			if(tbcResult.GetCurSel()==1)
				theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_SkillsInfo_Query);//技能信息查询
			else if(tbcResult.GetCurSel()==2)	
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MissionsCompleted_Query);//已完成任务
			//else if(tbcResult.GetCurSel()==3)	
			//	theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MissionsReceived_Query);//已接任务

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_ResultInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 翻页进行查询
void CWAPlayerInfo::OnCbnSelchangeCmbresult()
{	
	try
	{
		if(pageResult)
		{
			CIni mIni;

			int index = cmbResult.GetCurSel() + 1;
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
				socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
				socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

				int midlength = socketdata.EnBody();
				if(tbcResult.GetCurSel()==1)
					theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_SkillsInfo_Query);//技能信息查询
				else if(tbcResult.GetCurSel()==2)	
					theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MissionsCompleted_Query);//已完成任务
				//else if(tbcResult.GetCurSel()==3)	
				//	theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MissionsReceived_Query);//已接任务
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_ResultInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 接收返回信息
LRESULT CWAPlayerInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	socketdata.DeBody(lpReceive,bodyLength);

	int pageCount = 0;

	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询服务器列表信息的回应
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
			}
			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://查询基本资料信息的回应
		{
			if(pageBasic)//如果已经能够翻页
			{
				theApp.operWA.BuildDataTable(&socketdata,&listBasic,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listBasic,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageBasic = false;//不能翻页					
					cmbBasic.ResetContent();//清空页数复选框
					while(listBasic.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbBasic.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbBasic.AddString(str);//在复选框中构造页数信息
					}
					cmbBasic.SetCurSel(0);//在复选框中选中第一页
					if(pageCount == 1)
					{
						pageBasic = false;//只有一页数据，不能翻页
					}
					else
					{
						pageBasic = true;//有多页数据，可以翻页
					}
				}				
			}
		}
		break;		
	default:
		{
			if(pageResult)//如果已经能够翻页
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					pageResult = false;//不能翻页		
					cmbResult.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					cmbResult.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbResult.AddString(str);
					}
					cmbResult.SetCurSel(0);
					if(pageCount == 1)
					{
						pageResult = false;
					}
					else
					{
						pageResult = true;
					}
				}				
			}
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// 清空页面
void CWAPlayerInfo::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITNAME,"");
	SetDlgItemText(IDC_EDITNICK,"");
}

// 关闭对话框
void CWAPlayerInfo::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//全选、复制
BOOL CWAPlayerInfo::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listBasic);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					for(int i=0; i<listBasic.GetItemCount(); i++)
					{
						listBasic.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listBasic.EnsureVisible(i,false);
					}
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					for(int i=0; i<listResult.GetItemCount(); i++)
					{
						listResult.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listResult.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

//基本资料信息页面
void CWAPlayerInfo::ShowBasicInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
}

//结果资料信息页面
void CWAPlayerInfo::ShowResultInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
}

