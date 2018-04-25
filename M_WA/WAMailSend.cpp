// WAMailSend.cpp : 实现文件
//

#include "stdafx.h"
#include "M_WA.h"
#include "WAMailSend.h"
#include ".\wamailsend.h"


// CWAMailSend 对话框

IMPLEMENT_DYNAMIC(CWAMailSend, CDialog)
CWAMailSend::CWAMailSend(CWnd* pParent /*=NULL*/)
	: CDialog(CWAMailSend::IDD, pParent)
{
}

CWAMailSend::~CWAMailSend()
{
}

void CWAMailSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_PROGRESSMAIL, progMail);
}


BEGIN_MESSAGE_MAP(CWAMailSend, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_CMBSERVER, OnCbnSelchangeCmbserver)
	ON_BN_CLICKED(IDC_BTNSEND, OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)	
	ON_BN_CLICKED(IDC_BTNBROWSE, OnBnClickedBtnbrowse)
END_MESSAGE_MAP()


// CWAMailSend 消息处理程序

// 初始化对话框
BOOL CWAMailSend::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符

	ServerIP = "";
	UserNick = "";
	MailTitle = "";
	MailContent = "";
	UserNum=0;//最开始角色名数量为0
	mCurNum = 0;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//当前的状态为初始建立对话框

	if(theApp.operWA.GetServerList())//请求所有的游戏服务器列表
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求
	}
	return TRUE;
}

// 初始化显示字符
void CWAMailSend::InitUI()
{
	SetWindowText(theApp.operWA.ReadValue("MWA","MM_UI_MULTMAIL"));

	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLPATH,theApp.operWA.ReadValue("MWA","IM_UI_LBLPATH"));
	SetDlgItemText(IDC_BTNBROWSE,theApp.operWA.ReadValue("MWA","IM_UI_BTNBROWSE"));
	SetDlgItemText(IDC_BTNSEND,theApp.operWA.ReadValue("MWA","Send"));
	SetDlgItemText(IDC_BTNRESET,theApp.operWA.ReadValue("MWA","Reset"));

	SetDlgItemText(IDC_LBLMAIN,"");
	SetDlgItemText(IDC_LBLPROG,"");
}

//设置背景颜色
HBRUSH CWAMailSend::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//获取选择的ServerIP
void CWAMailSend::OnCbnSelchangeCmbserver()
{
	try
	{
		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器为空
		{
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
	}
	catch(...)
	{
	}
}

//选择批量发送邮件的文件
void CWAMailSend::OnBnClickedBtnbrowse()
{
	char path[256];
	GetCurrentDirectory(256,path);
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象

	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"文件类型(*.xls)|*.xls||");

	if(lpszOpenFile->DoModal()==IDOK)//假如点击对话框确定按钮
	{
		CString szGetName;
		szGetName=lpszOpenFile->GetPathName();
		SetDlgItemText(IDC_EDITPATH,szGetName);
		SetCurrentDirectory(path);
	}
	delete lpszOpenFile;
}

//批量发送邮件信息
void CWAMailSend::OnBnClickedBtnsend()
{
	try
	{
		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//获取游戏服务器的名称
		if(m_ServerName == "")//游戏服务器为空
		{
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP
			
		//读取要批量添加的角色名txt文件				
		CString filename="";				
		GetDlgItemText(IDC_EDITPATH,filename);

		if(!ReadXls(filename))
		{
			return;
		}

		if(UserNum == 0)
			return;

		GetDlgItem(IDC_BTNSEND)->ShowWindow(SW_HIDE);
		
		CString tmpNum = "";
		tmpNum.Format("%i",UserNum);
		SetDlgItemText(IDC_LBLMAIN,theApp.operWA.ReadValue("MWA","IM_UI_LblMain")+tmpNum);
		SetDlgItemText(IDC_LBLPROG,"");	

		progMail.SetPos(0);
		progMail.SetRange(0,UserNum);
		progMail.SetStep(1);

		mCurNum = 1;
		UserList.Lookup(mCurNum,UserNick);//从CMap类的对象UserList中获取角色名
		TitleList.Lookup(mCurNum,MailTitle);//从CMap类的对象TitleList中获取邮件标题
		ContentList.Lookup(mCurNum,MailContent);//从CMap类的对象SubjectList中获取邮件内容
		SendMail();
	}
	catch(...)
	{
	}
}

//发送邮件
void CWAMailSend::SendMail()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,20);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(""),(unsigned char *)mIni.wcharToChar(""));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//玩家昵称
		socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(""),(unsigned char *)mIni.wcharToChar(""));//角色唯一IDKEY

		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员id

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//页数
		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//每页的条数

		socketdata.AddTFLV(CEnumCore::TagName::WA_MailSubject,CEnumCore::TagFormat::TLV_STRING,strlen(MailTitle),(unsigned char *)mIni.wcharToChar(MailTitle));//邮件主题
		socketdata.AddTFLV(CEnumCore::TagName::WA_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(MailContent),(unsigned char *)mIni.wcharToChar(MailContent));//邮件内容
		
		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_SendMails_Op);//发送邮件

		//::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//当前的状态为发送查询请求

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_SendMail"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

