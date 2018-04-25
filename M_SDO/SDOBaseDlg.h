#pragma once
#include "afxwin.h"


// CSDOBaseDlg �Ի���

class CSDOBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CSDOBaseDlg)

public:
	CSDOBaseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSDOBaseDlg();

// �Ի�������
	enum { IDD = IDD_BASEDIALOG };

	void SetRecvData(unsigned char * lpRecvbuf, int nLen, CEnumCore::Message_Tag_ID msgTagID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnbaseimp();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTcnSelchangeTabbase(NMHDR *pNMHDR, LRESULT *pResult);

protected:

	// ����tab��ǩҪ��ʾ��ctrl��ID.
	typedef struct _TCB_ITEM_DATA_
	{
		DWORD dwCtrlID;
		_TCB_ITEM_DATA_* pNext;
		_TCB_ITEM_DATA_(){pNext = NULL;}
	} TCB_ITEM_DATA, *LPTCB_ITEM_DATA;

	typedef struct _TCB_ITEM_
	{
		CString strKey;			// tab��ǩ������.ini�ļ��е�key.
		LPTCB_ITEM_DATA lptid;	// ����tab��ǩҪ��ʾ��ctrl��ID����.
	} TCB_ITEM, *LPTCB_ITEM;

	// TagName���ƶ�Ӧ��key(.ini�ļ���).
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
	void MoveImpButton(DWORD dwAboveCtrlID, DWORD dwButtonID);///�ƶ�button

	//����DataTimePicker�ؼ�
	void CreateCtrlDateTime(CDateTimeCtrl& datatimeCtrl, DWORD dwAboveCtrlID, DWORD dwDateTimeID);
	//����button//maple add
	void CreateCtrlButton(CButton& buttonCtrl, DWORD dwAboveCtrlID, DWORD dwButtonID);

	void QueryCharInfo(CString& curPage);////��ѯ��ҵĽ�ɫ��Ϣ
	void QueryOtherInfo(CEnumCore::ServiceKey eServiceKey, CString& curPage, CListCtrl &listCtrl);///��ѯ��ҵ�������Ϣ

	// dwAboveCtrlID ȡĬ��ֵ, cmbCtrl�ο�m_cmbPage���������С/���/λ����ͬ������,
	// cmbCtrl�ο�dwAboveCtrlIDָ���Ŀؼ���С����.
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

	// cmbCtrl �ڸ���Ͽ�����ʾҳ����.
	// listCtrl ��ʾ��ѯ������Ϣ.
	// strSection �б��������ڵĽ�(.ini��).
	void SetDataForListCtrl(CListCtrl &listCtrl, CSocketData& socketdata, CComboBox& cmbCtrl);

	// nRowIndex Ĭ��ֵȡ��ǰѡ�����.
	CString GetDataFromListCtrl(CListCtrl &listCtrl, CEnumCore::TagName tagName, int nRowIndex = -1);

	void InitGameServerComboBox(CSocketData& socketdata);

	// ָ���б�򏗳��ˆ�.
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

	// ����Ӧ�ô����Լ����б�ؼ���
	// ��ʱ���Բο��ÿؼ��ķ��/λ�õ�
	CListCtrl m_listBaseCtrl;
	enum {LIST_CTRL_COL_WIDTH = 80};

	// �ÿؼ���ֱ��ʹ�ã�
	// ������Ϊ��������ͬ��(��ʾҳ����)�ؼ��Ĳο�.
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
