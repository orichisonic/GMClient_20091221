#pragma once
#include "afxcmn.h"
#include <afxtempl.h>
#include "OperationGM.h"


// CPopedomManage �Ի���

class CPopedomManage : public CDialog
{
	DECLARE_DYNAMIC(CPopedomManage)

public:
	CPopedomManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPopedomManage();

// �Ի�������
	enum { IDD = IDD_DLGPOPEDOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	//Ҫ����Ȩ�޵��û�ID
	int userID;

	//Ҫ����Ȩ�޵��û���
	CString userName;

	//Ҫ�����ģ������
	CMap<int,int,CString,CString> SendData;

	//���е�ģ������
	CSocketData ModuleData;

	//������������ģ������
	CSocketData UserModule;	

public:
	// ListCtrl������Ϸ�б�
	CListCtrl listGame;

	// ListCtrl����ģ���б�
	CListCtrl listModule;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// ��ʼ��˽�б���
	void initVar(CString uName,int uID);

	// �����Ի���
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// ����������Ϸ�б�
	void InitGameList();

	// ������Ϸ�б���ȡ��Ӧ��ģ���б�
	afx_msg void OnNMClickListgame(NMHDR *pNMHDR, LRESULT *pResult);

	// ����ģ���б�������Ӧ����Ϣ
	afx_msg void OnNMClickListmodule(NMHDR *pNMHDR, LRESULT *pResult);

	//����ҷ�����ϷȨ��
	afx_msg void OnBnClickedOk();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�رնԻ���
	afx_msg void OnBnClickedCancel();		
};
