#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALItemManage �Ի���

class CPALItemManage : public CDialog
{
	DECLARE_DYNAMIC(CPALItemManage)

public:
	CPALItemManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALItemManage();

// �Ի�������
	enum { IDD = IDD_DLGITEMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б��õ��к�
	int nItem;

	// ���������б��õ��к�
	int nSelectItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���д�����Ϣ
	CMap<int,int,int,int> BigTypeList;

	// ����С����Ϣ
	CMap<int,int,int,int> GiftList;

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
	CStatic GrpPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CComboBox�������
	CComboBox cmbType;

	// CComboBox��������
	CComboBox cmbName;

	// CListCtrl�����͵ĵ����б�
	CListCtrl listItem;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	//������ݼ���Ӧ����
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	// �����û��б����浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ѯ��ұ�����Ϣ
	void BagInfo(int iBagType);

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ˫��������Ϣ����ɾ��
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ѯ���������Ϣ
    void ItemTypeInfo(void);

	// ���ݵ�������ѯ��Ӧ�ĵ�������
	afx_msg void OnCbnSelchangeCmbbigtype();

	//������б������ӵ���
	afx_msg void OnBnClickedBtnadd();

	//���������б������к�
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//˫�������б�����ɾ��
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//�ӵ����б��н���ɾ��
	afx_msg void OnBnClickedBtndelete();

	// ͨ���ʼ����ӵ���
	afx_msg void OnBnClickedBtnsend();

	// ������Ϣ
	afx_msg void OnBnClickedBtnreset();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();

public:

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(void);

	// ��ʾ������Ϣ
	void ShowBagType(void);	

	// ��ʾ������Ϣ
	void ShowOtherInfo(void);	

	// ��ʾ���͵���ҳ��
	void ShowMailItem(int m_cmdShow);
	
	//�����ʼ���Ϣ
	void ResetMailInfo(void);
};