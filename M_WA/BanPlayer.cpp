#include "..\m_xd\banplayer.h"
#include "..\m_xd\banplayer.h"
// BanPlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_WA.h"
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
	
	DDX_Control(pDX, IDC_EDITBANREASONCOM, cmbReason);
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

	//OperationWA operWA;
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//��ʼ�����Ի���

	if(theApp.operWA.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CBanPlayer::InitUI()
{
	SetWindowText(theApp.operWA.ReadValue("MWA","BU_UI_BanPlayer"));
  
	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Close"));
	SetDlgItemText(IDC_LBLHINTA,theApp.operWA.ReadValue("MWA","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLHINT,theApp.operWA.ReadValue("MWA","BU_UI_LblHint"));	
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLBANACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLBANTIME,theApp.operWA.ReadValue("MWA","BU_UI_LBLBANTIME"));
	SetDlgItemText(IDC_LBLBANDATE,theApp.operWA.ReadValue("MWA","BU_UI_LBLBANDATE"));
	SetDlgItemText(IDC_LBLBANTYPE,theApp.operWA.ReadValue("MWA","WA_BANDescription"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operWA.ReadValue("MWA","BU_UI_reason"));	
	SetDlgItemText(IDC_BTNBAN,theApp.operWA.ReadValue("MWA","BU_UI_TpgOpen"));
	SetDlgItemText(IDC_BTNRESET,theApp.operWA.ReadValue("MWA","Reset"));
	
	tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","BU_UI_TpgOpen"));
	tbcResult.InsertItem(2,theApp.operWA.ReadValue("MWA","BU_UI_TpgList"));
	tbcResult.InsertItem(3,theApp.operWA.ReadValue("MWA","BU_UI_BtnSave"));
	
	cmbReason.AddString(theApp.operWA.ReadValue("MWA","R_SYSTEM"));
	cmbReason.AddString(theApp.operWA.ReadValue("MWA","R_SYSTEM_TEMP"));
	cmbReason.AddString(theApp.operWA.ReadValue("MWA","R_USERCUSTOM"));
	cmbReason.AddString(theApp.operWA.ReadValue("MWA","R_USERCUSTOM_TEMP"));
		///////////////////////////
	//////////////////////////
	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));

	SetDlgItemText(IDC_LBLSERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDOK,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDCANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLSELFTYPE,theApp.operWA.ReadValue("MWA","UIC_UI_SelfType"));
}

//�����ݼ���Ӧ����
BOOL CBanPlayer::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operWA.CopyListInfo(&listResult);
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
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
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

// ��ѯ������Ϣ
void CBanPlayer::OnBnClickedOk()
{
	try
	{
		CIni mIni;

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
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITNAME,UserName);//��ȡ��ҽ�ɫ��

		if ((UserName == "") && (UserAccount == ""))
		{
			tbcResult.SetCurSel(2);
			showBanList();
			AllBanUserList();//��ѯ���б���ͣ�ʺ��б���Ϣ
		}
		else
		{
			tbcResult.SetCurSel(0);
			showUserInfo();
			UserInfo();//��ѯ���������Ϣ
		}
		//else if (tbcResult.GetCurSel() == 2)
		//{
		//	showBanList();
		//	AllBanUserList();//��ѯ���б���ͣ�ʺ��б���Ϣ
		//}
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

		int index = theApp.operWA.ReadIntValue("MWA","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼
		CString SearchType="1";
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP����ҽ�ɫ��������ʺš��������͡�ҳ����ÿҳ�ļ�¼����\\������Name��
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		//socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�
	//	socketdata.AddTFLV(CEnumCore::TagName::WA_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(SearchType),(unsigned char *)mIni.wcharToChar(SearchType));//��������
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query))//���Ͳ�ѯ���������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_UserInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ѯ���б���ͣ�ʺ��б���Ϣ
void CBanPlayer::AllBanUserList()
{
	//OperationWA operWA;
	try
	{				
		CIni mIni;

		mItem = -1;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}
		char strInt[10];
		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP����ҽ�ɫ��������ʺš�ҳ����ÿҳ�ļ�¼����
		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		//socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		//socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
		//socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_CloseList))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//���Ͳ�ѯ����
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_UserInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
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

				UserAccount = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));//��ȡҪ��ͣ������ʺ�
				UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));//��ȡҪ��ͣ����ҽ�ɫ��

				SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//����Ҫ��ͣ������ʺ�
				SetDlgItemText(IDC_EDITBANREASONCOM,"");				
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
		UserInfo();
	}
	else if(tbcResult.GetCurSel()==2)//���ѡ�е��Ƿ�ͣ�ʺ��б��ҳ��
	{		
		showBanList();
		AllBanUserList();
	}
	else if(tbcResult.GetCurSel()==1)//���ѡ�е��Ƿ�ͣ�ʺŵ�ҳ��
	{		
		showBanPlayer();

		UpdateData(false);

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));
			UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));

			SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);
			SetDlgItemText(IDC_EDITBANREASONCOM,"");
		}
		else
		{
			SetDlgItemText(IDC_EDITBANACCOUNT,"");
			SetDlgItemText(IDC_EDITBANREASONCOM,"");
		}
	}
	else if(tbcResult.GetCurSel()==3)//���ѡ�е��ǽ���ʺŵ�ҳ��
	{
		showUnbindPlayer();

		UpdateData(false);
		if((listResult.GetItemCount() > 0) && (mItem >= 0))
		{

			UserAccount = theApp.operWA.GetValueByColName(&listResult, mItem, theApp.operWA.ReadValue("MWA","WA_Account"));
			UserName = theApp.operWA.GetValueByColName(&listResult, mItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));

			SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);
			SetDlgItemText(IDC_EDITBANREASONCOM,"");
		}
		else
		{
			SetDlgItemText(IDC_EDITBANACCOUNT,"");
			SetDlgItemText(IDC_EDITBANREASONCOM,"");
		}
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
				//showBanPlayer();
				UpdateData(false);
				UserAccount = theApp.operWA.GetValueByColName(&listResult, mItem, theApp.operWA.ReadValue("MWA","WA_Account"));//��ȡҪ��������ʺ�
				UserName = theApp.operWA.GetValueByColName(&listResult, mItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));
				SetDlgItemText(IDC_EDITBANACCOUNT,UserAccount);//����Ҫ��ͣ������ʺ�
				SetDlgItemText(IDC_EDITBANREASONCOM,"");				
			}
		}
		else
		{
			mItem = 0;
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
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			//socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			if(tbcResult.GetCurSel() == 0)
			{
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�
			}
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(tbcResult.GetCurSel() == 0)
			{
				if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query))
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//���Ͳ�ѯ����
				}
				socketdata.Destroy();
			}
			if(tbcResult.GetCurSel() == 2)
			{
				if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_CloseList))
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//���Ͳ�ѯ����
				}
				socketdata.Destroy();
			}
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Page"),theApp.operWA.ReadValue("MWA","Error"),0);
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
		int RealTime = atoi(BanTime)*24*60;

		txtAccount.GetWindowText(BanAccount);//��ȡ����ʺ�
		if(BanAccount == "")//����ʺŲ���Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","BU_UI_AccountNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}				

		CString BanType = "";
		GetDlgItemText(IDC_EDITBANTYPE, BanType);
		if(tbcResult.GetCurSel() == 1)// ѡ����Ƿ�ͣ�����ʺ�
		{			
			if(strlen(BanType) >= 256 || strlen(BanType)==0||BanTime=="")//��ͣ����ԭ����Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","BU_UI_ContentNull"),theApp.operWA.ReadValue("MWA","Warn"),0);
				return;
			}
		}
		else if(tbcResult.GetCurSel() == 4)// ѡ����ǲ�ѯ�ʺ���û�б���ͣ
		{
			CString m_ServerName;
			GetDlgItemText(IDC_CMBSERVER,m_ServerName);//��ȡ����������
			if(m_ServerName == "")//���������Ʋ���Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��ȡ������IP
		}
		int userbyID = theApp.UserByID;//����ԱID
		int BanReson=0;
		BanReson = cmbReason.GetCurSel()+1;

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�����ĸ�������������IP������ʺš���ͣ����ԭ�򡢲���ԱID
		char strInt[10];
		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
