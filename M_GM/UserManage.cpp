// UserManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_GM.h"
#include "UserManage.h"
#include ".\usermanage.h"


// CUserManage �Ի���

IMPLEMENT_DYNAMIC(CUserManage, CDialog)
CUserManage::CUserManage(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManage::IDD, pParent)
{
}

CUserManage::~CUserManage()
{
}

void CUserManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABUSERMANAGE, tbcResult);
	DDX_Control(pDX, IDC_LISTUSER, listUser);
	DDX_Control(pDX, IDC_CHECKEXIT, cBtnExit);
	DDX_Control(pDX, IDC_CHECKUSERONLINE, cBtnOnline);
	DDX_Control(pDX, IDC_CHECKSYSMANAGE, cBtnSysAdmin);
	DDX_Control(pDX, IDC_CHECKDEPART, cBtnDepartAdmin);
	DDX_Control(pDX, IDC_DTPENDTIME, dtpEndTime);
	DDX_Control(pDX, IDC_CMBPAGE, cmbPage);
	DDX_Control(pDX, IDC_STATPAGE, GrpSearch);
	DDX_Control(pDX, IDC_CMBDEPART, cmbDepart);
}


BEGIN_MESSAGE_MAP(CUserManage, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABUSERMANAGE, OnTcnSelchangeTabusermanage)
	ON_BN_CLICKED(IDADDUSER, OnBnClickedAdduser)
	ON_BN_CLICKED(IDRESET, OnBnClickedReset)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTUSER, OnNMDblclkListuser)
	ON_BN_CLICKED(IDC_CHECKSYSMANAGE, OnBnClickedChecksysmanage)
	ON_BN_CLICKED(IDC_CHECKDEPART, OnBnClickedCheckdepart)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(NM_CLICK, IDC_LISTUSER, OnNMClickListuser)
	ON_CBN_SELCHANGE(IDC_CMBPAGE, OnCbnSelchangeCmbpage)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID__PPPEDOMMANAGE, OnPopedomManage)
	ON_NOTIFY(NM_RCLICK, IDC_LISTUSER, OnNMRclickListuser)
	ON_COMMAND(ID__MODIUSERPWD, OnModiUserPwd)
	ON_COMMAND(ID__UPDATEUSERMAC, OnUpdateUserMAC)
END_MESSAGE_MAP()

// ��ʼ���Ի���
BOOL CUserManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	nItem = -1;
	pageInfo = false;//��ʼ��һЩ˽�б���

	InitUI();// ��ʼ����ʾ�ַ�

	CRect rs;
	GetClientRect(rs); //��ȡ�Ի���Ĵ�С��Ϣ

	CRect srcRect;
	CRect newRect;

	if(tbcResult.m_hWnd != NULL)
	{
		tbcResult.GetWindowRect(srcRect);//��ȡtbcResult�Ĵ�С��Ϣ
		tbcHeight = srcRect.bottom - srcRect.top;//�õ�tbcResult�ĸ߶���Ϣ

		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//����tbcResult��λ��
	}
	
	if(GrpSearch.m_hWnd != NULL)
	{
		GrpSearch.GetWindowRect(srcRect);//��ȡGrpSearch�Ĵ�С��Ϣ
		grpHeight = srcRect.bottom - srcRect.top;//�õ�GrpSearch�ĸ߶���Ϣ

		newRect.top = rs.top + 4 + tbcHeight;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��
	}	

	if(listUser.m_hWnd != NULL)
	{
		listUser.GetWindowRect(srcRect);//��ȡlistUser�Ĵ�С��Ϣ

		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}

	GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_SHOW);//�տ�ʼ��Ҫ��ʾ�û��б���Ϣ
	GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_SHOW);//��ʾ��ҳ��Ϣ
	GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATNAME)->ShowWindow(SW_HIDE);//���������ݶ���������
	GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_HIDE);
	GetDlgItem(IDADDUSER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDRESET)->ShowWindow(SW_HIDE);

	InitUserList();//��ʼ���û��б�
	::EnableWindow(this->GetParent()->m_hWnd,false);

	return TRUE;
}

