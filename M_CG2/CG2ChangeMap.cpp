// CG2ChangeMap.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_CG2.h"
#include "CG2ChangeMap.h"
#include ".\CG2ChangeMap.h"


// CCG2ChangeMap �Ի���

IMPLEMENT_DYNAMIC(CCG2ChangeMap, CDialog)
CCG2ChangeMap::CCG2ChangeMap(CWnd* pParent /*=NULL*/)
	: CDialog(CCG2ChangeMap::IDD, pParent)
{
}

CCG2ChangeMap::~CCG2ChangeMap()
{
}

void CCG2ChangeMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBUISERVER, cmbServer);
	DDX_Control(pDX, IDC_CMBUIPAGE, cmbPage);
	DDX_Control(pDX, IDC_LISTUSERINFO, listUser);
	DDX_Control(pDX, IDC_GRPSEARCH, GrpSearch);
	DDX_Control(pDX, IDC_GRPUIPAGE, GrpPage);
	DDX_Control(pDX, IDC_TABUIRESULT, tbcResult);
	DDX_Control(pDX, IDC_CMBOBJECT, cmbObject);
	DDX_Control(pDX, IDC_CKMAP, ckMap);
	DDX_Control(pDX, IDC_CKMAPXY, ckMapXY);
}


BEGIN_MESSAGE_MAP(CCG2ChangeMap, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDUICANCEL, OnBnClickedUicancel)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_BN_CLICKED(IDUISEARCH, OnBnClickedUisearch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUIRESULT, OnTcnSelchangeTabuiresult)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSERINFO, OnNMClickListuserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSERINFO, OnNMDblclkListuserinfo)
	ON_BN_CLICKED(IDC_BTUPDATE, OnBnClickedBtupdate)
	ON_BN_CLICKED(IDC_BTRESET, OnBnClickedBtreset)
	ON_BN_CLICKED(IDC_CKMAP, OnBnClickedCkmap)
	ON_BN_CLICKED(IDC_CKMAPXY, OnBnClickedCkmapxy)
	ON_BN_CLICKED(IDC_BTSEARCHMAP, OnBnClickedBtsearchmap)
END_MESSAGE_MAP()


// CCG2ChangeMap ��Ϣ�������

BOOL CCG2ChangeMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();

	nItem = -1;
	pageInfo = false;
	pageUInfo = false;
	ServerIP = "";
	UserID = "";
	UserName = "";
	UserNick = "";//��ʼ��һЩ˽�б���
	iCharNo=0;

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

		
	}


	//OperationCG2 theApp.operCG2;
	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Create");//��ǰ��״̬Ϊ��ʼ�����Ի���

	theApp.operCG2.GetServerList();//�������е���Ϸ�������б�
	::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CCG2ChangeMap::InitUI()
{
	//OperationCG2 theApp.operCG2;

	SetWindowText(theApp.operCG2.ReadValue("MCG2","CG2_UI_UpdateChar"));

	SetDlgItemText(IDC_GRPSEARCH,theApp.operCG2.ReadValue("MCG2","UIC_UI_GrpSearch"));
	SetDlgItemText(IDC_LBLUISERVER,theApp.operCG2.ReadValue("MCG2","UIC_UI_LblServer"));
	SetDlgItemText(IDC_LBLUIACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	SetDlgItemText(IDC_LBLUINICK,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblNick"));
	SetDlgItemText(IDUISEARCH,theApp.operCG2.ReadValue("MCG2","Search"));
	SetDlgItemText(IDUICANCEL,theApp.operCG2.ReadValue("MCG2","Reset"));
	SetDlgItemText(IDC_LBLUIPAGE,theApp.operCG2.ReadValue("MCG2","UIC_UI_Page"));
	//SetDlgItemText(IDC_BTUPDATE,theApp.operCG2.ReadValue("MCG2","Update"));
	//SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));

	//SetDlgItemText(IDC_BTSEARCH,theApp.operCG2.ReadValue("MCG2","Search"));//IDC_STATICACCOUNT IDC_STATICCURJOB IDC_STATICNEWJOB
	//SetDlgItemText(IDC_STATICACCOUNT,theApp.operCG2.ReadValue("MCG2","UIC_UI_lblAccount"));
	//SetDlgItemText(IDC_STATICCURJOB,theApp.operCG2.ReadValue("MCG2","UC_UI_CurrentJob"));//��ǰְҵ
	//SetDlgItemText(IDC_STATICNEWJOB,theApp.operCG2.ReadValue("MCG2","UC_UI_NewJob"));//��ְҵ////IDC_BTUPDATE
	//SetDlgItemText(IDC_BTUPDATE,theApp.operCG2.ReadValue("MCG2","Update"));//�޸�
	//SetDlgItemText(IDC_BTRESET,theApp.operCG2.ReadValue("MCG2","Reset"));//����


	tbcResult.InsertItem(0,theApp.operCG2.ReadValue("MCG2","UIC_UI_tpgUserInfo"));//��һ�����Ϣ
	tbcResult.InsertItem(1,theApp.operCG2.ReadValue("MCG2","BU_UI_tpgChangeMap"));//�ƶ���ɫ����

	ShowChangeMap(SW_HIDE);
}

//�رնԻ���
void CCG2ChangeMap::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!ServerList.IsEmpty())
	{
		ServerList.RemoveAll();
	}
	if(!ObjectList.IsEmpty())
	{
		ObjectList.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}

void CCG2ChangeMap::OnBnClickedUicancel()
{
	cmbServer.SetCurSel(0);
	SetDlgItemText(IDC_EDITUIACCOUNT,"");
	SetDlgItemText(IDC_EDITUINICK,"");
}

void CCG2ChangeMap::OnSize(UINT nType, int cx, int cy)
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

		
	}
}

HBRUSH CCG2ChangeMap::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}



void CCG2ChangeMap::UserInfo()
{
	//OperationCG2 theApp.operCG2;
	try
	{		
		CIni mIni;		
		
		int index = theApp.operCG2.ReadIntValue("MCG2","index");//��ѯ��һҳ����Ϣ
		int iPageSize = theApp.operCG2.ReadIntValue("MCG2","pageSize");//ÿҳ��ʾ50����¼

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������

		CSocketData socketdata;		
		socketdata.InitCreate(1,10);//�������������������IP������ʺš�����ǳơ�ҳ����ÿҳ�ļ�¼����
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_nickname,CEnumCore::TagFormat::TLV_STRING,strlen(UserNick),(unsigned char *)mIni.wcharToChar(UserNick));//����ǳ�

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ҳ��

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//ÿҳ�ļ�¼����

		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Account_Query);//���Ͳ�ѯ���������Ϣ������

		::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UserInfo"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}	
}
void CCG2ChangeMap::OnBnClickedUisearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;
		//OperationCG2 theApp.operCG2;

		tbcResult.SetCurSel(0);//�����Ϣ

		nItem = -1;//��������б�û��ѡ����
		pageUInfo = false;//��������б��ܷ�ҳ	
		cmbPage.ResetContent();//�����������б�ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//�����������б��е���������


		CString m_ServerName;
		GetDlgItemText(IDC_CMBUISERVER,m_ServerName);//��ȡ��Ϸ������������
		if(m_ServerName == "")//��Ϸ����������Ϊ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_SelectServer"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		ServerList.Lookup(cmbServer.GetCurSel()+1,ServerIP);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP

		GetDlgItemText(IDC_EDITUIACCOUNT,UserName);//��ȡ����ʺ�
		GetDlgItemText(IDC_EDITUINICK,UserNick);//��ȡ����ǳ�
		if((UserName == "") && (UserNick == ""))//����ʺź�����ǳƲ���ͬʱΪ��
		{
			MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Warn_InputAccount"),theApp.operCG2.ReadValue("MCG2","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

	    UserInfo();// ��ѯ���������Ϣ
	}
	catch(...)
	{
	}
}

