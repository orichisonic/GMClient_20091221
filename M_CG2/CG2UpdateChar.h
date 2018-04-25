#pragma once

#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
// CCG2UpdateChar �Ի���

class CCG2UpdateChar : public CDialog
{
	DECLARE_DYNAMIC(CCG2UpdateChar)

public:
	CCG2UpdateChar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2UpdateChar();

// �Ի�������
	enum { IDD = IDD_DLGUPDATECHAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ʼ����ʾ�ַ�
	void InitUI();

	private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// �ж��û��б��Ƿ���Ҫ��ҳ
	bool pageUInfo;

	// ��Ϸ������IP
	CString ServerIP;

	// ���ID
	CString UserID;

	// ���������ʺ�
	CString UserName;

	// ���������ǳ�
	CString UserNick;

	//��ҽ�ɫ��ְҵid
	CString UserJob;
	
	//��ҽ�ɫ��
	int iCharNo;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;
public:
	//��Ϸ��������Ͽ�
	CComboBox cmbServer;

	//��ҳ��Ͽ�
	CComboBox cmbPage;

	//��ʾ�б��
	CListCtrl listUser;

	//��������
	CStatic GrpSearch;

	//��ҳ����
	CStatic GrpPage;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//��ʼ���Ի���
	virtual BOOL OnInitDialog();
	
	//�رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedUicancel();

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	//�Զ����ڴ���
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	void UserInfo();//���������Ϣ

	afx_msg void OnBnClickedUisearch();//�����ѯ��ť
	
	//�л�tabCtrl
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);
	
	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	
	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	void JobQuery();//ְҵ��ѯ

	//��ְҵ��Ͽ�
	CComboBox cmbNewJob;

	//�޸İ�ť
	afx_msg void OnBnClickedBtupdate();
	//���ð�ť
	afx_msg void OnBnClickedBtreset();
};
