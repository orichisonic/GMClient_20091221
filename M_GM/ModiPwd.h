#pragma once

#include "OperationGM.h"
// CModiPwd 对话框

class CModiPwd : public CDialog
{
	DECLARE_DYNAMIC(CModiPwd)

public:
	CModiPwd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModiPwd();

// 对话框数据
	enum { IDD = IDD_DLGMODIPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:

	// 指示对话框当前状态
	int dlgStatus;

	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 发送修改玩家密码信息之后进行接收
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 修改玩家密码
	afx_msg void OnBnClickedModipwd();

	// 重置信息
	afx_msg void OnBnClickedMpreset();

	// 关闭对话框
	afx_msg void OnClose();	
};
