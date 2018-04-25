// PALGuildManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_PAL.h"
#include "PALGuildManage.h"
#include ".\palguildmanage.h"


// CPALGuildManage �Ի���

IMPLEMENT_DYNAMIC(CPALGuildManage, CDialog)
CPALGuildManage::CPALGuildManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPALGuildManage::IDD, pParent)
{
}

CPALGuildManage::~CPALGuildManage()
{
}

void CPALGuildManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBSERVER, cmbServer);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_TABRESULT, tbcResult);
	DDX_Control(pDX, IDC_GRPPAGE, GrpPage);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTGUILD, listGuild);
	DDX_Control(pDX, IDC_LISTMEMBER, listMember);
	DDX_Control(pDX, IDC_EDITNEW, txtGuildLvl);
	DDX_Control(pDX, IDC_CMBGUILDLVL, cmbLvl);
	DDX_Control(pDX, IDC_CMBMEMBERLVL, cmbMemberLvl);
}


BEGIN_MESSAGE_MAP(CPALGuildManage, CDialog)
	ON_BN_CLICKED(IDSEARCH, OnBnClickedSearch)
	ON_NOTIFY(NM_CLICK, IDC_LISTGUILD, OnNMClickListguild)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTGUILD, OnNMDblclkListguild)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABRESULT, OnTcnSelchangeTabresult)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_NOTIFY(NM_CLICK, IDC_LISTMEMBER, OnNMClickListmember)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTMEMBER, OnNMDblclkListmember)
	ON_BN_CLICKED(IDC_BTNMODI, OnBnClickedBtnmodi)
	ON_BN_CLICKED(IDC_BTNRESET, OnBnClickedBtnreset)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDC_BTNMODIMEMBERLVL, OnBnClickedBtnmodimemberlvl)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTGUILD, OnLvnColumnclickListguild)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTMEMBER, OnLvnColumnclickListmember)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CPALGuildManage::OnInitDialog()
{
	CDialog::OnInitDialog();	
	InitUI();// ��ʼ����ʾ�ַ�			

	nGuildItem = 0;
	nGuildMemberItem = 0;
	pageInfo = false;// �ж��Ƿ���Ҫ��ҳ
	ServerIP = "";// ��Ϸ������IP		
	GuildName= "";
	UserName = "";//��ҽ�ɫ��

	SetProp(listGuild.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listGuild.GetSafeHwnd(),"����˳��",(HANDLE)1);

	SetProp(listMember.GetSafeHwnd(),"�����к�",(HANDLE)0);
    SetProp(listMember.GetSafeHwnd(),"����˳��",(HANDLE)1);

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

	if(listGuild.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGuild.MoveWindow(newRect);//���ú�listGuild��λ��
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

	if(listMember.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMember.MoveWindow(newRect);//���ú�listMember��λ��
	}

	ShowGuildInfo();

	//OperationPAL operPAL;
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Create");//��ʼ�����Ի���

	if(theApp.operPAL.GetServerList())//�������е���Ϸ�������б�
	{
		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	}

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CPALGuildManage::InitUI()
{
	//OperationPAL operPAL;

	SetWindowText(theApp.operPAL.ReadValue("MPAL","GM_UI_GuildManage"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operPAL.ReadValue("MPAL","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLSERVER,theApp.operPAL.ReadValue("MPAL","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLGUILD,theApp.operPAL.ReadValue("MPAL","GM_UI_Guild"));
	SetDlgItemText(IDSEARCH,theApp.operPAL.ReadValue("MPAL","Search"));
	SetDlgItemText(IDCANCEL,theApp.operPAL.ReadValue("MPAL","Cancel"));
	SetDlgItemText(IDC_LBLHINT,theApp.operPAL.ReadValue("MPAL","GM_HINT_TIME"));	
	SetDlgItemText(IDC_LBLPAGE,theApp.operPAL.ReadValue("MPAL","UIC_UI_Page"));

	SetDlgItemText(IDC_LBLGUILDNAME,theApp.operPAL.ReadValue("MPAL","GM_UI_Guild"));
	SetDlgItemText(IDC_LBLBANREASON,theApp.operPAL.ReadValue("MPAL","GM_UI_DIMGUILDREASON"));
	SetDlgItemText(IDC_BTNBAN,theApp.operPAL.ReadValue("MPAL","Modify"));
	SetDlgItemText(IDC_BTNRESET,theApp.operPAL.ReadValue("MPAL","Reset"));

	SetDlgItemText(IDC_LBLMEMBERNAME,theApp.operPAL.ReadValue("MPAL","GM_UI_MEMBERNAME"));//��Ա����
	SetDlgItemText(IDC_LBLMEMBERLVL,theApp.operPAL.ReadValue("MPAL","GM_UI_NEWMEMBERPL"));//�³�Ա�ȼ�
	SetDlgItemText(IDC_LBLMEMBERREASON,theApp.operPAL.ReadValue("MPAL","GM_UI_MODIFYMEMBERPLREASON"));//��ְԭ��
	SetDlgItemText(IDC_BTNMODIMEMBERLVL,theApp.operPAL.ReadValue("MPAL","GM_UI_MODIFYMEMBERPLCONFIRM"));//��ְԭ��

	tbcResult.InsertItem(0,theApp.operPAL.ReadValue("MPAL","GM_UI_tpgGuildInfo"));
	tbcResult.InsertItem(1,theApp.operPAL.ReadValue("MPAL","GM_UI_tpgDisGuild"));
	tbcResult.InsertItem(2,theApp.operPAL.ReadValue("MPAL","GM_UI_tpgModifyGuild"));
	tbcResult.InsertItem(3,theApp.operPAL.ReadValue("MPAL","GM_UI_tpgModifyGuildLv"));
	tbcResult.InsertItem(4,theApp.operPAL.ReadValue("MPAL","GM_UI_tpgGuildMember"));
	tbcResult.InsertItem(5,theApp.operPAL.ReadValue("MPAL","GM_UI_tpgModiGuildNote"));
}

//�����ݼ���Ӧ����
BOOL CPALGuildManage::PreTranslateMessage(MSG* pMsg)
{
	//OperationPAL operPAL;
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listGuild.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listGuild);				
				}
				else if(pMsg->hwnd == listMember.m_hWnd)
				{
					theApp.operPAL.CopyListInfo(&listMember);
				}
			}
			else if(pMsg->wParam == 'A')
			{
				if(pMsg->hwnd == listGuild.m_hWnd)
				{
					for(int i=0; i<listGuild.GetItemCount(); i++)
					{
					    listGuild.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listGuild.EnsureVisible(i,false);
					}
				}
				else if(pMsg->hwnd == listMember.m_hWnd)
				{
					for(int i=0; i<listMember.GetItemCount(); i++)
					{
					    listMember.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);   
						listMember.EnsureVisible(i,false);
					}
				}
			}
		}		
	}
	return FALSE;
}

