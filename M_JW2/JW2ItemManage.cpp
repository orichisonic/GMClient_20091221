// JW2ItemManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_JW2.h"
#include "JW2ItemManage.h"
#include ".\JW2ItemManage.h"


// CJW2ItemManage �Ի���

IMPLEMENT_DYNAMIC(CJW2ItemManage, CDialog)
CJW2ItemManage::CJW2ItemManage(CWnd* pParent /*=NULL*/)
	: CDialog(CJW2ItemManage::IDD, pParent)
{
}

CJW2ItemManage::~CJW2ItemManage()
{
}

void CJW2ItemManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listResult);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_LISTCHARACTER, listUser);
	DDX_Control(pDX, IDC_CMBUSERPAGE, cmbUPage);
	DDX_Control(pDX, IDC_CMBPOS, cmbPos);
	DDX_Control(pDX, IDC_LISTRESULT, listItem);
	DDX_Control(pDX, IDC_LISTITEM, listItemResult);
}


BEGIN_MESSAGE_MAP(CJW2ItemManage, CDialog)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_CBN_SELCHANGE(IDC_CMBUIPAGE, OnCbnSelchangeCmbuipage)
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LISTCHARACTER, OnNMClickListcharacter)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCHARACTER, OnNMDblclkListcharacter)
	ON_CBN_SELCHANGE(IDC_CMBUSERPAGE, OnCbnSelchangeCmbuserpage)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_CMBPOS, OnCbnSelchangeCmbpos)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_BN_CLICKED(IDC_BTNSEND, OnBnClickedBtnsend)
	ON_BN_CLICKED(IDC_BTNBLURSEARCH, OnBnClickedBtnblursearch)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBnClickedBtndelete)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULT, OnNMClickListresult)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULT, OnNMDblclkListresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTITEM, OnNMDblclkListitem)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CJW2ItemManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�	

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserAccount = "";
	UserID = 0;
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
			listResult.MoveWindow(newRect);//���ú�listResult��λ�ã�listResult��listUser��λ����ȫ�ص�
		}
	}

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	theApp.operJW2.GetServerList();//�������е���Ϸ�������б�
	::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������

	dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CJW2ItemManage::InitUI()
{


	SetWindowText(theApp.operJW2.ReadValue("MJW2","UIC_UI_UserInfo"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operJW2.ReadValue("MJW2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operJW2.ReadValue("MJW2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operJW2.ReadValue("MJW2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operJW2.ReadValue("MJW2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operJW2.ReadValue("MJW2","Cancel"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operJW2.ReadValue("MJW2","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operJW2.ReadValue("MJW2","UIC_UI_tpgUserInfo"));

	tbcResult.InsertItem(1,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgAddItem"));
	//tbcResult.InsertItem(1,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgItemManage"));
	//tbcResult.InsertItem(2,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgMoneyManage"));
	//tbcResult.InsertItem(3,theApp.operJW2.ReadValue("MJW2","IM_UI_tpgAddItem"));


	InitItemPos();

	GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);

	ShowAddItem(SW_HIDE);

}

//�����ݼ���Ӧ����
BOOL CJW2ItemManage::PreTranslateMessage(MSG* pMsg)
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
void CJW2ItemManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect newRect;

	int iWidth=0;

	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;		
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;
		newRect.bottom = newRect.top + grpHeight;

		GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��

		iWidth = newRect.right - newRect.left;
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

	//maple add
/*	if(listItem.m_hWnd != NULL)///�����б�
	{
		//RECT rctGroup;
		//GrpPage.GetWindowRect(&rctGroup);
		//ScreenToClient(&rctGroup);

		newRect.top = rs.top + 4 +grpHeight + tbcHeight+ grpPHeight;
		newRect.bottom = rs.bottom - 100;
		newRect.left = rs.left + 10;
		newRect.right = rs.left + (iWidth/3.5);////380;

		listItem.MoveWindow(newRect);
	}
*/
}

//���ñ�����ɫ
HBRUSH CJW2ItemManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ���������Ϣ
void CJW2ItemManage::OnBnClickedUisearch()
{
	try
	{
		CIni mIni;


		tbcResult.SetCurSel(0);

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������
		
		GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);

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
		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Warn_InputAccount"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CJW2ItemManage::UserInfo()
{	

	try
	{		
		CIni mIni;		
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

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

// ��ҳ��ѯ���������Ϣ
void CJW2ItemManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;
			
			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");//ÿҳ��ʾ50����¼

			while(listUser.DeleteColumn(0)){}//���ҳ������

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

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// �����û��б��浱ǰ�к�
void CJW2ItemManage::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
void CJW2ItemManage::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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

			nItem = listUser.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

			/*if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������
				

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_SHOW);

				UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));
				UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));

			//	ItemInfo();// ������Ϣ��ѯ
			}*/
			if(nItem >= 0)
			{
				tbcResult.SetCurSel(1);

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������




				UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));
				UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
				ShowModifyMoney(SW_HIDE);
				ShowAddItem(SW_SHOW);

				if((listUser.GetItemCount() > 0) && (nItem >= 0))
				{
					UserAccount =theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
					SetDlgItemText(IDC_EDITADDNAME,UserAccount);

				}



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
void CJW2ItemManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{		
	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
			ShowAddItem(SW_HIDE);
			ShowModifyMoney(SW_HIDE);

			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		
		}
		break;
	/*case 1:
		{
			CIni mIni;
			pageInfo = false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){}// �������б��е���������

			ShowAddItem(SW_HIDE);
			ShowModifyMoney(SW_HIDE);

			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserAccount = theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserID"));
				UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
				ItemInfo();// ��ѯ��ҹ��������Ϣ

			}


		}
		break;
	case 2:
		{
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
			ShowAddItem(SW_HIDE);
			ShowModifyMoney(SW_SHOW);


			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserAccount =theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
				CString money=theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_Money"));
				SetDlgItemText(IDC_EDITADDNAME,UserAccount);
				SetDlgItemText(IDC_EDITITEM,money);
				

			}

			

		}
		

		break;
	case 3:
		{
			
			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
			ShowModifyMoney(SW_HIDE);
			ShowAddItem(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				UserAccount =theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
				SetDlgItemText(IDC_EDITADDNAME,UserAccount);

			}
			
		}
		break;*/
		case 1:
			{

				GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);
				ShowModifyMoney(SW_HIDE);
				ShowAddItem(SW_SHOW);

				if((listUser.GetItemCount() > 0) && (nItem >= 0))
				{
					UserAccount =theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_ACCOUNT"));
					SetDlgItemText(IDC_EDITADDNAME,UserAccount);

				}

			}
			break;
	}

	*pResult = 0;
}

// ��ѯ��ҵ�����Ϣ
void CJW2ItemManage::ItemInfo()
{
	try
	{		
	    CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�


		int iItemPos=cmbPos.GetCurSel();
		_itoa(iItemPos,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ItemPos,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����λ��


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ItemInfo_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Story"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ɾ������
void CJW2ItemManage::DelItem()
{
	
	try
	{		
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");


		CString avatarItem;
		CString avatarItemName;
		avatarItem = theApp.operJW2.GetValueByColName(&listResult, nItemResult, theApp.operJW2.ReadValue("MJW2","JW2_AvatarItem"));
		avatarItemName = theApp.operJW2.GetValueByColName(&listResult, nItemResult, theApp.operJW2.ReadValue("MJW2","JW2_AvatarItemName"));
		int iItemNo=atoi(theApp.operJW2.GetValueByColName(&listResult, nItemResult, theApp.operJW2.ReadValue("MJW2","JW2_ItemNo")));
		if (AfxMessageBox("ȷʵɾ���õ���", MB_YESNO) == IDNO) 
		{
			return;
		}


		CSocketData socketdata;
		socketdata.InitCreate(1,20);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID


		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(avatarItem),(unsigned char *)mIni.wcharToChar(avatarItem));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItemName,CEnumCore::TagFormat::TLV_STRING,strlen(avatarItemName),(unsigned char *)mIni.wcharToChar(avatarItemName));//����ǳ�


		int iItemPos=cmbPos.GetCurSel();
		_itoa(iItemPos,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ItemPos,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����λ��

		int userByID = theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID


		_itoa(iItemNo,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ItemNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����λ��


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ITEM_DEL);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Item"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ��ѯ��ҹ��������¼
void CJW2ItemManage::PresentInfo()
{
	
	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");
		iType = cmbType.GetCurSel() + 1;

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�


		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		_itoa(iType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_GOODSTYPE, CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_PRESENT_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Present"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ѡ��ͬ���Ͳ�ѯ��ҹ��������¼
void CJW2ItemManage::OnCbnSelchangeCmbtype()
{
	
	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");
		iType = cmbType.GetCurSel() + 1;

		CSocketData socketdata;
		socketdata.InitCreate(1,6);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		_itoa(iType,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_GOODSTYPE, CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_PRESENT_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Present"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ��ѯ��������Ե���ʹ��
void CJW2ItemManage::ConsumeItem()
{
	
	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,5);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_WASTE_ITEM_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Consume"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}

// ��ѯ���С���ȷ��ͼ�¼
void CJW2ItemManage::BugleSend()
{

	try
	{
		CIni mIni;
		
		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,5);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_BUGLE_QUERY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Bugle"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}
//�û�����
void CJW2ItemManage::UserFamily()
{

	try
	{
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,5);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_User_Family_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_Bugle"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}	
}
// ��ҳ���в�ѯ
void CJW2ItemManage::OnCbnSelchangeCmbuipage()
{
	
	try
	{
		if(pageInfo)
		{
			CIni mIni;
			
			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

			while(listResult.DeleteColumn(0)){}

			CSocketData socketdata;
			socketdata.InitCreate(1,6);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(UserID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

			_itoa(iType,strInt,10);
		    socketdata.AddTFLV(CEnumCore::TagName::JW2_GOODSTYPE, CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����
			
			int midlength = socketdata.EnBody();				
			if(tbcResult.GetCurSel() == 1)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_RPG_QUERY);// ��ѯ��ҹ��������Ϣ
			}
			else if(tbcResult.GetCurSel() == 2)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ITEMSHOP_BYOWNER_QUERY);// ��ѯ������ϵ�����Ϣ
			}
			else if(tbcResult.GetCurSel() == 3)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_HOME_ITEM_QUERY);// ��ѯ��ҷ��������Ϣ
			}
			else if(tbcResult.GetCurSel() == 4)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_PRESENT_QUERY);// ��ѯ��ҹ��������¼
			}
			else if(tbcResult.GetCurSel() == 5)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_WASTE_ITEM_QUERY);// ��ѯ��������Ե���ʹ��
			}
			else if(tbcResult.GetCurSel() == 6)
			{
				theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_SMALL_BUGLE_QUERY);// ��ѯ���С���ȷ��ͼ�¼
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

// ���շ�����Ϣ
LRESULT CJW2ItemManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
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
			/*//////maple add
			char *pdest;
			int nPos;
			char strServer[128];
			ZeroMemory(strServer,128);
			char *split=",";
			char destServer[128];
			ZeroMemory(destServer,128);*/

			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ServerIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP

			/*	//maple add
				sprintf(strServer,"%s",ServerIP);
				pdest=strstr(strServer,split);
				nPos=pdest-strServer;
				strncpy(destServer,strServer,nPos);
				destServer[nPos]='\0';*/

				ServerList.SetAt(i,ServerIP);//��������IP������CMap��Ķ���ServerList��
				//ServerList.SetAt(i,(LPCSTR)&destServer);
			}

			theApp.operJW2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ACCOUNT_QUERY_RESP://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageUInfo = false;//���ܷ�ҳ					
					cmbUPage.ResetContent();//���ҳ����ѡ��
					while(listUser.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
					cmbUPage.ResetContent();//���ҳ����ѡ���Ա����¹���
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbUPage.AddString(str);//�ڸ�ѡ���й���ҳ����Ϣ
					}
					cmbUPage.SetCurSel(0);//�ڸ�ѡ����ѡ�е�һҳ
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
	case CEnumCore::Message_Tag_ID::JW2_ITEM_DEL_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ�������
			pageInfo = false;
			cmbPage.ResetContent();
			while(listResult.DeleteColumn(0)){}// �������б��е���������
			ItemInfo();
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_MODIFY_MONEY_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ�������
			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPOS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPOS)->ShowWindow(SW_HIDE);
			ShowAddItem(SW_HIDE);
			ShowModifyMoney(SW_HIDE);

			GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);
			UserInfo();

		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ITEM_SELECT_RESP:
		{
			theApp.operJW2.BuildDataTable(&socketdata,&listItem,&pageCount);//����CListCtrl����
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ADD_ITEM_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			/////theApp.operJW2.ShowResult(result);//��ʾ�������
			
			if(result=="Add_Item_Success")
				DeductProductManage();
			else
				theApp.operJW2.ShowResult(result);//��ʾ�������

		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Validate_Resp://��֤Ȩ��
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			if(result=="1")
				AddItem();
			else
			{
				m_tflv=socketdata.getTLVBynIndex(2);
				result=(LPCTSTR)&m_tflv.lpdata;
				theApp.operJW2.ShowResult(result);//��ʾ�������*/
			}


			//maple add
			/*char strResult[128];
			ZeroMemory(strResult,128);
			char *split=";";
			sprintf(strResult,"%s",result);
			char *pdest;
			pdest=strstr(strResult,split);
			pdest++;
			char strSuccess[30];
			ZeroMemory(strSuccess,30);
			strcpy(strSuccess,pdest);
			CString str1=(LPCSTR)&strSuccess;

			if("SUCCESS"==str1)
				AddItem();
			else
				theApp.operJW2.ShowResult(result);//��ʾ�������*/

			
		}
		break;
	case CEnumCore::Message_Tag_ID::JW2_ProductManage_Deduct_Resp://��֤ͨ����Ȩ�ޱ��м�ȥ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operJW2.ShowResult(result);//��ʾ�������

			OnBnClickedBtnreset();
		}
		break;
	default:
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operJW2.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	}

	socketdata.Destroy();
	return false;
}

//�����û�������Ϣ��������������
void CJW2ItemManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CJW2ItemManage::OnLvnColumnclickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
{

	theApp.operJW2.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CJW2ItemManage::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void CJW2ItemManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//��ʼ����Ʒλ��
void CJW2ItemManage::InitItemPos()
{
	cmbPos.ResetContent();
	cmbPos.AddString(theApp.operJW2.ReadValue("MJW2","IM_Pos_Body"));
	cmbPos.AddString(theApp.operJW2.ReadValue("MJW2","IM_Pos_WuBin"));
	cmbPos.AddString(theApp.operJW2.ReadValue("MJW2","IM_Pos_liWu"));	
	cmbPos.SetCurSel(0);
}

void CJW2ItemManage::OnCbnSelchangeCmbpos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pageInfo = false;
	cmbPage.ResetContent();
	while(listResult.DeleteColumn(0)){}// �������б��е���������
	ItemInfo();
}

void CJW2ItemManage::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)//ɾ������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(listResult.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItemResult = listResult.SubItemHitTest(&lvinfo);//���������������Ϣ�б���ѡ�е��к�

		if(nItemResult >= 0)
		{
			DelItem();
		}
	}
	else
	{
		nItemResult = -1;
	}

	*pResult = 0;
}

