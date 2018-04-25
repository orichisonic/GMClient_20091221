// SDOMatchManager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOMatchManager.h"
#include ".\sdomatchmanager.h"


// CSDOMatchManager �Ի���

IMPLEMENT_DYNAMIC(CSDOMatchManager, CDialog)
CSDOMatchManager::CSDOMatchManager(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOMatchManager::IDD, pParent)
{
}

CSDOMatchManager::~CSDOMatchManager()
{
}

void CSDOMatchManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBWEEKDAY, cmbWeekDay);
	DDX_Control(pDX, IDC_CMBSENCE, cmbSence);
	DDX_Control(pDX, IDC_CMBMODE, cmbMode);
	DDX_Control(pDX, IDC_LISTMATCH, listMatch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
}


BEGIN_MESSAGE_MAP(CSDOMatchManager, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BTOK, OnBnClickedBtok)
	ON_NOTIFY(NM_CLICK, IDC_LISTMATCH, OnNMClickListmatch)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTMATCH, OnNMDblclkListmatch)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTMATCH, OnLvnColumnclickListmatch)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
END_MESSAGE_MAP()


// CSDOMatchManager ��Ϣ�������

// ��ʼ���Ի���
BOOL CSDOMatchManager::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();// ��ʼ����ʾ�ַ�

	ShowMatch();

	SetProp(listMatch.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listMatch.GetSafeHwnd(),"����˳��",(HANDLE)1);


	ServerIP = "";
//	strServer="";

	nItem=0;
	MiniuteOpen=0;
	MiniuteUnit=0;
	GCash=0;
	pageInfo = false;
	
	
	SetProp(listMatch.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listMatch.GetSafeHwnd(),"����˳��",(HANDLE)1);

	CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ


	CRect srcRect;
	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
		GrpSearch.GetWindowRect(srcRect);//��ȡGrpSearch�Ĵ�С��Ϣ
		grpHeight = srcRect.bottom - srcRect.top;//�õ�GrpSearch�ĸ߶���Ϣ

		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��
	}

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//��ȡtbcResult�Ĵ�С��Ϣ
		tbcHeight = srcRect.bottom - srcRect.top;//�õ�tbcResult�ĸ߶���Ϣ

		newRect.top = rs.top + 4 + grpHeight;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		GrpPage.GetWindowRect(srcRect);//��ȡGrpPage�Ĵ�С��Ϣ
		grpPHeight = srcRect.bottom - srcRect.top;//�õ�GrpPage�ĸ߶���Ϣ

		newRect.top = rs.top + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listMatch.m_hWnd != NULL)
	{
		newRect.top = rs.top +4+ grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMatch.MoveWindow(newRect);
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

// ��ʼ����ʾ�ַ�
void CSDOMatchManager::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","MM_UI_MatchManager"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operSDO.ReadValue("MSDO","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operSDO.ReadValue("MSDO","UIC_UI_LblServer"));
	SetDlgItemText(IDC_BTOK,theApp.operSDO.ReadValue("MSDO","Search"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operSDO.ReadValue("MSDO","UIC_UI_Page"));

	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","AddMatch"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));

	SetDlgItemText(IDC_LBLCHECKEDSERVER,theApp.operSDO.ReadValue("MSDO","CheckedServer"));
	SetDlgItemText(IDC_LBLWEEKDAY,theApp.operSDO.ReadValue("MSDO","WeekDay"));
	SetDlgItemText(IDC_LBLMINIUTEOPEN,theApp.operSDO.ReadValue("MSDO","MiniuteOpen"));
	SetDlgItemText(IDC_LBLMINIUTEUNIT,theApp.operSDO.ReadValue("MSDO","MiniuteUnit"));
	SetDlgItemText(IDC_LBLCHARGEGCASH,theApp.operSDO.ReadValue("MSDO","ChargeGCash"));
	SetDlgItemText(IDC_LBLSENCE,theApp.operSDO.ReadValue("MSDO","Sence"));
	SetDlgItemText(IDC_LBLMODE,theApp.operSDO.ReadValue("MSDO","Mode"));

	tbcResult.InsertItem(0,theApp.operSDO.ReadValue("MSDO","MM_UI_tpgMatch"));
	tbcResult.InsertItem(1,theApp.operSDO.ReadValue("MSDO","MM_UI_tpgAddMatch"));//��ӱ�����Ϣ
	tbcResult.InsertItem(2,theApp.operSDO.ReadValue("MSDO","MM_UI_tpgUpdateMatch"));//�༭������Ϣ

//	WeekDay();
//	Mode();
}

