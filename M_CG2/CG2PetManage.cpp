// CG2PetManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2PetManage.h"
#include ".\CG2PetManage.h"


// CCG2PetManage 对话框

IMPLEMENT_DYNAMIC(CCG2PetManage, CDialog)
CCG2PetManage::CCG2PetManage(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2PetManage::IDD, pParent)
{
}

CCG2PetManage::~CCG2PetManage()
{
}

void CCG2PetManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTPET, listPet);
	DDX_Control(pDX, IDC_CMBUSERPAGE, cmbUPage);
	DDX_Control(pDX, IDC_CMBPETPAGE, cmbPetPage);
	DDX_Control(pDX, IDC_EDITUSERNAME, editUserName);
	DDX_Control(pDX, IDC_CMBPETNAME, cmbPet);
	DDX_Control(pDX, IDC_EDITNOWLEVEL, m_NowLevel);
}


BEGIN_MESSAGE_MAP(CCG2PetManage, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListUser)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListUser)

	ON_NOTIFY(NM_CLICK, IDC_LISTPET, OnNMClickListPet)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTPET, OnNMDblclkListPet)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNCONFIRM, OnBnClickedBtnconfirm)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CCG2PetManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符	

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//初始化一些私有变量

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置

		if(listPet.m_hWnd!=NULL)
		{
			listPet.MoveWindow(newRect);//设置好listResult的位置，listResult和listUser的位置完全重叠
		}
	}

	ShowUpdatePet(SW_HIDE);
	ShowAddPet(SW_HIDE);
	ShowUpdatePetLevel(SW_HIDE);
	

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//当前的状态为初始建立对话框

	theApp.operCG2.GetServerList();//请求所有的游戏服务器列表
	::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

	return TRUE;
}

// 初始化显示字符
void CCG2PetManage::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_ItemInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));


	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgPetInfo"));
	tbcResult.InsertItem(2,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgUpdatePet"));
	tbcResult.InsertItem(3,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgAddPet"));
	tbcResult.InsertItem(4,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgUpdatePetLevel"));
}


// 自动改变大小
void CCG2PetManage::OnSize(UINT nType, int cx, int cy)
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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置

		if(listPet.m_hWnd!=NULL)
		{
			listPet.MoveWindow(newRect);//设置好listPet的位置
		}
	}
}

//设置背景颜色
HBRUSH CCG2PetManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CCG2PetManage::OnBnClickedUisearch()
{
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;		

		tbcResult.SetCurSel(0);

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容
		
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);


		UpdateData(true);			

		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//获取玩家帐号
		GetDlgItemText(IDC_EDITUINICK,UserNick);//获取玩家昵称
		if((UserName == "") && (UserNick == ""))//玩家帐号和玩家昵称不能同时为空
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_InputAccount"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    UserInfo();// 查询玩家资料信息
	}
	catch(...)
	{
	}
}

// 查询玩家资料信息
void CCG2PetManage::UserInfo()
{	
	//OperationCG2 theApp.operCG2;
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//查询第一页的信息
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

		nItem = -1;//玩家资料列表没有选定项
		pageUInfo = false;//玩家资料列表不能翻页	
		cmbUPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query);//发送查询玩家资料信息的请求

		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 翻页查询玩家资料信息
void CCG2PetManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//如果可以翻页的话
		{
			CIni mIni;
			//OperationCG2 theApp.operCG2;	
			
			int index = cmbUPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//每页显示50条记录

			while(listUser.DeleteColumn(0)){}//清除页面内容

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query );//发送查询玩家资料信息的请求

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// 单击用户列表保存当前行号
void CCG2PetManage::OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
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
			nItem = -1;
		}
	}
	*pResult = 0;
}

// 双击玩家资料信息进行查询
void CCG2PetManage::OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() > 0)
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

				CIni mIni;
				pagePetInfo = false;
				cmbPetPage.ResetContent();
				while(listPet.DeleteColumn(0)){}// 清除结果列表中的所有内容
				

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);



				GetDlgItem(IDC_LISTPET)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_SHOW);



				//OperationCG2 theApp.operCG2;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			    UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称

				PetInfo();// 查询角色详细资料
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}
// 单击宠物列表保存当前行号
void CCG2PetManage::OnNMClickListPet(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 1)
	{
		if(listPet.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listPet.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nPetItem = listPet.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
		}
		else
		{
			nPetItem = -1;
		}
	}
	*pResult = 0;
}

