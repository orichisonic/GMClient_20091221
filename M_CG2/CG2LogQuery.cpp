// CG2LogQuery.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2LogQuery.h"
#include ".\cg2logquery.h"


// CCG2LogQuery �Ի���

IMPLEMENT_DYNAMIC(CCG2LogQuery, CDialog)
CCG2LogQuery::CCG2LogQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2LogQuery::IDD, pParent)
	, ServerIP(_T(""))
{
}

CCG2LogQuery::~CCG2LogQuery()
{
}

void CCG2LogQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBKPPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTCHARACTER, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_CBString(pDX, IDC_CMBUISERVER, ServerIP);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBCATEGORY, cmbCategory);
	DDX_Control(pDX, IDC_CMBACTION, cmbAction);
	DDX_Control(pDX, IDC_DATESTART, dtcStartDate);
	DDX_Control(pDX, IDC_TIMESTART, dtcStartTime);
	DDX_Control(pDX, IDC_DATEEND, dtcEndDate);
	DDX_Control(pDX, IDC_TIMEEND, dtcEndTime);
}


BEGIN_MESSAGE_MAP(CCG2LogQuery, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_CBN_SELCHANGE(IDC_CMBCATEGORY, OnCbnSelchangeCmbcategory)
	ON_BN_CLICKED(IDC_BTSEARCH, OnBnClickedBtsearch)
END_MESSAGE_MAP()


// CCG2LogQuery ��Ϣ�������

BOOL CCG2LogQuery::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//���ú�listResult��λ��
		}

	}

	GetDlgItem(IDC_STATICCATEGORY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBCATEGORY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICACTION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBACTION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICSTARTTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATESTART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TIMESTART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICENDTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATEEND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TIMEEND)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTSEARCH)->ShowWindow(SW_HIDE);



	//OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	theApp.operCG2.GetServerList();//�������е���Ϸ�������б�
	::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ��ʼ����ʾ�ַ�
void CCG2LogQuery::InitUI()//
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_LogQuery"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));

	SetDlgItemText(IDC_STATICCATEGORY,theApp.operCG2.ReadValue("MCG2","UIC_UI_CATEGORY"));
	SetDlgItemText(IDC_STATICACTION,theApp.operCG2.ReadValue("MCG2","UIC_UI_ACTION"));
	SetDlgItemText(IDC_STATICSTARTTIME,theApp.operCG2.ReadValue("MCG2","UIC_UI_STARTTIME"));
	SetDlgItemText(IDC_STATICENDTIME,theApp.operCG2.ReadValue("MCG2","UIC_UI_ENDTIME"));

	SetDlgItemText(IDC_BTSEARCH,theApp.operCG2.ReadValue("MCG2","Search"));

	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","CG2_UI_tpgLogInfo"));

}

//�Զ��ı��С
void CCG2LogQuery::OnSize(UINT nType, int cx, int cy)
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
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��

		if(listResult.m_hWnd != NULL)
		{
			listResult.MoveWindow(newRect);//���ú�listResult��λ��
		}

	}
}

//���ñ�����ɫ
HBRUSH CCG2LogQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ѯ�����Ϣ
void CCG2LogQuery::OnBnClickedUisearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;

		tbcResult.SetCurSel(0);//�����Ϣ

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		//GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

		//GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		//GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		//UpdateData(true);
		

		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITUINICK,UserNick);//��ȡ����ǳ�
		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_InputAccount"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}


void CCG2LogQuery::UserInfo()
{
	//OperationCG2 theApp.operCG2;
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

//�л�ѡ�
void CCG2LogQuery::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;
	if(tbcResult.GetCurSel() == 0)//ѡ�е������������Ϣѡ�
	{
		GetDlgItem(IDC_STATICCATEGORY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBCATEGORY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICACTION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBACTION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICSTARTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATESTART)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TIMESTART)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICENDTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATEEND)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TIMEEND)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTSEARCH)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);

		UpdateData(true);
		cmbCategory.ResetContent();
	}
	else if(tbcResult.GetCurSel() == 1)//ѡ�е�����־��ѯ
	{
		CIni mIni;
		pageInfo = false;
		cmbPage.ResetContent();
		//cmbCategory.ResetContent();
		//cmbAction.ResetContent();
		while(listUser.DeleteColumn(0)){}// �������б��е���������

		GetDlgItem(IDC_STATICCATEGORY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBCATEGORY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICACTION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBACTION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICSTARTTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DATESTART)->ShowWindow(SW_SHOW);
////		GetDlgItem(IDC_TIMESTART)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICENDTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DATEEND)->ShowWindow(SW_SHOW);
////		GetDlgItem(IDC_TIMEEND)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTSEARCH)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		//��־������ʾ
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR"));//����
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM"));//����
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_MAIL"));//�ʼ�
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET"));//����
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL"));//����
		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD"));//��Ǯ

//		cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT"));//�ʺ�

		UpdateData(true);
	}
	*pResult = 0;
}

