// GTOWNImport.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNImport.h"
#include ".\GTOWNImport.h"


// CGTOWNImport 对话框

IMPLEMENT_DYNAMIC(CGTOWNImport, CDialog)
CGTOWNImport::CGTOWNImport(CWnd* pParent /*=NULL*/)
	: CDialog(CGTOWNImport::IDD, pParent)
{
}

CGTOWNImport::~CGTOWNImport()
{
}

void CGTOWNImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
}


BEGIN_MESSAGE_MAP(CGTOWNImport, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_COMFIRM, OnBnClickedComfirm)
END_MESSAGE_MAP()

// 初始化对话框
BOOL CGTOWNImport::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// 初始化显示字符	


	CRect rs;
	GetClientRect(rs);//获取对话框的大小信息


	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Create");//初始建立对话框

	theApp.operGTOWN.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//发送查询请求

	return TRUE;
}

// 初始化显示字符
void CGTOWNImport::InitUI()
{

	SetDlgItemText(IDC_LBLUISERVER,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_LblServer"));
	SetDlgItemText(IDUICANCEL,theApp.operGTOWN.ReadValue("MGTOWN","Cancel"));
}

//处理快捷键响应函数
BOOL CGTOWNImport::PreTranslateMessage(MSG* pMsg)
{
   	return FALSE;
}

// 自动改变大小
void CGTOWNImport::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);


}

//设置背景颜色
HBRUSH CGTOWNImport::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//背景颜色为白色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}



// 接收返回信息
LRESULT CGTOWNImport::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的数据长度


	CIni mIni;

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Receive");//当前的状态为接收到了返回信息

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
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//得到服务器IP
				ServerList.SetAt(i,sIP);//将服务器IP保存在CMap类的对象ServerList中
			}

			theApp.operGTOWN.BuildCombox(&socketdata,&cmbServer);//构造服务器列表信息
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Import_Item_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGTOWN.ShowResult(result);//显示操作结果
		}
		break;
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

// 关闭对话框
void CGTOWNImport::OnBnClickedUicancel()
{

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//关闭窗体
	OnClose();
}

// 关闭对话框
void CGTOWNImport::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CGTOWNImport::OnBnClickedBrowse()
{
	// TODO: 在此添加控件通知处理程序代码
	char path[256];
	GetCurrentDirectory(256,path);
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象

	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"文件类型(*.xls)|*.xls||");


	if(lpszOpenFile->DoModal()==IDOK)//假如点击对话框确定按钮
	{
		CString szGetName;
		szGetName=lpszOpenFile->GetPathName();
		SetDlgItemText(IDC_FILENAME,szGetName);
		SetCurrentDirectory(path);

	}
	delete lpszOpenFile;
}

void CGTOWNImport::OnBnClickedComfirm()
{
	CIni mIni;		
	CString allUserName;
	CString allItemID;
	CString allNum;
	CString filename;
	CString strTitle;
	CString strText;
	GetDlgItemText(IDC_EDITTITLE,strTitle);
	if(strlen(strTitle)<1)
	{
		MessageBox("标题不能为空");
		return;
	}
	GetDlgItemText(IDC_EDITCONTENT,strText);
	if(strlen(strText)<1)
	{
		MessageBox("内容不能为空");
		return;
	}
	GetDlgItemText(IDC_FILENAME,filename);
	if(!ReadXls(filename,&allUserName,&allItemID,&allNum))
	{
		AfxMessageBox("格式错误");
		return;
	}
	if(strlen(allUserName)>2000||strlen(allItemID)>2000||strlen(allNum)>2000)
	{
		MessageBox("超出最大批量数,请在分批");
		return;
	}
	else
	{
		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//共有五个参数，服务器IP、玩家帐号、玩家昵称、页数、每页的记录条数
		char strInt[10];

		int userbyID = theApp.UserByID;//操作员ID
		GetDlgItemText(IDC_CMBUISERVER,ServerName);//获取游戏服务器的名称
		if(ServerName == "")//游戏服务器不能为空
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//从CMap类的对象ServerList中获取游戏服务器的IP


		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//服务器IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_MailTitle,CEnumCore::TagFormat::TLV_STRING,strlen(strTitle),(unsigned char *)mIni.wcharToChar(strTitle));//服务器Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(strText),(unsigned char *)mIni.wcharToChar(strText));//服务器IP

		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(allUserName),(unsigned char *)mIni.wcharToChar(allUserName));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemID,CEnumCore::TagFormat::TLV_STRING,strlen(allItemID),(unsigned char *)mIni.wcharToChar(allItemID));//玩家帐号
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(allNum),(unsigned char *)mIni.wcharToChar(allNum));//玩家帐号
		
		
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID


		int midlength = socketdata.EnBody();
		theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Import_Item);//发送查询玩家资料信息的请求
		::EnableWindow(this->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
		dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//当前的状态为发送查询请求
		socketdata.Destroy();//销毁CSocketData局部变量
	}
}

bool CGTOWNImport::ReadXls(CString m_filePath,CString* m_allUserName,CString* m_allItemID,CString * m_Num)
{
	try
	{
		CoInitialize(NULL);
		_ConnectionPtr m_pConnection;
		_RecordsetPtr	m_pRecordset;
		CString ConnectionString="";
		CString allusername="";
		ConnectionString = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");   
		ConnectionString += m_filePath;   //excel   file   name   
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

		if(m_pRecordset->adoEOF) AfxMessageBox("该文档没有内容");
		//////第一行不读
		while(!m_pRecordset->adoEOF)
		{
			if(m_pRecordset->GetFields()->GetItem("Account")->Value.vt==VT_NULL
				||m_pRecordset->GetFields()->GetItem("ItemID")->Value.vt==VT_NULL
				||m_pRecordset->GetFields()->GetItem("Num")->Value.vt==VT_NULL) 
			{
				AfxMessageBox("格式错误");
				break;
			}
			CString tmpusername=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem("Account")->GetValue());
			*m_allUserName += tmpusername;
			*m_allUserName += "|";

			CString tmpItemID=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem("ItemID")->GetValue());
			*m_allItemID += tmpItemID;
			*m_allItemID += "|";

			CString tmpNum=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem("Num")->GetValue());
			*m_Num += tmpNum;
			*m_Num += "|";

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
	return TRUE;
}
