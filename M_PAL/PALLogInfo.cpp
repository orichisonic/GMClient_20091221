// PALLogInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALLogInfo.h"
#include ".\palloginfo.h"


// CPALLogInfo 对话框

IMPLEMENT_DYNAMIC(CPALLogInfo, CDialog)
CPALLogInfo::CPALLogInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CPALLogInfo::IDD, pParent)
{
}

CPALLogInfo::~CPALLogInfo()
{
}

void CPALLogInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBBIGTYPE, cmbBigType);
	DDX_Control(pDX, IDC_CMBSMALLTYPE, cmbSmallType);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartDate);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndDate);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
}


BEGIN_MESSAGE_MAP(CPALLogInfo, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_CBN_SELCHANGE(IDC_CMBBIGTYPE, OnCbnSelchangeCmbbigtype)
	ON_BN_CLICKED(IDC_BTNSEARCHLOG, OnBnClickedBtnsearchlog)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
END_MESSAGE_MAP()


// CPALLogInfo 消息处理程序

// 初始化对话框
BOOL CPALLogInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符

	nItem = 0;
	pageInfo = false;
	ServerIP = "";//初始化服务器IP
	ServerName = "";//初始化服务器名
	UserAccount = "";
	UserName = "";//初始化玩家角色名
	BigType = "";//日志大类
	bTypeID = 0;//日志大类ID
	SmallType = "";//日志小类
	sTypeID = 0;//日志小类ID	
	strStartTime = "";//开始时间
	strEndTime = "";//结束时间

	ShowUserInfo();//显示玩家资料信息界面

	SetProp(listUser.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listUser.GetSafeHwnd(),"排序顺序",(HANDLE)1);

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
	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listResult的位置
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

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}

	//OperationPAL operPAL;
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//当前的状态为初始建立对话框

	if(theApp.operPAL.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
	}
	return TRUE;
}

// 初始化显示字符
void CPALLogInfo::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","LI_UI_LogInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));

	SetDlgItemText(IDC_LBLBIGTYPE,theApp.operPAL.ReadValue("MPAL","LI_UI_BigType"));
	SetDlgItemText(IDC_LBLSMALLTYPE,theApp.operPAL.ReadValue("MPAL","LI_UI_SmallType"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operPAL.ReadValue("MPAL","LI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operPAL.ReadValue("MPAL","LI_UI_EndTime"));
	SetDlgItemText(IDC_BTNSEARCHLOG,theApp.operPAL.ReadValue("MPAL","LI_UI_SearchLog"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","LI_UI_tpgLogInfo"));
}

//处理快捷键响应函数
BOOL CPALLogInfo::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operPAL;
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					for(int i=0; i<listUser.GetItemCount(); i++)
					{
					    listUser.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listUser.EnsureVisible(i,false);
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

// 自动改变大小
void CPALLogInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

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
	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listResult的位置
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CPALLogInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//查询玩家资料信息
void CPALLogInfo::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;

		ShowUserInfo();

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//查询第一页的信息
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_SelectServer"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//获取玩家帐号
		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家角色名
		if((UserName == "") && (UserAccount == ""))//玩家帐号和玩家角色名不能同时为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_InputAccount"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERINFO))//发送查询玩家资料信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

// 单击玩家资料信息保存当前行号
void CPALLogInfo::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listUser.GetItemCount() > 0)//如果玩家资料信息不为空
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listUser.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listUser.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
	}
	else
	{
		nItem = 0;
	}
	*pResult = 0;
}

// 双击玩家资料信息进行切换
void CPALLogInfo::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listUser.GetItemCount() > 0)//如果玩家资料信息不为空
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nItem >= 0)
			{
				ShowLogInfo();//显示日志信息列表

				GetAllBigType();//获取所有大类信息
				cmbSmallType.ResetContent();//小类列表置为空

				CTime curTime = CTime::GetCurrentTime();//获取系统当前时间
				dtcStartDate.SetTime(&curTime);//开始时间设为当前时间
				dtcEndDate.SetTime(&curTime);//结束时间设为当前时间

				pageInfo=false;//玩家日志信息不能翻页
				cmbPage.ResetContent();//玩家日志信息不能翻页
				while(listResult.DeleteColumn(0)){}//清空玩家日志信息

				//OperationPAL operPAL;

			    UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
			    UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名
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

// 切换选项卡进行查询
void CPALLogInfo::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//显示用户信息界面
	}
	else
	{
		ShowLogInfo();//显示日志信息界面

		GetAllBigType();//获取所有大类信息
		cmbSmallType.ResetContent();//小类列表置为空

		CTime curTime = CTime::GetCurrentTime();//获取系统当前时间
		dtcStartDate.SetTime(&curTime);//开始时间设为当前时间
		dtcEndDate.SetTime(&curTime);//结束时间设为当前时间

		pageInfo=false;//玩家日志信息不能翻页
		cmbPage.ResetContent();//玩家日志信息不能翻页00
		while(listResult.DeleteColumn(0)){}//清空玩家日志信息

		//OperationPAL operPAL;
		UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
	    UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名
	}
	*pResult = 0;
}