// ��ʼ����ʾ�ַ�
void CUserManage::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","UM_UI_UserManage"));
	tbcResult.InsertItem(0,theApp.operGM.ReadValue("MGM","UM_UI_UserList"));
	tbcResult.InsertItem(1,theApp.operGM.ReadValue("MGM","UM_UI_AddUser"));
	tbcResult.InsertItem(2,theApp.operGM.ReadValue("MGM","UM_UI_EditUser"));

	SetDlgItemText(IDC_LBLPAGE,theApp.operGM.ReadValue("MGM","UM_UI_Page"));
	SetDlgItemText(IDC_STATNAME,theApp.operGM.ReadValue("MGM","UM_UI_UserName"));
	SetDlgItemText(IDC_STATUPWD,theApp.operGM.ReadValue("MGM","UM_UI_UserPwd"));
	SetDlgItemText(IDC_STATPWDAG,theApp.operGM.ReadValue("MGM","UM_UI_UserPwdAG"));
	SetDlgItemText(IDC_STATREALNAME,theApp.operGM.ReadValue("MGM","UM_UI_RealName"));
	SetDlgItemText(IDC_STATDEPART,theApp.operGM.ReadValue("MGM","UM_UI_UserDepart"));
	SetDlgItemText(IDC_STATENDTIME,theApp.operGM.ReadValue("MGM","UM_UI_EndTime"));
	SetDlgItemText(IDC_CHECKEXIT,theApp.operGM.ReadValue("MGM","UM_UI_CheckExit"));
	SetDlgItemText(IDC_CHECKUSERONLINE,theApp.operGM.ReadValue("MGM","UM_UI_CheckOnline"));
	SetDlgItemText(IDC_CHECKSYSMANAGE,theApp.operGM.ReadValue("MGM","UM_UI_CheckSys"));
	SetDlgItemText(IDC_CHECKDEPART,theApp.operGM.ReadValue("MGM","UM_UI_CheckDepart"));
	SetDlgItemText(IDADDUSER,theApp.operGM.ReadValue("MGM","UM_UI_AddUser"));
	SetDlgItemText(IDRESET,theApp.operGM.ReadValue("MGM","Reset"));

	SetDlgItemText(ID__PPPEDOMMANAGE,theApp.operGM.ReadValue("MGM","PM_UI_PopedomManage"));
}

