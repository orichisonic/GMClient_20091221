// PALGuildInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALGuildInfo.h"
#include ".\palguildinfo.h"


// CPALGuildInfo 对话框

IMPLEMENT_DYNAMIC(CPALGuildInfo, CDialog)
CPALGuildInfo::CPALGuildInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CPALGuildInfo::IDD, pParent)
{
}

CPALGuildInfo::~CPALGuildInfo()
{
}

void CPALGuildInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTGUILD, listGuild);
	DDX_Control(pDX, IDC_LISTMEMBER, listMember);
}


BEGIN_MESSAGE_MAP(CPALGuildInfo, CDialog)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTGUILD, OnNMClickListguild)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTGUILD, OnNMDblclkListguild)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTGUILD, OnLvnColumnclickListguild)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTMEMBER, OnLvnColumnclickListmember)
END_MESSAGE_MAP()


// 初始化对话框
BOOL CPALGuildInfo::OnInitDialog()
{
	CDialog::OnInitDialog();	
	InitUI();// 初始化显示字符			

	nGuildItem = 0;
	pageInfo = false;// 判断是否需要翻页
	ServerIP = "";// 游戏服务器IP		
	GuildName= "";

	SetProp(listGuild.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listGuild.GetSafeHwnd(),"排序顺序",(HANDLE)1);

	SetProp(listMember.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listMember.GetSafeHwnd(),"排序顺序",(HANDLE)1);

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

	if(listGuild.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGuild.MoveWindow(newRect);//设置好listGuild的位置
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

	if(listMember.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMember.MoveWindow(newRect);//设置好listMember的位置
	}

	ShowGuildInfo();

	//OperationPAL operPAL;
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//初始建立对话框

	if(theApp.operPAL.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}

// 初始化显示字符
void CPALGuildInfo::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","GM_UI_GuildInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLGUILD,theApp.operPAL.ReadValue("MPAL","GM_UI_Guild"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Cancel"));

	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","GM_UI_tpgGuildInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","GM_UI_tpgGuildMember"));
}

//处理快捷键响应函数
BOOL CPALGuildInfo::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operPAL;
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listGuild.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listGuild);				
				}
				else if(pMsg->hwnd == listMember.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listMember);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listGuild.m_hWnd)
				{
					for(int i=0; i<listGuild.GetItemCount(); i++)
					{
					    listGuild.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listGuild.EnsureVisible(i,false);
					}
				}
				else if(pMsg->hwnd == listMember.m_hWnd)
				{
					for(int i=0; i<listMember.GetItemCount(); i++)
					{
					    listMember.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listMember.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

// 自动改变大小
void CPALGuildInfo::OnSize(UINT nType, int cx, int cy)
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

	if(listGuild.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGuild.MoveWindow(newRect);//设置好listGuild的位置
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listMember.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMember.MoveWindow(newRect);//设置好listMember的位置
	}
}

//设置背景颜色
HBRUSH CPALGuildInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询资料信息
void CPALGuildInfo::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;	

		nGuildItem = 0;
		pageInfo = false;//列表不能翻页		
		cmbPage.ResetContent();//清除列表翻页的复选框
		while(listGuild.DeleteColumn(0)){}//清除列表中的所有内容
		while(listMember.DeleteColumn(0)){}//清除列表中的所有内容

		ShowGuildInfo();

		UpdateData(true);			

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//查询第一页的信息
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//每页显示50条记录

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_SelectServer"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITGUILD,GuildName);//获取公会名
		if(GuildName=="")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_GUILDNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_GUILDBASEINFO))//发送查询公告基本资料信息的请求
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

// 单击公会资料信息保存当前行号
void CPALGuildInfo::OnNMClickListguild(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listGuild.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listGuild.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nGuildItem = listGuild.SubItemHitTest(&lvinfo);//保存在列表中选中的行号
		}
		else
		{
			nGuildItem = 0;
		}
	}
	else
	{
		nGuildItem=-1;
	}
	*pResult = 0;
}

// 双击公会资料信息进行操作
void CPALGuildInfo::OnNMDblclkListguild(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel()==0)
	{
		if(listGuild.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listGuild.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nGuildItem = listGuild.SubItemHitTest(&lvinfo);//保存在列表中选中的行号

			if(nGuildItem>=0)
			{
				tbcResult.SetCurSel(1);
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowGuildMember(SW_SHOW);

				//OperationPAL operPAL;
				GuildName = theApp.operPAL.GetValueByColName(&listGuild, nGuildItem, theApp.operPAL.ReadValue("MPAL","PAL_GUILDNAME"));//获取公会名称

				GuildMemberList();
			}
		}
		else
		{
			nGuildItem = 0;
		}		
	}
	*pResult = 0;
}

// 切换选项卡进行操作
void CPALGuildInfo::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;
	//OperationPAL operPAL;

	if(tbcResult.GetCurSel()==0)//查询公会基本信息
	{
		ShowGuildInfo();
	}	
	else
	{
		if((listGuild.GetItemCount() > 0) && (nGuildItem >= 0))
		{
			GuildName = theApp.operPAL.GetValueByColName(&listGuild, nGuildItem, theApp.operPAL.ReadValue("MPAL","PAL_GUILDNAME"));//获取公会名称

			if(tbcResult.GetCurSel() == 1)//显示公会成员列表
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowGuildMember(SW_SHOW);

				GuildMemberList();
			}
		}
		else
		{
			if(tbcResult.GetCurSel() == 1)//显示公会成员列表
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowGuildMember(SW_SHOW);
			}
		}
	}
	*pResult = 0;
}

// 查询公会成员列表
void CPALGuildInfo::GuildMemberList()
{
	//OperationPAL operPAL;
	try
	{				
		CIni mIni;
		
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listMember.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name,公会名称、页数、每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_GUILDMEMBERLIST))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_UserInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

// 翻页进行查询
void CPALGuildInfo::OnCbnSelchangeCmbpage()
{
	//OperationPAL operPAL;
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listMember.DeleteColumn(0)){}
			
			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//每页显示50条记录
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_GUILDMEMBERLIST);
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_Page"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

// 接收返回信息
LRESULT CPALGuildInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	//OperationPAL operPAL;
	CIni mIni;

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
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,sIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operPAL.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_GUILDBASEINFO_RESP://查询公会信息的回应
		{
			ShowGuildInfo();
			theApp.operPAL.BuildDataTable(&socketdata,&listGuild,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_GUILDMEMBERLIST_RESP://查询公会成员列表的回应
		{
			if(pageInfo)
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listMember,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listMember,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页				
					cmbPage.ResetContent();//清空页数复选框
					while(listMember.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
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
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//单击用户资料信息的列名进行排序
void CPALGuildInfo::OnLvnColumnclickListguild(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listGuild,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CPALGuildInfo::OnLvnColumnclickListmember(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listMember,pNMHDR,pResult);
}

// 关闭对话框
void CPALGuildInfo::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITGUILD,"");
	ShowGuildInfo();
}

// 关闭对话框
void CPALGuildInfo::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// 显示公会信息
void CPALGuildInfo::ShowGuildInfo()
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_SHOW);
	ShowGuildMember(SW_HIDE);
}

// 显示修改公会成员信息
void CPALGuildInfo::ShowGuildMember(int m_cmdShow)
{
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTMEMBER)->ShowWindow(m_cmdShow);
}