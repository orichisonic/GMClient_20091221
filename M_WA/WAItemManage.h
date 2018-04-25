#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CWAItemManage �Ի���


class CWAItemManage : public CDialog
{
	DECLARE_DYNAMIC(CWAItemManage)

public:
	CWAItemManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWAItemManage();

// �Ի�������
	enum { IDD = IDD_DLGITEMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���е�����Ϣ�б�
	CMap<int,int,CString,CString> ItemList;

	// �����û���Ϣ�б�
	CMap<int,int,CString,CString> UserList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// �ж��û��б��Ƿ���Ҫ��ҳ
	bool pageUInfo;

	// ��Ϸ������IP
	CString ServerIP;

	// ���ID
	CString UserID;

	// ���������ʺ�
	CString UserName;

	// ���������ǳ�
	CString UserNick;

	//����ID
	CString ItemID;

	//��������
	CString ItemName;

	//��ӵ��ߵ����ս��
	char ItemResult[2048];

	//��ӵ��ߵ���ʱ���
	char tmpItemResult[2048];	

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CComboBox��ҽ�ɫ��Ϣ��ҳ��ѯ
	CComboBox cmbUPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	//��ʾ�����б�
	CComboBox cmbType;

	//��ʾ�����б�
	CComboBox cmbList;

	//�����б�
	CListCtrl listItem;

	//ѡ���Ƿ���Ҫ�������
	CButton checkSelect;

	//ѡ���Ƿ���ҪȺ������
	CButton checkGroup;

	//ģ��������&�½�Ǯ��
	CEdit CEditNew;

	//����Ʒ��
	CComboBox cmbQuality;

	//CProgressCtrl���͵��߽�����
	CProgressCtrl progMail;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//ѡ���Ƿ����ڵ�һ����ӵ���
	int nFirst;

	//ѡ����Ӧ����ҵ����к�
	int nListItem;

	//ѡ����Ӧ����ӵ����к�
	int nSelectItem;

	//ȷ���Ƿ�������ӵ���
	int multStatus;

	//�����͵��ߵĽ�ɫ������
	int UserNum;

	//��ǰ���ڷ��͵Ľ�ɫ���
	int mCurNum;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//��ȡѡ���ServerIP
	afx_msg void OnCbnSelchangeCmbuiserver();

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedUisearch();

	// ��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbuserpage();

	// �������������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ѯ���������Ϣ
	void UserInfo();

	// ��ѯ��ɫ������Ϣ
	void ItemInfo();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	//ѡ����Ӧ�ļ�����Ϣ�����޸�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//ɾ��ѡ�еĵ���
	afx_msg void OnBnClickedBtndelitem();

	//ѡ���Ƿ�������ӵ���
	afx_msg void OnBnClickedCheckselect();

	//ѡ���Ƿ���ҪȺ������
	afx_msg void OnBnClickedCheckgroup();

	//ѡ��������ӵ��ߵĽ�ɫ�ļ���
	afx_msg void OnBnClickedBtnbrowse();

	//��ѯ����������Ϣ
	void SearchItemType();

	//��ѯ��Ӧ���͵ĵ�����Ϣ
	afx_msg void OnBnClickedBtnitemlist();

	//������б�����ӵ���
	afx_msg void OnBnClickedBtnadd();

	//���������б����к�
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//˫�������б����ɾ��
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//�ӵ����б��н���ɾ��
	afx_msg void OnBnClickedBtndelete();

	//�޸Ļ������Ϣ
	afx_msg void OnBnClickedBtnedit();

	//����µ���
	void AddItem();

	//�޸Ľ�Ǯ����
	void EditMoney();

	//������Ϣ
	afx_msg void OnBnClickedBtnrecover();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//��������������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();	

	//�û�����������Ϣҳ��
	void ShowUserInfo(int m_cmdShow);

	//�û�������Ϣҳ��
	void ShowItemInfo(int m_cmdShow);

	//����µ���ҳ��
	void ShowNewItem(int m_cmdShow);

	//���µ���ҳ�����ز�����ֵ
	void NewItemValue();

	//�޸��û���Ǯҳ��
	void ShowMoneyInfo(int m_cmdShow);

	//��Ctrl+A/C������Ӧ
	virtual	BOOL PreTranslateMessage(MSG* pMsg);
};
