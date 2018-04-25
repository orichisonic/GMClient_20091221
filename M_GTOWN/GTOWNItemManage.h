#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNItemManage �Ի���

class CGTOWNItemManage : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNItemManage)

public:
	CGTOWNItemManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNItemManage();

	// �Ի�������
	enum { IDD = IDD_DLGITEMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	//���������б�õ�Ҫ��ӵĵ��ߵ��к�
	int addItem;

	//�������͵����б�õ�Ҫɾ���ĵ����б�
	int delItem;

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
	int grpHeight, tbcHeight,grpPHeight, listWidth;

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

	//��ʾ�����Ϣ�б��
	CListCtrl listUser;

	// ��ѯ�õ��ĵ����б�
	CListCtrl listResult;

	//Ҫ��ӵĵ����б�
	CListCtrl listItem;

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

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	//��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	//��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbpage();


	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);


	//ģ����ѯ���Խ�����ӵĵ�����Ϣ
	afx_msg void OnBnClickedBtnblursearch();


	//����������ӵĵ����б������к�
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//˫��������ӵĵ����б��������
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ӵ�����Ϣ�����͵����б���
	afx_msg void OnBnClickedBtnadd();


	//�������͵����б������к�
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//˫�����͵����б�����ɾ��
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//�����͵����б���ɾ����Ӧ�ĵ���
	afx_msg void OnBnClickedBtndelete();



	//��ӵ���
	afx_msg void OnBnClickedBtnsend();

	//������ӵ����е���Ϣ
	afx_msg void OnBnClickedBtnreset();


	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);


	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//������ӵ����б��������
	afx_msg void OnLvnColumnclickListitem(NMHDR *pNMHDR, LRESULT *pResult);


	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(int nCmdShow);

	// ��ʾ������Ϣ
	void ShowItemInfo(int nCmdShow);

	//ʹ�ùرհ�ť
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();	
	CComboBox cmbBigType;
	CComboBox cmbSmallType;
};
