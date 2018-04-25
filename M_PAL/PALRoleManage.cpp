// PALRoleManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALRoleManage.h"
#include ".\palrolemanage.h"


// CPALRoleManage 对话框

IMPLEMENT_DYNAMIC(CPALRoleManage, CDialog)
CPALRoleManage::CPALRoleManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPALRoleManage::IDD, pParent)
{
}

CPALRoleManage::~CPALRoleManage()
{
}

void CPALRoleManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
	DDX_Control(pDX, IDC_EDITSRC, txtSrc);
	DDX_Control(pDX, IDC_EDITNEW, txtNew);
	DDX_Control(pDX, IDC_CMBQUESTSTATUS, cmbStatus);
	DDX_Control(pDX, IDC_CMBSTATUS, cmbNewStatus);
}


BEGIN_MESSAGE_MAP(CPALRoleManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDC_BTNMODIQUEST, OnBnClickedBtnmodiquest)
	ON_BN_CLICKED(IDC_BTNMODI, OnBnClickedBtnmodi)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBQUESTSTATUS, OnCbnSelchangeCmbqueststatus)
	ON_CBN_SELCHANGE(IDC_CMBTYPE, OnCbnSelchangeCmbtype)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
END_MESSAGE_MAP()


// 初始化对话框
BOOL CPALRoleManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符

	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//初始化一些私有变量
	QuestNum = 0;
	iQuestType = 0;

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

	GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);

	return TRUE;
}

// 初始化显示字符
void CPALRoleManage::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","RM_UI_RoleManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDC_LBLQUESTSTATUS,theApp.operPAL.ReadValue("MPAL","RM_UI_QuestStatus"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));

	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLQUESTNAME,theApp.operPAL.ReadValue("MPAL","RM_UI_QuestName"));
	SetDlgItemText(IDC_LBLSTATUS,theApp.operPAL.ReadValue("MPAL","RM_UI_QuestStatus"));
	SetDlgItemText(IDC_BTNMODIQUEST,theApp.operPAL.ReadValue("MPAL","RM_UI_BtnModiQuest"));

	SetDlgItemText(IDC_LBLROLENAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","Modify"));
	SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","Reset"));

	SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_PwdType"));
	SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_TmpPwd"));
	SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_ReTmpPwd"));
	SetDlgItemText(IDC_LBLHINT,"");

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","RM_UI_tpgModiTmpPwd"));
	tbcResult.InsertItem(2,theApp.operPAL.ReadValue("MPAL","RM_UI_tpgModiMoney"));
	tbcResult.InsertItem(3,theApp.operPAL.ReadValue("MPAL","RM_UI_tpgModiQuest"));
	tbcResult.InsertItem(4,theApp.operPAL.ReadValue("MPAL","RM_UI_tpgSafeLock"));


}

//处理快捷键响应函数
BOOL CPALRoleManage::PreTranslateMessage(MSG* pMsg)
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

// 自动改变大小
void CPALRoleManage::OnSize(UINT nType, int cx, int cy)
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
}

