#pragma once

#include "OperationGTOWN.h"
#include "afxwin.h"
#include "afxcmn.h"

// CGTOWNKickPlayer �Ի���

class CGTOWNKickPlayer : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNKickPlayer)

public:
	CGTOWNKickPlayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGTOWNKickPlayer();

// �Ի�������
	enum { IDD = IDD_DLGKICKPLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	private:
	// �����û��б��õ��к�
	int nItem;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//���������ʺźͽ�ɫ��
	CString Account, Name;

	// ��õ�����ʺźͽ�ɫ��
	CString UserAccount, UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, grpPHeight;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	//��ҳ����
	CStatic GrpPage;

	//��ҳ��Ͽ�
	CComboBox cmbPage;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	//������ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	//��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbpage();

	// ˫�����������Ϣǿ���������
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	//��ӦWM_CLOSE��Ϣ
	afx_msg void OnClose();
};