// �Զ��ı��С
void CPALGuildManage::OnSize(UINT nType, int cx, int cy)
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

	if(listGuild.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listGuild.MoveWindow(newRect);//���ú�listGuild��λ��
	}

	if(GrpPage.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = newRect.top + grpPHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpPage.MoveWindow(newRect);//���ú�GrpPage��λ��
	}

	if(listMember.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight + grpPHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listMember.MoveWindow(newRect);//���ú�listMember��λ��
	}
}

//���ñ�����ɫ
HBRUSH CPALGuildManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

// ��ѯ������Ϣ
void CPALGuildManage::OnBnClickedSearch()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;	

		nGuildItem = 0;
		nGuildMemberItem = 0;
		pageInfo = false;//�б��ܷ�ҳ		
		cmbPage.ResetContent();//����б�ҳ�ĸ�ѡ��
		while(listGuild.DeleteColumn(0)){}//����б��е���������
		while(listMember.DeleteColumn(0)){}//����б��е���������

		ShowGuildInfo();

		UpdateData(true);			

		int index = theApp.operPAL.ReadIntValue("MPAL","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//ÿҳ��ʾ50����¼

		GetDlgItemText(IDC_CMBSERVER,ServerName);//��ȡ��Ϸ������������
		if(ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Warn_SelectServer"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITGUILD,GuildName);//��ȡ������
		if(GuildName=="")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_GUILDNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CSocketData socketdata;	
		socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_GUILDBASEINFO))//���Ͳ�ѯ���������Ϣ������
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

