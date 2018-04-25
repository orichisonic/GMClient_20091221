// SDOFamilyManager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOFamilyManager.h"
#include ".\sdofamilymanager.h"

#include "OperationSDO.h"

// CSDOFamilyDonate �Ի���
static LPCSTR INI_WNDTEXT_SECTION ="MSDO"; //"WNDTEXT";

CSDOFamilyManager::CSDOFamilyManager(CWnd* pParent /*=NULL*/)
	: CSDOFamilyBaseDlg(pParent)
{
}

CSDOFamilyManager::~CSDOFamilyManager()
{
}


BEGIN_MESSAGE_MAP(CSDOFamilyManager, CSDOFamilyBaseDlg)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_FAMILY_INFO, OnLvnColumnclickListFamilyInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_FAMILY_INFO, OnCbnSelchangeCmbFamilyInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FAMILY_INFO, OnNMRclickListFamilyInfo)
	ON_COMMAND(IDM_QUERY_MEMBER, OnMenuCmdQueryMember)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_MEMBER_INFO, OnLvnColumnclickListMemberInfo)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_MEMBER, OnCbnSelchangeCmbMemberInfo)
	ON_NOTIFY(NM_RCLICK,IDC_LIST_MEMBER_INFO, OnNMRclickListMemberInfo)
	ON_COMMAND(IDM_DEL_FAMILY, OnMenuCmdDelFamily)
	ON_COMMAND(IDM_UPDATE_MEMBER, OnMenuCmdUpdateMember)
	ON_COMMAND(IDM_QUERY_BRAND, OnMenuCmdQueryBrand)
	ON_CBN_SELCHANGE(IDC_CMB_PAGE_BRAND, OnCbnSelchangeCmbBrandInfo)
	ON_COMMAND(IDM_ADD_BRAND, OnMenuCmdAddBrand)
	ON_COMMAND(IDM_DEL_BRAND, OnMenuCmdDelBrand)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_BRAND_INFO, OnLvnColumnclickListBrandInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_BRAND_INFO, OnNMRclickListBrandInfo)
END_MESSAGE_MAP()


// CSDOFamilyManager ��Ϣ�������

//��ʼ���Ի���

BOOL CSDOFamilyManager::OnInitDialog()
{
	CSDOFamilyBaseDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"FM_UI_FamilyManager"));
	const char const *pMenuTextKey[] =
	{
		"",								// ��ԃ��̖�Ľ�ɫ��Ϣ������Ҫ�ˆ�.
		"MenuText_QueryMember",		// ��ѯ�����Ա��Ϣ
		"MenuText_QueryBrand",		//��ѯ���������Ϣ
		"MenuText_DelFamily",		//ɾ������
		"MenuText_UpdateMember",	//�޸ļ����Ա
		"MenuText_AddBrand",		//��ӻ���
		"MenuText_DelBrand",		//ɾ������
	};
	CString strMenuText;

	//��ѯ���������Ϣ
	CreateCtrlList(m_listFamilyInfo, IDC_LIST_FAMILY_INFO);
	CreateCtrlComCmb(m_cmbFamilyPage, IDC_CMB_PAGE_FAMILY_INFO);

	m_menuFamily.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_MEMBER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_MEMBER, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_BRAND-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_BRAND, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_DEL_FAMILY-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_DEL_FAMILY, (LPCTSTR)strMenuText);

	//��ѯ�����Ա��Ϣ
	CreateCtrlList(m_listMemberInfo, IDC_LIST_MEMBER_INFO);
	CreateCtrlComCmb(m_cmbMemberPage, IDC_CMB_PAGE_MEMBER);

	m_menuMember.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_UPDATE_MEMBER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuMember.AppendMenu(MF_STRING, IDM_UPDATE_MEMBER, (LPCTSTR)strMenuText);

	//�����Ա�޸�
	CreateCtrlStatic(m_staticFamilyID, IDC_STATICBASEREF,IDC_STATIC_FAMILYID);//����ID
	CreateCtrlEdit(m_editFamilyID, IDC_EDITBASEREF, IDC_EDIT_FAMILYID);
	CreateCtrlStatic(m_staticFamilyName, IDC_STATIC_FAMILYID, IDC_STATIC_FAMILYNAME);//��������
	CreateCtrlEdit(m_editFamilyName, IDC_EDIT_FAMILYID, IDC_EDIT_FAMILYNAME);
	CreateCtrlStatic(m_staticMemberType, IDC_STATIC_FAMILYNAME, IDC_STATIC_MEMBERTYPE);
	CreateCtrlComCmb(m_cmbMemberType, IDC_CMB_MEMBERTYPE, IDC_EDIT_FAMILYNAME);
	////MoveImpButton(IDC_CMB_MEMBERTYPE, IDC_BTNBASEIMP);
	m_editFamilyID.SetReadOnly(true);
	m_editFamilyName.SetReadOnly(true);

	//���������Ϣ
	CreateCtrlList(m_listBrandInfo, IDC_LIST_BRAND_INFO);
	CreateCtrlComCmb(m_cmbBrandPage, IDC_CMB_PAGE_BRAND);
	m_menuBrand.CreatePopupMenu();

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_ADD_BRAND-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuBrand.AppendMenu(MF_STRING, IDM_ADD_BRAND, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_DEL_BRAND-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuBrand.AppendMenu(MF_STRING, IDM_DEL_BRAND, (LPCTSTR)strMenuText);

	//��Ӽ������
	CreateCtrlStatic(m_staticUserID, IDC_STATIC_FAMILYID, IDC_STATIC_USERID);//�û�ID
	CreateCtrlEdit(m_editUserID, IDC_EDIT_FAMILYID, IDC_EDIT_USERID);
	CreateCtrlStatic(m_staticBrandType, IDC_STATIC_USERID, IDC_STATIC_BRANDTYPE);//��������
	CreateCtrlComCmb(m_cmbBrandType, IDC_CMB_BRANDTYPE, IDC_EDIT_USERID);
	CreateCtrlStatic(m_staticBrandNum, IDC_STATIC_BRANDTYPE, IDC_STATIC_BRANDNUM);//��������
	CreateCtrlEdit(m_editBrandNum, IDC_CMB_BRANDTYPE, IDC_EDIT_BRANDNUM);
	m_editUserID.SetReadOnly(true);

	MoveImpButton(IDC_EDIT_BRANDNUM, IDC_BTNBASEIMP);

	DWORD dwTabItemCtrlID[][TAB_ITEM_CTRL_MAX_NUM] = 
	{
		{IDC_LIST_FAMILY_INFO, IDC_CMB_PAGE_FAMILY_INFO, IDOK,IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE, IDC_STATICMENUPROMPT, 0,0,0},
		{IDC_LIST_MEMBER_INFO, IDC_CMB_PAGE_MEMBER, IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,IDC_STATICMENUPROMPT,0,0,0,0},
		{IDC_STATIC_FAMILYID, IDC_EDIT_FAMILYID, IDC_STATIC_FAMILYNAME, IDC_EDIT_FAMILYNAME, IDC_STATIC_MEMBERTYPE, IDC_CMB_MEMBERTYPE,IDC_BTNBASEIMP,0,0},
		{IDC_LIST_BRAND_INFO, IDC_CMB_PAGE_BRAND, IDC_STATICBASEGRPPAGE, IDD_STATICBASEPAGE,IDC_STATICMENUPROMPT,0,0,0,0},
		{IDC_STATIC_FAMILYID, IDC_EDIT_FAMILYID, IDC_STATIC_USERID, IDC_EDIT_USERID, IDC_STATIC_BRANDTYPE, IDC_CMB_BRANDTYPE, IDC_STATIC_BRANDNUM, IDC_EDIT_BRANDNUM ,IDC_BTNBASEIMP},
	};

	// Tab�ؼ���ǩ�ı���.ini�ļ��е�key.
	const char const *pTabTextKey[] = 
	{
		"FI_UI_tpgBasicInfo",//�������
		"FI_UI_tpgMemberInfo",//�����Ա��Ϣ
		"FM_UI_tpgMemberUpdate",//�����Ա�޸�
		"FI_UI_tpgBrandInfo",//���������Ϣ
		"FM_UI_tpgBrandAdd",//��Ӽ������
	};

	TCB_ITEM ti[TII_ITEM_COUNT];
	for (int i=0; i<TII_ITEM_COUNT; i++)
	{
		LPTCB_ITEM_DATA lptid = NULL;
		for (int j=0; j<TAB_ITEM_CTRL_MAX_NUM; j++)
		{
			if (lptid == NULL)
			{
				lptid = new TCB_ITEM_DATA;
				ti[i].lptid = lptid;
			}
			else
			{
				lptid->pNext = new TCB_ITEM_DATA;
				lptid = lptid->pNext;
			}
			lptid->dwCtrlID = dwTabItemCtrlID[i][j];
		}

		ti[i].strKey = pTabTextKey[i];
	}

	CString strSec(INI_WNDTEXT_SECTION);
	InitTableCtrl(ti, TII_ITEM_COUNT, strSec);


	// ���¿ؼ�������ʾ.
	CTRLID_INI_KEY cik[] = 
	{
		IDC_STATICBASEGRPPAGE,	"PageGroupText",
		IDD_STATICBASEPAGE,		"PleaseSelPageCount",
		IDC_STATICMENUPROMPT,	"ListCtrlMenuPrompt",
		IDC_STATIC_FAMILYID,	"FM_UI_FamilyID",
		IDC_STATIC_FAMILYNAME,	"FM_UI_FamilyName",
		IDC_STATIC_MEMBERTYPE,	"FM_UI_MemberType",
		IDC_STATIC_USERID,		"FM_UI_UserID",
		IDC_STATIC_BRANDTYPE,	"FM_UI_BrandType",
		IDC_STATIC_BRANDNUM,	"FM_UI_BrandNum",
	};
	for (int i=0; i<sizeof(cik)/sizeof(CTRLID_INI_KEY); i++)
	{
		CWnd* pWnd = GetDlgItem(cik[i].dwCtrlID);
		ASSERT(pWnd != NULL);
		////pWnd->ShowWindow(SW_SHOW);
		CString strText=theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, CString(cik[i].lpKey));
		pWnd->SetWindowText(strText);
	}
	BrandType();
	MemberType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSDOFamilyManager::QueryOperation(int nTabCurSel)//�̳�BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_FAMILY);

	ResetCmbCtrl(m_cmbFamilyPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}


