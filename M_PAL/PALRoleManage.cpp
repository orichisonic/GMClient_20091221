// PALRoleManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALRoleManage.h"
#include ".\palrolemanage.h"


// CPALRoleManage �Ի���

IMPLEMENT_DYNAMIC(CPALRoleManage, CDialog)
CPALRoleManage::CPALRoleManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPALRoleManage::IDD, pParent)
{
}

CPALRoleManage::~CPALRoleManage()
{
}

void CPALRoleManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
	DDX_Control(pDX, IDC_EDITSRC, txtSrc);
	DDX_Control(pDX, IDC_EDITNEW, txtNew);
	DDX_Control(pDX, IDC_CMBQUESTSTATUS, cmbStatus);
	DDX_Control(pDX, IDC_CMBSTATUS, cmbNewStatus);
}


BEGIN_MESSAGE_MAP(CPALRoleManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_BN_CLICKED(IDC_BTNMODIQUEST, OnBnClickedBtnmodiquest)
	ON_BN_CLICKED(IDC_BTNMODI, OnBnClickedBtnmodi)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBQUESTSTATUS, OnCbnSelchangeCmbqueststatus)
	ON_CBN_SELCHANGE(IDC_CMBTYPE, OnCbnSelchangeCmbtype)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CPALRoleManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�

	nItem = 0;
	pageInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserName = "";//��ʼ��һЩ˽�б���
	QuestNum = 0;
	iQuestType = 0;

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
	//OperationPAL operPAL;
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operPAL.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CPALRoleManage::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","RM_UI_RoleManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLACCOUNT,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDC_LBLQUESTSTATUS,theApp.operPAL.ReadValue("MPAL","RM_UI_QuestStatus"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Close"));

	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));
	SetDlgItemText(IDC_LBLQUESTNAME,theApp.operPAL.ReadValue("MPAL","RM_UI_QuestName"));
	SetDlgItemText(IDC_LBLSTATUS,theApp.operPAL.ReadValue("MPAL","RM_UI_QuestStatus"));
	SetDlgItemText(IDC_BTNMODIQUEST,theApp.operPAL.ReadValue("MPAL","RM_UI_BtnModiQuest"));

	SetDlgItemText(IDC_LBLROLENAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","Modify"));
	SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","Reset"));

	SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_PwdType"));
	SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_TmpPwd"));
	SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_ReTmpPwd"));
	SetDlgItemText(IDC_LBLHINT,"");

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","RM_UI_tpgModiTmpPwd"));
	tbcResult.InsertItem(2,theApp.operPAL.ReadValue("MPAL","RM_UI_tpgModiMoney"));
	tbcResult.InsertItem(3,theApp.operPAL.ReadValue("MPAL","RM_UI_tpgModiQuest"));
	tbcResult.InsertItem(4,theApp.operPAL.ReadValue("MPAL","RM_UI_tpgSafeLock"));


}

//�����ݼ���Ӧ����
BOOL CPALRoleManage::PreTranslateMessage(MSG* pMsg)
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
void CPALRoleManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CPALRoleManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CPALRoleManage::OnBnClickedSearch()
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
		socketdata.InitCreate(1,6);//�������������������IP��������Name������ʺš���ҽ�ɫ����ҳ����ÿҳ�ļ�¼����
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
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

// �����û��б��浱ǰ�к�
void CPALRoleManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
void CPALRoleManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
				//OperationPAL operPAL;
				tbcResult.SetCurSel(1);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);

				InitPwdType();//��ʼ��Ҫ�޸ĵ���������
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_PwdType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_TmpPwd"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_ReTmpPwd"));
				SetDlgItemText(IDC_LBLHINT,"");

				UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// ����ѡ�е�����ʺ�
				UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��

				SetDlgItemText(IDC_EDITROLENAME,UserName);//��ʾ��ҽ�ɫ��

				if (cmbType.GetCurSel() == 0)
				{
					GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_SHOWNORMAL);
				}

			}
			else
			{
				nItem = 0;
			}
		}
		else
		{
			nItem = 0;
		}
	}
	*pResult = 0;
}

