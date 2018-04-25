// KickPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "M_WA.h"
#include "KickPlayer.h"
#include ".\kickplayer.h"


// CKickPlayer 对话框

IMPLEMENT_DYNAMIC(CKickPlayer, CDialog)
CKickPlayer::CKickPlayer(CWnd* pParent /*=NULL*/)
: CDialog(CKickPlayer::IDD, pParent)
{
}

CKickPlayer::~CKickPlayer()
{
}

void CKickPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
		DDX_Control(pDX, IDC_TABRESULT2, tbcResult);
}


BEGIN_MESSAGE_MAP(CKickPlayer, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	//ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	//ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
END_MESSAGE_MAP()


// CKickPlayer 消息处理程序
BOOL CKickPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();

	//InitUI();// 初始化显示字符

	nItem = 0;
	ServerIP = "";
	ServerName = "";
	UserAccount = "";
	UserName = "";//初始化一些私有变量

	SetProp(listUser.GetSafeHwnd(),"排序列号",(HANDLE)0);
	SetProp(listUser.GetSafeHwnd(),"排序顺序",(HANDLE)1);
tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","UIC_UI_tpgUserInfo"));
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
		newRect.top = rs.top + 4 + grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}

	//OperationWA operWA;
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//当前的状态为初始建立对话框

	if(theApp.operWA.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
	}
	///////////////////////////
	//////////////////////////
	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));

	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLNAME2,theApp.operWA.ReadValue("MWA","KICKPLAYER_NOTICE"));
	//MessageBox(theApp.operWA.ReadValue("MWA","KICKPLAYER_NOTICE"),"",0);
	/////////////////////////
	////////////////////////
	return TRUE;
}
// 查询玩家资料信息
void CKickPlayer::OnBnClickedSearch()
{
	try
	{
		////////////////////////////////按帐号踢人
		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//获取玩家帐号
		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家角色名
		if((UserName == "") && (UserAccount == ""))//玩家帐号和玩家角色名不能同时为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_InputAccount"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if((UserName != "") && (UserAccount != ""))//玩家帐号和玩家角色名同时有数值
		{
			MessageBox(theApp.operWA.ReadValue("MWA","KICKPLAYER_NOTICE"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(UserAccount!=""&&false)
		{
			UserName="";
			CIni mIni;
			int userbyID = theApp.UserByID;
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家昵称、玩家帐号、操作员ID
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			//socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称

			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

			int midlength = socketdata.EnBody();
			if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_KickPlayer))//发送强制玩家下线的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();
			return;
		}
		else if(UserName!=""&&false)
		{
//			UserAccount="";
			CIni mIni;
			int userbyID = theApp.UserByID;
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家昵称、玩家帐号、操作员ID
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			//socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称

			//socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

			int midlength = socketdata.EnBody();
			if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_KickPlayer))//发送强制玩家下线的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();
			//return;
		}
		//////////////////////////////////////////
	}
	catch(...)
	{

	}

	try
	{


		CIni mIni;

		//ShowUserInfo();

		int index = theApp.operWA.ReadIntValue("MWA","index");//查询第一页的信息
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

		nItem = 0;//玩家资料列表没有选定项
		while(listUser.DeleteColumn(0)){}//清除玩家资料列表中的所有内容
		//MessageBox("test");
		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		//////////////////////////////////////////获取查找类型
		//int searchindex=((CComboBox*)GetDlgItem(IDC_CMSEARCHTYPE))->GetCurSel();
		//if(searchindex==0)
		//{
		//	SearchType="precisesimple";
		//}
		//else if(searchindex==1)
		//{
		//	SearchType="precisedetail";
		//}
		//else if(searchindex==2)
		//{
		//	SearchType="vaguesimple";
		//}
		//else if(searchindex==3)
		//{
		//	SearchType="vaguedetail";
		//}
		//CString temp;
		//temp.Format("%d",searchindex);
		//MessageBox(SearchType);
		CString  SearchType="1";

		/////////////////////////////////////////获取查找类型结束
		if(ServerName == "")//游戏服务器不能为空
		{
			//MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			//return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
		//MessageBox(ServerIP);
		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//获取玩家帐号
		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家角色名
		if((UserName == "") && (UserAccount == ""))//玩家帐号和玩家角色名不能同时为空
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_InputAccount"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//共有六个参数，服务器IP、玩家帐号、玩家角色名、页数、每页的记录条数\\、服务器Name
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		//socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家角色名
	//	socketdata.AddTFLV(CEnumCore::TagName::WA_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(SearchType),(unsigned char *)mIni.wcharToChar(SearchType));//查找类型
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query))//发送查询玩家资料信息的请求
		{
			//MessageBox("YY");
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
			//MessageBox("发送成功");
		}
		socketdata.Destroy();//销毁CSocketData局部变量

	}
	catch(...)
	{
	}
}

// 接收返回信息
LRESULT CKickPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	//OperationWA operWA;
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
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,sIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://取得角色基本资讯响应
		{
			//theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
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

		}
		break;
	case CEnumCore::Message_Tag_ID::WA_KickPlayer_Resp://强制玩家下线的回应
		{
			//MessageBox()
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			MessageBox(result);
			//theApp.operWA.ShowResult(result);//显示操作结果

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
// 双击玩家资料信息强制玩家下线
void CKickPlayer::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
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
				CIni mIni;
				UserAccount = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// 保存选中的玩家帐号
				UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// 保存选中的玩家角色名
                
				if (AfxMessageBox(theApp.operWA.ReadValue("MWA","KP_Hint_KickPlayer"), MB_YESNO) == IDNO) 
				{
					return;
				}

				int userbyID = theApp.UserByID;

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家昵称、玩家帐号、操作员ID
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				//socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
				socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称

				socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

				int midlength = socketdata.EnBody();
				if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_KickPlayer))//发送强制玩家下线的请求
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
				}
				socketdata.Destroy();
			}
		}
		else
		{
			nItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}
// 翻页进行查询
void CKickPlayer::OnCbnSelchangeCmbpage()
{
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;
			while(listUser.DeleteColumn(0)){}

			int index = cmbPage.GetCurSel() + 1;//页数为cmbPage当前的索引值加1，也就是cmbPage中当前显示的值
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//每页显示50条记录

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			//socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//发送查询请求
			}

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Page"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// 关闭对话框
void CKickPlayer::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
}

// 关闭对话框
void CKickPlayer::OnClose()
{
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Close");//关闭窗体	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
HBRUSH CKickPlayer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{ 
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}
//单击用户资料信息的列名进行排序
void CKickPlayer::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operWA.SortListInfo(&listUser,pNMHDR,pResult);
}
// 自动改变大小
void CKickPlayer::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;
CRect srcRect;
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
	newRect.top = rs.top + 4 + grpHeight + tbcHeight+ grpPHeight;
	newRect.bottom = rs.bottom-10;
	newRect.left = rs.left +10;
	newRect.right = rs.right - 10;

	listUser.MoveWindow(newRect);//设置好listUser的位置
}
}
//处理快捷键响应函数
BOOL CKickPlayer::PreTranslateMessage(MSG* pMsg)
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
				//else if(pMsg->hwnd == listResult.m_hWnd)
				//{
				//	theApp.operWA.CopyListInfo(&listResult);
				//}
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
				//else if(pMsg->hwnd == listResult.m_hWnd)
				//{
				//	for(int i=0; i<listResult.GetItemCount(); i++)
				//	{
				//		listResult.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
				//		listResult.EnsureVisible(i,false);
				//	}
				//}
			}
		}		
	}
	return FALSE;
}