//设置背景颜色
HBRUSH CPALRoleManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 查询玩家资料信息
void CPALRoleManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;

		ShowUserInfo();

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//查询第一页的信息
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容

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
		socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERINFO))//发送查询玩家资料信息的请求
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
void CPALRoleManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
void CPALRoleManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				//OperationPAL operPAL;
				tbcResult.SetCurSel(1);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);

				InitPwdType();//初始化要修改的密码类型
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_PwdType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_TmpPwd"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_ReTmpPwd"));
				SetDlgItemText(IDC_LBLHINT,"");

				UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
				UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名

				SetDlgItemText(IDC_EDITROLENAME,UserName);//显示玩家角色名

				if (cmbType.GetCurSel() == 0)
				{
					GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_SHOWNORMAL);
				}

			}
			else
			{
				nItem = 0;
			}
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// 切换选项卡进行操作
void CPALRoleManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operPAL;
	GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);

	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//显示用户资料信息
	}
	else
	{
		nQuestItem = -1;
		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// 清除结果列表中的所有内容

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// 保存选中的玩家帐号
			UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// 保存选中的玩家角色名

			if(tbcResult.GetCurSel()==1)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);

				InitPwdType();//初始化要修改的密码类型
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_PwdType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_TmpPwd"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_ReTmpPwd"));
				SetDlgItemText(IDC_LBLHINT,"");

				SetDlgItemText(IDC_EDITROLENAME,UserName);//显示玩家角色名
				if (cmbType.GetCurSel() == 0)
				{
					GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_SHOWNORMAL);
				}

			}
			else if(tbcResult.GetCurSel()==2)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);				
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);
				GetDlgItem(IDC_LBLHINT)->ShowWindow(SW_HIDE);	
				
				InitMoneyType();//初始化文钱类型复选框
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_MoneyType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_OwnMoney"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_NewMoney"));
				CString srcMoney;
				srcMoney = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_BODYMONEY"));// 保存玩家身上的文钱数

				SetDlgItemText(IDC_EDITROLENAME,UserName);//显示玩家角色名
				SetDlgItemText(IDC_EDITSMONEY,srcMoney);//显示玩家拥有的金钱数
			}
			else if(tbcResult.GetCurSel()==3)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_HIDE);
				ShowQuestTab(SW_SHOW,2);

				InitQuestType();//初始化任务类型
				QuestInfo();//查询玩家任务信息
			}
			else if(tbcResult.GetCurSel()==4)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_HIDE);
				ShowQuestTab(SW_HIDE,1);

				GetDlgItem(IDC_EDITROLENAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLROLENAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNMODI)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);
				
				SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","RM_UI_USESAFTLOCK"));
				SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RM_UI_FREESAFTLOCK"));


				SetDlgItemText(IDC_EDITROLENAME,UserName);//显示玩家角色名
			}

		}
		else
		{
			if(tbcResult.GetCurSel()==1)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);

				InitPwdType();//初始化要修改的密码类型
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_PwdType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_TmpPwd"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_ReTmpPwd"));
				SetDlgItemText(IDC_LBLHINT,"");
	            //SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","RM_UI_HintDeleteRolePwd"));
				SetDlgItemText(IDC_EDITROLENAME,"");//显示玩家角色名为空
			}
			else if(tbcResult.GetCurSel()==2)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);				
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);
				GetDlgItem(IDC_LBLHINT)->ShowWindow(SW_HIDE);	
				
				InitMoneyType();//初始化文钱类型复选框
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_MoneyType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_OwnMoney"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_NewMoney"));
				SetDlgItemText(IDC_EDITROLENAME,"");//显示玩家角色名为空
				SetDlgItemText(IDC_EDITSMONEY,"");//显示玩家拥有的金钱数
			}
			else if(tbcResult.GetCurSel()==3)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_HIDE);
				ShowQuestTab(SW_SHOW,2);

				InitQuestType();//初始化任务类型
				SetDlgItemText(IDC_EDITROLENAME,"");//显示玩家角色名为空
			}
			else if(tbcResult.GetCurSel()==4)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_HIDE);
				ShowQuestTab(SW_HIDE,1);

				GetDlgItem(IDC_EDITROLENAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLROLENAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNMODI)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);
				
				SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","RM_UI_USESAFTLOCK"));
				SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RM_UI_FREESAFTLOCK"));
				

				SetDlgItemText(IDC_EDITROLENAME,"");//显示玩家角色名为空
			}
		}
	}
	*pResult = 0;
}

