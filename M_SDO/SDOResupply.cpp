// SDOResupply.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOResupply.h"
#include ".\sdoresupply.h"


// CSDOResupply 对话框

IMPLEMENT_DYNAMIC(CSDOResupply, CDialog)
CSDOResupply::CSDOResupply(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOResupply::IDD, pParent)
{
}

CSDOResupply::~CSDOResupply()
{
}

void CSDOResupply::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
}


BEGIN_MESSAGE_MAP(CSDOResupply, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDC_BTADD, OnBnClickedBtadd)
END_MESSAGE_MAP()


// CSDOResupply 消息处理程序

// 初始化对话框
BOOL CSDOResupply::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();// 初始化显示字符

	ServerIP = "";
	UserAccount = "";
	UserName = "";//初始化一些私有变量
	UserID=0;

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
void CSDOResupply::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","Resupply"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operSDO.ReadValue("MSDO","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operSDO.ReadValue("MSDO","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operSDO.ReadValue("MSDO","UIC_UI_lblAccount"));

	SetDlgItemText(IDC_CURGCASH,theApp.operSDO.ReadValue("MSDO","CurrentGCash"));
	SetDlgItemText(IDC_ADDGCASH,theApp.operSDO.ReadValue("MSDO","AddGCash"));

	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","Search"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));
	SetDlgItemText(IDC_BTADD,theApp.operSDO.ReadValue("MSDO","Resuppy"));
}

// 自动改变大小
void CSDOResupply::OnSize(UINT nType, int cx, int cy)
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

}

HBRUSH CSDOResupply::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// 关闭对话框
void CSDOResupply::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//关闭窗体	

	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CSDOResupply::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	SetDlgItemInt(IDC_ETCURGCASH,0);
	SetDlgItemInt(IDC_ETADDGCASH,0);
	cmbServer.SetCurSel(0);
}

//搜索玩家G币
void CSDOResupply::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;

		GetDlgItemText(IDC_CMBSERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_SelectServer"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP

		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//获取玩家帐号//IDC_EDITACCOUNT
		if(UserAccount == "")//玩家帐号和玩家角昵称不能同时为空
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_InputAccount"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		SetDlgItemInt(IDC_ETADDGCASH,0);
	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//共有五个参数，服务器IP、服务器Name、玩家帐号、玩家角色名、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//玩家角色名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_USERGCASH_QUERY))
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

// 接收返回信息
LRESULT CSDOResupply::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::SDO_USERGCASH_QUERY_RESP://返回G币金额
		{
			//account=(LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::SDO_Account).lpdata;//getTLVByTag
			int iCurGCash=0;
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				iCurGCash=StrToInt((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::SDO_GCash).lpdata);
			}
				//SetDlgItemText(IDC_ETCURGCASH,CurGCash);
			
				SetDlgItemInt(IDC_ETCURGCASH,iCurGCash);
	
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_USERGCASH_UPDATE_RESP://补发G币金额
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

//补发G币金额
void CSDOResupply::OnBnClickedBtadd()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{		
		CIni mIni;

		
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

//		CString addGCash="";
//		GetDlgItemText(IDC_ETADDGCASH,addGCash);
//		if(addGCash == "")
//		{
//			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_AddGCash"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
//			return;
//		}
		int iAddGCash=0;
		iAddGCash=GetDlgItemInt(IDC_ETADDGCASH);
		if(iAddGCash==0)
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_AddGCash"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int userbyID = theApp.UserByID;//操作员ID

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//玩家帐号
		
		_itoa(iAddGCash,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_GCash,CEnumCore::TagFormat::TLV_STRING,sizeof(int),(unsigned char *)&strInt);//G币金额

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_USERGCASH_UPDATE))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Error_ItemInfoError"),theApp.operSDO.ReadValue("MGTOWN","Error"),0);
	}
}
