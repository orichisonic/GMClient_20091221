// PALRoleDel.cpp : 实现文件
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALRoleDel.h"
#include ".\PALRoleDel.h"


// CPALRoleDel 对话框

IMPLEMENT_DYNAMIC(CPALRoleDel, CDialog)
CPALRoleDel::CPALRoleDel(CWnd* pParent /*=NULL*/)
	: CDialog(CPALRoleDel::IDD, pParent)
{
}

CPALRoleDel::~CPALRoleDel()
{
}

void CPALRoleDel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartTime);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndTime);
	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
}


BEGIN_MESSAGE_MAP(CPALRoleDel, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	//ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	//ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_CBN_SELCHANGE(IDC_CMBTYPE, OnCbnSelchangeCmbtype)
END_MESSAGE_MAP()


// 初始化对话框
BOOL CPALRoleDel::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符

	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";
	UserID = 0;//初始化一些私有变量

	ShowUserInfo();//显示用户资料信息

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
void CPALRoleDel::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","BI_UI_MailBoxInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));

	tbcResult.InsertItem(0,"角色删除记录");
}

//处理快捷键响应函数
BOOL CPALRoleDel::PreTranslateMessage(MSG* pMsg)
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
				else if(pMsg->hwnd==listMailDetail.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listMailDetail);
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
				else if(pMsg->hwnd==listMailDetail.m_hWnd)
				{
					for(int i=0; i<listMailDetail.GetItemCount(); i++)
					{
						listMailDetail.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listMailDetail.EnsureVisible(i,false);
					}

				}
			}
		}		
	}
	return FALSE;
}

// 自动改变大小
void CPALRoleDel::OnSize(UINT nType, int cx, int cy)
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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
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
	if(listMailDetail.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMailDetail.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CPALRoleDel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CPALRoleDel::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;

		ShowUserInfo();

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		strStartTime = "";//开始时间
		strEndTime = "";//结束时间
		CTime curTime = CTime::GetCurrentTime();
		CTime StartTime;
		dtcStartTime.GetTime(StartTime);//获取开始时间
		CTime EndTime;
		dtcEndTime.GetTime(EndTime);//获取结束时间

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
		socketdata.InitCreate(1,20);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGINTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGOUTTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//结束时间

	
		int iType=cmbType.GetCurSel();

		_itoa(iType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MALLTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_ROLEDEL_QUERY))//发送查询玩家资料信息的请求
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

// 单击用户列表保存当前行号
void CPALRoleDel::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() != 0)
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
	}
	*pResult = 0;
}
// 单击邮箱列表保存当前行号
void CPALRoleDel::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 1)
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nMailItem = listResult.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
		}
		else
		{
			nMailItem = 0;
		}
	}
	*pResult = 0;
}
// 双击玩家资料信息进行查询
void CPALRoleDel::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() != 0)
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
				tbcResult.SetCurSel(1);
				ShowMailInfo();				

				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				//OperationPAL operPAL;
				UserID = atoi(theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLEID")));//保存选中的玩家ID
				UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
			    UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名
			}
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 切换选项卡进行查询
void CPALRoleDel::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//显示用户资料信息
	}
	*pResult = 0;
}


// 翻页进行查询
void CPALRoleDel::OnCbnSelchangeCmbpage()
{
	//OperationPAL operPAL;
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;
		
			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//每页显示50条记录

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,15);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGINTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//开始时间
		    socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGOUTTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//结束时间

			_itoa(UserID,strInt,10);
		    socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLEID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

			int iType=cmbType.GetCurSel();

			_itoa(iType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PAL_MALLTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			
			midlength=socketdata.EnBody();
			if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_ROLEDEL_QUERY))//发送查询玩家邮箱信息的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		       	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_Page"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

// 接收返回信息
LRESULT CPALRoleDel::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::PAL_ROLEDEL_QUERY_RESP://查询玩家邮箱信息回应
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
	case CEnumCore::Message_Tag_ID::PAL_CHECKMAILBOX_DETAIL_RESP://查询玩家邮件附件回应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listMailDetail,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listMailDetail,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
					cmbPage.ResetContent();
					while(listMailDetail.DeleteColumn(0)){}
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
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//单击用户资料信息的列名进行排序
void CPALRoleDel::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CPALRoleDel::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CPALRoleDel::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	CTime curTime = CTime::GetCurrentTime();//获取当前时间
	dtcStartTime.SetTime(&curTime);
	dtcEndTime.SetTime(&curTime);
	ShowUserInfo();
}

// 关闭对话框
void CPALRoleDel::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// 显示角色资料信息
void CPALRoleDel::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
	InitCmdType();
}

// 显示邮箱信息
void CPALRoleDel::ShowMailInfo(void)
{
	tbcResult.SetCurSel(1);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTMAILDETAIL)->ShowWindow(SW_HIDE);
}
// 显示邮件附件界面
void CPALRoleDel::ShowMailDetail(void)
{
	tbcResult.SetCurSel(2);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTMAILDETAIL)->ShowWindow(SW_SHOW);

}




void CPALRoleDel::InitCmdType(void)
{
	cmbType.ResetContent();
	cmbType.AddString("当前");
	cmbType.AddString("历史");
	cmbType.SetCurSel(0);
}

void CPALRoleDel::OnCbnSelchangeCmbtype()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		strStartTime = "";//开始时间
		strEndTime = "";//结束时间
		CTime curTime = CTime::GetCurrentTime();
		CTime StartTime;
		dtcStartTime.GetTime(StartTime);//获取开始时间
		CTime EndTime;
		dtcEndTime.GetTime(EndTime);//获取结束时间

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
		socketdata.InitCreate(1,20);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGINTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//开始时间
		socketdata.AddTFLV(CEnumCore::TagName::PAL_LOGOUTTIME,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//结束时间


		int iType=cmbType.GetCurSel();

		_itoa(iType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MALLTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_ROLEDEL_QUERY))//发送查询玩家资料信息的请求
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
