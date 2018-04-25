#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSDOFriendManager �Ի���

class CSDOFriendManager : public CDialog
{
	DECLARE_DYNAMIC(CSDOFriendManager)

public:
	CSDOFriendManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSDOFriendManager();

// �Ի�������
	enum { IDD = IDD_DLGFRIENDMANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	private:
	// �����û��б�õ��к�
	int nItem;
	int nSelect;//˫������б����к�

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//���������ʺźͽ�ɫ��
	CString Account, Name;

	// ��õ�����ʺźͽ�ɫ��
	CString UserAccount, UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

	//���ID
	int UserID;
public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	//��ҳ����
	CStatic GrpPage;

	//��ҳ��Ͽ�
	CComboBox cmbPage;

	//�����Ϣ��ҳ��Ͽ�
	CComboBox cmbUPage;

	//��ʾ�����Ϣ�б��
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// �رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(void);

	// ��ʾ������Ϣ
	void ShowOtherInfo(void);

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//�л���ҳ��Ͽ�
	afx_msg void OnCbnSelchangeCmbuipage();
	afx_msg void OnCbnSelchangeCmbpage();

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//��Һ�����Ϣ
	void FriendInfo();

	//˫������б�ɾ������
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//ɾ�������б�
	void DeleteFriend();
};