//切换不同类型
void CPALRoleManage::OnCbnSelchangeCmbtype()
{
	//OperationPAL operPAL;
	if(tbcResult.GetCurSel() == 1)
	{
		if(cmbType.GetCurSel() == 0)
		{
			 SetDlgItemText(IDC_LBLHINT,"");
			 GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_SHOWNORMAL);
		}
		else if(cmbType.GetCurSel() == 1)
		{
	        SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","RM_UI_HintDeleteRolePwd"));
			GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);
		}
		else if(cmbType.GetCurSel() == 2)
		{
			SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","RM_UI_HintBanPwd"));
			GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);
		}
		if(cmbType.GetCurSel() == 3)
		{
			 SetDlgItemText(IDC_LBLHINT,"");
			 GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);
		}
	}
	else if(tbcResult.GetCurSel() == 2)
	{
		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			CString srcMoney;				
		    if(cmbType.GetCurSel() == 0)
		    {
				srcMoney = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_BODYMONEY"));// 保存玩家身上的文钱数
		    }
		    else if(cmbType.GetCurSel() == 1)
		    {
				srcMoney = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_BANKMONEY"));// 保存玩家仓库的文钱数
	    	}
			SetDlgItemText(IDC_EDITSMONEY,srcMoney);//显示玩家拥有的金钱数
		}
		else
		{
			SetDlgItemText(IDC_EDITSMONEY,"");//显示玩家拥有的金钱数
		}
	}
}

//查询玩家任务信息
void CPALRoleManage::QuestInfo()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		int iQuestType;		
		CString QuestType = "";
		GetDlgItemText(IDC_CMBQUESTSTATUS,QuestType);
		if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished")))
		{
			iQuestType = 1;
		}
		else if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received")))
		{
			iQuestType = 2;
		}
		else
		{
			iQuestType = 0;
			return;
		}

		nQuestItem = -1;
		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有六个参数，服务器IP、服务器Name、玩家昵称、玩家任务类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(iQuestType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERQUEST))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_QuestInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}		
}

//切换任务类型查询玩家任务信息
void CPALRoleManage::OnCbnSelchangeCmbqueststatus()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{			
			CString QuestType = "";
			GetDlgItemText(IDC_CMBQUESTSTATUS,QuestType);
			if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished")))
			{
				iQuestType = 1;
			}
			else if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received")))
			{
				iQuestType = 2;
			}
			else
			{
				iQuestType = 0;
				return;
			}

			nQuestItem = -1;
			pageInfo=false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//共有六个参数，服务器IP、服务器Name、玩家昵称、玩家任务类型,页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(iQuestType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数


			int midlength = socketdata.EnBody();
			if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERQUEST))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_QuestInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}		
}

// 翻页进行查询
void CPALRoleManage::OnCbnSelchangeCmbpage()
{
	//OperationPAL operPAL;
	try
	{	
		if(pageInfo)//如果可以翻页的话
		{
			CIni mIni;
		
			int index = cmbPage.GetCurSel() + 1;//页数为cmbUPage当前的索引值加1，也就是cmbUPage中当前显示的值
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//每页显示50条记录
			
			nQuestItem = -1;
			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数
			
			switch(tbcResult.GetCurSel())
			{
			case 3:
				{
					CString QuestType = "";
					GetDlgItemText(IDC_CMBQUESTSTATUS,QuestType);
					if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished")))
					{
						iQuestType = 1;
					}
					else if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received")))
					{
						iQuestType = 2;
					}
					else
					{
						iQuestType = 0;
						return;
					}
					_itoa(iQuestType,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
					midlength=socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERQUEST))//发送查询玩家任务信息的请求
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					}
				}
				break;
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_Page"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

//双击任务列表进行修改
void CPALRoleManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 3)
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nQuestItem = listResult.SubItemHitTest(&lvinfo);//保存在玩家资料信息列表中选中的行号

			if(nQuestItem >= 0)
			{
				CIni mIni;
				//OperationPAL operPAL;
				QuestNum = atoi(theApp.operPAL.GetValueByColName(&listResult, nQuestItem, theApp.operPAL.ReadValue("MPAL","PAL_QUESTID")));// 保存选中的任务号

				SetDlgItemText(IDC_EDITQUESTNAME,(LPCSTR)mIni.wcharToChar(theApp.operPAL.GetValueByColName(&listResult, nQuestItem, theApp.operPAL.ReadValue("MPAL","PAL_QUESTID"))));//显示任务号
				InitQuestStatus();
				ShowQuestTab(SW_SHOW,1);				
			}
			else
			{
				SetDlgItemText(IDC_EDITQUESTNAME,"");//任务号为空
				InitQuestType();
				ShowQuestTab(SW_SHOW,2);	
				nQuestItem = -1;
			}
		}
		else
		{
			SetDlgItemText(IDC_EDITQUESTNAME,"");//任务名称为空
			InitQuestType();
			ShowQuestTab(SW_SHOW,2);	
			nQuestItem = -1;
		}
	}
	*pResult = 0;
}

