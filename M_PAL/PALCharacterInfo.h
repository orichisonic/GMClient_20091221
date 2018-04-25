#pragma once


// CPALCharacterInfo �Ի���

class CPALCharacterInfo : public CDialog
{
	DECLARE_DYNAMIC(CPALCharacterInfo)

public:
	CPALCharacterInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALCharacterInfo();

// �Ի�������
	enum { IDD = IDD_DLGCHARACTERINFO };

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

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	//�رնԻ���
	afx_msg void OnClose();

	//���öԻ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//���öԻ����С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();
};