// ��������������Ϣ���浱ǰ�к�
void CPALGuildManage::OnNMClickListguild(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 0)
	{
		if(listGuild.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listGuild.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nGuildItem = listGuild.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
		}
		else
		{
			nGuildItem = 0;
		}
	}
	else
	{
		nGuildItem=-1;
	}
	*pResult = 0;
}

// ˫������������Ϣ���в���
void CPALGuildManage::OnNMDblclkListguild(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel()==0)
	{
		if(listGuild.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listGuild.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nGuildItem = listGuild.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�

			if(nGuildItem>=0)
			{
				tbcResult.SetCurSel(1);
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);

				UpdateData(false);

				//OperationPAL operPAL;
				GuildName = theApp.operPAL.GetValueByColName(&listGuild, nGuildItem, theApp.operPAL.ReadValue("MPAL","PAL_GUILDNAME"));//��ȡ��������

				SetDlgItemText(IDC_EDITGUILDNAME,GuildName);//���ù�������
				SetDlgItemText(IDC_EDITREASON,"");
			}
		}
		else
		{
			nGuildItem = 0;
		}		
	}
	*pResult = 0;
}

// �л�ѡ����в���
void CPALGuildManage::OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	CIni mIni;
	//OperationPAL operPAL;

	if(tbcResult.GetCurSel()==0)//��ѯ���������Ϣ
	{
		ShowGuildInfo();
	}	
	else
	{
		if((listGuild.GetItemCount() > 0) && (nGuildItem >= 0))
		{
			GuildName = theApp.operPAL.GetValueByColName(&listGuild, nGuildItem, theApp.operPAL.ReadValue("MPAL","PAL_GUILDNAME"));//��ȡ��������

			UpdateData(false);
			SetDlgItemText(IDC_EDITGUILDNAME,GuildName);//���ù�������
			SetDlgItemText(IDC_EDITREASON,"");//����ԭ��

			if(tbcResult.GetCurSel()==1)//��ʾ��ɢ������Ϣ
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);
			}
			else if(tbcResult.GetCurSel()==2)//��ʾ�޸Ĺ���������Ϣ
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);
			}
			else if(tbcResult.GetCurSel()==3)//��ʾ�޸Ĺ���ȼ���Ϣ
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);

				UpdateData(false);

				CString GuildLvl = theApp.operPAL.GetValueByColName(&listGuild, nGuildItem, theApp.operPAL.ReadValue("MPAL","PAL_GUILDLEVEL"));//��ȡ����ȼ�

				SetDlgItemText(IDC_EDITNEW,GuildLvl);//���ù���ȼ�
				InitNewGuildLevl();
			}
			else if(tbcResult.GetCurSel()==4)//��ʾ�����Ա�б�
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_HIDE);
				ShowGuildMember(SW_SHOW);

				InitMemberLevel();

				GuildMemberList();
			}
			else if(tbcResult.GetCurSel()==5)//�޸İ�ṫ������
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);
			}
		}
		else
		{
			UpdateData(false);
			SetDlgItemText(IDC_EDITGUILDNAME,"");//���ù�������
			SetDlgItemText(IDC_EDITREASON,"");//����ԭ��

			if(tbcResult.GetCurSel()==1)//��ʾ��ɢ������Ϣ
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);
			}
			else if(tbcResult.GetCurSel()==2)//��ʾ�޸Ĺ���������Ϣ
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);
			}
			else if(tbcResult.GetCurSel()==3)//��ʾ�޸Ĺ���ȼ���Ϣ
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);

				UpdateData(false);
				SetDlgItemText(IDC_EDITNEW,"");//���ù���ȼ�

				InitNewGuildLevl();
			}
			else if(tbcResult.GetCurSel()==4)//��ʾ�����Ա�б�
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_HIDE);
				ShowGuildMember(SW_SHOW);

				InitMemberLevel();
			}
			else if(tbcResult.GetCurSel()==5)//�޸İ�ṫ������
			{
				GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_HIDE);
				ShowModiTab(SW_SHOW);
				ShowGuildMember(SW_HIDE);
			}
		}
	}
	*pResult = 0;
}

