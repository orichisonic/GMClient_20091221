#pragma once
#include "afxdtctl.h"


// CUpdateUserMAC �Ի���

class CUpdateUserMAC : public CDialog
{
	DECLARE_DYNAMIC(CUpdateUserMAC)

public:
	CUpdateUserMAC(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdateUserMAC();

// �Ի�������
	enum { IDD = IDD_DLGUPDATEMAC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	//Ҫ����Ȩ�޵��û�ID
	int userID;

	//Ҫ����Ȩ�޵��û���
	CString userName;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:

	//CDateTimeCtrlʹ��ʱЧ
	CDateTimeCtrl dtcEndTime;

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// ��ʼ��˽�б���
	void initVar(CString uName,int uID);

	//����Mac�벢����ʹ��ʱЧ
	afx_msg void OnBnClickedOk();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�رնԻ���
	afx_msg void OnBnClickedCancel();
};
