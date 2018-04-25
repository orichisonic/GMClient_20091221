// SDOItemManager.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOItemManager.h"
#include ".\sdoitemmanager.h"


// CSDOItemManager 对话框

IMPLEMENT_DYNAMIC(CSDOItemManager, CDialog)
CSDOItemManager::CSDOItemManager(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOItemManager::IDD, pParent)
{
}

CSDOItemManager::~CSDOItemManager()
{
}

void CSDOItemManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_CMBBIGTYPEM, cmbBigTypeM);
	DDX_Control(pDX, IDC_CMBSMALLTYPEM, cmbSmallTypeM);
	DDX_Control(pDX, IDC_CMBGETITEMM, cmbGetItemM);
	DDX_Control(pDX, IDC_CMBBIGTYPEF, cmbBigTypeF);
	DDX_Control(pDX, IDC_CMBSMALLTYPEF, cmbSmallTypeF);
	DDX_Control(pDX, IDC_CMBGETITEMF, cmbGetItemF);
}


BEGIN_MESSAGE_MAP(CSDOItemManager, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTITEM, OnNMDblclkListitem)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTITEM, OnLvnColumnclickListitem)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BTOK, OnBnClickedBtok)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBBIGTYPEM, OnCbnSelchangeCmbbigtypem)
	ON_CBN_SELCHANGE(IDC_CMBSMALLTYPEM, OnCbnSelchangeCmbsmalltypem)
	ON_CBN_SELCHANGE(IDC_CMBBIGTYPEF, OnCbnSelchangeCmbbigtypef)
	ON_CBN_SELCHANGE(IDC_CMBSMALLTYPEF, OnCbnSelchangeCmbsmalltypef)
END_MESSAGE_MAP()


// CSDOItemManager 消息处理程序

// 初始化对话框
BOOL CSDOItemManager::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();// 初始化显示字符

	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	iType=0;
	iSort=0;
	iSexType=0;

	iLevel=0;
	iLevelPer=0;
	iRegistPer=0;
	iUseTimes=0;
	iUseLimit=0;
	iItemCode=0;

	ItemName1="";
	ItemName2="";
	iItemCode=0;
	iItemCode=0;

	ShowUserInfo();//显示用户资料信息

	SetProp(listItem.GetSafeHwnd(),"排序列号",(HANDLE)0);
    SetProp(listItem.GetSafeHwnd(),"排序顺序",(HANDLE)1);


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

	if(listItem.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listItem.MoveWindow(newRect);//设置好listUser的位置
	}

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Create");//当前的状态为初始建立对话框

	if(theApp.operSDO.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 初始化显示字符
void CSDOItemManager::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","YYL_UI_ItemManager"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operSDO.ReadValue("MSDO","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operSDO.ReadValue("MSDO","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLITEMNAME,theApp.operSDO.ReadValue("MSDO","ItemName"));
	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","Search"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operSDO.ReadValue("MSDO","UIC_UI_Page"));

	
	SetDlgItemText(IDC_LBLBIGTYPEM,theApp.operSDO.ReadValue("MSDO","BigType"));
	SetDlgItemText(IDC_LBLSMALLTYPEM,theApp.operSDO.ReadValue("MSDO","SmallType"));
	SetDlgItemText(IDC_LBLGETITEMM,theApp.operSDO.ReadValue("MSDO","MaleItem"));

	SetDlgItemText(IDC_LBLBIGTYPEF,theApp.operSDO.ReadValue("MSDO","BigType"));
	SetDlgItemText(IDC_LBLSMALLTYPEF,theApp.operSDO.ReadValue("MSDO","SmallType"));
	SetDlgItemText(IDC_LBLGETITEMF,theApp.operSDO.ReadValue("MSDO","FemaleItem"));

	SetDlgItemText(IDC_LBLLEVEL,theApp.operSDO.ReadValue("MSDO","Level"));
	SetDlgItemText(IDC_LBLLEVELPER,theApp.operSDO.ReadValue("MSDO","LevelPercent"));
	SetDlgItemText(IDC_LBLREGISTPER,theApp.operSDO.ReadValue("MSDO","RegistPercent"));
	SetDlgItemText(IDC_LBLUSETIMES,theApp.operSDO.ReadValue("MSDO","UseTimes"));
	SetDlgItemText(IDC_LBLUSELIMIT,theApp.operSDO.ReadValue("MSDO","UseLimit"));

	SetDlgItemText(IDC_BTOK,theApp.operSDO.ReadValue("MSDO","Search"));
	SetDlgItemText(IDC_BTREST,theApp.operSDO.ReadValue("MSDO","Close"));

	tbcResult.InsertItem(0,theApp.operSDO.ReadValue("MSDO","YYL_UI_tpgItemInfo"));
	tbcResult.InsertItem(1,theApp.operSDO.ReadValue("MSDO","YYL_UI_tpgItemAdd"));//add
	tbcResult.InsertItem(2,theApp.operSDO.ReadValue("MSDO","YYL_UI_tpgItemUpdate"));//update
}


// 自动改变大小
void CSDOItemManager::OnSize(UINT nType, int cx, int cy)
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

	if(listItem.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listItem.MoveWindow(newRect);//设置好listUser的位置
	}

}

