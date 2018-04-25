// GTOWNImport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNImport.h"
#include ".\GTOWNImport.h"


// CGTOWNImport �Ի���

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

// ��ʼ���Ի���
BOOL CGTOWNImport::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�	


	CRect rs;
	GetClientRect(rs);//��ȡ�Ի���Ĵ�С��Ϣ


	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Create");//��ʼ�����Ի���

	theApp.operGTOWN.GetServerList();
	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CGTOWNImport::InitUI()
{

	SetDlgItemText(IDC_LBLUISERVER,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_LblServer"));
	SetDlgItemText(IDUICANCEL,theApp.operGTOWN.ReadValue("MGTOWN","Cancel"));
}

//�����ݼ���Ӧ����
BOOL CGTOWNImport::PreTranslateMessage(MSG* pMsg)
{
   	return FALSE;
}

// �Զ��ı��С
void CGTOWNImport::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);


}

//���ñ�����ɫ
HBRUSH CGTOWNImport::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}



// ���շ�����Ϣ
LRESULT CGTOWNImport::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���


	CIni mIni;

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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

			theApp.operGTOWN.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_Import_Item_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGTOWN.ShowResult(result);//��ʾ�������
		}
		break;
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

// �رնԻ���
void CGTOWNImport::OnBnClickedUicancel()
{

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//�رմ���
	OnClose();
}

// �رնԻ���
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
		MessageBox("���ⲻ��Ϊ��");
		return;
	}
	GetDlgItemText(IDC_EDITCONTENT,strText);
	if(strlen(strText)<1)
	{
		MessageBox("���ݲ���Ϊ��");
		return;
	}
	GetDlgItemText(IDC_FILENAME,filename);
	if(!ReadXls(filename,&allUserName,&allItemID,&allNum))
	{
		AfxMessageBox("��ʽ����");
		return;
	}
	if(strlen(allUserName)>2000||strlen(allItemID)>2000||strlen(allNum)>2000)
	{
		MessageBox("�������������,���ڷ���");
		return;
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
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP


		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_MailTitle,CEnumCore::TagFormat::TLV_STRING,strlen(strTitle),(unsigned char *)mIni.wcharToChar(strTitle));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(strText),(unsigned char *)mIni.wcharToChar(strText));//������IP

		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(allUserName),(unsigned char *)mIni.wcharToChar(allUserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemID,CEnumCore::TagFormat::TLV_STRING,strlen(allItemID),(unsigned char *)mIni.wcharToChar(allItemID));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(allNum),(unsigned char *)mIni.wcharToChar(allNum));//����ʺ�
		
		
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID


		int midlength = socketdata.EnBody();
		theApp.operGTOWN.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_Import_Item);//���Ͳ�ѯ���������Ϣ������
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
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

		if(m_pRecordset->adoEOF) AfxMessageBox("���ĵ�û������");
		//////��һ�в���
		while(!m_pRecordset->adoEOF)
		{
			if(m_pRecordset->GetFields()->GetItem("Account")->Value.vt==VT_NULL
				||m_pRecordset->GetFields()->GetItem("ItemID")->Value.vt==VT_NULL
				||m_pRecordset->GetFields()->GetItem("Num")->Value.vt==VT_NULL) 
			{
				AfxMessageBox("��ʽ����");
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
