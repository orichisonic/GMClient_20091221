#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// CGMOperationLog �Ի���

class CGMOperationLog : public CDialog
{
	DECLARE_DYNAMIC(CGMOperationLog)

public:
	CGMOperationLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGMOperationLog();

// �Ի�������
	enum { IDD = IDD_DLGGMLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ������Ϸ��Ϣ
	CMap<int,int,int,int> GameList;

	// ��Ӧ�ķ�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ��Ӧ�������Ϣ
	CMap<int,int,int,int> UserList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	//��ϷID
	int GameID;

	//��Ϸ����
	CString GameName;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// �õ��������ʵ����
	CString UserName;

	// �õ������ID
	int UserID;

	//�����ؼ��ĸ߶�
	int grpHeight, grpPHeight;

	//��ʼʱ��
	CString strStartTime;

	//����ʱ��
	CString strEndTime;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ����
	CComboBox cmbGame;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CDateTimeCtrl��ʼʱ��
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl����ʱ��
	CDateTimeCtrl dtcEndTime;

	//CComboBox GM��ʵ����
	CComboBox cmbRealName;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	//�����ݼ���Ӧ����
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//��ȡ���е��û�����
	void QueryUserList();

	//��ȡ���е���Ϸ����
	void QueryGameList();

	//ͨ����Ϸ���Ʋ�ѯ��Ӧ����Ϸ������IP
	afx_msg void OnCbnSelchangeCmbgamename();

	// ��ѯGM������־
	afx_msg void OnBnClickedSearch();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();
};
