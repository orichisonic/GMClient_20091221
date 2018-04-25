#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGTOWNQueueInfo �Ի���

class CGTOWNQueueInfo : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNQueueInfo)

public:
	CGTOWNQueueInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNQueueInfo();

// �Ի�������
	enum { IDD = IDD_DLGQUEUEINFO };

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

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//���������ʺźͽ�ɫ��
	CString Account, Name;

	// ��õ�����ʺźͽ�ɫ��
	CString UserAccount, UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

	//���ID
	int UserID;
public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	//��ҳ����
	CStatic GrpPage;

	//��ҳ��Ͽ�
	CComboBox cmbPage;

	//��ʾ�����Ϣ�б��
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	int index;
	int iPageSize;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// �رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();



	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//�л���ҳ��Ͽ�
	afx_msg void OnCbnSelchangeCmbpage();

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//Ѫƴս��
	void McoinRank();

	//�ռ�����
	void SnsQuery();

	//��������
	void AttrQueue();

	//��Ƭ����
	void CardRecord();

	CComboBox m_cmbType;
	void InitType(void);
	afx_msg void OnCbnSelchangeCmbtype();
};
