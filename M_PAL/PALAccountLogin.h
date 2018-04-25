#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// CPALAccountLogin �Ի���

class CPALAccountLogin : public CDialog
{
	DECLARE_DYNAMIC(CPALAccountLogin)

public:
	CPALAccountLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALAccountLogin();

// �Ի�������
	enum { IDD = IDD_DLGLOGINLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:

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

	// ��������IP
	CString UserIP;

	//�����ؼ��ĸ߶�
	int grpHeight, grpPHeight;

	//��ʼʱ��
	CString strStartTime;

	//����ʱ��
	CString strEndTime;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CButtonͨ���ʺŲ�ѯ
	CButton checkByAccount;

	// CButtonͨ��IP��ѯ
	CButton checkByIP;

	// CDateTimeCtrl��ʼʱ��
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl����ʱ��
	CDateTimeCtrl dtcEndTime;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CIPAddressCtrl���IP
	CIPAddressCtrl IPACtrl_UserIP;

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

	// ����ͨ���ʺ�����ѯ
	afx_msg void OnBnClickedCheckbyaccount();

	// ����ͨ��IP����ѯ
	afx_msg void OnBnClickedCheckbyip();

	// ��ѯ��ҵ�¼��־��Ϣ
	afx_msg void OnBnClickedSearch();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();

public:

	//��ʾͨ���ʺŲ�ѯ����Ϣ
	void ShowCheckByAccount(void);

	//��ʾͨ��IP��ѯ����Ϣ
	void ShowCheckByIP(void);	
	CComboBox cmbType;
};