//��ʾ��ӵ���
void CJW2ItemManage::ShowAddItem(int nCmdShow)
{
	GetDlgItem(IDC_LBLADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNBLURSEARCH)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_LISTRESULT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLITEMNUM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITITEMNUM)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_BTNADD)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNDELETE)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_LBLTOADDITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_LBLMAILSUBJECT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDMAILSUBJECT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLMAILCONTENT)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDMAILCONTENT)->ShowWindow(nCmdShow);

	GetDlgItem(IDC_BTNSEND)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(nCmdShow);


	SetDlgItemText(IDC_LBLADDNAME,theApp.operJW2.ReadValue("MJW2","IM_UI_Account"));
	SetDlgItemText(IDC_LBLITEM,theApp.operJW2.ReadValue("MJW2","IM_UI_ItemName"));
	SetDlgItemText(IDC_BTNBLURSEARCH,theApp.operJW2.ReadValue("MJW2","IM_UI_Search"));
	SetDlgItemText(IDC_LBLITEMNUM,theApp.operJW2.ReadValue("MJW2","IM_UI_ItemNum"));
	SetDlgItemText(IDC_LBLTOADDITEM,theApp.operJW2.ReadValue("MJW2","IM_UI_ItemList"));
	SetDlgItemText(IDC_LBLMAILSUBJECT,theApp.operJW2.ReadValue("MJW2","IM_UI_MailSubject"));
	SetDlgItemText(IDC_LBLMAILCONTENT,theApp.operJW2.ReadValue("MJW2","IM_UI_MailBody"));
	SetDlgItemText(IDC_BTNSEND,theApp.operJW2.ReadValue("MJW2","IM_UI_Send"));
	SetDlgItemText(IDC_BTNRESET,theApp.operJW2.ReadValue("MJW2","IM_UI_Reset"));

	SetDlgItemText(IDC_EDITITEM,"");
	SetDlgItemInt(IDC_EDITITEMNUM,1);



}

