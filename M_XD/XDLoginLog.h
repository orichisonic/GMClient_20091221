#pragma once


// CXDLoginLog �Ի���

class CXDLoginLog : public CDialog
{
	DECLARE_DYNAMIC(CXDLoginLog)

public:
	CXDLoginLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CXDLoginLog();

// �Ի�������
	enum { IDD = IDD_DLGLOGINLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:

	// ����������Ϣ�б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �жϻ����б��Ƿ���Ҫ��ҳ
	bool pageBasic;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageResult;	

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ����ʺ�
	CString UserName;

	// �������ҽ�ɫ��
	CString UserNick;

	// ��������IP
	CString UserIP;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

	//��ʼʱ��
	CString BeginTime;

	//����ʱ��
	CString EndTime;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CButtonͨ���ʺŲ�ѯ
	CButton checkByAccount;

	// CButtonͨ��IP��ѯ
	CButton checkByIP;

	// CDateTimeCtrl��ʼʱ��
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl����ʱ��
	CDateTimeCtrl dtcEndTime;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CComboBoxl������Ϣ��ҳ��ѯ
	CComboBox cmbBasic;

	// CComboBox��ҳ��ѯ
	CComboBox cmbResult;

	// CListCtrl����������Ϣ
	CListCtrl listBasic;

	// CListCtrl�����ʾ
	CListCtrl listResult;
    
	// CIPAddressCtrl���IP
	CIPAddressCtrl IPACtrl_UserIP;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;
    
	//��ѯ���ͣ�1��ͨ���˺Ų�ѯ��2��ͨ��IP��ѯ
	int checkType;

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

	// ����ͨ���ʺ�����ѯ
	afx_msg void OnBnClickedCheckbyaccount();

	// ����ͨ��IP����ѯ
	afx_msg void OnBnClickedCheckbyip();

	// ��ѯ��ҵ�¼��־��Ϣ
	afx_msg void OnBnClickedSearch();

	// ��ѯ����������Ϣ
	void BasicInfo();

	// ��ҳ��ѯ����������Ϣ
	afx_msg void OnCbnSelchangeCmbbasic();

	// ��������������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫������������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//ͨ��IP��ѯ��־��Ϣ
	afx_msg void OnBnClickedBtnlog();

	//��ѯ���������Ϣ
	void ResultInfo();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbresult();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();

public:

	//��ʾͨ����ɫ����ѯ����Ϣ
	void ShowCheckByName(void);

	//��ʾͨ��IP��ѯ����Ϣ
	void ShowCheckByIP(void);

	//����������Ϣҳ��
	void ShowBasicInfo(int m_cmdShow);

	//���������Ϣҳ��
	void ShowResultInfo(int m_cmdShow);

	//��������������Ϣ��������������
	afx_msg void OnLvnColumnclickListbasic(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);
};
