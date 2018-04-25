// SDOSenceSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOSenceSet.h"
#include ".\sdosenceset.h"


// CSDOSenceSet �Ի���

IMPLEMENT_DYNAMIC(CSDOSenceSet, CDialog)
CSDOSenceSet::CSDOSenceSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOSenceSet::IDD, pParent)
{
}

CSDOSenceSet::~CSDOSenceSet()
{
}

void CSDOSenceSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_LISTSENCE, listSence);
}


BEGIN_MESSAGE_MAP(CSDOSenceSet, CDialog)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTSENCE, OnLvnColumnclickListsence)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTSENCE, OnNMClickListsence)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTSENCE, OnNMDblclkListsence)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
END_MESSAGE_MAP()


// CSDOSenceSet ��Ϣ�������

// ��ʼ���Ի���
BOOL CSDOSenceSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();

	nItem=0;
	SenceID=0;
	SenceName="";

	ShowSence();

	CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ


	CRect srcRect;
	CRect newRect;

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//��ȡtbcResult�Ĵ�С��Ϣ
		tbcHeight = srcRect.bottom - srcRect.top;//�õ�tbcResult�ĸ߶���Ϣ

		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}

	if(listSence.m_hWnd != NULL)
	{
		newRect.top = rs.top +4+ tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listSence.MoveWindow(newRect);
	}

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	SenceInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ��ʼ����ʾ�ַ�
void CSDOSenceSet::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","SenceSet"));

	SetDlgItemText(IDC_LBLSENCEID,theApp.operSDO.ReadValue("MSDO","SenceID"));
	SetDlgItemText(IDC_LBLSENCENAME,theApp.operSDO.ReadValue("MSDO","SenceName"));
	
	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","AddSence"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));

	tbcResult.InsertItem(0,theApp.operSDO.ReadValue("MSDO","SenceQuery"));//������ѯ
	tbcResult.InsertItem(1,theApp.operSDO.ReadValue("MSDO","AddSence"));
	tbcResult.InsertItem(2,theApp.operSDO.ReadValue("MSDO","UpdateSence"));
}

//��ʾ�����б���Ϣ
void CSDOSenceSet::ShowSence()
{
	GetDlgItem(IDC_LISTSENCE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLSENCEID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSENCENAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSENCEID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSENCENAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDSEARCH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
}

//��ʾ��������
void CSDOSenceSet::ShowOther()
{
	GetDlgItem(IDC_LISTSENCE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSENCEID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSENCENAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSENCEID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSENCENAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDSEARCH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);
}

//�����б�ͷ����
void CSDOSenceSet::OnLvnColumnclickListsence(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listSence,pNMHDR,pResult);
}

// �Զ��ı��С
void CSDOSenceSet::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rs;
	GetClientRect(rs);

	CRect newRect;
	if(tbcResult.m_hWnd != NULL)
	{
	    newRect.top = rs.top + 4 ;
	    newRect.bottom = newRect.top + tbcHeight;
	    newRect.left = rs.left +10;
    	newRect.right = rs.right - 10;

	    tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}

	if(listSence.m_hWnd != NULL)
	{
		newRect.top = rs.top +4+ tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listSence.MoveWindow(newRect);
	}
}

//���ñ�����ɫ
HBRUSH CSDOSenceSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//�����ݼ���Ӧ����
BOOL CSDOSenceSet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listSence.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listSence);				
				}
				
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listSence.m_hWnd)
				{
					for(int i=0; i<listSence.GetItemCount(); i++)
					{
					    listSence.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listSence.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

//�ر�
void CSDOSenceSet::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//�رմ���	
	DestroyWindow();
	CDialog::OnClose();
}

void CSDOSenceSet::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemInt(IDC_ETSENCEID,0);
	SetDlgItemText(IDC_ETSENCENAME,"");
}


//���ͳ�����Ϣ
void CSDOSenceSet::SenceInfo()
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

//�л�tabCtrl
void CSDOSenceSet::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel()==0)
	{
		ShowSence();
		SenceInfo();
	}
	else if(tbcResult.GetCurSel()==1)//���
	{
		ShowOther();
		SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","AddSence"));
		SetDlgItemInt(IDC_ETSENCEID,0);
		SetDlgItemText(IDC_ETSENCENAME,"");

	}
	else if(tbcResult.GetCurSel()==2)//�༭
	{
		ShowOther();
		SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","UpdateSence"));
		SetDlgItemInt(IDC_ETSENCEID,SenceID);
		SetDlgItemText(IDC_ETSENCENAME,SenceName);
		
	}
	*pResult = 0;
}

//���������б��
void CSDOSenceSet::OnNMClickListsence(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		if(listSence.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listSence.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listSence.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			SenceID=atoi(theApp.operSDO.GetValueByColName(&listSence, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SenceID")));
			SenceName=theApp.operSDO.GetValueByColName(&listSence, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Sence"));

		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

//��ӻ��߱༭����
void CSDOSenceSet::OnBnClickedSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		UpdateData(true);

		CString SenceOp = "";
		GetDlgItemText(IDSEARCH, SenceOp);

		if(SenceOp == theApp.operSDO.ReadValue("MSDO","AddSence"))
		{
			AddSence();
		}
		else if(SenceOp == theApp.operSDO.ReadValue("MSDO","UpdateSence"))
		{
			UpdateSence();
		}
	}
	catch(...)
	{
	}
}

//��ӳ���
void CSDOSenceSet::AddSence()
{
	try
	{
		CIni mIni;
		SenceID=GetDlgItemInt(IDC_ETSENCEID);
		GetDlgItemText(IDC_ETSENCENAME,SenceName);

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int UserByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));
		
		_itoa(UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		///_itoa(SenceID,strInt,10);
		///socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//WeekDay

		

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_CREATE))
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
void CSDOSenceSet::UpdateSence()
{

	try
	{
		CIni mIni;
		SenceID=GetDlgItemInt(IDC_ETSENCEID);
		GetDlgItemText(IDC_ETSENCENAME,SenceName);

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int UserByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));

		_itoa(UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		_itoa(SenceID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//WeekDay



		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_UPDATE))
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
//˫�������б�ɾ��
void CSDOSenceSet::OnNMDblclkListsence(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;

		UpdateData(true);
		CString strMsg = theApp.operSDO.ReadValue("MSDO","SS_UI_DelSence");
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
		{
			return;
		}
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//����9����������ʼʱ�䡢����ʱ�䡢ʱ�������������ݡ�����IP������ԱID������״̬������ID��������IP
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_Sence,CEnumCore::TagFormat::TLV_STRING,strlen(SenceName),(unsigned char *)mIni.wcharToChar(SenceName));
		
		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		_itoa(SenceID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SenceID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHALLENGE_SCENE_DELETE))//
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// ���շ�����Ϣ
LRESULT CSDOSenceSet::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_QUERY_RESP:////��ѯ����
		{
			theApp.operSDO.BuildDataTable(&socketdata,&listSence,&pageCount);//����CListCtrl����
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_DELETE_RESP://SDO_CHALLENGE_SCENE_DELETE
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_CHALLENGE_SCENE_CREATE_RESP:
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