//设置背景颜色
HBRUSH CSDOItemManager::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//处理快捷键响应函数
BOOL CSDOItemManager::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listItem.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listItem);				
				}
				
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listItem.m_hWnd)
				{
					for(int i=0; i<listItem.GetItemCount(); i++)
					{
					    listItem.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listItem.EnsureVisible(i,false);
					}
				}

			}
		}		
	}
	return FALSE;
}

// 关闭对话框
void CSDOItemManager::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//关闭窗体	

	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}

	if(!ItemCodeList.IsEmpty())
	{
		ItemCodeList.RemoveAll();
	}

	if(!ItemCodeListF.IsEmpty())
	{
		ItemCodeListF.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CSDOItemManager::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_ETITEMNAME,"");
	ShowUserInfo();
}

// 显示角色资料信息
void CSDOItemManager::ShowUserInfo()
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLBIGTYPEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSMALLTYPEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGETITEMM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBIGTYPEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSMALLTYPEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBGETITEMM)->ShowWindow(SW_HIDE);


	GetDlgItem(IDC_LBLBIGTYPEF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSMALLTYPEF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGETITEMF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBIGTYPEF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSMALLTYPEF)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBGETITEMF)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLEVELPER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLEVELPER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLREGISTPER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETREGISTPER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUSELIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETUSELIMIT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTREST)->ShowWindow(SW_HIDE);
}

	// 显示其它信息
void CSDOItemManager::ShowOtherInfo()
{
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBIGTYPEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSMALLTYPEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLGETITEMM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBBIGTYPEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBSMALLTYPEM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBGETITEMM)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_LBLBIGTYPEF)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSMALLTYPEF)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLGETITEMF)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBBIGTYPEF)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBSMALLTYPEF)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBGETITEMF)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLLEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETLEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLLEVELPER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETLEVELPER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLREGISTPER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETREGISTPER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUSETIMES)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETUSETIMES)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUSELIMIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETUSELIMIT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BTOK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTREST)->ShowWindow(SW_SHOW);

	ItemType();
}

