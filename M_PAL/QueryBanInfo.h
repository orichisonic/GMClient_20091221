#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CQueryBanInfo �Ի���

class CQueryBanInfo : public CDialog
{
	DECLARE_DYNAMIC(CQueryBanInfo)

public:
	CQueryBanInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQueryBanInfo();

// �Ի�������
	enum { IDD = IDD_DLGQUERYBAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ���������ʺ�
	CString UserAccount;

	//�����ؼ��ĸ߶�
	int grpHeight;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CEdit����ʺ�
	CEdit txtAccount;

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

	// ��ѯ������Ϣ
	afx_msg void OnBnClickedSearch();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û���ͣ��Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���	
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();
};
