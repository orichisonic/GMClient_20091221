#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALPuzzleMapManage �Ի���

class CPALPuzzleMapManage : public CDialog
{
	DECLARE_DYNAMIC(CPALPuzzleMapManage)

public:
	CPALPuzzleMapManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALPuzzleMapManage();

// �Ի�������
	enum { IDD = IDD_DLGPUZZLEMAPMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���������б�õ��к�
	int nListItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���д�����Ϣ
	CMap<int,int,int,int> BigTypeList;

	// ����С����Ϣ
	CMap<int,int,int,int> GiftList;

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

	CString strPuzzleMap;

	int iPuzzleMapID[9];
	
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

	// CComboBox�������
	CComboBox cmbType;

	// CComboBox��������
	CComboBox cmbName;

	// CListCtrl�����͵ĵ����б�
	CListCtrl listItem;

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

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ѯ���ͼ��
	void PuzzleMap();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ˫��������Ϣ����ɾ��
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);




	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();

public:

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(void);

	// ��ʾ������Ϣ
	void ShowBagType(void);	

	void ShowModifyPuzzleMap(void);


	afx_msg void OnBnClickedBtn1();
	void InitComBox(void);
	CComboBox m_CB1;
	CComboBox m_CB2;
	CComboBox m_CB6;
	CComboBox m_CB9;
	CComboBox m_CB4;
	CComboBox m_CB3;
	CComboBox m_CB5;
	CComboBox m_CB7;
	CComboBox m_CB8;
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtn2();
};