void CCG2ChangeMap::OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;
	if(tbcResult.GetCurSel() == 0)//ѡ�е������������Ϣѡ�
	{
		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

		ShowChangeMap(SW_HIDE);

		UpdateData(true);
	}
	else if(tbcResult.GetCurSel()==1)
	{
		CIni mIni;

		GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

		ShowChangeMap(SW_SHOW);
		
		UpdateData(true);


		if((listUser.GetItemCount() > 0) && (nItem >= 0))
		{
			MapList();
			UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
			UserID = theApp.operCG2.GetValueByColName(&listUser, nItem,theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
			UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�

			MapName =theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_MapName"));//����ѡ�е����ְҵID
			iCharNo =atoi(theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//����ѡ�е���ҽ�ɫ��

			UpdateData(true);


			tbcResult.SetCurSel(1);
			SetDlgItemText(IDC_ETUSERNICK,UserNick);
			SetDlgItemText(IDC_ETCURMAP,MapName);
			GetDlgItem(IDC_EDMAPNAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTSEARCHMAP)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDMAPX)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDMAPY)->EnableWindow(FALSE);
			ckMap.SetCheck(1);
		}
		else
		{
		}



	}
	*pResult = 0;
}

// �����û��б��浱ǰ�к�
void CCG2ChangeMap::OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
void CCG2ChangeMap::OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OperationCG2 theApp.operCG2;

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

				CIni mIni;
				pageInfo = false;
				cmbPage.ResetContent();
				//while(listUser.DeleteColumn(0)){}// �������б��е���������
				
				

				GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_HIDE);

				ShowChangeMap(SW_SHOW);

				MapList();
				UserName = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_UserName"));// ����ѡ�е�����ʺ�
				UserID = theApp.operCG2.GetValueByColName(&listUser, nItem,theApp.operCG2.ReadValue("MCG2","CG2_UserID"));// ����ѡ�е����ID
				UserNick = theApp.operCG2.GetValueByColName(&listUser, nItem, theApp.operCG2.ReadValue("MCG2","CG2_nickname"));// ����ѡ�е�����ǳ�

				MapName =theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_MapName"));//����ѡ�е����ְҵID
				iCharNo =atoi(theApp.operCG2.GetValueByColName(&listUser,nItem,theApp.operCG2.ReadValue("MCG2","CG2_CharacterNum")));//����ѡ�е���ҽ�ɫ��

				UpdateData(true);


				tbcResult.SetCurSel(1);
				SetDlgItemText(IDC_ETUSERNICK,UserNick);
				SetDlgItemText(IDC_ETCURMAP,MapName);
				GetDlgItem(IDC_EDMAPNAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTSEARCHMAP)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDMAPX)->EnableWindow(FALSE);
				GetDlgItem(IDC_EDMAPY)->EnableWindow(FALSE);
				ckMap.SetCheck(1);
				
			}

		}
		else
		{
			nItem = -1;
		}
	}
	*pResult = 0;
}
//��ѯ��ͼ�б�
void CCG2ChangeMap::MapList(void)
{
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,6);//�������������������IP������ʺš���ɫIDKEY����ɫ�š���ְҵ����ע

		char strInt[10];
		_itoa(iCharNo,strInt,10);



		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY



		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_MapList_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UpdateJob"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
//ģ����ѯ
void CCG2ChangeMap::SearchMap(void)
{
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,6);//�������������������IP������ʺš���ɫIDKEY����ɫ�š���ְҵ����ע

		char strInt[10];
		_itoa(iCharNo,strInt,10);


		CString m_MapName="";
		GetDlgItemText(IDC_EDMAPNAME,m_MapName);

		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

		socketdata.AddTFLV(CEnumCore::TagName::CG2_MapName,CEnumCore::TagFormat::TLV_STRING,strlen(m_MapName),(unsigned char *)mIni.wcharToChar(m_MapName));//����ʺ�


		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_SearchMap_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UpdateJob"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
