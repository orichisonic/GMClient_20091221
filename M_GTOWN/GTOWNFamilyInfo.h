#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNFamilyInfo �Ի���

class CGTOWNFamilyInfo : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNFamilyInfo)

public:
	CGTOWNFamilyInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNFamilyInfo();

// �Ի�������
	enum { IDD = IDD_DLGFAMILYINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageFInfo;
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ����ļ�������
	CString Name;

	// ��ȡ�ļ�������
	CString FamilyName;

	//��ȡ�ļ���ID
	int FamilyID;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	//��ҳ����
	CStatic GrpPage;

	//���巭ҳ��ѡ��
	CComboBox cmbFPage;

	//��ҳ��Ͽ�
	CComboBox cmbPage;

	//��ʾ�����Ϣ�б��
	CListCtrl listFamily;

	//��ʾ�����Ϣ
	CListCtrl listMember;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	//��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	//��ѯ������Ϣ
	afx_msg void OnBnClickedSearch();

	// ��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbfpage();	


	// ���������б��浱ǰ�к�
	afx_msg void OnNMClickListfamily(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫������������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListfamily(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//�����Ա��ϸ��Ϣ
	void MemberInfo();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();


	//���ܷ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//��ʾ������Ϣ
	void ShowFamilyInfo();

	//��ʾ������Ϣ
	void ShowOtherInfo();



	//��������������Ϣ��������������
	afx_msg void OnLvnColumnclickListfamily(NMHDR *pNMHDR, LRESULT *pResult);

	//������Ա��Ϣ��������������
	afx_msg void OnLvnColumnclickListmember(NMHDR *pNMHDR, LRESULT *pResult);

	//ʹ�ùرհ�ť
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();		
	
};
