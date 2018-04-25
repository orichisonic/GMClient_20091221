// GMOperationLog.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GM.h"
#include "GMOperationLog.h"
#include ".\gmoperationlog.h"


// CGMOperationLog 对话框

IMPLEMENT_DYNAMIC(CGMOperationLog, CDialog)
CGMOperationLog::CGMOperationLog(CWnd* pParent /*=NULL*/)
	: CDialog(CGMOperationLog::IDD, pParent)
{
}

CGMOperationLog::~CGMOperationLog()
{
}

void CGMOperationLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBGAMENAME, cmbGame);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartTime);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndTime);
	DDX_Control(pDX, IDC_CMBREALNAME, cmbRealName);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
}


BEGIN_MESSAGE_MAP(CGMOperationLog, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBGAMENAME, OnCbnSelchangeCmbgamename)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
END_MESSAGE_MAP()


// 初始化对话框
BOOL CGMOperationLog::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符

	GameName = "";
	ServerName = "";
	ServerIP = "";
	UserName = "";
	UserID = 0;
	strStartTime = "";
	strEndTime = "";//初始化一些私有变量

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
	//OperationGM operGM;
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Create");//当前的状态为初始建立对话框

	QueryUserList();

	return TRUE;
}

// 初始化显示字符
void CGMOperationLog::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","OL_UI_GMOperLog"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGM.ReadValue("MGM","OL_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLGAMENAME,theApp.operGM.ReadValue("MGM","OL_UI_LblGame"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGM.ReadValue("MGM","OL_UI_LblServer"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operGM.ReadValue("MGM","OL_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operGM.ReadValue("MGM","OL_UI_EndTime"));
	SetDlgItemText(IDC_LBLREALNAME,theApp.operGM.ReadValue("MGM","OL_UI_GMRealName"));
	SetDlgItemText(IDSEARCH,theApp.operGM.ReadValue("MGM","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGM.ReadValue("MGM","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operGM.ReadValue("MGM","UM_UI_Page"));
}

//处理快捷键响应函数
BOOL CGMOperationLog::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operGM.CopyListInfo(&listResult);
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
void CGMOperationLog::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CGMOperationLog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//获取所有的用户名称
void CGMOperationLog::QueryUserList()
{
	//OperationGM operGM;	
	try
	{		
		CIni mIni;

		int index = 0;
		int iPageSize = 0;

		cmbRealName.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,3);//共有3个参数，页数、每页的记录条数
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_QUERY_ALL))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","IM_Error_SearchItemType"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

//获取所有的游戏名称
void CGMOperationLog::QueryGameList()
{
	//OperationGM operGM;	
	try
	{		
		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");

		cmbGame.ResetContent();
		cmbServer.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,3);//共有3个参数，页数、每页的记录条数
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::GAME_ADMIN,CEnumCore::ServiceKey::GAME_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","IM_Error_SearchItemType"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

//通过游戏名称查询相应的游戏服务器IP
void CGMOperationLog::OnCbnSelchangeCmbgamename()
{
	//OperationGM operGM;	
	try
	{		
		if(cmbGame.GetCurSel() == 0)
		{
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			ServerList.SetAt(0,0);
			cmbServer.ResetContent();
			cmbServer.AddString(theApp.operGM.ReadValue("MGM","OL_UI_AllCity"));//获取相应的游戏服务器
			cmbServer.SetCurSel(0);
			return;
		}

		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");

		cmbServer.ResetContent();

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//获取游戏名称
		if(GameName == "")//游戏名称不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","OL_Warn_GameNameNull"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel(),GameID);//从CMap类的对象GameList中获取游戏ID

		CSocketData socketdata;	
		socketdata.InitCreate(1,5);//共有六个参数，服务器IP、服务器Name、玩家昵称、背包类型,页数、每页的记录条数
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//游戏名称
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::SERVERINFO_IP_ALL_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","IM_Error_SearchItemType"),theApp.operGM.ReadValue("MGM","Error"),0);
	}	
}

// 查询GM操作记录日志信息
void CGMOperationLog::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		int index = theApp.operGM.ReadIntValue("MGM","index");//查询第一页的信息
		int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");//每页显示50条记录

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel(),ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_CMBGAMENAME,GameName);//获取游戏名
		if(GameName == "")//游戏名不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UIC_Warn_SelectServer"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GameList.Lookup(cmbGame.GetCurSel(),GameID);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_CMBREALNAME,UserName);//获取GM真实姓名
		if(UserName == "")//玩家帐号不能为空
		{
			MessageBox(theApp.operGM.ReadValue("MGM","OL_Warn_InputNotNull"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		UserList.Lookup(cmbRealName.GetCurSel()+1,UserID);//从CMap类的对象UserList中获取用户ID

		strStartTime = "";//开始时间
	    strEndTime = "";//结束时间
		CTime curTime = CTime::GetCurrentTime();
		CTime StartTime;
		dtcStartTime.GetTime(StartTime);//获取开始时间
		CTime EndTime;
		dtcEndTime.GetTime(EndTime);//获取结束时间

		if(StartTime >= curTime)//开始时间不能大于当前时间
		{
			MessageBox(theApp.operGM.ReadValue("MGM","LI_Warn_StartTime"),theApp.operGM.ReadValue("MGM","Warn"),0);
			return;
		}
		if(EndTime <= StartTime)//结束时间不能小于开始时间
		{
			MessageBox(theApp.operGM.ReadValue("MGM","LI_Warn_TimeSpan"),theApp.operGM.ReadValue("MGM","Warn"),0);
			return;
		}
		strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//设置开始时间
		strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//设置结束时间

	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];
	

		_itoa(GameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//游戏名称
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		if(cmbServer.GetCurSel() == 0)
		{
			ServerIP = "ALL";
		}
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID
		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//用户真实姓名
		
		socketdata.AddTFLV(CEnumCore::TagName::BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//结束时间

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength=socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::GMTOOLS_OperateLog_Query))//发送查询GM操作记录日志信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		    dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}		
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

// 翻页进行查询
void CGMOperationLog::OnCbnSelchangeCmbpage()
{
	//OperationGM operGM;
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;
		
			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operGM.ReadIntValue("MGM","pageSize");//每页显示50条记录

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];

			_itoa(GameID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//游戏ID		
			socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(GameName),(unsigned char *)mIni.wcharToChar(GameName));//游戏名称
			socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_City,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_IP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			
			_itoa(UserID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID
			socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//用户真实姓名
			
			socketdata.AddTFLV(CEnumCore::TagName::BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//开始时间
			socketdata.AddTFLV(CEnumCore::TagName::EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//结束时间

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			midlength=socketdata.EnBody();
			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::GMTOOLS_OperateLog_Query))//发送查询GM操作记录日志信息的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGM.ReadValue("MGM","UIC_Error_Page"),theApp.operGM.ReadValue("MGM","Error"),0);
	}
}

// 接收返回信息
LRESULT CGMOperationLog::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch(theApp.m_tag_id)
	{
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP://查询用户信息的回应
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int UserID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::User_ID).lpdata);//得到用户ID
				UserList.SetAt(i,UserID);//将用户ID保存在CMap类的对象UserList中
			}

			theApp.operGM.BuildComboxUser(&socketdata,&cmbRealName);//构造玩家姓名列表信息
			QueryGameList();
		}
		break;
	case CEnumCore::Message_Tag_ID::GAME_QUERY_RESP://查询游戏信息的回应
		{
			if(!GameList.IsEmpty())
			{
				GameList.RemoveAll();
			}
			GameList.SetAt(0,0);
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int GameID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::GameID).lpdata);//得到游戏ID
				GameList.SetAt(i,GameID);//将游戏ID保存在CMap类的对象UserList中
			}

			theApp.operGM.BuildComboxGame(&socketdata,&cmbGame);//构造游戏名称列表信息

			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			ServerList.SetAt(0,0);
			cmbServer.ResetContent();
			cmbServer.AddString(theApp.operGM.ReadValue("MGM","OL_UI_AllCity"));//获取相应的游戏服务器
			cmbServer.SetCurSel(0);

			::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	        ::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
		break;
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_ALL_QUERY_RESP://查询游戏服务器IP的回应
		{
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			ServerList.SetAt(0,0);
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到游戏服务器IP
				ServerList.SetAt(i,ServerIP);//将游戏服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operGM.BuildComboxCity(&socketdata,&cmbServer);//构造游戏服务器列表信息

			::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	        ::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
		break;
	case CEnumCore::Message_Tag_ID::GMTOOLS_OperateLog_Query_RESP://查询GM操作日志信息回应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operGM.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operGM.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

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
			::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	        ::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		}
		break;
	default:
		break;
	}	
	return false;
}

// 关闭对话框
void CGMOperationLog::OnBnClickedCancel()
{
	CTime curTime = CTime::GetCurrentTime();//获取当前时间
	dtcStartTime.SetTime(&curTime);
	dtcEndTime.SetTime(&curTime);
	cmbServer.SetCurSel(0);
	cmbGame.SetCurSel(0);
	cmbRealName.SetCurSel(0);
}

// 关闭对话框
void CGMOperationLog::OnClose()
{
	if(!GameList.IsEmpty())
	{
		GameList.RemoveAll();
	}
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!UserList.IsEmpty())
	{
		UserList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}