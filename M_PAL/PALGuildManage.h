#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPALGuildManage �Ի���

class CPALGuildManage : public CDialog
{
	DECLARE_DYNAMIC(CPALGuildManage)

public:
	CPALGuildManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALGuildManage();

// �Ի�������
	enum { IDD = IDD_DLGGUILDMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ���������б�õ��к�
	int nGuildItem;

	// ���������û��б�õ��к�
	int nGuildMemberItem;

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

	//��ҽ�ɫ��
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

	//CComboBox��Աְ��
	CComboBox cmbMemberLvl;

	// CListCtrl�����б�
	CListCtrl listGuild;

	// CListCtrl�����Ա�б�
	CListCtrl listMember;

	// CEdit����ԭ�ȼ�
	CEdit txtGuildLvl;

	//CComboBox�ȼ�
	CComboBox cmbLvl;

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

	// ��ѯ�����Ա��Ϣ
	void GuildMemberList();

	// ��������������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListguild(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫������������Ϣ���в���
	afx_msg void OnNMDblclkListguild(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в���
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ���������Ա��Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListmember(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�������Ա��Ϣ���в���
	afx_msg void OnNMDblclkListmember(NMHDR *pNMHDR, LRESULT *pResult);

	// �����޸�
	afx_msg void OnBnClickedBtnmodi();

	//�޸Ĺ����Ա�ȼ���Ϣ
	afx_msg void OnBnClickedBtnmodimemberlvl();

	// ������Ϣ
	afx_msg void OnBnClickedBtnreset();

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
	// ��ʼ�������Ա�ȼ�
	void InitMemberLevel(void);

	// ��ʼ�����е��¹���ȼ�
	void InitNewGuildLevl(void);

	// ��ʾ������Ϣ
	void ShowGuildInfo();

	// ��ʾ�޸���Ϣ����
	void ShowModiTab(int m_cmdShow);

	// ��ʾ�޸Ĺ����Ա��Ϣ
	void ShowGuildMember(int m_cmdShow);
};
