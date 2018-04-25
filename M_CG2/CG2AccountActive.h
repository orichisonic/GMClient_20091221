#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CCG2AccountActive �Ի���

class CCG2AccountActive : public CDialog
{
	DECLARE_DYNAMIC(CCG2AccountActive)

public:
	CCG2AccountActive(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2AccountActive();

// �Ի�������
	enum { IDD = IDD_DLGACCOUNTACTIVE };

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
	CString UserID;

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

	// ��ѯ���������Ϣ
	void UserInfo();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbkppage();


	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���	
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();

	afx_msg void OnBnClickedCk1();
	CButton ck_Type;


};
