#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CGTOWNNoticeInfo �Ի���

class CGTOWNNoticeInfo : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNNoticeInfo)

public:
	CGTOWNNoticeInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNNoticeInfo();

// �Ի�������
	enum { IDD = IDD_DLGNOTICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ���������б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ���ͻ��Ǳ༭����
	bool addOrEdit;

	// �Ƿ������д������͹���
	bool AllServer;

	// ������IP
	CString ServerIP;

	// ����������
	CString ServerName;

	// ����ID
	int NoticeID;

	//�������б���
	int listRWidth;

	//�������ݸ߶�
	int contentLength;

	//��ҳ���ݸ߶�
	int gPageLength;

	//��������
	int NoticeType;

public:
	// CListCtrl��Ϸ�������б�
	CListCtrl listServer;

	// CListCtrl������Ϣ
	CListCtrl listNotice;

	// CComboBox���淭ҳ
	CComboBox cmbPage;

	// CDateTimeCtrl��ʼ����
	CDateTimeCtrl dtcStartDate;

	// CDateTimeCtrl��������
	CDateTimeCtrl dtcEndDate;

	// CDateTimeCtrl��ʼʱ��
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl����ʱ��
	CDateTimeCtrl dtcEndTime;

	// CheckBox��������
	CButton checkSendImme;

	// CComboBox����״̬
	CComboBox cmbStatus;

	// CEdit���ͼ��
	CEdit txtInterval;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

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

	// ѡ��������Ϸ���������з���
	afx_msg void OnBnClickedCheckselectall();

	// �鿴������Ϣ
	afx_msg void OnBnClickedBtnnoticeinfo();

	// �鿴������Ϣ
	void NoticeInfo();

	// ��ҳ�鿴������Ϣ
	afx_msg void OnCbnSelchangeCmbpage();

	// ˫��������Ϣ����ɾ������///maple add
	afx_msg void OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult);

	// ���ͻ�༭����
	afx_msg void OnBnClickedBtnnotice();

	// �Ƿ��������͹���
	afx_msg void OnBnClickedCheckimme();

	// ���͹���
	void AddNotice();

	//�༭����
	void EditNotice();

	//�༭����
	void DelNotice();

	//����Ҫ���͹������Ϸ�������б�
	CString ReturnServerIP();

	//����Ҫ���͹������Ϸ�����������б�
	CString ReturnServerName();

	//����������Ϸ�������б�
	CString ReturnAllServerIP();

	//����������Ϸ�����������б�
	CString ReturnAllServerName();	

	void ReturnAllServerIP(char* allServerIP);
	// ������Ϣ
	afx_msg void OnBnClickedBtnreset();	

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//����������Ϣ��������������
	afx_msg void OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnClose();

};
