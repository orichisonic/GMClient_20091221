// WAItemManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_WA.h"
#include "WAItemManage.h"
#include ".\waitemmanage.h"

/*���߹���
��ִ�в�����
�١�������ӣ��ɵ���/����������е���
�ڡ�����ɾ������ɾ����ɫ���ϡ�������������Ʒ
�ۡ��޸Ľ�ɫ���н�Ǯ����(�������޴洢��Ǯ����)
�ܡ���ӽ�ɫ���ϡ����н�Ǯ����(�������޴洢��Ǯ����)*/

// CWAItemManage �Ի���

IMPLEMENT_DYNAMIC(CWAItemManage, CDialog)
CWAItemManage::CWAItemManage(CWnd* pParent /*=NULL*/)
	: CDialog(CWAItemManage::IDD, pParent)
{
}

CWAItemManage::~CWAItemManage()
{
}

void CWAItemManage::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_CMBITEM, cmbList);
	DDX_Control(pDX, IDC_LISTITEM, listItem);
	DDX_Control(pDX, IDC_CMBTYPE, cmbType);
	DDX_Control(pDX, IDC_CHECKBATCH, checkSelect);
	DDX_Control(pDX, IDC_EDITNEW, CEditNew);
	DDX_Control(pDX, IDC_CHECKGROUP, checkGroup);
	DDX_Control(pDX, IDC_PROGRESSMAIL, progMail);
	DDX_Control(pDX, IDC_CMBQUALITY, cmbQuality);
}


BEGIN_MESSAGE_MAP(CWAItemManage, CDialog)
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
	ON_BN_CLICKED(IDC_BTNEDIT, OnBnClickedBtnedit)
	ON_BN_CLICKED(IDC_BTNRECOVER, OnBnClickedBtnrecover)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_BN_CLICKED(IDC_BTNDELITEM, OnBnClickedBtndelitem)
	ON_BN_CLICKED(IDC_BTNITEMLIST, OnBnClickedBtnitemlist)
	ON_BN_CLICKED(IDC_BTNADD, OnBnClickedBtnadd)
	ON_NOTIFY(NM_CLICK, IDC_LISTITEM, OnNMClickListitem)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTITEM, OnNMDblclkListitem)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBnClickedBtndelete)
	ON_BN_CLICKED(IDC_CHECKBATCH, OnBnClickedCheckselect)
	ON_BN_CLICKED(IDC_BTNBROWSE, OnBnClickedBtnbrowse)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTCHARACTER, OnLvnColumnclickListuserinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTUSERINFO, OnLvnColumnclickListresult)
	ON_BN_CLICKED(IDC_CHECKGROUP, OnBnClickedCheckgroup)
	ON_CBN_SELCHANGE(IDC_CMBUISERVER, OnCbnSelchangeCmbuiserver)
END_MESSAGE_MAP()


