#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAUBanPlayer �Ի���

class CJW2BanPlayer : public CDialog
{
	DECLARE_DYNAMIC(CJW2BanPlayer)

public:
	CJW2BanPlayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJW2BanPlayer();

// �Ի�������
	enum { IDD = IDD_DLGBANPLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	//������ͣ�˺��б�õ��к�
	int mItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;
	bool pageUInfo;

	//��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ����ʺ�
	CString UserAccount;

	//���������ʺź��ǳ�
	CString UserName;

	//���������ǳ�
	CString UserNick;

	// ���ID
	int UserID;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	//CComboBox��ҳ��ѯ��ͣ�ʺ��б���Ϣ
	CComboBox cmbLPage;

	//CListCtrl�û���Ϣ
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// CEdit����ʺ�
	CEdit txtAccount;

	// CEdit�����ͣԭ��
	CEdit txtReason;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;
public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	//�����ݼ���Ӧ����
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ��ѯ������Ϣ
	afx_msg void OnBnClickedUisearch();

	// ��ѯ���������Ϣ
	void UserInfo();

	// ��ѯ���б���ͣ�ʺ��б���Ϣ
	void AllBanUserList();

	// ��ҳ���в�ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbuipage();

	// ��ҳ���в�ѯ��ͣ�ʺ��б���Ϣ
	afx_msg void OnCbnSelchangeCmbpage();

	// ����������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫��������Ϣ���в���
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ������ͣ�˺��б���Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫����ͣ�˺��б���Ϣ���н��
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);
	
	// ��ͣ�����ʺ�
	afx_msg void OnBnClickedBtnban();

	// ������Ϣ
	afx_msg void OnBnClickedBtnreset();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���	
	afx_msg void OnBnClickedUicancel();	

	// �رնԻ���
	afx_msg void OnClose();		
};
