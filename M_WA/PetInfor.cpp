// PetInfor.cpp : 实现文件
//

#include "stdafx.h"
#include "M_WA.h"
#include "PetInfor.h"
#include ".\PetInfor.h"


// PetInfor 对话框

IMPLEMENT_DYNAMIC(PetInfor, CDialog)
PetInfor::PetInfor(CWnd* pParent /*=NULL*/)
: CDialog(PetInfor::IDD, pParent)
{
}

PetInfor::~PetInfor()
{
}

void PetInfor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	//DDX_Control(pDX, IDC_CMBQUESTTYPE, cmbQuestType);
	DDX_Control(pDX, IDC_CMSEARCHTYPE, cmbQuestType);
}


BEGIN_MESSAGE_MAP(PetInfor, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	//ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListhuizhanginfo)
	//ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListhuizhanginfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
END_MESSAGE_MAP()


// PetInfor 消息处理程序
// 初始化对话框
BOOL PetInfor::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符	
	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//初始化一些私有变量

	//ShowUserInfo();//显示用户资料信息

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
	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}

	if(theApp.operWA.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
	}

	return TRUE;
}
HBRUSH PetInfor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}
// 初始化显示字符
VOID PetInfor::InitUI()
{

	tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","UIC_UI_tpgUserInfo"));
	//tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","HUIZHANG"));
	tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","PI_UI_tpgPetInfo"));
	//InitQuestType();



	///////////////////////////
	//////////////////////////
	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));

	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLSELFTYPE,theApp.operWA.ReadValue("MWA","UIC_UI_SelfType"));
	/////////////////////////
	////////////////////////

}
// 查询玩家资料信息
void PetInfor::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		ShowUserInfo();
		int index = theApp.operWA.ReadIntValue("MWA","index");//查询第一页的信息
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容
		//MessageBox("test");
		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称

		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
		//MessageBox(ServerIP);
		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//获取玩家帐号
		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家角色名
		//MessageBox(UserName);
		if((UserName == "") && (UserAccount == ""))//玩家帐号和玩家角色名不能同时为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_InputAccount"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,7);//共有六个参数，服务器IP、玩家帐号、玩家角色名、查找类型、页数、每页的记录条数\\、服务器Name
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
		//socketdata.AddTFLV(CEnumCore::TagName::WA_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(SearchType),(unsigned char *)mIni.wcharToChar(SearchType));//查找类型
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();

		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query))//发送查询玩家资料信息的请求
		{

			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

		}

		socketdata.Destroy();//销毁CSocketData局部变量

	}
	catch(...)
	{
	}
}

// 单击用户列表保存当前行号
void PetInfor::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
		}
		else
		{
			nItem = 0;
		}
	}

	*pResult = 0;
}

// 双击玩家资料信息进行查询
void PetInfor::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationWA operWA;
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
								
				
               
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

				UserAccount = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_ACCOUNT"));
				UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));
                PetList();
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
			}
		}
		else
		{
			nItem = 0;
		}
	}

	*pResult = 0;
}
// 单击徽章列表保存当前行号
//void PetInfor::OnNMClickListhuizhanginfo(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	if(tbcResult.GetCurSel() == 1)
//	{
//		if(listResult.GetItemCount() > 0)
//		{
//			DWORD dwPos = GetMessagePos();
//			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
//
//			listResult.ScreenToClient(&point);
//
//			LVHITTESTINFO lvinfo;
//			lvinfo.pt = point;
//			lvinfo.flags = LVHT_ABOVE;
//
//			nItemresult = listResult.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
//		}
//		else
//		{
//			nItemresult = 0;
//		}
//	}
//	*pResult = 0;
//}

// 双击徽章信息进行查询
//void PetInfor::OnNMDblclkListhuizhanginfo(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	//OperationWA operWA;
//	if(tbcResult.GetCurSel() == 1)
//	{
//		if(listResult.GetItemCount() > 0)
//		{
//			DWORD dwPos = GetMessagePos();
//			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
//
//			listResult.ScreenToClient(&point);
//
//			LVHITTESTINFO lvinfo;
//			lvinfo.pt = point;
//			lvinfo.flags = LVHT_ABOVE;
//
//			nItemresult = listResult.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号
//
//			if(nItemresult >= 0)
//			{
//				tbcResult.SetCurSel(2);
//				pageInfo = false;
//				cmbPage.ResetContent();
//				
//               // CString huizhang;
//				UserAccount = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_ACCOUNT"));
//				UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));//WA_medalPetIndex
//				WA_medalPetIndex = theApp.operWA.GetValueByColName(&listResult, nItemresult, theApp.operWA.ReadValue("MWA","WA_medalPetIndex"));
//				while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容
//				CString temp;
//				temp.Format("%s",WA_medalPetIndex);
//				//MessageBox(WA_medalPetIndex);
//				//EmblemList();
//				PetList();
//				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
//				GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
//			}
//		}
//		else
//		{
//			nItemresult = 0;
//		}
//	}
//
//	*pResult = 0;
//}

