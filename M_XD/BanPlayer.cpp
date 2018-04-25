// BanPlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_XD.h"
#include "BanPlayer.h"
#include ".\banplayer.h"


// CBanPlayer �Ի���

IMPLEMENT_DYNAMIC(CBanPlayer, CDialog)
CBanPlayer::CBanPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CBanPlayer::IDD, pParent)
{
}

CBanPlayer::~CBanPlayer()
{
}
void CBanPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_EDITBANACCOUNT, txtAccount);
	DDX_Control(pDX, IDC_EDITBANREASON, txtReason);
	DDX_Control(pDX, IDC_CMBBANTYPE, cmbType);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);	
}


BEGIN_MESSAGE_MAP(CBanPlayer, CDialog)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDC_BTNBAN, OnBnClickedBtnban)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_BN_CLICKED(IDC_BTNSEARCH, OnBnClickedBtnsearch)
	ON_CBN_SELCHANGE(IDC_CMBSERVER, OnCbnSelchangeCmbserver)
	//ON_BN_CLICKED(IDC_BTBROWSE, OnBnClickedBtbrowse)
	//ON_BN_CLICKED(IDC_BTMULTICLOSE, OnBnClickedBtmulticlose)
	//ON_BN_CLICKED(IDC_BTBROWSE, OnBnClickedBtbrowse)	
END_MESSAGE_MAP()


// CBanPlayer ��Ϣ�������

// ��ʼ���Ի���
BOOL CBanPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();	

	InitUI();// ��ʼ����ʾ�ַ�		
	showUserInfo();

	nItem = 0;// �����û��б�õ��к�
	mItem = 0;// �����ʺŷ�ͣ�б�õ��к�
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	ServerIP = "";// ��Ϸ������IP	
	ServerName = "";//��Ϸ����������
	UserAccount = "";// ����ʺ�	
	UserName = "";//����ʺź��ǳ�

	SetProp(listUser.GetSafeHwnd(),"�����к�",(HANDLE)0);
	SetProp(listUser.GetSafeHwnd(),"����˳��",(HANDLE)1);

	SetProp(listResult.GetSafeHwnd(),"�����к�",(HANDLE)0);
	SetProp(listResult.GetSafeHwnd(),"����˳��",(HANDLE)1);

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
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

	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��
	}

	//OperationPAL operXD;
	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//��ʼ�����Ի���

	if(theApp.operXD.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CBanPlayer::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","BU_UI_BanPlayer"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operXD.ReadValue("MXD","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDCANCEL,theApp.operXD.ReadValue("MXD","Close"));

	SetDlgItemText(IDC_LBLHINT,theApp.operXD.ReadValue("MXD","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLSACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_BTNSEARCH,theApp.operXD.ReadValue("MXD","BU_UI_SEARCHBAN"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operXD.ReadValue("MXD","BU_UI_reason"));
	SetDlgItemText(IDC_LBLBANTYPE,theApp.operXD.ReadValue("MXD","BU_UI_TYPE"));
	SetDlgItemText(IDC_BTNRESET,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_BTNBAN,theApp.operXD.ReadValue("MXD","BU_UI_TpgOpen"));
	SetDlgItemText(IDC_LBBANTIME2,theApp.operXD.ReadValue("MXD","BU_UI_LblDate"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","BU_UI_TpgOpen"));
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","BU_UI_TpgList"));
	tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","BU_UI_BtnSave"));
	tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","BU_UI_Tpgquary"));
	//tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","BU_UI_TpgMultiClose"));
}

//�����ݼ���Ӧ����
BOOL CBanPlayer::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operXD;
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operXD.CopyListInfo(&listResult);
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
void CBanPlayer::OnSize(UINT nType, int cx, int cy)
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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
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
HBRUSH CBanPlayer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ȡѡ���ServerIP
void CBanPlayer::OnCbnSelchangeCmbserver()
{
	try
	{
		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ������Ϊ��
		{
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
	}
	catch(...)
	{
	}
}

// ��ѯ������Ϣ
void CBanPlayer::OnBnClickedOk()
{
	try
	{
		CIni mIni;
		//OperationPAL operXD;

		nItem = 0;//��������б�û��ѡ����
		mItem = 0;// �����ʺŷ�ͣ�б�õ��к�
		pageInfo = false;//�б��ܷ�ҳ		
		cmbPage.ResetContent();//����б�ҳ�ĸ�ѡ��
		while(listResult.DeleteColumn(0)){}//����б��е���������
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITNAME,UserName);//��ȡ��ҽ�ɫ��
		if((UserName == "") && (UserAccount == ""))//����ʺź���ҽ�ɫ��ͬʱΪ��
		{
			showBanList();
			AllBanUserList();//��ѯ���б���ͣ�ʺ��б���Ϣ
		}
		else
		{
			showUserInfo();
			UserInfo();//��ѯ���������Ϣ
		}
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CBanPlayer::UserInfo()
{
	try
	{		
		CIni mIni;	

		nItem = 0;
		while(listUser.DeleteColumn(0)){}

		int index = theApp.operXD.ReadIntValue("MXD","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//ÿҳ��ʾ50����¼
        CString SearchType="1";
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP����ҽ�ɫ��������ʺš��������͡�ҳ����ÿҳ�ļ�¼����\\������Name��
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�
        socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(SearchType),(unsigned char *)mIni.wcharToChar(SearchType));//��������
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_Query))//���Ͳ�ѯ���������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}

		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// ��ѯ���б���ͣ�ʺ��б���Ϣ
void CBanPlayer::AllBanUserList()
{
	try
	{				
		CIni mIni;

		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP����ҽ�ɫ��������ʺš�ҳ����ÿҳ�ļ�¼����
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_CloseList))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//���Ͳ�ѯ����
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// �����û��б��浱ǰ�к�
void CBanPlayer::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
			nItem = 0;
		}
	}
	*pResult = 0;
}

// ˫���û��б��л�����
void CBanPlayer::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				showBanPlayer();

				UpdateData(false);

				UserAccount = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));//��ȡҪ��ͣ������ʺ�
				UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));//��ȡҪ��ͣ����ҽ�ɫ��

				SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//����Ҫ��ͣ������ʺ�
				SetDlgItemText(IDC_EDITBANREASON,"");				
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

