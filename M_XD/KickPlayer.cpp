// KickPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "M_XD.h"
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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}

	//OperationPAL operPAL;
	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//当前的状态为初始建立对话框

	if(theApp.operXD.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
	}

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
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_InputAccount"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if((UserName != "") && (UserAccount != ""))//玩家帐号和玩家角色名同时有数值
		{
			MessageBox("帐号和角色名不能同时输入",theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(UserAccount!="")
		{
			UserName="";
			CIni mIni;
			int userbyID = theApp.UserByID;
           ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家昵称、玩家帐号、操作员ID
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

			int midlength = socketdata.EnBody();
			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_KickPlayer))//发送强制玩家下线的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();
			return;
		}
		else if(UserName!="")
		{
			UserName="";
			CIni mIni;
			int userbyID = theApp.UserByID;
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家昵称、玩家帐号、操作员ID
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
			//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称

			//socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

			int midlength = socketdata.EnBody();
			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_KickPlayer))//发送强制玩家下线的请求
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
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

		int index = theApp.operXD.ReadIntValue("MXD","index");//查询第一页的信息
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//每页显示50条记录

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
			//MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			//return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
		//MessageBox(ServerIP);
		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//获取玩家帐号
		GetDlgItemText(IDC_EDITNAME,UserName);//获取玩家角色名
		if((UserName == "") && (UserAccount == ""))//玩家帐号和玩家角色名不能同时为空
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_InputAccount"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//共有六个参数，服务器IP、玩家帐号、玩家角色名、页数、每页的记录条数\\、服务器Name
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		//socketdata.AddTFLV(CEnumCore::TagName::XDJG_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(SearchType),(unsigned char *)mIni.wcharToChar(SearchType));//查找类型
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的记录条数

		int midlength = socketdata.EnBody();
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query))//发送查询玩家资料信息的请求
		{
			//MessageBox("YY");
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
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

	//OperationPAL operPAL;
	CIni mIni;

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Receive");//当前的状态为接收到了返回信息

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operXD.ReadValue("MXD","Main_UI_ParseData"),theApp.operXD.ReadValue("MXD","ERROR"),0);		
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

			theApp.operXD.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://取得角色基本资讯响应
		{
			theApp.operXD.BuildDataTable(&socketdata,&listUser,&pageCount);//构造CListCtrl对象
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_KickPlayer_Resp://强制玩家下线的回应
		{
			//MessageBox()
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			MessageBox(result);
			//theApp.operXD.ShowResult(result);//显示操作结果

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
				UserAccount = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// 保存选中的玩家帐号
				UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// 保存选中的玩家角色名

				if (AfxMessageBox(theApp.operXD.ReadValue("MXD","KP_Hint_KickPlayer"), MB_YESNO) == IDNO) 
				{
					return;
				}

				int userbyID = theApp.UserByID;

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//共有四个参数，服务器IP、玩家昵称、玩家帐号、操作员ID
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
				//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//玩家昵称

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号

				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

				int midlength = socketdata.EnBody();
				if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_KickPlayer))//发送强制玩家下线的请求
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//当前的状态为发送查询请求
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
	dlgStatus = theApp.operXD.ReadIntValue("MXD","Close");//关闭窗体	
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
	theApp.operXD.SortListInfo(&listUser,pNMHDR,pResult);
}
// 自动改变大小
void CKickPlayer::OnSize(UINT nType, int cx, int cy)
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
	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//设置好listUser的位置
	}
}