// �Զ��ı��С
void CSDOMatchManager::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
	    newRect.top = rs.top + 4;		
	    newRect.left = rs.left +10;
	    newRect.right = rs.right - 10;
	    newRect.bottom = newRect.top + grpHeight;

	    GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��
	}

	if(tbcResult.m_hWnd != NULL)
	{
	    newRect.top = rs.top + 4 + grpHeight;
	    newRect.bottom = newRect.top + tbcHeight;
	    newRect.left = rs.left +10;
    	newRect.right = rs.right - 10;

	    tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listMatch.m_hWnd != NULL)
	{
		newRect.top = rs.top +4+ grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMatch.MoveWindow(newRect);
	}
}

//���ñ�����ɫ
HBRUSH CSDOMatchManager::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// �رնԻ���
void CSDOMatchManager::OnClose()
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

//�����ݼ���Ӧ����
BOOL CSDOMatchManager::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listMatch.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listMatch);				
				}
				
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listMatch.m_hWnd)
				{
					for(int i=0; i<listMatch.GetItemCount(); i++)
					{
					    listMatch.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listMatch.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

void CSDOMatchManager::OnBnClickedCancel()
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

//��ʾ������Ϣ
void CSDOMatchManager::ShowMatch()
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTMATCH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLCHECKEDSERVER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLWEEKDAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMINIUTEOPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMINIUTEUNIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCHARGEGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMODE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_ETCHECKSERVER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBWEEKDAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMINIUTEOPEN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMINIUTEUNIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCHARGEGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSENCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBMODE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDSEARCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);//
}

//��ʾ������Ϣ
void CSDOMatchManager::ShowOther()
{
	GetDlgItem(IDC_LISTMATCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLCHECKEDSERVER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLWEEKDAY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLMINIUTEOPEN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLMINIUTEUNIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLCHARGEGCASH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSENCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLMODE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_ETCHECKSERVER)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBWEEKDAY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETMINIUTEOPEN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETMINIUTEUNIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETCHARGEGCASH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBSENCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBMODE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDSEARCH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);

	WeekDay();
	Mode();


}

// �л�ѡ����в�ѯ
void CSDOMatchManager::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel()==0)
	{
		ShowMatch();
	}
	else if(tbcResult.GetCurSel()==1)//���
	{
		ShowOther();
		SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","AddMatch"));
		SetDlgItemText(IDC_ETCHECKSERVER,ServerName);
		GetDlgItem(IDC_ETCHECKSERVER)->EnableWindow(false);

		SetDlgItemInt(IDC_ETMINIUTEOPEN,0);
		SetDlgItemInt(IDC_ETMINIUTEUNIT,0);
		SetDlgItemInt(IDC_ETCHARGEGCASH,0);

		SenceQuery();
		
	}
	else if(tbcResult.GetCurSel()==2)//�༭
	{
		ShowOther();
		SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","UpdateMatch"));

		SetDlgItemText(IDC_ETCHECKSERVER,ServerName);
		GetDlgItem(IDC_ETCHECKSERVER)->EnableWindow(false);

		SetDlgItemInt(IDC_ETMINIUTEOPEN,MiniuteOpen);
		SetDlgItemInt(IDC_ETMINIUTEUNIT,MiniuteUnit);
		SetDlgItemInt(IDC_ETCHARGEGCASH,GCash);

		SenceQuery();
	}
	*pResult = 0;
}

////��ѯ������Ϣ
void CSDOMatchManager::OnBnClickedBtok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;

		int index = theApp.operSDO.ReadIntValue("MSDO","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//ÿҳ��ʾ50����¼

		nItem = 0;//��������б�û��ѡ����
		pageInfo=false;
		cmbPage.ResetContent();
		while(listMatch.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			
		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_SelectServer"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
	
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

//��ӻ��߱༭����
void CSDOMatchManager::OnBnClickedSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		UpdateData(true);

		CString MatchOp = "";
		GetDlgItemText(IDSEARCH, MatchOp);

		if(MatchOp == theApp.operSDO.ReadValue("MSDO","AddMatch"))//��ӱ���
		{
			AddMatch();
		}
		else if(MatchOp == theApp.operSDO.ReadValue("MSDO","UpdateMatch"))//�༭����
		{
			UpdateMatch();
		}
	}
	catch(...)
	{
	}
}

