// SDOMatchMul.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOMatchMul.h"
#include ".\sdomatchmul.h"


// CSDOMatchMul �Ի���

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


// CSDOMatchMul ��Ϣ�������

// ��ʼ���Ի���
BOOL CSDOMatchMul::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();
	ServerIP = "";// ������IP
	AllServer = false;// �Ƿ������д������͹���
	//��������
	SenceName = "";

	MiniuteOpen = 0;//���ŷ���
	MiniuteUnit = 0;//���Ϸ���
	GCash = 0;//G��

	listServer.SetExtendedStyle(listServer.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);//�������б�����Ҫ��ʾCheckBox
	listServer.InsertColumn(0,theApp.operSDO.ReadValue("MSDO","NI_UI_ServerList"),LVCFMT_CENTER,150,-1);

	CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ

	CRect srcRect;
	CRect newRect;

	if( listServer.m_hWnd != NULL )   
	{
		listServer.GetWindowRect(srcRect);//��ȡlistResult�Ĵ�С��Ϣ
		listRWidth = srcRect.right - srcRect.left;//�õ�listResult�Ŀ����Ϣ

		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 8;

		listServer.MoveWindow(newRect);//����listResult��λ��
	}  
	
	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operSDO.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
//��ʼ����ʾ�ַ�
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
	
	SetDlgItemText(IDC_BTQUERYSENCE,theApp.operSDO.ReadValue("MSDO","QuerySence"));//��ѯ����
	WeekDay();
	Mode();
}

// �Զ��ı��С
void CSDOMatchMul::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if( listServer.m_hWnd != NULL )   
	{
		newRect.top = rs.top + 45;		
		newRect.left = rs.left + 10;
		newRect.right = newRect.left + listRWidth;
		newRect.bottom = rs.bottom - 10;

		listServer.MoveWindow(newRect);//����listResult��λ��
	}  
}

//���ñ�����ɫ
HBRUSH CSDOMatchMul::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}


// ѡ��������Ϸ���������з���
void CSDOMatchMul::OnBnClickedCheckselectall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(AllServer == false)
	{
		for(int i=0; i<listServer.GetItemCount(); i++)
		{
			listServer.SetCheck(i);//ѡ�����е���Ϸ������
		}
		listServer.EnableWindow(true);//����Ϸ�������б��ΪDisable��״̬
		AllServer = true;
	}
	else
	{
		for(int i=0; i<listServer.GetItemCount(); i++)
		{
			listServer.SetCheck(i,false);//ȡ��ѡ�����е���Ϸ������
		}
		//listResult.EnableWindow(true);//����Ϸ�������б��ΪEnable��״̬
		AllServer = false;
	}
}

//����Ҫ���͹������Ϸ�������б�
void CSDOMatchMul::ReturnServerIP(char* allServerIP)
{
	CString serverName="";
	int num=0;
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			ServerList.Lookup(i+1,serverName);//���ҷ�����IP
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

//����Ҫ���͹������Ϸ�����������б�
CString CSDOMatchMul::ReturnServerName()
{
	CString rServerName = "";
	CString serverName = "";
	for(int i=0;i<listServer.GetItemCount();i++)
	{
		if(listServer.GetCheck(i))
		{
			serverName=listServer.GetItemText(i,0);//���ҷ���������
			rServerName += serverName;
			rServerName += ",";//�����еķ�����IP��","����
		}
	}
	return rServerName;
}

// �رնԻ���
void CSDOMatchMul::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//�رմ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_ETCHECKSERVER,"");
	cmbWeekDay.SetCurSel(0);
	SetDlgItemText(IDC_ETMINIUTEOPEN,"");
	SetDlgItemText(IDC_ETMINIUTEUNIT,"");
	SetDlgItemText(IDC_ETCHARGEGCASH,"");
	cmbSence.SetCurSel(0);
	cmbMode.SetCurSel(0);

}

