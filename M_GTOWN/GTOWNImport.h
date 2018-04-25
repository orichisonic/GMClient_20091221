#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#import "c:\program files\common files\system\ado\msado15.dll"\
	no_namespace \
	rename ("EOF", "adoEOF")
// CGTOWNImport �Ի���

class CGTOWNImport : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNImport)

public:
	CGTOWNImport(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNImport();

// �Ի�������
	enum { IDD = IDD_DLGIMPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;


	//��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;



	//�����ؼ��ĸ߶�
	int grpHeight, grpPHeight;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

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

	//������ݼ���Ӧ����
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);






	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���	
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();
	
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedComfirm();
	bool ReadXls(CString m_filePath,CString* m_allUserName,CString* m_allItemID,CString * m_Num);
	CTabCtrl tbcResult;
};