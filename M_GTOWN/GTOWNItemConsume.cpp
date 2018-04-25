// GTOWNItemConsume.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GTOWN.h"
#include "GTOWNItemConsume.h"
#include ".\gtownitemconsume.h"


// CGTOWNItemConsume �Ի���

IMPLEMENT_DYNAMIC(CGTOWNItemConsume, CDialog)
CGTOWNItemConsume::CGTOWNItemConsume(CWnd* pParent /*=NULL*/)
: CDialog(CGTOWNItemConsume::IDD, pParent)
{
}

CGTOWNItemConsume::~CGTOWNItemConsume()
{
}

void CGTOWNItemConsume::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_DTPSTARTDATE, dtcStartDate);
	DDX_Control(pDX, IDC_DTPENDDATE, dtcEndDate);
	DDX_Control(pDX, IDC_CMBUPAGE, cmbUPage);
	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
	DDX_Control(pDX, IDC_CMBUSER, cmbUser);
}


BEGIN_MESSAGE_MAP(CGTOWNItemConsume, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBUPAGE, OnCbnSelchangeCmbupage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_CBN_SELCHANGE(IDC_CMBTYPE, OnCbnSelchangeCmbtype)
	ON_BN_CLICKED(IDC_QUERY, OnBnClickedQuery)
	ON_CBN_SELCHANGE(IDC_CMBUSER, OnCbnSelchangeCmbuser)
END_MESSAGE_MAP()


// CGTOWNItemConsume ��Ϣ�������

// ��ʼ���Ի���
BOOL CGTOWNItemConsume::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();
	ShowUserInfo();
	InitType();

	nItem = 0;
	pageUInfo = false;
	pageInfo = false;
	ServerIP = "";//��ʼ��������IP
	ServerName = "";//��ʼ����������
	Account = "";
	Name = "";
	UserAccount = "";
	UserName = "";//��ʼ����ҽ�ɫ��
	strStartTime = "";//��ʼʱ��
	strEndTime = "";//����ʱ��

	CRect rs;
	GetClientRect(rs);; //��ȡ�Ի���Ĵ�С��Ϣ

	CRect srcRect;
	CRect newRect;
	InitType();//��ʼ�����߹����ʹ������

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listResult��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operGTOWN.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//��ʼ����ʾ�ַ�
void CGTOWNItemConsume::InitUI()
{
	SetWindowText(theApp.operGTOWN.ReadValue("MGTOWN","IC_UI_ItemConsume"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operGTOWN.ReadValue("MGTOWN","Search"));
	SetDlgItemText(IDCANCEL,theApp.operGTOWN.ReadValue("MGTOWN","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operGTOWN.ReadValue("MGTOWN","LI_UI_StartTime"));//��ʼʱ��
	SetDlgItemText(IDC_LBLENDTIME,theApp.operGTOWN.ReadValue("MGTOWN","LI_UI_EndTime"));//����ʱ��


	tbcResult.InsertItem(0,theApp.operGTOWN.ReadValue("MGTOWN","UIC_UI_tpgUserInfo"));//��һ�����Ϣ
	tbcResult.InsertItem(1,theApp.operGTOWN.ReadValue("MGTOWN","IC_UI_tpgItemConsume"));//���߹������Ѽ�¼
}

// �Զ��ı��С
void CGTOWNItemConsume::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listResult��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}
}

//���ñ�����ɫ
HBRUSH CGTOWNItemConsume::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//�����ݼ���Ӧ
BOOL CGTOWNItemConsume::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operGTOWN.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					for(int i=0; i<listUser.GetItemCount(); i++)
					{
						listUser.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listUser.EnsureVisible(i,false);
					}
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					for(int i=0; i<listResult.GetItemCount(); i++)
					{
						listResult.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listResult.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

// ��ѯ���������Ϣ
void CGTOWNItemConsume::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		ShowUserInfo();

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

		nItem = 0;//��������б�û��ѡ����
		pageUInfo = false;//�տ�ʼ���ܷ�ҳ
		cmbUPage.ResetContent();//��ո�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_SelectServer"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITACCOUNT,Account);//��ȡ����ʺ�//IDC_EDITACCOUNT
		GetDlgItemText(IDC_EDITNAME,Name);//��ȡ��ҽ�ɫ��//IDC_EDITNAME
		if((Name == "") && (Account == ""))//����ʺź���ҽ�ɫ������ͬʱΪ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Warn_InputAccount"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//��ҽ�ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_UserInfo_Query))//���Ͳ�ѯ���������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

//��ҳ��ѯ���������Ϣ
void CGTOWNItemConsume::OnCbnSelchangeCmbupage()
{
	try
	{	
		if(pageUInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

			while(listUser.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//��ҽ�ɫ��
			socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//����ʺ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_UserInfo_Query))//���Ͳ�ѯ���������Ϣ������
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
				dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

// �����û��б��浱ǰ�к�
void CGTOWNItemConsume::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// ˫�����������Ϣ���в�ѯ
void CGTOWNItemConsume::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);
				ShowOtherInfo();

				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������

				UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//����ʺ�
				UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//����ǳ�
				UserID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID

				strStartTime = "";//��ʼʱ��
				strEndTime = "";//����ʱ��

				CTime curTime = CTime::GetCurrentTime();

				CTime StartTime;
				dtcStartDate.GetTime(StartTime);//��ȡ��ʼʱ��

				CTime EndTime;
				dtcEndDate.GetTime(EndTime);//��ȡ����ʱ��

				if(StartTime >= curTime)//��ʼʱ�䲻�ܴ��ڵ�ǰʱ��
				{
					MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","LI_Warn_StartTime"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
					return;
				}

				if(EndTime <= StartTime)//����ʱ�䲻��С�ڿ�ʼʱ��
				{
					MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","LI_Warn_TimeSpan"),theApp.operGTOWN.ReadValue("MPAL","Warn"),0);
					return;
				}
				strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
				strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��



			//	ItemConsume();//���߹������Ѽ�¼��ѯ
			}
		}
		else
		{
			nItem = 0;
		}
	}*/
	*pResult = 0;
}

// �л�ѡ����в�ѯ
void CGTOWNItemConsume::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//��ʾ�û�������Ϣ
	}
	else
	{
		ShowOtherInfo();

	/*	pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//����ʺ�
			UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//����ǳ�
			UserID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID

			strStartTime = "";//��ʼʱ��
			strEndTime = "";//����ʱ��

			CTime curTime = CTime::GetCurrentTime();

			CTime StartTime;
			dtcStartDate.GetTime(StartTime);//��ȡ��ʼʱ��

			CTime EndTime;
			dtcEndDate.GetTime(EndTime);//��ȡ����ʱ��

			if(StartTime >= curTime)//��ʼʱ�䲻�ܴ��ڵ�ǰʱ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","LI_Warn_StartTime"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
				return;
			}

			if(EndTime <= StartTime)//����ʱ�䲻��С�ڿ�ʼʱ��
			{
				MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","LI_Warn_TimeSpan"),theApp.operGTOWN.ReadValue("MPAL","Warn"),0);
				return;
			}
			strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
			strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

			InitType();//��ʼ�����߹����ʹ������

			if(tbcResult.GetCurSel()==1)
			{
				ItemConsume();//���߹������Ѽ�¼��ѯ
			}
		}*/
	}
	*pResult = 0;
}

