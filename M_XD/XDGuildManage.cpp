// XDGuildManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDGuildManage.h"
#include ".\xdguildmanage.h"


// CXDGuildManage 对话框

IMPLEMENT_DYNAMIC(CXDGuildManage, CDialog)
CXDGuildManage::CXDGuildManage(CWnd* pParent /*=NULL*/)
	: CDialog(CXDGuildManage::IDD, pParent)
{
}

CXDGuildManage::~CXDGuildManage()
{
}

void CXDGuildManage::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
}


BEGIN_MESSAGE_MAP(CXDGuildManage, CDialog)
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
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNDEL, OnBnClickedBtndel)
	ON_CBN_SELCHANGE(IDC_CMBTYPE, OnCbnSelchangeCmbtype)
END_MESSAGE_MAP()


// CXDGuildManage 消息处理程序

// 初始化对话框
BOOL CXDGuildManage::OnInitDialog()
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

	ShowEditInfo(SW_HIDE);	
	ShowResultInfo(SW_HIDE);
	ShowBasicInfo(SW_SHOW);

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
void CXDGuildManage::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","GM_UI_GuildManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLNAME,theApp.operXD.ReadValue("MXD","GM_UI_GuildName"));
	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLEDITNAME,theApp.operXD.ReadValue("MXD","GM_UI_MemberName"));
	SetDlgItemText(IDC_BTNDEL,theApp.operXD.ReadValue("MXD","GM_UI_DelMember"));

	SetDlgItemText(IDC_LBLMODNAME,theApp.operXD.ReadValue("MXD","GM_UI_GuildName"));
	SetDlgItemText(IDC_LBLTYPE,theApp.operXD.ReadValue("MXD","GM_UI_Type"));
	SetDlgItemText(IDC_LBLNEWVALUE,theApp.operXD.ReadValue("MXD","GM_UI_NewValue"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","GM_UI_Edit"));
	SetDlgItemText(IDC_BTNRESET,theApp.operXD.ReadValue("MXD","Reset"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","GI_UI_GuildInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","GI_UI_GuildMember"));
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","GM_UI_InfoEdit"));
	//tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","GM_UI_GuildEdit"));	

	cmbType.ResetContent();
	cmbType.AddString(theApp.operXD.ReadValue("MXD","GM_UI_Level"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","GM_UI_Name"));
}


// 自动改变大小
void CXDGuildManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CXDGuildManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询基本资料信息
void CXDGuildManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//基本资料列表没有选定项
		pageBasic = false;//基本资料列表不能翻页	
		cmbBasic.ResetContent();//清除基本资料列表翻页的复选框
		while(listBasic.DeleteColumn(0)){}//清除基本资料列表中的所有内容

		ShowEditInfo(SW_HIDE);	
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

		GetDlgItemText(IDC_EDITNAME,GuildName);//获取公会名称
		BasicInfo();// 查询基本资料信息
	}
	catch(...)
	{
	}
}

// 查询基本资料信息
void CXDGuildManage::BasicInfo()
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
		socketdata.InitCreate(1,10);//服务器IP、公会名称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//公会名称
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_GuildBaseInfo_Query);//发送查询基本资料信息的请求

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
void CXDGuildManage::OnCbnSelchangeCmbbasic()
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
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//公会名称
			
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_GuildBaseInfo_Query);//发送查询基本资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 单击基本资料信息保存当前行号
void CXDGuildManage::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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
void CXDGuildManage::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
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

				GuildID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildID"));// 保存选中的公会ID
				GuildName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildName"));// 保存选中的公会名称

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
void CXDGuildManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	OnBnClickedBtnreset();
	if(tbcResult.GetCurSel() == 0)//选中的是基本资料信息选项卡
	{
		ShowEditInfo(SW_HIDE);	
		ShowResultInfo(SW_HIDE);
		ShowBasicInfo(SW_SHOW);
	}
	else if(tbcResult.GetCurSel() == 1)//选中的是结果资料信息选项卡
	{
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		ShowEditInfo(SW_HIDE);
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_SHOW);

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildID"));// 保存选中的公会ID
			GuildName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildName"));// 保存选中的公会名称

			//查询相关资料信息
			ResultInfo();
		}
	}
	else if(tbcResult.GetCurSel() == 3)//选中的是解散/恢复公会页面
	{
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_HIDE);
		ShowEditInfo(SW_SHOW);

		GetDlgItem(IDC_LBLTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBTYPE)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_LBLNEWVALUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNEWVALUE)->ShowWindow(SW_HIDE);

		SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","GM_UI_DelGuild"));
		SetDlgItemText(IDC_BTNRESET,theApp.operXD.ReadValue("MXD","GM_UI_RecoverGuild"));

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildID"));// 保存选中的公会ID
			GuildName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildName"));// 保存选中的公会名称

			SetDlgItemText(IDC_EDITMODNAME,GuildName);
		}
	}
	else if(tbcResult.GetCurSel() == 2)//选中的是修改公会信息
	{
		ShowBasicInfo(SW_HIDE);		
		ShowResultInfo(SW_HIDE);
		ShowEditInfo(SW_SHOW);

		SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","GM_UI_Edit"));
		SetDlgItemText(IDC_BTNRESET,theApp.operXD.ReadValue("MXD","Reset"));

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			GuildID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildID"));// 保存选中的公会ID
			GuildName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_GuildName"));// 保存选中的公会名称

			SetDlgItemText(IDC_EDITMODNAME,GuildName);
		}
	}
	*pResult = 0;
}

//查询相关资料信息
void CXDGuildManage::ResultInfo()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//公会ID
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//公会名称
			
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_GuildMemberList_Query);//相关记录信息

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

