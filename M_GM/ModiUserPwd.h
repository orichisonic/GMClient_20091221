#pragma once


// CModiUserPwd �Ի���

class CModiUserPwd : public CDialog
{
	DECLARE_DYNAMIC(CModiUserPwd)

public:
	CModiUserPwd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModiUserPwd();

// �Ի�������
	enum { IDD = IDD_DLGMODIUPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	//Ҫ����Ȩ�޵��û�ID
	int userID;

	//Ҫ����Ȩ�޵��û���
	CString userName;
public:

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// ��ʼ��˽�б���
	void initVar(CString uName,int uID);

	//�޸�����
	afx_msg void OnBnClickedOk();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�رնԻ���
	afx_msg void OnBnClickedCancel();
};
