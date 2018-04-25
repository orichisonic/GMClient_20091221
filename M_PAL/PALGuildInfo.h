#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALGuildInfo �Ի���

class CPALGuildInfo : public CDialog
{
	DECLARE_DYNAMIC(CPALGuildInfo)

public:
	CPALGuildInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALGuildInfo();

// �Ի�������
	enum { IDD = IDD_DLGGUILDINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ���������б�õ��к�
	int nGuildItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//����Ĺ�������
	CString GuildName;

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

	// CListCtrl�����б�
	CListCtrl listGuild;

	// CListCtrl�����Ա�б�
	CListCtrl listMember;

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

	// ��ѯ������Ϣ
	afx_msg void OnBnClickedSearch();

	// ��������������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListguild(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫������������Ϣ���в���
	afx_msg void OnNMDblclkListguild(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в���
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ѯ�����Ա��Ϣ
	void GuildMemberList();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//����������Ϣ��������������
	afx_msg void OnLvnColumnclickListguild(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ա��Ϣ��������������
	afx_msg void OnLvnColumnclickListmember(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���	
	afx_msg void OnBnClickedCancel();

	// �رնԻ���	
	afx_msg void OnClose();

public:
	
	// ��ʾ������Ϣ
	void ShowGuildInfo();

	// ��ʾ�޸Ĺ����Ա��Ϣ
	void ShowGuildMember(int m_cmdShow);
};