void CSDOFamilyManager::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//�̳�BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_Family_Info_QUERY_RESP://���������Ϣ
		SetDataForListCtrl(m_listFamilyInfo, socketData, m_cmbFamilyPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_FamilyMember_Query_RESP://�����Ա
		SetDataForListCtrl(m_listMemberInfo, socketData, m_cmbMemberPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_Personal_Emblem_Query_RESP://�������
		SetDataForListCtrl(m_listBrandInfo, socketData, m_cmbBrandPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_Emblem_Insert_Query_RESP://��ӻ���
	case CEnumCore::Message_Tag_ID::SDO_Family_Duty_Query_RESP://�޸ĳ�Ա��Ϣ
	case CEnumCore::Message_Tag_ID::SDO_Family_Emblem_Delete_Query_RESP://ɾ������
	case CEnumCore::Message_Tag_ID::SDO_Family_Delete_Query_RESP://ɾ������
		/*{
			CGlobalStruct::TFLV tflvErr = socketData.getTLVBynIndex(1);
			if ((unsigned short)tflvErr.m_tagName == CEnumCore::TagName::MESSAGE)
			{
				AfxMessageBox((LPTSTR)tflvErr.lpdata);
			}
		}*/
		break;
	default:
		break;
	}
}

BOOL CSDOFamilyManager::ClearDataForCtrl()//�̳�BaseDlg
{
	m_menuFamily.DestroyMenu();
	m_menuMember.DestroyMenu();
	m_menuBrand.DestroyMenu();
	return TRUE;
}

void CSDOFamilyManager::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//�̳�BaseDlg
{
}

void CSDOFamilyManager::ImplementUpdateOperation(int nTabCurSel)//�̳�BaseDlg
{
	CEnumCore::ServiceKey eServiceKey=NULL;
	CString strFamilyID("");
	CString strFamilyName("");
	CString strUserID("");

	CString strMemberType("");////��Ա����

	CString strBrandType("");//��������
	CString strBrandNum("");//��������

	switch(nTabCurSel)
	{
	case TII_UPDATE_MEMBER:
		{
			GetDlgItemText(IDC_EDIT_FAMILYID, strFamilyID);
			GetDlgItemText(IDC_EDIT_FAMILYNAME, strFamilyName);
			strUserID = GetDataFromListCtrl(m_listMemberInfo, CEnumCore::TagName::SDO_UserIndexID);
			GetDlgItemText(IDC_CMB_MEMBERTYPE, strMemberType);
			eServiceKey = CEnumCore::ServiceKey::SDO_Family_Duty_Query;
		}
		break;
	case TII_ADD_BRAND:
		{
			GetDlgItemText(IDC_EDIT_FAMILYID, strFamilyID);
			GetDlgItemText(IDC_EDIT_USERID, strUserID);
			strFamilyName = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_FamilyName);
			GetDlgItemText(IDC_CMB_BRANDTYPE, strBrandType);
			GetDlgItemText(IDC_EDIT_BRANDNUM, strBrandNum);
			eServiceKey = CEnumCore::ServiceKey::SDO_Family_Emblem_Insert_Query;
		}
		break;
	default:
		break;
	}
	
	
	int Type=0;

	if(strMemberType == theApp.operSDO.ReadValue("MSDO","FamilyChief"))
		Type=255;
	else if(strMemberType == theApp.operSDO.ReadValue("MSDO","Assistant_FamilyChief"))
		Type=2;
	else if(strMemberType == theApp.operSDO.ReadValue("MSDO","NormalMember"))
		Type=0;
	else if(strMemberType == theApp.operSDO.ReadValue("MSDO","Administrator"))
		Type=1;

	int userbyID = theApp.UserByID;
	char strInt[10];

	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 10);

		// ������IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// ��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyName, CEnumCore::TagFormat::TLV_STRING,
			strFamilyName.GetLength(), (unsigned char *)(LPCTSTR)strFamilyName);

		// ����ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyID, CEnumCore::TagFormat::TLV_STRING,
			strFamilyID.GetLength(), (unsigned char *)(LPCTSTR)strFamilyID);
		
		//����ԱID
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);
		
		//��Ա����
		_itoa(Type,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Type,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);

		//���ID
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING, 
			strUserID.GetLength(), (unsigned char *)(LPCTSTR)strUserID);
		
		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Emblemtype,CEnumCore::TagFormat::TLV_INTEGER,
			strBrandType.GetLength(),(unsigned char *)(LPCTSTR)strBrandType);
		
		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Emblemnum,CEnumCore::TagFormat::TLV_INTEGER,
			strBrandNum.GetLength(),(unsigned char *)(LPCTSTR)strBrandNum);

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, eServiceKey);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}

}

