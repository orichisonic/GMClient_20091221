// CG2BanPlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2BanPlayer.h"
#include ".\CG2banplayer.h"


// CCG2BanPlayer �Ի���

IMPLEMENT_DYNAMIC(CCG2BanPlayer, CDialog)
CCG2BanPlayer::CCG2BanPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2BanPlayer::IDD, pParent)
{
}

CCG2BanPlayer::~CCG2BanPlayer()
{
}

void CCG2BanPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbUPage);
	DDX_Control(pDX, IDC_LISTUSERINFO,listUser);
	DDX_Control(pDX, IDC_EDITBANACCOUNT, txtAccount);
	DDX_Control(pDX, IDC_EDITBANREASON, txtReason);
	DDX_Control(pDX, IDC_DTPBANENDDATE, dtcBanEndDate);
	DDX_Control(pDX, IDC_DTPBANENDTIME, dtcBanEndTime);
	DDX_Control(pDX, IDC_CMBBANTYPE, cmbBanType);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
}


BEGIN_MESSAGE_MAP(CCG2BanPlayer, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_BN_CLICKED(IDC_BTNBAN, OnBnClickedBtnban)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_CMBBANTYPE, OnCbnSelchangeCmbbantype)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CCG2BanPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();	
	InitUI();// ��ʼ����ʾ�ַ�	
	InitBanType();

	nItem = -1;// �����û��б�õ��к�
	mItem = -1;
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	pageUInfo = false;
	ServerIP = "";// ��Ϸ������IP	
	UserName = "";//����ʺ�
	UserNick = "";//����ǳ�
	UserID = "";//���ID

	CRect rs;
	GetClientRect(rs);//��ȡ�Ի���Ĵ�С��Ϣ

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

		listUser.MoveWindow(newRect);//���ú�listResult��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}

	dtcBanEndTime.SetFormat("HH:mm:ss");
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//

	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ʼ�����Ի���

	theApp.operCG2.GetServerList();//�������е���Ϸ�������б�

	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//���Ͳ�ѯ����	

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CCG2BanPlayer::InitUI()
{

	SetWindowText(theApp.operCG2.ReadValue("MCG2","BU_UI_BanPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLHINT,theApp.operCG2.ReadValue("MCG2","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANENDTIME,theApp.operCG2.ReadValue("MCG2","BU_UI_LblBanEndTime"));
	SetDlgItemText(IDC_LBLBANTYPE,theApp.operCG2.ReadValue("MCG2","BU_UI_LblBanType"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_reason"));
	SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgOpen"));
	SetDlgItemText(IDC_BTNRESET,theApp.operCG2.ReadValue("MCG2","Reset"));

	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgOpen"));
	tbcResult.InsertItem(2,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgList"));
	tbcResult.InsertItem(3,theApp.operCG2.ReadValue("MCG2","BU_UI_BtnSave"));
	tbcResult.InsertItem(4,theApp.operCG2.ReadValue("MCG2","BU_UI_Tpgquary"));
}

// �Զ��ı��С
void CCG2BanPlayer::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

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

		listUser.MoveWindow(newRect);//���ú�listResult��λ��
	}

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}
}

//���ñ�����ɫ
HBRUSH CCG2BanPlayer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ������Ϣ
void CCG2BanPlayer::OnBnClickedUisearch()
{
	try
	{

		nItem = -1;//�б�û��ѡ����
		mItem = -1;
		pageInfo = false;//�б��ܷ�ҳ	
		pageUInfo = false;
		cmbPage.ResetContent();//����б�ҳ�ĸ�ѡ��
		cmbUPage.ResetContent();
		while(listUser.DeleteColumn(0)){}
		while(listResult.DeleteColumn(0)){}//����б��е���������

		UpdateData(true);			

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

		if((UserName != "") || (UserNick != ""))//����ʺź�����ǳƲ�ͬʱΪ��ʱ����ѯ���������Ϣ
		{
			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);//SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);


			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);//SW_HIDE);
	        GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			UserInfo();//��ѯ���������Ϣ
		}
		else//����ʺź�����ǳ�ͬʱΪ��ʱ����ѯ���б���ͣ�ʺ��б���Ϣ
		{
			tbcResult.SetCurSel(2);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	        GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);


			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			AllBanUserList();//��ѯ���б���ͣ�ʺ��б���Ϣ
		}
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CCG2BanPlayer::UserInfo()
{
	try
	{		
		CIni mIni;	

		nItem = -1;
		pageUInfo = false;		
		cmbUPage.ResetContent();
		while(listUser.DeleteColumn(0)){}
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

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

// ��ѯ���б���ͣ�ʺ��б���Ϣ
void CCG2BanPlayer::AllBanUserList()
{
	try
	{				
		CIni mIni;
		
		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operCG2.ReadIntValue("MCG2","index");
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BanAccount_Query);
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CCG2BanPlayer::OnCbnSelchangeCmbuipage()
{	
	////OperationCG2 operCG2;
	try
	{		
		if(pageUInfo)
		{	
			CIni mIni;

			while(listUser.DeleteColumn(0)){}
			
			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query);
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ��ҳ��ѯ��ͣ�˺��б�
void CCG2BanPlayer::OnCbnSelchangeCmbpage()
{
	//OperationCG2 operCG2;
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listResult.DeleteColumn(0)){}
			
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 2)
			{				
				theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_BanAccount_Query);				
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_Page"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}

// ����������Ϣ���浱ǰ�к�
void CCG2BanPlayer::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
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

			nItem = listUser.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}

// ˫��������Ϣ���в���
void CCG2BanPlayer::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listUser.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listUser.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nItem = listUser.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�

			if(nItem >= 0)
			{
				//////OperationCG2 operCG2;
				CIni mIni;
				if(tbcResult.GetCurSel() == 0)//�����ǰ�������������Ϣ��ҳ��
				{
					tbcResult.SetCurSel(1);//��ת�������ʺŷ�ͣ��ҳ��

					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_SHOW);//
					GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_SHOW);//
					GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_SHOW);//
					GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_SHOW);//
					GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_SHOW);//

					CTime curTime = CTime::GetCurrentTime();//����ʱ��
					dtcBanEndDate.SetTime(&curTime);
					dtcBanEndTime.SetTime(&curTime);

					GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

					UpdateData(false);

					SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_reason"));//��ͣԭ��
					SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgOpen"));//�ʺŷ�ͣ

					txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������

					UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
				    UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			        UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
					iCharNo = atoi(theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//��ȡ��ɫ��

					SetDlgItemText(IDC_EDITBANACCOUNT,UserName);//����Ҫ��ͣ������ʺ�
					SetDlgItemText(IDC_EDITBANREASON,"");
				}			
			}
		}
		else
		{
			nItem = -1;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// ����������Ϣ���浱ǰ�к�
void CCG2BanPlayer::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			mItem = listResult.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
		}
		else
		{
			mItem = -1;
		}
	}
	*pResult = 0;
}