bool CWAMailSend::ReadXls(CString m_filePath)
{
	try
	{
		CoInitialize(NULL);
		_ConnectionPtr m_pConnection;
		_RecordsetPtr	m_pRecordset;
		CString ConnectionString="";
		ConnectionString = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");   
		ConnectionString += m_filePath;
		ConnectionString += _T(";Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\""); 

		BSTR resultsString = ConnectionString.AllocSysString();

		m_pConnection.CreateInstance(__uuidof(Connection));

		m_pConnection->Open(resultsString,"","",adModeUnknown);
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open("select * from [Sheet1$]",
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

		UserNum = 0;
		if(m_pRecordset->adoEOF) 
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Error_ReadFile"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return false;
		}

		if(!UserList.IsEmpty())
		{
			UserList.RemoveAll();
		}
		if(!TitleList.IsEmpty())
		{
			TitleList.RemoveAll();
		}
		if(!ContentList.IsEmpty())
		{
			ContentList.RemoveAll();
		}

		UserNick = "";
		MailTitle = "";
		MailContent = "";
		CString tmpNum="";			

		_variant_t TheValue; //VARIANT数据类型
		while(!m_pRecordset->adoEOF)
		{
			UserNum++;//循环增加，获取玩家数量
			tmpNum.Format("%i",UserNum);

			TheValue = m_pRecordset->GetCollect(_variant_t((long)0));
			if(TheValue.vt==VT_NULL) 
			{
				MessageBox(tmpNum+"："+theApp.operWA.ReadValue("MWA","IM_Warn_RoleNameNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return false;
			}

			UserNick=(LPCSTR)_bstr_t(TheValue);//获取角色名
			UserNick.Trim();
			if(UserNick == "")//玩家角色名不能为空
			{
				MessageBox(tmpNum+"："+theApp.operWA.ReadValue("MWA","IM_Warn_RoleNameNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return false;
			}
			UserList.SetAt(UserNum,UserNick);//保存角色名

			TheValue = m_pRecordset->GetCollect(_variant_t((long)1));
			MailTitle=(LPCSTR)_bstr_t(TheValue);//获取邮件标题
			MailTitle.Trim();
			if(MailTitle == "")//邮件标题不能为空
			{
				MessageBox(tmpNum+"："+theApp.operWA.ReadValue("MWA","IM_Warn_MailSubject"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return false;
			}
			if(strlen(MailTitle) > 20)//邮件标题不能超过20个字符
			{
				MessageBox(tmpNum+"："+theApp.operWA.ReadValue("MWA","IM_Warn_SubjectTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return false;
			}
			TitleList.SetAt(UserNum,MailTitle);//保存邮件标题

			TheValue = m_pRecordset->GetCollect(_variant_t((long)2));
			MailContent=(LPCSTR)_bstr_t(TheValue);//获取邮件内容
			if(MailContent == "")//邮件内容不能为空
			{
				MessageBox(tmpNum+"："+theApp.operWA.ReadValue("MWA","IM_Warn_MailContent"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return false;
			}
			if(strlen(MailContent) > 200)//邮件内容不能超过200个字符
			{
				MessageBox(tmpNum+"："+theApp.operWA.ReadValue("MWA","IM_Warn_ContentTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return false;
			}
			ContentList.SetAt(UserNum,MailContent);//保存邮件内容

			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		if(m_pRecordset) m_pRecordset.Release();
		m_pConnection->Close();
		if(m_pConnection) m_pConnection.Release();
		CoUninitialize();
	}
	catch(...)
	{
		return false;
	}
	return true;
}

//重置信息
void CWAMailSend::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITPATH,"");
	
	mCurNum = UserNum;
	SetDlgItemText(IDC_LBLMAIN,"");
	SetDlgItemText(IDC_LBLPROG,"");
	progMail.SetPos(0);
}

// 接收返回信息
LRESULT CWAMailSend::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//当前的状态为接收到了返回信息

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
			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_SendMails_Op_Resp://批量发送邮件
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString Result = (LPCTSTR)&m_tflv.lpdata;

			CString tmpNum="";
			if(mCurNum<UserNum)
			{					
				tmpNum.Format("%i",mCurNum);
				SetDlgItemText(IDC_LBLPROG,theApp.operWA.ReadValue("MWA","IM_UI_LblMailFirst")+tmpNum+theApp.operWA.ReadValue("MWA","IM_UI_LblMailSecond")+UserNick+theApp.operWA.ReadValue("MWA","IM_UI_LblMailThird")+Result+theApp.operWA.ReadValue("MWA","IM_UI_LblMailFourth"));	
				progMail.StepIt();

				mCurNum++;
				UserList.Lookup(mCurNum,UserNick);//从CMap类的对象UserList中获取角色名
				TitleList.Lookup(mCurNum,MailTitle);//从CMap类的对象TitleList中获取邮件标题
				ContentList.Lookup(mCurNum,MailContent);//从CMap类的对象SubjectList中获取邮件内容

				SendMail();
				return false;					
			}
			tmpNum.Format("%i",mCurNum);
			SetDlgItemText(IDC_LBLPROG,theApp.operWA.ReadValue("MWA","IM_UI_LblMailFirst")+tmpNum+theApp.operWA.ReadValue("MWA","IM_UI_LblMailSecond")+UserNick+theApp.operWA.ReadValue("MWA","IM_UI_LblMailThird")+Result+theApp.operWA.ReadValue("MWA","IM_UI_LblMailFourth"));	
			progMail.SetPos(mCurNum);

			theApp.operWA.ShowResult(Result);//显示返回结果
			SetDlgItemText(IDC_EDITPATH,"");

			GetDlgItem(IDC_BTNSEND)->ShowWindow(SW_SHOW);
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//显示返回结果
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}
// 关闭对话框
void CWAMailSend::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!UserList.IsEmpty())
	{
		UserList.RemoveAll();
	}
	if(!TitleList.IsEmpty())
	{
		TitleList.RemoveAll();
	}
	if(!ContentList.IsEmpty())
	{
		ContentList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}