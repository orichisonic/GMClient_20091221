#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#import "c:\program files\common files\system\ado\msado15.dll"\
	no_namespace \
	rename ("EOF", "adoEOF")


// CWAMailSend �Ի���

class CWAMailSend : public CDialog
{
	DECLARE_DYNAMIC(CWAMailSend)

public:
	CWAMailSend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWAMailSend();

// �Ի�������
	enum { IDD = IDD_DLGMAILSEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ���н�ɫ����Ϣ
	CMap<int,int,CString,CString> UserList;

	// �����ʼ�������Ϣ
	CMap<int,int,CString,CString> TitleList;

	// �����ʼ�������Ϣ
	CMap<int,int,CString,CString> ContentList;

	// ��Ϸ������IP
	CString ServerIP;

	//��ҽ�ɫ��
	CString UserNick;

	//�ʼ�����
	CString MailTitle;

	//�ʼ�����
	CString MailContent;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	//CProgressCtrl���͵��߽�����
	CProgressCtrl progMail;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//ѡ���Ƿ����ڵ�һ�η����ʼ�
	int nFirst;

	//�������ʼ��Ľ�ɫ������
	int UserNum;

	//��ǰ���ڷ��͵Ľ�ɫ���
	int mCurNum;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//��ȡѡ���ServerIP
	afx_msg void OnCbnSelchangeCmbserver();

	//ѡ�����������ʼ����ļ�
	afx_msg void OnBnClickedBtnbrowse();

	//���������ʼ���Ϣ
	afx_msg void OnBnClickedBtnsend();

	//��ȡxls�ļ�
	bool ReadXls(CString m_filePath);

	//�����ʼ�
	void SendMail();

	//������Ϣ
	afx_msg void OnBnClickedBtnreset();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnClose();		
};
