#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CModuleUpdate �Ի���

class CModuleUpdate : public CDialog
{
	DECLARE_DYNAMIC(CModuleUpdate)

public:
	CModuleUpdate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModuleUpdate();

// �Ի�������
	enum { IDD = IDD_DLGUPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	int UpdateFileNum;

public:
	//��ʾ��ǰ�������ص�ģ��
	CStatic lblUpdate;

	//CProgressCtrl����������
	CProgressCtrl progUpdate;

	//CEdit���µ��ļ�����
	CEdit txtContent;

	//�ж��ܷ��Զ�����
	CButton btnUpdate;

	//��Ҫ���µ��ļ�����·��
	CSocketData UpdateData;

	//�ͷ�������ӵ�SOCKET
	SOCKET m_Socket;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
    void InitUI();	

	//��ʼ������
	void InitVar(SOCKET mSocket);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//����Ƿ���Ҫ����
	void CheckUpdate();

	//�Զ�����
	afx_msg void OnBnClickedBtnupdate();

	// ���͵�¼��Ϣ֮����н���
	LRESULT OnLoginReceive(WPARAM wParam, LPARAM lParam);

	//����GMTools
	afx_msg void OnBnClickedOk();
};
