// WAPetLog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_WA.h"
#include "WAPetLog.h"


// CWAPetLog �Ի���

IMPLEMENT_DYNAMIC(CWAPetLog, CDialog)
CWAPetLog::CWAPetLog(CWnd* pParent /*=NULL*/)
	: CDialog(CWAPetLog::IDD, pParent)
{
}

CWAPetLog::~CWAPetLog()
{
}

void CWAPetLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBBASIC, cmbBasic);
	DDX_Control(pDX, IDC_CMBRESULT, cmbResult);

	DDX_Control(pDX, IDC_LISTBASIC, listBasic);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);

	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBLOGTYPE, cmbLogType);
	DDX_Control(pDX, IDC_DATESTART, dtcStartTime);
	DDX_Control(pDX, IDC_DATEEND, dtcEndTime);
}


BEGIN_MESSAGE_MAP(CWAPetLog, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_CBN_SELCHANGE(IDC_CMBBASIC, OnCbnSelchangeCmbbasic)	
	ON_NOTIFY(NM_CLICK, IDC_LISTBASIC, OnNMClickListbasic)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBASIC, OnNMDblclkListbasic)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDC_BTNLOG, OnBnClickedBtnlog)
	ON_CBN_SELCHANGE(IDC_CMBRESULT, OnCbnSelchangeCmbresult)	
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CWAPetLog ��Ϣ�������

// ��ʼ���Ի���
BOOL CWAPetLog::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�	
	nItem = -1;
	pageBasic = false;
	pageResult = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//��ʼ��һЩ˽�б���

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

		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listBasic.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listBasic.MoveWindow(newRect);//���ú�listBasic��λ��

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//���ú�listResult��λ�ã�listResult��listBasic��λ����ȫ�ص�
		}
	}

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���
	if(theApp.operWA.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}
	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CWAPetLog::InitUI()
{
	SetWindowText(theApp.operWA.ReadValue("MWA","PL_UI_PetInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLNAME,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Reset"));

	SetDlgItemText(IDC_LBLLOGTYPE,theApp.operWA.ReadValue("MWA","QL_UI_LogType"));
	SetDlgItemText(IDC_LBLSTARTTIME,theApp.operWA.ReadValue("MWA","NI_UI_StartTime"));
	SetDlgItemText(IDC_LBLENDTIME,theApp.operWA.ReadValue("MWA","NI_UI_EndTime"));
	SetDlgItemText(IDC_BTNLOG,theApp.operWA.ReadValue("MWA","LogSearch"));

	tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","PL_UI_PetLog"));

	cmbLogType.AddString(theApp.operWA.ReadValue("MWA","PL_UI_CatchPetSpirit"));
	cmbLogType.AddString(theApp.operWA.ReadValue("MWA","PL_UI_GainSpirit"));
	cmbLogType.AddString(theApp.operWA.ReadValue("MWA","PL_UI_LoseSpirit"));
	cmbLogType.AddString(theApp.operWA.ReadValue("MWA","PL_UI_SellSpirit"));
}


// �Զ��ı��С
void CWAPetLog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

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
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listBasic.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listBasic.MoveWindow(newRect);//���ú�listBasic��λ��

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//���ú�listResult��λ��
		}
	}
}

//���ñ�����ɫ
HBRUSH CWAPetLog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ����������Ϣ
void CWAPetLog::OnBnClickedSearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//���������б�û��ѡ����
		pageBasic = false;//���������б��ܷ�ҳ	
		cmbBasic.ResetContent();//������������б�ҳ�ĸ�ѡ��
		while(listBasic.DeleteColumn(0)){}//������������б��е���������

		GetDlgItem(IDC_LISTBASIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBBASIC)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBRESULT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLLOGTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBLOGTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLSTARTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATESTART)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLENDTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATEEND)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNLOG)->ShowWindow(SW_HIDE);

		UpdateData(true);			

		CString m_ServerName;
		GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITNAME,UserName);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITNICK,UserNick);//��ȡ����ǳ�

		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_InputAccount"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BasicInfo();// ��ѯ����������Ϣ
	}
	catch(...)
	{
	}
}

