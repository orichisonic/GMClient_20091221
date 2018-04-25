#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALSendPwd �Ի���

class CPALSendPwd : public CDialog
{
	DECLARE_DYNAMIC(CPALSendPwd)

public:
	CPALSendPwd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALSendPwd();

// �Ի�������
	enum { IDD = IDD_DLGSENDPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ���������ʺ�
	CString UserAccount;

	// �������ҽ�ɫ��
	CString UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	//����ʺŻ��ɫ��
	CEdit txtUserName;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

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

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ѯ���������Ϣ
	void MailBoxInfo();

	//��������
	afx_msg void OnBnClickedBtnsendmail();

	//������Ϣ
	afx_msg void OnBnClickedBtnreset();

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();

public:
	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(void);

	// ��ʾ������Ϣ
	void ShowOtherInfo(int m_ShowWnd);			

};