// ˫��������Ϣ���в���
void CCG2BanPlayer::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			mItem = listResult.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�

			if(mItem >= 0)
			{
				//OperationCG2 operCG2;
				CIni mIni;
				if(tbcResult.GetCurSel() == 2)//�����ǰ���ڷ�ͣ�˺��б�Ľ���
				{
					tbcResult.SetCurSel(3);//��ת�������ʺŽ���ҳ��
					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
					GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
					GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
					GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
					GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//

					GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

					UpdateData(false);

					SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_UnBind"));//���ԭ��
					SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_BtnSave"));//����ʺ�

					txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������

					UserName = theApp.operCG2.GetValueByColName(&listResult,mItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ��ȡҪ��������ʺ�
				    UserID = theApp.operCG2.GetValueByColName(&listResult, mItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ��ȡҪ�������ID

					SetDlgItemText(IDC_EDITBANACCOUNT,UserName);//����Ҫ��������ʺ�
					SetDlgItemText(IDC_EDITBANREASON,"");
				}				
			}
		}
		else
		{
			nItem = -1;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// �л�ѡ����в�ѯ
void CCG2BanPlayer::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CIni mIni;
	//OperationCG2 operCG2;

	if(tbcResult.GetCurSel()==0)//���ѡ�е������������Ϣ��ҳ��
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
		
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
	}
	else if(tbcResult.GetCurSel()==2)//���ѡ�е��Ƿ�ͣ�ʺ��б��ҳ��
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
	}
	else if(tbcResult.GetCurSel()==1)//���ѡ�е��Ƿ�ͣ�ʺŵ�ҳ��
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_SHOW);//
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_reason"));//��ͣԭ��
		SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_TpgOpen"));//�ʺŷ�ͣ

		txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������
		CTime curTime = CTime::GetCurrentTime();//����ʱ��
		dtcBanEndDate.SetTime(&curTime);
		dtcBanEndTime.SetTime(&curTime);

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))//�������ʺź��ǳƲ�ͬʱΪ�գ�nItem>=0��˵���Ѿ���ѯ�����������Ϣ�������Ѿ�ѡ����Ҫ��ͣ���ʺţ����Խ��з�ͣ����
		{
			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
			iCharNo = atoi(theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//��ȡ��ɫ��

			SetDlgItemText(IDC_EDITBANACCOUNT,UserName);
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
		else
		{
			SetDlgItemText(IDC_EDITBANACCOUNT,"");
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
	}
	else if(tbcResult.GetCurSel()==3)//���ѡ�е��ǽ���ʺŵ�ҳ��
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLBANREASON,theApp.operCG2.ReadValue("MCG2","BU_UI_UnBind"));
		SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","BU_UI_BtnSave"));

		txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������
		UpdateData(false);

		if((listResult.GetItemCount()) > 0 && (mItem >= 0))//�������ʺź��ǳ�ͬʱΪ�գ�nItem>=0��˵���Ѿ���ѯ����ͣ�ʺ��б������Ѿ�ѡ����Ҫ�����ʺţ����Խ��н�����
		{
			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�
			iCharNo = atoi(theApp.operCG2.GetValueByColName(&listResult, nItem, theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//��ȡ��ɫ��

			SetDlgItemText(IDC_EDITBANACCOUNT,UserName);
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
		else
		{
			SetDlgItemText(IDC_EDITBANACCOUNT,"");
			SetDlgItemText(IDC_EDITBANREASON,"");
		}
	}
	else if(tbcResult.GetCurSel()==4)//���ѡ�е��ǲ�ѯ�ʺ���û�б���ͣ��ҳ��
	{
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
		GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		UpdateData(false);

		SetDlgItemText(IDC_BTNBAN,theApp.operCG2.ReadValue("MCG2","Search"));
		UserID = "";
		txtAccount.SetReadOnly(false);//����ʺŵ�CEdit����ȡ��ֻ������

		SetDlgItemText(IDC_EDITBANACCOUNT,"");
		SetDlgItemText(IDC_EDITBANREASON,"");
	}
	*pResult = 0;
}

// ��ͣ�����ʺ�
void CCG2BanPlayer::OnBnClickedBtnban()
{
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;	

		int iBanType=0;

		CString strBanType;
		CString BanAccount = "";
		txtAccount.GetWindowText(BanAccount);//��ȡ����ʺ�
		if(BanAccount == "")//����ʺŲ���Ϊ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","BU_UI_AccountNull"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
			return;
		}				

		CString BanReason = "";
		txtReason.GetWindowText(BanReason);//��ȡ��ͣ����ԭ��
		if((tbcResult.GetCurSel() == 1) || (tbcResult.GetCurSel() == 3))// ѡ����Ƿ�ͣ�����ʺ�
		{			
			if(strlen(BanReason) >= 256)//��ͣ����ԭ����Ϊ��
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","BU_UI_ReasonTooLong"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
			else if(strlen(BanReason)<=0)
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","BU_UI_ReasonNotNull"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
			UserID=listResult.GetItemText(nItem,1);
			strBanType=listResult.GetItemText(nItem,5);
			if(!strcmp(strBanType,theApp.operCG2.ReadValue("MCG2","BU_UI_STRBANTYPEROLE")))
			{
				iBanType=0;
			}
			//else///////maple add
			else if(!strcmp(strBanType,theApp.operCG2.ReadValue("MCG2","BU_UI_STRBANTYPEACCOUNT")))
			{
				iBanType=1;
			}

		}
		else if(tbcResult.GetCurSel() == 4)// ѡ����ǲ�ѯ�ʺ���û�б���ͣ
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ����������
			if(m_ServerName == "")//���������Ʋ���Ϊ��
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��ȡ������IP
			GetDlgItemText(IDC_EDITBANACCOUNT,UserName);
			
			


		}
		CString strBanEndTime;
	

		if(tbcResult.GetCurSel()==1)
		{
			CTime curTime = CTime::GetCurrentTime();

			CTime StartDate;
			dtcBanEndDate.GetTime(StartDate);
			CTime StartTime;
			dtcBanEndTime.GetTime(StartTime);//��ȡʱ��

			CTime BanEndTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),StartTime.GetHour(),StartTime.GetMinute(),StartTime.GetSecond());

			strBanEndTime = BanEndTime.Format("%Y-%m-%d %H:%M:%S");//���ÿ�ʼʱ��


		
			if(BanEndTime <= curTime)//����ʱ�䲻��С�ڵ�ǰʱ��
			{
				MessageBox(theApp.operCG2.ReadValue("MCG2","BU_Warn_BanTime"),theApp.operCG2.ReadValue("MCG2","Warn"),0);
				return;
			}
			iBanType=cmbBanType.GetCurSel();

		}
		

		int userbyID = theApp.UserByID;//����ԱID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš���ͣ����ԭ�򡢲���ԱID�����ID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���ID


		if(tbcResult.GetCurSel()==1)
		{
			socketdata.AddTFLV(CEnumCore::TagName::CG2_BanTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBanEndTime),(unsigned char *)mIni.wcharToChar(strBanEndTime));

		}
		
		_itoa(iBanType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_TypeID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ͣ����

		_itoa(iCharNo,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Content,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//��ͣ����ԭ��

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID


		int midlength = socketdata.EnBody();
		
		if(tbcResult.GetCurSel() == 1)
		{
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Close);//���ͷ�ͣ����ʺŵ�����
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Open);//���ͽ������ʺŵ�����
		}
		else if(tbcResult.GetCurSel() == 4)
		{
			theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_BANISHMENT_QUERY);//���Ͳ�ѯ����ʺ���û�б���ͣ������
		}
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// ������Ϣ
void CCG2BanPlayer::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASON,"");
	if(tbcResult.GetCurSel() == 4)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
	}		
}

