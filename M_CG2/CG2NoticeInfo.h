#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CCG2NoticeInfo �Ի���

class CCG2NoticeInfo : public CDialog
{
	DECLARE_DYNAMIC(CCG2NoticeInfo)

public:
	CCG2NoticeInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2NoticeInfo();

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

	//������Name
	CString ServerName;

	// ����ID
	CString NoticeID;

	//�������б���
	int listRWidth;

	//�������ݸ߶�
	int contentLength;

	//��ҳ���ݸ߶�
	int gPageLength;

public:
	// CListCtrl��Ϸ�������б�
	CListCtrl listResult;

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
public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

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
	afx_msg void OnCbnSelchangeCmbuipage();

	// ˫��������Ϣ���б༭
	afx_msg void OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult);	

	// ���ͻ�༭����
	afx_msg void OnBnClickedBtnnotice();	

	// �Ƿ��������͹���
	afx_msg void OnBnClickedCheckimme();

	// ���͹���
	void AddNotice();

	//�༭����
	void EditNotice();

	//ɾ������
	void DelNotice();

	//����Ҫ���͹������Ϸ������IP�б�
	CString ReturnServerIP();

	//����Ҫ���͹������Ϸ�����������б�
	CString ReturnServerName();


	// ������Ϣ
	afx_msg void OnBnClickedBtnreset();	

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnClose();		
};