//���߹������Ѽ�¼��ѯ
void CGTOWNItemConsume::ItemConsume()
{
	try
	{
		CIni mIni;

		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");
		int iType=cmbType.GetCurSel();
		int iUser=cmbUser.GetCurSel();
		int ItemType=iUser*2+iType; 

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,20);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����,��ʼʱ�䣬����ʱ��
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		_itoa(ItemType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_Type,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����
		
		CString ItemName;
		GetDlgItemText(IDC_ITEMNAME,ItemName);
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//����ʺ�


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::GT_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::GT_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//����ʱ��


		int midlength = socketdata.EnBody();
		if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_ItemConsume_Query))//���߹������Ѽ�¼
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_DetailInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}

//�л����Ͳ�ѯ���߹������Ѽ�¼
void CGTOWNItemConsume::OnCbnSelchangeCmbtype()
{
	try
	{
		CIni mIni;
		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		int iType=cmbType.GetCurSel();
		int iUser=cmbUser.GetCurSel();
		int ItemType=iUser*2+iType; 

		CSocketData socketdata;	
		socketdata.InitCreate(1,20);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����,��ʼʱ�䣬����ʱ��
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		_itoa(ItemType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_Type,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

		CString ItemName;
		GetDlgItemText(IDC_ITEMNAME,ItemName);
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//����ʺ�


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::GT_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::GT_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//����ʱ��

		int midlength = 0;
		switch(tbcResult.GetCurSel())
		{
		case 1:
			{
				midlength=socketdata.EnBody();
				if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_ItemConsume_Query))//���߹������Ѽ�¼
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
					dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		default:
			break;
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_DetailInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}


//��ҳ���в�ѯ
void CGTOWNItemConsume::OnCbnSelchangeCmbpage()
{
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");//ÿҳ��ʾ50����¼

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};
			int iType=cmbType.GetCurSel();
			int iUser=cmbUser.GetCurSel();
			int ItemType=iUser*2+iType; 

			CSocketData socketdata;	
			socketdata.InitCreate(1,20);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(UserID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

			_itoa(ItemType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::GT_Type,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

			CString ItemName;
			GetDlgItemText(IDC_ITEMNAME,ItemName);
			socketdata.AddTFLV(CEnumCore::TagName::GT_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//����ʺ�


			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			socketdata.AddTFLV(CEnumCore::TagName::GT_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��ʼʱ��
			socketdata.AddTFLV(CEnumCore::TagName::GT_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//����ʱ��

			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					midlength=socketdata.EnBody();
					if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_ItemConsume_Query))//��ҳ��ѯ���߹������Ѽ�¼
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			default:
				break;

			}
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_Page"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}

}

// ���շ�����Ϣ
LRESULT CGTOWNItemConsume::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","Main_UI_ParseData"),theApp.operGTOWN.ReadValue("MGTOWN","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	int pageCount = 0;

	switch (theApp.m_TagID)
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

			theApp.operGTOWN.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_UserInfo_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageUInfo = false;//���ܷ�ҳ		
					cmbUPage.ResetContent();
					while(listUser.DeleteColumn(0)){}
				}
				else
				{
					cmbUPage.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUPage.AddString(str);
					}
					cmbUPage.SetCurSel(0);
					if(pageCount == 1)
					{
						pageUInfo = false;
					}
					else
					{
						pageUInfo = true;
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::GT_ItemConsume_Query_Resp://��ѯ���߹������Ѽ�¼�Ļ�Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operGTOWN.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageInfo = false;//���ܷ�ҳ		
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
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
	default:
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return FALSE;
}

//������߹�����������
void CGTOWNItemConsume::InitType()
{
	cmbType.ResetContent();
	cmbType.AddString("�м��");
	cmbType.AddString("����");
	cmbType.SetCurSel(0);
	cmbUser.ResetContent();
	cmbUser.AddString("���ͷ�");//���ͷ�
	cmbUser.AddString("���ܷ�");//���ܷ�
	cmbUser.SetCurSel(0);
}

// ��ʾ��ɫ������Ϣ
void CGTOWNItemConsume::ShowUserInfo()
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

}

//��ʾ������Ϣ
void CGTOWNItemConsume::ShowOtherInfo()
{
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

}

//�����û�������Ϣ��������������
void CGTOWNItemConsume::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CGTOWNItemConsume::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operGTOWN.SortListInfo(&listResult,pNMHDR,pResult);
}

