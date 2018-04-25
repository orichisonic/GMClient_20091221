#pragma once
#include "afxwin.h"


// CSDOResupply �Ի���

class CSDOResupply : public CDialog
{
	DECLARE_DYNAMIC(CSDOResupply)

public:
	CSDOResupply(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSDOResupply();

// �Ի�������
	enum { IDD = IDD_DLGRESUPPLY };

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
//	CString Account, Name;

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

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

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

	//�������G��
	afx_msg void OnBnClickedSearch();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//����G�ҽ��
	afx_msg void OnBnClickedBtadd();
};
