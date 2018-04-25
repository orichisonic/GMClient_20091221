#pragma once
#include "afxwin.h"


// CSDOBaseDlg 对话框

class CSDOBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CSDOBaseDlg)

public:
	CSDOBaseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSDOBaseDlg();

// 对话框数据
	enum { IDD = IDD_BASEDIALOG };

	void SetRecvData(unsigned char * lpRecvbuf, int nLen, CEnumCore::Message_Tag_ID msgTagID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnbaseimp();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTcnSelchangeTabbase(NMHDR *pNMHDR, LRESULT *pResult);

protected:

	// 激活tab标签要显示的ctrl的ID.
	typedef struct _TCB_ITEM_DATA_
	{
		DWORD dwCtrlID;
		_TCB_ITEM_DATA_* pNext;
		_TCB_ITEM_DATA_(){pNext = NULL;}
	} TCB_ITEM_DATA, *LPTCB_ITEM_DATA;

	typedef struct _TCB_ITEM_
	{
		CString strKey;			// tab标签文字在.ini文件中的key.
		LPTCB_ITEM_DATA lptid;	// 激活tab标签要显示的ctrl的ID链表.
	} TCB_ITEM, *LPTCB_ITEM;

	// TagName名称对应的key(.ini文件中).
	typedef struct _TAG_NAME_INI_KEY_
	{
		CEnumCore::TagName eTagName;
		CString strKey;
	} TAG_NAME_INI_KEY, *LPTAG_NAME_INI_KEY;

	typedef struct _CTRLID_INI_KEY_
	{
		DWORD dwCtrlID;
		LPCTSTR lpKey;
	} CTRLID_INI_KEY, *LPCTRLID_INI_KEY;


protected:

	// Create ctrl. editCtrl is below the edit-ctrl specified by dwAboveCtrlID. 
	void CreateCtrlEdit(CEdit& editCtrl, DWORD dwAboveCtrlID, DWORD dwEditID);
	void CreateCtrlStatic(CStatic& staticCtrl, DWORD dwAboveStaticCtrlID, DWORD dwStaticID);
	void CreateCtrlList(CListCtrl& listCtrl, DWORD dwListID);
	void MoveImpButton(DWORD dwAboveCtrlID, DWORD dwButtonID);///移动button

	//创建DataTimePicker控件
	void CreateCtrlDateTime(CDateTimeCtrl& datatimeCtrl, DWORD dwAboveCtrlID, DWORD dwDateTimeID);
	//创建button//maple add
	void CreateCtrlButton(CButton& buttonCtrl, DWORD dwAboveCtrlID, DWORD dwButtonID);

	void QueryCharInfo(CString& curPage);////查询玩家的角色信息
	void QueryOtherInfo(CEnumCore::ServiceKey eServiceKey, CString& curPage, CListCtrl &listCtrl);///查询玩家的其它信息

	// dwAboveCtrlID 取默认值, cmbCtrl参考m_cmbPage创建，其大小/风格/位置相同，否则,
	// cmbCtrl参考dwAboveCtrlID指定的控件大小创建.
	void CreateCtrlComCmb(CComboBox& cmbCtrl, DWORD dwCmbID, DWORD dwAboveCtrlID = 0);


	virtual void QueryOperation(int nTabCurSel)=0;
	virtual void ImplementUpdateOperation(int nTabCurSel)=0;
	virtual void ProcessRecvData(CSocketData& socketData, CEnumCore::Message_Tag_ID msgTagID)=0;
	virtual void OnSelectTabCtrlItem(int nLastTimeSel, int nCurSel)=0;
	virtual BOOL ClearDataForCtrl()=0;

	void SetTabCtrlItemCurSel(int nCurSel);
	int GetTabCtrlItemCurSel();
	void ResetCmbCtrl(CComboBox& cmbCtrl);
	void InitTableCtrl(TCB_ITEM tidArray[], DWORD dwCount, CString& strSection);
	void ClearTabCtrlData();

	// cmbCtrl 在该组合框中显示页索引.
	// listCtrl 显示查询到的信息.
	// strSection 列表框标题所在的节(.ini中).
	void SetDataForListCtrl(CListCtrl &listCtrl, CSocketData& socketdata, CComboBox& cmbCtrl);

	// nRowIndex 默认值取当前选择的行.
	CString GetDataFromListCtrl(CListCtrl &listCtrl, CEnumCore::TagName tagName, int nRowIndex = -1);

	void InitGameServerComboBox(CSocketData& socketdata);

	// 指定列表框彈出菜單.
	void PopupMenuForListCtrlRClick(CListCtrl& listCtrl, CMenu& menu, POINT& point);

	// Get data from ctrl.
	CString GetGameServerIP();
	CString GetAccount();
	CString GetNick();
	CString GetCmbCurSelText(CComboBox& cmbPage);

	CString GetGameServerName();

protected:
	CComboBox m_cmbGameServer;

////	OperationCG2 OperCG2;

	CString m_strPageSize;

private:

	// 子类应该创建自己的列表控件，
	// 此时可以参考该控件的风格/位置等
	CListCtrl m_listBaseCtrl;
	enum {LIST_CTRL_COL_WIDTH = 80};

	// 该控件不直接使用，
	// 而是作为创建其他同类(显示页索引)控件的参考.
	CComboBox m_cmbPage;
	CTabCtrl m_tcbBase;
	int m_nCurrentSelIndex;
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	CDateTimeCtrl dtcLoginDate;
	CDateTimeCtrl dtcLogoutDate;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CComboBox cmbTradeType;
};
