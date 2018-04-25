#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using std::vector;
using std::map;
using std::pair;


void CALLBACK CircleGameAssist(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime);

// GMGameAssist �Ի���

class GMGameAssist : public CDialog
{
	DECLARE_DYNAMIC(GMGameAssist)

public:
	GMGameAssist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GMGameAssist();

// �Ի�������
	enum { IDD = IDD_DLGGAMEASSIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	// ������Ϸ��Ϣ
	CMap<int,int,int,int> GameList;

	// ��Ӧ�ķ�������Ϣ
	CMap<int,int,CString,CString> ServerList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	//��ϷID
	int GameID;

	//��Ϸ����
	CString GameName;

	// Ҫ��ѯ���������
	int AssitType;

	// ���������Ϣ�б�õ��к�
	int mItem;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	// ����ͣ������ʺ�
	CString UserAccount;

	// ����ͣ����ҽ�ɫ��
	CString UserName;

	//ҳ����ÿҳ��ʾ�ļ�¼����
	int iIndex,iPageSize;

	//�Ƿ�����ˢ��
	bool iRefresh;

	//ˢ��ʱ��
	int refreshTime;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight, grpPHeight;

	//�����ļ�·����
	CString exportFilePath;

	//�����ļ�·����
	CString importFilePath;

public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ����
	CComboBox cmbGame;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	//CComboBox �������
	CComboBox cmbAssit;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	// CGroupBox��ҳ����
	CStatic GrpPage;

	// CComboBox��ҳ��ѯ
	CComboBox cmbPage;

	// CListCtrl�����ʾ
	CListCtrl listResult;

	// CComboBox��ͣ����
	CComboBox cmbType;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	//��ʾexcel������ʺ���Ϣ
	CListCtrl listAccountImport;
	
	//��ʾexcel�����ʺ���Ϣ�е�vip�û�
	CListCtrl listVIPAccount;

	//��Ϸ������ӦIP��
	map<CString, CString> ServerCityToServerIP;

	//��ǰ���͵��ʺ�
	CString m_curAccount;

	//��ǰ�����ʺ��Ƿ�ΪVIP
	BOOL m_isVipAccount;

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

	//��Ӧ��ʱ������
	afx_msg void OnTimer(UINT nIDEvent);

	//��ȡ���е���Ϸ����
	void QueryGameList();

	//ͨ����Ϸ���Ʋ�ѯ��Ӧ����Ϸ������IP
	afx_msg void OnCbnSelchangeCmbgamename();

	//��ѯ��Ϸ�����Ϣ
	afx_msg void OnBnClickedSearch();

	//�޸�ѭ����ѯ��ʱ����
	afx_msg void OnBnClickedBtnstart();

	//��ѯ��Ϸ�����Ϣ
	void GameAssist();

	// ��ҳ���в�ѯ
	afx_msg void OnCbnSelchangeCmbpage();

	// ���������Ϣ�б��浱ǰ�к�
	afx_msg void OnNMClickListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫�������Ϣ�б����������
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	// �л�ѡ����в���
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);	

	// ��ͣ�ʺ�
	afx_msg void OnBnClickedBtnban();

	// ������Ϣ
	afx_msg void OnBnClickedBtnreset();

	//�������ݵ�xls�ļ�  Added by yanfei_qin 2010-9-15
	afx_msg void OnBnClickedBtnExport();
	
	//�򿪵����ļ��Ի���
	//afx_msg void OnBnClickedOpenFileExport();
	
	//�򿪵����ļ��Ի���
	//afx_msg void OnBnClickedOpenFileImport();

	//��xls�ļ�������clistctrl
	afx_msg void OnBnClickedBtnImport();
	
	//������ͣ�ʺ�
	afx_msg void OnBnClickedBtnBanBatch();

	//������ѯ�ʺ��Ƿ�vip
	afx_msg void OnBnClickedCheckVip();

	//������ѯ�����Ϣ
	afx_msg void OnBnClickedBtnCheckAccountAll();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);


	// �رնԻ���
	afx_msg void OnBnClickedCancel();

	// �رնԻ���
	afx_msg void OnClose();

public:
	//��ʾ�����Ϣ�б�
	void ShowUserInfo(int m_cmdShow);

	//��ʾ��ͣ�ʺ�
	void ShowBanPlayer(int m_cmdShow);	

	//��ʾ����ķ�ͣ�ʺ�ҳ��
	void ShowExcelBanPlayer(int m_cmdShow);

public:
	HANDLE m_hCheckVipEvent;
	HANDLE m_hCheckVipThread;

	HANDLE m_hBanAccountEvent;
	HANDLE m_hBanAccountThread;
	
	//��װ�����ʺ���Ϣ
	static DWORD WINAPI sendBanAccountList(LPVOID pClsParam);
	static DWORD WINAPI GMGameAssist::sendVIPAccountRequest(LPVOID pClsParam); 
public:
	
};