//��ʾ�޸�G��
void CJW2ItemManage::ShowModifyMoney(int nCmdShow)
{

	GetDlgItem(IDC_LBLADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITADDNAME)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_LBLITEMNUM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_EDITITEMNUM)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNSEND)->ShowWindow(nCmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(nCmdShow);

	SetDlgItemText(IDC_LBLADDNAME,theApp.operJW2.ReadValue("MJW2","IM_UI_Account"));
	SetDlgItemText(IDC_LBLITEM,theApp.operJW2.ReadValue("MJW2","IM_UI_OldMoney"));
	SetDlgItemText(IDC_LBLITEMNUM,theApp.operJW2.ReadValue("MJW2","IM_UI_NewMoney"));
	SetDlgItemText(IDC_BTNSEND,theApp.operJW2.ReadValue("MJW2","IM_UI_Confirm"));
	SetDlgItemText(IDC_BTNRESET,theApp.operJW2.ReadValue("MJW2","IM_UI_Reset"));
}
//��ӵ���
void CJW2ItemManage::AddItem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		GetDlgItemText(IDC_EDITADDNAME,UserName);//��ȡ��ɫ��
		if(UserName == "")
		{
			MessageBox(theApp.operJW2.ReadValue("MGTOWN","RM_Warn_RoleNameNull"),theApp.operJW2.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		///////////////////ȡ�ʼ�����///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_EDMAILSUBJECT,m_strSubject);
		if(m_strSubject == "")
		{
			MessageBox(theApp.operJW2.ReadValue("MGTOWN","IM_Warn_MailSubject"),theApp.operJW2.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		CString m_strContent;
		GetDlgItemText(IDC_EDMAILCONTENT,m_strContent);
		if(m_strContent == "")
		{
			MessageBox(theApp.operJW2.ReadValue("MGTOWN","IM_Warn_MailContent"),theApp.operJW2.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}	

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//��ʼ��Ҫ���͵ĵ�����Ϣ
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//������ʱ�ĵ�����Ϣ

		int itemCount = listItemResult.GetItemCount();//Ҫ��ӵ��ߵ�����
		int mid = 0;//Ҫ��ӵĵ�����Ʒ��
		int itemNum = 0;//Ҫ��ӵĵ�������
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,2)));
			sprintf(tmpItemData, "%i*%i", mid, itemNum);
			if(i == 0)
			{
				sprintf(ItemData, "%s", tmpItemData);
			}
			else
			{
				sprintf(ItemData, "%s|%s", ItemData, tmpItemData);
			}
		}		

	

		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�


		//�ʼ�����
		socketdata.AddTFLV(CEnumCore::TagName::JW2_MailTitle,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));
		//�ʼ�����
		socketdata.AddTFLV(CEnumCore::TagName::JW2_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));

		//��ӵĵ�������
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		_itoa(itemCount,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�������

		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID


		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ADD_ITEM))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

