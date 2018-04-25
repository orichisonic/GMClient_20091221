#pragma once

#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
// CCG2LogQuery �Ի���

class CCG2LogQuery : public CDialog
{
	DECLARE_DYNAMIC(CCG2LogQuery)

public:
	CCG2LogQuery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2LogQuery();

// �Ի�������
	enum { IDD = IDD_DLGLOGQUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

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

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

public:
	//��Ϸ��������Ͽ�
	CComboBox cmbServer;

	//��ҳ��Ͽ�
	CComboBox cmbPage;

	//��ʾ�б��
	CListCtrl listUser;
	CListCtrl listResult;

	//��������
	CStatic GrpSearch;

	//��ҳ����
	CStatic GrpPage;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//�Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedUisearch();

	void UserInfo();//���������Ϣ

	//�رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedUicancel();

	//CTabCtrlѡ�
	CTabCtrl tbcResult;

	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);//�л�tabCtrl

	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);//�����б��

	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);//˫���б��

	CComboBox cmbCategory;//��־����

	afx_msg void OnCbnSelchangeCmbcategory();//�л���־������Ͽ�

	CComboBox cmbAction;//��־С��

	afx_msg void OnBnClickedBtsearch();//��־��ѯ��ť

	CDateTimeCtrl dtcStartDate;//��ʼ����
	CDateTimeCtrl dtcStartTime;//��ʼʱ��

	CDateTimeCtrl dtcEndDate;//��ʼ����
	CDateTimeCtrl dtcEndTime;//����ʱ��
};