//�����ݼ���Ӧ����
BOOL CUserManage::PreTranslateMessage(MSG* pMsg)
{
    if(GetKeyState(VK_CONTROL)&0x8000)
	{
		if(pMsg->message == WM_KEYDOWN)  //�ж��Ƿ��а�������
		{				
			if(pMsg->wParam == 'C')
			{
				if(pMsg->hwnd == listUser.m_hWnd)
				{
					theApp.operGM.CopyListInfo(&listUser);
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

/// <summary>
/// �Զ��ı��С
/// </summary>
void CUserManage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rs;
	GetClientRect(rs);

	CRect srcRect;
	CRect newRect;
	
	if(tbcResult.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4;
		newRect.bottom = newRect.top + tbcHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		tbcResult.MoveWindow(newRect);//���ú�tbcResult��λ��
	}
	
	if(GrpSearch.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + tbcHeight;
		newRect.bottom = newRect.top + grpHeight;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		GrpSearch.MoveWindow(newRect);//���ú�GrpSearch��λ��
	}	

	if(listUser.m_hWnd != NULL)
	{
		newRect.top = rs.top + 4 + grpHeight + tbcHeight;
		newRect.bottom = rs.bottom-10;
		newRect.left = rs.left +10;
		newRect.right = rs.right - 10;

		listUser.MoveWindow(newRect);//���ú�listUser��λ��
	}
}

//���ñ�����ɫ
HBRUSH CUserManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF backColor = RGB(255, 255, 255);//������ɫΪ��ɫ

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	return CreateSolidBrush(backColor);
}

/// <summary>
/// ���������û���Ϣ�б�
/// </summary>
void CUserManage::InitUserList()
{
	try
	{
		//OperationGM operGM;

		nItem = -1;//�û��б�û��ѡ����
		pageInfo = false;//�û��б��ܷ�ҳ	
		cmbPage.ResetContent();//�����ҳ�ĸ�ѡ��
		while(listUser.DeleteColumn(0)){}//����û��б��е���������

		int userByID=theApp.UserByID;
		int index=1;//��ѯ��һҳ����Ϣ
		int iPageSize=50;//ÿҳ��ʾ50����¼

		CSocketData socketdata;
		socketdata.InitCreate(1,3);//��������������������ID��ҳ����ÿҳ�ļ�¼����
		char strInt[10];		

		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(index,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(iPageSize,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_QUERY_ALL))//���Ͳ�ѯ�û��б������
		{
		    ::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();//����CSocketData�ֲ�����
	}
	catch(...)
	{
	}
}

/// <summary>
/// ��ҳ���������û���Ϣ�б�
/// </summary>
void CUserManage::OnCbnSelchangeCmbpage()
{
	try
	{			
		if(pageInfo)//������Է�ҳ�Ļ�
		{
			//OperationGM operGM;
			nItem = -1;
			while(listUser.DeleteColumn(0)){}//���ҳ������

			CSocketData socketdata;
			socketdata.InitCreate(1,3);
			char strInt[10];

			int userByID=theApp.UserByID;
			int index = cmbPage.GetCurSel() + 1;//ҳ��ΪcmbPage��ǰ������ֵ��1��Ҳ����cmbPage�е�ǰ��ʾ��ֵ
			int iPageSize=50;//ÿҳ��ʾ50����¼

			_itoa(userByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(index,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::Index,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			_itoa(iPageSize,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::PageSize,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

			int midlength = socketdata.EnBody();
			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_QUERY_ALL))//���Ͳ�ѯ�û��б������
			{
			    ::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
				dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();
		}
	}
	catch(...)
	{
	}
}

/// <summary>
/// �����û��б��浱ǰ�к�
/// </summary>
void CUserManage::OnNMClickListuser(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listUser.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listUser.SubItemHitTest(&lvinfo);//�������û��б���ѡ�е��к�

		*pResult = 0;
	}
	catch(...)
	{
	}
}

/// <summary>
/// ˫���û��б����ɾ��
/// </summary>
void CUserManage::OnNMDblclkListuser(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{		
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listUser.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listUser.SubItemHitTest(&lvinfo);//�������û��б���ѡ�е��к�

		if(nItem >= 0)
		{
			CIni mIni;
			//OperationGM operGM;					

			UpdateData(true);

			int userID=0;
			userID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//��ȡҪɾ�����û�ID

			CString userName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));//��ȡҪɾ�����û�����

			if(userID == 0)//�û�ID����Ϊ0
			{
				return;
			}

			if (AfxMessageBox(theApp.operGM.ReadValue("MGM","UM_Hint_DeleteSelectUser"), MB_YESNO) != IDYES) //�Ƿ�ȷ��Ҫɾ��
			{
				return;
			} 

			CSocketData socketdata;
			socketdata.InitCreate(1,3);//��������������������ID��Ҫɾ�����û����ơ�Ҫɾ�����û�ID
			char strInt[10];
			
			int userByID=theApp.UserByID;

			_itoa(userByID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//������ID

			socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char*)mIni.wcharToChar(userName));//Ҫɾ�����û�����

			_itoa(userID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//Ҫɾ�����û�ID

			int midlength = socketdata.EnBody();
			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_DELETE))//����ɾ���û�������
			{
			    ::EnableWindow(this->GetParent()->m_hWnd,false);//����һ������ʱ�����������涼���Disable��״̬������ͻ���ͬʱ�����������
				dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
			}
			socketdata.Destroy();
		}
		*pResult = 0;
	}
	catch(...)
	{
	}
}

/// <summary>
/// �л�ѡ����в���
/// </summary>
void CUserManage::OnTcnSelchangeTabusermanage(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		CIni mIni;
		//OperationGM operGM;
		if(tbcResult.GetCurSel()==0)//�鿴�û��б�ʱ��ֻҪ���û��б���ʾ�����Ϳ����ˣ�����Ҫ����������
		{
			GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDADDUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDRESET)->ShowWindow(SW_HIDE);
		}
		else if(tbcResult.GetCurSel()==1)//����µ��û���Ϣʱ��������ʾ��Ӧ�Ľ�����Ϣ����Ҫ������еĲ����б�
		{
			GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTUSER)->EnableWindow(true);

			GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDADDUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDRESET)->ShowWindow(SW_SHOW);

			SetDlgItemText(IDC_TXTUSER,"");
			SetDlgItemText(IDC_TXTPWD,"");
			SetDlgItemText(IDC_TXTPWDAG,"");
			SetDlgItemText(IDC_TXTREALNAME,"");
			SetDlgItemText(IDC_TXTREALNAME,"");

			CTime curTime = CTime::GetCurrentTime();
			dtpEndTime.SetTime(&curTime);//����Ҫ�༭���û���ʹ��ʱЧ

			cBtnExit.SetCheck(false);
			cBtnSysAdmin.SetCheck(false);
			cBtnDepartAdmin.SetCheck(false);

			SetDlgItemText(IDADDUSER,theApp.operGM.ReadValue("MGM","UM_UI_AddUser"));
			DepartList();//��ȡ���еĲ�����Ϣ
		}
		else if(tbcResult.GetCurSel()==2)//�༭���е��û���Ϣʱ��Ҫ�����е���Ϣ����ʾ�ڽ����У���Ҫ������е��û�������Ϣ
		{
			if(nItem < 0)
			{
				MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_SelectModiUser"),theApp.operGM.ReadValue("MGM","Warn"),0);

				tbcResult.SetCurSel(0);
				GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_STATNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_HIDE);
				GetDlgItem(IDADDUSER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDRESET)->ShowWindow(SW_HIDE);

				return;
			}
			GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_TXTUSER)->EnableWindow(false);//Ҫ�༭���û������ǹ̶���
			CString userName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));
			SetDlgItemText(IDC_TXTUSER,userName);//����Ҫ�༭���û�����

			CString realName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","RealName"));
			SetDlgItemText(IDC_TXTREALNAME,realName);//����Ҫ�༭���û���ʵ����

			CString limitTime = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","Limit"));
			CTime curTime = mIni.StrToTime(limitTime);
			dtpEndTime.SetTime(&curTime);

			GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_SHOW);
			GetDlgItem(IDADDUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDRESET)->ShowWindow(SW_SHOW);

			cBtnExit.SetCheck(false);
			cBtnOnline.SetCheck(false);
			cBtnSysAdmin.SetCheck(false);
			cBtnDepartAdmin.SetCheck(false);

			SetDlgItemText(IDADDUSER,theApp.operGM.ReadValue("MGM","UM_UI_EditUser"));
			DepartList();//��ȡ���еĲ�����Ϣ
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}

