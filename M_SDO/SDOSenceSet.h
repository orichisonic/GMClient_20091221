#pragma once
#include "afxcmn.h"


// CSDOSenceSet �Ի���

class CSDOSenceSet : public CDialog
{
	DECLARE_DYNAMIC(CSDOSenceSet)

public:
	CSDOSenceSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSDOSenceSet();

// �Ի�������
	enum { IDD = IDD_DLGSENCESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
		int nItem;

		int tbcHeight;//TabCtrl�ĸ߶�

		//����ID
		int SenceID;

		//��������
		CString SenceName;

public:
	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	//��ʾ�����б���Ϣ
	void ShowSence();

	//�����б�ͷ����
	afx_msg void OnLvnColumnclickListsence(NMHDR *pNMHDR, LRESULT *pResult);

	//���ͳ�����Ϣ
	void SenceInfo();

	//��ʾ��������
	void ShowOther();

	//�����б��
	CListCtrl listSence;

	//�л�tabCtrl
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//���������б��
	afx_msg void OnNMClickListsence(NMHDR *pNMHDR, LRESULT *pResult);

	//��ӻ��߱༭����
	afx_msg void OnBnClickedSearch();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//�رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//��ӳ���
	void AddSence();

	//�༭����
	void UpdateSence();

	//˫�������б�ɾ��
	afx_msg void OnNMDblclkListsence(NMHDR *pNMHDR, LRESULT *pResult);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);
};
