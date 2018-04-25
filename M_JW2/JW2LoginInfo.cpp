// CJW2LoginInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2LoginInfo.h"
#include ".\JW2LoginInfo.h"


// CJW2KickPlayer 对话框

IMPLEMENT_DYNAMIC(CJW2LoginInfo, CDialog)
CJW2LoginInfo::CJW2LoginInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2LoginInfo::IDD, pParent)
{
}

CJW2LoginInfo::~CJW2LoginInfo()
{
}

void CJW2LoginInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBKPPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPKPPAGE, GrpPage);

	DDX_Control(pDX, IDC_DATETIMELOGIN, dtcLoginDate);
	DDX_Control(pDX, IDC_DATETIMELOGOUT, dtcLogoutDate);

	DDX_Control(pDX, IDC_CHECKBYACCOUNT, m_ckAccount);
	DDX_Control(pDX, IDC_CHECKBYIP, m_ckIP);
}


BEGIN_MESSAGE_MAP(CJW2LoginInfo, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBKPPAGE, OnCbnSelchangeCmbkppage)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECKBYACCOUNT, OnBnClickedCheckbyaccount)
	ON_BN_CLICKED(IDC_CHECKBYIP, OnBnClickedCheckbyip)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CJW2LoginInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符	

	nItem = -1;
	pageInfo = false;//初始化一些私有变量

	CRect rs;
	GetClientRect(rs);//获取对话框的大小信息

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

		listResult.MoveWindow(newRect);//设置好listUser的位置
	}

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//初始建立对话框

	theApp.operJW2.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//发送查询请求

	return TRUE;
}

// 初始化显示字符
void CJW2LoginInfo::InitUI()
{
	//OperationJW2 theApp.operJW2;

	SetWindowText(theApp.operJW2.ReadValue("MJW2","LI_UI_LoginInfo"));


	SetDlgItemText(IDC_GRPSEARCH,theApp.operJW2.ReadValue("MJW2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operJW2.ReadValue("MJW2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operJW2.ReadValue("MJW2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operJW2.ReadValue("MJW2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operJW2.ReadValue("MJW2","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLHINT,theApp.operJW2.ReadValue("MJW2","KP_UI_KickHint"));
	GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
	m_ckAccount.SetCheck(1);
	m_ckIP.SetCheck(0);
}

// 自动改变大小
void CJW2LoginInfo::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CJW2LoginInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CJW2LoginInfo::OnBnClickedUisearch()
{
	try
	{
		//OperationJW2 theApp.operJW2;

		nItem = -1;//玩家资料列表没有选定项
		pageInfo = false;//玩家资料列表不能翻页	
		cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			


		GetDlgItemText(IDC_CMBUISERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		if(m_ckIP.GetCheck()==0)
		{
			GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//获取玩家帐号
			GetDlgItemText(IDC_EDITUINICK,UserNick);//获取玩家昵称
			if((UserName == "") && (UserNick == ""))//玩家帐号和玩家昵称不能同时为空
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_InputAccount"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}	
		}
		

	    LoginInfo();
	}
	catch(...)
	{
	}
}

// 查询玩家登陆信息
void CJW2LoginInfo::LoginInfo()
{
	try
	{
		CIni mIni;	

		int index = theApp.operJW2.ReadIntValue("MJW2","index");//查询第一页的信息
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageInfo = false;//玩家资料列表不能翻页		
		cmbPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容		

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
	
		if(m_ckIP.GetCheck()==1)
		{
			CString JW2_IP;
			GetDlgItemText(IDC_IPADDRESSCHECK,JW2_IP);
			socketdata.AddTFLV(CEnumCore::TagName::JW2_IP,CEnumCore::TagFormat::TLV_STRING,strlen(JW2_IP),(unsigned char *)mIni.wcharToChar(JW2_IP));//玩家帐号

		}
		else
		{
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
		}

	
		CTime LoginDate,LogoutDate;
		dtcLoginDate.GetTime(LoginDate);
		dtcLogoutDate.GetTime(LogoutDate);

		CTime LoginDT=CTime::CTime(LoginDate.GetYear(),LoginDate.GetMonth(),LoginDate.GetDay(),0,0,0);
		CTime LogoutDT=CTime::CTime(LogoutDate.GetYear(),LogoutDate.GetMonth(),LogoutDate.GetDay(),0,0,0);

		CString strLoginTime,strLogoutTime;
		strLoginTime=LoginDT.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
		strLogoutTime=LogoutDT.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLoginTime),(unsigned char *)mIni.wcharToChar(strLoginTime));

		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLogoutTime),(unsigned char *)mIni.wcharToChar(strLogoutTime));


		
		
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数



		
		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_LOGINOUT_QUERY);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_UserInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// 翻页进行查询
void CJW2LoginInfo::OnCbnSelchangeCmbkppage()
{	
	try
	{
		if(pageInfo)//如果可以翻页的话
		{	
			CIni mIni;
			//OperationJW2 theApp.operJW2;
			
			char strInt[10];
			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//每页显示50条记录

			while(listResult.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			if(m_ckIP.GetCheck()==1)
			{
				CString JW2_IP;
				GetDlgItemText(IDC_IPADDRESSCHECK,JW2_IP);
				socketdata.AddTFLV(CEnumCore::TagName::JW2_IP,CEnumCore::TagFormat::TLV_STRING,strlen(JW2_IP),(unsigned char *)mIni.wcharToChar(JW2_IP));//玩家帐号

			}
			else
			{
				socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
				socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			}

			CTime LoginDate,LogoutDate;
			dtcLoginDate.GetTime(LoginDate);
			dtcLogoutDate.GetTime(LogoutDate);

			CTime LoginDT=CTime::CTime(LoginDate.GetYear(),LoginDate.GetMonth(),LoginDate.GetDay(),0,0,0);
			CTime LogoutDT=CTime::CTime(LogoutDate.GetYear(),LogoutDate.GetMonth(),LogoutDate.GetDay(),0,0,0);

			CString strLoginTime,strLogoutTime;
			strLoginTime=LoginDT.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
			strLogoutTime=LogoutDT.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

			socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLoginTime),(unsigned char *)mIni.wcharToChar(strLoginTime));

			socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strLogoutTime),(unsigned char *)mIni.wcharToChar(strLogoutTime));




			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);



						

			int midlength = socketdata.EnBody();
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_LOGINOUT_QUERY);//当前的状态为发送查询请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 双击玩家资料信息进行踢人
void CJW2LoginInfo::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	*pResult = 0;
}