// �л�ѡ����в���
void CPALRoleManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operPAL;
	GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);

	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//��ʾ�û�������Ϣ
	}
	else
	{
		nQuestItem = -1;
		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// ����ѡ�е�����ʺ�
			UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��

			if(tbcResult.GetCurSel()==1)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);

				InitPwdType();//��ʼ��Ҫ�޸ĵ���������
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_PwdType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_TmpPwd"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_ReTmpPwd"));
				SetDlgItemText(IDC_LBLHINT,"");

				SetDlgItemText(IDC_EDITROLENAME,UserName);//��ʾ��ҽ�ɫ��
				if (cmbType.GetCurSel() == 0)
				{
					GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_SHOWNORMAL);
				}

			}
			else if(tbcResult.GetCurSel()==2)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);				
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);
				GetDlgItem(IDC_LBLHINT)->ShowWindow(SW_HIDE);	
				
				InitMoneyType();//��ʼ����Ǯ���͸�ѡ��
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_MoneyType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_OwnMoney"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_NewMoney"));
				CString srcMoney;
				srcMoney = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_BODYMONEY"));// ����������ϵ���Ǯ��

				SetDlgItemText(IDC_EDITROLENAME,UserName);//��ʾ��ҽ�ɫ��
				SetDlgItemText(IDC_EDITSMONEY,srcMoney);//��ʾ���ӵ�еĽ�Ǯ��
			}
			else if(tbcResult.GetCurSel()==3)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_HIDE);
				ShowQuestTab(SW_SHOW,2);

				InitQuestType();//��ʼ����������
				QuestInfo();//��ѯ���������Ϣ
			}
			else if(tbcResult.GetCurSel()==4)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_HIDE);
				ShowQuestTab(SW_HIDE,1);

				GetDlgItem(IDC_EDITROLENAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLROLENAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNMODI)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);
				
				SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","RM_UI_USESAFTLOCK"));
				SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RM_UI_FREESAFTLOCK"));


				SetDlgItemText(IDC_EDITROLENAME,UserName);//��ʾ��ҽ�ɫ��
			}

		}
		else
		{
			if(tbcResult.GetCurSel()==1)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);

				InitPwdType();//��ʼ��Ҫ�޸ĵ���������
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_PwdType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_TmpPwd"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_ReTmpPwd"));
				SetDlgItemText(IDC_LBLHINT,"");
	            //SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","RM_UI_HintDeleteRolePwd"));
				SetDlgItemText(IDC_EDITROLENAME,"");//��ʾ��ҽ�ɫ��Ϊ��
			}
			else if(tbcResult.GetCurSel()==2)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);				
				ShowOperTab(SW_SHOW);
				ShowQuestTab(SW_HIDE,1);
				GetDlgItem(IDC_LBLHINT)->ShowWindow(SW_HIDE);	
				
				InitMoneyType();//��ʼ����Ǯ���͸�ѡ��
				SetDlgItemText(IDC_LBLTYPE,theApp.operPAL.ReadValue("MPAL","RM_UI_MoneyType"));
	            SetDlgItemText(IDC_LBLSRC,theApp.operPAL.ReadValue("MPAL","RM_UI_OwnMoney"));
	            SetDlgItemText(IDC_LBLNEW,theApp.operPAL.ReadValue("MPAL","RM_UI_NewMoney"));
				SetDlgItemText(IDC_EDITROLENAME,"");//��ʾ��ҽ�ɫ��Ϊ��
				SetDlgItemText(IDC_EDITSMONEY,"");//��ʾ���ӵ�еĽ�Ǯ��
			}
			else if(tbcResult.GetCurSel()==3)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_HIDE);
				ShowQuestTab(SW_SHOW,2);

				InitQuestType();//��ʼ����������
				SetDlgItemText(IDC_EDITROLENAME,"");//��ʾ��ҽ�ɫ��Ϊ��
			}
			else if(tbcResult.GetCurSel()==4)
			{
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
				ShowOperTab(SW_HIDE);
				ShowQuestTab(SW_HIDE,1);

				GetDlgItem(IDC_EDITROLENAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLROLENAME)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNMODI)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTNRESET)->ShowWindow(SW_SHOW);
				
				SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","RM_UI_USESAFTLOCK"));
				SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RM_UI_FREESAFTLOCK"));
				

				SetDlgItemText(IDC_EDITROLENAME,"");//��ʾ��ҽ�ɫ��Ϊ��
			}
		}
	}
	*pResult = 0;
}

