// XDItemManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_XD.h"
#include "XDItemManage.h"


// CXDItemManage �Ի���

IMPLEMENT_DYNAMIC(CXDItemManage, CDialog)
CXDItemManage::CXDItemManage(CWnd* pParent /*=NULL*/)
	: CDialog(CXDItemManage::IDD, pParent)
{
}

CXDItemManage::~CXDItemManage()
{
}

void CXDItemManage::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CXDItemManage, CDialog)
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


// CXDItemManage ��Ϣ�������

// ��ʼ���Ի���
BOOL CXDItemManage::OnInitDialog()
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

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	if(theApp.operXD.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CXDItemManage::InitUI()
{
	SetWindowText(theApp.operXD.ReadValue("MXD","IM_UI_ITEMMANAGE"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operXD.ReadValue("MXD","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operXD.ReadValue("MXD","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operXD.ReadValue("MXD","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operXD.ReadValue("MXD","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operXD.ReadValue("MXD","UIC_UI_Page"));

	tbcResult.InsertItem(0,theApp.operXD.ReadValue("MXD","UIC_UI_tpgUserInfo"));
	tbcResult.InsertItem(1,theApp.operXD.ReadValue("MXD","IC_UI_Avatar"));
	tbcResult.InsertItem(2,theApp.operXD.ReadValue("MXD","IC_UI_PackItem"));
	tbcResult.InsertItem(3,theApp.operXD.ReadValue("MXD","IC_UI_BankItem"));
	tbcResult.InsertItem(4,theApp.operXD.ReadValue("MXD","IM_UI_tpgAddItem"));
	tbcResult.InsertItem(5,theApp.operXD.ReadValue("MXD","IM_UI_tpgEditMoney"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLNICK,theApp.operXD.ReadValue("MXD","UIC_UI_lblNick"));
	SetDlgItemText(IDC_LBLITEM,theApp.operXD.ReadValue("MXD","IM_UI_lblItemName"));
	SetDlgItemText(IDC_LBLNUM,theApp.operXD.ReadValue("MXD","IM_UI_lblItemNum"));
	SetDlgItemText(IDC_BTNDELITEM,theApp.operXD.ReadValue("MXD","IM_UI_DELITEM"));

	SetDlgItemText(IDC_CHECKBATCH,theApp.operXD.ReadValue("MXD","IM_UI_CHECKMULT"));
	SetDlgItemText(IDC_CHECKGROUP,theApp.operXD.ReadValue("MXD","IM_UI_CHECKGROUP"));
	SetDlgItemText(IDC_BTNBROWSE,theApp.operXD.ReadValue("MXD","IM_UI_BTNBROWSE"));

	SetDlgItemText(IDC_LBLSENDER,theApp.operXD.ReadValue("MXD","IM_UI_Sender"));
	SetDlgItemText(IDC_LBLQUALITY,theApp.operXD.ReadValue("MXD","IM_UI_ITEMQUALITY"));
	SetDlgItemText(IDC_LBLMAILSUBJECT2,theApp.operXD.ReadValue("MXD","IM_UI_LBLMAILSUBJECT"));
	SetDlgItemText(IDC_LBLMAILCONTENT2,theApp.operXD.ReadValue("MXD","IM_UI_LBLMAILCONTENT"));
	SetDlgItemText(IDC_LBLMAILMONEY,theApp.operXD.ReadValue("MXD","IM_UI_MONEY"));

	SetDlgItemText(IDC_LBLDELNUM,theApp.operXD.ReadValue("MXD","IM_UI_lblItemNum"));

	SetDlgItemText(IDC_LBLATTRID,theApp.operXD.ReadValue("MXD","IM_UI_ATTRID"));
	SetDlgItemText(IDC_LBLATTRVALUE,theApp.operXD.ReadValue("MXD","IM_UI_ATTRVALUE"));
	SetDlgItemText(IDC_LBLADDLEVEL,theApp.operXD.ReadValue("MXD","IM_UI_ADDLEVEL"));
	SetDlgItemText(IDC_LBLADDTYPE,theApp.operXD.ReadValue("MXD","IM_UI_ADDTYPE"));
	SetDlgItemText(IDC_LBLADDVALUE,theApp.operXD.ReadValue("MXD","IM_UI_ADDVALUE"));
	SetDlgItemText(IDC_LBLADDVALUELAST,theApp.operXD.ReadValue("MXD","IM_UI_ADDVALUELAST"));
	SetDlgItemText(IDC_LBLSTAR,theApp.operXD.ReadValue("MXD","IM_UI_STAR"));
	SetDlgItemText(IDC_LBLPLUGIN,theApp.operXD.ReadValue("MXD","IM_UI_PLUGIN"));
	SetDlgItemText(IDC_LBLSLOTNUM,theApp.operXD.ReadValue("MXD","IM_UI_SLOTNUM"));
	SetDlgItemText(IDC_LBLSLOT1,theApp.operXD.ReadValue("MXD","IM_UI_SLOT1"));
	SetDlgItemText(IDC_LBLSLOT2,theApp.operXD.ReadValue("MXD","IM_UI_SLOT2"));
	SetDlgItemText(IDC_LBLSLOT3,theApp.operXD.ReadValue("MXD","IM_UI_SLOT3"));
	SetDlgItemText(IDC_LBLAPTITUDE,theApp.operXD.ReadValue("MXD","IM_UI_APTITUDE"));
	SetDlgItemText(IDC_LBLBIND,theApp.operXD.ReadValue("MXD","IM_UI_BIND"));

	SetDlgItemText(IDC_EDITATTRID,"-1");
	SetDlgItemText(IDC_EDITATTRVALUE,"-1");
	SetDlgItemText(IDC_EDITADDLEVEL,"-1");
	SetDlgItemText(IDC_EDITADDTYPE,"-1");
	SetDlgItemText(IDC_EDITADDVALUE,"-1");
	SetDlgItemText(IDC_EDITADDVALUELAST,"-1");
	SetDlgItemText(IDC_EDITSTAR,"-1");
	SetDlgItemText(IDC_EDITPLUGIN,"-1");
	SetDlgItemText(IDC_EDITSLOTNUM,"-1");
	SetDlgItemText(IDC_EDITSLOT1,"-1");
	SetDlgItemText(IDC_EDITSLOT2,"-1");
	SetDlgItemText(IDC_EDITSLOT3,"-1");
	SetDlgItemText(IDC_EDITAPTITUDE,"-1");
	SetDlgItemText(IDC_EDITBIND,"-1");

	//cmbQuality.AddString(theApp.operXD.ReadValue("MXD","IM_UI_WHITE"));
	//cmbQuality.AddString(theApp.operXD.ReadValue("MXD","IM_UI_BLUE"));
	//cmbQuality.AddString(theApp.operXD.ReadValue("MXD","IM_UI_PURPLE"));
	//cmbQuality.AddString(theApp.operXD.ReadValue("MXD","IM_UI_ORANGE"));
	//cmbQuality.SetCurSel(0);

	SetDlgItemText(IDC_LBLMAIN,theApp.operXD.ReadValue("MXD","IM_UI_LblMain"));
	SetDlgItemText(IDC_LBLPROG,theApp.operXD.ReadValue("MXD","IM_UI_LblMailFirst")+theApp.operXD.ReadValue("MXD","IM_UI_LblMailSecond")+theApp.operXD.ReadValue("MXD","IM_UI_LblMailThird")+theApp.operXD.ReadValue("MXD","IM_UI_LblMailFourth"));
}

// �Զ��ı��С
void CXDItemManage::OnSize(UINT nType, int cx, int cy)
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
HBRUSH CXDItemManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

//��ȡѡ���ServerIP
void CXDItemManage::OnCbnSelchangeCmbuiserver()
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
void CXDItemManage::OnBnClickedUisearch()
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
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_SelectServer"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITUINICK,UserNick);//��ȡ����ǳ�
		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","UIC_Warn_InputAccount"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}

// ��ѯ���������Ϣ
void CXDItemManage::UserInfo()
{	
	try
	{		
		CIni mIni;		

		int index = theApp.operXD.ReadIntValue("MXD","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbUPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen("1"),(unsigned char *)mIni.wcharToChar("1"));//��������

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_UserInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

// ��ҳ��ѯ���������Ϣ
void CXDItemManage::OnCbnSelchangeCmbuserpage()
{	
	try
	{	
		if(pageUInfo)//������Է�ҳ�Ļ�
		{
			CIni mIni;
			//OperationWA theApp.operXD;	

			int index = cmbUPage.GetCurSel() + 1;//ҳ��ΪcmbUPage��ǰ������ֵ��1��Ҳ����cmbUPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");//ÿҳ��ʾ50����¼

			while(listUser.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_SEARCHTYPE,CEnumCore::TagFormat::TLV_STRING,strlen("1"),(unsigned char *)mIni.wcharToChar("1"));//��������

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::WA_Account_Query );//���Ͳ�ѯ���������Ϣ������

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

// �����û��б��浱ǰ�к�
void CXDItemManage::OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
void CXDItemManage::OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult)
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
					UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// ����ѡ�е�����ʺ�
					//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// ����ѡ�е����ID
					UserNick = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// ����ѡ�е�����ǳ�

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
void CXDItemManage::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	pageInfo = false;
	cmbPage.ResetContent();
	while(listResult.DeleteColumn(0)){}// �������б��е���������

	UserName = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Account"));// ����ѡ�е�����ʺ�
	//UserID = theApp.operXD.GetValueByColName(&listBasic, nItem, theApp.operXD.ReadValue("MXD","WA_NickID"));// ����ѡ�е����ID
	UserNick = theApp.operXD.GetValueByColName(&listUser, nItem, theApp.operXD.ReadValue("MXD","XDJG_Character"));// ����ѡ�е�����ǳ�

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
			ShowUserInfo(SW_HIDE);
			ShowNewItem(SW_HIDE);
			ShowItemInfo(SW_SHOW);

			GetDlgItem(IDC_LBLITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLDELNUM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITDELNUM)->ShowWindow(SW_HIDE);
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

			GetDlgItem(IDC_LBLITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITITEM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLDELNUM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDITDELNUM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTNDELITEM)->ShowWindow(SW_HIDE);

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
	}
	*pResult = 0;
}

// ��ѯ��ɫ������Ϣ
void CXDItemManage::ItemInfo()
{	
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
			
			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

			int midlength = socketdata.EnBody();
			if(tbcResult.GetCurSel()==1)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemBody_Query);//������Ʒ��Ϣ
			else if(tbcResult.GetCurSel()==2)	
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Itembackpack_Query);//������Ʒ��Ϣ
			else if(tbcResult.GetCurSel()==3)	
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemStorage_Query);//�ֿ���Ʒ��Ϣ

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

// ��ҳ���в�ѯ
void CXDItemManage::OnCbnSelchangeCmbuipage()
{	
	try
	{
		if(pageInfo)
		{
			CIni mIni;

			int index = cmbPage.GetCurSel() + 1;
			int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

			while(listResult.DeleteColumn(0)){}

			if((listUser.GetItemCount() > 0) && (nItem>=0))
			{
				CSocketData socketdata;
				socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
				char strInt[10];

				socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
				socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
				
				_itoa(index,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

				_itoa(iPageSize,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

				int midlength = socketdata.EnBody();
				if(tbcResult.GetCurSel()==1)
					theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemBody_Query);//������Ʒ��Ϣ
				else if(tbcResult.GetCurSel()==2)	
					theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_Itembackpack_Query);//������Ʒ��Ϣ
				else if(tbcResult.GetCurSel()==3)	
					theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemStorage_Query);//�ֿ���Ʒ��Ϣ

				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				socketdata.Destroy();
			}
		}		
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_ResultInfo"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//ѡ����Ӧ�ĵ�����Ϣ����ɾ��
void CXDItemManage::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
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
			ItemName = theApp.operXD.GetValueByColName(&listResult, nListItem, theApp.operXD.ReadValue("MXD","XDJG_ItemName"));// ����ѡ�еĵ�������
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
void CXDItemManage::OnBnClickedBtndelitem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listResult.GetItemCount() > 0) && (nListItem>=0))
		{		
			GetDlgItemText(IDC_EDITITEM,ItemName);//��ȡ��������
			if(ItemName == "")//Ҫɾ���ĵ������Ʋ���Ϊ��
			{
				MessageBox(theApp.operXD.ReadValue("MXD","IM_HINT_DELETEITEM"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			int ItemIndex = atoi(theApp.operXD.GetValueByColName(&listResult, nListItem, theApp.operXD.ReadValue("MXD","XDJG_ItemID")));// ����ѡ�еĵ������

			int ItemNum = -1;
			ItemNum = GetDlgItemInt(IDC_EDITDELNUM);

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
			
			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			_itoa(tbcResult.GetCurSel()-1,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemType,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ͣ�0�����ϣ�1��������2������

			_itoa(ItemIndex,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��������

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��������

			_itoa(ItemNum,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemNum,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//Ҫɾ���ĵ�������

			int midlength = socketdata.EnBody();
			theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemDel);//ɾ��������Ϣ

			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","IM_Error_DELETEITEM"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//ѡ���Ƿ�������ӵ���
void CXDItemManage::OnBnClickedCheckselect()
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

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","IM_UI_LBLPATH"));
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

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
		multStatus=0;
	}
}

//ѡ���Ƿ���ҪȺ������
void CXDItemManage::OnBnClickedCheckgroup()
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

		SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
		multStatus=0;
	}
}

//ѡ��������ӵ��ߵĽ�ɫ�ļ���
void CXDItemManage::OnBnClickedBtnbrowse()
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
void CXDItemManage::SearchItemType()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
		
		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemType_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","IM_Error_SearchItemType"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//��ѯ��Ӧ���͵ĵ�����Ϣ
void CXDItemManage::OnBnClickedBtnitemlist()
{
	try
	{
		CIni mIni;

		//int index = theApp.operXD.ReadIntValue("MXD","index");
		//int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");
		cmbList.ResetContent();

		CString ItemType;
		GetDlgItemText(IDC_CMBTYPE,ItemType);//��ȡ��������
		if(ItemType == "")//�������Ͳ���Ϊ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemTypeNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		ItemName="";
		GetDlgItemText(IDC_EDITNEW,ItemName);//��ȡģ��������
		
		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
		
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemType,CEnumCore::TagFormat::TLV_STRING,strlen(ItemType),(unsigned char *)mIni.wcharToChar(ItemType));//��������
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//ģ��������

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemNameLst_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","IM_Error_SearchItemName"),theApp.operXD.ReadValue("MXD","Error"),0);
	}	
}

//������б�����ӵ���
void CXDItemManage::OnBnClickedBtnadd()
{
	try
	{
		CString ItemName = "";		
		GetDlgItemText(IDC_CMBITEM,ItemName);//��ȡ��������
		if(ItemName == "")//�������Ʋ���Ϊ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNameNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ItemList.Lookup(cmbList.GetCurSel()+1,ItemID);//��CMap��Ķ���ItemList�л�ȡ����ID

		//CString ItemQuality = "";
		//GetDlgItemText(IDC_CMBQUALITY,ItemQuality);//��ȡ����Ʒ��

		int itemNum = GetDlgItemInt(IDC_EDITITEMNUM);
		if(itemNum == 0)
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNumNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		/*if(itemNum>5)
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNum"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}*/

		CString ATTRID = "";
		GetDlgItemText(IDC_EDITATTRID,ATTRID);//��������ID
		CString ATTRVALUE = "";
		GetDlgItemText(IDC_EDITATTRVALUE,ATTRVALUE);//��������ֵ
		CString ADDLEVEL = "";
		GetDlgItemText(IDC_EDITADDLEVEL,ADDLEVEL);//�����ȼ�
		CString ADDTYPE = "";
		GetDlgItemText(IDC_EDITADDTYPE,ADDTYPE);//��������
		CString ADDVALUE = "";
		GetDlgItemText(IDC_EDITADDVALUE,ADDVALUE);//����ֵ
		CString ADDVALUELAST = "";
		GetDlgItemText(IDC_EDITADDLEVEL,ADDVALUELAST);//�ϴ�����ֵ
		CString STAR = "";
		GetDlgItemText(IDC_EDITSTAR,STAR);//����
		CString PLUGIN = "";
		GetDlgItemText(IDC_EDITPLUGIN,PLUGIN);//��װID
		CString SLOTNUM = "";
		GetDlgItemText(IDC_EDITSLOTNUM,SLOTNUM);//�������
		CString SLOT1 = "";
		GetDlgItemText(IDC_EDITSLOT1,SLOT1);//���1
		CString SLOT2 = "";
		GetDlgItemText(IDC_EDITSLOT2,SLOT2);//���2
		CString SLOT3 = "";
		GetDlgItemText(IDC_EDITSLOT3,SLOT3);//���3
		CString APTITUDE = "";
		GetDlgItemText(IDC_EDITAPTITUDE,APTITUDE);//����
		CString BIND = "";
		GetDlgItemText(IDC_EDITBIND,BIND);//��

		int nRow = 0;
		char strInt[10];
		ZeroMemory(strInt,10);
		if(nFirst == 0)
		{
			nFirst = 1;

			DWORD dwStyle = listItem.GetExtendedStyle();
			dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
			listItem.SetExtendedStyle(dwStyle); //������չ���

			listItem.InsertColumn(0,theApp.operXD.ReadValue("MXD","IM_ITEM_ITEMID"),LVCFMT_CENTER,65,-1);
			listItem.InsertColumn(1,theApp.operXD.ReadValue("MXD","IM_ITEM_ITEMNAME"),LVCFMT_CENTER,120,-1);
		    listItem.InsertColumn(2,theApp.operXD.ReadValue("MXD","IM_ITEM_ITEMNUM"),LVCFMT_CENTER,65,-1);
			//listItem.InsertColumn(3,theApp.operXD.ReadValue("MXD","IM_ITEM_ITEMQULITY"),LVCFMT_CENTER,80,-1);
			listItem.InsertColumn(3,theApp.operXD.ReadValue("MXD","IM_UI_ATTRID"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(4,theApp.operXD.ReadValue("MXD","IM_UI_ATTRVALUE"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(5,theApp.operXD.ReadValue("MXD","IM_UI_ADDLEVEL"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(6,theApp.operXD.ReadValue("MXD","IM_UI_ADDTYPE"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(7,theApp.operXD.ReadValue("MXD","IM_UI_ADDVALUE"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(8,theApp.operXD.ReadValue("MXD","IM_UI_ADDVALUELAST"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(9,theApp.operXD.ReadValue("MXD","IM_UI_STAR"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(10,theApp.operXD.ReadValue("MXD","IM_UI_PLUGIN"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(11,theApp.operXD.ReadValue("MXD","IM_UI_SLOTNUM"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(12,theApp.operXD.ReadValue("MXD","IM_UI_SLOT1"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(13,theApp.operXD.ReadValue("MXD","IM_UI_SLOT2"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(14,theApp.operXD.ReadValue("MXD","IM_UI_SLOT3"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(15,theApp.operXD.ReadValue("MXD","IM_UI_APTITUDE"),LVCFMT_CENTER,40,-1);
			listItem.InsertColumn(16,theApp.operXD.ReadValue("MXD","IM_UI_BIND"),LVCFMT_CENTER,40,-1);

			nRow=listItem.InsertItem(0,ItemID);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);			
			//listItem.SetItemText(nRow,3,ItemQuality);
			listItem.SetItemText(nRow,3,ATTRID);
			listItem.SetItemText(nRow,4,ATTRVALUE);
			listItem.SetItemText(nRow,5,ADDLEVEL);
			listItem.SetItemText(nRow,6,ADDTYPE);
			listItem.SetItemText(nRow,7,ADDVALUE);
			listItem.SetItemText(nRow,8,ADDVALUELAST);
			listItem.SetItemText(nRow,9,STAR);
			listItem.SetItemText(nRow,10,PLUGIN);
			listItem.SetItemText(nRow,11,SLOTNUM);
			listItem.SetItemText(nRow,12,SLOT1);
			listItem.SetItemText(nRow,13,SLOT2);
			listItem.SetItemText(nRow,14,SLOT3);
			listItem.SetItemText(nRow,15,APTITUDE);
			listItem.SetItemText(nRow,16,BIND);
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
				MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNum"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}*/
			int itemCount = listItem.GetItemCount();
			if(itemCount >= 5)
			{
				MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemType"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}
			nRow=listItem.InsertItem(0,ItemID);
			listItem.SetItemText(nRow,1,ItemName);
			_itoa(itemNum,strInt,10);
			listItem.SetItemText(nRow,2,strInt);
			//listItem.SetItemText(nRow,3,ItemQuality);
			listItem.SetItemText(nRow,3,ATTRID);
			listItem.SetItemText(nRow,4,ATTRVALUE);
			listItem.SetItemText(nRow,5,ADDLEVEL);
			listItem.SetItemText(nRow,6,ADDTYPE);
			listItem.SetItemText(nRow,7,ADDVALUE);
			listItem.SetItemText(nRow,8,ADDVALUELAST);
			listItem.SetItemText(nRow,9,STAR);
			listItem.SetItemText(nRow,10,PLUGIN);
			listItem.SetItemText(nRow,11,SLOTNUM);
			listItem.SetItemText(nRow,12,SLOT1);
			listItem.SetItemText(nRow,13,SLOT2);
			listItem.SetItemText(nRow,14,SLOT3);
			listItem.SetItemText(nRow,15,APTITUDE);
			listItem.SetItemText(nRow,16,BIND);
		}
	}
	catch(...)
	{
	}
}

//���������б����к�
void CXDItemManage::OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult)
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
void CXDItemManage::OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult)
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
void CXDItemManage::OnBnClickedBtndelete()
{
	if((listItem.GetItemCount() != 0) && (nSelectItem >= 0))
	{
		listItem.DeleteItem(nSelectItem);
	}
}

//�޸Ļ������Ϣ
void CXDItemManage::OnBnClickedBtnedit()
{
	switch(tbcResult.GetCurSel())
	{
	case 4:
		//{
		//	nItemCount = listItem.GetItemCount();
		//	if(nItemCount == 0)
		//	{
		//		MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ItemNumNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
		//		return;
		//	}
		//	nSelectItem=0;
		//	AddItem();
		//}
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
					MessageBox(theApp.operXD.ReadValue("MXD","IM_Error_ReadFile"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
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
				SetDlgItemText(IDC_LBLMAIN,theApp.operXD.ReadValue("MXD","IM_UI_LblMain")+tmpNum);
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
						MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_RoleNameNull"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
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

//����µ���
void CXDItemManage::AddItem()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		CString SenderNick = "";
		GetDlgItemText(IDC_EDITSENDER,SenderNick);
		
		///////////////////ȡ�ʼ�����///////////////////////

		CString m_strSubject;
		GetDlgItemText(IDC_EDMAILSUBJECT2,m_strSubject);
		//if(m_strSubject == "")
		//{
		//	MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_MailSubject"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
		//	return;
		//}
		//if(strlen(m_strSubject) > 20)//�ʼ����ⲻ�ܳ���20���ַ�
		//{
		//	MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_SubjectTooLong"),theApp.operXD.ReadValue("MXD","Warn"),0);
		//	return;
		//}

		CString m_strContent;
		GetDlgItemText(IDC_EDMAILCONTENT2,m_strContent);
		//if(m_strContent == "")
		//{
		//	MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_MailContent"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
		//	return;
		//}
		//if(strlen(m_strContent) > 200)//�ʼ����ݲ��ܳ���200���ַ�
		//{
		//	MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_ContentTooLong"),theApp.operXD.ReadValue("MXD","Warn"),0);
		//	return;
		//}

		int iMoney=0;
		iMoney=GetDlgItemInt(IDC_EDMAILMONEY);

		int itemCount = listItem.GetItemCount();//Ҫ��ӵ��ߵ�����
		if(itemCount == 0)//Ҫ��ӵĵ��߲���Ϊ��
		{
			MessageBox(theApp.operXD.ReadValue("MXD","IM_HINT_ADDITEM"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		ItemID="";
		ItemName="";
		CString ItemNum="";
		//CString ItemQuality="";
		CString ATTRID = "";
		CString ATTRVALUE = "";
		CString ADDLEVEL = "";
		CString ADDTYPE = "";
		CString ADDVALUE = "";
		CString ADDVALUELAST = "";
		CString STAR = "";
		CString PLUGIN = "";
		CString SLOTNUM = "";
		CString SLOT1 = "";
		CString SLOT2 = "";
		CString SLOT3 = "";
		CString APTITUDE = "";
		CString BIND = "";

		for(int i=0;i<itemCount;i++)
		{
			ItemID += listItem.GetItemText(i,0);
			ItemID += ";";
			ItemName += listItem.GetItemText(i,1);
			ItemName += ";";
			ItemNum += listItem.GetItemText(i,2);
			ItemNum += ";";
			ATTRID += listItem.GetItemText(i,3);
			ATTRID += ";";
			ATTRVALUE += listItem.GetItemText(i,4);
			ATTRVALUE += ";";
			ADDLEVEL += listItem.GetItemText(i,5);
			ADDLEVEL += ";";
			ADDTYPE += listItem.GetItemText(i,6);
			ADDTYPE += ";";
			ADDVALUE += listItem.GetItemText(i,7);
			ADDVALUE += ";";
			ADDVALUELAST += listItem.GetItemText(i,8);
			ADDVALUELAST += ";";
			STAR += listItem.GetItemText(i,9);
			STAR += ";";
			PLUGIN += listItem.GetItemText(i,10);
			PLUGIN += ";";
			SLOTNUM += listItem.GetItemText(i,11);
			SLOTNUM += ";";
			SLOT1 += listItem.GetItemText(i,12);
			SLOT1 += ";";
			SLOT2 += listItem.GetItemText(i,13);
			SLOT2 += ";";
			SLOT3 += listItem.GetItemText(i,14);
			SLOT3 += ";";
			APTITUDE += listItem.GetItemText(i,15);
			APTITUDE += ";";
			BIND += listItem.GetItemText(i,16);
			BIND += ";";
			//if(listItem.GetItemText(i,3) == theApp.operXD.ReadValue("MXD","IM_UI_WHITE"))
			//{
			//	ItemQuality += "0;";
			//}
			//else if(listItem.GetItemText(i,3) == theApp.operXD.ReadValue("MXD","IM_UI_BLUE"))
			//{
			//	ItemQuality += "1;";
			//}
			//else if(listItem.GetItemText(i,3) == theApp.operXD.ReadValue("MXD","IM_UI_PURPLE"))
			//{
			//	ItemQuality += "2;";
			//}
			//else if(listItem.GetItemText(i,3) == theApp.operXD.ReadValue("MXD","IM_UI_ORANGE"))
			//{
			//	ItemQuality += "3;";
			//}
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,30);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
		
		int userbyID = theApp.UserByID;
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
		_itoa(0,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemID,CEnumCore::TagFormat::TLV_STRING,strlen(ItemID),(unsigned char *)mIni.wcharToChar(ItemID));//����ID
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemName,CEnumCore::TagFormat::TLV_STRING,strlen(ItemName),(unsigned char *)mIni.wcharToChar(ItemName));//��������
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_ItemNum,CEnumCore::TagFormat::TLV_STRING,strlen(ItemNum),(unsigned char *)mIni.wcharToChar(ItemNum));//��������

		//if(multStatus == 2)
		//	_itoa(1,strInt,10);//Ⱥ���ʼ�
		//else
		//	_itoa(0,strInt,10);//��ָ����ҷ����ʼ�
		//socketdata.AddTFLV(CEnumCore::TagName::WA_MailTag,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�Ƿ�Ⱥ���ʼ�
		//socketdata.AddTFLV(CEnumCore::TagName::WA_ItemGen,CEnumCore::TagFormat::TLV_STRING,strlen(ItemQuality),(unsigned char *)mIni.wcharToChar(ItemQuality));//����Ʒ��

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SendCharacter,CEnumCore::TagFormat::TLV_STRING,strlen(SenderNick),(unsigned char *)mIni.wcharToChar(SenderNick));//�������ǳ�
		
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_MailTitle,CEnumCore::TagFormat::TLV_STRING,strlen(m_strSubject),(unsigned char *)mIni.wcharToChar(m_strSubject));//�ʼ�����
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_MailContent,CEnumCore::TagFormat::TLV_STRING,strlen(m_strContent),(unsigned char *)mIni.wcharToChar(m_strContent));//�ʼ�����
		
		_itoa(iMoney,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_Money,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//���ͽ�Ǯ

		socketdata.AddTFLV(CEnumCore::TagName::XDJG_PropertyId,CEnumCore::TagFormat::TLV_STRING,strlen(ATTRID),(unsigned char *)mIni.wcharToChar(ATTRID));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_PropertyValue,CEnumCore::TagFormat::TLV_STRING,strlen(ATTRVALUE),(unsigned char *)mIni.wcharToChar(ATTRVALUE));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IncreaseNum,CEnumCore::TagFormat::TLV_STRING,strlen(ADDLEVEL),(unsigned char *)mIni.wcharToChar(ADDLEVEL));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IncreaseType,CEnumCore::TagFormat::TLV_STRING,strlen(ADDTYPE),(unsigned char *)mIni.wcharToChar(ADDTYPE));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IncreaseValue,CEnumCore::TagFormat::TLV_STRING,strlen(ADDVALUE),(unsigned char *)mIni.wcharToChar(ADDVALUE));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IncreaseEndValue,CEnumCore::TagFormat::TLV_STRING,strlen(ADDVALUELAST),(unsigned char *)mIni.wcharToChar(ADDVALUELAST));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_StarsLevel,CEnumCore::TagFormat::TLV_STRING,strlen(STAR),(unsigned char *)mIni.wcharToChar(STAR));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_AssemblyID,CEnumCore::TagFormat::TLV_STRING,strlen(PLUGIN),(unsigned char *)mIni.wcharToChar(PLUGIN));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_SlotNum,CEnumCore::TagFormat::TLV_STRING,strlen(SLOTNUM),(unsigned char *)mIni.wcharToChar(SLOTNUM));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_EquipSlotID1,CEnumCore::TagFormat::TLV_STRING,strlen(SLOT1),(unsigned char *)mIni.wcharToChar(SLOT1));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_EquipSlotID2,CEnumCore::TagFormat::TLV_STRING,strlen(SLOT2),(unsigned char *)mIni.wcharToChar(SLOT2));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_EquipSlotID3,CEnumCore::TagFormat::TLV_STRING,strlen(SLOT3),(unsigned char *)mIni.wcharToChar(SLOT3));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_QualityEquip,CEnumCore::TagFormat::TLV_STRING,strlen(APTITUDE),(unsigned char *)mIni.wcharToChar(APTITUDE));
		socketdata.AddTFLV(CEnumCore::TagName::XDJG_IsBind,CEnumCore::TagFormat::TLV_STRING,strlen(BIND),(unsigned char *)mIni.wcharToChar(BIND));		

		int midlength = socketdata.EnBody();
		theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_ItemAdd);//����µ���

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_AddItem"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//�޸Ľ�Ǯ����
void CXDItemManage::EditMoney()
{
	try
	{		
		CIni mIni;

		int index = theApp.operXD.ReadIntValue("MXD","index");
		int iPageSize = theApp.operXD.ReadIntValue("MXD","pageSize");

		if((listUser.GetItemCount() > 0) && (nItem>=0))
		{
			CString newMoney;
			GetDlgItemText(IDC_EDITNEW,newMoney);//�޸ĺ�Ľ�Ǯ����
			if(newMoney == "")//�޸ĺ�Ľ�Ǯ��������Ϊ��
			{
				MessageBox(theApp.operXD.ReadValue("MXD","IM_Warn_MoneyNum"),theApp.operXD.ReadValue("MXD","Warn"),MB_ICONWARNING+MB_OK);
				return;
			}

			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_ServerIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Account,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Character,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//��ҽ�ɫ��
			
			int userbyID = theApp.UserByID;
			_itoa(userbyID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����Աid

			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��
			_itoa(0,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ������

			socketdata.AddTFLV(CEnumCore::TagName::XDJG_Money,CEnumCore::TagFormat::TLV_STRING,strlen(newMoney),(unsigned char *)mIni.wcharToChar(newMoney));//��Ǯ����

			int midlength = socketdata.EnBody();
			if(cmbType.GetCurSel() == 0)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AddRoleBind_operate);//��ӽ�ɫ���Ͻ�Ǯ����(�󶨱�)
			else if(cmbType.GetCurSel() == 1)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_AddRoleNonBind_operate);//��ӽ�ɫ���Ͻ�Ǯ����(�ǰ󶨱�)
			else if(cmbType.GetCurSel() == 2)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_UpRoleBind_operate);//�޸Ľ�ɫ���Ͻ�Ǯ����(�󶨱�)
			else if(cmbType.GetCurSel() == 3)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_UpRoleNonBind_operate);//�޸Ľ�ɫ���Ͻ�Ǯ����(�ǰ󶨱�)
			else if(cmbType.GetCurSel() == 4)
				theApp.operXD.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::XDJG_MoneyAdd);//�����Ϸ��
			
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operXD.ReadIntValue("MXD","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operXD.ReadValue("MXD","UIC_Error_EditMoney"),theApp.operXD.ReadValue("MXD","Error"),0);
	}
}

//������Ϣ
void CXDItemManage::OnBnClickedBtnrecover()
{
	listItem.DeleteAllItems();
	while(listItem.DeleteColumn(0)){}
	nFirst = 0;
	SetDlgItemText(IDC_EDITNEW,"");
	cmbQuality.SetCurSel(0);
	SetDlgItemText(IDC_EDITITEMNUM,"1");
	//SetDlgItemText(IDC_EDITTIME,"0");
	SetDlgItemText(IDC_EDMAILSUBJECT2,"");
	SetDlgItemText(IDC_EDMAILCONTENT2,"");
	SetDlgItemText(IDC_EDMAILMONEY,"0");

	mCurNum = UserNum;
	progMail.SetPos(mCurNum-1);
}

// ���շ�����Ϣ
LRESULT CXDItemManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	CIni mIni;

	dlgStatus = theApp.operXD.ReadIntValue("MXD","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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
			theApp.operXD.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operXD.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

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
	case CEnumCore::Message_Tag_ID::XDJG_ItemType_Query_Resp://��ѯ����������Ϣ
		{
			theApp.operXD.BuildCombox(&socketdata,&cmbType,1);//�������������Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemNameLst_Query_Resp://��ѯ���еĵ�����Ϣ
		{
			for(int i = 1;i <= socketdata.getQueryNum();i++)
			{
				CString ItemID = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::XDJG_ItemID).lpdata;//�õ�����ID
				ItemList.SetAt(i,ItemID);//������ID������CMap��Ķ���ItemList��
			}
			theApp.operXD.BuildComboxs(&socketdata,&cmbList,CEnumCore::TagName::XDJG_ItemName);//���������Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemAdd_Resp://��ӵ�����Ϣ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString Result = (LPCTSTR)&m_tflv.lpdata;
			if(multStatus == 1) 
			{
				CString tmpNum="";
				if(mCurNum<UserNum)
				{					
					tmpNum.Format("%i",mCurNum);
					SetDlgItemText(IDC_LBLPROG,theApp.operXD.ReadValue("MXD","IM_UI_LblMailFirst")+tmpNum+theApp.operXD.ReadValue("MXD","IM_UI_LblMailSecond")+UserNick+theApp.operXD.ReadValue("MXD","IM_UI_LblMailThird")+Result+theApp.operXD.ReadValue("MXD","IM_UI_LblMailFourth"));	
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
				SetDlgItemText(IDC_LBLPROG,theApp.operXD.ReadValue("MXD","IM_UI_LblMailFirst")+tmpNum+theApp.operXD.ReadValue("MXD","IM_UI_LblMailSecond")+UserNick+theApp.operXD.ReadValue("MXD","IM_UI_LblMailThird")+Result+theApp.operXD.ReadValue("MXD","IM_UI_LblMailFourth"));	
				progMail.StepIt();

				theApp.operXD.ShowResult(Result);//��ʾ���ؽ��
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
				theApp.operXD.ShowResult(Result);//��ʾ���ؽ��
				OnBnClickedBtnrecover();
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::XDJG_ItemDel_Resp://����ɾ��
	case CEnumCore::Message_Tag_ID::XDJG_MoneyAdd_Resp://�����Ϸ��
	case CEnumCore::Message_Tag_ID::XDJG_AddRoleBind_operate_Resp://��ӽ�ɫ���Ͻ�Ǯ����(�󶨱�)
	case CEnumCore::Message_Tag_ID::XDJG_AddRoleNonBind_operate_Resp://��ӽ�ɫ���Ͻ�Ǯ����(�ǰ󶨱�)
	case CEnumCore::Message_Tag_ID::XDJG_UpRoleBind_operate_Resp://�޸Ľ�ɫ���Ͻ�Ǯ����(�󶨱�)
	case CEnumCore::Message_Tag_ID::XDJG_UpRoleNonBind_operate_Resp://�޸Ľ�ɫ���Ͻ�Ǯ����(�ǰ󶨱�)
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operXD.ShowResult(result);//��ʾ���ؽ��
		}
		break;
	default:
		{
			if(pageInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operXD.BuildDataTable(&socketdata,&listResult,&pageCount);//����CListCtrl����

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
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}

//�����û�������Ϣ��������������
void CXDItemManage::OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operXD.SortListInfo(&listUser,pNMHDR,pResult);
}

//���������Ϣ��������������
void CXDItemManage::OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operXD.SortListInfo(&listResult,pNMHDR,pResult);
}

// �رնԻ���
void CXDItemManage::OnBnClickedUicancel()
{
	ShowItemInfo(SW_HIDE);
	ShowNewItem(SW_HIDE);		
	ShowUserInfo(SW_SHOW);

	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

// �رնԻ���
void CXDItemManage::OnClose()
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
BOOL CXDItemManage::PreTranslateMessage(MSG* pMsg)
{
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

void CXDItemManage::ShowUserInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBUSERPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTCHARACTER)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(m_cmdShow);
}

void CXDItemManage::ShowItemInfo(int m_cmdShow)
{
	GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLDELNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITDELNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITITEM,"");
	SetDlgItemText(IDC_EDITDELNUM,"1");
}

void CXDItemManage::ShowNewItem(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","IM_UI_lblItemType"));
	SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","IM_UI_lblBIItem"));
	SetDlgItemText(IDC_LBLITEMNAME,theApp.operXD.ReadValue("MXD","IM_UI_lblItemInfo"));	
	SetDlgItemText(IDC_LBLTOADDITEM,theApp.operXD.ReadValue("MXD","IM_UI_lblItemList"));
	SetDlgItemText(IDC_BTNITEMLIST,theApp.operXD.ReadValue("MXD","IM_UI_btnItemList"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","IM_UI_BTNSEND"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));

	SetDlgItemText(IDC_LBLACCOUNT,theApp.operXD.ReadValue("MXD","UIC_UI_lblAccount"));
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
	CEditNew.ModifyStyle(ES_NUMBER,0);
	SetDlgItemText(IDC_EDITITEMNUM,"1");

	GetDlgItem(IDC_LBLSENDER)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSENDER)->ShowWindow(m_cmdShow);
	SetDlgItemText(IDC_EDITSENDER,theApp.operXD.ReadValue("MXD","IM_UI_SysMail"));
	//GetDlgItem(IDC_LBLQUALITY)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_CMBQUALITY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILSUBJECT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILSUBJECT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILCONTENT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILCONTENT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMAILMONEY)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDMAILMONEY)->ShowWindow(m_cmdShow);	
	SetDlgItemText(IDC_EDMAILMONEY,"0");

	GetDlgItem(IDC_LBLATTRID)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLATTRVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDLEVEL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLADDVALUELAST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSTAR)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPLUGIN)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSLOTNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSLOT1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSLOT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLSLOT3)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLAPTITUDE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLBIND)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_EDITATTRID)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITATTRVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDLEVEL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDTYPE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDVALUE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITADDVALUELAST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSTAR)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITPLUGIN)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSLOTNUM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSLOT1)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSLOT2)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITSLOT3)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITAPTITUDE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITBIND)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_EDITPATH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTNBROWSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKBATCH)->ShowWindow(m_cmdShow);
	//GetDlgItem(IDC_CHECKGROUP)->ShowWindow(m_cmdShow);
	multStatus=0;

	GetDlgItem(IDC_LBLTOADDITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTITEM)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNADD)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNDELETE)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_BTNITEMLIST)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNEDIT)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRECOVER)->ShowWindow(m_cmdShow);
}

//���µ���ҳ�����ز�����ֵ
void CXDItemManage::NewItemValue()
{
	cmbType.ResetContent();
	cmbList.ResetContent();

	checkSelect.SetCheck(0);
	checkGroup.SetCheck(0);
}	

void CXDItemManage::ShowMoneyInfo(int m_cmdShow)
{
	SetDlgItemText(IDC_LBLOLD,theApp.operXD.ReadValue("MXD","UM_UI_Type"));
	SetDlgItemText(IDC_LBLNEW,theApp.operXD.ReadValue("MXD","IM_UI_NewValue"));
	SetDlgItemText(IDC_BTNEDIT,theApp.operXD.ReadValue("MXD","Modify"));
	SetDlgItemText(IDC_BTNRECOVER,theApp.operXD.ReadValue("MXD","Reset"));

	SetDlgItemText(IDC_EDITACCOUNT,"");
	SetDlgItemText(IDC_EDITNICK,"");
	SetDlgItemText(IDC_EDITNEW,"");
	cmbType.ResetContent();
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_ADDBIND"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_ADDNONBIND"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_EDITBIND"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_EDITNONBIND"));
	cmbType.AddString(theApp.operXD.ReadValue("MXD","IM_UI_PLAYMONEY"));
	cmbType.SetCurSel(0);

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