/// <summary>
/// �������в����б�
/// </summary>
void CUserManage::DepartList()
{
	try
	{			
		//OperationGM operGM;

		cmbDepart.ResetContent();//������еĲ����б�

		CSocketData socketdata;
		socketdata.InitCreate(1,1);
		
		int userByID=theApp.UserByID;

		char strInt[10];
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::DEPART_QUERY))//���Ͳ�ѯ�����б������
		{
		    ::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}


/// <summary>
/// ��ӻ��޸��û���Ϣ
/// </summary>
void CUserManage::OnBnClickedAdduser()
{
	try
	{
		if(tbcResult.GetCurSel()==1)//�����������û���Ϣ�Ľ���
		{
			AddUser();//����û���Ϣ
		}
		else if(tbcResult.GetCurSel()==2)//������ڱ༭�û���Ϣ�Ľ���
		{
			EditUser();//�༭�û���Ϣ
		}
	}
	catch(...)
	{
	}
}

/// <summary>
/// ����û���Ϣ
/// </summary>
void CUserManage::AddUser()
{
	try
	{			
		//OperationGM operGM;
		CIni mIni;

		UpdateData(true);

		CString m_strAccount;	
		GetDlgItemText(IDC_TXTUSER,m_strAccount);//Ҫ��ӵ��û���
		if(m_strAccount=="")//�û�������Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_InputName"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString m_strPwd;
		GetDlgItemText(IDC_TXTPWD,m_strPwd);//�û�������
		if(m_strPwd=="")//���벻��Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_InputPwd"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString m_strPwdAG;
		GetDlgItemText(IDC_TXTPWDAG,m_strPwdAG);//�ظ��û�����
		if(m_strPwdAG=="")//�ظ����벻��Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_InputNPwdAG"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		if(m_strPwd!=m_strPwdAG)//����ǰ��Ҫ��ͬ
		{
			MessageBox(theApp.operGM.ReadValue("MGM","MP_Warn_PwdNotSame"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString realName;
		GetDlgItemText(IDC_TXTREALNAME,realName);//�û�����ʵ����
		if(realName=="")//�û�����ʵ��������Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_InputRealName"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString DepartName;
		GetDlgItemText(IDC_CMBDEPART,DepartName);//�û����ڵĲ�������
		if(DepartName=="")//�û��Ĳ������Ʋ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_SelectDepart"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CTime mTime;		
		dtpEndTime.GetTime(mTime);//��ȡ���õ�ʹ��ʱЧ
		CTime curTime = CTime::GetCurrentTime();//��ȡϵͳ��ǰʱ��
		if(mTime <= curTime)//ʹ��ʱЧ����С�ڵ�ǰʱ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_TimeLimit"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		CString strLimitTime = "";
		strLimitTime.Format("%i/%i/%i 00:00:00",mTime.GetYear(),mTime.GetMonth(),mTime.GetDay());//��ʹ��ʱЧ��ʽ����CString����

		int status = cBtnExit.GetCheck() ? 0 : 1;//�Ƿ�ͣ�ø��ʺ�
		int sysAdmin = cBtnSysAdmin.GetCheck() ? 1 : cBtnDepartAdmin.GetCheck() ? 2 : 0;//��ϵͳ����Ա���ǲ��Ź���Ա

		int departID = 0;
		POSITION pos = DepartData.GetStartPosition(); //����ID�Ͳ������Ʊ�����һ��CMap��Ķ�����
		int nKey;
		CString pt;
		while (pos != NULL)//ѭ������CMap��Ķ���
		{
			DepartData.GetNextAssoc(pos, nKey, pt);//��ȡCMap��Ķ���������һ������ݣ�posΪλ�ã�nkeyΪ��ֵ��ptΪ���������
			if(pt == DepartName)//������ݺ͵�ǰѡ�еĲ���������ͬ�Ļ�
			{
				departID = nKey;//��ֵ����Ҫ��ȡ�Ĳ���ID
			}
		}

		CSocketData socketdata;
		socketdata.InitCreate(1,8);//����8������������ԱID��Ҫ��ӵ��û��������롢��ʵ������ʹ��ʱЧ���û�״̬���Ƿ�ͣ�ã����ǲ���ϵͳ����Ա������ID
		char strInt[10];
		
		int userByID=theApp.UserByID;
		
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID
		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(m_strAccount),(unsigned char *)mIni.wcharToChar(m_strAccount));//Ҫ��ӵ��û���
		socketdata.AddTFLV(CEnumCore::TagName::PassWord,CEnumCore::TagFormat::TLV_STRING,strlen(m_strPwd),(unsigned char *)mIni.wcharToChar(m_strPwd));//����
		socketdata.AddTFLV(CEnumCore::TagName::RealName,CEnumCore::TagFormat::TLV_STRING,strlen(realName),(unsigned char *)mIni.wcharToChar(realName));	//	��ʵ����
		socketdata.AddTFLV(CEnumCore::TagName::Limit,CEnumCore::TagFormat::TLV_STRING,strlen(strLimitTime),(unsigned char *)mIni.wcharToChar(strLimitTime));//ʹ��ʱЧ
		
		_itoa(status,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_Status,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�״̬���Ƿ�ͣ�ã�
		
		_itoa(sysAdmin,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SysAdmin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�ǲ���ϵͳ����Ա
		
		_itoa(departID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::DepartID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_CREATE))//��������û�������
		{
		    ::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

/// <summary>
/// �޸��û���Ϣ
/// </summary>
void CUserManage::EditUser()
{
	try
	{			
		CIni mIni;
		//OperationGM operGM;

		CString m_strAccount;//�û����������޸�
		GetDlgItemText(IDC_TXTUSER,m_strAccount);
		if(m_strAccount=="")//�û�������Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_SelectModiUser"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString realName;//Ҫ�༭���û���ʵ����
		GetDlgItemText(IDC_TXTREALNAME,realName);
		if(realName=="")//�û�����ʵ��������Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_InputRealName"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CString DepartName;
		GetDlgItemText(IDC_CMBDEPART,DepartName);//�û����ڵĲ�������
		if(DepartName=="")//�û��Ĳ������Ʋ���Ϊ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_SelectDepart"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}

		CTime mTime;		
		dtpEndTime.GetTime(mTime);//��ȡ���õ�ʹ��ʱЧ
		CTime curTime = CTime::GetCurrentTime();//��ȡϵͳ��ǰʱ��
		if(mTime <= curTime)//ʹ��ʱЧ����С�ڵ�ǰʱ��
		{
			MessageBox(theApp.operGM.ReadValue("MGM","UM_Warn_TimeLimit"),theApp.operGM.ReadValue("MGM","Warn"),MB_ICONWARNING+MB_OK);
			return;
		}
		CString strLimitTime = "";
		strLimitTime.Format("%i-%i-%i 00:00:00",mTime.GetYear(),mTime.GetMonth(),mTime.GetDay());//��ʹ��ʱЧ��ʽ����CString����

		int departID = 0;
		POSITION pos = DepartData.GetStartPosition(); //����ID�Ͳ������Ʊ�����һ��CMap��Ķ�����
		int nKey;
		CString pt;
		while (pos != NULL)//ѭ������CMap��Ķ���
		{
			DepartData.GetNextAssoc(pos, nKey, pt);//��ȡCMap��Ķ���������һ������ݣ�posΪλ�ã�nkeyΪ��ֵ��ptΪ���������
			if(pt == DepartName)//������ݺ͵�ǰѡ�еĲ���������ͬ�Ļ�
			{
				departID = nKey;//��ֵ����Ҫ��ȡ�Ĳ���ID
			}
		}

		int userID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//��ȡҪ�༭���û�ID
		int status = cBtnExit.GetCheck() ? 0 : 1;//�Ƿ�ͣ�ø��ʺ�
		int onlineActive = cBtnOnline.GetCheck() ? 1:0; //�Ƿ������û�Ϊ����״̬
		int sysAdmin = cBtnSysAdmin.GetCheck() ? 1 : cBtnDepartAdmin.GetCheck() ? 2 : 0;//��ϵͳ����Ա���ǲ��Ź���Ա

		CSocketData socketdata;
		socketdata.InitCreate(1,9);//����9������������ԱID��Ҫ�༭���û�ID��Ҫ�༭���û�������ʵ������ʹ��ʱЧ���û�״̬���Ƿ�ͣ�ã����û��Ƿ����ߡ��ǲ���ϵͳ����Ա������ID
		char strInt[10];
		
		int userByID=theApp.UserByID;
		
		_itoa(userByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ԱID
		
		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//Ҫ�༭���û�ID

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(m_strAccount),(unsigned char *)mIni.wcharToChar(m_strAccount));//Ҫ�༭���û���
		socketdata.AddTFLV(CEnumCore::TagName::RealName,CEnumCore::TagFormat::TLV_STRING,strlen(realName),(unsigned char *)mIni.wcharToChar(realName));//��ʵ����

		socketdata.AddTFLV(CEnumCore::TagName::Limit,CEnumCore::TagFormat::TLV_DATE,strlen(strLimitTime),(unsigned char *)mIni.wcharToChar(strLimitTime));//ʹ��ʱЧ
		
		_itoa(status,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_Status,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û�״̬���Ƿ�ͣ�ã�
		
		_itoa(onlineActive,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::OnlineActive,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�û��Ƿ�����
		
		_itoa(sysAdmin,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SysAdmin,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//�ǲ���ϵͳ����Ա

		_itoa(departID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::DepartID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//����ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_ADMIN,CEnumCore::ServiceKey::USER_UPDATE))//���ͱ༭�û���Ϣ������
		{
		    ::EnableWindow(this->GetParent()->m_hWnd,false);
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//��ǰ��״̬Ϊ���Ͳ�ѯ����
		}
		socketdata.Destroy();
	}
	catch(...)
	{
	}
}

/// <summary>
/// ������Ϣ
/// </summary>
void CUserManage::OnBnClickedReset()
{
	SetDlgItemText(IDC_TXTPWD,"");
	SetDlgItemText(IDC_TXTPWDAG,"");
	SetDlgItemText(IDC_TXTREALNAME,"");
	DepartList();//��ȡ�����б�
	
	CTime curTime = CTime::GetCurrentTime();
	dtpEndTime.SetTime(&curTime);//ʹ��ʱЧ����Ϊ��ǰʱ��

	cBtnExit.SetCheck(0);
	cBtnOnline.SetCheck(0);
	cBtnSysAdmin.SetCheck(0);
	cBtnDepartAdmin.SetCheck(0);
}

// �Ҽ�����û��б����Ȩ��
void CUserManage::OnNMRclickListuser(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
    {
        DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CPoint mPoint(LOWORD(dwPos), HIWORD(dwPos));

		listUser.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		nItem = listUser.SubItemHitTest(&lvinfo);//�������û��б���ѡ�е��к�
		if(nItem >= 0)
		{
			CMenu menu;
			VERIFY( menu.LoadMenu(IDR_MENUMANAGE));
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT( popup != NULL );
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, mPoint.x, mPoint.y, this );
			popup->DestroyMenu();
			popup=NULL;
			menu.DestroyMenu();
		}
    } 
	catch(...)
	{
	}
	*pResult = 0;
}

//�����û�MAC
void CUserManage::OnUpdateUserMAC()
{
	try
	{
		CIni mIni;
		//OperationGM operGM;
		CString uName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));//��ȡҪ����Ȩ�޵��û���
		int uID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//��ȡҪ����Ȩ�޵��û�ID
		
		::EnableWindow(this->m_hWnd,false);//�ø����ΪDisable��״̬
		::EnableWindow(this->GetParent()->m_hWnd,false);//�ø����ΪDisable��״̬

		theApp.updateUserMac.initVar(uName,uID);		
		theApp.updateUserMac.DoModal();		
		::SetParent(theApp.updateUserMac.m_hWnd,this->m_hWnd);//���о��������
	}
	catch(...)
	{
	}
}

//�޸��û�����
void CUserManage::OnModiUserPwd()
{
	try
	{
		CIni mIni;
		//OperationGM operGM;
		CString uName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));//��ȡҪ����Ȩ�޵��û���
		int uID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//��ȡҪ����Ȩ�޵��û�ID
		
		::EnableWindow(this->m_hWnd,false);//�ø����ΪDisable��״̬
		::EnableWindow(this->GetParent()->m_hWnd,false);//�ø����ΪDisable��״̬

		theApp.modiUserPwd.initVar(uName,uID);		
		theApp.modiUserPwd.DoModal();		
		::SetParent(theApp.modiUserPwd.m_hWnd,this->m_hWnd);//���о��������
	}
	catch(...)
	{
	}
}

// ��ѡ���û�����Ȩ��
void CUserManage::OnPopedomManage()
{
	try
	{
		CIni mIni;
		//OperationGM operGM;
		CString uName = theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","UserName"));//��ȡҪ����Ȩ�޵��û���
		int uID = atoi(mIni.wcharToChar(theApp.operGM.GetValueByColName(&listUser, nItem, theApp.operGM.ReadValue("MGM","User_ID"))));//��ȡҪ����Ȩ�޵��û�ID
		
		::EnableWindow(this->m_hWnd,false);//�ø����ΪDisable��״̬
		::EnableWindow(this->GetParent()->m_hWnd,false);//�ø����ΪDisable��״̬

		theApp.popedomManage.initVar(uName,uID);		
		theApp.popedomManage.DoModal();
		::SetParent(theApp.popedomManage.m_hWnd,this->m_hWnd);//���о��������
	}
	catch(...)
	{
	}
}

/// <summary>
/// �����ʺ�Ϊϵͳ����Ա
/// </summary>
void CUserManage::OnBnClickedChecksysmanage()
{
	if(cBtnSysAdmin.GetCheck())
	{
		cBtnDepartAdmin.SetCheck(0);
	}
}

/// <summary>
/// �����ʺ�Ϊ���Ź���Ա
/// </summary>
void CUserManage::OnBnClickedCheckdepart()
{
	if(cBtnDepartAdmin.GetCheck())
	{
		cBtnSysAdmin.SetCheck(0);
	}
}

/// <summary>
/// ���շ�����Ϣ
/// </summary>
LRESULT CUserManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//���յ�������ָ��
	int bodyLength = (int)lParam;//���յ��ĳ���
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//��ǰ��״̬Ϊ���յ��˷�����Ϣ

	CIni mIni;
	CSocketData socketdata;
	socketdata.Create(bodyLength/8);
	if(!socketdata.DeBody(lpReceive,bodyLength))
	{
		::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
		::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
		MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
		socketdata.Destroy();
		return false;
	}

	//OperationGM operGM;

	int pageCount = 0;//����ҳ����Ϣ

	switch(theApp.m_tag_id)
	{
	case CEnumCore::Message_Tag_ID::USER_QUERY_ALL_RESP://������ص��Ƕ������û��б����Ӧ
		{			
			if(pageInfo)//����Ѿ����˷�ҳ��Ϣ
			{
				theApp.operGM.BuildDataTable(&socketdata,&listUser,&pageCount);//��CListCtrl�й���õ�������
			}
			else
			{
				theApp.operGM.BuildDataTable(&socketdata,&listUser,&pageCount);

				if(pageCount<=0)//�������ֵΪ��
				{
					pageInfo = false;//��ҳ��ϢΪfalse,���ܷ�ҳ
					cmbPage.ResetContent();//����ҳ����CComboBoxҲΪ��
					while(listUser.DeleteColumn(0)){}//CListCtrlΪ��
				}
				else
				{
					cmbPage.ResetContent();//����ҳ����CComboBoxҲΪ��
					for(int i=1;i<=pageCount;i++)
					{
						CString str="";
						str.Format("%d",i);
						cmbPage.AddString(str);//������е�ҳ��
					}
					cmbPage.SetCurSel(0);//�ʼ��ʾ��һҳ
					if(pageCount == 1)
					{
						pageInfo = false;//���ֻ��һҳ����ҳ��ϢҲΪfalse������Ҫ��ҳ
					}
					else
					{
						pageInfo = true;//��ҳ��ϢΪtrue�����Է�ҳ���в�ѯ
					}
				}
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::DEPART_QUERY_RESP://������ص��Ƕ��������б����Ӧ
		{
			if(!DepartData.IsEmpty())
			{
				DepartData.RemoveAll();
			}
			for(int i=0;i<socketdata.getQueryNum();i++)
			{
				int departID = atoi((char*)&socketdata.getTLVByName(i+1,CEnumCore::TagName::DepartID).lpdata);//�ӵõ��������л�ȡ���еĲ���ID��Ϣ
				CString departName = (LPCSTR)&socketdata.getTLVByName(i+1,CEnumCore::TagName::DepartName).lpdata;//��ȡ����������Ϣ
				DepartData.SetAt(departID,departName);//������ID�Ͳ��������Լ�-ֵ�Ե���ʽ������CMap��Ķ�����
			}
			theApp.operGM.BuildCombox(&socketdata,&cmbDepart);	//���챣�沿��������Ϣ��CComboBox
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_CREATE_RESP://������ص��ǲ������������Ӧ
	case CEnumCore::Message_Tag_ID::USER_UPDATE_RESP:
	case CEnumCore::Message_Tag_ID::USER_DELETE_RESP:
		{
			CGlobalStruct::TFLV m_tflv=socketdata.getTLVBynIndex(1);
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGM.ShowResult(result);//��ʾ�������

			tbcResult.SetCurSel(0);
			GetDlgItem(IDC_LISTUSER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LBLPAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CMBPAGE)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATUPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTPWDAG)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATREALNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TXTREALNAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CMBDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATENDTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_DTPENDTIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKEXIT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKUSERONLINE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKSYSMANAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_CHECKDEPART)->ShowWindow(SW_HIDE);
			GetDlgItem(IDADDUSER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDRESET)->ShowWindow(SW_HIDE);

			InitUserList();//�ٴβ�ѯ�û��б���Ϣ
		}
		break;
	default:
		{
			MessageBox("Error","Error",0);
		}
		break;
	}
	::EnableWindow(this->GetParent()->m_hWnd,true);//���յ�������Ϣ֮�����������涼���Enable��״̬����ʱ���Է��µ�����
	::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	socketdata.Destroy();
	return true;
}

// �رնԻ���
void CUserManage::OnClose()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//�رմ���
	if(!DepartData.IsEmpty())
	{
		DepartData.RemoveAll();
	}
	DestroyWindow();
	CDialog::OnClose();
}
