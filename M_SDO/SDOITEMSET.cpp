// SDOITEMSET.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOITEMSET.h"
#include ".\sdoitemset.h"


// CSDOITEMSET �Ի���

IMPLEMENT_DYNAMIC(CSDOITEMSET, CDialog)
CSDOITEMSET::CSDOITEMSET(CWnd* pParent /*=NULL*/)
	: CDialog(CSDOITEMSET::IDD, pParent)
{
}

CSDOITEMSET::~CSDOITEMSET()
{
}

void CSDOITEMSET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbUPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_LISTGIFTBOX, listGiftBox);
	DDX_Control(pDX, IDC_CMBBIGTYPE, cmbBigType);
	DDX_Control(pDX, IDC_CMBSMALLTYPE, cmbSmallType);
	DDX_Control(pDX, IDC_CMBGOODS, cmbGoods);
	DDX_Control(pDX, IDC_CHECK1, btnDark);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
}


BEGIN_MESSAGE_MAP(CSDOITEMSET, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)

	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTGIFTBOX, OnNMDblclkListgiftbox)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTGIFTBOX, OnLvnColumnclickListgiftbox)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_BN_CLICKED(IDC_BTUPDATE, OnBnClickedBtupdate)
	ON_BN_CLICKED(IDC_BTRESET, OnBnClickedBtreset)
	ON_CBN_SELCHANGE(IDC_CMBBIGTYPE, OnCbnSelchangeCmbbigtype)
	ON_CBN_SELCHANGE(IDC_CMBSMALLTYPE, OnCbnSelchangeCmbsmalltype)
	ON_BN_CLICKED(IDC_BTQUERY, OnBnClickedBtquery)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BTADD, OnBnClickedBtadd)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_BN_CLICKED(IDC_BTNSOCIAL, OnBnClickedBtnsocial)
	ON_BN_CLICKED(IDC_BTNLUCKY, OnBnClickedBtnlucky)
END_MESSAGE_MAP()


// CSDOITEMSET ��Ϣ�������

// ��ʼ���Ի���
BOOL CSDOITEMSET::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();// ��ʼ����ʾ�ַ�

	nItem = 0;
	nSelect=0;
	mItem=0;

	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//��ʼ��һЩ˽�б���
	UserID=0;

	iLevel=0;
	iExperience=0;
	iTotal=0;
	iWin=0;
	iBalance=0;
	iFall=0;
	iReputation=0;
	iGCash=0;
	iMCash=0;
	iSex=0;
	iSocial=0;
	iLucky=0;

	iItemCode=0;
	iItemCode1=0;//��ӵ��ߵı��

	iType=0;//����ֵ
	iSort=0;//С��ֵ

	ShowUserInfo();//��ʾ�û�������Ϣ

	SetProp(listUser.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listUser.GetSafeHwnd(),"����˳��",(HANDLE)1);

    SetProp(listResult.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listResult.GetSafeHwnd(),"����˳��",(HANDLE)1);

	 SetProp(listGiftBox.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listGiftBox.GetSafeHwnd(),"����˳��",(HANDLE)1);

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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}

	
	if(listResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listResult.MoveWindow(newRect);//���ú�listResult��λ��		
	}

	if(listGiftBox.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGiftBox.MoveWindow(newRect);//���ú�listGiftBox��λ��		
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
void CSDOITEMSET::InitUI()
{
	SetWindowText(theApp.operSDO.ReadValue("MSDO","IS_UI_ItemSet"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operSDO.ReadValue("MSDO","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operSDO.ReadValue("MSDO","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operSDO.ReadValue("MSDO","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operSDO.ReadValue("MSDO","UIC_UI_lblNick"));
	SetDlgItemText(IDSEARCH,theApp.operSDO.ReadValue("MSDO","Search"));
	SetDlgItemText(IDCANCEL,theApp.operSDO.ReadValue("MSDO","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operSDO.ReadValue("MSDO","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operSDO.ReadValue("MSDO","Account"));
	SetDlgItemText(IDC_LBLLEVEL,theApp.operSDO.ReadValue("MSDO","Level"));
	SetDlgItemText(IDC_LBLEXPE,theApp.operSDO.ReadValue("MSDO","Experience"));
	SetDlgItemText(IDC_LBLREPU,theApp.operSDO.ReadValue("MSDO","Reputation"));//IDC_LBLREPU
	SetDlgItemText(IDC_LBLGCASH,theApp.operSDO.ReadValue("MSDO","GCash"));
	SetDlgItemText(IDC_LBLTOTAL,theApp.operSDO.ReadValue("MSDO","Total"));
	SetDlgItemText(IDC_LBLWIN,theApp.operSDO.ReadValue("MSDO","Win"));
	SetDlgItemText(IDC_LBLFALL,theApp.operSDO.ReadValue("MSDO","Fall"));
	SetDlgItemText(IDC_LBLBALANCE,theApp.operSDO.ReadValue("MSDO","Balance"));
	SetDlgItemText(IDC_LBLMCASH,theApp.operSDO.ReadValue("MSDO","MCash"));

	SetDlgItemText(IDC_LBLSOCIAL,theApp.operSDO.ReadValue("MSDO","Social"));
	SetDlgItemText(IDC_LBLLUCKY,theApp.operSDO.ReadValue("MSDO","Lucky"));

	SetDlgItemText(IDC_LBLBASIC,theApp.operSDO.ReadValue("MSDO","BasicInfo"));
	SetDlgItemText(IDC_BTNSOCIAL,theApp.operSDO.ReadValue("MSDO","UpdateSocial"));
	SetDlgItemText(IDC_BTNLUCKY,theApp.operSDO.ReadValue("MSDO","UpdateLucky"));


	SetDlgItemText(IDC_BTUPDATE,theApp.operSDO.ReadValue("MSDO","Modify"));
	SetDlgItemText(IDC_BTRESET,theApp.operSDO.ReadValue("MSDO","Close"));

	SetDlgItemText(IDC_GRPCHOOSE,theApp.operSDO.ReadValue("MSDO","Choose"));
	SetDlgItemText(IDC_LBLBIGTYPE,theApp.operSDO.ReadValue("MSDO","BigType"));
	SetDlgItemText(IDC_LBLSMALLTYPE,theApp.operSDO.ReadValue("MSDO","SmallType"));
	SetDlgItemText(IDC_LBLGOODS,theApp.operSDO.ReadValue("MSDO","Goods"));

	SetDlgItemText(IDC_GRPDARK,theApp.operSDO.ReadValue("MSDO","Account"));
	SetDlgItemText(IDC_LBLITEMNAME,theApp.operSDO.ReadValue("MSDO","ItemName"));
	SetDlgItemText(IDC_BTQUERY,theApp.operSDO.ReadValue("MSDO","Search"));

	SetDlgItemText(IDC_GRPPRESENT,theApp.operSDO.ReadValue("MSDO","Present"));
	SetDlgItemText(IDC_LBLLIMIT,theApp.operSDO.ReadValue("MSDO","UseLimit"));
	SetDlgItemText(IDC_LBLUSETIMES,theApp.operSDO.ReadValue("MSDO","UseTimes"));
	SetDlgItemText(IDC_LBLSUBJECT,theApp.operSDO.ReadValue("MSDO","Subject"));
	SetDlgItemText(IDC_LBLCONTENT,theApp.operSDO.ReadValue("MSDO","Content"));
	SetDlgItemText(IDC_BTADD,theApp.operSDO.ReadValue("MSDO","Add"));

	SetDlgItemText(IDC_CHECK1,theApp.operSDO.ReadValue("MSDO","DarkQuery"));

	tbcResult.InsertItem(0,theApp.operSDO.ReadValue("MSDO","UIC_UI_tpgCharacterInfo"));//��ɫ��Ϣ
	tbcResult.InsertItem(1,theApp.operSDO.ReadValue("MSDO","IS_UI_tpgUpdateCharacter"));//
	tbcResult.InsertItem(2,theApp.operSDO.ReadValue("MSDO","IS_UI_tpgEquipment"));//
	tbcResult.InsertItem(3,theApp.operSDO.ReadValue("MSDO","IS_UI_tpgGiftBox"));//
	tbcResult.InsertItem(4,theApp.operSDO.ReadValue("MSDO","IS_UI_tpgPresentItem"));//
}

// �Զ��ı��С
void CSDOITEMSET::OnSize(UINT nType, int cx, int cy)
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

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}

	if(listGiftBox.m_hWnd != NULL)
	{
		newRect.top = rs.top + grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGiftBox.MoveWindow(newRect);//���ú�listGiftBox��λ��
	}
}

//���ñ�����ɫ
HBRUSH CSDOITEMSET::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//�����ݼ���Ӧ����
BOOL CSDOITEMSET::PreTranslateMessage(MSG* pMsg)
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
					theApp.operSDO.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listResult);
				}
				else if(pMsg->hwnd == listGiftBox.m_hWnd)
				{
					theApp.operSDO.CopyListInfo(&listGiftBox);
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
				else if(pMsg->hwnd == listGiftBox.m_hWnd)
				{
					for(int i=0; i<listGiftBox.GetItemCount(); i++)
					{
					    listGiftBox.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listGiftBox.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}


// �رնԻ���
void CSDOITEMSET::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Close");//�رմ���	

	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!ItemCodeList.IsEmpty())
	{
		ItemCodeList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CSDOITEMSET::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// ��ʾ��ɫ������Ϣ
void CSDOITEMSET::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);//IDC_CMBUIBPAGE
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTGIFTBOX)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLACCOUNT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLEXPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETEXPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLREPU)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETREPU)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLTOTAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETTOTAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLWIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETWIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLFALL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFALL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMCASH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLUCKY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBASIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPCHOOSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGOODS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBGOODS)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPDARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);//�б��
	GetDlgItem(IDC_BTQUERY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPRESENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCONTENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
}