//		socketdata.AddTFLV(CEnumCore::TagName::WA_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char*)mIni.wcharToChar(ServerName));//������name
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(BanAccount),(unsigned char *)mIni.wcharToChar(BanAccount));//����ʺ�
		_itoa(BanReson, strInt, 10);
		if(tbcResult.GetCurSel() == 1)
		{
			socketdata.AddTFLV(CEnumCore::TagName::WA_Reason,CEnumCore::TagFormat::TLV_STRING, sizeof(int), (unsigned char *)&strInt);//��ͣԭ��
			
			_itoa(RealTime, strInt, 10);
			socketdata.AddTFLV(CEnumCore::TagName::WA_Time,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ͣʱ��
			socketdata.AddTFLV(CEnumCore::TagName::WA_Description, CEnumCore::TagFormat::TLV_STRING,strlen(BanType),(unsigned char *)mIni.wcharToChar(BanType));//��ͣ����
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			socketdata.AddTFLV(CEnumCore::TagName::WA_Reason,CEnumCore::TagFormat::TLV_STRING,sizeof(int),(unsigned char *)&strInt);//��ͣԭ��
		}

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		int midlength = socketdata.EnBody();

		if(tbcResult.GetCurSel() == 1)
		{
			if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ClosePlayer))//���ͷ�ͣ����ʺŵ�����
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
		}
		else if(tbcResult.GetCurSel() == 3)
		{
			if(theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_OpenPlayer))//���ͽ������ʺŵ�����
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// ������Ϣ
void CBanPlayer::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITBANREASONCOM,"");
	if(tbcResult.GetCurSel() == 3)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
		SetDlgItemText(IDC_EDITBANREASONCOM,"");
	}
	if(tbcResult.GetCurSel() == 1)
	{
		SetDlgItemText(IDC_EDITBANACCOUNT,"");
        SetDlgItemText(IDC_BANTIME,"");
	    SetDlgItemText(IDC_EDITBANTYPE,"");
	    SetDlgItemText(IDC_EDITBANREASONCOM,"");
	}
}

