#pragma once


// CWACharLog �Ի���

class CWACharLog : public CDialog
{
	DECLARE_DYNAMIC(CWACharLog)

public:
	CWACharLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWACharLog();

// �Ի�������
	enum { IDD = IDD_DLGCHARLOG };

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

	//��־��ʼʱ��
	CString BeginTime;

	//��־����ʱ��
	CString EndTime;

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

	//CComboBox��־����
	CComboBox cmbLogType;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	//CDateTimeCtrl��ʼʱ��
	CDateTimeCtrl dtcStartTime;

	//CDateTimeCtrl����ʱ��
	CDateTimeCtrl dtcEndTime;

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

	//��ѯ�û���ɫ��־
	afx_msg void OnBnClickedBtnlog();

	//��ɫ��ɫ��־
	void CharLog(CString logType);

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();			

	//ȫѡ������
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