// 切换选项卡进行查询
void PetInfor::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationWA operWA;
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//显示用户资料信息
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	}
	else
	{
		//ShowOtherInfo();

		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{

			UserAccount = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_ACCOUNT"));
			UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));

			//if(tbcResult.GetCurSel()==1)
			//{
			//	EmblemList();//查询玩家徽章信息
			//	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			//	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
			//}
			if(tbcResult.GetCurSel()==1)
			{
				CString temp;
				temp.Format("%d",listResult.GetItemCount());
				//MessageBox(temp);
				if(listResult.GetItemCount()<=0)
				{
					return;
				}
				PetList();//查询玩家宠物属性
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
			}
		}
	}

	*pResult = 0;
}

//查询玩家徽章信息
void PetInfor::EmblemList()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();

		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_EmblemInfo_Query))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_FriendList"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}
//查询玩家宠物信息
void PetInfor::PetList()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");
       
		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
        socketdata.AddTFLV(CEnumCore::TagName::WA_medalPetIndex,CEnumCore::TagFormat::TLV_STRING,strlen(WA_medalPetIndex),(unsigned char *)mIni.wcharToChar(WA_medalPetIndex));//玩家帐号
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数
		int midlength = socketdata.EnBody();

		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_PetInfo_Query))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
			}




		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_FriendList"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 翻页进行查询
void PetInfor::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录
			int iQuestType=cmbQuestType.GetCurSel()+1;

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,7);//共有六个参数，服务器IP、玩家帐号、玩家角色名、查找类型、页数、每页的记录条数\\、服务器Name
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
			//			socketdata.AddTFLV(CEnumCore::TagName::WA_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(SearchType),(unsigned char *)mIni.wcharToChar(SearchType));//查找类型
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


			if(tbcResult.GetCurSel()==0)
			{
				midlength = socketdata.EnBody();
				if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query))
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
					dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
				}
			}
			//if(tbcResult.GetCurSel()==1)
			//{
			//	midlength = socketdata.EnBody();
			//	if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_EmblemInfo_Query))
			//	{
			//		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			//		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
			//	}
			//}
			if(tbcResult.GetCurSel()==1)
			{
				socketdata.AddTFLV(CEnumCore::TagName::WA_medalPetIndex,CEnumCore::TagFormat::TLV_STRING,strlen(WA_medalPetIndex),(unsigned char *)mIni.wcharToChar(WA_medalPetIndex));//宠物序号
				midlength = socketdata.EnBody();
				if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_PetInfo_Query))
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
					dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
				}
			}

			socketdata.Destroy();//销毁CSocketData局部变量

		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Page"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

//初始化任务类型
void PetInfor::InitQuestType(void)
{
	cmbQuestType.ResetContent();
	cmbQuestType.AddString(theApp.operWA.ReadValue("MWA","WA_SEARCHTYPE1"));
	cmbQuestType.AddString(theApp.operWA.ReadValue("MWA","WA_SEARCHTYPE2"));
	cmbQuestType.AddString(theApp.operWA.ReadValue("MWA","WA_SEARCHTYPE3"));
	cmbQuestType.AddString(theApp.operWA.ReadValue("MWA","WA_SEARCHTYPE4"));
	cmbQuestType.SetCurSel(0);
}

// 自动改变大小
void PetInfor::OnSize(UINT nType, int cx, int cy)
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

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//设置好listResult的位置
	}

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}
}

// 接收socket返回信息
LRESULT PetInfor::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,ServerIP);//将服务器IP保存在CMap类的对象ServerList中
				//MessageBox(ServerIP);
			}
			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://查询玩家资料信息的回应
		//case CEnumCore::Message_Tag_ID::WA_EmblemInfo_Query_Resp://查询玩家徽章的回应
		//case CEnumCore::Message_Tag_ID::WA_PetInfo_Query_Resp://查询玩家宠物的回应
		{

			if(pageInfo)//如果已经能够翻页
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
				if(pageCount<=0)//页数<=0，说明没有数据返回
				{
					pageInfo = false;//不能翻页		
					cmbPage.ResetContent();
					while(listUser.DeleteColumn(0)){}
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
			break;
			//case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://查询玩家资料信息的回应
	case CEnumCore::Message_Tag_ID::WA_EmblemInfo_Query_Resp://查询玩家徽章的回应
	case CEnumCore::Message_Tag_ID::WA_PetInfo_Query_Resp://查询玩家宠物的回应
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
			break;
		}
		}

	default:
		break;
	}

	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}
// 显示角色资料信息
void PetInfor::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLQUESTTYPE)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_CMBQUESTTYPE)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
}

// 显示好友列表信息
void PetInfor::ShowFriendInfo(void)
{
	tbcResult.SetCurSel(1);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLQUESTTYPE)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_CMBQUESTTYPE)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
}


//处理快捷键响应函数
BOOL PetInfor::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operXD;
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //判断是否有按键按下
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
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
			}
		}		
	}
	return FALSE;
}