//获取所有大类信息
void CPALLogInfo::GetAllBigType()
{	
	try
	{	
		CIni mIni;	
		//OperationPAL operPAL;

		CSocketData socketdata;	
		socketdata.InitCreate(1,2);//共有两个参数，服务器IP、服务器名称

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_LOG_BIGTYPE_QUERY))//发送查询日志大类信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}	
}

// 选择大类查询小类
void CPALLogInfo::OnCbnSelchangeCmbbigtype()
{
	try
	{	
		CIni mIni;	
		//OperationPAL operPAL;

		BigType = "";//日志大类
		bTypeID = 0;//日志大类ID

		GetDlgItemText(IDC_CMBBIGTYPE,BigType);//获取日志大类的名称
		if(BigType == "")//日志大类不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_BigTypeNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BigTypeID.Lookup(cmbBigType.GetCurSel()+1,bTypeID);//从CMap类的对象BigTypeID中获取日志大类ID

		CSocketData socketdata;	
		socketdata.InitCreate(1,4);//共有四个参数，服务器IP、服务器名称、日志大类ID、日志大类名称
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		
		_itoa(bTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//日志大类ID
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigType,CEnumCore::TagFormat::TLV_STRING,strlen(BigType),(unsigned char *)mIni.wcharToChar(BigType));//日志大类

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_LOG_SMALLTYPE_QUERY))//通过日志大类查询日志小类信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}	
}

// 查询日志信息
void CPALLogInfo::OnBnClickedBtnsearchlog()
{
	try
	{	
		CIni mIni;	
		//OperationPAL operPAL;

		pageInfo=false;//玩家日志信息不能翻页
		cmbPage.ResetContent();//玩家日志信息不能翻页
		while(listResult.DeleteColumn(0)){}//清空玩家日志信息

		BigType = "";//日志大类
		bTypeID = 0;//日志大类ID
		SmallType = "";//日志小类
		sTypeID = 0;//日志小类ID

		if(UserName == "")//玩家角色名不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_InputAccount"), theApp.operPAL.ReadValue("MPAL","Warn"), MB_ICONWARNING+MB_OK);
			return;
		}

		GetDlgItemText(IDC_CMBBIGTYPE,BigType);//获取日志大类的名称
		if(BigType == "")//日志大类不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_BigTypeNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		GetDlgItemText(IDC_CMBSMALLTYPE,SmallType);//获取日志小类的名称
		if(SmallType == "")//日志小类不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_SmallTypeNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BigTypeID.Lookup(cmbBigType.GetCurSel()+1,bTypeID);//从CMap类的对象BigTypeID中获取日志大类ID
		SmallTypeID.Lookup(cmbSmallType.GetCurSel()+1,sTypeID);//从CMap类的对象SmallTypeID中获取日志小类ID

		strStartTime = "";//开始时间
	    strEndTime = "";//结束时间

		CTime curTime = CTime::GetCurrentTime();

		CTime StartTime;
		dtcStartDate.GetTime(StartTime);//获取开始时间

		CTime EndTime;
		dtcEndDate.GetTime(EndTime);//获取结束时间

		if(StartTime >= curTime)//开始时间不能大于当前时间
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_StartTime"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
			return;
		}

		if(EndTime <= StartTime)//结束时间不能小于开始时间
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","LI_Warn_TimeSpan"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
			return;
		}
		strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
		strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//页数
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//页面记录数

		CSocketData socketdata;	
		socketdata.InitCreate(1,11);//共有十一个参数，服务器IP、服务器名称、角色名称、日志大类ID、日志大类名称、日志小类ID、日志小类名称、开始时间、结束时间、页数、页面记录数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
		
		_itoa(bTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//日志大类ID
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigType,CEnumCore::TagFormat::TLV_STRING,strlen(BigType),(unsigned char *)mIni.wcharToChar(BigType));//日志大类
		
		_itoa(sTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogSmallTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//日志小类ID
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LogSmallType,CEnumCore::TagFormat::TLV_STRING,strlen(SmallType),(unsigned char *)mIni.wcharToChar(SmallType));//日志小类

		socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGINTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGOUTTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//结束时间

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_LOGINFO_QUERY))//查询日志信息
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}	
}