//�ƶ���ɫ����
void CCG2ChangeMap::OnBnClickedBtupdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		CIni mIni;
		CSocketData socketdata;
		socketdata.InitCreate(1,20);//�������������������IP������ʺš���ɫIDKEY����ɫ�š���ְҵ����ע

		char strInt[10];
		_itoa(iCharNo,strInt,10);
		CString MapID="";
		CString MapXY="";


		socketdata.AddTFLV(CEnumCore::TagName::CG2_Serverip,CEnumCore::TagFormat::TLV_STRING,strlen(ServerIP),(unsigned char *)mIni.wcharToChar(ServerIP));//������IP
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserName,CEnumCore::TagFormat::TLV_STRING,strlen(UserName),(unsigned char *)mIni.wcharToChar(UserName));//����ʺ�
		socketdata.AddTFLV(CEnumCore::TagName::CG2_CharNo,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//��ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_UserID,CEnumCore::TagFormat::TLV_STRING,strlen(UserID),(unsigned char *)mIni.wcharToChar(UserID));//��ɫΨһIDKEY

		GetDlgItemText(IDC_CMBOBJECT,MapName);//��ȡ��ͼ����
		if(MapName == "")//��ͼ���Ʋ���Ϊ��
		{
			MessageBox("��ѡ��Ŀ���ͼ");
			return;
		}
		ObjectList.Lookup(cmbObject.GetCurSel()+1,MapID);//��CMap��Ķ���ServerList�л�ȡ��Ϸ��������IP
		int MapX=0,MapY=0;
		
		if(ckMap.GetCheck()==1)
		{
			MapXY.Format("%i,%i",-1,-1);
		}
		else
		{
			MapX=GetDlgItemInt(IDC_EDMAPX);
			MapY=GetDlgItemInt(IDC_EDMAPY);
			MapXY.Format("%i,%i",MapX,MapY);
	

		}
		socketdata.AddTFLV(CEnumCore::TagName::CG2_MapID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)mIni.wcharToChar(MapID));//��ɫ��
		socketdata.AddTFLV(CEnumCore::TagName::CG2_MapName,CEnumCore::TagFormat::TLV_STRING,strlen(MapName),(unsigned char *)mIni.wcharToChar(MapName));//��ɫΨһIDKEY
		socketdata.AddTFLV(CEnumCore::TagName::CG2_Coordinate,CEnumCore::TagFormat::TLV_STRING,strlen(MapXY),(unsigned char *)mIni.wcharToChar(MapXY));//��ɫΨһIDKEY



		int midlength = socketdata.EnBody();
		theApp.operCG2.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::ServiceKey::CG2_Change_Map_Query);

		::EnableWindow(this->GetParent()->m_hWnd,false);
		dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����

		socketdata.Destroy();
	}
	catch(...)
	{
		MessageBox(theApp.operCG2.ReadValue("MCG2","UIC_Error_UpdateJob"),theApp.operCG2.ReadValue("MCG2","Error"),0);
	}
}
//
void CCG2ChangeMap::OnBnClickedBtreset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������




}

