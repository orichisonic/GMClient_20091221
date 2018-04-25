#pragma once


// CXDGMManage �Ի���

class CXDGMManage : public CDialog
{
	DECLARE_DYNAMIC(CXDGMManage)

public:
	CXDGMManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXDGMManage();

// �Ի�������
	enum { IDD = IDD_DLGGMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���м�����Ϣ�б�
	CMap<int,int,int,int> BuffList;

	// �жϻ���������Ϣ�б��Ƿ���Ҫ��ҳ
	bool pageBasic;

	// ��Ϸ������IP
	CString ServerIP;

	// ���ID
	CString UserID;

	// ���������ʺ�
	CString UserName;

	// ���������ǳ�
	CString UserNick;

	//��ӻ��Ƴ���BUFFID
	int BuffID;

	//��ӻ��Ƴ���BUFF����
	CString BuffName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CComboBox����������Ϣ��ҳ��ѯ
	CComboBox cmbBasic;

	// CListCtrl����������Ϣ
	CListCtrl listBasic;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	//��ʾ�б���Ϣ
	CComboBox cmbList;

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

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	// ��ѯ���������Ϣ
	void UserInfo();

	// ��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbbasic();

	// �������������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в���
	afx_msg void OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в���
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);	

	//��ѯ����BUFF��Ϣ
	void SearchBuff();

	//�ƶ���ɫλ��
	afx_msg void OnBnClickedBtnedit();

	//������Ϣ
	afx_msg void OnBnClickedBtnrecover();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();	

	//�û�����������Ϣҳ��
	void ShowUserInfo(int m_cmdShow);

	//������ָ������ҳ��
	void ShowCoordinate(int m_cmdShow);

	//��Һ�GM���ഫ�����Է�λ��
	void ShowTransferGM(int m_cmdShow);

	//���/�Ƴ�BUFFҳ��
	void ShowEditBuff(int m_cmdShow);

	//��Ctrl+A/C������Ӧ
	virtual	BOOL PreTranslateMessage(MSG* pMsg);
};