// 双击宠物信息进行查询
void CCG2PetManage::OnNMDblclkListPet(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 1)
	{
		if(listPet.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listPet.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nPetItem = listPet.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nPetItem >= 0)
			{
				tbcResult.SetCurSel(2);

				CIni mIni;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
				PetID=atoi(theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetID")));

				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);

				ShowAddPet(SW_HIDE);
				ShowUpdatePetLevel(SW_HIDE);
				ShowUpdatePet(SW_SHOW);
				
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
void CCG2PetManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowUpdatePet(SW_HIDE);
			ShowAddPet(SW_HIDE);
			ShowUpdatePetLevel(SW_HIDE);

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		}
		break;
	case 1:
		{
			ShowUpdatePet(SW_HIDE);
			ShowAddPet(SW_HIDE);
			ShowUpdatePetLevel(SW_HIDE);

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_SHOW);


			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				PetInfo();// 查询角色属性资料
			}

		}
		break;
	case 2:
		{
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);
			
			ShowAddPet(SW_HIDE);
			ShowUpdatePetLevel(SW_HIDE);
			ShowUpdatePet(SW_SHOW);
			

		}
		break;
	case 3:
		{
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);

			
			ShowUpdatePetLevel(SW_HIDE);
			ShowUpdatePet(SW_HIDE);
			ShowAddPet(SW_SHOW);

			PetListQuery();
		}
		break;
	case 4:
		{
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTPET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPETPAGE)->ShowWindow(SW_HIDE);

			ShowUpdatePet(SW_HIDE);
			ShowAddPet(SW_HIDE);
			ShowUpdatePetLevel(SW_SHOW);
			
		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