// ��ѯ�����Ա�б�
void CPALGuildManage::GuildMemberList()
{
	//OperationPAL operPAL;
	try
	{				
		CIni mIni;
		
		nGuildMemberItem = 0;
		pageInfo = false;		
		cmbPage.ResetContent();
		while(listMember.DeleteColumn(0)){}

		char strInt[10];
		int index = theApp.operPAL.ReadIntValue("MPAL","index");
		int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�������������������IP��������Name,�������ơ�ҳ����ÿҳ�ļ�¼����

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_GUILDMEMBERLIST))
		{		
			::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//���Ͳ�ѯ����
		}

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_UserInfo"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

// ��ҳ���в�ѯ
void CPALGuildManage::OnCbnSelchangeCmbpage()
{
	//OperationPAL operPAL;
	try
	{		
		if(pageInfo)
		{	
			CIni mIni;

			while(listMember.DeleteColumn(0)){}
			
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize = theApp.operPAL.ReadIntValue("MPAL","pageSize");//ÿҳ��ʾ50����¼
			
			CSocketData socketdata;
			socketdata.InitCreate(1,10);//�������������������IP��������Name������ǳơ�ҳ����ÿҳ�ļ�¼����
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));
			socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
		
			if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_GUILDMEMBERLIST))
			{
				::EnableWindow(this->GetParent()->m_hWnd,false);
				dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
		MessageBox(theApp.operPAL.ReadValue("MPAL","UIC_Error_Page"),theApp.operPAL.ReadValue("MPAL","Error"),0);
	}
}

// ���������Ա��Ϣ���浱ǰ�к�
void CPALGuildManage::OnNMClickListmember(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel() == 4)
	{
		if(listMember.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listMember.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nGuildMemberItem = listMember.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�
		}
		else
		{
			nGuildMemberItem = 0;
		}
	}
	else
	{
		nGuildMemberItem=-1;
	}
	*pResult = 0;
}

// ˫�������Ա��Ϣ���в���
void CPALGuildManage::OnNMDblclkListmember(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(tbcResult.GetCurSel()==4)
	{
		if(listMember.GetItemCount() > 0)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

			listMember.ScreenToClient(&point);

			LVHITTESTINFO lvinfo;
			lvinfo.pt = point;
			lvinfo.flags = LVHT_ABOVE;

			nGuildMemberItem = listMember.SubItemHitTest(&lvinfo);//�������б���ѡ�е��к�

			if(nGuildMemberItem>=0)
			{
				//OperationPAL operPAL;
				UserName = theApp.operPAL.GetValueByColName(&listMember, nGuildMemberItem, theApp.operPAL.ReadValue("MPAL","PAL_ROLENAME"));//��ȡ��Ա����

			    SetDlgItemText(IDC_EDITMEMBERNAME,UserName);//���ù����Ա����
			    SetDlgItemText(IDC_EDITREASON,"");
			}
		}
		else
		{
			nGuildMemberItem = 0;
		}		
	}
}

