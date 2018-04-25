#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNItemInfo �Ի���

class CGTOWNItemInfo : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNItemInfo)

public:
	CGTOWNItemInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNItemInfo();

// �Ի�������
	enum { IDD = IDD_DLGITEMINFO };

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

	//�����ݼ���Ӧ
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedOk();

	//��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbupage();

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);


	//������Ʒ���ϲ�ѯ
	void BagInfo();

	//��ɫװ����Ϣ��ѯ
	void CharacterItem();

	//���ﱳ����Ϣ��ѯ
	void PetBag();

	//��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);


	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo();

	// ��ʾ������Ϣ
	void ShowOtherInfo();

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//ʹ�ùرհ�ť
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();
};
