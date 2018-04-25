#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSDOMatchManager �Ի���

class CSDOMatchManager : public CDialog
{
	DECLARE_DYNAMIC(CSDOMatchManager)

public:
	CSDOMatchManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSDOMatchManager();

// �Ի�������
	enum { IDD = IDD_DLGMATCHMANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	
	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;
	CMap<int,int,int,int> SenceList;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//ѡ��ķ�����name
//	CString strServer;

	// ��õ�����ʺźͽ�ɫ��
//	CString UserAccount, UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

	//���ID
//	int UserID;
	int nItem;

	bool pageInfo;
public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

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

	// �л�ѡ����в�ѯ
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//���ڼ�
	CComboBox cmbWeekDay;

	//��������
	CComboBox cmbSence;
	//����ģʽ
	CComboBox cmbMode;

	//��ӻ���ɾ������
	afx_msg void OnBnClickedSearch();

	//����������
	void WeekDay();

	//�������ģʽ
	void Mode();

	//��ѯ��������
	void SenceQuery();

	//��ӱ���
	void AddMatch();

	//�༭����
	void UpdateMatch();

	//������Ϣ�б�
	CListCtrl listMatch;

	//��ʾ������Ϣ
	void ShowMatch();

	//��ʾ������Ϣ
	void ShowOther();

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//��ѯ������Ϣ
	afx_msg void OnBnClickedBtok();

	//����������Ϣ�б��
	afx_msg void OnNMClickListmatch(NMHDR *pNMHDR, LRESULT *pResult);

	int MiniuteOpen;//���ŷ���
	int MiniuteUnit;//���Ϸ���
	int GCash;//G��

	int SenceID;//����id

	//˫��������Ϣ�б��ɾ��
	afx_msg void OnNMDblclkListmatch(NMHDR *pNMHDR, LRESULT *pResult);

	//ɾ��������Ϣ
	void DelMatch();
	//������������
	afx_msg void OnLvnColumnclickListmatch(NMHDR *pNMHDR, LRESULT *pResult);

	//��ҳ��Ͽ�
	CStatic GrpPage;

	//��ҳ��
	CComboBox cmbPage;

	//�л���ҳ��
	afx_msg void OnCbnSelchangeCmbpage();
};
