#pragma once

//#include "OperationWA.h"
//#include "afxcmn.h"
//#include "afxwin.h"

// GoodsInfor �Ի���

// ��Ʒ��ѯλ��
enum ITEM__POS_TYPE
{
	ITEM_BODY			= 0,	// ��ɫ������Ʒ
	ITEM_BAG			= 1,	// ��ɫ������Ʒ
	ITEM_BANK			= 2		// ��ɫ������Ʒ

}; 

class GoodsInfor : public CDialog
{
	DECLARE_DYNAMIC(GoodsInfor)

public:
	GoodsInfor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GoodsInfor();

	// �Ի�������
	enum { IDD = IDD_DLGGOODSINFOR};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б��õ��к�
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
	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CComboBox��ҽ�ɫ��Ϣ��ҳ��ѯ
	CComboBox cmbUPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl���������Ϣ
	CListCtrl listUser;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CGroupBox��������
	CStatic GrpSearch;

	// CGroupBox��ҳ����
	CStatic GrpPage;

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

	// ��ѯ���������Ϣ
	afx_msg void OnBnClickedUisearch();

	// ��ҳ��ѯ���������Ϣ
	afx_msg void OnCbnSelchangeCmbuserpage();

	// �������������Ϣ���浱ǰ�к�
	afx_msg void OnNMClickListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ��ѯ���������Ϣ
	void UserInfo();

	// װ����Ϣ��ѯ(0 ���ϣ� 1 ������ 2 ����)
	void CharItemInfo(int itemPos);

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//��������������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();			


	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);
};