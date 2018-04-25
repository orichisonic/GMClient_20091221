#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CModuleUpdate 对话框

class CModuleUpdate : public CDialog
{
	DECLARE_DYNAMIC(CModuleUpdate)

public:
	CModuleUpdate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModuleUpdate();

// 对话框数据
	enum { IDD = IDD_DLGUPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	int UpdateFileNum;

public:
	//显示当前正在下载的模块
	CStatic lblUpdate;

	//CProgressCtrl升级进度条
	CProgressCtrl progUpdate;

	//CEdit更新的文件内容
	CEdit txtContent;

	//判断能否自动更新
	CButton btnUpdate;

	//需要更新的文件名和路径
	CSocketData UpdateData;

	//和服务端连接的SOCKET
	SOCKET m_Socket;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
    void InitUI();	

	//初始化变量
	void InitVar(SOCKET mSocket);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//检测是否需要更新
	void CheckUpdate();

	//自动更新
	afx_msg void OnBnClickedBtnupdate();

	// 发送登录信息之后进行接收
	LRESULT OnLoginReceive(WPARAM wParam, LPARAM lParam);

	//重启GMTools
	afx_msg void OnBnClickedOk();
};