//��ӱ���
void CSDOMatchManager::AddMatch()
{
	try
	{
		CIni mIni;
		CString strMode="";
		int iPos=((CComboBox*)GetDlgItem(IDC_CMBMODE))->GetCurSel();//��ǰѡ�е���
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

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
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
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_INSERT))
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

//�༭����
void CSDOMatchManager::UpdateMatch()
{
	try
	{
		CIni mIni;
		CString strMode="";
		int iPos=((CComboBox*)GetDlgItem(IDC_CMBMODE))->GetCurSel();//��ǰѡ�е���
		if(iPos==0)
			strMode="10";
		else if(iPos==1)
			strMode="13";
		else if(iPos==2)
			strMode="12";
		else if(iPos==3)
			strMode="11";

		int nDay=((CComboBox*)GetDlgItem(IDC_CMBWEEKDAY))->GetCurSel();//��ǰѡ�е���

		MiniuteOpen=GetDlgItemInt(IDC_ETMINIUTEOPEN);//���ŷ�����
		MiniuteUnit=GetDlgItemInt(IDC_ETMINIUTEUNIT);//��Ϸ�����
		GCash=GetDlgItemInt(IDC_ETCHARGEGCASH);

		CSocketData socketdata;	
		socketdata.InitCreate(1,11);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int UserByID=theApp.UserByID;
		int SenceID1=0;

		SenceList.Lookup(cmbSence.GetCurSel()+1,SenceID1);
		CString strSence="";
		GetDlgItemText(IDC_CMBSENCE,strSence);

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_IsBattle,CEnumCore::TagFormat::TLV_STRING,strlen(strMode),(unsigned char *)mIni.wcharToChar(strMode));//mode

		_itoa(SenceID1,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//sence

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

		_itoa(SenceID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_UPDATE))
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

//�л���ҳ��
void CSDOMatchManager::OnCbnSelchangeCmbpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//ÿҳ��ʾ50����¼

			while(listMatch.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();

			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_QUERY))//
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
				dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}


			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Error_Page"),theApp.operSDO.ReadValue("MSDO","Error"),0);
	}
}


//����������
void CSDOMatchManager::WeekDay()
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
void CSDOMatchManager::Mode()
{
	cmbMode.ResetContent();
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type1"));//��ͨ����
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type2"));//Showtime
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type3"));//����ս����
	cmbMode.AddString(theApp.operSDO.ReadValue("MSDO","XF_UI_Type4"));//��������
	cmbMode.SetCurSel(0);
}


//��ѯ��������
void CSDOMatchManager::SenceQuery()
{
	try
	{		
		CIni mIni;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		

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
LRESULT CSDOMatchManager::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
			if(!ServerList.IsEmpty())
			{
				ServerList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operSDO.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
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
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_QUERY_RESP:////��ѯ������Ϣ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listMatch,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listMatch,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageInfo = false;//���ܷ�ҳ		
					cmbPage.ResetContent();
					while(listMatch.DeleteColumn(0)){}
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
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_INSERT_RESP:
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_DELETE_RESP:
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


//����������Ϣ�б��
void CSDOMatchManager::OnNMClickListmatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		if(listMatch.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listMatch.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listMatch.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			SenceID=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SenceID")));

			MiniuteOpen=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_StPtMin")));
			MiniuteUnit=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_MatPtMin")));
			GCash=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GCash")));
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

//˫��������Ϣ�б��ɾ��
void CSDOMatchManager::OnNMDblclkListmatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		if(listMatch.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listMatch.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listMatch.SubItemHitTest(&lvinfo);//

			if(nItem >= 0)
			{
				SenceID=atoi(theApp.operSDO.GetValueByColName(&listMatch, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SenceID")));
				DelMatch();

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

//ɾ��������Ϣ
void CSDOMatchManager::DelMatch()
{
	try
	{
		CIni mIni;

		UpdateData(true);
		CString strMsg = theApp.operSDO.ReadValue("MSDO","MM_UI_DelMatch");
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
		{
			return;
		}
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//����9����������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID������״̬������ID��������IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		_itoa(SenceID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

//		_itoa(UserID,strInt,10);
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

//		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_DELETE))//
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//������������
void CSDOMatchManager::OnLvnColumnclickListmatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listMatch,pNMHDR,pResult);
}