// ��ʼ���Ի���
BOOL CWAItemManage::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitUI();// ��ʼ����ʾ�ַ�

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//��ʼ��һЩ˽�б���
	nFirst = 0;
	nListItem = 0;
	nSelectItem = 0;
	ZeroMemory(ItemResult, 2048);//��ʼ����ӵ��ߵ����ս��
	ZeroMemory(tmpItemResult, 2048);//��ʱ����ӵ�����Ϣ
	multStatus=0;//���������
	UserNum=0;//�ʼ��ɫ������Ϊ0
	mCurNum = 0;

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

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operWA.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}
	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CWAItemManage::InitUI()
{
	SetWindowText(theApp.operWA.ReadValue("MWA","IM_UI_ITEMMANAGE"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operWA.ReadValue("MWA","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operWA.ReadValue("MWA","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operWA.ReadValue("MWA","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operWA.ReadValue("MWA","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operWA.ReadValue("MWA","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operWA.ReadValue("MWA","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operWA.ReadValue("MWA","IM_UI_tpgBodyItem"));
	tbcResult.InsertItem(2,theApp.operWA.ReadValue("MWA","IM_UI_tpgPackItem"));
	tbcResult.InsertItem(3,theApp.operWA.ReadValue("MWA","IM_UI_tpgBankItem"));
	tbcResult.InsertItem(4,theApp.operWA.ReadValue("MWA","IM_UI_tpgAddItem"));
	tbcResult.InsertItem(5,theApp.operWA.ReadValue("MWA","IM_UI_tpgEditMoney"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operWA.ReadValue("MWA","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLITEM,theApp.operWA.ReadValue("MWA","IM_UI_lblItemName"));
	SetDlgItemText(IDC_LBLNUM,theApp.operWA.ReadValue("MWA","IM_UI_lblItemNum"));
	SetDlgItemText(IDC_BTNDELITEM,theApp.operWA.ReadValue("MWA","IM_UI_DELITEM"));

	SetDlgItemText(IDC_CHECKBATCH,theApp.operWA.ReadValue("MWA","IM_UI_CHECKMULT"));
	SetDlgItemText(IDC_CHECKGROUP,theApp.operWA.ReadValue("MWA","IM_UI_CHECKGROUP"));
	SetDlgItemText(IDC_BTNBROWSE,theApp.operWA.ReadValue("MWA","IM_UI_BTNBROWSE"));

	SetDlgItemText(IDC_LBLQUALITY,theApp.operWA.ReadValue("MWA","IM_UI_ITEMQUALITY"));
	SetDlgItemText(IDC_LBLTIME,theApp.operWA.ReadValue("MWA","IM_UI_ITEMTIME"));
	SetDlgItemText(IDC_LBLSECOND,theApp.operWA.ReadValue("MWA","IM_UI_SECOND"));
	SetDlgItemText(IDC_LBLMAILSUBJECT,theApp.operWA.ReadValue("MWA","IM_UI_LBLMAILSUBJECT"));
	SetDlgItemText(IDC_LBLMAILCONTENT,theApp.operWA.ReadValue("MWA","IM_UI_LBLMAILCONTENT"));
	SetDlgItemText(IDC_LBLMAILMONEY,theApp.operWA.ReadValue("MWA","IM_UI_MONEY"));

	cmbQuality.AddString(theApp.operWA.ReadValue("MWA","IM_UI_WHITE"));
	cmbQuality.AddString(theApp.operWA.ReadValue("MWA","IM_UI_BLUE"));
	cmbQuality.AddString(theApp.operWA.ReadValue("MWA","IM_UI_PURPLE"));
	cmbQuality.AddString(theApp.operWA.ReadValue("MWA","IM_UI_ORANGE"));
	cmbQuality.SetCurSel(0);

	SetDlgItemText(IDC_LBLMAIN,theApp.operWA.ReadValue("MWA","IM_UI_LblMain"));
	SetDlgItemText(IDC_LBLPROG,theApp.operWA.ReadValue("MWA","IM_UI_LblMailFirst")+theApp.operWA.ReadValue("MWA","IM_UI_LblMailSecond")+theApp.operWA.ReadValue("MWA","IM_UI_LblMailThird")+theApp.operWA.ReadValue("MWA","IM_UI_LblMailFourth"));
}

// �Զ��ı��С
void CWAItemManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CWAItemManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ȡѡ���ServerIP
void CWAItemManage::OnCbnSelchangeCmbuiserver()
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

// ��ѯ���������Ϣ
void CWAItemManage::OnBnClickedUisearch()
{
	try
	{
		CIni mIni;

		tbcResult.SetCurSel(0);

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		ShowItemInfo(SW_HIDE);
		ShowNewItem(SW_HIDE);
		ShowUserInfo(SW_SHOW);

		UpdateData(true);

		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_SelectServer"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITUINICK,UserNick);//��ȡ����ǳ�
		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","UIC_Warn_InputAccount"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CWAItemManage::UserInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operWA.ReadIntValue("MWA","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_UserInfo"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ҳ��ѯ���������Ϣ
void CWAItemManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;
			//OperationWA theApp.operWA;	

			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");//ÿҳ��ʾ50����¼

			while(listUser.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query );//���Ͳ�ѯ���������Ϣ������

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// �����û��б��浱ǰ�к�
void CWAItemManage::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
void CWAItemManage::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				while(listResult.DeleteColumn(0)){}// �������б��е���������

				ShowNewItem(SW_HIDE);
				ShowUserInfo(SW_HIDE);
				ShowItemInfo(SW_SHOW);

				GetDlgItem(IDC_LBLITEM)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTNDELITEM)->ShowWindow(SW_HIDE);

				if((listUser.GetItemCount() > 0) && (nItem >= 0))
				{
					UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// ����ѡ�е�����ʺ�
					UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// ����ѡ�е����ID
					UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// ����ѡ�е�����ǳ�

					tbcResult.SetCurSel(1);
					ItemInfo();
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
void CWAItemManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	UserName = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Account"));// ����ѡ�е�����ʺ�
	UserID = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_NickID"));// ����ѡ�е����ID
	UserNick = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_UserNick"));// ����ѡ�е�����ǳ�

	switch(tbcResult.GetCurSel())
	{
	case 0:
		{
			ShowItemInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowUserInfo(SW_SHOW);
		}
		break;
	case 1:
		{
			ShowNewItem(SW_HIDE);	
			ShowUserInfo(SW_HIDE);
			ShowItemInfo(SW_SHOW);

			GetDlgItem(IDC_LBLITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNDELITEM)->ShowWindow(SW_HIDE);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				ItemInfo();
			}
		}
		break;
	case 2:
		{		
			ShowUserInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);	
			ShowItemInfo(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				ItemInfo();
			}
		}
		break;
	case 3:
		{				
			ShowUserInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowItemInfo(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				ItemInfo();
			}	
		}
		break;
	case 4:
		{
			ShowUserInfo(SW_HIDE);
			ShowItemInfo(SW_HIDE);
			ShowMoneyInfo(SW_HIDE);
			ShowNewItem(SW_SHOW);
			NewItemValue();

			SearchItemType();

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);				
			}
		}
		break;
	case 5:
		{
			ShowUserInfo(SW_HIDE);
			ShowItemInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowMoneyInfo(SW_SHOW);

			if((listUser.GetItemCount() > 0) && (nItem >= 0))
			{
				SetDlgItemText(IDC_EDITACCOUNT,UserName);
				SetDlgItemText(IDC_EDITNICK,UserNick);
			}
		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

// ��ѯ��ɫ������Ϣ
void CWAItemManage::ItemInfo()
{	
	try
	{		
		CIni mIni;
		pageInfo = false;
		cmbPage.ResetContent();
		while(listResult.DeleteColumn(0)){}// �������б��е���������

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			_itoa(tbcResult.GetCurSel()-1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::WA_ItemPos,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ͣ�0�����ϣ�1��������2������

			int midlength = socketdata.EnBody();
			switch(tbcResult.GetCurSel())
			{
			case 1:
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BodyItemInfo_Query);//��ѯ��ɫ������Ʒ
				break;
			case 2:
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BagItemInfo_Query);//��ѯ��ɫ������Ʒ
				break;
			case 3:
				theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query );//��ѯ��ɫ������Ʒ
				break;
			default:
				break;
			}
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Item"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

// ��ҳ���в�ѯ
void CWAItemManage::OnCbnSelchangeCmbuipage()
{	
	try
	{
		if(pageInfo)
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
				socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//���IDKEY

				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

				_itoa(tbcResult.GetCurSel()-1,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::WA_ItemPos,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ͣ�0�����ϣ�1��������2������

				int midlength = socketdata.EnBody();				
				switch(tbcResult.GetCurSel())
				{
				case 1:
					theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BodyItemInfo_Query);//��ѯ��ɫ������Ʒ
					break;
				case 2:
					theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BagItemInfo_Query);//��ѯ��ɫ������Ʒ
					break;
				case 3:
					theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_BankItemInfo_Query );//��ѯ��ɫ������Ʒ
					break;
				default:
					break;
				}

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_Page"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//ѡ����Ӧ�ĵ�����Ϣ����ɾ��
void CWAItemManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(listResult.GetItemCount() != 0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listResult.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nListItem = listResult.SubItemHitTest(&lvinfo);//��������Ҽ�����Ϣ�б���ѡ�е��к�

		if(nListItem >= 0)
		{			
			ItemName = theApp.operWA.GetValueByColName(&listResult, nListItem, theApp.operWA.ReadValue("MWA","WA_itemName"));// ����ѡ�еĵ�������
			SetDlgItemText(IDC_EDITITEM,ItemName);
		}
	}
	else
	{
		nListItem = -1;
	}
	*pResult = 0;
}

//ɾ��ѡ�еĵ�����Ϣ
void CWAItemManage::OnBnClickedBtndelitem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITITEM,ItemName);//��ȡ��������
			if(ItemName == "")//Ҫɾ���ĵ������Ʋ���Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","IM_HINT_DELETEITEM"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			int ItemIndex = atoi(theApp.operWA.GetValueByColName(&listResult, nListItem, theApp.operWA.ReadValue("MWA","WA_itemIndex")));// ����ѡ�еĵ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			_itoa(tbcResult.GetCurSel()-1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::WA_ItemPos,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ͣ�0�����ϣ�1��������2������

			_itoa(ItemIndex,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::WA_ItemID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������

			socketdata.AddTFLV(CEnumCore::TagName::WA_itemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��������

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Item_Del);//ɾ��������Ϣ

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","IM_Error_DELETEITEM"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//ѡ���Ƿ�������ӵ���
void CWAItemManage::OnBnClickedCheckselect()
{
	if(checkSelect.GetCheck()==1)
	{
		checkGroup.SetCheck(0);

		GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_HIDE);

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","IM_UI_LBLPATH"));
		multStatus=1;
	}
	else
	{
		GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
		multStatus=0;
	}
}

//ѡ���Ƿ���ҪȺ������
void CWAItemManage::OnBnClickedCheckgroup()
{
	if(checkGroup.GetCheck()==1)
	{
		checkSelect.SetCheck(0);

		GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_HIDE);

		multStatus=2;
	}
	else
	{
		GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLNICK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITNICK)->ShowWindow(SW_SHOW);

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
		multStatus=0;
	}
}

//ѡ��������ӵ��ߵĽ�ɫ�ļ���
void CWAItemManage::OnBnClickedBtnbrowse()
{
	char path[256];
	GetCurrentDirectory(256,path);
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����

	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,"�ļ�����(*.txt)|*.txt||");

	if(lpszOpenFile->DoModal()==IDOK)//�������Ի���ȷ����ť
	{
		CString szGetName;
		szGetName=lpszOpenFile->GetPathName();
		SetDlgItemText(IDC_EDITPATH,szGetName);
		SetCurrentDirectory(path);
	}
	delete lpszOpenFile;
}

//��ѯ����������Ϣ
void CWAItemManage::SearchItemType()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ItemType_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","IM_Error_SearchItemType"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//��ѯ��Ӧ���͵ĵ�����Ϣ
void CWAItemManage::OnBnClickedBtnitemlist()
{
	try
	{		
		CIni mIni;

		//int index = theApp.operWA.ReadIntValue("MWA","index");
		//int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");
		cmbList.ResetContent();

		CString ItemType;
		GetDlgItemText(IDC_CMBTYPE,ItemType);//��ȡ��������
		if(ItemType == "")//�������Ͳ���Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_ItemTypeNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		ItemName="";
		GetDlgItemText(IDC_EDITNEW,ItemName);//��ȡģ��������
		
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

		socketdata.AddTFLV(CEnumCore::TagName::WA_ItemType,CEnumCore::TagFormat::TLV_STRING,strlen(ItemType),(unsigned char *)mIni.wcharToChar(ItemType));//��������
		socketdata.AddTFLV(CEnumCore::TagName::WA_itemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//ģ��������

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_ItemList_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","IM_Error_SearchItemName"),theApp.operWA.ReadValue("MWA","Error"),0);
	}	
}

//������б�����ӵ���
void CWAItemManage::OnBnClickedBtnadd()
{
	try
	{
		CString ItemName = "";		
		GetDlgItemText(IDC_CMBITEM,ItemName);//��ȡ��������
		if(ItemName == "")//�������Ʋ���Ϊ��
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_ItemNameNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ItemList.Lookup(cmbList.GetCurSel()+1,ItemID);//��CMap��Ķ���ItemList�л�ȡ����ID

		CString ItemQuality = "";
		GetDlgItemText(IDC_CMBQUALITY,ItemQuality);//��ȡ����Ʒ��

		CString ItemTime = "0";
		GetDlgItemText(IDC_EDITTIME,ItemTime);//��ȡ����ʱЧ

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_ItemNumNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		/*if(itemNum>5)
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_ItemNum"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}*/

		CIni mIni;

		int nRow = 0;
		char strInt[10];
		ZeroMemory(strInt,10);
		if(nFirst == 0)
		{
			nFirst = 1;

			DWORD dwStyle = listItem.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
			listItem.SetExtendedStyle(dwStyle); //������չ���

			listItem.InsertColumn(0,theApp.operWA.ReadValue("MWA","IM_ITEM_ITEMID"),LVCFMT_CENTER,60,-1);
			listItem.InsertColumn(1,theApp.operWA.ReadValue("MWA","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,80,-1);
		    listItem.InsertColumn(2,theApp.operWA.ReadValue("MWA","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,60,-1);
			listItem.InsertColumn(3,theApp.operWA.ReadValue("MWA","IM_ITEM_ITEMQULITY"),LVCFMT_CENTER,60,-1);
			listItem.InsertColumn(4,theApp.operWA.ReadValue("MWA","IM_ITEM_ITEMTIME"),LVCFMT_CENTER,60,-1);

			nRow=listItem.InsertItem(0,ItemID);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
			listItem.SetItemText(nRow,3,ItemQuality);
			listItem.SetItemText(nRow,4,ItemTime);
		}
		else
		{
			/*int itemCount = 0;
			for(int i=0;i<listItem.GetItemCount();i++)
			{
				itemCount += atoi((LPCSTR)mIni.wcharToChar(listItem.GetItemText(i,2)));
			}
			if((itemCount + itemNum)>5)
			{
				MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_ItemNum"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}*/
			int itemCount = listItem.GetItemCount();
			if(itemCount >= 5)
			{
				MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_ItemType"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			nRow=listItem.InsertItem(0,ItemID);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
			listItem.SetItemText(nRow,3,ItemQuality);
			listItem.SetItemText(nRow,4,ItemTime);
		}
	}
	catch(...)
	{
	}
}

//���������б����к�
void CWAItemManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
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
void CWAItemManage::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
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
void CWAItemManage::OnBnClickedBtndelete()
{
	if((listItem.GetItemCount() != 0) && (nSelectItem >= 0))
	{
		listItem.DeleteItem(nSelectItem);
	}
}

//�޸Ļ������Ϣ
void CWAItemManage::OnBnClickedBtnedit()
{
	switch(tbcResult.GetCurSel())
	{
	case 4:
		{
			nSelectItem=0;
			if(multStatus > 0) 
			{
				CString m_ServerName;
				GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������
				if(m_ServerName == "")//��Ϸ������Ϊ��
				{
					return;
				}
				ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
			}
			if(multStatus == 1) 
			{
				//��ȡҪ������ӵĽ�ɫ��txt�ļ�				
				CString filename="";				
				GetDlgItemText(IDC_EDITPATH,filename);	

				CStdioFile nFile;
				if(!nFile.Open(filename,CFile::typeBinary))
				{
					MessageBox(theApp.operWA.ReadValue("MWA","IM_Error_ReadFile"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}				
				UserNum = 0;
				UserNick = "";
				nFile.ReadString(UserNick);
				while(nFile.ReadString(UserNick) != false && UserNick.GetLength() != 0)
				{
					UserNick = UserNick.TrimLeft();
					UserNick = UserNick.TrimRight();
					UserNum++;
					UserList.SetAt(UserNum,UserNick);//����ɫ��������CMap��Ķ���UserList��
				}
				nFile.Close();

				if(UserNum == 0)
					return;

				ShowNewItem(SW_HIDE);				
				GetDlgItem(IDUISEARCH)->ShowWindow(SW_HIDE);
				GetDlgItem(IDUICANCEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TABUIRESULT)->ShowWindow(SW_HIDE);

				multStatus=1;
				GetDlgItem(IDC_BTNRECOVER)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_LBLMAIN)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_PROGRESSMAIL)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLPROG)->ShowWindow(SW_SHOW);
				
				CString tmpNum = "";
				tmpNum.Format("%i",UserNum);
				SetDlgItemText(IDC_LBLMAIN,theApp.operWA.ReadValue("MWA","IM_UI_LblMain")+tmpNum);
				SetDlgItemText(IDC_LBLPROG,"");	

				progMail.SetPos(0);
				progMail.SetRange(0,UserNum);
				progMail.SetStep(1);

				mCurNum = 1;
				UserNick = "";
				UserList.Lookup(mCurNum,UserNick);//��CMap��Ķ���UserList�л�ȡ��ɫ��
				AddItem();
			}
			else
			{
				UserNick = "";
				if(multStatus==0)//��ָ�������ӵ���
				{
					GetDlgItemText(IDC_EDITNICK,UserNick);//��ȡ��ɫ��
					if(UserNick == "")
					{
						MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_RoleNameNull"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
						return;
					}
				}
				AddItem();
			}
		}		
		break;
	case 5:
		EditMoney();
		break;
	default:
		break;
	}	
}

//������Ⱥ������µ���
void CWAItemManage::AddItem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");
		
		///////////////////ȡ�ʼ�����///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_EDMAILSUBJECT,m_strSubject);
		if(m_strSubject == "")
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_MailSubject"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(strlen(m_strSubject) > 20)//�ʼ����ⲻ�ܳ���20���ַ�
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_SubjectTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}

		CString m_strContent;
		GetDlgItemText(IDC_EDMAILCONTENT,m_strContent);
		if(m_strContent == "")
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_MailContent"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(strlen(m_strContent) > 200)//�ʼ����ݲ��ܳ���200���ַ�
		{
			MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_ContentTooLong"),theApp.operWA.ReadValue("MWA","Warn"),0);
			return;
		}

		int iMoney=0;
		iMoney=GetDlgItemInt(IDC_EDMAILMONEY);

		int itemCount = listItem.GetItemCount();//Ҫ��ӵ��ߵ�����
		//if(itemCount == 0)//Ҫ��ӵĵ��߲���Ϊ��
		//{
		//	MessageBox(theApp.operWA.ReadValue("MWA","IM_HINT_ADDITEM"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
		//	return;
		//}

		ItemID="";
		ItemName="";
		CString ItemNum="";
		CString ItemQuality="";
		CString ItemTime = "";

		for(int i=0;i<itemCount;i++)
		{
			ItemID += listItem.GetItemText(i,0);
			ItemID += ";";
			ItemName += listItem.GetItemText(i,1);
			ItemName += ";";
			ItemNum += listItem.GetItemText(i,2);
			ItemNum += ";";
			if(listItem.GetItemText(i,3) == theApp.operWA.ReadValue("MWA","IM_UI_WHITE"))
			{
				ItemQuality += "0;";
			}
			else if(listItem.GetItemText(i,3) == theApp.operWA.ReadValue("MWA","IM_UI_BLUE"))
			{
				ItemQuality += "1;";
			}
			else if(listItem.GetItemText(i,3) == theApp.operWA.ReadValue("MWA","IM_UI_PURPLE"))
			{
				ItemQuality += "2;";
			}
			else if(listItem.GetItemText(i,3) == theApp.operWA.ReadValue("MWA","IM_UI_ORANGE"))
			{
				ItemQuality += "3;";
			}
			ItemTime += listItem.GetItemText(i,4);
			ItemTime += ";";
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,20);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

		socketdata.AddTFLV(CEnumCore::TagName::WA_ItemID,CEnumCore::TagFormat::TLV_STRING,strlen(ItemID),(unsigned char *)mIni.wcharToChar(ItemID));//����ID
		socketdata.AddTFLV(CEnumCore::TagName::WA_itemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��������
		socketdata.AddTFLV(CEnumCore::TagName::WA_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(ItemNum),(unsigned char *)mIni.wcharToChar(ItemNum));//��������

		if(multStatus == 2)
			_itoa(1,strInt,10);//Ⱥ���ʼ�
		else
			_itoa(0,strInt,10);//��ָ����ҷ����ʼ�
		socketdata.AddTFLV(CEnumCore::TagName::WA_MailTag,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�Ƿ�Ⱥ���ʼ�

		socketdata.AddTFLV(CEnumCore::TagName::WA_ItemGen,CEnumCore::TagFormat::TLV_STRING,strlen(ItemQuality),(unsigned char *)mIni.wcharToChar(ItemQuality));//����Ʒ��
		socketdata.AddTFLV(CEnumCore::TagName::WA_ItemExpire,CEnumCore::TagFormat::TLV_STRING,strlen(ItemTime),(unsigned char *)mIni.wcharToChar(ItemTime));//����ʱЧ

		socketdata.AddTFLV(CEnumCore::TagName::WA_MailSubject,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));//�ʼ�����
		socketdata.AddTFLV(CEnumCore::TagName::WA_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));//�ʼ�����
		
		_itoa(iMoney,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::WA_SendMoney,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ͽ�Ǯ

		int midlength = socketdata.EnBody();
		theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_MailItem);//����µ���

		if(multStatus!=1)
			::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_AddItem"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

//�޸Ľ�Ǯ����
void CWAItemManage::EditMoney()
{
	try
	{		
		CIni mIni;

		int index = theApp.operWA.ReadIntValue("MWA","index");
		int iPageSize = theApp.operWA.ReadIntValue("MWA","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CString newMoney;
			GetDlgItemText(IDC_EDITNEW,newMoney);//�޸ĺ�Ľ�Ǯ����
			if(newMoney == "")//�޸ĺ�Ľ�Ǯ��������Ϊ��
			{
				MessageBox(theApp.operWA.ReadValue("MWA","IM_Warn_MoneyNum"),theApp.operWA.ReadValue("MWA","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::WA_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::WA_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_UserNick,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�
			socketdata.AddTFLV(CEnumCore::TagName::WA_NickID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

			CString CurMoney = theApp.operWA.GetValueByColName(&listUser, nItem, theApp.operWA.ReadValue("MWA","WA_Money"));// ����ԭ�еĽ�Ǯ����

			socketdata.AddTFLV(CEnumCore::TagName::WA_CurMoney,CEnumCore::TagFormat::TLV_STRING,strlen(CurMoney),(unsigned char *)mIni.wcharToChar(CurMoney));//ԭ�еĽ�Ǯ����
			socketdata.AddTFLV(CEnumCore::TagName::WA_Money,CEnumCore::TagFormat::TLV_STRING,strlen(newMoney),(unsigned char *)mIni.wcharToChar(newMoney));//��Ǯ����

			int midlength = socketdata.EnBody();
			theApp.operWA.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Money_Update);//��Ǯ�޸�

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operWA.ReadIntValue("MWA","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operWA.ReadValue("MWA","UIC_Error_EditMoney"),theApp.operWA.ReadValue("MWA","Error"),0);
	}
}

//������Ϣ
void CWAItemManage::OnBnClickedBtnrecover()
{
	listItem.DeleteAllItems();
	while(listItem.DeleteColumn(0)){}
	nFirst = 0;
	SetDlgItemText(IDC_EDITNEW,"");
	cmbQuality.SetCurSel(0);
	SetDlgItemText(IDC_EDITITEMNUM,"1");
	SetDlgItemText(IDC_EDITTIME,"0");
	SetDlgItemText(IDC_EDMAILSUBJECT,"");
	SetDlgItemText(IDC_EDMAILCONTENT,"");
	SetDlgItemText(IDC_EDMAILMONEY,"0");

	mCurNum = UserNum;
	progMail.SetPos(mCurNum-1);
}

// ���շ�����Ϣ
LRESULT CWAItemManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operWA.ReadIntValue("MWA","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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
			theApp.operWA.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
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
	case CEnumCore::Message_Tag_ID::WA_BodyItemInfo_Query_Resp://��ѯ���������Ʒ�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::WA_BagItemInfo_Query_Resp://��ѯ��ұ�����Ʒ�Ļ�Ӧ
	case CEnumCore::Message_Tag_ID::WA_BankItemInfo_Query_Resp://��ѯ���������Ʒ�Ļ�Ӧ
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operWA.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
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
	case CEnumCore::Message_Tag_ID::WA_ItemType_Query_Resp://��ѯ����������Ϣ
		{
			theApp.operWA.BuildCombox(&socketdata,&cmbType,1);//�������������Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_ItemList_Query_Resp://��ѯ���еĵ�����Ϣ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ItemID = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::WA_ItemID).lpdata;//�õ�����ID
				ItemList.SetAt(i,ItemID);//������ID������CMap��Ķ���ItemList��
			}
			theApp.operWA.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::WA_itemName);//���������Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::WA_MailItem_Resp://��ӵ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString Result = (LPCTSTR)&m_tflv.lpdata;
			if(multStatus == 1) 
			{
				CString tmpNum="";
				if(mCurNum<UserNum)
				{					
					tmpNum.Format("%i",mCurNum);
					SetDlgItemText(IDC_LBLPROG,theApp.operWA.ReadValue("MWA","IM_UI_LblMailFirst")+tmpNum+theApp.operWA.ReadValue("MWA","IM_UI_LblMailSecond")+UserNick+theApp.operWA.ReadValue("MWA","IM_UI_LblMailThird")+Result+theApp.operWA.ReadValue("MWA","IM_UI_LblMailFourth"));	
					progMail.StepIt();

					mCurNum++;
					UserList.Lookup(mCurNum,UserNick);//��CMap��Ķ���UserList�л�ȡ��ɫ��					

					AddItem();
					return false;					
				}
				if(!UserList.IsEmpty())
				{
					UserList.RemoveAll();
				}
				tmpNum.Format("%i",mCurNum);
				SetDlgItemText(IDC_LBLPROG,theApp.operWA.ReadValue("MWA","IM_UI_LblMailFirst")+tmpNum+theApp.operWA.ReadValue("MWA","IM_UI_LblMailSecond")+UserNick+theApp.operWA.ReadValue("MWA","IM_UI_LblMailThird")+Result+theApp.operWA.ReadValue("MWA","IM_UI_LblMailFourth"));	
				progMail.StepIt();

				theApp.operWA.ShowResult(Result);//��ʾ���ؽ��
				OnBnClickedBtnrecover();

				GetDlgItem(IDC_LBLMAIN)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_PROGRESSMAIL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLPROG)->ShowWindow(SW_HIDE);

				ShowNewItem(SW_SHOW);
				checkSelect.SetCheck(0);
				checkGroup.SetCheck(0);				
				multStatus=0;

				GetDlgItem(IDC_TABUIRESULT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDUISEARCH)->ShowWindow(SW_SHOW);
				GetDlgItem(IDUICANCEL)->ShowWindow(SW_SHOW);
			}
			else
			{
				theApp.operWA.ShowResult(Result);//��ʾ���ؽ��
				OnBnClickedBtnrecover();
			}
		}
		break;
	default:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operWA.ShowResult(result);//��ʾ���ؽ��
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//�����û�������Ϣ��������������
void CWAItemManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operWA.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CWAItemManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operWA.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CWAItemManage::OnBnClickedUicancel()
{
	ShowItemInfo(SW_HIDE);
	ShowNewItem(SW_HIDE);		
	ShowUserInfo(SW_SHOW);

	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void CWAItemManage::OnClose()
{
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!ItemList.IsEmpty())
	{
		ItemList.RemoveAll();
	}
	if(!UserList.IsEmpty())
	{
		UserList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

//�����ݼ���Ӧ����
BOOL CWAItemManage::PreTranslateMessage(MSG* pMsg)
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

void CWAItemManage::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(m_cmdShow);
}

void CWAItemManage::ShowItemInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITITEM,"");
}

void CWAItemManage::ShowNewItem(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operWA.ReadValue("MWA","IM_UI_lblItemType"));
	SetDlgItemText(IDC_LBLNEW,theApp.operWA.ReadValue("MWA","IM_UI_lblBIItem"));
	SetDlgItemText(IDC_LBLITEMNAME,theApp.operWA.ReadValue("MWA","IM_UI_lblItemInfo"));	
	SetDlgItemText(IDC_LBLTOADDITEM,theApp.operWA.ReadValue("MWA","IM_UI_lblItemList"));
	SetDlgItemText(IDC_BTNITEMLIST,theApp.operWA.ReadValue("MWA","IM_UI_btnItemList"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operWA.ReadValue("MWA","IM_UI_BTNSEND"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operWA.ReadValue("MWA","AM_UI_Reset"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operWA.ReadValue("MWA","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITNEW,"");

	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLITEMNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITITEMNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLQUALITY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBQUALITY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLTIME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITTIME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSECOND)->ShowWindow(m_cmdShow);
	CEditNew.ModifyStyle(ES_NUMBER,0);
	SetDlgItemText(IDC_EDITITEMNUM,"1");
	
	GetDlgItem(IDC_LBLMAILSUBJECT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILSUBJECT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILCONTENT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILCONTENT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILMONEY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILMONEY)->ShowWindow(m_cmdShow);
	SetDlgItemText(IDC_EDITTIME,"0");
	SetDlgItemText(IDC_EDMAILMONEY,"0");

	GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKBATCH)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CHECKGROUP)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLTOADDITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNADD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELETE)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_BTNITEMLIST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//���µ���ҳ�����ز�����ֵ
void CWAItemManage::NewItemValue()
{
	cmbType.ResetContent();
	cmbList.ResetContent();

	checkSelect.SetCheck(0);
	checkGroup.SetCheck(0);
	
	multStatus=0;
}

void CWAItemManage::ShowMoneyInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operWA.ReadValue("MWA","AM_UI_Type"));
	SetDlgItemText(IDC_LBLNEW,theApp.operWA.ReadValue("MWA","IM_UI_NewValue"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operWA.ReadValue("MWA","AM_UI_Edit"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operWA.ReadValue("MWA","AM_UI_Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITNEW,"");
	cmbType.ResetContent();
	cmbType.AddString(theApp.operWA.ReadValue("MWA","IM_Warn_BODYMONEY"));
	cmbType.SetCurSel(0);
	//cmbType.AddString(theApp.operWA.ReadValue("MWA","IM_Warn_BANKMONEY"));
	CEditNew.ModifyStyle(0,ES_NUMBER);
	
	GetDlgItem(IDC_LBLACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLOLD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITACCOUNT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNICK)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}