void CSDOFamilyManager::OnLvnColumnclickListFamilyInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listFamilyInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOFamilyManager::OnCbnSelchangeCmbFamilyInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}

void CSDOFamilyManager::OnNMRclickListFamilyInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listFamilyInfo, m_menuFamily, lpItemActive->ptAction);
}

void CSDOFamilyManager::OnMenuCmdQueryMember()
{
	SetTabCtrlItemCurSel(TII_QUERY_MEMBER);
	CString strPageIndex = GetCmbCurSelText(m_cmbMemberPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_FamilyMember_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyManager::OnLvnColumnclickListMemberInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listMemberInfo,pNMHDR,pResult);
	*pResult = 0;
}
void CSDOFamilyManager::OnCbnSelchangeCmbMemberInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbMemberPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_FamilyMember_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyManager::OnNMRclickListMemberInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listMemberInfo, m_menuMember, lpItemActive->ptAction);
}
//ɾ������
void CSDOFamilyManager::OnMenuCmdDelFamily()
{
	CString strMsg = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"NI_Hint_DelFamily");//operCG2.ReadValue("MCG2","NI_Hint_DelNotice"); 
	if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
	{
		return;
	}

	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();
	CString strFamilyName = GetDataFromListCtrl(m_listFamilyInfo, CEnumCore::TagName::SDO_FamilyName);
	CString strFamilyID = GetDataFromListCtrl(m_listFamilyInfo, CEnumCore::TagName::SDO_FamilyID);
	
	int userbyID = theApp.UserByID;
	char strInt[10];

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 6);

		// ������IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// ��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyName, CEnumCore::TagFormat::TLV_STRING,
			strFamilyName.GetLength(), (unsigned char *)(LPCTSTR)strFamilyName);

		// ����ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyID, CEnumCore::TagFormat::TLV_STRING,
			strFamilyID.GetLength(), (unsigned char *)(LPCTSTR)strFamilyID);

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);//����ԱID

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_Family_Delete_Query);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}

