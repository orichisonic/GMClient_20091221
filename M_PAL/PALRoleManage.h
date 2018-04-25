#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALRoleManage �Ի���

class CPALRoleManage : public CDialog
{
	DECLARE_DYNAMIC(CPALRoleManage)

public:
	CPALRoleManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALRoleManage();

// �Ի�������
	enum { IDD = IDD_DLGROLEMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���������б�õ��к�
	int nQuestItem;

	//���в�ѯ���������
	int iQuestType;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

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

	// ѡ��������
	int QuestNum;

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

	// CComboBox�û���Ϣ��ҳ��ѯ
	CComboBox cmbUPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CComboBox��������
	CComboBox cmbStatus;

	// CComboBox����������
	CComboBox cmbNewStatus;

	// CComboBox����
	CComboBox cmbType;

	// CEditԭ����Ϣ
	CEdit txtSrc;

	// CEdit�޸���Ϣ
	CEdit txtNew;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:

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

	// ˫�����������Ϣ���в���
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в���
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);
	
	//��ѯ���������Ϣ
	void QuestInfo();

	//�л��������Ͳ�ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbqueststatus();

	//��ҳ��ѯ������Ϣ
	afx_msg void OnCbnSelchangeCmbpage();

	//˫�������б�����޸�
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//�޸���������
	afx_msg void OnBnClickedBtnmodiquest();

	//�л���ͬ����
	afx_msg void OnCbnSelchangeCmbtype();

	//�޸Ľ�Ǯ��������Ϣ
	afx_msg void OnBnClickedBtnmodi();

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

	// ��ʼ���������͸�ѡ��
	void InitPwdType(void);

	// ��ʼ����Ǯ���͸�ѡ��
	void InitMoneyType(void);

	// ��ʼ���������͸�ѡ��
	void InitQuestType(void);

	// ��ʼ��Ҫ�޸ĵ��������͸�ѡ��
	void InitQuestStatus(void);

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(void);

	// ��ʾ����ҳ��
	void ShowOperTab(int m_cmdShow);

	//��ʾ�����������
	void ShowQuestTab(int m_cmdShow,int selectShow);		
};