//修改任务类型
void CPALRoleManage::OnBnClickedBtnmodiquest()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		CString QuestName = "";
		GetDlgItemText(IDC_EDITQUESTNAME,QuestName);
		if(QuestName == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_SelectQuest"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int iQuestStatus = 0;	
		CString QuestType = "";
		GetDlgItemText(IDC_CMBSTATUS,QuestType);
		if(QuestType == theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished"))
		{
			iQuestStatus = 1;
		}
		else if(QuestType == theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received"))
		{
			iQuestStatus = 2;
		}
		else
		{
			iQuestStatus = 0;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、玩家任务ID，玩家任务类型,页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(QuestNum,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家任务ID

		_itoa(iQuestStatus,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家任务类型

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYCHARACTERQUEST))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Error_ModiQuestType"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

//修改密码或金钱信息
void CPALRoleManage::OnBnClickedBtnmodi()
{
	//OperationPAL operPAL;
	try
	{				
		CIni mIni;

		GetDlgItemText(IDC_EDITROLENAME,UserName);//获取角色名
		if(UserName == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_RoleNameNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString strNewPwd,strReNewPwd;
		CString sMoney,nMoney;
		int iCount = 0;
		int iType=0;
		if(tbcResult.GetCurSel() == 1)
		{
		    GetDlgItemText(IDC_EDITSRC,strNewPwd);
		    GetDlgItemText(IDC_EDITNEW,strReNewPwd);
		    if(strcmp(strNewPwd,strReNewPwd))
		    {
			    MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_PwdSame"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			    return;
	    	}
		}
		else if(tbcResult.GetCurSel() == 2)
		{
			iType = cmbType.GetCurSel();
			GetDlgItemText(IDC_EDITSMONEY,sMoney);
		    GetDlgItemText(IDC_EDITNMONEY,nMoney);
		    
		    if(nMoney == "")
		    {
			    MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_InputNewMoney"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			    return;
	    	}
			if(sMoney == "")
			{
				iCount=GetDlgItemInt(IDC_EDITNMONEY)-0;
			}
			else
			{
			    iCount=GetDlgItemInt(IDC_EDITNMONEY)-GetDlgItemInt(IDC_EDITSMONEY);
			}
		}


		CSocketData socketdata;
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name,公会名称、页数、每页的记录条数
		char strInt[10];
		int midlength = 0;

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
        socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		switch(tbcResult.GetCurSel())
		{
		case 1:
			{
				if(cmbType.GetCurSel() == 0)
				{
					socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNTPW,CEnumCore::TagFormat::TLV_STRING,strlen(strNewPwd),(unsigned char *)mIni.wcharToChar(strNewPwd));

					int selectStatus = ((CButton*)GetDlgItem(IDC_CHEAK_CITYALL))->GetCheck();
					if (selectStatus == 1)
					{
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYACCOUNTPWALL))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
						}						
					}
					else
					{						
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYACCOUNTPW))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
						}
					}

				}
				else if(cmbType.GetCurSel() == 1)
				{
					socketdata.AddTFLV(CEnumCore::TagName::PAL_DROPROLEPW,CEnumCore::TagFormat::TLV_STRING,strlen(strNewPwd),(unsigned char *)mIni.wcharToChar(strNewPwd));
					midlength = socketdata.EnBody();
		            if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYCHARACTERDROPPW))
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					}
				}
				else if(cmbType.GetCurSel() == 2)
				{
					socketdata.AddTFLV(CEnumCore::TagName::PAL_BANKPW,CEnumCore::TagFormat::TLV_STRING,strlen(strNewPwd),(unsigned char *)mIni.wcharToChar(strNewPwd));
					midlength = socketdata.EnBody();
		            if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYACCOUNTBANKPW))
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					}
				}
				else if(cmbType.GetCurSel() == 3)
				{
					socketdata.AddTFLV(CEnumCore::TagName::PAL_SECONDPW,CEnumCore::TagFormat::TLV_STRING,strlen(strNewPwd),(unsigned char *)mIni.wcharToChar(strNewPwd));
					midlength = socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYSECONDPW))
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					}
				}

			}
			break;
		case 2:
			{
				_itoa(iType,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PAL_MONEYTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

				_itoa(iCount,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PAL_MONEYCOUNT,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYCHARACTERMONEY))
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
				}
			}
			break;
		case 4:
			{
				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_USESAFELOCK))
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
				}
			}
			break;
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_UserInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