//�л���ͬ����
void CPALRoleManage::OnCbnSelchangeCmbtype()
{
	//OperationPAL operPAL;
	if(tbcResult.GetCurSel() == 1)
	{
		if(cmbType.GetCurSel() == 0)
		{
			 SetDlgItemText(IDC_LBLHINT,"");
			 GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_SHOWNORMAL);
		}
		else if(cmbType.GetCurSel() == 1)
		{
	        SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","RM_UI_HintDeleteRolePwd"));
			GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);
		}
		else if(cmbType.GetCurSel() == 2)
		{
			SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","RM_UI_HintBanPwd"));
			GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);
		}
		if(cmbType.GetCurSel() == 3)
		{
			 SetDlgItemText(IDC_LBLHINT,"");
			 GetDlgItem(IDC_CHEAK_CITYALL)->ShowWindow(SW_HIDE);
		}
	}
	else if(tbcResult.GetCurSel() == 2)
	{
		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			CString srcMoney;				
		    if(cmbType.GetCurSel() == 0)
		    {
				srcMoney = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_BODYMONEY"));// ����������ϵ���Ǯ��
		    }
		    else if(cmbType.GetCurSel() == 1)
		    {
				srcMoney = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_BANKMONEY"));// ������Ҳֿ����Ǯ��
	    	}
			SetDlgItemText(IDC_EDITSMONEY,srcMoney);//��ʾ���ӵ�еĽ�Ǯ��
		}
		else
		{
			SetDlgItemText(IDC_EDITSMONEY,"");//��ʾ���ӵ�еĽ�Ǯ��
		}
	}
}

//��ѯ���������Ϣ
void CPALRoleManage::QuestInfo()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		int iQuestType;		
		CString QuestType = "";
		GetDlgItemText(IDC_CMBQUESTSTATUS,QuestType);
		if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished")))
		{
			iQuestType = 1;
		}
		else if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received")))
		{
			iQuestType = 2;
		}
		else
		{
			iQuestType = 0;
			return;
		}

		nQuestItem = -1;
		pageInfo=false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){};

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//��������������������IP��������Name������ǳơ������������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(iQuestType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERQUEST))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_QuestInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}		
}

//�л��������Ͳ�ѯ���������Ϣ
void CPALRoleManage::OnCbnSelchangeCmbqueststatus()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{			
			CString QuestType = "";
			GetDlgItemText(IDC_CMBQUESTSTATUS,QuestType);
			if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished")))
			{
				iQuestType = 1;
			}
			else if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received")))
			{
				iQuestType = 2;
			}
			else
			{
				iQuestType = 0;
				return;
			}

			nQuestItem = -1;
			pageInfo=false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){};

			CSocketData socketdata;	
			socketdata.InitCreate(1,10);//��������������������IP��������Name������ǳơ������������,ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(iQuestType,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


			int midlength = socketdata.EnBody();
			if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERQUEST))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_QuestInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}		
}