// 单击用户列表保存当前行号
void CSDOItemManager::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 0)
	{
		if(listItem.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listItem.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;


			nItem = listItem.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
			iLevel= atoi(theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Level")));
			iLevelPer= atoi(theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_LevPercent")));
			iRegistPer= atoi(theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Precent")));
			iUseTimes= atoi(theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_TimesLimit")));
			iUseLimit= atoi(theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_DaysLimit")));

			ItemName1=theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_ItemName1"));
			ItemName2=theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_ItemName2"));
			iItemCode= atoi(theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_ItemCode1")));
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 双击道具列表删除
void CSDOItemManager::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 0)
	{
		if(listItem.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listItem.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listItem.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nItem >= 0)
			{

				iItemCode= atoi(theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_ItemCode1")));
				ItemName1=theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_ItemName1"));
				ItemName2=theApp.operSDO.GetValueByColName(&listItem, nItem, theApp.operSDO.ReadValue("MSDO","SDO_ItemName2"));
				DelItem();
			}
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

//删除道具
void CSDOItemManager::DelItem()
{
	try
	{
		UpdateData(true);
		CString strMsg = theApp.operSDO.ReadValue("MSDO","IM_UI_DelItem");
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
		{
			return;
		}

		CIni mIni;

		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		int userByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name

		_itoa(iItemCode,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);


		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName1,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName1),(unsigned char *)mIni.wcharToChar(ItemName1));//道具名称1
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName2,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName2),(unsigned char *)mIni.wcharToChar(ItemName2));//道具名称1

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_YYHAPPYITEM_DELETE))//
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量

	}
	catch(...)
	{
	}
}

// 切换选项卡进行查询
void CSDOItemManager::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if(tbcResult.GetCurSel() == 0)
	{
		cmbPage.ResetContent();
		pageInfo = false;
		ShowUserInfo();//显示用户资料信息
	}
	else if(tbcResult.GetCurSel() == 1)//添加
	{
		ShowOtherInfo();
		SetDlgItemText(IDC_BTOK,theApp.operSDO.ReadValue("MSDO","AddItem"));

		SetDlgItemInt(IDC_ETLEVEL,0);
		SetDlgItemInt(IDC_ETLEVELPER,0);
		SetDlgItemInt(IDC_ETREGISTPER,0);
		SetDlgItemInt(IDC_ETUSETIMES,0);
		SetDlgItemInt(IDC_ETUSELIMIT,0);

	}
	else if(tbcResult.GetCurSel() ==2 )//编辑
	{
		ShowOtherInfo();
		SetDlgItemText(IDC_BTOK,theApp.operSDO.ReadValue("MSDO","UpdateItem"));

		SetDlgItemInt(IDC_ETLEVEL,iLevel);
		SetDlgItemInt(IDC_ETLEVELPER,iLevelPer);
		SetDlgItemInt(IDC_ETREGISTPER,iRegistPer);
		SetDlgItemInt(IDC_ETUSETIMES,iUseTimes);
		SetDlgItemInt(IDC_ETUSELIMIT,iUseLimit);
	}
	*pResult = 0;
}



//单击结果信息的列名进行排序
void CSDOItemManager::OnLvnColumnclickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listItem,pNMHDR,pResult);
}

//查询道具信息//SDO_YYHAPPYITEM_QUERY
void CSDOItemManager::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;

		int index = theApp.operSDO.ReadIntValue("MSDO","index");//查询第一页的信息
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		pageInfo=false;
		cmbPage.ResetContent();
		while(listItem.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_SelectServer"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
		
		CString Item="";
		GetDlgItemText(IDC_ETITEMNAME,Item);
		if(Item == "")
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_InputItemName"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(Item),(unsigned char *)mIni.wcharToChar(Item));
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_YYHAPPYITEM_QUERY))//
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}

//添加或者编辑道具
void CSDOItemManager::OnBnClickedBtok()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ItemOp="";
	GetDlgItemText(IDC_BTOK,ItemOp);

	if(ItemOp==theApp.operSDO.ReadValue("MSDO","AddItem"))
	{
		AddItem();
	}
	else if(ItemOp==theApp.operSDO.ReadValue("MSDO","UpdateItem"))
	{
		UpdateItem();
	}
}