//重置信息
void CPALRoleManage::OnBnClickedBtnreset()
{	
	SetDlgItemText(IDC_EDITSRC,"");
	SetDlgItemText(IDC_EDITNEW,"");

	char strInt[10];
	if(tbcResult.GetCurSel() == 1||tbcResult.GetCurSel()==4)
	{
		//OperationPAL operPAL;
		try
		{				
			CIni mIni;

			GetDlgItemText(IDC_EDITROLENAME,UserName);//获取角色名
			if(UserName == "")
			{
				MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_RoleNameNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name,公会名称、页数、每页的记录条数
			int midlength = 0;

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(theApp.UserByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					if(cmbType.GetCurSel() == 0)
					{
						int selectStatus = ((CButton*)GetDlgItem(IDC_CHEAK_CITYALL))->GetCheck();
						if (selectStatus == 1)
						{
							midlength = socketdata.EnBody();
							if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLACCOUNTPWALL))
							{
								::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
								dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
							}
						}
						else
						{
							midlength = socketdata.EnBody();
							if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLACCOUNTPW))
							{
								::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
								dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
							}
						}
					}
					else if(cmbType.GetCurSel() == 1)
					{
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLCHARACTERDROPPW))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
						}
					}
					else if(cmbType.GetCurSel() == 2)
					{
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLACCOUNTBANKPW))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
						}
					}
					else if(cmbType.GetCurSel() == 3)
					{
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLSECONDPW))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
						}
					}
				}
				break;
			case 4:
				{	
					midlength = socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_FREESAFELOCK))
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//当前的状态为发送查询请求
					}

				}
				break;
			}
			socketdata.Destroy();
		}
		catch(...)
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_UserInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
		}
	}
}

// 接收返回信息
LRESULT CPALRoleManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://查询玩家资料信息的回应
		{
			theApp.operPAL.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERQUEST_RESP://查询玩家任务回应
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
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTPW_RESP://修改角色游戏密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTPW_RESP://恢复角色游戏密码的回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERDROPPW_RESP://修改角色删除密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLCHARACTERDROPPW_RESP://恢复角色删除密码的回应	
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTBANKPW_RESP://修改角色银行密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTBANKPW_RESP://恢复角色银行密码的回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERMONEY_RESP://修改角色金钱的回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERQUEST_RESP://修改角色人物状态的回应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYSECONDPW_RESP://修改二级密码的回应
	case CEnumCore::Message_Tag_ID::PAL_RECALLSECONDPW_RESP://恢复二级密码的回应
	case CEnumCore::Message_Tag_ID::PAL_USESAFELOCK_RESP://使用安全锁
	case CEnumCore::Message_Tag_ID::PAL_FREESAFELOCK_RESP://释放安全锁响应
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTPWALL_RESP://修改全区临时密码
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTPWALL_RESP://修改全区临时密码
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//显示返回结果

			SetDlgItemText(IDC_EDITSRC,"");
			SetDlgItemText(IDC_EDITNEW,"");
			SetDlgItemText(IDC_EDITNMONEY,"");
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
void CPALRoleManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//单击结果信息的列名进行排序
void CPALRoleManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// 关闭对话框
void CPALRoleManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// 关闭对话框
void CPALRoleManage::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// 初始化密码类型复选框
void CPALRoleManage::InitPwdType(void)
{
	//OperationPAL operPAL;
	cmbType.ResetContent();
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_GAMETMPPWD"));
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_DELETEROLEPWD"));
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_BANKTMPPWD"));
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_SECONDPWD"));
	cmbType.SetCurSel(0);
	SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","RM_UI_HintDeleteRolePwd"));
}

// 初始化文钱类型复选框
void CPALRoleManage::InitMoneyType(void)
{
	//OperationPAL operPAL;
	cmbType.ResetContent();
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_PERSONALMONEY"));
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_MONEYINBANK"));
	cmbType.SetCurSel(0);	
}

//初始化任务类型
void CPALRoleManage::InitQuestType(void)
{
	//OperationPAL operPAL;
	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operPAL.ReadValue("MPAL","UIC_ITEM_Finished"));
	cmbStatus.AddString(theApp.operPAL.ReadValue("MPAL","UIC_ITEM_Received"));
	cmbStatus.SetCurSel(0);
}

