// WAMailSend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_WA.h"
#include "WAMailSend.h"
#include ".\wamailsend.h"


// CWAMailSend �Ի���

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


// CWAMailSend ��Ϣ�������

// ��ʼ���Ի���
BOOL CWAMailSend::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�

	ServerIP = "";
	UserNick = "";
	MailTitle = "";
	MailContent = "";
	UserNum=0;//�ʼ��ɫ������Ϊ0
	mCurNum = 0;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operWA.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}
	return TRUE;
}

// ��ʼ����ʾ�ַ�
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

//���ñ�����ɫ
HBRUSH CWAMailSend::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ȡѡ���ServerIP
void CWAMailSend::OnCbnSelchangeCmbserver()
{
	try
	{
		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ������Ϊ��
		{
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
	}
	catch(...)
	{
	}
}

//ѡ�����������ʼ����ļ�
void CWAMailSend::OnBnClickedBtnbrowse()
{
	char path[256];
	GetCurrentDirectory(256,path);
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����

	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"�ļ�����(*.xls)|*.xls||");

	if(lpszOpenFile->DoModal()==IDOK)//�������Ի���ȷ����ť
	{
		CString szGetName;
		szGetName=lpszOpenFile->GetPathName();
		SetDlgItemText(IDC_EDITPATH,szGetName);
		SetCurrentDirectory(path);
	}
	delete lpszOpenFile;
}

//���������ʼ���Ϣ
void CWAMailSend::OnBnClickedBtnsend()
{
	try
	{
		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ������Ϊ��
		{
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
			
		//��ȡҪ������ӵĽ�ɫ��txt�ļ�				
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
		UserList.Lookup(mCurNum,UserNick);//��CMap��Ķ���UserList�л�ȡ��ɫ��
		TitleList.Lookup(mCurNum,MailTitle);//��CMap��Ķ���TitleList�л�ȡ�ʼ�����
		ContentList.Lookup(mCurNum,MailContent);//��CMap��Ķ���SubjectList�л�ȡ�ʼ�����
		SendMail();
	}
	catch(...)
	{
	}
}

//�����ʼ�
void CWAMailSend::SendMail()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,20);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(""),(unsigned char *)mIni.wcharToChar(""));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(""),(unsigned char *)mIni.wcharToChar(""));//��ɫΨһIDKEY

		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

		socketdata.AddTFLV(CEnumCore::TagName::WA_MailSubject,CEnumCore::TagFormat::TLV_STRING,strlen(MailTitle),(unsigned char *)mIni.wcharToChar(MailTitle));//�ʼ�����
		socketdata.AddTFLV(CEnumCore::TagName::WA_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(MailContent),(unsigned char *)mIni.wcharToChar(MailContent));//�ʼ�����
		
		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_SendMails_Op);//�����ʼ�

		//::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

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

		_variant_t TheValue; //VARIANT��������
		while(!m_pRecordset->adoEOF)
		{
			UserNum++;//ѭ�����ӣ���ȡ�������
			tmpNum.Format("%i",UserNum);

			TheValue = m_pRecordset->GetCollect(_variant_t((long)0));
			if(TheValue.vt==VT_NULL) 
			{
				MessageBox(tmpNum+"��"+theApp.operWA.ReadValue("MWA","IM_Warn_RoleNameNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return false;
			}

			UserNick=(LPCSTR)_bstr_t(TheValue);//��ȡ��ɫ��
			UserNick.Trim();
			if(UserNick == "")//��ҽ�ɫ������Ϊ��
			{
				MessageBox(tmpNum+"��"+theApp.operWA.ReadValue("MWA","IM_Warn_RoleNameNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return false;
			}
			UserList.SetAt(UserNum,UserNick);//�����ɫ��

			TheValue = m_pRecordset->GetCollect(_variant_t((long)1));
			MailTitle=(LPCSTR)_bstr_t(TheValue);//��ȡ�ʼ�����
			MailTitle.Trim();
			if(MailTitle == "")//�ʼ����ⲻ��Ϊ��
			{
				MessageBox(tmpNum+"��"+theApp.operWA.ReadValue("MWA","IM_Warn_MailSubject"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return false;
			}
			if(strlen(MailTitle) > 20)//�ʼ����ⲻ�ܳ���20���ַ�
			{
				MessageBox(tmpNum+"��"+theApp.operWA.ReadValue("MWA","IM_Warn_SubjectTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return false;
			}
			TitleList.SetAt(UserNum,MailTitle);//�����ʼ�����

			TheValue = m_pRecordset->GetCollect(_variant_t((long)2));
			MailContent=(LPCSTR)_bstr_t(TheValue);//��ȡ�ʼ�����
			if(MailContent == "")//�ʼ����ݲ���Ϊ��
			{
				MessageBox(tmpNum+"��"+theApp.operWA.ReadValue("MWA","IM_Warn_MailContent"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return false;
			}
			if(strlen(MailContent) > 200)//�ʼ����ݲ��ܳ���200���ַ�
			{
				MessageBox(tmpNum+"��"+theApp.operWA.ReadValue("MWA","IM_Warn_ContentTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return false;
			}
			ContentList.SetAt(UserNum,MailContent);//�����ʼ�����

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

//������Ϣ
void CWAMailSend::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITPATH,"");
	
	mCurNum = UserNum;
	SetDlgItemText(IDC_LBLMAIN,"");
	SetDlgItemText(IDC_LBLPROG,"");
	progMail.SetPos(0);
}

// ���շ�����Ϣ
LRESULT CWAMailSend::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	socketdata.DeBody(lpReceive,bodyLength);

	int pageCount = 0;
	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ�������б���Ϣ�Ļ�Ӧ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
			}
			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_SendMails_Op_Resp://���������ʼ�
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
				UserList.Lookup(mCurNum,UserNick);//��CMap��Ķ���UserList�л�ȡ��ɫ��
				TitleList.Lookup(mCurNum,MailTitle);//��CMap��Ķ���TitleList�л�ȡ�ʼ�����
				ContentList.Lookup(mCurNum,MailContent);//��CMap��Ķ���SubjectList�л�ȡ�ʼ�����

				SendMail();
				return false;					
			}
			tmpNum.Format("%i",mCurNum);
			SetDlgItemText(IDC_LBLPROG,theApp.operWA.ReadValue("MWA","IM_UI_LblMailFirst")+tmpNum+theApp.operWA.ReadValue("MWA","IM_UI_LblMailSecond")+UserNick+theApp.operWA.ReadValue("MWA","IM_UI_LblMailThird")+Result+theApp.operWA.ReadValue("MWA","IM_UI_LblMailFourth"));	
			progMail.SetPos(mCurNum);

			theApp.operWA.ShowResult(Result);//��ʾ���ؽ��
			SetDlgItemText(IDC_EDITPATH,"");

			GetDlgItem(IDC_BTNSEND)->ShowWindow(SW_SHOW);
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ���ؽ��
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}
// �رնԻ���
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