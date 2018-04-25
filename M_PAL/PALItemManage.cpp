// PALItemManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALItemManage.h"
#include ".\palitemmanage.h"


// CPALItemManage �Ի���

IMPLEMENT_DYNAMIC(CPALItemManage, CDialog)
CPALItemManage::CPALItemManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPALItemManage::IDD, pParent)
{
}

CPALItemManage::~CPALItemManage()
{
}

void CPALItemManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_LISTRESULT, listResult);
	DDX_Control(pDX, IDC_CMBBIGTYPE, cmbType);
	DDX_Control(pDX, IDC_CMBSMALLTYPE, cmbName);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
}


BEGIN_MESSAGE_MAP(CPALItemManage, CDialog)
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
	ON_BN_CLICKED(IDC_BTNSEND, OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_CBN_SELCHANGE(IDC_CMBBIGTYPE, OnCbnSelchangeCmbbigtype)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTITEM, OnNMDblclkListitem)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBnClickedBtndelete)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTRESULT, OnLvnColumnclickListresult)
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CPALItemManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// ��ʼ����ʾ�ַ�

	nItem = 0;
	nSelectItem = 0;
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
void CPALItemManage::InitUI()
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

	SetDlgItemText(IDC_LBLADDNAME,theApp.operPAL.ReadValue("MPAL","UIC_UI_lblRole"));
	SetDlgItemText(IDC_LBLBIGTYPE,theApp.operPAL.ReadValue("MPAL","IM_UI_lblItemType"));
	SetDlgItemText(IDC_LBLSMALLTYPE,theApp.operPAL.ReadValue("MPAL","IM_UI_lblItemName"));
	SetDlgItemText(IDC_LBLITEMNUM,theApp.operPAL.ReadValue("MPAL","IM_UI_lblItemNum"));
	SetDlgItemText(IDC_LBLMAILMONEY,theApp.operPAL.ReadValue("MPAL","IM_UI_LBLMAILMONEY"));
	SetDlgItemText(IDC_LBLTOADDITEM,theApp.operPAL.ReadValue("MPAL","IM_UI_lblItemList"));
	SetDlgItemText(IDC_LBLMAILSUBJECT,theApp.operPAL.ReadValue("MPAL","IM_UI_LBLMAILSUBJECT"));
	SetDlgItemText(IDC_LBLMAILCONTENT,theApp.operPAL.ReadValue("MPAL","IM_UI_LBLMAILCONTENT"));
	SetDlgItemText(IDC_LBLMAILREASON,theApp.operPAL.ReadValue("MPAL","IM_UI_LBLMAILREASON"));
	SetDlgItemText(IDC_BTNSEND,theApp.operPAL.ReadValue("MPAL","IM_UI_BTNSEND"));
	SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","RESET"));

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_tpgBody"));
	tbcResult.InsertItem(2,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_tpgBank"));
	tbcResult.InsertItem(3,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_tpgPK"));
	tbcResult.InsertItem(4,theApp.operPAL.ReadValue("MPAL","IM_UI_ADDITEM"));
}

//�����ݼ���Ӧ����
BOOL CPALItemManage::PreTranslateMessage(MSG* pMsg)
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
void CPALItemManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CPALItemManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CPALItemManage::OnBnClickedSearch()
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
void CPALItemManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
void CPALItemManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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

				BagInfo(0);// ��ѯ��ұ�����Ϣ
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
void CPALItemManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		ShowUserInfo();//��ʾ�û�������Ϣ
	}
	else
	{
		ShowOtherInfo();

		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			//OperationPAL operPAL;
			UserAccount = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// ����ѡ�е�����ʺ�
			UserName = theApp.operPAL.GetValueByColName(&listUser, nItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��

			if(tbcResult.GetCurSel()==1)
			{
				BagInfo(0);//��ѯ��ұ�����Ϣ
			}
			else if(tbcResult.GetCurSel() == 2)
			{
				BagInfo(3);//��ѯ��Ҳֿ���Ϣ
			}
			else if(tbcResult.GetCurSel() == 3)
			{
				BagInfo(2);//��ѯ��Ҳر�����Ϣ
			}
			else if(tbcResult.GetCurSel() == 4)
			{
				SetDlgItemText(IDC_EDITADDNAME,UserName);
				ItemTypeInfo();
			}
		}
	}
	*pResult = 0;
}

