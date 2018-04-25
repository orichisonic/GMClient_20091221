#pragma once


// CWAPetManage �Ի���

class CWAPetManage : public CDialog
{
	DECLARE_DYNAMIC(CWAPetManage)

public:
	CWAPetManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWAPetManage();

// �Ի�������
	enum { IDD = IDD_DLGPETMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:

	// ����������Ϣ�б�õ��к�
	int nItem;

	//���������Ϣ�б�õ��к�
	int mItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���г�����Ϣ�б�
	CMap<int,int,CString,CString> PetList;

	// �жϻ����б��Ƿ���Ҫ��ҳ
	bool pageBasic;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageResult;	

	// ��Ϸ������IP
	CString ServerIP;

	// ���ID
	CString UserID;

	// ����ʺ�
	CString UserName;

	// ����ǳ�
	CString UserNick;

	//��������
	CString PetName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

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

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	//��ʾ�����б�
	CComboBox cmbPet;

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

	// ��ѯ����������Ϣ
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

	//��ѯ���������Ϣ
	void ResultInfo();
	
	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbresult();

	//��������б����к�
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//ɾ��ѡ�еĳ�����Ϣ
	afx_msg void OnBnClickedBtndelpet();

	//˫������б�ִ����Ӧ�Ĳ���
	//afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ѯ���п�����ӵĳ����б�
	void PetInfo();

	//����µĳ�����Ϣ
	afx_msg void OnBnClickedBtnadd();

	//������ӳ�����Ϣ����
	afx_msg void OnBnClickedBtnreset();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// ���ҳ��
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();			

	//ȫѡ������
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//����������Ϣҳ��
	void ShowBasicInfo(int m_cmdShow);

	//���������Ϣҳ��
	void ShowResultInfo(int m_cmdShow);

	//����³���ҳ��
	void ShowNewPet(int m_cmdShow);	
};
