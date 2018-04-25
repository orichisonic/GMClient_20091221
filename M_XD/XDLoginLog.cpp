// XDLoginLog.cpp : 实现文件
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDLoginLog.h"
#include ".\xdloginlog.h"


// CXDLoginLog 对话框

IMPLEMENT_DYNAMIC(CXDLoginLog, CDialog)
CXDLoginLog::CXDLoginLog(CWnd* pParent /*=NULL*/)
	: CDialog(CXDLoginLog::IDD, pParent)
{
}

CXDLoginLog::~CXDLoginLog()
{
}

void CXDLoginLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);	
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartTime);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndTime);	

	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBBASIC, cmbBasic);
	DDX_Control(pDX, IDC_CMBRESULT, cmbResult);

	DDX_Control(pDX, IDC_LISTBASIC, listBasic);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);

	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);

	DDX_Control(pDX, IDC_CHECKBYACCOUNT, checkByAccount);
	DDX_Control(pDX, IDC_CHECKBYIP, checkByIP);
	DDX_Control(pDX, IDC_IPADDRESSCHECK, IPACtrl_UserIP);
}


BEGIN_MESSAGE_MAP(CXDLoginLog, CDialog)	
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBBASIC, OnCbnSelchangeCmbbasic)	
	ON_NOTIFY(NM_CLICK, IDC_LISTBASIC, OnNMClickListbasic)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBASIC, OnNMDblclkListbasic)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_CBN_SELCHANGE(IDC_CMBRESULT, OnCbnSelchangeCmbresult)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECKBYACCOUNT, OnBnClickedCheckbyaccount)
	ON_BN_CLICKED(IDC_CHECKBYIP, OnBnClickedCheckbyip)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTBASIC, OnLvnColumnclickListbasic)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_BN_CLICKED(IDC_BTNLOG, OnBnClickedBtnlog)
END_MESSAGE_MAP()


// CXDLoginLog 消息处理程序

// 初始化对话框
BOOL CXDLoginLog::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符
	ServerName = "";
	ServerIP = "";
	UserNick = "";
	UserIP = "";//初始化一些私有变量
	checkType = 1;//通过账号查询
	checkByAccount.SetCheck(1);
	ShowCheckByName();//显示通过帐号查询的信息

	SetProp(listResult.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listResult.GetSafeHwnd(),"排序顺序",(HANDLE)1);

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

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//当前的状态为初始建立对话框

	if(theApp.operXD.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}

// 初始化显示字符
void CXDLoginLog::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","AL_UI_LoginLog"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLNAME,theApp.operXD.ReadValue("MXD","AL_UI_Account"));
	SetDlgItemText(IDC_LBLNICK,theApp.operXD.ReadValue("MXD","AL_UI_UserNick"));
	SetDlgItemText(IDC_LBLIP,theApp.operXD.ReadValue("MXD","AL_UI_UserIP"));

	SetDlgItemText(IDC_CHECKBYACCOUNT,theApp.operXD.ReadValue("MXD","AL_UI_CheckByName"));
	SetDlgItemText(IDC_CHECKBYIP,theApp.operXD.ReadValue("MXD","AL_UI_CheckByIP"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operXD.ReadValue("MXD","UIC_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operXD.ReadValue("MXD","UIC_UI_EndTime"));

	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	SetDlgItemText(IDC_BTNLOG,theApp.operXD.ReadValue("MXD","LogSearch"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","AL_UI_LoginLog"));
}

//处理快捷键响应函数
BOOL CXDLoginLog::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listBasic);
				}
				if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listResult);
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
				if(pMsg->hwnd == listResult.m_hWnd)
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

// 自动改变大小
void CXDLoginLog::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CXDLoginLog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(backColor);
}

// 设置通过帐号来查询
void CXDLoginLog::OnBnClickedCheckbyaccount()
{
	if(checkByAccount.GetCheck() == 1)
	{
		checkByIP.SetCheck(0);
		ShowCheckByName();
	}
	else
	{
		checkByIP.SetCheck(1);
		ShowCheckByIP();
	}
}

// 设置通过IP来查询
void CXDLoginLog::OnBnClickedCheckbyip()
{
	if(checkByIP.GetCheck() == 1)
	{
		checkByAccount.SetCheck(0);
		ShowCheckByIP();
	}
	else
	{
		checkByAccount.SetCheck(1);
		ShowCheckByName();
	}
}

// 查询玩家登录日志信息
void CXDLoginLog::OnBnClickedSearch()
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
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家帐号
		GetDlgItemText(IDC_EDITNICK,UserNick);//获取玩家昵称
		if((UserName == "") && (UserNick == ""))//玩家帐号和玩家昵称不能同时为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_InputAccount"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BasicInfo();// 查询基本资料信息
	}
	catch(...)
	{
	}
}

