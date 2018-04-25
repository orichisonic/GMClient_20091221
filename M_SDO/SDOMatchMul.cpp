// SDOMatchMul.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOMatchMul.h"
#include ".\sdomatchmul.h"


// CSDOMatchMul 对话框

IMPLEMENT_DYNAMIC(CSDOMatchMul, CDialog)
CSDOMatchMul::CSDOMatchMul(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOMatchMul::IDD, pParent)
{
}

CSDOMatchMul::~CSDOMatchMul()
{
}

void CSDOMatchMul::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSERVER, listServer);
	DDX_Control(pDX, IDC_CMBWEEKDAY, cmbWeekDay);
	DDX_Control(pDX, IDC_CMBSENCE, cmbSence);
	DDX_Control(pDX, IDC_CMBMODE, cmbMode);
}


BEGIN_MESSAGE_MAP(CSDOMatchMul, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECKSELECTALL, OnBnClickedCheckselectall)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDC_BTQUERYSENCE, OnBnClickedBtquerysence)
END_MESSAGE_MAP()


// CSDOMatchMul 消息处理程序

// 初始化对话框
BOOL CSDOMatchMul::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();
	ServerIP = "";// 服务器IP
	AllServer = false;// 是否在所有大区发送公告
	//场景名称
	SenceName = "";

	MiniuteOpen = 0;//开放分钟
	MiniuteUnit = 0;//联合分钟
	GCash = 0;//G币

	listServer.SetExtendedStyle(listServer.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//服务器列表中需要显示CheckBox
	listServer.InsertColumn(0,theApp.operSDO.ReadValue("MSDO","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

	CRect rs;
	GetClientRect(rs);; //获取对话框的大小信息

	CRect srcRect;
	CRect newRect;

	if( listServer.m_hWnd != NULL )   
	{
		listServer.GetWindowRect(srcRect);//获取listResult的大小信息
		listRWidth = srcRect.right - srcRect.left;//得到listResult的宽度信息

		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 8;

		listServer.MoveWindow(newRect);//设置listResult的位置
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
//初始化显示字符
void CSDOMatchMul::InitUI()
{
	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","MakeSure"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));

	SetDlgItemText(IDC_LBLWEEKDAY,theApp.operSDO.ReadValue("MSDO","WeekDay"));
	SetDlgItemText(IDC_LBLMINIUTEOPEN,theApp.operSDO.ReadValue("MSDO","MiniuteOpen"));
	SetDlgItemText(IDC_LBLMINIUTEUNIT,theApp.operSDO.ReadValue("MSDO","MiniuteUnit"));
	SetDlgItemText(IDC_LBLCHARGEGCASH,theApp.operSDO.ReadValue("MSDO","ChargeGCash"));
	SetDlgItemText(IDC_LBLSENCE,theApp.operSDO.ReadValue("MSDO","Sence"));
	SetDlgItemText(IDC_LBLMODE,theApp.operSDO.ReadValue("MSDO","Mode"));
	SetDlgItemText(IDC_CHECKSELECTALL,theApp.operSDO.ReadValue("MSDO","NI_UI_SelectAll"));//
	
	SetDlgItemText(IDC_BTQUERYSENCE,theApp.operSDO.ReadValue("MSDO","QuerySence"));//查询场景
	WeekDay();
	Mode();
}

// 自动改变大小
void CSDOMatchMul::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if( listServer.m_hWnd != NULL )   
	{
		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 10;

		listServer.MoveWindow(newRect);//设置listResult的位置
	}  
}

//设置背景颜色
HBRUSH CSDOMatchMul::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}


// 选择所有游戏服务器进行发送
void CSDOMatchMul::OnBnClickedCheckselectall()
{
	// TODO: 在此添加控件通知处理程序代码
	if(AllServer == false)
	{
		for(int i=0; i<listServer.GetItemCount(); i++)
		{
			listServer.SetCheck(i);//选中所有的游戏服务器
		}
		listServer.EnableWindow(true);//让游戏服务器列表变为Disable的状态
		AllServer = true;
	}
	else
	{
		for(int i=0; i<listServer.GetItemCount(); i++)
		{
			listServer.SetCheck(i,false);//取消选中所有的游戏服务器
		}
		//listResult.EnableWindow(true);//让游戏服务器列表变为Enable的状态
		AllServer = false;
	}
}

//返回要发送公告的游戏服务器列表
void CSDOMatchMul::ReturnServerIP(char* allServerIP)
{
	CString serverName="";
	int num=0;
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverName);//查找服务器IP
			if(num==0)
			{
				
				sprintf(allServerIP,"%s",serverName);
				
			}
			else
			{
				sprintf(allServerIP,"%s,%s",allServerIP,serverName);
			}
			num++;
		}
	}
	sprintf(allServerIP,"%s,",allServerIP);
}

//返回要发送公告的游戏服务器名称列表
CString CSDOMatchMul::ReturnServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			serverName=listServer.GetItemText(i,0);//查找服务器名称
			rServerName += serverName;
			rServerName += ",";//将所有的服务器IP用","隔开
		}
	}
	return rServerName;
}

