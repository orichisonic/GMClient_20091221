// PALPuzzleMapManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALPuzzleMapManage.h"
#include ".\PALPuzzleMapManage.h"


// CPALPuzzleMapManage �Ի���

IMPLEMENT_DYNAMIC(CPALPuzzleMapManage, CDialog)
CPALPuzzleMapManage::CPALPuzzleMapManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPALPuzzleMapManage::IDD, pParent)
{
}

CPALPuzzleMapManage::~CPALPuzzleMapManage()
{
}

void CPALPuzzleMapManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CB1, m_CB1);
	DDX_Control(pDX, IDC_CB2, m_CB2);
	DDX_Control(pDX, IDC_CB6, m_CB6);
	DDX_Control(pDX, IDC_CB9, m_CB9);
	DDX_Control(pDX, IDC_CB4, m_CB4);
	DDX_Control(pDX, IDC_CB3, m_CB3);
	DDX_Control(pDX, IDC_CB5, m_CB5);
	DDX_Control(pDX, IDC_CB7, m_CB7);
	DDX_Control(pDX, IDC_CB8, m_CB8);
}


BEGIN_MESSAGE_MAP(CPALPuzzleMapManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
	ON_BN_CLICKED(IDC_BTN1, OnBnClickedBtn1)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_BN_CLICKED(IDC_BTN2, OnBnClickedBtn2)
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CPALPuzzleMapManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�

	nItem = 0;
	nListItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//��ʼ��һЩ˽�б���

	ShowUserInfo();//��ʾ�û�������Ϣ

	SetProp(listUser.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listUser.GetSafeHwnd(),"����˳��",(HANDLE)1);

	SetProp(listResult.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listResult.GetSafeHwnd(),"����˳��",(HANDLE)1);

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
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operPAL.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CPALPuzzleMapManage::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","IM_UI_ITEMMANAGE"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));
	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLBAGTYPE,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblBAGTYPE"));

	SetDlgItemText(IDC_LBL0,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP"));
	SetDlgItemText(IDC_LBL1,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP1"));
	SetDlgItemText(IDC_LBL2,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP2"));
	SetDlgItemText(IDC_LBL3,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP3"));
	SetDlgItemText(IDC_LBL4,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP4"));
	SetDlgItemText(IDC_LBL5,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP5"));
	SetDlgItemText(IDC_LBL6,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP6"));
	SetDlgItemText(IDC_LBL7,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP7"));
	SetDlgItemText(IDC_LBL8,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP8"));
	SetDlgItemText(IDC_LBL9,theApp.operPAL.ReadValue("MPAL","UIC_UI_PUZZLEMAP9"));

	SetDlgItemText(IDC_BTN1,theApp.operPAL.ReadValue("MPAL","MakeSure"));
	SetDlgItemText(IDC_BTN2,theApp.operPAL.ReadValue("MPAL","Close"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","PMI_UI_tpgPuzzleMapInfo"));
	tbcResult.InsertItem(2,theApp.operPAL.ReadValue("MPAL","MPM_UI_tpgModifyPuzzleMap"));
	
}

//�����ݼ���Ӧ����
BOOL CPALPuzzleMapManage::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operPAL;
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listUser);				
				}
				else if(pMsg->hwnd == listResult.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listResult);
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
void CPALPuzzleMapManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CPALPuzzleMapManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CPALPuzzleMapManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;

		ShowUserInfo();

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//ÿҳ��ʾ50����¼

		nItem = 0;//��������б�û��ѡ����
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		UpdateData(true);			

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_SelectServer"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITACCOUNT,UserAccount);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITNAME,UserName);//��ȡ��ҽ�ɫ��
		if((UserName == "") && (UserAccount == ""))//����ʺź���ҽ�ɫ������ͬʱΪ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_InputAccount"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
	    
		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//��ҽ�ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERINFO))//���Ͳ�ѯ���������Ϣ������
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

// �����û��б��浱ǰ�к�
void CPALPuzzleMapManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// ˫�����������Ϣ���в�ѯ
void CPALPuzzleMapManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			if(nItem >= 0)
			{
				ShowBagType();				

				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������

				//OperationPAL operPAL;
				UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// ����ѡ�е�����ʺ�
			    UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��

				PuzzleMap();// ��ѯ��ұ�����Ϣ
			}
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// �л�ѡ����в�ѯ
void CPALPuzzleMapManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch(tbcResult.GetCurSel())
	{
	case 0:
			ShowUserInfo();//��ʾ�û�������Ϣ
		break;
	case 1:

		ShowBagType();
		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			//OperationPAL operPAL;
			UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// ����ѡ�е�����ʺ�
			UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��
			PuzzleMap();//��ѯ��ұ�����Ϣ
		}			
		break;
	case 2:
		ShowModifyPuzzleMap();
		if((listResult.GetItemCount() > 0) && (nListItem >= 0))
		{
			InitComBox();
			strPuzzleMap = theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMap"));
			iPuzzleMapID[0]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID1")));
			iPuzzleMapID[1]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID2")));
			iPuzzleMapID[2]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID3")));
			iPuzzleMapID[3]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID4")));
			iPuzzleMapID[4]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID5")));
			iPuzzleMapID[5]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID6")));
			iPuzzleMapID[6]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID7")));
			iPuzzleMapID[7]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID8")));
			iPuzzleMapID[8]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID9")));

			SetDlgItemText(IDC_PUZZLEMAP,strPuzzleMap);
			m_CB1.SetCurSel(iPuzzleMapID[0]);
			m_CB2.SetCurSel(iPuzzleMapID[1]);
			m_CB3.SetCurSel(iPuzzleMapID[2]);
			m_CB4.SetCurSel(iPuzzleMapID[3]);
			m_CB5.SetCurSel(iPuzzleMapID[4]);
			m_CB6.SetCurSel(iPuzzleMapID[5]);
			m_CB7.SetCurSel(iPuzzleMapID[6]);
			m_CB8.SetCurSel(iPuzzleMapID[7]);
			m_CB9.SetCurSel(iPuzzleMapID[8]);

		}		
		break;
	}
	*pResult = 0;
}
//��ѯ���ͼ��
void CPALPuzzleMapManage::PuzzleMap()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,7);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERPUZZLEMAP))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_BagInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CPALPuzzleMapManage::OnCbnSelchangeCmbpage()
{
	//OperationPAL operPAL;
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;
		
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//ÿҳ��ʾ50����¼

			int midlength = 0;
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			
			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					_itoa(0,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
					midlength=socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERPUZZLEMAP))//���Ͳ�ѯ���������Ϣ������
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			}			
			socketdata.Destroy();//����CSocketData�ֲ�����
		}
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_Page"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

// ˫��������Ϣ����ɾ��
void CPALPuzzleMapManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
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

			nListItem = listResult.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if((listResult.GetItemCount() > 0) && (nListItem >= 0))
			{
				ShowModifyPuzzleMap();
				InitComBox();
				strPuzzleMap = theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMap"));
				iPuzzleMapID[0]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID1")));
				iPuzzleMapID[1]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID2")));
				iPuzzleMapID[2]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID3")));
				iPuzzleMapID[3]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID4")));
				iPuzzleMapID[4]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID5")));
				iPuzzleMapID[5]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID6")));
				iPuzzleMapID[6]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID7")));
				iPuzzleMapID[7]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID8")));
				iPuzzleMapID[8]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID9")));

				SetDlgItemText(IDC_PUZZLEMAP,strPuzzleMap);
				m_CB1.SetCurSel(iPuzzleMapID[0]);
				m_CB2.SetCurSel(iPuzzleMapID[1]);
				m_CB3.SetCurSel(iPuzzleMapID[2]);
				m_CB4.SetCurSel(iPuzzleMapID[3]);
				m_CB5.SetCurSel(iPuzzleMapID[4]);
				m_CB6.SetCurSel(iPuzzleMapID[5]);
				m_CB7.SetCurSel(iPuzzleMapID[6]);
				m_CB8.SetCurSel(iPuzzleMapID[7]);
				m_CB9.SetCurSel(iPuzzleMapID[8]);

			}	
		}
		else
		{
	    	nListItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// ���շ�����Ϣ
LRESULT CPALPuzzleMapManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;
	//OperationPAL operPAL;	

	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(theApp.operPAL.ReadValue("MPAL","Main_UI_ParseData"),theApp.operPAL.ReadValue("MPAL","ERROR"),0);		
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
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operPAL.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ITEMTYPE_QUERY_RESP://��ѯ���������Ϣ�Ļ�Ӧ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int ItemTypeID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_ITEMBIGTYPEID).lpdata);//�õ��������ID
				BigTypeList.SetAt(i,ItemTypeID);//���������ID������CMap��Ķ���BigTypeList��
			}

			theApp.operPAL.BuildComboxs(&socketdata,&cmbType);//�����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_ITEMNAME_QUERY_RESP://��ѯ����������Ϣ�Ļ�Ӧ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				int ItemNameID = atoi((LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::PAL_ITEMID).lpdata);//�õ����߱��
				GiftList.SetAt(i,ItemNameID);//�����߱�ű�����CMap��Ķ���GiftList��
			}

			theApp.operPAL.BuildComboxs(&socketdata,&cmbName);//������������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://��ѯ���������Ϣ�Ļ�Ӧ
		{
			theApp.operPAL.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERPUZZLEMAP_RESP://��ѯ��ұ����Ļ�Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	case CEnumCore::Message_Tag_ID::PAL_MODIFYPUZZLEMAP_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��
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

//�����û�������Ϣ��������������
void CPALPuzzleMapManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CPALPuzzleMapManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CPALPuzzleMapManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// �رնԻ���
void CPALPuzzleMapManage::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// ��ʾ��ɫ������Ϣ
void CPALPuzzleMapManage::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_LBL0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PUZZLEMAP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN2)->ShowWindow(SW_HIDE);
}

