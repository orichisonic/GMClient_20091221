#pragma once


// MailInfor �Ի���

class MailInfor : public CDialog
{
	DECLARE_DYNAMIC(MailInfor)

public:
	MailInfor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MailInfor();
	// �Ի�������
	enum { IDD =IDD_DLGMAIL};
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
	// ѡ��Ĳ�������
	CString SearchType;
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

	//��ѯ��Һ����б�
	void FriendList();
	//��ʾ������Ϣ�б�
	void ShowFriendInfo();
	//��ѯ���������Ϣ
	void QuestInfo();

	//��ѯ���������Ϣ
	void PetBagInfo();

	//ȡ�ý�ɫ������Ѷ
	void AdvanceInfo();

	//ȡ�ý�ɫ������Ѷ
	void CharacterSkill();

	//ȡ�ý�ɫ��ħ��Ѷ
	void CharacterMob();

	//ȡ�ý�ɫͼ����Ѷ
	void PuzzleMap();

	//ȡ�ý�ɫ�������б�
	void BlackList();

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
	afx_msg void OnCbnSelchangeCmsearchtype();
};