//��ʾ�޸Ľ�ɫ����
void CSDOITEMSET::ShowUpdateUser()
{
	tbcResult.SetCurSel(1);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);//IDC_CMBUIBPAGE
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTGIFTBOX)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLACCOUNT1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETACCOUNT)->EnableWindow(false);
	
	GetDlgItem(IDC_LBLLEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETLEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLEXPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETEXPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLREPU)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETREPU)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLGCASH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETGCASH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLTOTAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETTOTAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLWIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETWIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLFALL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETFALL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBALANCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETBALANCE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLMCASH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETMCASH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETMCASH)->EnableWindow(false);

	GetDlgItem(IDC_LBLSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLUCKY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBASIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPCHOOSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGOODS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBGOODS)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPDARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);//�б��
	GetDlgItem(IDC_BTQUERY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPRESENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCONTENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
}

//��ʾװ��
void CSDOITEMSET::ShowEquipment()
{
	tbcResult.SetCurSel(2);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);//IDC_CMBUIBPAGE
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTGIFTBOX)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLACCOUNT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLEXPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETEXPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLREPU)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETREPU)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLTOTAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETTOTAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLWIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETWIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLFALL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFALL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMCASH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLUCKY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBASIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNLUCKY)->ShowWindow(SW_HIDE);


	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPCHOOSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGOODS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBGOODS)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPDARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);//�б��
	GetDlgItem(IDC_BTQUERY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPRESENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCONTENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
}

//��ʾ�����
void CSDOITEMSET::ShowGiftBox()
{
	tbcResult.SetCurSel(3);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);//IDC_CMBUIBPAGE
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTGIFTBOX)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LBLACCOUNT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLEXPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETEXPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLREPU)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETREPU)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLTOTAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETTOTAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLWIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETWIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLFALL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFALL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMCASH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLUCKY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBASIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPCHOOSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGOODS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBGOODS)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPDARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETITEMNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_HIDE);//�б��
	GetDlgItem(IDC_BTQUERY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPPRESENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLIMIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETUSETIMES)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLCONTENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTADD)->ShowWindow(SW_HIDE);
}

//��ʾ��ӵ���
void CSDOITEMSET::ShowAddItem()
{
	tbcResult.SetCurSel(4);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);//IDC_CMBUIBPAGE
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTGIFTBOX)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLACCOUNT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLEXPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETEXPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLREPU)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETREPU)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETGCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLTOTAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETTOTAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLWIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETWIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLFALL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETFALL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETBALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLMCASH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETMCASH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLLUCKY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ETLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBLBASIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNSOCIAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNLUCKY)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTUPDATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTRESET)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_GRPCHOOSE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLGOODS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBGOODS)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPDARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLITEMNAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETITEMNAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(SW_SHOW);//�б��
	GetDlgItem(IDC_BTQUERY)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRPPRESENT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLLIMIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETLIMIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLUSETIMES)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETUSETIMES)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLSUBJECT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETSUBJECT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLCONTENT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ETCONTENT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
	btnDark.SetCheck(BST_UNCHECKED);

	GetDlgItem(IDC_BTADD)->ShowWindow(SW_SHOW);
	BigTypeData();
}