// ��ʾ������Ϣ
void CPALPuzzleMapManage::ShowBagType(void)
{
	tbcResult.SetCurSel(1);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);


	GetDlgItem(IDC_LBL0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBL9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PUZZLEMAP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CB9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN2)->ShowWindow(SW_HIDE);
}

// ��ʾ�޸�ͼ��
void CPALPuzzleMapManage::ShowModifyPuzzleMap(void)
{
	tbcResult.SetCurSel(2);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);


	GetDlgItem(IDC_LBL0)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL9)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_PUZZLEMAP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CB9)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN2)->ShowWindow(SW_SHOW);

}


void CPALPuzzleMapManage::OnBnClickedBtn1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,30);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		CString PuzzleMap;
		GetDlgItemText(IDC_PUZZLEMAP,PuzzleMap);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMap,CEnumCore::TagFormat::TLV_STRING,strlen(PuzzleMap),(unsigned char *)mIni.wcharToChar(PuzzleMap));//����ʺ�

		_itoa(m_CB1.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID1,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(m_CB2.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID2,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(m_CB3.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID3,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(m_CB4.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID4,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(m_CB5.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID5,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(m_CB6.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID6,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(m_CB7.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID7,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(m_CB8.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID8,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(m_CB9.GetCurSel(),strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_PuzzleMapID9,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYPUZZLEMAP))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_BagInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	

}

void CPALPuzzleMapManage::InitComBox(void)
{
	m_CB1.ResetContent();
	m_CB2.ResetContent();
	m_CB3.ResetContent();
	m_CB4.ResetContent();
	m_CB5.ResetContent();
	m_CB6.ResetContent();
	m_CB7.ResetContent();
	m_CB8.ResetContent();
	m_CB9.ResetContent();

	m_CB1.AddString("��");
	m_CB1.AddString("��");
	m_CB1.SetCurSel(0);
	m_CB2.AddString("��");
	m_CB2.AddString("��");
	m_CB2.SetCurSel(0);
	m_CB3.AddString("��");
	m_CB3.AddString("��");
	m_CB3.SetCurSel(0);
	m_CB4.AddString("��");
	m_CB4.AddString("��");
	m_CB4.SetCurSel(0);
	m_CB5.AddString("��");
	m_CB5.AddString("��");
	m_CB5.SetCurSel(0);
	m_CB6.AddString("��");
	m_CB6.AddString("��");
	m_CB6.SetCurSel(0);
	m_CB7.AddString("��");
	m_CB7.AddString("��");
	m_CB7.SetCurSel(0);
	m_CB8.AddString("��");
	m_CB8.AddString("��");
	m_CB8.SetCurSel(0);
	m_CB9.AddString("��");
	m_CB9.AddString("��");
	m_CB9.SetCurSel(0);

}




void CPALPuzzleMapManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(tbcResult.GetCurSel() == 1)
	{
		if(listResult.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nListItem = listUser.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�
		}
		else
		{
			nListItem = 0;
		}
	}
	*pResult = 0;
}

void CPALPuzzleMapManage::OnBnClickedBtn2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitComBox();
	strPuzzleMap = theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMap"));
	iPuzzleMapID[0]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID1")));
	iPuzzleMapID[1]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID2")));
	iPuzzleMapID[2]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID3")));
	iPuzzleMapID[3]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID4")));
	iPuzzleMapID[4]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID5")));
	iPuzzleMapID[5]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID6")));
	iPuzzleMapID[6]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID7")));
	iPuzzleMapID[7]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID8")));
	iPuzzleMapID[8]=atoi(theApp.operPAL.GetValueByColName(&listResult, nListItem, theApp.operPAL.ReadValue("MPAL","PAL_PuzzleMapID9")));

	SetDlgItemText(IDC_PUZZLEMAP,strPuzzleMap);
	m_CB1.SetCurSel(iPuzzleMapID[0]);
	m_CB2.SetCurSel(iPuzzleMapID[1]);
	m_CB3.SetCurSel(iPuzzleMapID[2]);
	m_CB4.SetCurSel(iPuzzleMapID[3]);
	m_CB5.SetCurSel(iPuzzleMapID[4]);
	m_CB6.SetCurSel(iPuzzleMapID[5]);
	m_CB7.SetCurSel(iPuzzleMapID[6]);
	m_CB8.SetCurSel(iPuzzleMapID[7]);
	m_CB9.SetCurSel(iPuzzleMapID[8]);
}
