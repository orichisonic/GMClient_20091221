#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CJW2ProductManage �Ի���

class CJW2ProductManage : public CDialog
{
	DECLARE_DYNAMIC(CJW2ProductManage)

public:
	CJW2ProductManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJW2ProductManage();

// �Ի�������
	enum { IDD = IDD_DLGPRODUCTMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// ���������б�õ��к�
	int nItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// ��Ӧ�������Ϣ
	CMap<int,int,int,int> UserList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ���ͻ��Ǳ༭����
	bool addOrEdit;

	// �Ƿ������д������͹���
	bool AllServer;

	// ������IP
	CString ServerIP;

	// Ȩ��ID
	int ProductID;

	//�������б���
	int listRWidth;

	//�������ݸ߶�
	int contentLength;

	//��ҳ���ݸ߶�
	int gPageLength;

public:
	// CListCtrl��Ϸ�������б�
	CListCtrl listResult;

	// CListCtrl������Ϣ
	CListCtrl listNotice;

	// CComboBox���淭ҳ
	CComboBox cmbPage;

	// CDateTimeCtrl��ʼ����
	CDateTimeCtrl dtcStartDate;

	// CDateTimeCtrl��������
	CDateTimeCtrl dtcEndDate;

	// CDateTimeCtrl��ʼʱ��
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl����ʱ��
	CDateTimeCtrl dtcEndTime;

	// CheckBox��������
	CButton checkSendImme;

	// CComboBox����״̬
	CComboBox cmbStatus;

	// CEdit���ͼ��
	CEdit txtInterval;

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

	// ѡ��������Ϸ���������з���
//	afx_msg void OnBnClickedCheckselectall();

	// �鿴������Ϣ
//////	afx_msg void OnBnClickedBtnnoticeinfo();

	// �鿴������Ϣ
//////	void NoticeInfo();

	// ��ҳ�鿴������Ϣ
/////	afx_msg void OnCbnSelchangeCmbuipage();

	// ˫��������Ϣ���б༭
/////	afx_msg void OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult);	

	// ����Ȩ��
	afx_msg void OnBnClickedBtnnotice();	

	// �Ƿ��������͹���
/////	afx_msg void OnBnClickedCheckimme();

	// ���͹���
/////	void AddNotice();

	//�༭����
//////	void EditNotice();

	//����Ҫ���͹������Ϸ�������б�
	CString ReturnServerIP();

	// ������Ϣ
	afx_msg void OnBnClickedBtnreset();	

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//����������Ϣ��������������
	afx_msg void OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult);

	// �رնԻ���
	afx_msg void OnClose();		

	//��ȡ���е��û�����
	void QueryUserList();
	CComboBox cmbRealName;
	afx_msg void OnBnClickedButton3();
	CListCtrl listItem;
	afx_msg void OnBnClickedButton1();
	CListCtrl listItemResult;
	afx_msg void OnBnClickedButton2();

	int addItem;
	int delItem;
	CString selectItemID;//��ֹ�ظ����

	int MulAddItem[100];


	void MulInsertListCtrl(int nSel);
	//int ii;
	//maple add

	int CountItemPrice;//�ܶ�

	afx_msg void OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);


/////////	CComboBox cmbGM;


	CButton m_ckServer;//ȫѡcheckBox
	afx_msg void OnBnClickedCheckselectall();

	//�鿴Ȩ��
	afx_msg void OnBnClickedBtnnoticeinfo();

	//˫��ɾ��Ȩ��
	afx_msg void OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult);

	void DelProductManager();
	//��ҳ�鿴Ȩ��
	afx_msg void OnCbnSelchangeCmbuipage();

	//��֤Ȩ��
	afx_msg void OnBnClickedBtnvalidate();
};
