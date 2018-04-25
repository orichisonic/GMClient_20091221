#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCG2LoginInfo �Ի���

class CCG2LoginInfo : public CDialog
{
	DECLARE_DYNAMIC(CCG2LoginInfo)

public:
	CCG2LoginInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2LoginInfo();

// �Ի�������
	enum { IDD = IDD_DLGLOGININFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������IP
	CString ServerIP;

	// ����ʺ�
	CString UserAccount;

	// ���ID
	int UserID;

	// ���������ʺ�
	CString UserName;

	// ���������ǳ�
	CString UserNick;

	//�����ؼ��ĸ߶�
	int grpHeight, grpPHeight;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;


	// CDateTimeCtrl����
	CDateTimeCtrl dtcLoginDate;
	CDateTimeCtrl dtcLogoutDate;

	// CDateTimeCtrlʱ��
	CDateTimeCtrl dtcLoginTime;
	CDateTimeCtrl dtcLogoutTime;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedUisearch();

	// ��ѯ��ҵ�½��Ϣ
	void LoginInfo();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbkppage();

	// ˫�����������Ϣ��������
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���	
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();
};
