#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#import "c:\program files\common files\system\ado\msado15.dll"\
	no_namespace \
	rename ("EOF", "adoEOF")
// CJW2Import 对话框

class CJW2Import : public CDialog
{
	DECLARE_DYNAMIC(CJW2Import)

public:
	CJW2Import(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJW2Import();

// 对话框数据
	enum { IDD = IDD_DLGIMPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;


	//游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;



	//各个控件的高度
	int grpHeight, grpPHeight;

public:
	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CComboBox翻页查询
	CComboBox cmbPage;

	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CGroupBox翻页容器
	CStatic GrpPage;

	// 指示对话框当前状态
	int dlgStatus;

public:
	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	//处理快捷键响应函数
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);






	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	// 关闭对话框	
	afx_msg void OnBnClickedUicancel();

	// 关闭对话框
	afx_msg void OnClose();
	
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedComfirm();
	void ReadXls(CString m_filePath,CString* m_allUserName);
	CTabCtrl tbcResult;
};