///��֤Ȩ��
void CJW2ItemManage::ValidateProductManage()
{
	try
	{		
		CIni mIni;


		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		//GM�ʺ�
		//UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		int userByID=theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱIDChar(GMName));

	
		//ServerIP = ReturnServerIP();
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
		//ServerIP="222.211.80.58";
		
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//��ʼ��Ҫ���͵ĵ�����Ϣ
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//������ʱ�ĵ�����Ϣ


		//maple add
		//char tmpItemIDList[1024];
		//ZeroMemory(tmpItemIDList,1024);
		//char ItemIDList[1024];
		//ZeroMemory(ItemIDList,1024);

		int itemCount = listItemResult.GetItemCount();//Ҫ��ӵ��ߵ�����
		int mid = 0;//Ҫ��ӵĵ�����Ʒ��
		int itemNum = 0;//Ҫ��ӵĵ�������
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,2)));
			sprintf(tmpItemData, "%i*%i", mid, itemNum);
			if(i == 0)
			{
				sprintf(ItemData, "%s|", tmpItemData);
				////sprintf(ItemIDList,"<%s>",mid);
			}
			else
			{
				sprintf(ItemData, "%s%s|", ItemData, tmpItemData);
			}
		}		

		//��ӵĵ�������
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

/*		/////_itoa(itemCount,strInt,10);
		/////socketdata.AddTFLV(CEnumCore::TagName::PageCount,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�������


		CTime StartDate;
		dtcStartDate.GetTime(StartDate);

		CTime EndDate;
		dtcEndDate.GetTime(EndDate);

		CTime beginTime = CTime::CTime(StartDate.GetYear(),StartDate.GetMonth(),StartDate.GetDay(),0,0,0);
		CTime toTime = CTime::CTime(EndDate.GetYear(),EndDate.GetMonth(),EndDate.GetDay(),0,0,0);

		CString strBeginTime = beginTime.Format("%Y/%m/%d %H:%M:%S");//���ÿ�ʼʱ��
		CString strEndTime = toTime.Format("%Y/%m/%d %H:%M:%S");//���ý���ʱ��


		socketdata.AddTFLV(CEnumCore::TagName::JW2_BeginTime,CEnumCore::TagFormat::TLV_STRING,strlen(strBeginTime),(unsigned char*)mIni.wcharToChar(strBeginTime));//��ʼʱ��
		socketdata.AddTFLV(CEnumCore::TagName::JW2_EndTime,CEnumCore::TagFormat::TLV_STRING,strlen(strEndTime),(unsigned char*)mIni.wcharToChar(strEndTime));//����ʱ��

		///_itoa(CountItemPrice,strInt,10);
		////socketdata.AddTFLV(CEnumCore::TagName::JW2_TotalPrice,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�ܶ�
*/

		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Validate))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		/////MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}

}

