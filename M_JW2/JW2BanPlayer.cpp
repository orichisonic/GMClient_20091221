// JW2BanPlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2BanPlayer.h"
#include ".\JW2BanPlayer.h"


// CJW2BanPlayer �Ի���

IMPLEMENT_DYNAMIC(CJW2BanPlayer, CDialog)
CJW2BanPlayer::CJW2BanPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2BanPlayer::IDD, pParent)
{
}

CJW2BanPlayer::~CJW2BanPlayer()
{
}

void CJW2BanPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_EDITBANACCOUNT, txtAccount);
	DDX_Control(pDX, IDC_EDITBANREASON, txtReason);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBPAGE, cmbLPage);
}


BEGIN_MESSAGE_MAP(CJW2BanPlayer, CDialog)
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
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CJW2BanPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();	
	InitUI();// ��ʼ����ʾ�ַ�			

	nItem = -1;// �����û��б�õ��к�
	mItem = -1;
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	pageUInfo = false;
	ServerIP = "";// ��Ϸ������IP	
	UserAccount = "";// ����ʺ�	
	UserName = "";//����ʺź��ǳ�
	UserNick = "";
	UserID = 0;//���ID

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

	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);


	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//��ʼ�����Ի���

	theApp.operJW2.GetServerList();

	::EnableWindow(this->GetParent()->m_hWnd,false);
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//���Ͳ�ѯ����	

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CJW2BanPlayer::InitUI()
{

	SetWindowText(theApp.operJW2.ReadValue("MJW2","BU_UI_BanPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operJW2.ReadValue("MJW2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operJW2.ReadValue("MJW2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operJW2.ReadValue("MJW2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operJW2.ReadValue("MJW2","Cancel"));
	SetDlgItemText(IDC_LBLHINT,theApp.operJW2.ReadValue("MJW2","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operJW2.ReadValue("MJW2","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_reason"));
	SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgOpen"));
	SetDlgItemText(IDC_BTNRESET,theApp.operJW2.ReadValue("MJW2","Reset"));

	tbcResult.InsertItem(0,theApp.operJW2.ReadValue("MJW2","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgOpen"));
	tbcResult.InsertItem(2,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgList"));
	tbcResult.InsertItem(3,theApp.operJW2.ReadValue("MJW2","BU_UI_BtnSave"));
	tbcResult.InsertItem(4,theApp.operJW2.ReadValue("MJW2","BU_UI_Tpgquary"));
}

//�����ݼ���Ӧ����
BOOL CJW2BanPlayer::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operJW2.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operJW2.CopyListInfo(&listResult);
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

// �Զ��ı��С
void CJW2BanPlayer::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CJW2BanPlayer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ������Ϣ
void CJW2BanPlayer::OnBnClickedUisearch()
{
	try
	{

		nItem = -1;//�б�û��ѡ����
		mItem = -1;
		pageInfo = false;//�б��ܷ�ҳ	
		pageUInfo = false;
		cmbPage.ResetContent();//����б�ҳ�ĸ�ѡ��
		cmbLPage.ResetContent();
		while(listUser.DeleteColumn(0)){}//����б��е���������
		while(listResult.DeleteColumn(0)){}//����б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBUISERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
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
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	        GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
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
void CJW2BanPlayer::UserInfo()
{
	try
	{		
		CIni mIni;	

		nItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listUser.DeleteColumn(0)){}
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��ʾ50����¼

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_QUERY);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_UserInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ��ѯ���б���ͣ�ʺ��б���Ϣ
void CJW2BanPlayer::AllBanUserList()
{
	try
	{				
		CIni mIni;
		
		mItem = -1;
		pageUInfo = false;		
		cmbLPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNTREMOTE_QUERY);
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_UserInfo"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CJW2BanPlayer::OnCbnSelchangeCmbuipage()
{	
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listUser.DeleteColumn(0)){}
			
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��ʾ50����¼
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_QUERY);
			}
			else if(tbcResult.GetCurSel() == 2)
			{				
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNTREMOTE_QUERY);
				
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Page"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ��ҳ���в�ѯ���������Ϣ
void CJW2BanPlayer::OnCbnSelchangeCmbpage()
{
	try
	{		
		if(pageUInfo)
		{	
			CIni mIni;

			while(listResult.DeleteColumn(0)){}
			
			int index = cmbLPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��ʾ50����¼
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(tbcResult.GetCurSel() == 0)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_QUERY);
			}
			else if(tbcResult.GetCurSel() == 2)
			{				
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNTREMOTE_QUERY);
				
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Page"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ����������Ϣ���浱ǰ�к�
void CJW2BanPlayer::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
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
void CJW2BanPlayer::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listUser.GetItemCount() != 0)
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
				CIni mIni;
				if(tbcResult.GetCurSel() == 0)//�����ǰ�������������Ϣ��ҳ��
				{
					tbcResult.SetCurSel(1);//��ת�������ʺŷ�ͣ��ҳ��

					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

					UpdateData(false);

					SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_reason"));//��ͣԭ��
					SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgOpen"));//�ʺŷ�ͣ

					//txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������

					UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));// ��ȡҪ��ͣ������ʺ�
				    UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// ��ȡҪ��ͣ�����ID

					SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//����Ҫ��ͣ������ʺ�
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

// ������ͣ�˺��б���Ϣ���浱ǰ�к�
void CJW2BanPlayer::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 2)
	{
		if(listResult.GetItemCount() >0)
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

// ˫����ͣ�˺��б���Ϣ���н��
void CJW2BanPlayer::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		if(listResult.GetItemCount() > 0)
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
				CIni mIni;
				if(tbcResult.GetCurSel() == 2)//�����ǰ���ڷ�ͣ�˺��б�Ľ���
				{
					tbcResult.SetCurSel(3);//��ת�������ʺŽ���ҳ��
					GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

					UpdateData(false);

					SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_UnBind"));//���ԭ��
					SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_BtnSave"));//����ʺ�

					//txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������

				    UserAccount = theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));// ��ȡҪ��������ʺ�
				    UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// ��ȡҪ�������ID

					SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//����Ҫ��������ʺ�
					SetDlgItemText(IDC_EDITBANREASON,"");
				}				
			}
		}
		else
		{
			mItem = -1;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}



// �л�ѡ����в�ѯ
void CJW2BanPlayer::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{	
	CIni mIni;

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
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_reason"));//��ͣԭ��
		SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_TpgOpen"));//�ʺŷ�ͣ

	//	txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))//�������ʺź��ǳƲ�ͬʱΪ�գ�nItem>=0��˵���Ѿ���ѯ�����������Ϣ�������Ѿ�ѡ����Ҫ��ͣ���ʺţ����Խ��з�ͣ����
		{
			UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));// ��ȡ����ʺ�
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// ��ȡ���ID

			SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);
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

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLBANREASON,theApp.operJW2.ReadValue("MJW2","BU_UI_UnBind"));
		SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","BU_UI_BtnSave"));

	//	txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������
		UpdateData(false);

		if((listResult.GetItemCount() > 0) && (mItem >= 0))//�������ʺź��ǳ�ͬʱΪ�գ�nItem>=0��˵���Ѿ���ѯ����ͣ�ʺ��б������Ѿ�ѡ����Ҫ�����ʺţ����Խ��н�����
		{
			UserAccount = theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));// ��ȡ����ʺ�
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// ��ȡ���ID

			SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);
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

		GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

		UpdateData(false);

		SetDlgItemText(IDC_BTNBAN,theApp.operJW2.ReadValue("MJW2","Search"));
		UserID = 0;
		//txtAccount.SetReadOnly(false);//����ʺŵ�CEdit����ȡ��ֻ������

		SetDlgItemText(IDC_EDITBANACCOUNT,"");
		SetDlgItemText(IDC_EDITBANREASON,"");
	}
	*pResult = 0;
}