//��ѯ��ұ�����Ϣ
void CPALItemManage::BagInfo(int iBagType)
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
		socketdata.InitCreate(1,10);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

		_itoa(iBagType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERBAG))
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
void CPALItemManage::OnCbnSelchangeCmbpage()
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
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERBAG))//���Ͳ�ѯ���������Ϣ������
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 2:
				{
					_itoa(3,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
					midlength=socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERBAG))//���Ͳ�ѯ���������Ϣ������
					{
						::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
						dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					}
				}
				break;
			case 3:
				{
					_itoa(2,strInt,10);
					socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
					midlength=socketdata.EnBody();
					if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_CHARACTERBAG))//���Ͳ�ѯ���������Ϣ������
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
void CPALItemManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
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

			int nSelectItem = listResult.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			if(nSelectItem >= 0)
			{	
				CIni mIni;
				//OperationPAL operPAL;
				UserAccount = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ACCOUNT"));// ����ѡ�е�����ʺ�
			    UserName = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));// ����ѡ�е���ҽ�ɫ��

				int itemType = 0;
				CString strItemType = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ITEMTYPE"));// ������Ʒ����
				CString ItemName = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ITEMNAME"));// ������Ʒ����

				if(!strcmp(strItemType,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_Body")))
				{
					itemType = 0;
				}
				else if(!strcmp(strItemType,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_PetBag")))
				{
					itemType = 1;
				}
				else if(!strcmp(strItemType,theApp.operPAL.ReadValue("MPAL","UIC_ITEM_PK")))
				{
					itemType = 2;
				}
				else
				{
					itemType = 3;
				}

				int itemPosition = 0;
				CString strItemPosition = "";
				strItemPosition = theApp.operPAL.GetValueByColName(&listResult, nSelectItem, theApp.operPAL.ReadValue("MPAL","PAL_ITEMPOS"));// ������Ʒλ��

				itemPosition = atoi(strItemPosition);

				if (AfxMessageBox(theApp.operPAL.ReadValue("MPAL","IM_HINT_DELETEITEM"), MB_YESNO) == IDNO) 
				{
				    return;
				}

				int userbyID = theApp.UserByID;

				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�����ĸ�������������IP��������Name������ǳơ�����ԱID
				int midlength = 0;
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�

				_itoa(itemPosition,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ITEMPOS,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��Ʒλ��
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ITEMNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��Ʒ����

				_itoa(userbyID,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

				switch(tbcResult.GetCurSel())
				{
				case 1:
					{
						_itoa(0,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
						midlength=socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_DELCHARACTERITEM))//����ɾ�����ߵ�����
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					    }
					}
					break;
				case 2:
					{
						_itoa(3,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
						midlength=socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_DELCHARACTERITEM))//����ɾ�����ߵ�����
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					    }
					}
					break;
				case 3:
					{
						_itoa(2,strInt,10);
						socketdata.AddTFLV(CEnumCore::TagName::PAL_BAGTYPE,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
						midlength=socketdata.EnBody();
						if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_DELCHARACTERITEM))//����ɾ�����ߵ�����
						{
							::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
							dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
					    }
					}
					break;
				}
				socketdata.Destroy();
			}
		}
		else
		{
	    	nSelectItem = 0;
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

// ��ѯ���������Ϣ
void CPALItemManage::ItemTypeInfo()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		cmbType.ResetContent();
		cmbName.ResetContent();

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_ITEMTYPE_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Error_SearchItemType"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

// ���ݵ�������ѯ��Ӧ�ĵ�������
void CPALItemManage::OnCbnSelchangeCmbbigtype()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		cmbName.ResetContent();

		int ItemTypeID = 0;
		CString ItemTypeName = "";
		GetDlgItemText(IDC_CMBBIGTYPE,ItemTypeName);//��ȡ������������
		if(ItemTypeName == "")//���������Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemTypeNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		BigTypeList.Lookup(cmbType.GetCurSel()+1,ItemTypeID);//��CMap��Ķ���BigTypeList�л�ȡ��������ID

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�

		_itoa(ItemTypeID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ITEMBIGTYPEID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�������ID
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ITEMBIGTYPE,CEnumCore::TagFormat::TLV_STRING,strlen(ItemTypeName),(unsigned char *)mIni.wcharToChar(ItemTypeName));//�������

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_ITEMNAME_QUERY))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Error_SearchItemName"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

