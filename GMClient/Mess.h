#pragma once


// CMess �Ի���

class CMess : public CDialog
{
	DECLARE_DYNAMIC(CMess)

public:
	CMess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMess();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