// ��ҳ���в�ѯ
void CPALRoleManage::OnCbnSelchangeCmbpage()
{
	//OperationPAL operPAL;
	try
	{	
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;
		
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//ÿҳ��ʾ50����¼
			
			nQuestItem = -1;
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
			case 3:
				{
					CString QuestType = "";
					GetDlgItemText(IDC_CMBQUESTSTATUS,QuestType);
					if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished")))
					{
						iQuestType = 1;
					}
					else if(!strcmp(QuestType,theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received")))
					{
						iQuestType = 2;
					}
					else
					{
						iQuestType = 0;
						return;
					}
					_itoa(iQuestType,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
					midlength=socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERQUEST))//���Ͳ�ѯ���������Ϣ������
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

//˫�������б�����޸�
void CPALRoleManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 3)
	{
		if(listResult.GetItemCount() != 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listResult.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nQuestItem = listResult.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if(nQuestItem >= 0)
			{
				CIni mIni;
				//OperationPAL operPAL;
				QuestNum = atoi(theApp.operPAL.GetValueByColName(&listResult, nQuestItem, theApp.operPAL.ReadValue("MPAL","PAL_QUESTID")));// ����ѡ�е������

				SetDlgItemText(IDC_EDITQUESTNAME,(LPCSTR)mIni.wcharToChar(theApp.operPAL.GetValueByColName(&listResult, nQuestItem, theApp.operPAL.ReadValue("MPAL","PAL_QUESTID"))));//��ʾ�����
				InitQuestStatus();
				ShowQuestTab(SW_SHOW,1);				
			}
			else
			{
				SetDlgItemText(IDC_EDITQUESTNAME,"");//�����Ϊ��
				InitQuestType();
				ShowQuestTab(SW_SHOW,2);	
				nQuestItem = -1;
			}
		}
		else
		{
			SetDlgItemText(IDC_EDITQUESTNAME,"");//��������Ϊ��
			InitQuestType();
			ShowQuestTab(SW_SHOW,2);	
			nQuestItem = -1;
		}
	}
	*pResult = 0;
}

//�޸���������
void CPALRoleManage::OnBnClickedBtnmodiquest()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		CString QuestName = "";
		GetDlgItemText(IDC_EDITQUESTNAME,QuestName);
		if(QuestName == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_SelectQuest"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int iQuestStatus = 0;	
		CString QuestType = "";
		GetDlgItemText(IDC_CMBSTATUS,QuestType);
		if(QuestType == theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished"))
		{
			iQuestStatus = 1;
		}
		else if(QuestType == theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received"))
		{
			iQuestStatus = 2;
		}
		else
		{
			iQuestStatus = 0;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ��������ID�������������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(QuestNum,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�������ID

		_itoa(iQuestStatus,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_QUESTTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�����������

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYCHARACTERQUEST))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Error_ModiQuestType"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

//�޸�������Ǯ��Ϣ
void CPALRoleManage::OnBnClickedBtnmodi()
{
	//OperationPAL operPAL;
	try
	{				
		CIni mIni;

		GetDlgItemText(IDC_EDITROLENAME,UserName);//��ȡ��ɫ��
		if(UserName == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_RoleNameNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString strNewPwd,strReNewPwd;
		CString sMoney,nMoney;
		int iCount = 0;
		int iType=0;
		if(tbcResult.GetCurSel() == 1)
		{
		    GetDlgItemText(IDC_EDITSRC,strNewPwd);
		    GetDlgItemText(IDC_EDITNEW,strReNewPwd);
		    if(strcmp(strNewPwd,strReNewPwd))
		    {
			    MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_PwdSame"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			    return;
	    	}
		}
		else if(tbcResult.GetCurSel() == 2)
		{
			iType = cmbType.GetCurSel();
			GetDlgItemText(IDC_EDITSMONEY,sMoney);
		    GetDlgItemText(IDC_EDITNMONEY,nMoney);
		    
		    if(nMoney == "")
		    {
			    MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_InputNewMoney"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			    return;
	    	}
			if(sMoney == "")
			{
				iCount=GetDlgItemInt(IDC_EDITNMONEY)-0;
			}
			else
			{
			    iCount=GetDlgItemInt(IDC_EDITNMONEY)-GetDlgItemInt(IDC_EDITSMONEY);
			}
		}


		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP��������Name,�������ơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];
		int midlength = 0;

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
        socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		switch(tbcResult.GetCurSel())
		{
		case 1:
			{
				if(cmbType.GetCurSel() == 0)
				{
					socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNTPW,CEnumCore::TagFormat::TLV_STRING,strlen(strNewPwd),(unsigned char *)mIni.wcharToChar(strNewPwd));

					int selectStatus = ((CButton*)GetDlgItem(IDC_CHEAK_CITYALL))->GetCheck();
					if (selectStatus == 1)
					{
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYACCOUNTPWALL))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
						}						
					}
					else
					{						
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYACCOUNTPW))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
						}
					}

				}
				else if(cmbType.GetCurSel() == 1)
				{
					socketdata.AddTFLV(CEnumCore::TagName::PAL_DROPROLEPW,CEnumCore::TagFormat::TLV_STRING,strlen(strNewPwd),(unsigned char *)mIni.wcharToChar(strNewPwd));
					midlength = socketdata.EnBody();
		            if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYCHARACTERDROPPW))
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				else if(cmbType.GetCurSel() == 2)
				{
					socketdata.AddTFLV(CEnumCore::TagName::PAL_BANKPW,CEnumCore::TagFormat::TLV_STRING,strlen(strNewPwd),(unsigned char *)mIni.wcharToChar(strNewPwd));
					midlength = socketdata.EnBody();
		            if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYACCOUNTBANKPW))
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				else if(cmbType.GetCurSel() == 3)
				{
					socketdata.AddTFLV(CEnumCore::TagName::PAL_SECONDPW,CEnumCore::TagFormat::TLV_STRING,strlen(strNewPwd),(unsigned char *)mIni.wcharToChar(strNewPwd));
					midlength = socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYSECONDPW))
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}

			}
			break;
		case 2:
			{
				_itoa(iType,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PAL_MONEYTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

				_itoa(iCount,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PAL_MONEYCOUNT,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYCHARACTERMONEY))
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		case 4:
			{
				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_USESAFELOCK))
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_UserInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