//添加道具
void CSDOItemManager::AddItem()
{
	try
	{

			CIni mIni;

			CSocketData socketdata;	
			socketdata.InitCreate(1,14);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];

			int userByID=theApp.UserByID;

			iUseTimes=GetDlgItemInt(IDC_ETUSETIMES);
			iUseLimit=GetDlgItemInt(IDC_ETUSELIMIT);
			iLevel=GetDlgItemInt(IDC_ETLEVEL);
			iLevelPer=GetDlgItemInt(IDC_ETLEVELPER);
			iRegistPer=GetDlgItemInt(IDC_ETREGISTPER);


				ItemCodeList.Lookup(cmbGetItemM.GetCurSel()+1,iItemCode1);
				GetDlgItemText(IDC_CMBGETITEMM,ItemName1);

				ItemCodeListF.Lookup(cmbGetItemF.GetCurSel()+1,iItemCode2);
				GetDlgItemText(IDC_CMBGETITEMF,ItemName2);


	
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
//			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

			_itoa(iItemCode1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode1,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iItemCode2,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode2,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_BigType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//大类

			_itoa(iSort,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_SmallType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//小类
			
			_itoa(iLevel,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Level,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iLevelPer,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_LevPercent,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iRegistPer,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Precent,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iUseTimes,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_TimesLimit,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);
			
			_itoa(iUseLimit,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_DaysLimit,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);


			_itoa(userByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName1,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName1),(unsigned char *)mIni.wcharToChar(ItemName1));//道具名称1
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName2,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName2),(unsigned char *)mIni.wcharToChar(ItemName2));//道具名称1


			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_YYHAPPYITEM_CREATE))//
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量

	}
	catch(...)
	{
	}
}
//编辑道具
void CSDOItemManager::UpdateItem()
{
	try
	{

			CIni mIni;

			CSocketData socketdata;	
			socketdata.InitCreate(1,15);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];

			int userByID=theApp.UserByID;

			iUseTimes=GetDlgItemInt(IDC_ETUSETIMES);
			iUseLimit=GetDlgItemInt(IDC_ETUSELIMIT);
			iLevel=GetDlgItemInt(IDC_ETLEVEL);
			iLevelPer=GetDlgItemInt(IDC_ETLEVELPER);
			iRegistPer=GetDlgItemInt(IDC_ETREGISTPER);

			ItemCodeList.Lookup(cmbGetItemM.GetCurSel()+1,iItemCode1);
			GetDlgItemText(IDC_CMBGETITEMM,ItemName1);

			ItemCodeListF.Lookup(cmbGetItemF.GetCurSel()+1,iItemCode2);
			GetDlgItemText(IDC_CMBGETITEMF,ItemName2);

			
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
//			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

			_itoa(iItemCode,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iItemCode1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode1,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iItemCode2,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode2,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_BigType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//大类

			_itoa(iSort,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_SmallType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//小类
			
			_itoa(iLevel,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Level,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iLevelPer,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_LevPercent,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iRegistPer,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Precent,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iUseTimes,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_TimesLimit,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);
			
			_itoa(iUseLimit,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_DaysLimit,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);


			_itoa(userByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName1,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName1),(unsigned char *)mIni.wcharToChar(ItemName1));//道具名称1
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName2,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName2),(unsigned char *)mIni.wcharToChar(ItemName2));//道具名称1


			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_YYHAPPYITEM_UPDATE))//
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量

	}
	catch(...)
	{
	}
}

//道具类别导入数据
void CSDOItemManager::ItemType()
{
	cmbBigTypeM.ResetContent();
	cmbBigTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Dress"));
	cmbBigTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Item"));
	cmbBigTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_TaoZhuang"));
	cmbBigTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Brand"));
	cmbBigTypeM.SetCurSel(0);

	cmbBigTypeF.ResetContent();
	cmbBigTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Dress"));
	cmbBigTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Item"));
	cmbBigTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_TaoZhuang"));
	cmbBigTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Brand"));
	cmbBigTypeF.SetCurSel(0);

}



