#pragma once

#include "OperationGM.h"
// CModiPwd �Ի���

class CModiPwd : public CDialog
{
	DECLARE_DYNAMIC(CModiPwd)

public:
	CModiPwd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModiPwd();

// �Ի�������
	enum { IDD = IDD_DLGMODIPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:

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

	// �����޸����������Ϣ֮����н���
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// �޸��������
	afx_msg void OnBnClickedModipwd();

	// ������Ϣ
	afx_msg void OnBnClickedMpreset();

	// �رնԻ���
	afx_msg void OnClose();	
};
