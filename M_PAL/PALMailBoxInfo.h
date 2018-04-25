#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CPALMailBoxInfo �Ի���

class CPALMailBoxInfo : public CDialog
{
	DECLARE_DYNAMIC(CPALMailBoxInfo)

public:
	CPALMailBoxInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALMailBoxInfo();

// �Ի�������
	enum { IDD = IDD_DLGMAILBOXINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	//���������б�
	int nMailItem;

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

	//��ȡ�����ID
	int UserID;

	//��ȡMAILID
	int MailID;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;
	
public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CDateTimeCtrl��ʼʱ��
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl����ʱ��
	CDateTimeCtrl dtcEndTime;

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

	//CListCtrl��ʾ���������5����
	CListCtrl listMailDetail;

	//��ʼʱ��
	CString strStartTime;

	//����ʱ��
	CString strEndTime;

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

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�������ʼ����в�ѯ
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);


	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ѯ���������Ϣ
	void MailBoxInfo();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();

public:
	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(void);

	// ��ʾ������Ϣ
	void ShowMailInfo(void);

	// ��ʾ�ʼ���������
	void ShowMailDetail(void);

	//��ѯ������丽����Ϣ
	void MailBoxDetail();

	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);
};
