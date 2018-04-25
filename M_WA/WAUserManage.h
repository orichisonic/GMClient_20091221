#pragma once
#include "afxwin.h"


// CWAUserManage �Ի���

class CWAUserManage : public CDialog
{
	DECLARE_DYNAMIC(CWAUserManage)

public:
	CWAUserManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWAUserManage();

// �Ի�������
	enum { IDD = IDD_DLGUSERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���м�����Ϣ�б�
	CMap<int,int,int,int> SkillList;

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

	//�޸Ļ���ӵļ���ID
	int SkillID;

	//�޸Ļ���ӵļ�������
	CString SkillName;

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

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	//��ʾ�����б�
	CComboBox cmbList;

	//����Password����
	CEdit CEditOld;

	//����Number����
	CEdit CEditNew;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	int nListItem;

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

	// ��ѯ��ɫ������Ϣ
	void SkillInfo();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	//ѡ����Ӧ�ļ�����Ϣ�����޸�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//�޸�ѡ�еĽ�ɫ������Ϣ
	afx_msg void OnBnClickedBtneditlvl();

	//ɾ��ѡ�еĽ�ɫ������Ϣ
	afx_msg void OnBnClickedBtndelskill();

	//��ѯ���м�����Ϣ
	void SearchSkill();

	//�޸Ļ������Ϣ
	afx_msg void OnBnClickedBtnedit();

	//ɾ����ָ���Ϣ
	afx_msg void OnBnClickedBtnrecover();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();	

	//ѡ��ͬ�����Խ����޸�
	afx_msg void OnCbnSelchangeCmbskill();

	//�û�����������Ϣҳ��
	void ShowUserInfo(int m_cmdShow);

	//�û�������Ϣҳ��
	void ShowSkillInfo(int m_cmdShow);

	//����¼���ҳ��
	void ShowNewSkill(int m_cmdShow);

	//�޸�/�ָ��û�����ҳ��
	void ShowPwdInfo(int m_cmdShow);

	//ɾ��/�ָ��û�ҳ��
	void ShowManageInfo(int m_cmdShow);

	//�޸��û���ɫ��/�ȼ�/��Ǯҳ��
	void ShowAccountInfo(int m_cmdShow);

	//��Ctrl+A/C������Ӧ
	virtual	BOOL PreTranslateMessage(MSG* pMsg);
};