// ��ͣ�����ʺ�
void CJW2BanPlayer::OnBnClickedBtnban()
{
	try
	{
		CIni mIni;
	
		UpdateData(true);			

		GetDlgItemText(IDC_CMBUISERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		CString BanAccount = "";
		txtAccount.GetWindowText(BanAccount);//��ȡ����ʺ�
		if(BanAccount == "")//����ʺŲ���Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","BU_UI_AccountNull"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
			return;
		}				

		CString BanReason = "";
		txtReason.GetWindowText(BanReason);//��ȡ��ͣ����ԭ��
		if((tbcResult.GetCurSel() == 1) || (tbcResult.GetCurSel() == 3))// ѡ����Ƿ�ͣ�����ʺ�
		{			
			if(strlen(BanReason) >= 256)//��ͣ����ԭ����Ϊ��
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","BU_UI_ReasonTooLong"),theApp.operJW2.ReadValue("MJW2","Warn"),0);
				return;
			}
			else if(strlen(BanReason)<10)
			{
				MessageBox("ԭ����С��5��������",0);
				return;
			}
		}
		else if(tbcResult.GetCurSel() == 4)// ѡ����ǲ�ѯ�ʺ���û�б���ͣ
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ����������
			if(m_ServerName == "")//���������Ʋ���Ϊ��
			{
				MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_SelectServer"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��ȡ������IP
		}
		int userbyID = theApp.UserByID;//����ԱID
		GetDlgItemText(IDC_EDITBANACCOUNT,UserName);

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš���ͣ����ԭ�򡢲���ԱID�����ID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

	

		socketdata.AddTFLV(CEnumCore::TagName::JW2_Reason,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//��ͣ����ԭ��

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID
		
		switch(tbcResult.GetCurSel())
		{
		case 1:
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// ����ѡ�е����ID
			break;
		case 3:
			UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listResult, mItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));// ����ѡ�е����ID
			break;
		case 4:
			break;
		}
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		int midlength = socketdata.EnBody();
		
		if(tbcResult.GetCurSel() == 1)
		{

			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_CLOSE);//���ͷ�ͣ����ʺŵ�����
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_OPEN);//���ͽ������ʺŵ�����
		}
		else if(tbcResult.GetCurSel() == 4)
		{
			theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ACCOUNT_BANISHMENT_QUERY);//���Ͳ�ѯ����ʺ���û�б���ͣ������
		}
		
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// ������Ϣ
void CJW2BanPlayer::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASON,"");
	if(tbcResult.GetCurSel() == 4)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
	}		
}

