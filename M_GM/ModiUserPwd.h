#pragma once


// CModiUserPwd 对话框

class CModiUserPwd : public CDialog
{
	DECLARE_DYNAMIC(CModiUserPwd)

public:
	CModiUserPwd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModiUserPwd();

// 对话框数据
	enum { IDD = IDD_DLGMODIUPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	//要分配权限的用户ID
	int userID;

	//要分配权限的用户名
	CString userName;
public:

	// 指示对话框当前状态
	int dlgStatus;

	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 初始化私有变量
	void initVar(CString uName,int uID);

	//修改密码
	afx_msg void OnBnClickedOk();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//关闭对话框
	afx_msg void OnBnClickedCancel();
};