//��֤ͨ����Ȩ���м�ȥ
void CJW2ItemManage::DeductProductManage()
{
	try
	{		
		CIni mIni;


		CSocketData socketdata;	
		socketdata.InitCreate(1,25);
		char strInt[10];
		ZeroMemory(strInt, 10);

		//GM�ʺ�
		//UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		int userByID=theApp.UserByID;
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱIDChar(GMName));


		//ServerIP = ReturnServerIP();
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
		//ServerIP="222.211.80.58";
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP

		char ItemData[2048];
		ZeroMemory(ItemData, 2048);//��ʼ��Ҫ���͵ĵ�����Ϣ
		char tmpItemData[2048];
		ZeroMemory(tmpItemData, 2048);//������ʱ�ĵ�����Ϣ

		int itemCount = listItemResult.GetItemCount();//Ҫ��ӵ��ߵ�����
		int mid = 0;//Ҫ��ӵĵ�����Ʒ��
		int itemNum = 0;//Ҫ��ӵĵ�������
		for(int i=0;i<itemCount;i++)
		{
			mid = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,0)));
			itemNum = atoi(mIni.wcharToChar(listItemResult.GetItemText(i,2)));
			sprintf(tmpItemData, "%i*%i", mid, itemNum);
			if(i == 0)
			{
				sprintf(ItemData, "%s|", tmpItemData);
			}
			else
			{
				sprintf(ItemData, "%s%s|", ItemData, tmpItemData);
			}
		}		

		//��ӵĵ�������
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItem,CEnumCore::TagFormat::TLV_STRING,strlen(ItemData),(unsigned char *)ItemData);

		

		int midlength = socketdata.EnBody();
		if(theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ProductManage_Deduct))
		{
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
		/////MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Error_ADDITEM"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}

}


