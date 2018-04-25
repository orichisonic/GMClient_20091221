#pragma once
//#include "OperationCG2.h"
//#include "afxcmn.h"
//#include "afxwin.h"
//
//#import "c:\program files\common files\system\ado\msado15.dll"\
//	no_namespace \
//	rename ("EOF", "adoEOF")

// ChangeMoney �Ի���

class ChangeMoney : public CDialog
{
	DECLARE_DYNAMIC(ChangeMoney)

public:
	ChangeMoney(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChangeMoney();

	// �Ի�������
	enum { IDD = IDD_DLGBANKMANAGE };

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

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	int nListItem;

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

	// ��ѯ��ɫ��ϸ����
	void BankInfo();

	// ��ѯ��ɫ��������
	void BankItem();

	// ��ѯ��ɫ��������
	void BankPet();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();			

	//��������ѯ
	void ItemType();


	void ShowAddBankItem(int n_cmdShow);
	afx_msg void OnEnChangeEdit3();
	CButton ckItemType;
	afx_msg void OnBnClickedCkitemtype();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();

	//������е���
	void AddBankItem();

	//�޸����н�Ǯ
	void ModifyBankMoney();

	//����������е���
	void MultiAddBankItem();

	//��ѯ����
	void SearchItem();

	afx_msg void OnBnClickedBtright();
	afx_msg void OnBnClickedBtleft();
	CListCtrl listItem;
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox cmbItemName;
	CComboBox cmbItemType;
	afx_msg void OnCbnSelchangeCmb1();
	void GetListItem(CString m_ItemName, CString m_ItemNum);
	void ShowBankMoney(int m_cmdShow);
	void ShowMultiAdd(int m_cmdShow);
	bool ReadXls(CString strFilePath,CString* strUserName, CString* strUserID, CString* strItemName, CString* strItemNum);
	afx_msg void OnBnClickedBtn3();
	virtual	BOOL PreTranslateMessage(MSG* pMsg);
};