//��ɢ����,�޸Ĺ������ƣ��޸Ĺ����Աְ��
void CPALGuildManage::OnBnClickedBtnmodi()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;

		GuildName="";
		GetDlgItemText(IDC_EDITGUILDNAME,GuildName);//��ȡ��������
		if(GuildName=="")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_GUILDNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int midlength=0;
		int iGuildLevel=0;		
		int iNewGuildLevel=0;
		CString NewGuildName="";

		CString Reason = "";		
		GetDlgItemText(IDC_EDITREASON,Reason);//��ȡԭ��

		switch(tbcResult.GetCurSel())
		{
		case 1:// ��ɢ����
			{
				if(strlen(Reason) == 0)//ԭ����Ϊ��
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_REASONNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
					return;
				}		
				if(strlen(Reason) >= 256)//ԭ���ܳ���256���ַ�
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","BU_UI_ReasonTooLong"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
					return;
				}
			}
			break;
		case 2://�޸Ĺ�������
			{
				if(strlen(Reason) == 0)//ԭ����Ϊ��
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_REASONNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
					return;
				}		
				if(strlen(Reason) >= 256)//ԭ���ܳ���256���ַ�
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","BU_UI_ReasonTooLong"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
					return;
				}
			}
			break;
		case 3://�޸Ĺ���ȼ�
			{
				if(strlen(Reason) == 0)//ԭ����Ϊ��
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_REASONNULL"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
					return;
				}		
				if(strlen(Reason) >= 256)//ԭ���ܳ���256���ַ�
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","BU_UI_ReasonTooLong"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
					return;
				}
			}
			break;
		case 5:// �޸Ĺ���
			{
				if(strlen(Reason) == 0)//��ṫ�治��Ϊ��
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_GUILDNOTICENULL"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
					return;
				}		
				if(strlen(Reason) >= 256)//��ṫ�治�ܳ���256���ַ�
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_GUILDNOTICETOOLONG"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
					return;
				}				
			}
			break;
		}

		int userbyID = theApp.UserByID;//����ԱID
		iNewGuildLevel=cmbLvl.GetCurSel()+1;

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�����ĸ�������������IP��������Name����������,��ͣ����ԭ�򡢲���ԱID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
				
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		switch(tbcResult.GetCurSel())
		{
		case 1:// ��ɢ����
			{
				socketdata.AddTFLV(CEnumCore::TagName::PAL_REASON,CEnumCore::TagFormat::TLV_STRING,strlen(Reason),(unsigned char *)mIni.wcharToChar(Reason));//ԭ��
				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_DISMISSGUILD))//���ͽ�ɢ��������
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		case 2://�޸Ĺ�������
			{
				socketdata.AddTFLV(CEnumCore::TagName::PAL_REASON,CEnumCore::TagFormat::TLV_STRING,strlen(Reason),(unsigned char *)mIni.wcharToChar(Reason));//ԭ��

				GetDlgItemText(IDC_EDITNEW,NewGuildName);
				if(NewGuildName=="")
				{
					MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_NEWGUILDNAMENULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
					return;
				}
				socketdata.AddTFLV(CEnumCore::TagName::PAL_NEWGUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(NewGuildName),(unsigned char *)mIni.wcharToChar(NewGuildName));
				
				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYGUILDNAME))//���ͽ�ɢ��������
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		case 3://�޸Ĺ���ȼ�
			{
				socketdata.AddTFLV(CEnumCore::TagName::PAL_REASON,CEnumCore::TagFormat::TLV_STRING,strlen(Reason),(unsigned char *)mIni.wcharToChar(Reason));//ԭ��
				_itoa(iNewGuildLevel,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDLEVEL,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�¹���ȼ�
				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYGUILDLV))//���ͽ�ɢ��������	
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		case 5:// �޸Ĺ���
			{
				socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNOTICE,CEnumCore::TagFormat::TLV_STRING,strlen(Reason),(unsigned char *)mIni.wcharToChar(Reason));//��ṫ��
				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYGUILDNOTICE))//�����޸Ĺ�������
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		}		
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

//�޸Ĺ����Ա�ȼ���Ϣ
void CPALGuildManage::OnBnClickedBtnmodimemberlvl()
{
	try
	{
		CIni mIni;
		//OperationPAL operPAL;

		GetDlgItemText(IDC_EDITMEMBERNAME,UserName);//��ȡ��������
		if(UserName == "")
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","GM_WARN_GUILDMEMBERNAMENULL"),theApp.operPAL.ReadValue("MPAL","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		int midlength=0;

		CString Reason = "";		
		GetDlgItemText(IDC_EDITMEMBERREASON,Reason);//��ȡԭ��

		int userbyID = theApp.UserByID;//����ԱID

		CSocketData socketdata;
		socketdata.InitCreate(1,10);//�����ĸ�������������IP��������Name����������,��ͣ����ԭ�򡢲���ԱID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIP,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GMSERVERIPNAME,CEnumCore::TagFormat::TLV_STRING,strlen(ServerName),(unsigned char *)mIni.wcharToChar(ServerName));//������Name
		socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDNAME,CEnumCore::TagFormat::TLV_STRING,strlen(GuildName),(unsigned char *)mIni.wcharToChar(GuildName));//��������
		
		if(strlen(Reason) >= 256)//ԭ����Ϊ��
		{
			MessageBox(theApp.operPAL.ReadValue("MPAL","BU_UI_ReasonTooLong"),theApp.operPAL.ReadValue("MPAL","Warn"),0);
			return;
		}		
		socketdata.AddTFLV(CEnumCore::TagName::PAL_REASON,CEnumCore::TagFormat::TLV_STRING,strlen(Reason),(unsigned char *)mIni.wcharToChar(Reason));//ԭ��
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		switch(tbcResult.GetCurSel())
		{
		case 4://�޸Ĺ����Աְ��
			{
				socketdata.AddTFLV(CEnumCore::TagName::PAL_ROLENAME,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));

				int iMemberLevel=cmbMemberLvl.GetCurSel();
				_itoa(iMemberLevel,strInt,10);
				socketdata.AddTFLV(CEnumCore::TagName::PAL_GUILDPOWERLEVEL,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);
				midlength = socketdata.EnBody();
				if(theApp.operPAL.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::PAL_MODIFYGUILDMEMBERPL))//���ͽ�ɢ��������
				{
					::EnableWindow(this->GetParent()->m_hWnd,false);
					dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
				}
			}
			break;
		}
		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