//������Ϣ
void CPALRoleManage::OnBnClickedBtnreset()
{	
	SetDlgItemText(IDC_EDITSRC,"");
	SetDlgItemText(IDC_EDITNEW,"");

	char strInt[10];
	if(tbcResult.GetCurSel() == 1||tbcResult.GetCurSel()==4)
	{
		//OperationPAL operPAL;
		try
		{				
			CIni mIni;

			GetDlgItemText(IDC_EDITROLENAME,UserName);//��ȡ��ɫ��
			if(UserName == "")
			{
				MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_RoleNameNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP��������Name,�������ơ�ҳ����ÿҳ�ļ�¼����
			int midlength = 0;

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

			_itoa(theApp.UserByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

			switch(tbcResult.GetCurSel())
			{
			case 1:
				{
					if(cmbType.GetCurSel() == 0)
					{
						int selectStatus = ((CButton*)GetDlgItem(IDC_CHEAK_CITYALL))->GetCheck();
						if (selectStatus == 1)
						{
							midlength = socketdata.EnBody();
							if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLACCOUNTPWALL))
							{
								::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
								dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
							}
						}
						else
						{
							midlength = socketdata.EnBody();
							if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLACCOUNTPW))
							{
								::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
								dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
							}
						}
					}
					else if(cmbType.GetCurSel() == 1)
					{
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLCHARACTERDROPPW))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
						}
					}
					else if(cmbType.GetCurSel() == 2)
					{
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLACCOUNTBANKPW))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
						}
					}
					else if(cmbType.GetCurSel() == 3)
					{
						midlength = socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_RECALLSECONDPW))
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
						}
					}
				}
				break;
			case 4:
				{	
					midlength = socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_FREESAFELOCK))
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}

				}
				break;
			}
			socketdata.Destroy();
		}
		catch(...)
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_UserInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
		}
	}
}

// ���շ�����Ϣ
LRESULT CPALRoleManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERINFO_RESP://��ѯ���������Ϣ�Ļ�Ӧ
		{
			theApp.operPAL.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERQUEST_RESP://��ѯ��������Ӧ
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
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTPW_RESP://�޸Ľ�ɫ��Ϸ����Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTPW_RESP://�ָ���ɫ��Ϸ����Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERDROPPW_RESP://�޸Ľ�ɫɾ������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLCHARACTERDROPPW_RESP://�ָ���ɫɾ������Ļ�Ӧ	
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTBANKPW_RESP://�޸Ľ�ɫ��������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTBANKPW_RESP://�ָ���ɫ��������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERMONEY_RESP://�޸Ľ�ɫ��Ǯ�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYCHARACTERQUEST_RESP://�޸Ľ�ɫ����״̬�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYSECONDPW_RESP://�޸Ķ�������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_RECALLSECONDPW_RESP://�ָ���������Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::PAL_USESAFELOCK_RESP://ʹ�ð�ȫ��
	case CEnumCore::Message_Tag_ID::PAL_FREESAFELOCK_RESP://�ͷŰ�ȫ����Ӧ
	case CEnumCore::Message_Tag_ID::PAL_MODIFYACCOUNTPWALL_RESP://�޸�ȫ����ʱ����
	case CEnumCore::Message_Tag_ID::PAL_RECALLACCOUNTPWALL_RESP://�޸�ȫ����ʱ����
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��

			SetDlgItemText(IDC_EDITSRC,"");
			SetDlgItemText(IDC_EDITNEW,"");
			SetDlgItemText(IDC_EDITNMONEY,"");
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
void CPALRoleManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CPALRoleManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CPALRoleManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// �رնԻ���
void CPALRoleManage::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// ��ʼ���������͸�ѡ��
void CPALRoleManage::InitPwdType(void)
{
	//OperationPAL operPAL;
	cmbType.ResetContent();
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_GAMETMPPWD"));
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_DELETEROLEPWD"));
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_BANKTMPPWD"));
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_SECONDPWD"));
	cmbType.SetCurSel(0);
	SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","RM_UI_HintDeleteRolePwd"));
}

// ��ʼ����Ǯ���͸�ѡ��
void CPALRoleManage::InitMoneyType(void)
{
	//OperationPAL operPAL;
	cmbType.ResetContent();
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_PERSONALMONEY"));
	cmbType.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_MONEYINBANK"));
	cmbType.SetCurSel(0);	
}

//��ʼ����������
void CPALRoleManage::InitQuestType(void)
{
	//OperationPAL operPAL;
	cmbStatus.ResetContent();
	cmbStatus.AddString(theApp.operPAL.ReadValue("MPAL","UIC_ITEM_Finished"));
	cmbStatus.AddString(theApp.operPAL.ReadValue("MPAL","UIC_ITEM_Received"));
	cmbStatus.SetCurSel(0);
}

// ��ʼ��Ҫ�޸ĵ��������͸�ѡ��
void CPALRoleManage::InitQuestStatus(void)
{
	//OperationPAL operPAL;
	cmbNewStatus.ResetContent();
	cmbNewStatus.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_UnReceived"));
	cmbNewStatus.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_Finished"));
	cmbNewStatus.AddString(theApp.operPAL.ReadValue("MPAL","RM_ITEM_Received"));
	cmbNewStatus.SetCurSel(0);
}

// ��ʾ��ɫ������Ϣ
void CPALRoleManage::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	ShowQuestTab(SW_HIDE,1);
	ShowOperTab(SW_HIDE);
}