//��־������Ͽ�ı�
void CCG2LogQuery::OnCbnSelchangeCmbcategory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;
	CString strCategory="";
	GetDlgItemText(IDC_CMBCATEGORY,strCategory);//��ô�����Ϣ
	int index=cmbCategory.GetCurSel();

	if(index==4)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_CHAR"))//����
	{
		cmbAction.ResetContent();
		//UpdateData(true);
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LOGIN"));//�����½
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LOGOUT"));//����ǳ�
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LEVELUP"));//��������

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_QUESTERROR"));//�ش��������������
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_CREATE"));//���ﴴ��
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_DELETE"));//����ɾ��
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_QUESTCLEAR"));//�������
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GHONORUP"));//������������
		
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GRANKUP"));//����ȼ�����
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCREATE"));//��������
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCLOSE"));//��ɢ����
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GJOIN"));//���빤��
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GLEFT"));//�뿪����

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GKICK"));//�������߳�����
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCHANGEM"));//��������᳤
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GEXTEND"));//��������
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_MARRY"));//���
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_DIVORCE"));//���
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GETGD"));//����ս
		
	}
	else if(index==5)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_MAIL"))//�ʼ�
	{
		cmbAction.ResetContent();
		//UpdateData(true);
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_MAIL_NORMAL"));

	}
/*	else if(index==6)//strCategory==theApp.operCG2.ReadVlaue("MCG2","UIC_ACCOUNT")
	{
		cmbAction.ResetContent();
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT_LOGIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT_XTRAPERROR"));
	}*/
	else if(index==0)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_PET"))//����
	{
		cmbAction.ResetContent();
		//UpdateData(true);
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_LEVELUP"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_GAIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_DELETESKILL"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_RELEASE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_TRADE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_SELL"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_GRADEUPSKILL"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_PUTBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET_GETBANK"));
		
	}
	else if(index==2)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_SKILL"))//����
	{
		cmbAction.ResetContent();
		//UpdateData(true);
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL_DELETE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL_GAIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL_GRADEUP"));

		
	}
	else if(index==1)////strCategory==theApp.operCG2.ReadValue("MCG2","UIC_ITEM"))///����
	{
		cmbAction.ResetContent();
		cmbAction.SetCurSel(0);

		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BUY"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_USE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAIN_BATTLE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROP"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROPCHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROP_DELETE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_SELL"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_USECHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_TRADE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GETCHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BREAK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_PUTBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GETBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_MERGE"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_ITEMCOLOR"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BREAKCHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BUYCHARGEITEM"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAINSKILLITEM"));//UIC_ITEM_GAINSKILLITEM
	}
	else if(index=3)//strCategory==theApp.operCG2.ReadValue("MCG2","UIC_GOLD"))
	{
		cmbAction.ResetContent();
		cmbAction.SetCurSel(0);
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_TRADELOST"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_PUTBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_GETBANK"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_GAIN"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_DROP"));
		cmbAction.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD_SPENDMONEY"));
	}
}

// �����û��б��浱ǰ�к�
void CCG2LogQuery::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		if(listUser.GetItemCount() != 0)
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
			nItem = -1;
		}
	}
	*pResult = 0;
}

// ˫�����������Ϣ���в�ѯ
void CCG2LogQuery::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;

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

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				//while(listUser.DeleteColumn(0)){}// �������б��е���������
				while(listResult.DeleteColumn(0)){}// �������б��е���������
				

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
				///GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				///GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);

				UpdateData(true);

				//OperationCG2 theApp.operCG2;
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem,theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�



				GetDlgItem(IDC_STATICCATEGORY)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBCATEGORY)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICACTION)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBACTION)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICSTARTTIME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_DATESTART)->ShowWindow(SW_SHOW);
