// SDOFamilyManager.cpp : 实现文件
//

#include "stdafx.h"
#include "M_SDO.h"
#include "SDOFamilyManager.h"
#include ".\sdofamilymanager.h"

#include "OperationSDO.h"

// CSDOFamilyDonate 对话框
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


// CSDOFamilyManager 消息处理程序

//初始化对话框

BOOL CSDOFamilyManager::OnInitDialog()
{
	CSDOFamilyBaseDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"FM_UI_FamilyManager"));
	const char const *pMenuTextKey[] =
	{
		"",								// 查詢帳號的角色信息，不需要菜單.
		"MenuText_QueryMember",		// 查询家族成员信息
		"MenuText_QueryBrand",		//查询家族徽章信息
		"MenuText_DelFamily",		//删除家族
		"MenuText_UpdateMember",	//修改家族成员
		"MenuText_AddBrand",		//添加徽章
		"MenuText_DelBrand",		//删除徽章
	};
	CString strMenuText;

	//查询家族基本信息
	CreateCtrlList(m_listFamilyInfo, IDC_LIST_FAMILY_INFO);
	CreateCtrlComCmb(m_cmbFamilyPage, IDC_CMB_PAGE_FAMILY_INFO);

	m_menuFamily.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_MEMBER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_MEMBER, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_QUERY_BRAND-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_QUERY_BRAND, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_DEL_FAMILY-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuFamily.AppendMenu(MF_STRING, IDM_DEL_FAMILY, (LPCTSTR)strMenuText);

	//查询家族成员信息
	CreateCtrlList(m_listMemberInfo, IDC_LIST_MEMBER_INFO);
	CreateCtrlComCmb(m_cmbMemberPage, IDC_CMB_PAGE_MEMBER);

	m_menuMember.CreatePopupMenu();
	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_UPDATE_MEMBER-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuMember.AppendMenu(MF_STRING, IDM_UPDATE_MEMBER, (LPCTSTR)strMenuText);

	//家族成员修改
	CreateCtrlStatic(m_staticFamilyID, IDC_STATICBASEREF,IDC_STATIC_FAMILYID);//家族ID
	CreateCtrlEdit(m_editFamilyID, IDC_EDITBASEREF, IDC_EDIT_FAMILYID);
	CreateCtrlStatic(m_staticFamilyName, IDC_STATIC_FAMILYID, IDC_STATIC_FAMILYNAME);//家族名称
	CreateCtrlEdit(m_editFamilyName, IDC_EDIT_FAMILYID, IDC_EDIT_FAMILYNAME);
	CreateCtrlStatic(m_staticMemberType, IDC_STATIC_FAMILYNAME, IDC_STATIC_MEMBERTYPE);
	CreateCtrlComCmb(m_cmbMemberType, IDC_CMB_MEMBERTYPE, IDC_EDIT_FAMILYNAME);
	////MoveImpButton(IDC_CMB_MEMBERTYPE, IDC_BTNBASEIMP);
	m_editFamilyID.SetReadOnly(true);
	m_editFamilyName.SetReadOnly(true);

	//家族徽章信息
	CreateCtrlList(m_listBrandInfo, IDC_LIST_BRAND_INFO);
	CreateCtrlComCmb(m_cmbBrandPage, IDC_CMB_PAGE_BRAND);
	m_menuBrand.CreatePopupMenu();

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_ADD_BRAND-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuBrand.AppendMenu(MF_STRING, IDM_ADD_BRAND, (LPCTSTR)strMenuText);

	strMenuText = theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION, pMenuTextKey[IDM_DEL_BRAND-IDM_QUERY_ACCOUNT_CHAR]);
	m_menuBrand.AppendMenu(MF_STRING, IDM_DEL_BRAND, (LPCTSTR)strMenuText);

	//添加家族徽章
	CreateCtrlStatic(m_staticUserID, IDC_STATIC_FAMILYID, IDC_STATIC_USERID);//用户ID
	CreateCtrlEdit(m_editUserID, IDC_EDIT_FAMILYID, IDC_EDIT_USERID);
	CreateCtrlStatic(m_staticBrandType, IDC_STATIC_USERID, IDC_STATIC_BRANDTYPE);//徽章类型
	CreateCtrlComCmb(m_cmbBrandType, IDC_CMB_BRANDTYPE, IDC_EDIT_USERID);
	CreateCtrlStatic(m_staticBrandNum, IDC_STATIC_BRANDTYPE, IDC_STATIC_BRANDNUM);//徽章数量
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

	// Tab控件标签文本在.ini文件中的key.
	const char const *pTabTextKey[] = 
	{
		"FI_UI_tpgBasicInfo",//家族基本
		"FI_UI_tpgMemberInfo",//家族成员信息
		"FM_UI_tpgMemberUpdate",//家族成员修改
		"FI_UI_tpgBrandInfo",//家族徽章信息
		"FM_UI_tpgBrandAdd",//添加家族徽章
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


	// 以下控件总是显示.
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
	// 异常: OCX 属性页应返回 FALSE
}

void CSDOFamilyManager::QueryOperation(int nTabCurSel)//继承BaseDlg
{
	ASSERT(nTabCurSel == TII_QUERY_FAMILY);

	ResetCmbCtrl(m_cmbFamilyPage);

	//maple add
	CString strPageIndex = GetCmbCurSelText(m_cmbFamilyPage);
	QueryFamilyInfo(strPageIndex);
}