// ��ѯ����������Ϣ
void CWAPetLog::BasicInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operWA.ReadIntValue("MWA","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//���������б�û��ѡ����
		pageBasic = false;//���������б��ܷ�ҳ	
		cmbBasic.ResetContent();//������������б�ҳ�ĸ�ѡ��
		while(listBasic.DeleteColumn(0)){}//������������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_UserInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ҳ��ѯ����������Ϣ
void CWAPetLog::OnCbnSelchangeCmbbasic()
{	
	try
	{	
		if(pageBasic)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbBasic.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

			while(listBasic.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query );//���Ͳ�ѯ���������Ϣ������
			}

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// ��������������Ϣ���浱ǰ�к�
void CWAPetLog::OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listBasic.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listBasic.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listBasic.SubItemHitTest(&lvinfo);//�����ڻ���������Ϣ�б���ѡ�е��к�
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// ˫������������Ϣ���в�ѯ
void CWAPetLog::OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listBasic.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listBasic.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;
			nItem = listBasic.SubItemHitTest(&lvinfo);//�����ڻ���������Ϣ�б���ѡ�е��к�

			if(nItem >= 0)
			{
				CIni mIni;
				pageResult = false;
				cmbResult.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������

				GetDlgItem(IDC_LISTBASIC)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBBASIC)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBRESULT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLLOGTYPE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBLOGTYPE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLSTARTTIME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_DATESTART)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLENDTIME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_DATEEND)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNLOG)->ShowWindow(SW_SHOW);

				UserName = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// ����ѡ�е�����ʺ�
				UserID = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// ����ѡ�е����ID
				UserNick = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// ����ѡ�е�����ǳ�

				tbcResult.SetCurSel(1);
				cmbLogType.SetCurSel(0);//����ѯѡ��ѡΪ0
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}


// �л�ѡ����в�ѯ
void CWAPetLog::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	if(tbcResult.GetCurSel() == 0)//ѡ�е��ǻ���������Ϣѡ�
	{
		GetDlgItem(IDC_LISTBASIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBBASIC)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBRESULT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLLOGTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBLOGTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLSTARTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATESTART)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLENDTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATEEND)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNLOG)->ShowWindow(SW_HIDE);
	}
	else
	{
		CIni mIni;
		pageResult = false;
		cmbResult.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		GetDlgItem(IDC_LISTBASIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBBASIC)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBRESULT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLLOGTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBLOGTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLSTARTTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DATESTART)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLENDTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DATEEND)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNLOG)->ShowWindow(SW_SHOW);

		if((listBasic.GetItemCount() > 0) && (nItem >= 0))
		{
			UserName = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// ����ѡ�е�����ʺ�
			UserID = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// ����ѡ�е����ID
			UserNick = theApp.operWA.GetValueByColName(&listBasic, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// ����ѡ�е�����ǳ�
		}
	}
	*pResult = 0;
}

//��ѯ��־��Ϣ
void CWAPetLog::OnBnClickedBtnlog()
{
	pageResult = false;
	cmbResult.ResetContent();
	while(listResult.DeleteColumn(0)){}// �������б��е���������

	CString m_LogType;
	GetDlgItemText(IDC_CMBLOGTYPE,m_LogType);//��ȡ��ǰ��ѯ����־���͵�����
	ResultLog(m_LogType);
}