// �����û��б��浱ǰ�к�
void CSDOITEMSET::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			nItem = listUser.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�
			UserAccount = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Account"));//����ʺ�
			UserName = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_NickName"));//����ǳ�
			UserID = atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_UserIndexID")));//���ID

			iLevel =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Level")));
			iExperience =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Exp")));
			iTotal =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GameTotal")));
			iWin =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GameWin")));
			iBalance =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_DogFall")));
			iFall =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GameFall")));
			iReputation =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Reputation")));
			iGCash =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GCash")));
			iMCash =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_MCash")));

			iSex =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SEX")));

			iSocial=atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SocialValue")));
			iLucky=atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Lucky")));
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

//˫����ɫ��Ϣ�б�
void CSDOITEMSET::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);
				ShowUpdateUser();				

				UserAccount = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Account"));//����ʺ�
				UserName = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_NickName"));//����ǳ�
				UserID = atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_UserIndexID")));//���ID

				iLevel =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Level")));
				iExperience =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Exp")));
				iTotal =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GameTotal")));
				iWin =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GameWin")));
				iBalance =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_DogFall")));
				iFall =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GameFall")));
				iReputation =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Reputation")));
				iGCash =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_GCash")));
				iMCash =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_MCash")));

				iSex =atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SEX")));

				iSocial=atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_SocialValue")));
				iLucky=atoi(theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Lucky")));

				SetDlgItemText(IDC_ETACCOUNT,UserAccount);
				SetDlgItemInt(IDC_ETLEVEL,iLevel);
				SetDlgItemInt(IDC_ETEXPE,iExperience);
				SetDlgItemInt(IDC_ETREPU,iReputation);
				SetDlgItemInt(IDC_ETGCASH,iGCash);
				SetDlgItemInt(IDC_ETTOTAL,iTotal);
				SetDlgItemInt(IDC_ETWIN,iWin);
				SetDlgItemInt(IDC_ETFALL,iFall);
				SetDlgItemInt(IDC_ETBALANCE,iBalance);
				SetDlgItemInt(IDC_ETMCASH,iMCash);

				SetDlgItemInt(IDC_ETSOCIAL,iSocial);
				SetDlgItemInt(IDC_ETLUCKY,iLucky);
			}
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

//˫��װ����Ϣ�б�ɾ��
void CSDOITEMSET::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nSelect = listResult.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

		if(nSelect >= 0)
		{

			iItemCode= atoi(theApp.operSDO.GetValueByColName(&listResult, nSelect , theApp.operSDO.ReadValue("MSDO","SDO_ItemCode")));
			ItemName =theApp.operSDO.GetValueByColName(&listResult, nItem, theApp.operSDO.ReadValue("MSDO","SDO_ItemName"));

			DeleteEquipment();
		}
	}
	else
	{
		nSelect = 0;
	}
	*pResult = 0;
}

//ɾ������װ��
void CSDOITEMSET::DeleteEquipment()
{
	try
	{
		UpdateData(true);
		CString strMsg = theApp.operSDO.ReadValue("MSDO","IM_UI_DelItem");
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
		{
			return;
		}

		CIni mIni;

		CSocketData socketdata;	
		socketdata.InitCreate(1,9);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int userByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//��ҽ�ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��������

		_itoa(iItemCode,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_ITEMSHOP_DELETE))//
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

//˫���������Ϣ�б�ɾ��
void CSDOITEMSET::OnNMDblclkListgiftbox(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listGiftBox.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listGiftBox.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		mItem = listGiftBox.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

		if(mItem >= 0)
		{

			iItemCode= atoi(theApp.operSDO.GetValueByColName(&listGiftBox, mItem , theApp.operSDO.ReadValue("MSDO","SDO_ItemCode")));
			ItemName =theApp.operSDO.GetValueByColName(&listGiftBox, nItem, theApp.operSDO.ReadValue("MSDO","SDO_ItemName"));
			DeleteGiftBox();
		}
	}
	else
	{
		mItem = 0;
	}
	*pResult = 0;
}

//ɾ�������
void CSDOITEMSET::DeleteGiftBox()
{
	try
	{
		UpdateData(true);
		CString strMsg = theApp.operSDO.ReadValue("MSDO","IM_UI_DelItem");
		if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
		{
			return;
		}

		CIni mIni;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int userByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//��ҽ�ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��������

		_itoa(iItemCode,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_GIFTBOX_DELETE))//
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


//����������������
void CSDOITEMSET::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listUser,pNMHDR,pResult);
}