///				GetDlgItem(IDC_TIMESTART)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATICENDTIME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_DATEEND)->ShowWindow(SW_SHOW);
///				GetDlgItem(IDC_TIMEEND)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTSEARCH)->ShowWindow(SW_SHOW);


				//��־������ʾ
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_CHAR"));//����
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ITEM"));//����
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_MAIL"));//�ʼ�
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_PET"));//����
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_SKILL"));//����
				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_GOLD"));//��Ǯ

//				cmbCategory.AddString(theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT"));//�ʺ�

				UpdateData(true);



				//DetailInfo();// ��ѯ��ɫ��ϸ����
				tbcResult.SetCurSel(1);
			}
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}


///��������־��ѯbutton
void CCG2LogQuery::OnBnClickedBtsearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ���ɫIDKey����־���ࡢ��־С�ࡢ��ʼʱ�䡢����ʱ�䡢ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		//��ȡ��ʼʱ��ͽ���ʱ��
		CTime startDate,endDate;
		dtcStartDate.GetTime(startDate);
		dtcEndDate.GetTime(endDate);

		CTime startTime,endTime;
		dtcStartTime.GetTime(startTime);
		dtcEndTime.GetTime(endTime);

		CTime startDT=CTime::CTime(startDate.GetYear(),startDate.GetMonth(),startDate.GetDay(),startTime.GetHour(),startTime.GetMinute(),startTime.GetSecond());
		CTime endDT=CTime::CTime(endDate.GetYear(),endDate.GetMonth(),endDate.GetDay(),endTime.GetHour(),endTime.GetMinute(),endTime.GetSecond());

		CString strStartTime,strEndTime;
		strStartTime=startDT.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��
		strEndTime=endDT.Format("%Y-%m-%d %H:%M:%S");//���ý���ʱ��

		//�����־���࣬��־С��
		CString strCategory="";
		CString strAction="";
		CString str="";

		GetDlgItemText(IDC_CMBCATEGORY,str);//��ô�����Ϣ
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR"))//����
		{
			strCategory="char";
			GetDlgItemText(IDC_CMBACTION,str);//���С����Ϣ
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LEVELUP"))//��������
				strAction="levelup";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LOGIN"))//�����½
				strAction="login";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_LOGOUT"))//����ǳ�
				strAction="logout";



			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_QUESTERROR"))//�ش��������������
				strAction="questerror";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_CREATE"))//���ﴴ��
				strAction="create";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_DELETE"))//����ɾ��
				strAction="delete";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_QUESTCLEAR"))//�������
				strAction="questclear";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GHONORUP"))//������������
				strAction="ghonorup";
		
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GRANKUP"))//����ȼ�����
				strAction="grankup";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCREATE"))//��������
				strAction="gcreate";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCLOSE"))//��ɢ����
				strAction="gclose";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GJOIN"))//���빤��
				strAction="gjoin";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GLEFT"))//�뿪����
				strAction="gleft";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GKICK"))//�������߳�����
				strAction="gkick";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GCHANGEM"))//��������᳤
				strAction="gchangem";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GEXTEND"))//��������
				strAction="gextend";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_MARRY"))//���
				strAction="marry";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_DIVORCE"))//���
				strAction="divorce";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_CHAR_GETGD"))//����ս
				strAction="getgd";
		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_SKILL"))//����
		{
			strCategory="skill";
			GetDlgItemText(IDC_CMBACTION,str);//���С����Ϣ
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_SKILL_GRADEUP"))//��������
				strAction="gradeup";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_SKILL_DELETE"))//ɾ������
				strAction="delete";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_SKILL_GAIN"))//��ü���
				strAction="gain";
		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_MAIL"))//�ʼ�
		{
			strCategory="mail";
			GetDlgItemText(IDC_CMBACTION,str);//���С����Ϣ
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_MAIL_NORMAL"))//����
				strAction="normal";
		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM"))//����
		{
			strCategory="item";
			GetDlgItemText(IDC_CMBACTION,str);//���С����Ϣ
			

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAIN_BATTLE"))//ս�����
				strAction="gain_battle";
				
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BUY"))//����
				strAction="buy";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_USE"))//ʹ��
				strAction="use";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROP"))//����
				strAction="drop";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROPCHARGEITEM"))//�����ϳɵ���
				strAction="dropchargeitem";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_DROP_DELETE"))//����ɾ��
				strAction="drop_delete";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_SELL"))//����
				strAction="sell";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_USECHARGEITEM"))//ʹ�úϳɵ���
				strAction="usechargeitem";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_TRADE"))//����
				strAction="trade";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GETCHARGEITEM"))//��úϳɵ���
				strAction="getchargeitem";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAIN"))//���
				strAction="gain";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BREAK"))//��
				strAction="break";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_PUTBANK"))//���߷ŵ�����
				strAction="putbank";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GETBANK"))//������ȡ������
				strAction="getbank";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_MERGE"))//�ϳɵ���
				strAction="merge";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_ITEMCOLOR"))//װ��Ⱦɫ
				strAction="itemcolor";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BREAKCHARGEITEM"))//�շѵ�����
				strAction="breakchargeitem";

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_BUYCHARGEITEM"))//��M�ҹ������
				strAction="buychargeitem";//UIC_ITEM_GAINSKILLITEM

			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ITEM_GAINSKILLITEM"))//��ü��ܵ���
				strAction="gainskillitem";

		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET"))//����
		{
			strCategory="pet";
			GetDlgItemText(IDC_CMBACTION,str);//���С����Ϣ
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_LEVELUP"))//��������
				strAction="levelup";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_GAIN"))//��ó���
				strAction="gain";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_DELETESKILL"))//ɾ������
				strAction="deleteskill";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_RELEASE"))//�ͷ�
				strAction="release";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_TRADE"))//���׳���
				strAction="trade";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_SELL"))//���۳���
				strAction="sell";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_GRADEUPSKILL"))//���＼������
				strAction="gradeupskill";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_PUTBANK"))//�ѳ���ŵ�����
				strAction="putbank";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_PET_GETBANK"))//������ȡ������
				strAction="getbank";
		}
		if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD"))//��Ǯ
		{
			strCategory="gold";
			GetDlgItemText(IDC_CMBACTION,str);//���С����Ϣ
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_TRADELOST"))//���׽�Ǯ
				strAction="tradeLost";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_PUTBANK"))//�ѽ�Ǯ�ŵ�����
				strAction="putbank";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_GETBANK"))//������ȡ����Ǯ
				strAction="getbank";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_GAIN"))//��ý�Ǯ
				strAction="gain";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_DROP"))//������Ǯ
				strAction="drop";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_GOLD_SPENDMONEY"))//��������M��
				strAction="spendmoney";
		}
/*		if(str==theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT"))//�ʺ�
		{
			strCategory="account";
			GetDlgItemText(IDC_CMBACTION,str);//���С����Ϣ
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT_LOGIN"))//�ʺŵ�½
				strAction="accountlogin";
			if(str==theApp.operCG2.ReadValue("MCG2","UIC_ACCOUNT_XTRAPERROR"))//xtrap�������˷�����ҶϿ�����
				strAction="xtraperror";
		}
*/
		

		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP


		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫIDKey
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Log_StartTime,CEnumCore::TagFormat::TLV_STRING,strlen(strStartTime),(unsigned char *)mIni.wcharToChar(strStartTime));//��־��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Log_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char *)mIni.wcharToChar(strEndTime));//��־����ʱ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_category,CEnumCore::TagFormat::TLV_STRING,strlen(strCategory),(unsigned char *)mIni.wcharToChar(strCategory));//��־����
		socketdata.AddTFLV(CEnumCore::TagName::CG2_action,CEnumCore::TagFormat::TLV_STRING,strlen(strAction),(unsigned char *)mIni.wcharToChar(strAction));//��־С��


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Log_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_LogQuery"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

//���ܷ�����Ϣ
LRESULT CCG2LogQuery::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	//OperationCG2 theApp.operCG2;
	CIni mIni;

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
///	case CEnumCore::Message_Tag_ID::CG2_Log_Query_Resp://�����־��ѯ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageUInfo = false;//���ܷ�ҳ					
					cmbPage.ResetContent();//���ҳ����ѡ��
					while(listUser.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//���ҳ����ѡ���Ա����¹���
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
					if(pageCount == 1)
					{
						pageUInfo = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pageUInfo = true;//�ж�ҳ���ݣ����Է�ҳ
					}
				}				
			}
		}
		break;

	default:
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageUInfo = false;//���ܷ�ҳ					
					cmbPage.ResetContent();//���ҳ����ѡ��
					//cmbCategory.ResetContent();
					while(listResult.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//���ҳ����ѡ���Ա����¹���
					//cmbCategory.ResetContent();
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
					if(pageCount == 1)
					{
						pageUInfo = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pageUInfo = true;//�ж�ҳ���ݣ����Է�ҳ
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


//�رնԻ���
void CCG2LogQuery::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CCG2LogQuery::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");

}