//ʹ�ùرհ�ť
void CGTOWNItemConsume::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	CTime curTime = CTime::GetCurrentTime();//��ȡ��ǰʱ��
	dtcStartDate.SetTime(&curTime);
	dtcEndDate.SetTime(&curTime);
	ShowUserInfo();
}

// �رնԻ���
void CGTOWNItemConsume::OnClose()
{
	dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}

	DestroyWindow();
	CDialog::OnClose();
}
void CGTOWNItemConsume::OnBnClickedQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pageInfo = false;
	cmbPage.ResetContent();
	while(listResult.DeleteColumn(0)){}// �������б��е���������

	if((listUser.GetItemCount() > 0) && (nItem >= 0))
	{
		tbcResult.SetCurSel(1);
		ShowOtherInfo();
		UserAccount = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_Account"));//����ʺ�
		UserName = theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserNick"));//����ǳ�
		UserID= atoi(theApp.operGTOWN.GetValueByColName(&listUser, nItem, theApp.operGTOWN.ReadValue("MGTOWN","GT_UserID")));//���ID

		strStartTime = "";//��ʼʱ��
		strEndTime = "";//����ʱ��

		CTime curTime = CTime::GetCurrentTime();

		CTime StartTime;
		dtcStartDate.GetTime(StartTime);//��ȡ��ʼʱ��

		CTime EndTime;
		dtcEndDate.GetTime(EndTime);//��ȡ����ʱ��

		if(StartTime >= curTime)//��ʼʱ�䲻�ܴ��ڵ�ǰʱ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","LI_Warn_StartTime"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),0);
			return;
		}

		if(EndTime <= StartTime)//����ʱ�䲻��С�ڿ�ʼʱ��
		{
			MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","LI_Warn_TimeSpan"),theApp.operGTOWN.ReadValue("MPAL","Warn"),0);
			return;
		}
		strStartTime = StartTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		strEndTime = EndTime.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��
		ItemConsume();

	}
	
}

void CGTOWNItemConsume::OnCbnSelchangeCmbuser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;
		int index = theApp.operGTOWN.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operGTOWN.ReadIntValue("MGTOWN","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		int iType=cmbType.GetCurSel();
		int iUser=cmbUser.GetCurSel();
		int ItemType=iUser*2+iType; 

		CSocketData socketdata;	
		socketdata.InitCreate(1,20);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����,��ʼʱ�䣬����ʱ��
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::GT_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::GT_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_UserID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�ID

		_itoa(ItemType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::GT_Type,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

		CString ItemName;
		GetDlgItemText(IDC_ITEMNAME,ItemName);
		socketdata.AddTFLV(CEnumCore::TagName::GT_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//����ʺ�


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::GT_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::GT_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//����ʱ��

		int midlength = 0;
		switch(tbcResult.GetCurSel())
		{
		case 1:
			{
				midlength=socketdata.EnBody();
				if(theApp.operGTOWN.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::GT_ItemConsume_Query))//���߹������Ѽ�¼
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
					dlgStatus = theApp.operGTOWN.ReadIntValue("MGTOWN","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		default:
			break;
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","UIC_Error_DetailInfo"),theApp.operGTOWN.ReadValue("MGTOWN","Error"),0);
	}
}