void CSDOITEMSET::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listResult,pNMHDR,pResult);
}

void CSDOITEMSET::OnLvnColumnclickListgiftbox(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&listGiftBox,pNMHDR,pResult);
}



//��ѯ���������Ϣ
void CSDOITEMSET::OnBnClickedSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;

		int index = theApp.operSDO.ReadIntValue("MSDO","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//ÿҳ��ʾ50����¼

		nItem = 0;//��������б�û��ѡ����
		pageInfo=false;
		cmbUPage.ResetContent();
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_SelectServer"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITACCOUNT,Account);//��ȡ����ʺ�//IDC_EDITACCOUNT
		GetDlgItemText(IDC_EDITNAME,Name);//��ȡ��ҽ��ǳ�//IDC_EDITNAME
		if((Account == "") && (Name == ""))//����ʺź���ҽ��ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Warn_InputAccount"),theApp.operSDO.ReadValue("MSDO","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//��ҽ�ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHARACTERINFO_QUERY))//���Ͳ�ѯ���������Ϣ������
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

//װ����ѯ
void CSDOITEMSET::EquipmentInfo()//SDO_ITEMSHOP_BYOWNER_QUERY
{
	try
	{		
		CIni mIni;

		int index = theApp.operSDO.ReadIntValue("MSDO","index");
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");

		while(listResult.DeleteColumn(0)){};
		cmbPage.ResetContent();
		pageInfo = false;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID


		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_ITEMSHOP_BYOWNER_QUERY))
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

//����в�ѯ
void CSDOITEMSET::GiftBoxInfo()
{
	try
	{		
		CIni mIni;

		int index = theApp.operSDO.ReadIntValue("MSDO","index");
		int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");

		while(listGiftBox.DeleteColumn(0)){};
		cmbPage.ResetContent();
		pageInfo = false;

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_GIFTBOX_QUERY))
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

//�л���ҳ��Ͽ�
void CSDOITEMSET::OnCbnSelchangeCmbpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//ÿҳ��ʾ50����¼

			while(listResult.DeleteColumn(0)){};
			while(listGiftBox.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(UserName));//��ҽ�ɫ��
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{
			case 2:
				{
					if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_ITEMSHOP_BYOWNER_QUERY))////װ����ѯ
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 3:
				{
					if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_GIFTBOX_QUERY))//����в�ѯ
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operSDO.ReadIntValue("MSDO","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
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
		MessageBox(theApp.operSDO.ReadValue("MSDO","UIC_Error_Page"),theApp.operSDO.ReadValue("MSDO","Error"),0);
	}
}

void CSDOITEMSET::OnCbnSelchangeCmbuipage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;

			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operSDO.ReadIntValue("MSDO","pageSize");//ÿҳ��ʾ50����¼

			while(listUser.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(Name),(unsigned char *)mIni.wcharToChar(Name));//��ҽ�ɫ��
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(Account),(unsigned char *)mIni.wcharToChar(Account));//����ʺ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHARACTERINFO_QUERY))//���Ͳ�ѯ���������Ϣ������
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

//�л�tabCtrl
void CSDOITEMSET::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 0)
	{
		cmbUPage.ResetContent();
		pageInfo = false;
		ShowUserInfo();//��ʾ�û�������Ϣ
	}
	else
	{
		
		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_Account"));//����ʺ�
			UserName = theApp.operSDO.GetValueByColName(&listUser, nItem, theApp.operSDO.ReadValue("MSDO","SDO_NickName"));//����ǳ�

			if(tbcResult.GetCurSel()==1)
			{
				ShowUpdateUser();

				SetDlgItemText(IDC_ETACCOUNT,UserAccount);
				SetDlgItemInt(IDC_ETLEVEL,iLevel);
				SetDlgItemInt(IDC_ETEXPE,iExperience);
				SetDlgItemInt(IDC_ETREPU,iReputation);
				SetDlgItemInt(IDC_ETGCASH,iGCash);
				SetDlgItemInt(IDC_ETTOTAL,iTotal);
				SetDlgItemInt(IDC_ETWIN,iWin);
				SetDlgItemInt(IDC_ETFALL,iFall);
				SetDlgItemInt(IDC_ETBALANCE,iBalance);
				SetDlgItemInt(IDC_ETMCASH,iMCash);

				SetDlgItemInt(IDC_ETSOCIAL,iSocial);
				SetDlgItemInt(IDC_ETLUCKY,iLucky);
			}
			if(tbcResult.GetCurSel() ==2)
			{
				ShowEquipment();
				EquipmentInfo();
			}
			if(tbcResult.GetCurSel() ==3)
			{
				ShowGiftBox();
				GiftBoxInfo();
			}
			if(tbcResult.GetCurSel() ==4)
			{
				ShowAddItem();
			}
		}

	}
	*pResult = 0;
}


