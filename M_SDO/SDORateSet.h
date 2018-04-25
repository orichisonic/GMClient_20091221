#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSDORateSet �Ի���

class CSDORateSet : public CDialog
{
	DECLARE_DYNAMIC(CSDORateSet)

public:
	CSDORateSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSDORateSet();

// �Ի�������
	enum { IDD = IDD_DLGRATESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;
	CMap<int,int,int,int> ItemCodeList;//�����б�
	CMap<int,int,int,int> ItemCodeListF;//Ů�Ե����б�

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//��������
	CString ItemName;

	//���������ʺźͽ�ɫ��
//	CString Account, Name;

	// ��õ�����ʺźͽ�ɫ��
//	CString UserAccount, UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

	int iType;//����ֵ

	int iSort;//С��ֵ

	//����ֵ
	int iRate;

	//ʹ�ô���
	int iUseTimes;

	//ʹ������
	int iUseLimit;

	int iItemCode,iItemCode1,iItemCode2;

	//��������1����������2
	CString ItemName1,ItemName2;
public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	//�����Ϣ��ҳ��Ͽ�
	CStatic GrpPage;

	// CListCtrl�����ʾ
	CListCtrl listItem;

	//��ҳ��Ͽ�
	CComboBox cmbPage;

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

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo();

	// ��ʾ������Ϣ
	void ShowOtherInfo();

	// ���������б��浱ǰ�к�
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�������б�ɾ��
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//���������Ϣ��������������
	afx_msg void OnLvnColumnclickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//��ѯ������Ϣ
	afx_msg void OnBnClickedSearch();

	//��ӻ��߱༭����
	afx_msg void OnBnClickedBtok();

	//�������������
	void ItemType();

	//�л�����
	afx_msg void OnCbnSelchangeCmbbigtypem();

	//�л�С��
	afx_msg void OnCbnSelchangeCmbsmalltypem();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);
	CComboBox cmbBigTypeM;
	CComboBox cmbSmallTypeM;
	CComboBox cmbGoods;

	//��ѯ���Ե���
	void MaleItem();

	//���ӱ���
	void AddRate();

	//�༭����
	void UpdateRate();

	//�Ա�
	CComboBox cmbSex;

	//ɾ������
	void DelRate();
};
