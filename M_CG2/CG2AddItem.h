#pragma once


// CCG2AddItem �Ի���
#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

class CCG2AddItem : public CDialog
{
	DECLARE_DYNAMIC(CCG2AddItem)

public:
	CCG2AddItem(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCG2AddItem();

// �Ի�������
	enum { IDD = IDD_DLGADDITEM };

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

	//��ҽ�ɫ��������
	CString UserSkill;
	
	//��ҽ�ɫ���ܵȼ�
	int UserSkillLevel;

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

	//// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//��ʼ���Ի���
	virtual BOOL OnInitDialog();

	//�Զ����ڴ�С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//�رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedUicancel();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//��һ�����Ϣ
	void UserInfo();
	afx_msg void OnBnClickedUisearch();

	//�л�tabCtrl
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�����������Ϣ���в�ѯ
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//��������ѯ
	void ItemType();

	//���������Ͽ�
	CComboBox cmbItemType;

	//����������Ͽ�
	CComboBox cmbItemName;


   //�л����������Ͽ�
	afx_msg void OnCbnSelchangeCmbitemtype();

	//���õ�������
	void SetNumber();

	//����������Ͽ�
	CComboBox cmbItemNumber;

	//������͵����б�
	afx_msg void OnBnClickedBtright();

	//������͵����б�
	CListCtrl listItem;

	//ɾ�����͵����б�
	afx_msg void OnBnClickedBtleft();

	//���������б����к�
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//��ӵ���
	afx_msg void OnBnClickedBtadd();

	//������ð�ť
	afx_msg void OnBnClickedBtreset();
};