// 关闭对话框
void CSDOMatchMul::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//关闭窗体
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!SenceList.IsEmpty())
	{
		SenceList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CSDOMatchMul::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_ETCHECKSERVER,"");
	cmbWeekDay.SetCurSel(0);
	SetDlgItemText(IDC_ETMINIUTEOPEN,"");
	SetDlgItemText(IDC_ETMINIUTEUNIT,"");
	SetDlgItemText(IDC_ETCHARGEGCASH,"");
	cmbSence.SetCurSel(0);
	cmbMode.SetCurSel(0);

}

//导入星期数
void CSDOMatchMul::WeekDay()
{
	cmbWeekDay.ResetContent();
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Sun"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Mon"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Tues"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Wens"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Thus"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Fri"));
	cmbWeekDay.AddString(theApp.operSDO.ReadValue("MSDO","Sat"));
	cmbWeekDay.SetCurSel(0);
}

//导入比赛模式
void CSDOMatchMul::Mode()
{
	cmbMode.ResetContent();
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type1"));//普通大赛
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type2"));//Showtime
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type3"));//道具战大赛
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type4"));//反键大赛
	cmbMode.SetCurSel(0);
}

//查询比赛场景
void CSDOMatchMul::SenceQuery()
{
	try
	{		
		CIni mIni;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_QUERY))//比赛场景
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// 接收返回信息
LRESULT CSDOMatchMul::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
			listServer.EnableWindow(true);

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);//获取返回信息中的第一个模块
			if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//如果第一个模块的TagName是MESSAGE，表示出现了错误信息，显示错误信息并返回
			{
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operSDO.ReadValue("MSDO","Error"),0);
				socketdata.Destroy();
				return false;
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//获取所有的服务器IP
				ServerList.SetAt(i,ServerIP);//添加到CMap类的对象ServerList中
			}

			listServer.DeleteAllItems();//清除服务器列表中的所有内容
			CString serverName = "";
			int nRow = 0;
			for(int i=0;i<socketdata.getQueryNum();i++)
			{
				nRow = listServer.InsertItem(i,"");
				serverName = (LPSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::ServerInfo_City).lpdata;//获取游戏服务器名称
				listServer.SetItemText(nRow,0,serverName);//将游戏服务器名称添加到服务器列表中
			}

			
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_QUERY_RESP:////查询场景
		{
			if(!SenceList.IsEmpty())
			{
				SenceList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int nItem = StrToInt((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::SDO_SenceID).lpdata);//得到服务器IP
				SenceList.SetAt(i,nItem);//
			}

			theApp.operSDO.BuildComboxScene(&socketdata,&cmbSence);
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_INSERTALL_RESP://批量添加场景
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

//批量添加场景
void CSDOMatchMul::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		CIni mIni;
		CString strMode="";
		int iPos=((CComboBox*)GetDlgItem(IDC_CMBMODE))->GetCurSel();//当前选中的行//IDC_CMBMODE
		if(iPos==0)
			strMode="10";
		else if(iPos==1)
			strMode="13";
		else if(iPos==2)
			strMode="12";
		else if(iPos==3)
			strMode="11";

		int nDay=((CComboBox*)GetDlgItem(IDC_CMBWEEKDAY))->GetCurSel();//当前选中的行

		CString strSence="";
		GetDlgItemText(IDC_CMBSENCE,strSence);

		MiniuteOpen=GetDlgItemInt(IDC_ETMINIUTEOPEN);
		MiniuteUnit=GetDlgItemInt(IDC_ETMINIUTEUNIT);
		GCash=GetDlgItemInt(IDC_ETCHARGEGCASH);

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、服务器Name、玩家昵称、页数、每页的记录条数
		char strInt[10];

		int UserByID=theApp.UserByID;

		char strServerIP[2048];
		ZeroMemory(strServerIP,2048);
		if(AllServer)
		{
			ReturnServerIP(strServerIP);
			ServerName=ReturnServerName();
		}
		else
		{
			ReturnServerIP(strServerIP);
			ServerName=ReturnServerName();
		}

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(strServerIP),(unsigned char *)mIni.wcharToChar(strServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_IsBattle,CEnumCore::TagFormat::TLV_STRING,strlen(strMode),(unsigned char *)mIni.wcharToChar(strMode));//mode
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(strSence),(unsigned char *)mIni.wcharToChar(strSence));//sence

		_itoa(UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//用户ID

		_itoa(nDay,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_WeekDay,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//WeekDay

		_itoa(MiniuteOpen,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_StPtMin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(MiniuteUnit,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_MatPtMin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(GCash,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_GCash,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_INSERTALL))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();
			
	}
	catch(...)
	{
	}
}

//查询场景
void CSDOMatchMul::OnBnClickedBtquerysence()
{
	// TODO: 在此添加控件通知处理程序代码
	SenceQuery();
}