// ������Ϣ
void CPALGuildManage::OnBnClickedBtnreset()
{
	SetDlgItemText(IDC_EDITREASON,"");
}

// ���շ�����Ϣ
LRESULT CPALGuildManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	//OperationPAL operPAL;
	CIni mIni;

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
				CString sIP = (LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::ServerInfo_IP).lpdata;//�õ�������IP
				ServerList.SetAt(i,sIP);//��������IP������CMap��Ķ���ServerList��
			}

			theApp.operPAL.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_GUILDBASEINFO_RESP://��ѯ������Ϣ�Ļ�Ӧ
		{
			ShowGuildInfo();
			nGuildMemberItem = 0;//����ѡ��ĳһ��
			theApp.operPAL.BuildDataTable(&socketdata,&listGuild,&pageCount);//����CListCtrl����
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_GUILDMEMBERLIST_RESP://��ѯ�����Ա�б�Ļ�Ӧ
		{
			if(pageInfo)
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listMember,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operPAL.BuildDataTable(&socketdata,&listMember,&pageCount);//����CListCtrl����

				if(pageCount<=0)//ҳ��<=0��˵��û�����ݷ���
				{
					nGuildMemberItem = 0;//����ѡ��ĳһ��
					pageInfo = false;//���ܷ�ҳ				
					cmbPage.ResetContent();//���ҳ����ѡ��
					while(listMember.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nGuildMemberItem = 0;
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
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDLV_RESP://�޸Ĺ���ȼ��Ļ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��
			SetDlgItemText(IDC_EDITREASON,"");
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDNAME_RESP://�޸Ĺ������ƵĻ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��
			SetDlgItemText(IDC_EDITREASON,"");
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_DISMISSGUILD_RESP://��ɢ����Ļ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��
			SetDlgItemText(IDC_EDITREASON,"");
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDMEMBERPL_RESP://����ְ���Ļ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��
			SetDlgItemText(IDC_EDITREASON,"");
		}
		break;
	case CEnumCore::Message_Tag_ID::PAL_MODIFYGUILDNOTICE_RESP://�޸Ĺ���Ļ�Ӧ
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operPAL.ShowResult(result);//��ʾ���ؽ��
			SetDlgItemText(IDC_EDITREASON,"");
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
void CPALGuildManage::OnLvnColumnclickListguild(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operPAL;
	theApp.operPAL.SortListInfo(&listGuild,pNMHDR,pResult);
}

//���������Ϣ��������������
void CPALGuildManage::OnLvnColumnclickListmember(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OperationPAL operPAL;
	theApp.operPAL.SortListInfo(&listMember,pNMHDR,pResult);
}

// �رնԻ���
void CPALGuildManage::OnBnClickedCancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITGUILD,"");
}

// �رնԻ���
void CPALGuildManage::OnClose()
{
	dlgStatus = theApp.operPAL.ReadIntValue("MPAL","Close");//�رմ���	
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

// ��ʼ�������Ա�ȼ�
void CPALGuildManage::InitMemberLevel(void)
{
	cmbMemberLvl.ResetContent();
	cmbMemberLvl.AddString(theApp.operPAL.ReadValue("MPAL","GuildLvl_Member"));
	cmbMemberLvl.AddString(theApp.operPAL.ReadValue("MPAL","GuildLvl_BCadre"));
	cmbMemberLvl.AddString(theApp.operPAL.ReadValue("MPAL","GuildLvl_ACadre"));
	cmbMemberLvl.AddString(theApp.operPAL.ReadValue("MPAL","GuildLvl_VChairman"));
	cmbMemberLvl.AddString(theApp.operPAL.ReadValue("MPAL","GuildLvl_Chairman"));
	cmbMemberLvl.SetCurSel(0);
}

// ��ʼ�����е��¹���ȼ�
void CPALGuildManage::InitNewGuildLevl(void)
{
	cmbLvl.ResetContent();
	for(int i=1;i<=25;i++)
	{
		CString str="";
		str.Format("%d",i);
		cmbLvl.AddString(str);//�ڸ�ѡ���й���ȼ���Ϣ
	}
	cmbLvl.SetCurSel(0);
}

// ��ʾ������Ϣ
void CPALGuildManage::ShowGuildInfo()
{
	tbcResult.SetCurSel(0);
	GetDlgItem(IDC_LISTGUILD)->ShowWindow(SW_SHOW);
	ShowModiTab(SW_HIDE);
	ShowGuildMember(SW_HIDE);
}

// ��ʾ�޸���Ϣ����
void CPALGuildManage::ShowModiTab(int m_cmdShow)
{
	GetDlgItem(IDC_LBLGUILDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITGUILDNAME)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLNEWGUILDNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITNEW)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLGUILDLVL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBGUILDLVL)->ShowWindow(m_cmdShow);

	if(tbcResult.GetCurSel() == 1)
	{
		GetDlgItem(IDC_LBLNEWGUILDNAME)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_EDITNEW)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLGUILDLVL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBGUILDLVL)->ShowWindow(SW_HIDE);

		SetDlgItemText(IDC_LBLREASON,theApp.operPAL.ReadValue("MPAL","GM_UI_DIMGUILDREASON"));//��ɢԭ��
	}
	else if(tbcResult.GetCurSel() == 2)
	{
		GetDlgItem(IDC_LBLGUILDLVL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBGUILDLVL)->ShowWindow(SW_HIDE);

		txtGuildLvl.SetReadOnly(false);
		SetDlgItemText(IDC_LBLNEWGUILDNAME,theApp.operPAL.ReadValue("MPAL","GM_UI_NEWGUILDNAME"));//�µ�����
	    SetDlgItemText(IDC_LBLREASON,theApp.operPAL.ReadValue("MPAL","GM_UI_MODIFYGUILDNAMEREASON"));//����ԭ��
	}
	else if(tbcResult.GetCurSel() == 3)
	{
		txtGuildLvl.SetReadOnly(true);
		SetDlgItemText(IDC_LBLNEWGUILDNAME,theApp.operPAL.ReadValue("MPAL","GM_UI_ORIGUILDLVL"));//����ȼ�
	    SetDlgItemText(IDC_LBLGUILDLVL,theApp.operPAL.ReadValue("MPAL","GM_UI_NEWGUILDLVL"));//�µĵȼ�
	    SetDlgItemText(IDC_LBLREASON,theApp.operPAL.ReadValue("MPAL","GM_UI_MODIGUILDLVLREASON"));//����ԭ��	    
	}
	else if(tbcResult.GetCurSel() == 5)
	{
		GetDlgItem(IDC_LBLNEWGUILDNAME)->ShowWindow(SW_HIDE);
	    GetDlgItem(IDC_EDITNEW)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LBLGUILDLVL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBGUILDLVL)->ShowWindow(SW_HIDE);

		SetDlgItemText(IDC_LBLREASON,theApp.operPAL.ReadValue("MPAL","GM_UI_GUILDNOTICE"));//��ṫ��
	}
	GetDlgItem(IDC_LBLREASON)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITREASON)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNMODI)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNRESET)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITNEW,"");
	SetDlgItemText(IDC_EDITREASON,"");
}

// ��ʾ�޸Ĺ����Ա��Ϣ
void CPALGuildManage::ShowGuildMember(int m_cmdShow)
{
	GetDlgItem(IDC_GRPPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LISTMEMBER)->ShowWindow(m_cmdShow);

	GetDlgItem(IDC_LBLMEMBERNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITMEMBERNAME)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMEMBERLVL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_CMBMEMBERLVL)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_LBLMEMBERREASON)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_EDITMEMBERREASON)->ShowWindow(m_cmdShow);
	GetDlgItem(IDC_BTNMODIMEMBERLVL)->ShowWindow(m_cmdShow);

	SetDlgItemText(IDC_EDITMEMBERNAME,"");
	SetDlgItemText(IDC_EDITMEMBERREASON,"");
}
