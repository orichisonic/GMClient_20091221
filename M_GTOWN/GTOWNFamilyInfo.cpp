// GTOWNFamilyInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNFamilyInfo.h"
#include ".\gtownfamilyinfo.h"


// CGTOWNFamilyInfo 对话框

IMPLEMENT_DYNAMIC(CGTOWNFamilyInfo, CDialog)
CGTOWNFamilyInfo::CGTOWNFamilyInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CGTOWNFamilyInfo::IDD, pParent)
{
}

CGTOWNFamilyInfo::~CGTOWNFamilyInfo()
{
}

void CGTOWNFamilyInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTFAMILY, listFamily);
	DDX_Control(pDX, IDC_LISTMEMBER, listMember);
	DDX_Control(pDX, IDC_CMBFPAGE, cmbFPage);
}


BEGIN_MESSAGE_MAP(CGTOWNFamilyInfo, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBFPAGE, OnCbnSelchangeCmbfpage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTFAMILY, OnLvnColumnclickListfamily)
	ON_NOTIFY(NM_CLICK, IDC_LISTFAMILY, OnNMClickListfamily)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTFAMILY, OnNMDblclkListfamily)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTMEMBER, OnLvnColumnclickListmember)	
END_MESSAGE_MAP()


// CGTOWNFamilyInfo 消息处理程序