// 初始化要修改的任务类型复选框
void CPALRoleManage::InitQuestStatus(void)
{
	//OperationPAL operPAL;
	cmbNewStatus.ResetContent();
	cmbNewStatus.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_UnReceived"));
	cmbNewStatus.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished"));
	cmbNewStatus.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received"));
	cmbNewStatus.SetCurSel(0);
}

// 显示角色资料信息
void CPALRoleManage::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	ShowQuestTab(SW_HIDE,1);
	ShowOperTab(SW_HIDE);
}

// 显示操作页面
void CPALRoleManage::ShowOperTab(int m_cmdShow)
{
	//OperationPAL operPAL;
	GetDlgItem(IDC_LBLROLENAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITROLENAME)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLSRC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNMODI)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLHINT)->ShowWindow(m_cmdShow);
	if(tbcResult.GetCurSel() == 1)
	{
		GetDlgItem(IDC_EDITSRC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITNEW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITSMONEY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNMONEY)->ShowWindow(SW_HIDE);
		SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","RM_ITEM_MODITMPPWD"));
		SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RM_ITEM_RECOVERTMPPWD"));
	}
	else if(tbcResult.GetCurSel() == 2)
	{
		GetDlgItem(IDC_EDITSRC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNEW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITSMONEY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITNMONEY)->ShowWindow(SW_SHOW);
		SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","RM_ITEM_MODIMONEY"));
		SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RESET"));
	}
	else
	{
		GetDlgItem(IDC_EDITSRC)->ShowWindow(m_cmdShow);
		GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
		GetDlgItem(IDC_EDITSMONEY)->ShowWindow(m_cmdShow);
		GetDlgItem(IDC_EDITNMONEY)->ShowWindow(m_cmdShow);
		SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RESET"));
	}
	SetDlgItemText(IDC_EDITSRC,"");
	SetDlgItemText(IDC_EDITNEW,"");
	SetDlgItemText(IDC_EDITSMONEY,"");
	SetDlgItemText(IDC_EDITNMONEY,"");
}

//显示任务操作界面
void CPALRoleManage::ShowQuestTab(int m_cmdShow,int selectShow)
{	
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLQUESTSTATUS)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBQUESTSTATUS)->ShowWindow(m_cmdShow);	
	if(selectShow == 1)
	{
	    GetDlgItem(IDC_LBLQUESTNAME)->ShowWindow(m_cmdShow);	
	    GetDlgItem(IDC_EDITQUESTNAME)->ShowWindow(m_cmdShow);	
		GetDlgItem(IDC_LBLSTATUS)->ShowWindow(m_cmdShow);
	    GetDlgItem(IDC_CMBSTATUS)->ShowWindow(m_cmdShow);	
	    GetDlgItem(IDC_BTNMODIQUEST)->ShowWindow(m_cmdShow);
	}
	else
	{
		GetDlgItem(IDC_LBLQUESTNAME)->ShowWindow(SW_HIDE);	
	    GetDlgItem(IDC_EDITQUESTNAME)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_BTNMODIQUEST)->ShowWindow(SW_HIDE);
	}
}