//��ѯ��־��Ϣ
void CWAPetLog::ResultLog(CString logType)
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		CTime sTime;
		dtcStartTime.GetTime(sTime);//��ȡ��ʼʱ��
		CTime eTime;
		dtcEndTime.GetTime(eTime);//��ȡ����ʱ��
		BeginTime = sTime.Format("%Y-%m-%d %H:%M:%S");//��ȡ��ʼʱ��
		EndTime = eTime.Format("%Y-%m-%d %H:%M:%S");//��ȡ����ʱ��

		if((listBasic.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(BeginTime),(unsigned char*)mIni.wcharToChar(BeginTime));//��ʼʱ��
			socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(EndTime),(unsigned char*)mIni.wcharToChar(EndTime));//����ʱ��

			int midlength = socketdata.EnBody();
			if(logType==theApp.operWA.ReadValue("MWA","PL_UI_CatchPetSpirit"))
				theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_CatchPetSpirit_Record);//���ﾫ�겶׽��¼
			else if(logType==theApp.operWA.ReadValue("MWA","PL_UI_GainSpirit"))			
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_GainSpirit_Record);//���꽻�׻��
			else if(logType==theApp.operWA.ReadValue("MWA","PL_UI_LoseSpirit"))			
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_LoseSpirit_Record);//���꽻��ʧȥ
			else if(logType==theApp.operWA.ReadValue("MWA","PL_UI_SellSpirit"))			
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_SellSpirit_Record);//������ۼ�¼

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Log"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CWAPetLog::OnCbnSelchangeCmbresult()
{	
	try
	{
		if(pageResult)
		{
			CIni mIni;

			int index = cmbResult.GetCurSel() + 1;
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listBasic.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
				socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

				socketdata.AddTFLV(CEnumCore::TagName::WA_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(BeginTime),(unsigned char*)mIni.wcharToChar(BeginTime));//��ʼʱ��
				socketdata.AddTFLV(CEnumCore::TagName::WA_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(EndTime),(unsigned char*)mIni.wcharToChar(EndTime));//����ʱ��

				CString logType;
				GetDlgItemText(IDC_CMBLOGTYPE,logType);//��ȡ��ǰ��ѯ����־���͵�����

				int midlength = socketdata.EnBody();
				if(logType==theApp.operWA.ReadValue("MWA","PL_UI_CatchPetSpirit"))
					theApp.operWA.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_CatchPetSpirit_Record);//���ﾫ�겶׽��¼
				else if(logType==theApp.operWA.ReadValue("MWA","PL_UI_GainSpirit"))			
					theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_GainSpirit_Record);//���꽻�׻��
				else if(logType==theApp.operWA.ReadValue("MWA","PL_UI_LoseSpirit"))			
					theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_LoseSpirit_Record);//���꽻��ʧȥ
				else if(logType==theApp.operWA.ReadValue("MWA","PL_UI_SellSpirit"))			
					theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_SellSpirit_Record);//������ۼ�¼

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Log"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ���շ�����Ϣ
LRESULT CWAPetLog::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{	
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	
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
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://��ѯ����������Ϣ�Ļ�Ӧ
		{
			if(pageBasic)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listBasic,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listBasic,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageBasic = false;//���ܷ�ҳ					
					cmbBasic.ResetContent();//���ҳ����ѡ��
					while(listBasic.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
					cmbBasic.ResetContent();//���ҳ����ѡ���Ա����¹���
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbBasic.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbBasic.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
					if(pageCount == 1)
					{
						pageBasic = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pageBasic = true;//�ж�ҳ���ݣ����Է�ҳ
					}
				}				
			}
		}
		break;
	default:
		{
			if(pageResult)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageResult = false;//���ܷ�ҳ		
					cmbResult.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					cmbResult.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbResult.AddString(str);
					}
					cmbResult.SetCurSel(0);
					if(pageCount == 1)
					{
						pageResult = false;
					}
					else
					{
						pageResult = true;
					}
				}				
			}
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

// ���ҳ��
void CWAPetLog::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITNAME,"");
	SetDlgItemText(IDC_EDITNICK,"");
}

// �رնԻ���
void CWAPetLog::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//ȫѡ������
BOOL CWAPetLog::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listBasic);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listBasic.m_hWnd)
				{
					for(int i=0; i<listBasic.GetItemCount(); i++)
					{
						listBasic.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listBasic.EnsureVisible(i,false);
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


