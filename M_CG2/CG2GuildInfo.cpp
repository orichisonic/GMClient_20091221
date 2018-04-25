// CG2GuildInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2GuildInfo.h"
#include ".\CG2GuildInfo.h"


// CCG2GuildInfo 对话框

IMPLEMENT_DYNAMIC(CCG2GuildInfo, CDialog)
CCG2GuildInfo::CCG2GuildInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2GuildInfo::IDD, pParent)
{
}

CCG2GuildInfo::~CCG2GuildInfo()
{
}

void CCG2GuildInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbUPage);
	DDX_Control(pDX, IDC_LISTGUILDINFO,listGuild);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
}


BEGIN_MESSAGE_MAP(CCG2GuildInfo, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_NOTIFY(NM_CLICK, IDC_LISTGUILDINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTGUILDINFO, OnNMDblclkListuserinfo)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CCG2GuildInfo::OnInitDialog()
{
	CDialog::OnInitDialog();	
	InitUI();// 初始化显示字符	
	//InitBanType();

	nItem = -1;// 单击用户列表得到行号
	mItem = -1;
	pageInfo = false;// 判断是否需要翻页
	pageUInfo = false;
	ServerIP = "";// 游戏服务器IP	
	GuildName = "";//玩家帐号
	UserNick = "";//玩家昵称
	UserID = "";//玩家ID

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

	if(listGuild.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGuild.MoveWindow(newRect);//设置好listResult的位置
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}


	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//初始建立对话框

	theApp.operCG2.GetServerList();//请求所有的游戏服务器列表

	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//发送查询请求	

	return TRUE;
}

// 初始化显示字符
void CCG2GuildInfo::InitUI()
{

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_GuildManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIGUILDNAME,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblGuildName"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLHINT,theApp.operCG2.ReadValue("MCG2","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgGuildInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgGuildMember"));

}

// 自动改变大小
void CCG2GuildInfo::OnSize(UINT nType, int cx, int cy)
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

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listGuild.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGuild.MoveWindow(newRect);//设置好listResult的位置
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
HBRUSH CCG2GuildInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询资料信息
void CCG2GuildInfo::OnBnClickedUisearch()
{
	try
	{

		nItem = -1;//列表没有选定项
		mItem = -1;
		pageInfo = false;//列表不能翻页	
		pageUInfo = false;
		cmbPage.ResetContent();//清除列表翻页的复选框
		cmbUPage.ResetContent();
		while(listGuild.DeleteColumn(0)){}
		while(listResult.DeleteColumn(0)){}//清除列表中的所有内容

		UpdateData(true);			

		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
	
		GetDlgItemText(IDC_EDITUIGUILDNAME,GuildName);//获取玩家帐号
		GuildInfo();
		
	}
	catch(...)
	{
	}
}

// 查询公会信息
void CCG2GuildInfo::GuildInfo()
{
	try
	{		
		CIni mIni;	

		nItem = -1;
		pageUInfo = false;		
		cmbUPage.ResetContent();
		while(listGuild.DeleteColumn(0)){}
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//查询第一页的信息
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchGuild_Query);//发送查询公会资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

//查询公会成员
void CCG2GuildInfo::GuildDetail()
{
	try
	{				
		CIni mIni;
		
		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//玩家帐号
		_itoa(GuildId,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchGuild_Detail_Query);
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 翻页进行查询
void CCG2GuildInfo::OnCbnSelchangeCmbuipage()
{	
	////OperationCG2 operCG2;
	try
	{		
		if(pageUInfo)
		{	
			CIni mIni;

			while(listGuild.DeleteColumn(0)){}
			
			int index = cmbUPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchGuild_Query);
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 翻页查询成员列表
void CCG2GuildInfo::OnCbnSelchangeCmbpage()
{
	//OperationCG2 operCG2;
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listResult.DeleteColumn(0)){}
			
			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 2)
			{				
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchGuild_Detail_Query);				
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 单击资料信息保存当前行号
void CCG2GuildInfo::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			nItem = listGuild.SubItemHitTest(&lvinfo);//保存在列表中选中的行号
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// 双击资料信息进行操作
void CCG2GuildInfo::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listGuild.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listGuild.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listGuild.SubItemHitTest(&lvinfo);//保存在列表中选中的行号

			if(nItem >= 0)
			{
				//////OperationCG2 operCG2;
				CIni mIni;
				if(tbcResult.GetCurSel() == 0)//如果当前是在玩家资料信息的页面
				{
					tbcResult.SetCurSel(1);//跳转到进行帐号封停的页面

					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

					
					GuildName = theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildName"));// 保存选中的公会名称
					GuildId = atoi(theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildID")));//获取公会ID
					GuildDetail();	
				}	
				
			}
		}
		else
		{
			nItem = -1;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}


// 切换选项卡进行查询
void CCG2GuildInfo::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CIni mIni;
	//OperationCG2 operCG2;

	if(tbcResult.GetCurSel()==0)//如果选中的是玩家资料信息的页面
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
		
	}
	else if(tbcResult.GetCurSel()==1)//如果选中的是封停帐号列表的页面
	{
		CIni mIni;
		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTGUILDINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

		if((listGuild.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildName = theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildName"));// 保存选中的公会名称
			GuildId = atoi(theApp.operCG2.GetValueByColName(&listGuild, nItem, theApp.operCG2.ReadValue("MCG2","CG2_GuildID")));//获取公会ID

			if(tbcResult.GetCurSel()==1)
			{
				GuildDetail();	// 查询成员列表
			}
			
		}
		
	}
	*pResult = 0;
}


// 接收返回信息
LRESULT CCG2GuildInfo::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	//OperationCG2 theApp.operCG2;
	CIni mIni;

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Receive");//当前的状态为接收到了返回信息

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

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_SearchGuild_Query_Resp://查询公会资料信息的回应
		{
			if(pageInfo)
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listGuild,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listGuild,&pageCount);//构造CListCtrl对象

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
	case CEnumCore::Message_Tag_ID::CG2_SearchGuild_Detail_Query_Resp://查询公会成员
		{
			if(pageInfo)
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					nItem = -1;
					pageInfo = false;					
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//清空复选框
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
	//socketdata.Destroy();
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// 关闭对话框
void CCG2GuildInfo::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIGUILDNAME,"");
}

// 关闭对话框
void CCG2GuildInfo::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}



