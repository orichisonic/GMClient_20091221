#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSDOMatchMul 对话框

class CSDOMatchMul : public CDialog
{
	DECLARE_DYNAMIC(CSDOMatchMul)

public:
	CSDOMatchMul(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSDOMatchMul();

// 对话框数据
	enum { IDD = IDD_DLGMATCHMUL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	
	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;
	CMap<int,int,int,int> SenceList;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//选择的服务器name
	CString strServer;

	// 是否在所有大区发送公告
	bool AllServer;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

	int nItem;

	//场景名称
	CString SenceName;

	//服务器列表宽度
	int listRWidth;
public:
	// 指示对话框当前状态
	int dlgStatus;

	// 初始化对话框
	virtual BOOL OnInitDialog();

	// 初始化显示字符
	void InitUI();

	// CListCtrl游戏服务器列表
	CListCtrl listServer;

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 选择所有游戏服务器进行发送
	afx_msg void OnBnClickedCheckselectall();

	//返回要发送公告的游戏服务器列表
	void ReturnServerIP(char* allServerIP);

	//返回要发送公告的游戏服务器名称列表
	CString ReturnServerName();

	// 关闭对话框
	afx_msg void OnClose();

	afx_msg void OnBnClickedCancel();

	CComboBox cmbWeekDay;//星期几

	CComboBox cmbSence;//比赛场景

	CComboBox cmbMode;//比赛模式

	//导入星期数
	void WeekDay();

	//导入比赛模式
	void Mode();

	//查询比赛场景
	void SenceQuery();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//批量添加场景
	afx_msg void OnBnClickedSearch();

	int MiniuteOpen;//开放分钟
	int MiniuteUnit;//联合分钟
	int GCash;//G币

	//查询场景
	afx_msg void OnBnClickedBtquerysence();


};
