#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSDOMatchManager 对话框

class CSDOMatchManager : public CDialog
{
	DECLARE_DYNAMIC(CSDOMatchManager)

public:
	CSDOMatchManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSDOMatchManager();

// 对话框数据
	enum { IDD = IDD_DLGMATCHMANAGER };

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
//	CString strServer;

	// 获得的玩家帐号和角色名
//	CString UserAccount, UserName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

	//玩家ID
//	int UserID;
	int nItem;

	bool pageInfo;
public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

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

	// 关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//星期几
	CComboBox cmbWeekDay;

	//比赛场景
	CComboBox cmbSence;
	//比赛模式
	CComboBox cmbMode;

	//添加或者删除比赛
	afx_msg void OnBnClickedSearch();

	//导入星期数
	void WeekDay();

	//导入比赛模式
	void Mode();

	//查询比赛场景
	void SenceQuery();

	//添加比赛
	void AddMatch();

	//编辑比赛
	void UpdateMatch();

	//比赛信息列表
	CListCtrl listMatch;

	//显示比赛信息
	void ShowMatch();

	//显示其它信息
	void ShowOther();

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//查询比赛信息
	afx_msg void OnBnClickedBtok();

	//单击比赛信息列表框
	afx_msg void OnNMClickListmatch(NMHDR *pNMHDR, LRESULT *pResult);

	int MiniuteOpen;//开放分钟
	int MiniuteUnit;//联合分钟
	int GCash;//G币

	int SenceID;//场景id

	//双击比赛信息列表框删除
	afx_msg void OnNMDblclkListmatch(NMHDR *pNMHDR, LRESULT *pResult);

	//删除比赛信息
	void DelMatch();
	//单击列名排序
	afx_msg void OnLvnColumnclickListmatch(NMHDR *pNMHDR, LRESULT *pResult);

	//翻页组合框
	CStatic GrpPage;

	//翻页框
	CComboBox cmbPage;

	//切换翻页框
	afx_msg void OnCbnSelchangeCmbpage();
};
