// WAAccountLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "M_WA.h"
#include "AccountLog.h"
#include ".\accountlog.h"


// CWAAccountLogin 对话框

IMPLEMENT_DYNAMIC(CWAAccountLogin, CDialog)
CWAAccountLogin::CWAAccountLogin(CWnd* pParent /*=NULL*/)
: CDialog(CWAAccountLogin::IDD, pParent)
{
	//unsigned long long temp=0;
}

CWAAccountLogin::~CWAAccountLogin()
{
}

void CWAAccountLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_CHECKBYACCOUNT, checkByAccount);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartTime);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndTime);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_CHECKBYIP, checkByIP);
	DDX_Control(pDX, IDC_IPADDRESSCHECK, IPACtrl_UserIP);
}

BEGIN_MESSAGE_MAP(CWAAccountLogin, CDialog)
	ON_BN_CLICKED(IDC_CHECKBYACCOUNT, OnBnClickedCheckbyaccount)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECKBYIP, OnBnClickedCheckbyip)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
END_MESSAGE_MAP()


// 初始化对话框
BOOL CWAAccountLogin::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符
	ServerName = "";
	ServerIP = "";
	UserNick = "";
	UserIP = "";//初始化一些私有变量
	checkType = 1;//通过账号查询
	checkByAccount.SetCheck(1);
	ShowCheckByAccount();//显示通过帐号查询的信息

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

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//获取GrpPage的大小信息
		grpPHeight = srcRect.bottom - srcRect.top;//得到GrpPage的高度信息
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}
	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		listResult.MoveWindow(newRect);//设置好listResult的位置		
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
void CWAAccountLogin::InitUI()
{
	//OperationWA operWA;
	SetWindowText(theApp.operWA.ReadValue("MWA","AL_UI_AccountLoginLog"));
	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","AL_UI_UserNick"));
	SetDlgItemText(IDC_LBLIP,theApp.operWA.ReadValue("MWA","AL_UI_UserIP"));
	SetDlgItemText(IDC_CHECKBYACCOUNT,theApp.operWA.ReadValue("MWA","AL_UI_CheckByAccount"));
	SetDlgItemText(IDC_CHECKBYIP,theApp.operWA.ReadValue("MWA","AL_UI_CheckByIP"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operWA.ReadValue("MWA","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operWA.ReadValue("MWA","NI_UI_EndTime"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));
}

//处理快捷键响应函数
BOOL CWAAccountLogin::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
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
void CWAAccountLogin::OnSize(UINT nType, int cx, int cy)
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

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		listResult.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CWAAccountLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	return CreateSolidBrush(backColor);
}

// 设置通过帐号来查询
void CWAAccountLogin::OnBnClickedCheckbyaccount()
{
	if(checkByAccount.GetCheck() == 1)
	{
		checkByIP.SetCheck(0);
		ShowCheckByAccount();
	}
	else
	{
		checkByIP.SetCheck(1);
		ShowCheckByIP();
	}
}

// 设置通过IP来查询
void CWAAccountLogin::OnBnClickedCheckbyip()
{
	if(checkByIP.GetCheck() == 1)
	{
		checkByAccount.SetCheck(0);
		ShowCheckByIP();
	}
	else
	{
		checkByAccount.SetCheck(1);
		ShowCheckByAccount();
	}
}

// 查询玩家登录日志信息
void CWAAccountLogin::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		int index = theApp.operWA.ReadIntValue("MWA","index");//查询第一页的信息
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			
		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		if(checkByAccount.GetCheck() == 1) 
			checkType = 1;
		else 
			checkType = 2;

		if(checkType == 1)//通过账号查询
		{
			GetDlgItemText(IDC_EDITACCOUNT,UserNick);//获取玩家帐号
			if(UserNick == "")//玩家帐号不能为空
			{
				MessageBox(theApp.operWA.ReadValue("MWA","AL_Warn_InputNotNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
		}
		else//通过IP查询
		{
			GetDlgItemText(IDC_IPADDRESSCHECK,UserIP);//获取玩家IP
			if(!strcmp(UserIP,"0.0.0.0"))//玩家IP不能为空
			{
				MessageBox(theApp.operWA.ReadValue("MWA","AL_Warn_InputNotNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
		}		

		CTime sTime;
		dtcStartTime.GetTime(sTime);//获取开始时间
		CTime eTime;
		dtcEndTime.GetTime(eTime);//获取结束时间
		BeginTime = sTime.Format("%Y-%m-%d %H:%M:%S");//获取开始时间
		EndTime = eTime.Format("%Y-%m-%d %H:%M:%S");//获取结束时间

		CSocketData socketdata;	
		socketdata.InitCreate(1,12);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::WA_LoginIP,CEnumCore::TagFormat::TLV_STRING,strlen(UserIP),(unsigned char *)mIni.wcharToChar(UserIP));//玩家IP
		
		socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(BeginTime),(unsigned char*)mIni.wcharToChar(BeginTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(EndTime),(unsigned char*)mIni.wcharToChar(EndTime));//结束时间

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数
		
		int midlength=socketdata.EnBody();
		if(checkType == 1)
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_LoginLogout);//玩家登陆/登出日志			
		else
			theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_LoginLogoutByIP);//发送查询玩家登陆记录日志的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

// 翻页进行查询
void CWAAccountLogin::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,12);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];
			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::WA_LoginIP,CEnumCore::TagFormat::TLV_STRING,strlen(UserIP),(unsigned char *)mIni.wcharToChar(UserIP));//玩家IP
		
			socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(BeginTime),(unsigned char*)mIni.wcharToChar(BeginTime));//开始时间
			socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(EndTime),(unsigned char*)mIni.wcharToChar(EndTime));//结束时间

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数
			
			midlength=socketdata.EnBody();
			if(checkType == 1)
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_LoginLogout);//玩家登陆/登出日志			
			else
				theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Query_LoginLogoutByIP);//发送查询玩家登陆记录日志的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Page"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

// 接收返回信息
LRESULT CWAAccountLogin::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operWA.ReadValue("MWA","Main_UI_ParseData"),theApp.operWA.ReadValue("MWA","ERROR"),0);		
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

			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	default://查询玩家登录日志信息回应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

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
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);

	socketdata.Destroy();
	return false;
}

//单击用户资料信息的列名进行排序
void CWAAccountLogin::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operWA.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CWAAccountLogin::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_IPADDRESSCHECK,"");
	CTime curTime = CTime::GetCurrentTime();//获取当前时间
	dtcStartTime.SetTime(&curTime);
	dtcEndTime.SetTime(&curTime);
	ShowCheckByAccount();
}

// 关闭对话框
void CWAAccountLogin::OnClose()
{
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//显示通过帐号查询的信息
void CWAAccountLogin::ShowCheckByAccount(void)
{
	GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_IPADDRESSCHECK,"");
}

//显示通过IP查询的信息
void CWAAccountLogin::ShowCheckByIP(void)
{
	GetDlgItem(IDC_LBLIP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_HIDE);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_IPADDRESSCHECK,"");
}