// 初始化对话框
BOOL CGTOWNFamilyInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符	
	ShowFamilyInfo();//显示家族界面信息

	nItem = 0;
	pageFInfo = false;
	pageInfo = false;
	ServerName = "";
	ServerIP = "";
	Name = "";
	FamilyName = "";
	FamilyID = 0;//初始化一些私有变量
	
	SetProp(listFamily.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listFamily.GetSafeHwnd(),"排序顺序",(HANDLE)1);
	
	SetProp(listMember.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listMember.GetSafeHwnd(),"排序顺序",(HANDLE)1);

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

		newRect.top = rs.top + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listFamily.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listFamily.MoveWindow(newRect);//设置好listUser的位置
	}

	if(listMember.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMember.MoveWindow(newRect);//设置好listResult的位置		
	}

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Create");//当前的状态为初始建立对话框

	if(theApp.operGTOWN.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//初始化显示字符
void CGTOWNFamilyInfo::InitUI()
{
	SetWindowText(theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_UserInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLFAMILY,theApp.operGTOWN.ReadValue("MGTOWN","FI_UI_LblFamily"));
	SetDlgItemText(IDSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGTOWN.ReadValue("MGTOWN","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operGTOWN.ReadValue("MGTOWN","FI_UIC_FamilyBasic"));//家族基本信息
	tbcResult.InsertItem(1,theApp.operGTOWN.ReadValue("MGTOWN","FI_UIC_FamilyDetail"));//家族详细信息
}

//自动改变大小
void CGTOWNFamilyInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
	    newRect.top = rs.top + grpHeight + tbcHeight;
	    newRect.bottom = newRect.top + grpPHeight;
	    newRect.left = rs.left +10;
	    newRect.right = rs.right - 10;
  
	    GrpPage.MoveWindow(newRect);//设置好GrpPage的位置
	}

	if(listFamily.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listFamily.MoveWindow(newRect);//设置好listUser的位置
	}

	if(listMember.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMember.MoveWindow(newRect);//设置好listResult的位置
	}
}

//设置背景颜色
HBRUSH CGTOWNFamilyInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//处理快捷键响应函数
BOOL CGTOWNFamilyInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listFamily.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listFamily);				
				}
				else if(pMsg->hwnd == listMember.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listMember);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listFamily.m_hWnd)
				{
					for(int i=0; i<listFamily.GetItemCount(); i++)
					{
					    listFamily.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listFamily.EnsureVisible(i,false);
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



// 查询家族信息
void CGTOWNFamilyInfo::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");//查询第一页的信息
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		pageFInfo = false;//刚开始不能翻页
		cmbFPage.ResetContent();//清空翻页复选框
		while(listFamily.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITFAMILY,Name);//获取要查询的家族名称
		if(Name == "")//家族名称不能为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","FI_WARN_FAMILYNULL"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、家族名称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_FamilyName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//家族名称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FamilyInfo_Query))//发送查询家族资料信息的请求
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

// 翻页查询家族基本信息
void CGTOWNFamilyInfo::OnCbnSelchangeCmbfpage()
{
	try
	{	
		if(pageFInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbFPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//每页显示50条记录

			while(listFamily.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、家族名称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::GT_FamilyName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//家族名称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_FamilyInfo_Query))//发送查询家族资料信息的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// 单击家族信息列表保存当前行号
void CGTOWNFamilyInfo::OnNMClickListfamily(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listFamily.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listFamily.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listFamily.SubItemHitTest(&lvinfo);//保存在家族信息列表中选中的行号
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 双击家族信息列表进行查询
void CGTOWNFamilyInfo::OnNMDblclkListfamily(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listFamily.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listFamily.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listFamily.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);		
				ShowOtherInfo();

				pageInfo = false;
				cmbPage.ResetContent();
				while(listMember.DeleteColumn(0)){}// 清除结果列表中的所有内容

				FamilyName = theApp.operGTOWN.GetValueByColName(&listFamily, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_FamilyName"));//家族名称
				FamilyID = atoi(theApp.operGTOWN.GetValueByColName(&listFamily, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_FamilyID")));//家族ID

				MemberInfo();// 查询家族成员信息
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
void CGTOWNFamilyInfo::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		ShowFamilyInfo();//显示家族信息
	}
	else
	{
		ShowOtherInfo();

		while(listMember.DeleteColumn(0)){}// 清除结果列表中的所有内容

		if((listMember.GetItemCount() > 0) && (nItem >= 0))
		{
			FamilyName = theApp.operGTOWN.GetValueByColName(&listFamily, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_FamilyName"));
			FamilyID = atoi(theApp.operGTOWN.GetValueByColName(&listFamily, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_FamilyID")));

			if(tbcResult.GetCurSel()==1)
			{
				MemberInfo();//家族成员信息
			}
		}
	}
	*pResult = 0;
}

//家族成员信息
void CGTOWNFamilyInfo::MemberInfo()
{
	try
	{		
		CIni mIni;

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		while(listMember.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_FamilyName,CEnumCore::TagFormat::TLV_STRING,strlen(FamilyName),(unsigned char *)mIni.wcharToChar(FamilyName));//家族名称

		_itoa(FamilyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_FamilyID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//家族ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_MemberInfo_Query))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_DetailInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}	
}

// 翻页查询家族成员信息
void CGTOWNFamilyInfo::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//每页显示50条记录

			while(listMember.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//共有六个参数，服务器IP、服务器Name、家族名称、家族ID、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::GT_FamilyName,CEnumCore::TagFormat::TLV_STRING,strlen(FamilyName),(unsigned char *)mIni.wcharToChar(FamilyName));//家族名称

			_itoa(FamilyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_FamilyID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//家族ID

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_MemberInfo_Query))//发送查询家族资料信息的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}



//接收返回信息
LRESULT CGTOWNFamilyInfo::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","Main_UI_ParseData"),theApp.operGTOWN.ReadValue("MGTOWN","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;
	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://查询服务器列表信息的回应
		{
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operGTOWN.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_FamilyInfo_Query_Resp://查询家族资料信息的回应
		{
			if(pageFInfo)//如果已经能够翻页
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listFamily,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listFamily,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageFInfo = false;//不能翻页		
					cmbFPage.ResetContent();
					while(listFamily.DeleteColumn(0)){}
				}
				else
				{
					cmbFPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbFPage.AddString(str);
					}
					cmbFPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageFInfo = false;
					}
					else
					{
						pageFInfo = true;
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_MemberInfo_Query_Resp://查询家族成员信息的回应
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listMember,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listMember,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
					cmbPage.ResetContent();
					while(listMember.DeleteColumn(0)){}
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
	return FALSE;
}

//显示家族信息
void CGTOWNFamilyInfo::ShowFamilyInfo()
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTFAMILY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBFPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTMEMBER)->ShowWindow(SW_HIDE);
}

//显示其它信息
void CGTOWNFamilyInfo::ShowOtherInfo()
{
	GetDlgItem(IDC_LISTFAMILY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBFPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTMEMBER)->ShowWindow(SW_SHOW);
}

//单击家族资料信息的列名进行排序
void CGTOWNFamilyInfo::OnLvnColumnclickListfamily(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listFamily,pNMHDR,pResult);
}

//单击成员信息的列名进行排序
void CGTOWNFamilyInfo::OnLvnColumnclickListmember(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listMember,pNMHDR,pResult);
}

//使用关闭按钮
void CGTOWNFamilyInfo::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITFAMILY, "");
	ShowFamilyInfo();
}

// 关闭对话框
void CGTOWNFamilyInfo::OnClose()
{
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