//������б�����ӵ���
void CPALItemManage::OnBnClickedBtnadd()
{
	//OperationPAL operPAL;
	try
	{
		int ItemID = 0;
		CString ItemName = "";
		GetDlgItemText(IDC_CMBSMALLTYPE,ItemName);//��ȡ��������
		if(ItemName == "")//�������Ʋ���Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemNameNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		GiftList.Lookup(cmbName.GetCurSel()+1,ItemID);//��CMap��Ķ���GiftList�л�ȡ����ID

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemNumNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(itemNum>5)
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemNum"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CIni mIni;

		int nRow = 0;
		char strInt[10];
		ZeroMemory(strInt,10);
		if(listItem.GetItemCount() == 0)
		{
			DWORD dwStyle = listItem.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
			listItem.SetExtendedStyle(dwStyle); //������չ���

			listItem.InsertColumn(0,theApp.operPAL.ReadValue("MPAL","IM_ITEM_ITEMID"),LVCFMT_CENTER,80,-1);
			listItem.InsertColumn(1,theApp.operPAL.ReadValue("MPAL","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,100,-1);
			listItem.InsertColumn(2,theApp.operPAL.ReadValue("MPAL","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,80,-1);

			_itoa(ItemID,strInt,10);
			int nRow=listItem.InsertItem(0,strInt);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
		}
		else
		{
			int itemCount = 0;
			for(int i=0;i<listItem.GetItemCount();i++)
			{
				itemCount += atoi((LPCSTR)mIni.wcharToChar(listItem.GetItemText(i,2)));
			}
			if((itemCount + itemNum)>5)
			{
				MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_ItemNum"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			    return;
			}
			_itoa(ItemID,strInt,10);
			int nRow=listItem.InsertItem(0,strInt);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
		}
	}
	catch(...)
	{
	}
}

//���������б����к�
void CPALItemManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nSelectItem = listItem.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�
	}
	else
	{
		nSelectItem = 0;
	}
	*pResult = 0;
}

//˫�������б����ɾ��
void CPALItemManage::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nSelectItem = listItem.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

		if(nSelectItem >= 0)
		{
			listItem.DeleteItem(nSelectItem);
		}
	}
	else
	{
		nSelectItem = 0;
	}
	*pResult = 0;
}

//�ӵ����б��н���ɾ��
void CPALItemManage::OnBnClickedBtndelete()
{
	if((listItem.GetItemCount() != 0) && (nSelectItem >= 0))
	{
		listItem.DeleteItem(nSelectItem);
	}
}

