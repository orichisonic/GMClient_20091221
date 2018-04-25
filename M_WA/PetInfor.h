#pragma once


// PetInfor �Ի���

class PetInfor : public CDialog
{
	DECLARE_DYNAMIC(PetInfor)

public:
	PetInfor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PetInfor();
	// �Ի�������
	enum { IDD = IDD_DLGPETINFOR};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;
    int nItemresult;
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
	// ѡ��Ĳ�������
	CString SearchType;
	// �������ҽ�ɫ��
	CString UserName;
	//�������
    CString WA_medalPetIndex;
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

	// CComboBox��������
	CComboBox cmbQuestType;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	//�����ݼ���Ӧ����
	//virtual BOOL PreTranslateMessage(MSG* pMsg);

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
	// ���������б��浱ǰ�к�
	//afx_msg void OnNMClickListhuizhanginfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫������������Ϣ���в�ѯ
	//afx_msg void OnNMDblclkListhuizhanginfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ѯ��һ�����Ϣ
	void EmblemList();

	//��ʾ������Ϣ�б�
	void ShowFriendInfo();

	//��ѯ���������Ϣ
	void QuestInfo();
	
	void  PetList();
	//�л�����״̬��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbquesttype();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();

public:
	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ʼ����ѯ�б�ѡ��
	void InitQuestType(void);

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(void);

	// ��ʾ������Ϣ
	//void ShowOtherInfo(void);	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