// ��ʾ����ҳ��
void CPALRoleManage::ShowOperTab(int m_cmdShow)
{
	//OperationPAL operPAL;
	GetDlgItem(IDC_LBLROLENAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITROLENAME)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);	
	GetDlgItem(IDC_LBLSRC)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNMODI)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLHINT)->ShowWindow(m_cmdShow);
	if(tbcResult.GetCurSel() == 1)
	{
		GetDlgItem(IDC_EDITSRC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITNEW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITSMONEY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNMONEY)->ShowWindow(SW_HIDE);
		SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","RM_ITEM_MODITMPPWD"));
		SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RM_ITEM_RECOVERTMPPWD"));
	}
	else if(tbcResult.GetCurSel() == 2)
	{
		GetDlgItem(IDC_EDITSRC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNEW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITSMONEY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITNMONEY)->ShowWindow(SW_SHOW);
		SetDlgItemText(IDC_BTNMODI,theApp.operPAL.ReadValue("MPAL","RM_ITEM_MODIMONEY"));
		SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RESET"));
	}
	else
	{
		GetDlgItem(IDC_EDITSRC)->ShowWindow(m_cmdShow);
		GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
		GetDlgItem(IDC_EDITSMONEY)->ShowWindow(m_cmdShow);
		GetDlgItem(IDC_EDITNMONEY)->ShowWindow(m_cmdShow);
		SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RESET"));
	}
	SetDlgItemText(IDC_EDITSRC,"");
	SetDlgItemText(IDC_EDITNEW,"");
	SetDlgItemText(IDC_EDITSMONEY,"");
	SetDlgItemText(IDC_EDITNMONEY,"");
}

//��ʾ�����������
void CPALRoleManage::ShowQuestTab(int m_cmdShow,int selectShow)
{	
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLQUESTSTATUS)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBQUESTSTATUS)->ShowWindow(m_cmdShow);	
	if(selectShow == 1)
	{
	    GetDlgItem(IDC_LBLQUESTNAME)->ShowWindow(m_cmdShow);	
	    GetDlgItem(IDC_EDITQUESTNAME)->ShowWindow(m_cmdShow);	
		GetDlgItem(IDC_LBLSTATUS)->ShowWindow(m_cmdShow);
	    GetDlgItem(IDC_CMBSTATUS)->ShowWindow(m_cmdShow);	
	    GetDlgItem(IDC_BTNMODIQUEST)->ShowWindow(m_cmdShow);
	}
	else
	{
		GetDlgItem(IDC_LBLQUESTNAME)->ShowWindow(SW_HIDE);	
	    GetDlgItem(IDC_EDITQUESTNAME)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_LBLSTATUS)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_CMBSTATUS)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_BTNMODIQUEST)->ShowWindow(SW_HIDE);
	}
}