void CJW2ItemManage::ModifyMoney()
{
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MGTOWN","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MGTOWN","pageSize");


		UpdateData(true);			


		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		int iMoney=GetDlgItemInt(IDC_EDITITEMNUM);
		_itoa(iMoney,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_Money,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID


		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_MODIFY_MONEY);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ^����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MGTOWN","UIC_Error_TreasureBox"),theApp.operJW2.ReadValue("MGTOWN","Error"),0);
	}// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//���͵���
void CJW2ItemManage::OnBnClickedBtnsend()
{

	switch(tbcResult.GetCurSel())
	{
	case 1:
		//maple add
		ValidateProductManage();
		//DeductProductManage();
		///AddItem();
		break;
	default:
		break;
	/*case 2:
		ModifyMoney();
		break;
	case 3:
		//maple add
		ValidateProductManage();
		//DeductProductManage();
		///AddItem();
		break;
	default:
		break;*/
	}
	

}

void CJW2ItemManage::OnBnClickedBtnblursearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{		
		CIni mIni;

		int index = theApp.operJW2.ReadIntValue("MJW2","index");
		int iPageSize = theApp.operJW2.ReadIntValue("MJW2","pageSize");

		while(listItem.DeleteColumn(0)){};

		UpdateData(true);			

		CString tmpName = "";//����ģ����ѯ�ĵ�������
		GetDlgItemText(IDC_EDITITEM,tmpName);//��ȡ����ģ����ѯ�ĵ�������
		if(tmpName == "")//����ģ����ѯ�ĵ������Ʋ���Ϊ��
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","IM_WARN_BlurItemNameNull"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerName,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::JW2_ACCOUNT,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		//����ģ����ѯ�ĵ�������
		socketdata.AddTFLV(CEnumCore::TagName::JW2_AvatarItemName,CEnumCore::TagFormat::TLV_STRING,strlen(tmpName),(unsigned char *)mIni.wcharToChar(tmpName));

		UserID = atoi(mIni.wcharToChar(theApp.operJW2.GetValueByColName(&listUser, nItem, theApp.operJW2.ReadValue("MJW2","JW2_UserSN"))));
		_itoa(UserID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::JW2_UserSN,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ID

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����


		int midlength = socketdata.EnBody();
		theApp.operJW2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::JW2_ITEM_SELECT);//����ģ����ѯ

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operJW2.ReadIntValue("MJW2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ^����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operJW2.ReadValue("MJW2","UIC_Error_TreasureBox"),theApp.operJW2.ReadValue("MJW2","Error"),0);
	}

}

