#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CGTOWNLogInfo �Ի���

class CGTOWNLogInfo : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNLogInfo)

public:
	CGTOWNLogInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNLogInfo();

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

	// �ж��Ƿ���Ҫ��ҳ
	bool pageUInfo;
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//���������ʺźͽ�ɫ��
	CString Account, Name;

	// ��õ�����ʺźͽ�ɫ��
	CString UserAccount, UserName;

	//��ҽ�ɫID
	int UserID;

	//��ʼʱ��
	CString strStartTime;

	//����ʱ��
	CString strEndTime;

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

	//�����Ϣ��ҳ��ѡ��
	CComboBox cmbUPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	//��ʼʱ��
	CDateTimeCtrl dtcStartDate;

	//����ʱ��
	CDateTimeCtrl dtcEndDate;

	//��־����
	CComboBox cmbLogType;

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

	//�����ݼ���Ӧ
	virtual BOOL PreTranslateMessage(MSG* pMsg);



	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	//��ҳ��ѯ��ɫ������Ϣ
	afx_msg void OnCbnSelchangeCmbupage();

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);



	//������־
	void TradeLog();

	//�ʼ���־
	void MailLog();

	//���������־
	void TaskLog();

	//ʹ�õ�����־���շѵ��ߣ�
	void UseItemLog();

	//�һ�������־
	void GuajiLog();

	//��С������־
	void BugleLog();

	//�˺ŵ�½�ǳ���¼
	void LoginLog();

	//�л���־���ͽ��в�ѯ
	afx_msg void OnCbnSelchangeCmblogtype();

	//��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//������־����
	void LogType();

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo();

	// ��ʾ������Ϣ
	void ShowOtherInfo();

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//ʹ�ùرհ�ť
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();
};