// �л�ѡ����в���
void CBanPlayer::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	          
	CIni mIni;

	if(tbcResult.GetCurSel()==0)//���ѡ�е������������Ϣ��ҳ��
	{
		showUserInfo();
	}
	else if(tbcResult.GetCurSel()==2)//���ѡ�е��Ƿ�ͣ�ʺ��б��ҳ��
	{
		showBanList();
		AllBanUserList();
	}
	else if(tbcResult.GetCurSel()==1)//���ѡ�е��Ƿ�ͣ�ʺŵ�ҳ��
	{
		showBanPlayer();
		cmbType.SetCurSel(0);

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));
			UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));

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
		showUnbindPlayer();
		cmbType.SetCurSel(0);

		UpdateData(false);
		if((listResult.GetItemCount() > 0) && (mItem >= 0))
		{
			
			UserAccount = theApp.operXD.GetValueByColName(&listResult, mItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));
			UserName = theApp.operXD.GetValueByColName(&listResult, mItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));
 
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
		ShowPlayerInfo();
		SetDlgItemText(IDC_EDITSACCOUNT,"");
		while(listResult.DeleteColumn(0)){}
	}
	//else if(tbcResult.GetCurSel()==4)//���ѡ�е��ǲ�ѯ�ʺ���û�б���ͣ��ҳ��
	//{
	//	showSearchPlayer();
	//	SetDlgItemText(IDC_EDITBANACCOUNT,"");
	//	SetDlgItemText(IDC_EDITBANREASON,"");
	//	SetDlgItemText(IDC_ETFILE,"");
	//}
	*pResult = 0;
}

// ������ͣ�ʺ��б��浱ǰ�к�
void CBanPlayer::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 2)
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

// ˫����ͣ�ʺ��б��л�����
void CBanPlayer::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
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
				CIni mIni;
				showUnbindPlayer();
				UpdateData(false);
				UserAccount = theApp.operXD.GetValueByColName(&listResult, mItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));//��ȡҪ��������ʺ�
				UserName = theApp.operXD.GetValueByColName(&listResult, mItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));
				SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//����Ҫ��ͣ������ʺ�
				SetDlgItemText(IDC_EDITBANREASON,"");				
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

