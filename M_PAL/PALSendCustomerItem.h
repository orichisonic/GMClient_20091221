#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALSendCustomerItem �Ի���

class CPALSendCustomerItem : public CDialog
{
	DECLARE_DYNAMIC(CPALSendCustomerItem)

public:
	CPALSendCustomerItem(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALSendCustomerItem();

// �Ի�������
	enum { IDD = IDD_DLGSENDCUSTOMERITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���������б�õ��к�
	//int nSelectItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���д�����Ϣ
	CMap<int,int,int,int> BigTypeList;

	// ����С����Ϣ
	CMap<int,int,int,int> ItemNameList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ���������ʺ�
	CString UserAccount;

	// �������ҽ�ɫ��
	CString UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CGroupBox��ҳ����
	//CStatic GrpPage;

	// CComboBox��ҳ��ѯ
	//CComboBox cmbPage;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//��������
	CComboBox cmbItemName;

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();

public:

		// ��ʾ��ɫ������Ϣ
		void ShowUserInfo(void);

		// ��ʾ������Ϣ
		void ShowOtherInfo(void);

		//�������Ʋ�ѯ
		void ItemNameQuery();

		//��Ϊ��
		CButton checkBind;

		//ά��ԭ�����趨
		CButton checkNotBind;

		//�Ƿ�ʹ����ʯ�趨
		CButton checkStone;
		afx_msg void OnBnClickedCheckbind();
		afx_msg void OnBnClickedChecknotbind();
		afx_msg void OnBnClickedCheckstone();
		afx_msg void OnBnClickedBtnsend();
		afx_msg void OnBnClickedBtqueiryitem();
};