void CSDOFamilyManager::ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)//继承BaseDlg
{
	switch(msgTagID)
	{
	case CEnumCore::Message_Tag_ID::SDO_Family_Info_QUERY_RESP://家族基本信息
		SetDataForListCtrl(m_listFamilyInfo, socketData, m_cmbFamilyPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_FamilyMember_Query_RESP://家族成员
		SetDataForListCtrl(m_listMemberInfo, socketData, m_cmbMemberPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_Personal_Emblem_Query_RESP://家族徽章
		SetDataForListCtrl(m_listBrandInfo, socketData, m_cmbBrandPage);
		break;
	case CEnumCore::Message_Tag_ID::SDO_Family_Emblem_Insert_Query_RESP://添加徽章
	case CEnumCore::Message_Tag_ID::SDO_Family_Duty_Query_RESP://修改成员信息
	case CEnumCore::Message_Tag_ID::SDO_Family_Emblem_Delete_Query_RESP://删除徽章
	case CEnumCore::Message_Tag_ID::SDO_Family_Delete_Query_RESP://删除家族
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

BOOL CSDOFamilyManager::ClearDataForCtrl()//继承BaseDlg
{
	m_menuFamily.DestroyMenu();
	m_menuMember.DestroyMenu();
	m_menuBrand.DestroyMenu();
	return TRUE;
}

void CSDOFamilyManager::OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)//继承BaseDlg
{
}

void CSDOFamilyManager::ImplementUpdateOperation(int nTabCurSel)//继承BaseDlg
{
	CEnumCore::ServiceKey eServiceKey=NULL;
	CString strFamilyID("");
	CString strFamilyName("");
	CString strUserID("");

	CString strMemberType("");////成员类型

	CString strBrandType("");//徽章类型
	CString strBrandNum("");//徽章数量

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

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//服务器名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// 家族名称
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyName, CEnumCore::TagFormat::TLV_STRING,
			strFamilyName.GetLength(), (unsigned char *)(LPCTSTR)strFamilyName);

		// 家族ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyID, CEnumCore::TagFormat::TLV_STRING,
			strFamilyID.GetLength(), (unsigned char *)(LPCTSTR)strFamilyID);
		
		//操作员ID
		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);
		
		//成员类型
		_itoa(Type,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Type,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);

		//玩家ID
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING, 
			strUserID.GetLength(), (unsigned char *)(LPCTSTR)strUserID);
		
		//徽章类型
		socketdata.AddTFLV(CEnumCore::TagName::SDO_Emblemtype,CEnumCore::TagFormat::TLV_INTEGER,
			strBrandType.GetLength(),(unsigned char *)(LPCTSTR)strBrandType);
		
		//徽章数量
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
//删除家族
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

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//服务器名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// 家族名称
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyName, CEnumCore::TagFormat::TLV_STRING,
			strFamilyName.GetLength(), (unsigned char *)(LPCTSTR)strFamilyName);

		// 家族ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyID, CEnumCore::TagFormat::TLV_STRING,
			strFamilyID.GetLength(), (unsigned char *)(LPCTSTR)strFamilyID);

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);//操作员ID

		int nDataLen = socketdata.EnBody();
		theApp.operSDO.SendQuery((unsigned char *)socketdata.getDes(), nDataLen, CEnumCore::ServiceKey::SDO_Family_Delete_Query);

		EnableWindow(FALSE);
	}
	catch(...)
	{
	}
}

//家族成员修改
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

//添加徽章
void CSDOFamilyManager::OnMenuCmdAddBrand()
{
	SetTabCtrlItemCurSel(TII_ADD_BRAND);
	CString strFamilyID = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_FamilyID);
	CString strUserID = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_UserIndexID);

	SetDlgItemText(IDC_EDIT_FAMILYID, strFamilyID);
	SetDlgItemText(IDC_EDIT_USERID, strUserID);
}

//删除徽章
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
	CString strBrandType = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_Emblemtype);//徽章类型
	CString strUserID = GetDataFromListCtrl(m_listBrandInfo, CEnumCore::TagName::SDO_UserIndexID);
	
	int userbyID = theApp.UserByID;
	char strInt[10];

	try
	{
		CSocketData socketdata;	
		socketdata.InitCreate(1, 10);

		// 服务器IP.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerIP, CEnumCore::TagFormat::TLV_STRING, 
			strServerIP.GetLength(), (unsigned char *)(LPCTSTR)strServerIP);

		//服务器名
		socketdata.AddTFLV(CEnumCore::TagName::SDO_ServerName, CEnumCore::TagFormat::TLV_STRING, 
			strServerName.GetLength(), (unsigned char *)(LPCTSTR)strServerName);

		// 家族名称
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyName, CEnumCore::TagFormat::TLV_STRING,
			strFamilyName.GetLength(), (unsigned char *)(LPCTSTR)strFamilyName);

		// 家族ID.
		socketdata.AddTFLV(CEnumCore::TagName::SDO_FamilyID, CEnumCore::TagFormat::TLV_STRING,
			strFamilyID.GetLength(), (unsigned char *)(LPCTSTR)strFamilyID);

		_itoa(userbyID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,
			sizeof(int),(unsigned char *)&strInt);//操作员ID

		//玩家ID
		socketdata.AddTFLV(CEnumCore::TagName::SDO_UserIndexID, CEnumCore::TagFormat::TLV_STRING,
			strUserID.GetLength(), (unsigned char *)(LPCTSTR)strUserID);

		//徽章类型
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


//成员类型初始化
void CSDOFamilyManager::MemberType()
{
	m_cmbMemberType.ResetContent();
	m_cmbMemberType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"FamilyChief"));
	m_cmbMemberType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"Assistant_FamilyChief"));
	m_cmbMemberType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"NormalMember"));
	m_cmbMemberType.AddString(theApp.operSDO.ReadValue(INI_WNDTEXT_SECTION,"Administrator"));
	m_cmbMemberType.SetCurSel(0);
}


//导入徽章类型
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