// ���շ�����Ϣ
LRESULT CBanPlayer::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operWA.ReadValue("MWA","Main_UI_ParseData"),theApp.operWA.ReadValue("MWA","ERROR"),0);		
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

			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
			ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			nItem = 0;
			if(pageInfo)
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					mItem = -1;
					pageInfo = false;					
					cmbPage.ResetContent();
					while(listUser.DeleteColumn(0)){}
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
	case CEnumCore::Message_Tag_ID::WA_CloseList_Resp://��ѯ���б���ͣ�ʺ��б�Ļ�Ӧ
		{
			if(pageInfo)
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	case CEnumCore::Message_Tag_ID::WA_ClosePlayer_Resp://��ͣ����ʺŵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ�������

			showUserInfo();
			UserInfo();//��ѯ����ʺ���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_OpenPlayer_Resp://�������ʺŵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ�������

			showBanList();
			AllBanUserList();//��ѯ���б���ͣ�ʺ��б�
		}
		break;
		//case CEnumCore::Message_Tag_ID::WA_Account_BANISHMENT_QUERY_RESP://��ѯ�ʺ���û�б���ͣ�Ļ�Ӧ
		//	{
		//		CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
		//		CString result = (LPCTSTR)&m_tflv.lpdata;
		//		theApp.operWA.ShowResult(result);//��ʾ���ؽ��
		//	}
		//	break;
		//case CEnumCore::Message_Tag_ID::WA_CloseList_Resp://����������ͣ�Ľ��//maple add
		//	{

		//		CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
		//		CString result = (LPCTSTR)&m_tflv.lpdata;
		//		theApp.operWA.ShowResult(result);//��ʾ���ؽ��

		//		//showBanList();
		//		//AllBanUserList();//��ѯ���б���ͣ�ʺ��б�
		//	}
	default:
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
	theApp.operWA.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CBanPlayer::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operWA.SortListInfo(&listResult,pNMHDR,pResult);
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
	dlgStatus = theApp.operWA.ReadIntValue("MWA","Close");//�رմ���	
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

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASONCOM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANDATE)->ShowWindow(SW_HIDE);
}

//��ʾ��ͣ�ʺ�
void CBanPlayer::showBanPlayer()
{
	tbcResult.SetCurSel(1);

	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASONCOM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operWA.ReadValue("MWA","BU_UI_reason"));//��ͣԭ��
	SetDlgItemText(IDC_BTNBAN,theApp.operWA.ReadValue("MWA","BU_UI_TpgOpen"));//�ʺŷ�ͣ
	txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANDATE)->ShowWindow(SW_SHOW);
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

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASONCOM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANDATE)->ShowWindow(SW_HIDE);


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

	GetDlgItem(IDC_LBLBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_SHOW);
	//GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASONCOM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDITBANTYPE)->ShowWindow(SW_HIDE);
	
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_LBLBANREASON,theApp.operWA.ReadValue("MWA","BU_UI_UnBind"));//���ԭ��
	SetDlgItemText(IDC_BTNBAN,theApp.operWA.ReadValue("MWA","BU_UI_BtnSave"));//����ʺ�

	//txtAccount.SetReadOnly(true);//����ʺŵ�CEdit��������Ϊֻ������
	txtAccount.SetReadOnly(false);
	GetDlgItem(IDC_LBLFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFILE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANREASON)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BANTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBANDATE)->ShowWindow(SW_HIDE);
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
	//GetDlgItem(IDC_EDITBANREASON)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDITBANREASONCOM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTNBAN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTMULTICLOSE)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);

	SetDlgItemText(IDC_BTNBAN,theApp.operWA.ReadValue("MWA","Search"));

	//txtAccount.SetReadOnly(false);//����ʺŵ�CEdit����ȡ��ֻ������
}