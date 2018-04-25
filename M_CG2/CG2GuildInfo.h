#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CCG2GuildInfo �Ի���

class CCG2GuildInfo : public CDialog
{
	DECLARE_DYNAMIC(CCG2GuildInfo)

public:
	CCG2GuildInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2GuildInfo();

// �Ի�������
	enum { IDD = IDD_DLGGUILDINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;
	int mItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageUInfo;
	bool pageInfo;	

	// ��Ϸ������IP
	CString ServerIP;

	//����Ĺ�������
	CString GuildName;

	//����Ĺ���ID
	int GuildId;

	//����û���
	CString UserName;

	// ����ǳ�
	CString UserNick;

	// ���ID
	CString UserID;

	//��ɫ��
	int iCharNo;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// CEdit����ʺ�
	CEdit txtAccount;

	// CDateTimeCtrl��ͣ��ֹ����
	CDateTimeCtrl dtcBanEndDate;

	// CDateTimeCtrl��ͣ��ֹʱ��
	CDateTimeCtrl dtcBanEndTime;

	// CComboBox��ͣ����
	CComboBox cmbBanType;

	// CListCtrl����������Ϣ
	CListCtrl listGuild;

	//�û�������Ϣ��ҳ
	CComboBox cmbUPage;

	// CEdit�����ͣԭ��
	CEdit txtReason;

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

	// ��ѯ������Ϣ
	afx_msg void OnBnClickedUisearch();

	// ��ѯ������Ϣ
	void GuildInfo();

	// ��ѯ�����Ա��Ϣ
	void GuildDetail();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	// ��ҳ��ѯ��ͣ�˺��б�
	afx_msg void OnCbnSelchangeCmbpage();

	// ����������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫��������Ϣ���в���
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);
	

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �رնԻ���	
	afx_msg void OnBnClickedUicancel();	

	// �رնԻ���
	afx_msg void OnClose();
};