LRESULT CCG2ChangeMap::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ������ݳ���

	//OperationCG2 theApp.operCG2;
	CIni mIni;

	dlgStatus = theApp.operCG2.ReadIntValue("MCG2","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

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

			theApp.operCG2.BuildCombox(&socketdata,&cmbServer);//����������б���Ϣ
		}
		break;

	case CEnumCore::Message_Tag_ID::CG2_Account_Query_Resp://��ѯ���������Ϣ�Ļ�Ӧ
		{
			if(pageUInfo)//����Ѿ��ܹ���ҳ
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����
			}
			else
			{
				theApp.operCG2.BuildDataTable(&socketdata,&listUser,&pageCount);//����CListCtrl����

				if(pageCount<0)//ҳ��<=0��˵��û�����ݷ���
				{
					nItem = -1;//����ѡ��ĳһ��
					pageUInfo = false;//���ܷ�ҳ					
					cmbPage.ResetContent();//���ҳ����ѡ��
					while(listUser.DeleteColumn(0)){}//���CListCtrl����
				}
				else
				{
					nItem = 0;
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
	case CEnumCore::Message_Tag_ID::CG2_MapList_Query_Resp:
	case CEnumCore::Message_Tag_ID::CG2_SearchMap_Query_Resp:
		if(!ObjectList.IsEmpty())
		{
			ObjectList.RemoveAll();
		}
		cmbObject.ResetContent();
		for(int i = 1;i <= socketdata.getQueryNum();i++)
		{
			CString strObjectID=(LPCSTR)&socketdata.getTLVByName(i,CEnumCore::TagName::CG2_MapID).lpdata;
			ObjectList.SetAt(i,strObjectID);//��������IP������CMap��Ķ���ServerList��
		}
		theApp.operCG2.BuildPetCombox(&socketdata,&cmbObject);
		break;
	
	//��һ�λ�޸�
	case CEnumCore::Message_Tag_ID::CG2_Change_Map_Query_Resp:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operCG2.ShowResult(result);//��ʾ�������
			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_LISTUSERINFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBUIPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_GRPUIPAGE)->ShowWindow(SW_SHOW);

			ShowChangeMap(SW_HIDE);


			UpdateData(true);


			UserInfo();// ��ѯ���������Ϣ
		}
		break;

	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return false;
}









BOOL CCG2ChangeMap::PreTranslateMessage(MSG* pMsg)
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
					theApp.operCG2.CopyListInfo(&listUser);				
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
			}
		}		
	}
	return FALSE;
}

void CCG2ChangeMap::ShowChangeMap(int n_cmdShow)
{
	GetDlgItem(IDC_STATICUSERNICK)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_STATICCURMAP)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_STATICMAPNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ETUSERNICK)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_ETCURMAP)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDMAPNAME)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTSEARCHMAP)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CKMAP)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CKMAPXY)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_STATICOBJECT)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_CMBOBJECT)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_STATICMAPX)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDMAPX)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_STATICMAPY)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_EDMAPY)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTUPDATE)->ShowWindow(n_cmdShow);
	GetDlgItem(IDC_BTRESET)->ShowWindow(n_cmdShow);

	ckMap.SetCheck(0);
	ckMapXY.SetCheck(0);
	cmbObject.ResetContent();
	SetDlgItemText(IDC_EDMAPNAME,"");
	SetDlgItemText(IDC_EDMAPX,"");
	SetDlgItemText(IDC_EDMAPY,"");


	
	
}
//�����ͼ
void CCG2ChangeMap::OnBnClickedCkmap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(ckMap.GetCheck())
	{
	case 0:
		MessageBox("��ѡ��ʽ");
		ckMap.SetCheck(1);
		break;
	case 1:
		GetDlgItem(IDC_EDMAPNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTSEARCHMAP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDMAPX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDMAPY)->EnableWindow(FALSE);
		ckMapXY.SetCheck(0);
		MapList();

		break;
	}
}
//�������
void CCG2ChangeMap::OnBnClickedCkmapxy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(ckMapXY.GetCheck())
	{
	case 0:
		MessageBox("��ѡ��ʽ");
		ckMapXY.SetCheck(1);
		break;
	case 1:
		GetDlgItem(IDC_EDMAPNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTSEARCHMAP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDMAPX)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDMAPY)->EnableWindow(TRUE);
		cmbObject.ResetContent();
		ckMap.SetCheck(0);
		break;
	}
}


void CCG2ChangeMap::OnBnClickedBtsearchmap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SearchMap();
}