void CJW2ItemManage::OnBnClickedBtnadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;

		if((listItem.GetItemCount() == 0)||(addItem < 0))//���Ҫ��ӵĵ����б�Ϊ���򷵻�
		{
			return;
		}

		CString tmpItemID = listItem.GetItemText(addItem, 0);
		int ItemID = atoi(mIni.wcharToChar(tmpItemID));//��ȡҪ��ӵĵ���ID
		CString ItemName = listItem.GetItemText(addItem, 1);//��ȡҪ��ӵĵ�������
		CString ItemLimit= listItem.GetItemText(addItem, 2);
		CString ItemRemain= listItem.GetItemText(addItem, 3);

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operJW2.ReadValue("MJW2","IM_Warn_ItemNumNull"),theApp.operJW2.ReadValue("MJW2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		//if(itemNum>5)
		//{
		//	MessageBox(theApp.operGTOWN.ReadValue("MGTOWN","IM_Warn_ItemNum"),theApp.operGTOWN.ReadValue("MGTOWN","Warn"),MB_ICONWARNING+MB_OK);
		//	return;
		//}

		int nRow = 0;
		char strInt[10];
		ZeroMemory(strInt,10);
		if(listItemResult.GetItemCount() == 0)
		{
			DWORD dwStyle = listItemResult.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
			listItemResult.SetExtendedStyle(dwStyle); //������չ���

			listItemResult.InsertColumn(0,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMID"),LVCFMT_CENTER,40,-1);
			listItemResult.InsertColumn(1,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,50,-1);
			listItemResult.InsertColumn(2,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,40,-1);
			listItemResult.InsertColumn(3,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMEXPIREDATE"),LVCFMT_CENTER,50,-1);
			listItemResult.InsertColumn(4,theApp.operJW2.ReadValue("MJW2","IM_ITEM_ITEMREMAINCOUNT"),LVCFMT_CENTER,40,-1);

			_itoa(ItemID,strInt,10);
			int nRow=listItemResult.InsertItem(0,strInt);
			listItemResult.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItemResult.SetItemText(nRow,2,strInt);
			listItemResult.SetItemText(nRow,3,ItemLimit);
			listItemResult.SetItemText(nRow,4,ItemRemain);
		}
		else
		{
			_itoa(ItemID,strInt,10);
			int nRow=listItemResult.InsertItem(0,strInt);
			listItemResult.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItemResult.SetItemText(nRow,2,strInt);
			listItemResult.SetItemText(nRow,3,ItemLimit);
			listItemResult.SetItemText(nRow,4,ItemRemain);
		}
	}
	catch(...)
	{
	}
}

void CJW2ItemManage::OnBnClickedBtndelete()
{
	if((listItemResult.GetItemCount() != 0) && (delItem >= 0))
	{
		listItemResult.DeleteItem(delItem);
	}
	if(listItemResult.GetItemCount() == 0)
	{
		while(listItemResult.DeleteColumn(0)){};
	}

}

void CJW2ItemManage::OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		addItem = listItem.SubItemHitTest(&lvinfo);//�����ڿ�����ӵĵ����б���ѡ�е��к�
	}
	else
	{
		addItem = -1;
	}
	*pResult = 0;
}