//切换大类(男性)
void CSDOItemManager::OnCbnSelchangeCmbbigtypem()
{
	// TODO: 在此添加控件通知处理程序代码
	iSexType=0;//男性
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBBIGTYPEM))->GetCurSel();//当前选中的行
	CString str="";

	((CComboBox*)GetDlgItem(IDC_CMBBIGTYPEM))->GetLBText(iPos,str); //其中n为从0开始的索引值
	if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Dress"))
	{
		iType=0;
		cmbSmallTypeM.ResetContent();
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_head"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_hair"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_body"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_leg"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_hand"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_feet"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_face"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_glass"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Wing"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Link"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_StarFace"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_FalseFace"));
		cmbSmallTypeM.SetCurSel(0);

		//GetDlgItem(IDC_CMBGETITEMM)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPEM)->EnableWindow(true);
		cmbGetItemM.ResetContent();
	}
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Item"))
	{
		iType=1;
		cmbSmallTypeM.ResetContent();
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_eff"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_fitem"));
		cmbSmallTypeM.SetCurSel(0);

		//GetDlgItem(IDC_CMBGETITEMM)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPEM)->EnableWindow(true);
		cmbGetItemM.ResetContent();

	}
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_TaoZhuang"))
	{
		iType=2;
		cmbSmallTypeM.ResetContent();
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","IC_Code_taozhuang1"));
		cmbSmallTypeM.AddString(theApp.operSDO.ReadValue("MSDO","IC_Code_present"));
		cmbSmallTypeM.SetCurSel(0);

		//GetDlgItem(IDC_CMBGETITEMM)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPEM)->EnableWindow(true);
		cmbGetItemM.ResetContent();
	}
	else
	{
		iType=3;
		iSort=0;
		GetDlgItem(IDC_CMBGETITEMM)->EnableWindow(true);
		//GetDlgItem(IDC_CMBSMALLTYPEM)->EnableWindow(false);
		cmbSmallTypeM.ResetContent();
		//iSexType=0;
		MaleItem();////查询男性道具
	}
}

//查询男性道具
void CSDOItemManager::MaleItem()
{
	try
	{

			CIni mIni;

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
			char strInt[10];
			
			CString strPresent="";
			int iSex=0;
			GetDlgItemText(IDC_CMBSMALLTYPEM,strPresent);///////////////////////////////
			if(strPresent==theApp.operSDO.ReadValue("MSDO","IC_Code_present"))
				iSex=2;
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

			_itoa(iType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_BigType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iSort,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_SmallType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数
			
			_itoa(iSex,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_SEX,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_ITEMSHOP_QUERY))//
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量

	}
	catch(...)
	{
	}
}
//切换小类
void CSDOItemManager::OnCbnSelchangeCmbsmalltypem()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBSMALLTYPEM))->GetCurSel();//当前选中的行
	CString str="";

	((CComboBox*)GetDlgItem(IDC_CMBSMALLTYPEM))->GetLBText(iPos,str); //其中n为从0开始的索引值
	if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_head"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_hair"))
		iSort=1;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_body"))
		iSort=2;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_leg"))
		iSort=3;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_hand"))
		iSort=4;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_feet"))
		iSort=5;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_face"))
		iSort=6;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_glass"))
		iSort=7;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Wing"))
		iSort=8;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_onedress"))
		iSort=50;
	else if(str==theApp.operSDO.ReadValue("MSDO","IC_Code_taozhuang1"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Link"))
		iSort=9;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_StarFace"))
		iSort=51;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_FalseFace"))
		iSort=57;

	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_eff"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_fitem"))
		iSort=0;

	MaleItem();
}