//����������
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

//�������ģʽ
void CSDOMatchMul::Mode()
{
	cmbMode.ResetContent();
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type1"));//��ͨ����
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type2"));//Showtime
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type3"));//����ս����
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type4"));//��������
	cmbMode.SetCurSel(0);
}

//��ѯ��������
void CSDOMatchMul::SenceQuery()
{
	try
	{		
		CIni mIni;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_QUERY))//��������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// ���շ�����Ϣ
LRESULT CSDOMatchMul::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;
	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operSDO.ReadValue("MSDO","Main_UI_SENDDATAERROR"),theApp.operSDO.ReadValue("MSDO","ERROR"),0);//Main_UI_ParseData		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;
	switch(theApp.m_TagID)
	{
	case CEnumCore::Message_Tag_ID::SERVERINFO_IP_QUERY_RESP://��ѯ�������б���Ϣ�Ļ�Ӧ
		{
			listServer.EnableWindow(true);

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);//��ȡ������Ϣ�еĵ�һ��ģ��
			if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)//�����һ��ģ���TagName��MESSAGE����ʾ�����˴�����Ϣ����ʾ������Ϣ������
			{
				MessageBox((LPCSTR)&m_tflv.lpdata,theApp.operSDO.ReadValue("MSDO","Error"),0);
				socketdata.Destroy();
				return false;
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//��ȡ���еķ�����IP
				ServerList.SetAt(i,ServerIP);//��ӵ�CMap��Ķ���ServerList��
			}

			listServer.DeleteAllItems();//����������б��е���������
			CString serverName = "";
			int nRow = 0;
			for(int i=0;i<socketdata.getQueryNum();i++)
			{
				nRow = listServer.InsertItem(i,"");
				serverName = (LPSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::ServerInfo_City).lpdata;//��ȡ��Ϸ����������
				listServer.SetItemText(nRow,0,serverName);//����Ϸ������������ӵ��������б���
			}

			
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_QUERY_RESP:////��ѯ����
		{
			if(!SenceList.IsEmpty())
			{
				SenceList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int nItem = StrToInt((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::SDO_SenceID).lpdata);//�õ�������IP
				SenceList.SetAt(i,nItem);//
			}

			theApp.operSDO.BuildComboxScene(&socketdata,&cmbSence);
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_INSERTALL_RESP://������ӳ���
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operSDO.ShowResult(result);//��ʾ�������
		}
		break;
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//������ӳ���
void CSDOMatchMul::OnBnClickedSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;
		CString strMode="";
		int iPos=((CComboBox*)GetDlgItem(IDC_CMBMODE))->GetCurSel();//��ǰѡ�е���//IDC_CMBMODE
		if(iPos==0)
			strMode="10";
		else if(iPos==1)
			strMode="13";
		else if(iPos==2)
			strMode="12";
		else if(iPos==3)
			strMode="11";

		int nDay=((CComboBox*)GetDlgItem(IDC_CMBWEEKDAY))->GetCurSel();//��ǰѡ�е���

		CString strSence="";
		GetDlgItemText(IDC_CMBSENCE,strSence);

		MiniuteOpen=GetDlgItemInt(IDC_ETMINIUTEOPEN);
		MiniuteUnit=GetDlgItemInt(IDC_ETMINIUTEUNIT);
		GCash=GetDlgItemInt(IDC_ETCHARGEGCASH);

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
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

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(strServerIP),(unsigned char *)mIni.wcharToChar(strServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_IsBattle,CEnumCore::TagFormat::TLV_STRING,strlen(strMode),(unsigned char *)mIni.wcharToChar(strMode));//mode
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(strSence),(unsigned char *)mIni.wcharToChar(strSence));//sence

		_itoa(UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

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
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
			
	}
	catch(...)
	{
	}
}

//��ѯ����
void CSDOMatchMul::OnBnClickedBtquerysence()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SenceQuery();
}