//�޸Ľ�ɫ��Ϣ
void CSDOITEMSET::OnBnClickedBtupdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;

		iLevel=GetDlgItemInt(IDC_ETLEVEL);
		iExperience=GetDlgItemInt(IDC_ETEXPE);
		iReputation=GetDlgItemInt(IDC_ETREPU);
		iGCash=GetDlgItemInt(IDC_ETGCASH);
		iTotal=GetDlgItemInt(IDC_ETTOTAL);
		iWin=GetDlgItemInt(IDC_ETWIN);
		iFall=GetDlgItemInt(IDC_ETFALL);
		iBalance=GetDlgItemInt(IDC_ETBALANCE);
		iMCash=GetDlgItemInt(IDC_ETMCASH);
//		iSocial=GetDlgItemInt(IDC_ETSOCIAL);
//		iLucky=GetDlgItemInt(IDC_ETLUCKY);


		CSocketData socketdata;	
		socketdata.InitCreate(1,18);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int userByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iLevel,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Level,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iExperience,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Exp,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iReputation,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Reputation,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iGCash,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_GCash,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iTotal,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_GameTotal,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iWin,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_GameWin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iFall,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_GameFall,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iBalance,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_DogFall,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(iMCash,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_MCash,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

//		_itoa(iSocial,strInt,10);
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_SocialValue,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

//		_itoa(iLucky,strInt,10);
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_Lucky,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_CHARACTERINFO_UPDATE))
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

//���ý�ɫ��Ϣ
void CSDOITEMSET::OnBnClickedBtreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	tbcResult.SetCurSel(1);
	SetDlgItemText(IDC_ETACCOUNT,UserAccount);
	SetDlgItemInt(IDC_ETLEVEL,0);
	SetDlgItemInt(IDC_ETEXPE,0);
	SetDlgItemInt(IDC_ETREPU,0);
	SetDlgItemInt(IDC_ETGCASH,0);
	SetDlgItemInt(IDC_ETTOTAL,0);
	SetDlgItemInt(IDC_ETWIN,0);
	SetDlgItemInt(IDC_ETFALL,0);
	SetDlgItemInt(IDC_ETBALANCE,0);
	SetDlgItemInt(IDC_ETMCASH,iMCash);
}

//���ർ������
void CSDOITEMSET::BigTypeData()
{
	cmbBigType.ResetContent();
	cmbBigType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Dress"));
	cmbBigType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Item"));
	cmbBigType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_TaoZhuang"));
	cmbBigType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Brand"));
	cmbBigType.SetCurSel(0);
}

//�л�����
void CSDOITEMSET::OnCbnSelchangeCmbbigtype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBBIGTYPE))->GetCurSel();//��ǰѡ�е���
	CString str="";

	((CComboBox*)GetDlgItem(IDC_CMBBIGTYPE))->GetLBText(iPos,str); //����nΪ��0��ʼ������ֵ
	if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Dress"))
	{
		iType=0;
		cmbSmallType.ResetContent();
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_head"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_hair"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_body"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_leg"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_hand"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_feet"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_face"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_glass"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Wing"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_Link"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_StarFace"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_FalseFace"));
		cmbSmallType.SetCurSel(0);

//		GetDlgItem(IDC_CMBGOODS)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPE)->EnableWindow(true);
	}
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Item"))
	{
		iType=1;
		cmbSmallType.ResetContent();
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_eff"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","RE_Code_fitem"));
		cmbSmallType.SetCurSel(0);

