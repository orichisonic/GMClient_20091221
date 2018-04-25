#pragma once

#include "OperationJW2.h"
#include "afxcmn.h"
#include "afxwin.h"

// CJW2ItemManage �Ի���

class CJW2ItemManage : public CDialog
{
	DECLARE_DYNAMIC(CJW2ItemManage)

public:
	CJW2ItemManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJW2ItemManage();

// �Ի�������
	enum { IDD = IDD_DLGITEMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	//������õ����б���к�
	int nItemResult;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// �ж��û��б��Ƿ���Ҫ��ҳ
	bool pageUInfo;

	//��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ����ʺ�
	CString UserAccount;

	// ���ID
	int UserID;

	// ���������ʺ�
	CString UserName;

	// ���������ǳ�
	CString UserNick;

	//��ѯ���������¼������
	int iType;

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

	//CComboBox������������
	CComboBox cmbType;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	//�����ݼ���Ӧ����
    virtual BOOL PreTranslateMessage(MSG* pMsg);

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

	// ��ѯ��ҵ�����Ϣ
	void ItemInfo();

	// ɾ������
	void DelItem();

	// ��ѯ��ҹ��������¼
	void PresentInfo();

	// ѡ��ͬ���Ͳ�ѯ��ҹ��������¼
	afx_msg void OnCbnSelchangeCmbtype();

	// ��ѯ��������Ե���ʹ��
	void ConsumeItem();

	// ��ѯ���С���ȷ��ͼ�¼
	void BugleSend();

	//�û�����
	void UserFamily();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbuipage();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�����û�������Ϣ��������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListcharacter(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnBnClickedUicancel();

	// �رնԻ���
	afx_msg void OnClose();			

public:
	//��ʼ��������������
	void InitItemPos();
	CComboBox cmbPos;
	afx_msg void OnCbnSelchangeCmbpos();
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//��ʾ��ӵ���
	void ShowAddItem(int nCmdShow);
	
	//��ʾ�޸�G��
	void ShowModifyMoney(int nCmdShow);

	afx_msg void OnBnClickedBtnsend();

	void AddItem();
	void ModifyMoney();
	afx_msg void OnBnClickedBtnblursearch();
	CListCtrl listItem;
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnBnClickedBtndelete();

	int addItem;
	int delItem;
	CListCtrl listItemResult;
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnreset();

	//��֤Ȩ��
	void ValidateProductManage();

	//��֤ͨ����Ȩ�ޱ��м�ȥ
	void DeductProductManage();
};