// 查询基本资料信息
void CXDLoginLog::BasicInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operXD.ReadIntValue("MXD","index");//查询第一页的信息
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录

		nItem = -1;//基本资料列表没有选定项
		pageBasic = false;//基本资料列表不能翻页	
		cmbBasic.ResetContent();//清除基本资料列表翻页的复选框
		while(listBasic.DeleteColumn(0)){}//清除基本资料列表中的所有内容

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//服务器IP、玩家账号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen("1"),(unsigned char *)mIni.wcharToChar("1"));//查找类型
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query);//发送查询基本资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_BasicInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// 翻页查询基本资料信息
void CXDLoginLog::OnCbnSelchangeCmbbasic()
{	
	try
	{	
		if(pageBasic)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbBasic.GetCurSel() + 1;//页数为cmbBasic当前的索引值加1，也就是cmbBasic中当前显示的值
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录

			while(listBasic.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen("1"),(unsigned char *)mIni.wcharToChar("1"));//查找类型

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query);//发送查询基本资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Page"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// 单击基本资料信息保存当前行号
void CXDLoginLog::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
void CXDLoginLog::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
				checkType = 1;
				pageResult = false;
				cmbResult.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
				//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// 保存选中的玩家ID
				UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称
				UserIP = "";
				
				tbcResult.SetCurSel(1);
				ShowBasicInfo(SW_HIDE);
				ShowResultInfo(SW_SHOW);

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
void CXDLoginLog::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	if(tbcResult.GetCurSel() == 0)//选中的是基本资料信息选项卡
	{	
		ShowResultInfo(SW_HIDE);
		ShowBasicInfo(SW_SHOW);
	}
	else
	{
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_SHOW);

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			checkType = 1;
			pageResult = false;
			cmbResult.ResetContent();
			while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

			UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
			//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// 保存选中的玩家ID
			UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称
			UserIP = "";

			//查询相关资料信息
			ResultInfo();
		}
	}
	*pResult = 0;
}

//通过IP查询日志信息
void CXDLoginLog::OnBnClickedBtnlog()
{
	try
	{
		UpdateData(true);			
		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_IPADDRESSCHECK,UserIP);//获取玩家IP
		if(!strcmp(UserIP,"0.0.0.0"))//玩家IP不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_InputNotNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		UserName = "";
		UserNick = "";

		checkType = 2;//通过IP查询
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		tbcResult.SetCurSel(1);
		ShowResultInfo(SW_SHOW);
		ShowBasicInfo(SW_HIDE);

		ResultInfo();
	}
	catch(...)
	{
	}
}

//查询相关资料信息
void CXDLoginLog::ResultInfo()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		CTime sTime;
		dtcStartTime.GetTime(sTime);//获取开始时间
		CTime eTime;
		dtcEndTime.GetTime(eTime);//获取结束时间
		BeginTime = sTime.Format("%Y-%m-%d %H:%M:%S");//获取开始时间
		EndTime = eTime.Format("%Y-%m-%d %H:%M:%S");//获取结束时间

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_LogInOutIP,CEnumCore::TagFormat::TLV_STRING,strlen(UserIP),(unsigned char *)mIni.wcharToChar(UserIP));//玩家IP
			
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(BeginTime),(unsigned char*)mIni.wcharToChar(BeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(EndTime),(unsigned char*)mIni.wcharToChar(EndTime));//结束时间

		_itoa(checkType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_LoginType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用账号或IP查询

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Login_Log);//玩家登陆/登出日志

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// 翻页进行查询
void CXDLoginLog::OnCbnSelchangeCmbresult()
{	
	try
	{
		if(pageResult)
		{
			CIni mIni;

			int index = cmbResult.GetCurSel() + 1;
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			while(listResult.DeleteColumn(0)){}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_LogInOutIP,CEnumCore::TagFormat::TLV_STRING,strlen(UserIP),(unsigned char *)mIni.wcharToChar(UserIP));//玩家IP
				
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(BeginTime),(unsigned char*)mIni.wcharToChar(BeginTime));//开始时间
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(EndTime),(unsigned char*)mIni.wcharToChar(EndTime));//结束时间

			_itoa(checkType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_LoginType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用账号或IP查询

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Login_Log);//玩家登陆/登出日志

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// 接收返回信息
LRESULT CXDLoginLog::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operXD.ReadValue("MXD","Main_UI_ParseData"),theApp.operXD.ReadValue("MXD","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}
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

			theApp.operXD.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://查询基本资料信息的回应
		{
			if(pageBasic)//如果已经能够翻页
			{
				theApp.operXD.BuildDataTable(&socketdata,&listBasic,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listBasic,&pageCount);//构造CListCtrl对象

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
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

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

// 关闭对话框
void CXDLoginLog::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	CTime curTime = CTime::GetCurrentTime();//获取当前时间
	dtcStartTime.SetTime(&curTime);
	dtcEndTime.SetTime(&curTime);
	ShowCheckByName();
	tbcResult.SetCurSel(0);
	ShowResultInfo(SW_HIDE);
	ShowBasicInfo(SW_SHOW);
}

// 关闭对话框
void CXDLoginLog::OnClose()
{
	dlgStatus = theApp.operXD.ReadIntValue("MXD","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//显示通过角色名查询的信息
void CXDLoginLog::ShowCheckByName(void)
{
	GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNLOG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLNAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITNAME)->ShowWindow(SW_SHOW);	
	GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDSEARCH)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_EDITNAME,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_IPADDRESSCHECK,"");
}

//显示通过IP查询的信息
void CXDLoginLog::ShowCheckByIP(void)
{
	GetDlgItem(IDC_LBLIP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNLOG)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITNAME)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDSEARCH)->ShowWindow(SW_HIDE);
	SetDlgItemText(IDC_EDITNAME,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_IPADDRESSCHECK,"");
}

//基本资料信息页面
void CXDLoginLog::ShowBasicInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
}

//结果资料信息页面
void CXDLoginLog::ShowResultInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
}

//单击基本资料信息的列名进行排序
void CXDLoginLog::OnLvnColumnclickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operXD.SortListInfo(&listBasic,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CXDLoginLog::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operXD.SortListInfo(&listResult,pNMHDR,pResult);
}
