#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSDOMatchMul �Ի���

class CSDOMatchMul : public CDialog
{
	DECLARE_DYNAMIC(CSDOMatchMul)

public:
	CSDOMatchMul(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSDOMatchMul();

// �Ի�������
	enum { IDD = IDD_DLGMATCHMUL };

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
	CString strServer;

	// �Ƿ������д������͹���
	bool AllServer;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

	int nItem;

	//��������
	CString SenceName;

	//�������б���
	int listRWidth;
public:
	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// CListCtrl��Ϸ�������б�
	CListCtrl listServer;

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ѡ��������Ϸ���������з���
	afx_msg void OnBnClickedCheckselectall();

	//����Ҫ���͹������Ϸ�������б�
	void ReturnServerIP(char* allServerIP);

	//����Ҫ���͹������Ϸ�����������б�
	CString ReturnServerName();

	// �رնԻ���
	afx_msg void OnClose();

	afx_msg void OnBnClickedCancel();

	CComboBox cmbWeekDay;//���ڼ�

	CComboBox cmbSence;//��������

	CComboBox cmbMode;//����ģʽ

	//����������
	void WeekDay();

	//�������ģʽ
	void Mode();

	//��ѯ��������
	void SenceQuery();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//������ӳ���
	afx_msg void OnBnClickedSearch();

	int MiniuteOpen;//���ŷ���
	int MiniuteUnit;//���Ϸ���
	int GCash;//G��

	//��ѯ����
	afx_msg void OnBnClickedBtquerysence();


};