// ��ҳ���в�ѯ
void CBanPlayer::OnCbnSelchangeCmbpage()
{
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;
			while(listResult.DeleteColumn(0)){}

			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//ÿҳ��ʾ50����¼

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			//socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_CloseList))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//���Ͳ�ѯ����
			}

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_Page"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// ��ͣ�����ʺ�
void CBanPlayer::OnBnClickedBtnban()
{
	try
	{
		CIni mIni;			
		CString BanAccount = "";
		CString BanTime="";///////////////////////////////��¼��ͣʱ��
        GetDlgItemText(IDC_BANTIME,BanTime);
        //MessageBox(BanTime);
		txtAccount.GetWindowText(BanAccount);//��ȡ����ʺ�
		if(BanAccount == "")//����ʺŲ���Ϊ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","BU_UI_AccountNull"),theApp.operXD.ReadValue("MXD","Warn"),0);
			return;
		}				

		CString BanReason = "";
		txtReason.GetWindowText(BanReason);//��ȡ��ͣ����ԭ��
		if((tbcResult.GetCurSel() == 1) || (tbcResult.GetCurSel() == 3))// ѡ����Ƿ�ͣ�����ʺ�
		{			
			if(strlen(BanReason) >= 256)//��ͣ����ԭ����Ϊ��
			{
				MessageBox(theApp.operXD.ReadValue("MXD","BU_UI_ReasonTooLong"),theApp.operXD.ReadValue("MXD","Warn"),0);
				return;
			}
		}
		else if(tbcResult.GetCurSel() == 4)// ѡ����ǲ�ѯ�ʺ���û�б���ͣ
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ����������
			if(m_ServerName == "")//���������Ʋ���Ϊ��
			{
				MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��ȡ������IP
		}
		int userbyID = theApp.UserByID;//����ԱID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�����ĸ�������������IP������ʺš���ͣ����ԭ�򡢲���ԱID
		char strInt[10];
		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//����ʺ�
		//if(tbcResult.GetCurSel() == 1)
		//{
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_BANREASON,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//��ͣԭ��
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_BANTIME,CEnumCore::TagFormat::TLV_STRING,strlen(BanTime),(unsigned char *)mIni.wcharToChar(BanTime));//��ͣʱ��
	//	}
		//else if(tbcResult.GetCurSel() == 3)
		//{
		//	socketdata.AddTFLV(CEnumCore::TagName::XDJG_UNBANREASON,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//��ͣԭ��
		//}
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		int BanType=0;
		if(tbcResult.GetCurSel() == 1)
		{
			CString cmbBanType="";
			GetDlgItemText(IDC_CMBBANTYPE,cmbBanType);
			
			if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_NOACCOUNT"))
				BanType=BAN_NOACCOUNT;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_MAXCOUNT"))
				BanType=BAN_MAXCOUNT;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_BYGM"))
				BanType=BAN_BYGM;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_GAMEASSIST"))
				BanType=BAN_GAMEASSIST;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_FROZEN"))
				BanType=BAN_FROZEN;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_LOCK"))
				BanType=BAN_LOCK;
			else if(cmbBanType==theApp.operXD.ReadValue("MXD","BAN_NOCOND"))
				BanType=BAN_NOCOND;
		}
		_itoa(BanType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_BANTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ͣ����

		int midlength = socketdata.EnBody();
		if(tbcResult.GetCurSel() == 1)
		{
			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ClosePlayer))//���ͷ�ͣ����ʺŵ�����
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_OpenPlayer))//���ͽ������ʺŵ�����
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
		}
		/*else if(tbcResult.GetCurSel() == 4)
		{
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Account_BANISHMENT_QUERY))//���Ͳ�ѯ����ʺ���û�б���ͣ������
		{
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		}*/		
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//��ѯ����˺���û�б���ͣ
void CBanPlayer::OnBnClickedBtnsearch()
{
	try
	{				
		CIni mIni;

		CString BanAccount = "";
		GetDlgItemText(IDC_EDITSACCOUNT,BanAccount);

		while(listResult.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP����ҽ�ɫ��������ʺš�ҳ����ÿҳ�ļ�¼����
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		//socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AccountIsClose_Query))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//���Ͳ�ѯ����
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// ������Ϣ
void CBanPlayer::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASON,"");
	if(tbcResult.GetCurSel() == 4)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
	}		
}