// ���շ�����Ϣ
LRESULT CCG2BanPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
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
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,sIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageInfo)
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageInfo = false;//���ܷ�ҳ				
					cmbPage.ResetContent();//���ҳ����ѡ��
					while(listResult.DeleteColumn(0)){}//���CListCtrl����
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
						pageInfo = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pageInfo = true;//�ж�ҳ���ݣ����Է�ҳ
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_BanAccount_Query_Resp://��ѯ���б���ͣ�ʺ��б�Ļ�Ӧ
		{
			if(pageInfo)
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;
					pageInfo = false;					
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					nItem = 0;
					cmbPage.ResetContent();//��ո�ѡ��
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
					if(pageCount == 1)
					{
						pageInfo = false;//ֻ��һҳ���ݣ����ܷ�ҳ
					}
					else
					{
						pageInfo = true;//�ж�ҳ���ݣ����Է�ҳ
					}
				}				
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Close_RESP://��ͣ����ʺŵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ�������

			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			UserInfo();//��ѯ����ʺ���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_Open_RESP://�������ʺŵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ�������

			tbcResult.SetCurSel(2);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDDATE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_DTPBANENDTIME)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);//
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			AllBanUserList();//��ѯ���б���ͣ�ʺ��б�
		}
		break;
	case CEnumCore::Message_Tag_ID::CG2_Account_BANISHMENT_QUERY_RESP://��ѯ�ʺ���û�б���ͣ�Ļ�Ӧ
		{

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			if(!strcmp(result,UserName))
			{
				theApp.operCG2.ShowResult(theApp.operCG2.ReadValue("MCG2","BU_Warn_Result"));
			}
			else
			{
					theApp.operCG2.ShowResult(result);//��ʾ���ؽ��
			}
			
		}
		break;
	default:
		break;
	}
	//socketdata.Destroy();
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return false;
}

// �رնԻ���
void CCG2BanPlayer::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void CCG2BanPlayer::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
void CCG2BanPlayer::InitBanType(void)
{
	//OperationCG2 operCG2;
	cmbBanType.ResetContent();
	cmbBanType.AddString(theApp.operCG2.ReadValue("MCG2","BU_UI_CMBBANTYPEROLE"));
	cmbBanType.AddString(theApp.operCG2.ReadValue("MCG2","BU_UI_CMBBANTYPEACCOUNT"));
	cmbBanType.SetCurSel(0);
}

void CCG2BanPlayer::OnCbnSelchangeCmbbantype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


