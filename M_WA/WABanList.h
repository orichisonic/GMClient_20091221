#pragma once


// CWABanList �Ի���

class CWABanList : public CDialog
{
	DECLARE_DYNAMIC(CWABanList)

public:
	CWABanList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWABanList();

// �Ի�������
	enum { IDD = IDD_DLGBANLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����ʺŷ�ͣ�б�õ��к�
	int mItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//Ҫ��ѯ������ʺ�
	CString UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl�����ʾ
	CListCtrl listResult;

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

	// ��ѯ��ͣ�ʺ��б�
	afx_msg void OnBnClickedSearch();

	// ��ѯ���б���ͣ�ʺ��б���Ϣ
	void AllBanUserList();

	// ��ѯ�ض�����ʺŵķ�ͣ��Ϣ
	void BanInfo();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnClose();	

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