// 宠物基本资料
void CCG2PetManage::PetInfo()
{
	//OperationCG2 theApp.operCG2;	
	try
	{		
		CIni mIni;
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		nPetItem = -1;//玩家资料列表没有选定项
		pagePetInfo = false;//玩家资料列表不能翻页	
		cmbPetPage.ResetContent();//清除玩家资料列表翻页的复选框
		while(listPet.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetInfo_Query );

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_LEVELEXP"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 宠物技能信息
void CCG2PetManage::PetSkill()
{
	//OperationCG2 theApp.operCG2;
	
	try
	{		
		CIni mIni;
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

			_itoa(PetID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_PetID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetSkill_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}


//  更新宠物属性
void CCG2PetManage::UpdatePet()
{
	//OperationCG2 theApp.operCG2;

	try
	{		
		CIni mIni;

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");
		int cg2_charno=0;
		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,20);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
			cg2_charno=atoi(theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharNo")));

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

			_itoa(cg2_charno,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID



			if((listPet.GetItemCount() > 0) && (nPetItem>=0))
			{
				PetID=atoi(theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetID")));
				PetName=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetSrcName"));
				int	 PetAttr0=GetDlgItemInt(IDC_EDITPETATTR0);
				int  PetAttr1=GetDlgItemInt(IDC_EDITPETATTR1);
				int  PetAttr2=GetDlgItemInt(IDC_EDITPETATTR2);
				int  PetAttr3=GetDlgItemInt(IDC_EDITPETATTR3);
				int  PetAttr4=GetDlgItemInt(IDC_EDITPETATTR4);

				_itoa(PetID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSrcName,CEnumCore::TagFormat::TLV_STRING,strlen(PetName),(unsigned char *)mIni.wcharToChar(PetName));//玩家IDKEY
				_itoa(PetAttr0,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetPhysical,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID
				_itoa(PetAttr1,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetPower,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID
				_itoa(PetAttr2,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSmart,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID
				_itoa(PetAttr3,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSpeed,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID
				_itoa(PetAttr4,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSpirit,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID


			}



			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Update_Pet_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}
//宠物列表
void CCG2PetManage::PetListQuery()
{
	//OperationCG2 theApp.operCG2;

	try
	{		
		CIni mIni;

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY


			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetList_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}
// 添加宠物
void CCG2PetManage::AddPet()
{
	//OperationCG2 theApp.operCG2;

	try
	{		
		CIni mIni;

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];
			int cg2_charno=0;

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
			cg2_charno=atoi(theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharNo")));

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

			_itoa(cg2_charno,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID

		

			CString strPetID;
			GetDlgItemText(IDC_CMBPETNAME,PetName);//获取游戏服务器的名称
			PetList.Lookup(cmbPet.GetCurSel()+1,strPetID);//从CMap类的对象ServerList中获取游戏服务器的IP

			PetID=atoi(strPetID);
			_itoa(PetID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_PetID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID

			socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSrcName,CEnumCore::TagFormat::TLV_STRING,strlen(PetName),(unsigned char *)mIni.wcharToChar(PetName));//宠物名称

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_AddPet_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}


// 宠物技能信息
void CCG2PetManage::UpdatePetLevel()
{
	//OperationCG2 theApp.operCG2;

	try
	{		
		CIni mIni;

		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");
		int cg2_charno=0;
		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// 保存选中的玩家ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// 保存选中的玩家昵称
			cg2_charno=atoi(theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharNo")));

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

			_itoa(cg2_charno,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID

			if((listPet.GetItemCount() > 0) && (nPetItem>=0))
			{
				PetID=atoi(theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetID")));
				PetName=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetSrcName"));
				int  NewPetLevel=GetDlgItemInt(IDC_EDITPETATTR2);



				_itoa(PetID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID
				socketdata.AddTFLV(CEnumCore::TagName::CG2_PetSrcName,CEnumCore::TagFormat::TLV_STRING,strlen(PetName),(unsigned char *)mIni.wcharToChar(PetName));//玩家IDKEY
				_itoa(NewPetLevel,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::CG2_Level,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//宠物ID


			}

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

			int midlength = socketdata.EnBody();
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_UpdatePetLevel_Query);

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Item"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}


// 翻页进行查询
void CCG2PetManage::OnCbnSelchangeCmbuipage()
{
	//OperationCG2 theApp.operCG2;	
	try
	{
		if(pageInfo)
		{
			CIni mIni;
			
			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");


			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
				socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
				socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//玩家IDKEY

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

				
				
				int midlength = socketdata.EnBody();				
				if(tbcResult.GetCurSel() == 1)
				{
					theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetInfo_Query);// 查询角色详细资料
				}
				else if(tbcResult.GetCurSel() == 2)
				{
					theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_PetSkill_Query);// 查询角色属性资料
				}
				
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//当前的状态为发送查询请求
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// 接收返回信息
LRESULT CCG2PetManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
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
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://查询玩家资料信息的回应
		{
			if(pageUInfo)//如果已经能够翻页
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					nItem = -1;//不能选中某一行
					pageUInfo = false;//不能翻页					
					cmbUPage.ResetContent();//清空页数复选框
					while(listUser.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nItem = 0;
					cmbUPage.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUPage.AddString(str);//在复选框中构造页数信息
					}
					cmbUPage.SetCurSel(0);//在复选框中选中第一页
					if(pageCount == 1)
					{
						pageUInfo = false;//只有一页数据，不能翻页
					}
					else
					{
						pageUInfo = true;//有多页数据，可以翻页
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetInfo_Query_Resp://查询宠物信息的回应
		{
			if(pagePetInfo)//如果已经能够翻页
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listPet,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listPet,&pageCount);//构造CListCtrl对象

				if(pageCount<0)//页数<=0，说明没有数据返回
				{
					nPetItem = -1;//不能选中某一行
					pagePetInfo = false;//不能翻页					
					cmbPetPage.ResetContent();//清空页数复选框
					while(listPet.DeleteColumn(0)){}//清空CListCtrl内容
				}
				else
				{
					nPetItem = 0;
					cmbPetPage.ResetContent();//清空页数复选框，以便重新构造
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPetPage.AddString(str);//在复选框中构造页数信息
					}
					cmbPetPage.SetCurSel(0);//在复选框中选中第一页
					if(pageCount == 1)
					{
						pagePetInfo = false;//只有一页数据，不能翻页
					}
					else
					{
						pagePetInfo = true;//有多页数据，可以翻页
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_PetList_Query_Resp://宠物列表
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString strPetID=(LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::CG2_PetID).lpdata;
				PetList.SetAt(i,strPetID);//将服务器IP保存在CMap类的对象ServerList中
			}
			theApp.operCG2.BuildPetCombox(&socketdata,&cmbPet);
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//显示操作结果
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// 关闭对话框
void CCG2PetManage::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");

}

// 关闭对话框
void CCG2PetManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}



//更改宠物属性,添加宠物,更改宠物等级
void CCG2PetManage::OnBnClickedBtnconfirm()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(tbcResult.GetCurSel())
	{
	case 2:
		UpdatePet();
		break;
	case 3:
		AddPet();
		break;
	case 4:
		UpdatePetLevel();
		break;
	}
}

void CCG2PetManage::ShowUpdatePet(int n_cmdShow)
{
	GetDlgItem(IDC_LBLUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLNOWLEVEL)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETATTR3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETATTR4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR0)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR1)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR3)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR4)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNCONFIRM)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(n_cmdShow);

	SetDlgItemText(IDC_LBLUSERNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR0"));
	SetDlgItemText(IDC_LBLNOWLEVEL,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR1"));
	SetDlgItemText(IDC_LBLPETNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR2"));
	SetDlgItemText(IDC_LBLPETATTR3,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR3"));
	SetDlgItemText(IDC_LBLPETATTR4,theApp.operCG2.ReadValue("MCG2","BU_UI_PETATTR4"));
	SetDlgItemText(IDC_BTNCONFIRM,theApp.operCG2.ReadValue("MCG2","BU_UI_CHANGEPETATTR"));
	SetDlgItemText(IDC_BTNRESET,theApp.operCG2.ReadValue("MCG2","BU_UI_RESET"));
	if((listPet.GetItemCount() > 0) && (nPetItem>=0))
	{
		CString PetAttr0=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetPhysical"));
		CString PetAttr1=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Power"));
		CString PetAttr2=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Smart"));
		CString PetAttr3=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Speed"));
		CString PetAttr4=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Spirit"));
		SetDlgItemText(IDC_EDITPETATTR0,PetAttr0);
		SetDlgItemText(IDC_EDITPETATTR1,PetAttr1);
		SetDlgItemText(IDC_EDITPETATTR2,PetAttr2);
		SetDlgItemText(IDC_EDITPETATTR3,PetAttr3);
		SetDlgItemText(IDC_EDITPETATTR4,PetAttr4);

	}
}

void CCG2PetManage::ShowAddPet(int n_cmdShow)
{
	GetDlgItem(IDC_LBLUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CMBPETNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNCONFIRM)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(n_cmdShow);

	SetDlgItemText(IDC_LBLUSERNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_USERNAME"));
	SetDlgItemText(IDC_LBLPETNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_PETNAME"));
	SetDlgItemText(IDC_BTNCONFIRM,theApp.operCG2.ReadValue("MCG2","BU_UI_ADDPET"));
	SetDlgItemText(IDC_BTNRESET,theApp.operCG2.ReadValue("MCG2","BU_UI_RESET"));
	if((listUser.GetItemCount() > 0) && (nItem>=0))
	{
		UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// 保存选中的玩家帐号
		SetDlgItemText(IDC_EDITUSERNAME,UserName);
		editUserName.SetReadOnly(true);
	}

}

void CCG2PetManage::ShowUpdatePetLevel(int n_cmdShow)
{
	GetDlgItem(IDC_LBLUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITUSERNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLNOWLEVEL)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITNOWLEVEL)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_LBLPETNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDITPETATTR2)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNCONFIRM)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(n_cmdShow);

	SetDlgItemText(IDC_LBLUSERNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_PETNAME"));
	SetDlgItemText(IDC_LBLNOWLEVEL,theApp.operCG2.ReadValue("MCG2","BU_UI_NOWLEVEL"));
	SetDlgItemText(IDC_LBLPETNAME,theApp.operCG2.ReadValue("MCG2","BU_UI_NEWLEVEL"));
	SetDlgItemText(IDC_BTNCONFIRM,theApp.operCG2.ReadValue("MCG2","BU_UI_CHANGELEVEL"));
	SetDlgItemText(IDC_BTNRESET,theApp.operCG2.ReadValue("MCG2","BU_UI_RESET"));
	if((listPet.GetItemCount() > 0) && (nPetItem>=0))
	{
		PetName = theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_PetSrcName"));// 保存选中的宠物
		CString nowLevel=theApp.operCG2.GetValueByColName(&listPet, nPetItem, theApp.operCG2.ReadValue("MCG2","CG2_Level"));
		SetDlgItemText(IDC_EDITUSERNAME,PetName);
		SetDlgItemText(IDC_EDITNOWLEVEL,nowLevel);
		SetDlgItemText(IDC_EDITPETATTR2,nowLevel);
		editUserName.SetReadOnly(true);
		m_NowLevel.SetReadOnly(true);
	}
}
//重置一切
void CCG2PetManage::OnBnClickedBtnreset()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(tbcResult.GetCurSel())
	{
	case 2:
		ShowUpdatePet(SW_SHOW);
		break;
	case 3:
		ShowAddPet(SW_SHOW);
		break;
	case 4:
		ShowUpdatePetLevel(SW_SHOW);
		break;
	}
}
