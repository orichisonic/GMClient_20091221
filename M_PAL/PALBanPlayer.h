#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#import "c:\program files\common files\system\ado\msado15.dll"\
	no_namespace \
	rename ("EOF", "adoEOF")

// CPALBanPlayer �Ի���

class CPALBanPlayer : public CDialog
{
	DECLARE_DYNAMIC(CPALBanPlayer)

public:
	CPALBanPlayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALBanPlayer();

// �Ի�������
	enum { IDD = IDD_DLGBANPLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// �����ʺŷ�ͣ�б�õ��к�
	int mItem;

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

	// CEdit����ʺ�
	CEdit txtAccount;

	// CEdit�����ͣԭ��
	CEdit txtReason;

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
	afx_msg void OnBnClickedOk();

	// ��ѯ���������Ϣ
	void UserInfo();

	// ��ѯ���б���ͣ�ʺ��б���Ϣ
	void AllBanUserList();

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫���û��б��л�����
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в���
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ������ͣ�ʺ��б��浱ǰ�к�
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫����ͣ�ʺ��б��л�����
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ��ͣ�����ʺ�
	afx_msg void OnBnClickedBtnban();

	// ������Ϣ
	afx_msg void OnBnClickedBtnreset();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���	
	afx_msg void OnBnClickedCancel();

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnClose();

public:
	//��ʾ���������Ϣ
	void showUserInfo();

	//��ʾ��ͣ�ʺ�
	void showBanPlayer();

	//��ʾ��ͣ�ʺ��б�
	void showBanList();

	//��ʾ����ʺ�
	void showUnbindPlayer();

	//��ѯ�ʺ���û�з�ͣ
	void showSearchPlayer();

	
	//��ȡexcel�ļ�
	bool ReadXls(CString m_filePath,CString* m_allUserAccount,CString* m_allUserChar);

	afx_msg void OnBnClickedBtbrowse();
	afx_msg void OnBnClickedBtmulticlose();
};