// ���շ�����Ϣ
LRESULT CBanPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operXD.ReadValue("MXD","Main_UI_ParseData"),theApp.operXD.ReadValue("MXD","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

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

			theApp.operXD.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ

			GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
			if(ServerName == "")//��Ϸ������Ϊ��
				return false;
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			nItem = 0;
			theApp.operXD.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ClosePlayer_Resp://��ͣ����ʺŵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//��ʾ�������

			showUserInfo();
			UserInfo();//��ѯ����ʺ���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_OpenPlayer_Resp://�������ʺŵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//��ʾ�������

			showBanList();
			AllBanUserList();//��ѯ���б���ͣ�ʺ��б�
		}
		break;
	//case CEnumCore::Message_Tag_ID::XDJG_Account_BANISHMENT_QUERY_RESP://��ѯ�ʺ���û�б���ͣ�Ļ�Ӧ
	//	{
	//		CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
	//		CString result = (LPCTSTR)&m_tflv.lpdata;
	//		theApp.operXD.ShowResult(result);//��ʾ���ؽ��
	//	}
	//	break;
	//case CEnumCore::Message_Tag_ID::XDJG_CloseList_Resp://����������ͣ�Ľ��//maple add
	//	{

	//		CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
	//		CString result = (LPCTSTR)&m_tflv.lpdata;
	//		theApp.operXD.ShowResult(result);//��ʾ���ؽ��

	//		//showBanList();
	//		//AllBanUserList();//��ѯ���б���ͣ�ʺ��б�
	//	}
	default:
		{
			if(pageInfo)
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					mItem = -1;
					pageInfo = false;					
					cmbPage.ResetContent();
					while(listResult.DeleteColumn(0)){}
				}
				else
				{
					mItem = 0;
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
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//�����û�������Ϣ��������������
void CBanPlayer::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operXD;
	theApp.operXD.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CBanPlayer::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operXD;
	theApp.operXD.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CBanPlayer::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
}

// �رնԻ���
void CBanPlayer::OnClose()
{
	dlgStatus = theApp.operXD.ReadIntValue("MXD","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//��ʾ���������Ϣ
void CBanPlayer::showUserInfo()
{
	tbcResult.SetCurSel(0);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_HIDE);
}

//��ʾ��ͣ�ʺ�
void CBanPlayer::showBanPlayer()
{
	//OperationPAL operXD;
	tbcResult.SetCurSel(1);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	cmbType.ResetContent();
	//cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_NOACCOUNT"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_MAXCOUNT"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_BYGM"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_GAMEASSIST"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_FROZEN"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_LOCK"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","BAN_NOCOND"));
	cmbType.SetCurSel(0);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operXD.ReadValue("MXD","BU_UI_reason"));//��ͣԭ��
	SetDlgItemText(IDC_BTNBAN,theApp.operXD.ReadValue("MXD","BU_UI_TpgOpen"));//�ʺŷ�ͣ
	//txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_SHOW);
}

//��ʾ��ͣ�ʺ��б�
void CBanPlayer::showBanList()
{
	tbcResult.SetCurSel(2);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_HIDE);
}

//��ʾ����ʺ�
void CBanPlayer::showUnbindPlayer()
{
	tbcResult.SetCurSel(3);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operXD.ReadValue("MXD","BU_UI_UnBind"));//���ԭ��
	SetDlgItemText(IDC_BTNBAN,theApp.operXD.ReadValue("MXD","BU_UI_BtnSave"));//����ʺ�

	//txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������
	//txtAccount.SetReadOnly(false);
	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_HIDE);
}

//��ѯ�ʺ���û�з�ͣ
void CBanPlayer::showSearchPlayer()
{
	tbcResult.SetCurSel(4);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_BTNBAN,theApp.operXD.ReadValue("MXD","Search"));
}

//��ѯ�˺���û�б���ͣ
void CBanPlayer::ShowPlayerInfo()
{
	tbcResult.SetCurSel(4);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLSACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITSACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNSEARCH)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBBANTIME2)->ShowWindow(SW_HIDE);
}