// 接收返回信息
LRESULT CSDOItemManager::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;
	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operSDO.ReadValue("MSDO","Main_UI_SENDDATAERROR"),theApp.operSDO.ReadValue("MSDO","ERROR"),0);//Main_UI_ParseData		
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

			theApp.operSDO.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_YYHAPPYITEM_QUERY_RESP:
		{
			if(pageInfo)//如果已经能够翻页
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listItem,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listItem,&pageCount);//构造CListCtrl对象

				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
					cmbPage.ResetContent();
					while(listItem.DeleteColumn(0)){}
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
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_QUERY_RESP:
		{
			if(iSexType==0)//Male
			{
				if(!ItemCodeList.IsEmpty())
				{
					ItemCodeList.RemoveAll();
				}
				for(int i = 1;i <= socketdata.getQueryNum();i++)
				{
					int nItem = StrToInt((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::SDO_ItemCode).lpdata);//得到服务器IP
					ItemCodeList.SetAt(i,nItem);//
				}

				theApp.operSDO.BuildComboxs(&socketdata,&cmbGetItemM);
			}
			else if(iSexType==1)//Female
			{
				if(!ItemCodeListF.IsEmpty())
				{
					ItemCodeListF.RemoveAll();
				}
				for(int i = 1;i <= socketdata.getQueryNum();i++)
				{
					int nItem = StrToInt((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::SDO_ItemCode).lpdata);//得到服务器IP
					ItemCodeListF.SetAt(i,nItem);//
				}
				theApp.operSDO.BuildComboxs(&socketdata,&cmbGetItemF);
			}

		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_YYHAPPYITEM_CREATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_YYHAPPYITEM_DELETE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_YYHAPPYITEM_UPDATE_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operSDO.ShowResult(result);//显示操作结果
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

//切换大类（女性）
void CSDOItemManager::OnCbnSelchangeCmbbigtypef()
{
	// TODO: 在此添加控件通知处理程序代码

	iSexType=1;//女性
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBBIGTYPEF))->GetCurSel();//当前选中的行
	CString str="";

	((CComboBox*)GetDlgItem(IDC_CMBBIGTYPEF))->GetLBText(iPos,str); //其中n为从0开始的索引值
	if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Dress"))
	{
		iType=0;
		cmbSmallTypeF.ResetContent();
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_head"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_hair"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_body"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_leg"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_hand"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_feet"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_face"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_glass"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Wing"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Link"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_StarFace"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_FalseFace"));//RE_Code_onedress
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_onedress"));
		cmbSmallTypeF.SetCurSel(0);

		//GetDlgItem(IDC_CMBGETITEMF)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPEF)->EnableWindow(true);
		cmbGetItemF.ResetContent();
	}
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Item"))
	{
		iType=1;
		cmbSmallTypeF.ResetContent();
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_eff"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_fitem"));
		cmbSmallTypeF.SetCurSel(0);

		//GetDlgItem(IDC_CMBGETITEMF)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPEF)->EnableWindow(true);
		cmbGetItemF.ResetContent();

	}
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_TaoZhuang"))
	{
		iType=2;
		cmbSmallTypeF.ResetContent();
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","IC_Code_taozhuang1"));
		cmbSmallTypeF.AddString(theApp.operSDO.ReadValue("MSDO","IC_Code_present"));
		cmbSmallTypeF.SetCurSel(0);

		//GetDlgItem(IDC_CMBGETITEMF)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPEF)->EnableWindow(true);
		cmbGetItemF.ResetContent();
	}
	else
	{
		iType=3;
		iSort=0;
		//GetDlgItem(IDC_CMBGETITEMF)->EnableWindow(true);
		GetDlgItem(IDC_CMBSMALLTYPEF)->EnableWindow(false);
		cmbGetItemF.ResetContent();
		//iSexType=1;
		MaleItem();////查询男性道具
	}
}

//切换女性道具小类
void CSDOItemManager::OnCbnSelchangeCmbsmalltypef()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBSMALLTYPEF))->GetCurSel();//当前选中的行
	CString str="";

	((CComboBox*)GetDlgItem(IDC_CMBSMALLTYPEF))->GetLBText(iPos,str); //其中n为从0开始的索引值
	if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_head"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_hair"))
		iSort=1;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_body"))
		iSort=2;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_leg"))
		iSort=3;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_hand"))
		iSort=4;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_feet"))
		iSort=5;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_face"))
		iSort=6;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_glass"))
		iSort=7;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Wing"))
		iSort=8;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_onedress"))
		iSort=50;
	else if(str==theApp.operSDO.ReadValue("MSDO","IC_Code_taozhuang1"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Link"))
		iSort=9;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_StarFace"))
		iSort=51;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_FalseFace"))
		iSort=57;

	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_eff"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_fitem"))
		iSort=0;

	MaleItem();
}