//�����Ա�޸�
void CSDOFamilyManager::OnMenuCmdUpdateMember()
{
	SetTabCtrlItemCurSel(TII_UPDATE_MEMBER);

	//CString strServerIP = GetGameServerIP();
	//CString strServerName = GetGameServerName();
	CString strFamilyName = GetDataFromListCtrl(m_listMemberInfo, CEnumCore::TagName::SDO_FamilyName);
	CString strFamilyID = GetDataFromListCtrl(m_listMemberInfo, CEnumCore::TagName::SDO_FamilyID);
	CString strUserID = GetDataFromListCtrl(m_listMemberInfo, CEnumCore::TagName::SDO_UserIndexID);

	SetDlgItemText(IDC_EDIT_FAMILYID, strFamilyID);
	SetDlgItemText(IDC_EDIT_FAMILYNAME, strFamilyName);


}

void CSDOFamilyManager::OnMenuCmdQueryBrand()
{
	SetTabCtrlItemCurSel(TII_QUERY_BRAND);
	CString strPageIndex = GetCmbCurSelText(m_cmbBrandPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_Personal_Emblem_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyManager::OnCbnSelchangeCmbBrandInfo()
{
	CString strPageIndex = GetCmbCurSelText(m_cmbBrandPage);
	QueryOtherInfo(CEnumCore::ServiceKey::SDO_Personal_Emblem_Query, strPageIndex, m_listFamilyInfo);
}

void CSDOFamilyManager::OnLvnColumnclickListBrandInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	theApp.operSDO.SortListInfo(&m_listBrandInfo,pNMHDR,pResult);
	*pResult = 0;
}

void CSDOFamilyManager::OnNMRclickListBrandInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpItemActive = (LPNMITEMACTIVATE)pNMHDR;
	if (lpItemActive->iItem < 0)
		return;

	PopupMenuForListCtrlRClick(m_listBrandInfo, m_menuBrand, lpItemActive->ptAction);

}

//��ӻ���
void CSDOFamilyManager::OnMenuCmdAddBrand()
{
	SetTabCtrlItemCurSel(TII_ADD_BRAND);
	CString strFamilyID = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_FamilyID);
	CString strUserID = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_UserIndexID);

	SetDlgItemText(IDC_EDIT_FAMILYID, strFamilyID);
	SetDlgItemText(IDC_EDIT_USERID, strUserID);
}

