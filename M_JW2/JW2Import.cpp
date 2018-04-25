// JW2Import.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2Import.h"
#include ".\JW2Import.h"


// CJW2Import �Ի���

IMPLEMENT_DYNAMIC(CJW2Import, CDialog)
CJW2Import::CJW2Import(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2Import::IDD, pParent)
{
}

CJW2Import::~CJW2Import()
{
}

void CJW2Import::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
}


BEGIN_MESSAGE_MAP(CJW2Import, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_COMFIRM, OnBnClickedComfirm)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CJW2Import::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�	


	CRect rs;
	GetClientRect(rs);//��ȡ�Ի���Ĵ�С��Ϣ


	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//��ʼ�����Ի���

	theApp.operJW2.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CJW2Import::InitUI()
{

	SetDlgItemText(IDC_LBLUISERVER,theApp.operJW2.ReadValue("MJW2","UIC_UI_LblServer"));
	SetDlgItemText(IDUICANCEL,theApp.operJW2.ReadValue("MJW2","Cancel"));

	tbcResult.InsertItem(0,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgKickPlayer"));
	tbcResult.InsertItem(1,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgAccountClose"));
	tbcResult.InsertItem(2,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgAccountOpen"));

}

//�����ݼ���Ӧ����
BOOL CJW2Import::PreTranslateMessage(MSG* pMsg)
{
   	return FALSE;
}

// �Զ��ı��С
void CJW2Import::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);


}

//���ñ�����ɫ
HBRUSH CJW2Import::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}



// ���շ�����Ϣ
LRESULT CJW2Import::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���


	CIni mIni;

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,sIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operJW2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_Import_KickPlayer_Resp:
	case CEnumCore::Message_Tag_ID::JW2_Import_AccountClose_Resp:
	case CEnumCore::Message_Tag_ID::JW2_Import_AccountOpen_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ�������
		}
		break;
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

// �رնԻ���
void CJW2Import::OnBnClickedUicancel()
{

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Close");//�رմ���
	OnClose();
}

// �رնԻ���
void CJW2Import::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CJW2Import::OnBnClickedBrowse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char path[256];
	GetCurrentDirectory(256,path);
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����

	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"�ļ�����(*.xls)|*.xls||");


	if(lpszOpenFile->DoModal()==IDOK)//�������Ի���ȷ����ť
	{
		CString szGetName;
		szGetName=lpszOpenFile->GetPathName();
		SetDlgItemText(IDC_FILENAME,szGetName);
		SetCurrentDirectory(path);

	}
	delete lpszOpenFile;
}

void CJW2Import::OnBnClickedComfirm()
{
	CIni mIni;		
	CString allUserName;
	CString filename;
	GetDlgItemText(IDC_FILENAME,filename);
	ReadXls(filename,&allUserName);
	if(strlen(allUserName)>2000)
	{
		MessageBox("�������������,���ڷ���");
	}
	else
	{
		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int userbyID = theApp.UserByID;//����ԱID
		GetDlgItemText(IDC_CMBUISERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP


		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_BoardMessage,CEnumCore::TagFormat::TLV_STRING,strlen(allUserName),(unsigned char *)mIni.wcharToChar(allUserName));//����ʺ�
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID


		int midlength = socketdata.EnBody();
		switch(tbcResult.GetCurSel())
		{
		case 0:
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_Import_KickPlayer);//���Ͳ�ѯ���������Ϣ������
			break;
		case 1:
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_Import_AccountClose);//���Ͳ�ѯ���������Ϣ������
			break;
		case 2:
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_Import_AccountOpen);//���Ͳ�ѯ���������Ϣ������
			break;
		default:
			break;
		}

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
}

void CJW2Import::ReadXls(CString m_filePath,CString* m_allUserName)
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

		if(m_pRecordset->adoEOF) AfxMessageBox("���ĵ�û������");
		//////��һ�в���
		while(!m_pRecordset->adoEOF)
		{
			if(m_pRecordset->GetFields()->GetItem((long)1)->Value.vt==VT_NULL) break;
			CString tmpusername=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem((long)1)->GetValue());
			*m_allUserName += tmpusername;
			*m_allUserName += "|";
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

	}
}
