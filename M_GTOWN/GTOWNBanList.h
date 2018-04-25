#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNBanList �Ի���

class CGTOWNBanList : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNBanList)

public:
	CGTOWNBanList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNBanList();

// �Ի�������
	enum { IDD = IDD_DLGBANLIST };

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
	bool pageUInfo;
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//���������ʺźͽ�ɫ��
	CString Account, Name;

	// ��õ�����ʺźͽ�ɫ��
	CString UserAccount, UserName;

	//���ID
	int UserID;

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

	//�����Ϣ��ҳ��ѡ��
	CComboBox cmbUPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	//��ͣ����ʺ�
	CEdit txtAccount;

	//��ͣԭ��
	CEdit txtReason;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//��ͣ�����״̬
	int UserState;

	//���ID
	int userID;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//�����ݼ���Ӧ
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	

	//��ѯ���������Ϣ
	afx_msg void OnBnClickedOk();
	void UserInfo();

	//��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbupage();


	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫���û��б��л�����
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);



	// ��ѯ���б���ͣ�ʺ��б���Ϣ
	void AllBanUserList();

	// ��ҳ��ѯ����ͣ�ʺ��б���Ϣ
	afx_msg void OnCbnSelchangeCmbpage();


	// ������ͣ�ʺ��б��浱ǰ�к�
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫����ͣ�ʺ��б��л�����
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);


	//�л�tabCtrlѡ�
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);


	//��ͣ�����ʺ�
	afx_msg void OnBnClickedBtnban();


	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);


	//������Ϣ
	afx_msg void OnBnClickedBtnreset();


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

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
};