// 接收返回信息
LRESULT CJW2LoginInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	//OperationJW2 theApp.operJW2;
	CIni mIni;

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Receive");//当前的状态为接收到了返回信息

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
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,sIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operJW2.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_LOGINOUT_QUERY_RESP://查询玩家登陆信息的回应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{					
					nItem = -1;//不能选中某一行
					pageInfo = false;//不能翻页
					cmbPage.ResetContent();//清空页数复选框
					while(listResult.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//在复选框中构造页数信息
					}
					cmbPage.SetCurSel(0);//在复选框中选中第一页
					if(pageCount == 1)
					{
						pageInfo = false;//只有一页数据，不能翻页
					}
					else
					{
						pageInfo = true;//有多页数据，可以翻页
					}
				}				
			}
		}
		break;
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

// 关闭对话框
void CJW2LoginInfo::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// 关闭对话框
void CJW2LoginInfo::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}




//选择通过帐号和昵称查询
void CJW2LoginInfo::OnBnClickedCheckbyaccount()
{
	switch(m_ckAccount.GetCheck())
	{
	case 0:
		{
			GetDlgItem(IDC_EDITUIACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITUINICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUINICK)->ShowWindow(SW_HIDE);

			/////////隐藏/////////////////////////
			GetDlgItem(IDC_LBLIP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_SHOW);
			
			m_ckIP.SetCheck(1);
		}
		break;
	case 1:
		{
			///////////显示////////////////////////////////////
			GetDlgItem(IDC_EDITUIACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDITUINICK)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUINICK)->ShowWindow(SW_SHOW);

			/////////隐藏/////////////////////////
			GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_HIDE);

			m_ckIP.SetCheck(0);
		}
		break;
	default:
		break;
	}
	
	// TODO: 在此添加控件通知处理程序代码
}

void CJW2LoginInfo::OnBnClickedCheckbyip()
{
	switch(m_ckIP.GetCheck())
	{
	case 0:
		{
			///////////显示////////////////////////////////////
			GetDlgItem(IDC_EDITUIACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDITUINICK)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIACCOUNT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUINICK)->ShowWindow(SW_SHOW);

			/////////隐藏/////////////////////////
			GetDlgItem(IDC_LBLIP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_HIDE);
			

			m_ckAccount.SetCheck(1);
		}
		break;
	case 1:
		{
			GetDlgItem(IDC_EDITUIACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITUINICK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUINICK)->ShowWindow(SW_HIDE);

			/////////隐藏/////////////////////////
			GetDlgItem(IDC_LBLIP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_IPADDRESSCHECK)->ShowWindow(SW_SHOW);

			m_ckAccount.SetCheck(0);
		}
		break;
	default:
		break;
	}
}