// ͨ���ʼ���ӵ���
void CPALItemManage::OnBnClickedBtnsend()
{
	//OperationPAL operPAL;	
	try
	{		
		CIni mIni;

		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		GetDlgItemText(IDC_EDITADDNAME,UserName);//��ȡ��ɫ��
		if(UserName == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","RM_Warn_RoleNameNull"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		///////////////////ȡ�ʼ�����///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_EDMAILSUBJECT,m_strSubject);
		if(m_strSubject == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailSubject"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strContent;
		GetDlgItemText(IDC_EDMAILCONTENT,m_strContent);
		if(m_strContent == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailContent"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strReason;
		GetDlgItemText(IDC_EDMAILREASON,m_strReason);
		if(m_strReason == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Warn_MailReason"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int iMoney=0;
		iMoney=GetDlgItemInt(IDC_EDMAILMONEY);
		int iGift[5]={-1,-1,-1,-1,-1};

		int itemCount = 0;
		int num = 0;
		for(int i=0;i<listItem.GetItemCount();i++)
		{
			itemCount = atoi((LPCSTR)mIni.wcharToChar(listItem.GetItemText(i,2)));
			for(int j=0;j<itemCount;j++)
			{
				iGift[num] = atoi((LPCSTR)mIni.wcharToChar(listItem.GetItemText(i,0)));
				num++;
			}
		}		

		int iUserByID=theApp.UserByID;

		CSocketData socketdata;	
		socketdata.InitCreate(1,25);//��������������������IP��������Name������ǳơ���������,ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::PAL_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserAccount),(unsigned char *)mIni.wcharToChar(UserAccount));//����ʺ�
	
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILSUBJECT,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILCONTENT,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));//����ǳ�

		_itoa(iMoney,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILMONEY,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������


		_itoa(iGift[0],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID0,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������

		_itoa(iGift[1],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID1,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������

		_itoa(iGift[2],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID2,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������

		_itoa(iGift[3],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID3,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������

		_itoa(iGift[4],strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILGIFTDBID4,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������
	
		socketdata.AddTFLV(CEnumCore::TagName::PAL_MAILREASON,CEnumCore::TagFormat::TLV_STRING,strlen(m_strReason),(unsigned char *)mIni.wcharToChar(m_strReason));//����ǳ�


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		_itoa(iUserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������


		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_SENDGIFTMAIL))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","IM_Error_ADDITEM"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}	
}

// ������Ϣ
void CPALItemManage::OnBnClickedBtnreset()
{
	ResetMailInfo();//�����ʼ���Ϣ
}


// ���շ�����Ϣ
LRESULT CPALItemManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
	case CEnumCore::Message_Tag_ID::PAL_CHARACTERBAG_RESP://��ѯ��ұ����Ļ�Ӧ
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
	case CEnumCore::Message_Tag_ID::PAL_DELCHARACTERITEM_RESP:
	case CEnumCore::Message_Tag_ID::PAL_SENDGIFTMAIL_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��
			ShowOtherInfo();
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
void CPALItemManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CPALItemManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operPAL.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CPALItemManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNAME,"");
	ShowUserInfo();
}

// �رնԻ���
void CPALItemManage::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!BigTypeList.IsEmpty())
	{
		BigTypeList.RemoveAll();
	}
	if(!GiftList.IsEmpty())
	{
		GiftList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// ��ʾ��ɫ������Ϣ
void CPALItemManage::ShowUserInfo(void)
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
	ShowMailItem(SW_HIDE);
}

// ��ʾ������Ϣ
void CPALItemManage::ShowBagType(void)
{
	tbcResult.SetCurSel(1);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
	ShowMailItem(SW_HIDE);
}

// ��ʾ������Ϣ
void CPALItemManage::ShowOtherInfo(void)
{
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
	if(tbcResult.GetCurSel()!=4)
	{
	    GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_SHOW);
	    GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	    GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_SHOW);
		ShowMailItem(SW_HIDE);
	}
	else
	{
	    GetDlgItem(IDC_GRPPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_LISTRESULT)->ShowWindow(SW_HIDE);
		ShowMailItem(SW_SHOW);
	}
}

// ��ʾ���͵���ҳ��
void CPALItemManage::ShowMailItem(int m_cmdShow)
{
	GetDlgItem(IDC_LBLMAILSUBJECT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILSUBJECT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILCONTENT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILCONTENT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILMONEY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILMONEY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLBIGTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBBIGTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSMALLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBSMALLTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLITEMNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITITEMNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNADD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELETE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLTOADDITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNSEND)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILREASON)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILREASON)->ShowWindow(m_cmdShow);

	ResetMailInfo();
}

//�����ʼ���Ϣ
void CPALItemManage::ResetMailInfo(void)
{
	SetDlgItemText(IDC_EDMAILSUBJECT,"");
	SetDlgItemText(IDC_EDMAILCONTENT,"");
	SetDlgItemInt(IDC_EDMAILMONEY,0);
	SetDlgItemInt(IDC_EDITITEMNUM,0);
	listItem.DeleteAllItems();
	while(listItem.DeleteColumn(0)){}
	SetDlgItemText(IDC_EDMAILREASON,"");
}