//ɾ������
void CSDOFamilyManager::OnMenuCmdDelBrand()
{
	CString strMsg = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"NI_Hint_DelBrand");
	if (AfxMessageBox(strMsg, MB_YESNO) == IDNO) 
	{
		return;
	}

	CString strServerIP = GetGameServerIP();
	CString strServerName = GetGameServerName();
	CString strFamilyName = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_FamilyName);
	CString strFamilyID = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_FamilyID);
	CString strBrandType = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_Emblemtype);//��������
	CString strUserID = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_UserIndexID);
	
	int userbyID = theApp.UserByID;
	char strInt[10];

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 10);

		// ������IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// ��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyName, CEnumCore::TagFormat::TLV_STRING,
			strFamilyName.GetLength(), (unsigned char *)(LPCTSTR)strFamilyName);

		// ����ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyID, CEnumCore::TagFormat::TLV_STRING,
			strFamilyID.GetLength(), (unsigned char *)(LPCTSTR)strFamilyID);

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);//����ԱID

		//���ID
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING,
			strUserID.GetLength(), (unsigned char *)(LPCTSTR)strUserID);

		//��������
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Emblemtype,CEnumCore::TagFormat::TLV_INTEGER,
			strBrandType.GetLength(),(unsigned char *)(LPCTSTR)strBrandType);

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_Family_Emblem_Delete_Query);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}


//��Ա���ͳ�ʼ��
void CSDOFamilyManager::MemberType()
{
	m_cmbMemberType.ResetContent();
	m_cmbMemberType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"FamilyChief"));
	m_cmbMemberType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"Assistant_FamilyChief"));
	m_cmbMemberType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"NormalMember"));
	m_cmbMemberType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"Administrator"));
	m_cmbMemberType.SetCurSel(0);
}


//�����������
void CSDOFamilyManager::BrandType()
{
	m_cmbBrandType.ResetContent();
	m_cmbBrandType.AddString("0");
	m_cmbBrandType.AddString("1");
	m_cmbBrandType.AddString("2");
	m_cmbBrandType.AddString("3");
	m_cmbBrandType.AddString("4");
	m_cmbBrandType.AddString("5");
	m_cmbBrandType.AddString("6");
	m_cmbBrandType.AddString("7");
	m_cmbBrandType.AddString("8");
	m_cmbBrandType.AddString("9");
	m_cmbBrandType.AddString("10");
	m_cmbBrandType.AddString("11");
	m_cmbBrandType.AddString("12");
	m_cmbBrandType.AddString("13");
	m_cmbBrandType.AddString("14");
	m_cmbBrandType.AddString("15");
	m_cmbBrandType.AddString("16");
	m_cmbBrandType.AddString("17");
	m_cmbBrandType.AddString("18");
	m_cmbBrandType.AddString("19");
	m_cmbBrandType.AddString("20");
	m_cmbBrandType.AddString("21");
	m_cmbBrandType.AddString("22");
	m_cmbBrandType.AddString("23");
	m_cmbBrandType.AddString("24");
	m_cmbBrandType.AddString("25");
	m_cmbBrandType.AddString("26");
	m_cmbBrandType.AddString("27");
	m_cmbBrandType.AddString("28");
	m_cmbBrandType.AddString("29");
	m_cmbBrandType.AddString("30");
	m_cmbBrandType.AddString("31");
	m_cmbBrandType.AddString("32");
	m_cmbBrandType.AddString("33");
	m_cmbBrandType.AddString("34");
	m_cmbBrandType.AddString("35");
	m_cmbBrandType.AddString("36");
	m_cmbBrandType.AddString("37");
	m_cmbBrandType.AddString("38");
	m_cmbBrandType.AddString("39");
	m_cmbBrandType.AddString("40");
	m_cmbBrandType.AddString("41");
	m_cmbBrandType.AddString("42");
	m_cmbBrandType.AddString("43");
	m_cmbBrandType.AddString("44");
	m_cmbBrandType.AddString("45");
	m_cmbBrandType.AddString("46");
	m_cmbBrandType.AddString("47");
	m_cmbBrandType.AddString("48");
	m_cmbBrandType.AddString("49");

	m_cmbBrandType.SetCurSel(0);
}