// ���շ�����Ϣ
LRESULT CJW2BanPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_QUERY_RESP://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageInfo)
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageInfo = false;//���ܷ�ҳ				
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
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNTREMOTE_QUERY_RESP://��ѯ���б���ͣ�ʺ��б�Ļ�Ӧ
		{
			if(pageInfo)
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					mItem = -1;
					pageUInfo = false;					
					cmbLPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					mItem = 0;
					cmbLPage.ResetContent();//��ո�ѡ��
					for(int i=1;i <= pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbLPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbLPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
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
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_CLOSE_RESP://��ͣ����ʺŵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ�������

			/*tbcResult.SetCurSel(0);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);*/
			//UserInfo();//��ѯ����ʺ���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_OPEN_RESP://�������ʺŵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ�������

			tbcResult.SetCurSel(2);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);
			AllBanUserList();//��ѯ���б���ͣ�ʺ��б�
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_BANISHMENT_QUERY_RESP://��ѯ�ʺ���û�б���ͣ�Ļ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			if(m_tflv.m_tagName==CEnumCore::TagName::MESSAGE)
			{
				CString result = (LPCTSTR)&m_tflv.lpdata;
				theApp.operJW2.ShowResult(result);//��ʾ���ؽ��
			}
			else
			{
				theApp.operJW2.ShowResult("�˺��Ѿ���ͣ");//��ʾ���ؽ��
			}
		}
		break;
	default:
		break;
	}

	socketdata.Destroy();
	return false;
}

//�����û�������Ϣ��������������
void CJW2BanPlayer::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operJW2.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CJW2BanPlayer::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operJW2.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CJW2BanPlayer::OnBnClickedUicancel()
{
	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Close");//�رմ���
	OnClose();
}

// �رնԻ���
void CJW2BanPlayer::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}