//		GetDlgItem(IDC_CMBGOODS)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPE)->EnableWindow(true);

	}
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_TaoZhuang"))
	{
		iType=2;
		cmbSmallType.ResetContent();
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","IC_Code_taozhuang1"));
		cmbSmallType.AddString(theApp.operSDO.ReadValue("MSDO","IC_Code_present"));
		cmbSmallType.SetCurSel(0);

//		GetDlgItem(IDC_CMBGOODS)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPE)->EnableWindow(true);
	}
	else
	{
		iType=3;
		iSort=0;
//		GetDlgItem(IDC_CMBGOODS)->EnableWindow(true);
		GetDlgItem(IDC_CMBSMALLTYPE)->EnableWindow(false);
		MaleItem();////���߲�ѯ
	}
}

//�л�С��
void CSDOITEMSET::OnCbnSelchangeCmbsmalltype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPos=((CComboBox*)GetDlgItem(IDC_CMBSMALLTYPE))->GetCurSel();//��ǰѡ�е���
	CString str="";

	((CComboBox*)GetDlgItem(IDC_CMBSMALLTYPE))->GetLBText(iPos,str); //����nΪ��0��ʼ������ֵ
	if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_head"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_hair"))
		iSort=1;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_body"))
		iSort=2;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_leg"))
		iSort=3;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_hand"))
		iSort=4;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_feet"))
		iSort=5;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_face"))
		iSort=6;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_glass"))
		iSort=7;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Wing"))
		iSort=8;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_onedress"))
		iSort=50;
	else if(str==theApp.operSDO.ReadValue("MSDO","IC_Code_taozhuang1"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_Link"))
		iSort=9;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_StarFace"))
		iSort=51;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_FalseFace"))
		iSort=57;

	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_eff"))
		iSort=0;
	else if(str==theApp.operSDO.ReadValue("MSDO","RE_Code_fitem"))
		iSort=0;
	MaleItem();
}

//���߲�ѯ
void CSDOITEMSET::MaleItem()
{
	try
	{

			CIni mIni;

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];
			

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
//			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

			_itoa(iType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_BigType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

			_itoa(iSort,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_SmallType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//С��

			_itoa(iSex,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_SEX,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�Ա�

			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_ITEMSHOP_QUERY))//
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

//ģ����ѯ����
void CSDOITEMSET::OnBnClickedBtquery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{

			CIni mIni;

			CSocketData socketdata;	
			socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];
			CString ItemName="";
			GetDlgItemText(IDC_ETITEMNAME,ItemName);

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));

//			_itoa(iType,strInt,10);
//			socketdata.AddTFLV(CEnumCore::TagName::SDO_BigType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

//			_itoa(iSort,strInt,10);
//			socketdata.AddTFLV(CEnumCore::TagName::SDO_SmallType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//С��

//			_itoa(iSex,strInt,10);
//			socketdata.AddTFLV(CEnumCore::TagName::SDO_SEX,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�Ա�

			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_ITEMSHOP_QUERY))//
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

void CSDOITEMSET::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(btnDark.GetCheck()==BST_CHECKED)
	{
		GetDlgItem(IDC_ETITEMNAME)->EnableWindow(true);
		GetDlgItem(IDC_BTQUERY)->EnableWindow(true);
		GetDlgItem(IDC_LISTITEM)->EnableWindow(true);

		GetDlgItem(IDC_CMBBIGTYPE)->EnableWindow(false);
		GetDlgItem(IDC_CMBSMALLTYPE)->EnableWindow(false);
		GetDlgItem(IDC_CMBGOODS)->EnableWindow(false);
	}
	else if(btnDark.GetCheck()==BST_UNCHECKED)
	{
		GetDlgItem(IDC_ETITEMNAME)->EnableWindow(false);
		GetDlgItem(IDC_BTQUERY)->EnableWindow(false);
		GetDlgItem(IDC_LISTITEM)->EnableWindow(false);

		GetDlgItem(IDC_CMBBIGTYPE)->EnableWindow(true);
		GetDlgItem(IDC_CMBSMALLTYPE)->EnableWindow(true);
		GetDlgItem(IDC_CMBGOODS)->EnableWindow(true);
	}
}