// 翻页进行查询
void CPALLogInfo::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)
		{
			CIni mIni;	
			//OperationPAL operPAL;

			while(listResult.DeleteColumn(0)){}//清空玩家日志信息

			int index = cmbPage.GetCurSel() + 1;//页数
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//页面记录数

			CSocketData socketdata;	
			socketdata.InitCreate(1,11);//共有十一个参数，服务器IP、服务器名称、角色名称、日志大类ID、日志大类名称、日志小类ID、日志小类名称、开始时间、结束时间、页数、页面记录数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
			
			_itoa(bTypeID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//日志大类ID
			socketdata.AddTFLV(CEnumCore::TagName::PAL_LogBigType,CEnumCore::TagFormat::TLV_STRING,strlen(BigType),(unsigned char *)mIni.wcharToChar(BigType));//日志大类
			
			_itoa(sTypeID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PAL_LogSmallTypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//日志小类ID
			socketdata.AddTFLV(CEnumCore::TagName::PAL_LogSmallType,CEnumCore::TagFormat::TLV_STRING,strlen(SmallType),(unsigned char *)mIni.wcharToChar(SmallType));//日志小类

			socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGINTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//开始时间
		    socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGOUTTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//结束时间

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_LOGINFO_QUERY))//查询日志信息
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
	}	
}

//单击用户信息进行排序
void CPALLogInfo::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operPAL;
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击日志列表信息进行排序
void CPALLogInfo::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operPAL;
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// 接收返回信息
LRESULT CPALLogInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;
	//OperationPAL operPAL;
	
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operPAL.ReadValue("MPAL","Main_UI_ParseData"),theApp.operPAL.ReadValue("MPAL","ERROR"),0);		
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
			theApp.operPAL.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://查询玩家资料信息的回应
		{
			theApp.operPAL.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_LOGINFO_QUERY_RESP://查询玩家日志信息的回应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
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
	case CEnumCore::Message_Tag_ID::PAL_LOG_BIGTYPE_QUERY_RESP:
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				bTypeID = atoi((char*)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_LogBigTypeID).lpdata);//得到道具大类ID
				BigTypeID.SetAt(i,bTypeID);//将日志小类ID保存在CMap类的对象SmallTypeID中
			}
			theApp.operPAL.BuildComboxs(&socketdata,&cmbBigType);//构造日志大类列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_LOG_SMALLTYPE_QUERY_RESP:
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				sTypeID = atoi((char*)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_LogSmallTypeID).lpdata);//得到道具小类ID
				SmallTypeID.SetAt(i,sTypeID);//将日志小类ID保存在CMap类的对象SmallTypeID中
			}
			theApp.operPAL.BuildComboxs(&socketdata,&cmbSmallType);//构造日志小类列表信息
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

//显示用户信息界面
void CPALLogInfo::ShowUserInfo()
{
	tbcResult.SetCurSel(0);//显示用户资料信息界面
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSTARTTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DTPSTARTDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLENDTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DTPENDDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCHLOG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
}

//显示日志信息界面
void CPALLogInfo::ShowLogInfo()
{
	tbcResult.SetCurSel(1);//显示日志信息界面
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_SHOW);	
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSTARTTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPSTARTDATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLENDTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DTPENDDATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNSEARCHLOG)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
}

//关闭对话框
void CPALLogInfo::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// 关闭对话框
void CPALLogInfo::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!BigTypeID.IsEmpty())
	{
		BigTypeID.RemoveAll();
	}
	if(!SmallTypeID.IsEmpty())
	{
		SmallTypeID.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
