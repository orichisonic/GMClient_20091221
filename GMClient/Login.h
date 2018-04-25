#pragma once

#include "..\\Event\\Event.h"
#include "afxwin.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

// CLogin �Ի���

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
	enum { IDD = IDD_DLGLOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	//�ж��Ƿ����ӳɹ�
	bool m_connectflag;

public:
	//�ж��ܷ�鿴ͼƬ
	CStatic m_PicView;

public:

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ʹ�õ�¼��ť
	afx_msg void OnBnClickedOk();

	// ʹ�ùرհ�ť
	afx_msg void OnBnClickedCancel();
	
	// ���͵�¼��Ϣ֮����н���
	LRESULT OnLoginReceive(WPARAM wParam, LPARAM lParam);
	
	// ��ȡIP��ַ
	char* GetIP(void);

	// ��ȡMAC��
	CString GetMAC(void);

	// �رյ�ʱ����еĲ���
	LRESULT OnLoginClose(WPARAM wParam, LPARAM lParam);	
	
};