//��ӵ���
void CSDOITEMSET::OnBnClickedBtadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{

			CIni mIni;

			CSocketData socketdata;	
			socketdata.InitCreate(1,15);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
			char strInt[10];
			CString ItemName="";
			if(btnDark.GetCheck()==BST_CHECKED)
			{
				int iPos=((CListBox*)GetDlgItem(IDC_LISTITEM))->GetCurSel();//��ǰѡ�е���
				((CListBox*)GetDlgItem(IDC_LISTITEM))->GetText(iPos,ItemName);
				//((CListBox*)GetDlgItem(IDC_LISTITEM))->GetLBText(iPos,ItemName); //����nΪ��0��ʼ������ֵ
				ItemCodeList.Lookup(listItem.GetCurSel()+1,iItemCode1);
			}
			else
			{
				GetDlgItemText(IDC_CMBGOODS,ItemName);
				ItemCodeList.Lookup(cmbGoods.GetCurSel()+1,iItemCode1);//�ҳ���Ӧ�ĵ��߱��
			}

			int iDayLimit=GetDlgItemInt(IDC_ETLIMIT);
			int iUseTimes=GetDlgItemInt(IDC_ETUSETIMES);

			CString Subject="";
			CString Content="";
			GetDlgItemText(IDC_ETSUBJECT,Subject);
			GetDlgItemText(IDC_ETCONTENT,Content);

			

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));
			
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Title,CEnumCore::TagFormat::TLV_STRING,strlen(Subject),(unsigned char *)mIni.wcharToChar(Subject));
			socketdata.AddTFLV(CEnumCore::TagName::SDO_Context,CEnumCore::TagFormat::TLV_STRING,strlen(Content),(unsigned char *)mIni.wcharToChar(Content));

			_itoa(iItemCode1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_ItemCode,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���߱��

			_itoa(iDayLimit,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_DateLimit,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʹ������

			_itoa(iUseTimes,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_TimesLimit,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ʹ�ô���

			int userByID=theApp.UserByID;
			_itoa(userByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(UserID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

			int midlength = socketdata.EnBody();
			if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_GIFTBOX_CREATE))//
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

// ���շ�����Ϣ
LRESULT CSDOITEMSET::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_QUERY_RESP:
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageInfo = false;//���ܷ�ҳ		
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
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_BYOWNER_QUERY_RESP://װ��
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	case CEnumCore::Message_Tag_ID::SDO_GIFTBOX_QUERY_RESP://���
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listGiftBox,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operSDO.BuildDataTable(&socketdata,&listGiftBox,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					pageInfo = false;//���ܷ�ҳ		
					cmbPage.ResetContent();
					while(listGiftBox.DeleteColumn(0)){}
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
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_QUERY_RESP://���߲�ѯ
		{

			if(!ItemCodeList.IsEmpty())
			{
				ItemCodeList.RemoveAll();
			}
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int nItem = StrToInt((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::SDO_ItemCode).lpdata);//�õ�������IP
				ItemCodeList.SetAt(i,nItem);//
			}

			if(btnDark.GetCheck()==BST_CHECKED)
			{

				CGlobalStruct::TFLV m_tContent;
				listItem.ResetContent();
				for(int i=1;i<=socketdata.getQueryNum();i++)
				{
					m_tContent = socketdata.getTLVByName(i,CEnumCore::TagName::SDO_ItemName);
					listItem.AddString((LPCTSTR)&m_tContent.lpdata);
				}

			}
			else
			{

				theApp.operSDO.BuildComboxs(&socketdata,&cmbGoods);
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::SDO_CHARACTERINFO_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_GIFTBOX_CREATE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_GIFTBOX_DELETE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_ITEMSHOP_DELETE_RESP:
	case CEnumCore::Message_Tag_ID::SDO_Social_Update_Resp:
	case CEnumCore::Message_Tag_ID::SDO_Lucky_Update_Resp:
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


//�޸��罻ֵ
void CSDOITEMSET::OnBnClickedBtnsocial()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;


		iSocial=GetDlgItemInt(IDC_ETSOCIAL);
	//	iLucky=GetDlgItemInt(IDC_ETLUCKY);


		CSocketData socketdata;	
		socketdata.InitCreate(1,18);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int userByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

	
		_itoa(iSocial,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_SocialValue,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

//		_itoa(iLucky,strInt,10);
//		socketdata.AddTFLV(CEnumCore::TagName::SDO_Lucky,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_Social_Update))
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

//�޸�����ֵ
void CSDOITEMSET::OnBnClickedBtnlucky()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;

		iLucky=GetDlgItemInt(IDC_ETLUCKY);


		CSocketData socketdata;	
		socketdata.InitCreate(1,18);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		int userByID=theApp.UserByID;

		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::SDO_NickName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

	
		_itoa(iLucky,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Lucky,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//

		int midlength = socketdata.EnBody();
		if(theApp.operSDO.SendLogQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::SDO_Lucky_Update))
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