void CJW2ItemManage::OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItem.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItem.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		addItem = listItem.SubItemHitTest(&lvinfo);//�����ڿ�����ӵĵ����б���ѡ�е��к�

		if(addItem >= 0)
		{
			OnBnClickedBtnadd();
		}
	}
	else
	{
		addItem = -1;
	}
	*pResult = 0;
}

void CJW2ItemManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(listItemResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItemResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItemResult.SubItemHitTest(&lvinfo);//�����ڿ�����ӵĵ����б���ѡ�е��к�
	}
	else
	{
		delItem = -1;
	}
	*pResult = 0;
}

void CJW2ItemManage::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listItemResult.GetItemCount() > 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listItemResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		delItem = listItemResult.SubItemHitTest(&lvinfo);//�����ڿ�����ӵĵ����б���ѡ�е��к�

		if(delItem >= 0)
		{
			OnBnClickedBtndelete();
		}
	}
	else
	{
		delItem = -1;
	}
	*pResult = 0;
}

void CJW2ItemManage::OnBnClickedBtnreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDITITEM,"");//ģ����ѯ��������Ϊ��
	SetDlgItemInt(IDC_EDITITEMNUM,1);//��������Ϊ1
	SetDlgItemText(IDC_EDMAILSUBJECT,"");//�ʼ�����Ϊ��
	SetDlgItemText(IDC_EDMAILCONTENT,"");//�ʼ�����Ϊ��
	listItem.DeleteAllItems();
	while(listItem.DeleteColumn(0)){}//�����б�Ϊ��
	listItemResult.DeleteAllItems();
	while(listItemResult.DeleteColumn(0)){}//���͵����б�Ϊ��
}
