#pragma once

#include "..\\Event\\Event.h"
#include "afxwin.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

// CLogin 对话框

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogin();

// 对话框数据
	enum { IDD = IDD_DLGLOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	//判断是否连接成功
	bool m_connectflag;

public:
	//判断能否查看图片
	CStatic m_PicView;

public:

	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 使用登录按钮
	afx_msg void OnBnClickedOk();

	// 使用关闭按钮
	afx_msg void OnBnClickedCancel();
	
	// 发送登录信息之后进行接收
	LRESULT OnLoginReceive(WPARAM wParam, LPARAM lParam);
	
	// 获取IP地址
	char* GetIP(void);

	// 获取MAC码
	CString GetMAC(void);

	// 关闭的时候进行的操作
	LRESULT OnLoginClose(WPARAM wParam, LPARAM lParam);	
	
};