// 翻页进行查询
void CXDGuildManage::OnCbnSelchangeCmbresult()
{	
	try
	{
		if(pageResult)
		{
			CIni mIni;

			int index = cmbResult.GetCurSel() + 1;
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//公会ID
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//公会名称
			
				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

				int midlength = socketdata.EnBody();
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_GuildMemberList_Query);//相关记录信息
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//单击结果列表保存行号
void CXDGuildManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listResult.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		mItem = listResult.SubItemHitTest(&lvinfo);//保存在结果信息列表中选中的行号

		if(mItem >= 0)
		{			
			UserName = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
			//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_AccountID"));// 保存选中的玩家ID
			UserNick = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家昵称

			SetDlgItemText(IDC_EDITEDITNAME,UserNick);
		}
	}
	else
	{
		mItem = -1;
	}
	*pResult = 0;
}

//玩家退出公会
void CXDGuildManage::OnBnClickedBtndel()
{
	try
	{
		if((listResult.GetItemCount() == 0) || (mItem<0))
			return;	

		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		GetDlgItemText(IDC_EDITEDITNAME,UserNick);//获取玩家帐号
		if(UserNick == "")//要踢出公会的玩家昵称不能为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","GM_HINT_PARAMNULL"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家角色名

		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//公会ID
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//公会名称
		
		int midlength = socketdata.EnBody();
		//theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_KickGuildMember_Operate);//玩家退出公会

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","GM_Error_EditGuild"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//切换公会信息修改的类型
void CXDGuildManage::OnCbnSelchangeCmbtype()
{
	// TODO: 在此添加控件通知处理程序代码
}

//修改公会相关信息
void CXDGuildManage::OnBnClickedBtnedit()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			GetDlgItemText(IDC_EDITMODNAME,GuildName);//获取原公会名称
			if(GuildName == "")//要修改的公会名称不能为空
			{
				MessageBox(theApp.operXD.ReadValue("MXD","GM_HINT_PARAMNULL"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CString NewValue = "";			
			if(tbcResult.GetCurSel() == 3)
			{
				GetDlgItemText(IDC_EDITNEWVALUE,NewValue);//获取修改后的值
				if(NewValue == "")//修改后的值不能为空
				{
					MessageBox(theApp.operXD.ReadValue("MXD","GM_HINT_PARAMNULL"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//公会ID
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//公会名称
			
			//socketdata.AddTFLV(CEnumCore::TagName::WA_NewGuildName,CEnumCore::TagFormat::TLV_STRING,strlen(NewGuildName),(unsigned char *)mIni.wcharToChar(NewGuildName));//新公会名称
			
			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的条数

			int midlength = socketdata.EnBody();
			//theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyGuildName_Operate);//修改公会名称

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","GM_Error_EditName"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//重置公会管理信息
void CXDGuildManage::OnBnClickedBtnreset()
{	
	try
	{
		SetDlgItemText(IDC_EDITNEWVALUE,"");
		SetDlgItemText(IDC_EDITEDITNAME,"");
		if(tbcResult.GetCurSel() == 2)
		{
			CIni mIni;

			int index = theApp.operXD.ReadIntValue("MXD","index");
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				GetDlgItemText(IDC_EDITMODNAME,GuildName);//获取公会名称
				if(GuildName == "")//要修改的公会名称不能为空
				{
					MessageBox(theApp.operXD.ReadValue("MXD","GM_HINT_PARAMNULL"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildID,CEnumCore::TagFormat::TLV_STRING,strlen(GuildID),(unsigned char *)mIni.wcharToChar(GuildID));//公会ID
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_GuildName,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//公会名称
				
				//socketdata.AddTFLV(CEnumCore::TagName::WA_NewGuildName,CEnumCore::TagFormat::TLV_STRING,strlen(NewGuildName),(unsigned char *)mIni.wcharToChar(NewGuildName));//新公会名称
				
				int userbyID = theApp.UserByID;
				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

				_itoa(0,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
				_itoa(0,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的条数

				int midlength = socketdata.EnBody();
				//theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ModifyGuildName_Operate);//修改公会名称

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求

				socketdata.Destroy();
			}
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","GM_Error_EditName"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// 接收返回信息
LRESULT CXDGuildManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Receive");//当前的状态为接收到了返回信息

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
			theApp.operXD.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MercenaryGroup_Info_Query_Resp://查询基本资料信息的回应
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
	case CEnumCore::Message_Tag_ID::WA_DissolveGuild_Operate_Resp://解散公会
	case CEnumCore::Message_Tag_ID::WA_KickGuildMember_Operate_Resp://踢出公会成员
	case CEnumCore::Message_Tag_ID::WA_AttornPopedom_Operate_Resp://家族管理
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//显示返回结果
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_ModifyGuildName_Operate_Resp://修改公会名称
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//显示返回结果

			SetDlgItemText(IDC_EDITNEWVALUE,"");
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

// 清空页面
void CXDGuildManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITNAME,"");
}

// 关闭对话框
void CXDGuildManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//全选、复制
BOOL CXDGuildManage::PreTranslateMessage(MSG* pMsg)
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
				else if(pMsg->hwnd == listResult.m_hWnd)
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
void CXDGuildManage::ShowBasicInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTBASIC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
}

//结果资料信息页面
void CXDGuildManage::ShowResultInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLEDITNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITEDITNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDEL)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITEDITNAME,"");
}

//修改信息页面
void CXDGuildManage::ShowEditInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_EDITNEWVALUE,"");

	GetDlgItem(IDC_LBLMODNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITMODNAME)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLNEWVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEWVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
}
