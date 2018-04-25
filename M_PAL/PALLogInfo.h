#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CPALLogInfo �Ի���

class CPALLogInfo : public CDialog
{
	DECLARE_DYNAMIC(CPALLogInfo)

public:
	CPALLogInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPALLogInfo();

// �Ի�������
	enum { IDD = IDD_DLGLOGINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���д�����Ϣ
	CMap<int,int,int,int> BigTypeID;

	// ��Ӧ��С����Ϣ
	CMap<int,int,int,int> SmallTypeID;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ����ʺ�
	CString UserAccount;

	// ��ҽ�ɫ��
	CString UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

	//��־����
	CString BigType;

	//��־����ID
	int bTypeID;

	//��־С��
	CString SmallType;

	//��־С��ID
	int sTypeID;

	//��ʼʱ��
	CString strStartTime;

	//����ʱ��
	CString strEndTime;
public:
	// CComboBox��Ϸ�������б�
	CComboBox cmbServer;

	// CTabCtrl��ѯ���ѡ��
	CTabCtrl tbcResult;

	// CComboBox��־����
	CComboBox cmbBigType;

	// CComboBox��־С��
	CComboBox cmbSmallType;

	// CDateTimeCtrl��־��ʼʱ��	
	CDateTimeCtrl dtcStartDate;	

	// CDateTimeCtrl��־����ʱ��
	CDateTimeCtrl dtcEndDate;

	// CComboBox��־��ҳ
	CComboBox cmbPage;

	// CListCtrl��־��Ϣ�б�
	CListCtrl listResult;

	// CListCtrl�û�������Ϣ�б�
	CListCtrl listUser;

	// GroupBox��������
	CStatic GrpSearch;

	// GroupBox��ҳ��Ϣ
	CStatic GrpPage;

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

	// �������������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ�����л�
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//��ȡ���д�����Ϣ
	void GetAllBigType();

	// ѡ������ѯС��
	afx_msg void OnCbnSelchangeCmbbigtype();

	// ��ѯ��־��Ϣ
	afx_msg void OnBnClickedBtnsearchlog();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	//�����û���Ϣ��������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//������־�б���Ϣ��������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//��ʾ�û���Ϣ����
	void ShowUserInfo();

	//��ʾ��־��Ϣ����
	void ShowLogInfo();	
	
	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();
};