//bool CBanPlayer::ReadXls(CString m_filePath,CString* m_allUserAccount,CString* m_allUserChar)
//{
//	try
//	{
//		CoInitialize(NULL);
//		_ConnectionPtr m_pConnection;
//		_RecordsetPtr	m_pRecordset;
//		CString ConnectionString="";
//		//CString allusername="";
//		ConnectionString = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");   
//		ConnectionString += m_filePath;   //excel   file   name   
//		ConnectionString += _T(";Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\""); 
//
//
//		BSTR resultsString = ConnectionString.AllocSysString();
//
//
//
//		m_pConnection.CreateInstance(__uuidof(Connection));
//
//		m_pConnection->Open(resultsString,"","",adModeUnknown);
//		m_pRecordset.CreateInstance(__uuidof(Recordset));
//		m_pRecordset->Open("select * from [Sheet1$]",
//			m_pConnection.GetInterfacePtr(),
//			adOpenDynamic,
//			adLockOptimistic,
//			adCmdText);
//
//		if(m_pRecordset->adoEOF) AfxMessageBox("���ĵ�û������");
//		//////��һ�в���
//		while(!m_pRecordset->adoEOF)
//		{
//			if(m_pRecordset->GetFields()->GetItem("����ʺ�")->Value.vt==VT_NULL
//				||m_pRecordset->GetFields()->GetItem("��ɫ����")->Value.vt==VT_NULL) 
//			{
//				AfxMessageBox("��ʽ����");
//				break;
//			}
//			CString tmpUserName=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem("����ʺ�")->GetValue());
//			*m_allUserAccount += tmpUserName;
//			*m_allUserAccount += "|";
//
//			CString tmpChar=(LPCSTR)_bstr_t(m_pRecordset->GetFields()->GetItem("��ɫ����")->GetValue());
//			*m_allUserChar += tmpChar;
//			*m_allUserChar += "|";
//
//
//			m_pRecordset->MoveNext();
//		}
//		m_pRecordset->Close();
//		if(m_pRecordset) m_pRecordset.Release();
//		m_pConnection->Close();
//		if(m_pConnection) m_pConnection.Release();
//		CoUninitialize();
//
//	}
//	catch(...)
//	{
//		return false;
//	}
//	return TRUE;
//}

//void CBanPlayer::OnBnClickedBtbrowse()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	char path[256];
//	GetCurrentDirectory(256,path);
//	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
//
//	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"�ļ�����(*.xls)|*.xls||");
//
//
//	if(lpszOpenFile->DoModal()==IDOK)//�������Ի���ȷ����ť
//	{
//		CString szGetName;
//		szGetName=lpszOpenFile->GetPathName();
//		SetDlgItemText(IDC_ETFILE,szGetName);
//		SetCurrentDirectory(path);
//
//	}
//	delete lpszOpenFile;
//}
//
//void CBanPlayer::OnBnClickedBtmulticlose()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	try
//	{
//		CIni mIni;
//		CString allUserName="";
//		CString allChar="";
//		CString filename="";
//		CString BanReason="";
//
//		GetDlgItemText(IDC_EDITBANREASON,BanReason);
//		if(strlen(BanReason)<1)
//		{
//			MessageBox("��ͣ���ݲ���Ϊ��");
//			return;
//		}
//		GetDlgItemText(IDC_ETFILE,filename);
//		if(!ReadXls(filename,&allUserName,&allChar))
//		{
//			AfxMessageBox("��ʽ����");
//			return;
//		}
//		if(strlen(allUserName)>2000||strlen(allChar)>2000)
//		{
//			AfxMessageBox("�������������,���ڷ���");
//			return;
//		}
//		else
//		{
//			int userbyID = theApp.UserByID;//����ԱID
//
//			CSocketData socketdata;
//			socketdata.InitCreate(1,10);//�����ĸ�������������IP������ʺš���ͣ����ԭ�򡢲���ԱID
//
//			CString m_ServerName;
//			GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ����������
//			if(m_ServerName == "")//���������Ʋ���Ϊ��
//			{
//				MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
//				return;
//			}
//			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��ȡ������IP
//
//			char strInt[10];
//
//			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
//			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(m_ServerName),(unsigned char*)mIni.wcharToChar(m_ServerName));//������name
//			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(allUserName),(unsigned char *)mIni.wcharToChar(allUserName));//��������ʺ�
//			socketdata.AddTFLV(CEnumCore::TagName::PAL_REASON,CEnumCore::TagFormat::TLV_STRING,strlen(BanReason),(unsigned char *)mIni.wcharToChar(BanReason));//��ͣ����ԭ��
//
//			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(allChar),(unsigned char *)mIni.wcharToChar(allChar));//������ҽ�ɫ��
//
//			_itoa(userbyID,strInt,10);
//			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID
//
//			int midlength = socketdata.EnBody();
//
//			if(theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RELOADFUNCTIONSWITCH))
//			{
//				::EnableWindow(this->GetParent()->m_hWnd,false);
//				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//���Ͳ�ѯ����
//			}
//
//			socketdata.Destroy();
//		}
//
//	}
//	catch(...)
//	{
//
//	}
//}
