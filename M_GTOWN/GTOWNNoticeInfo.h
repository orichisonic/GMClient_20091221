#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CGTOWNNoticeInfo 对话框

class CGTOWNNoticeInfo : public CDialog
{
	DECLARE_DYNAMIC(CGTOWNNoticeInfo)

public:
	CGTOWNNoticeInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGTOWNNoticeInfo();

// 对话框数据
	enum { IDD = IDD_DLGNOTICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击公告列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;

	// 发送还是编辑公告
	bool addOrEdit;

	// 是否在所有大区发送公告
	bool AllServer;

	// 服务器IP
	CString ServerIP;

	// 服务器名字
	CString ServerName;

	// 公告ID
	int NoticeID;

	//服务器列表宽度
	int listRWidth;

	//公告内容高度
	int contentLength;

	//翻页内容高度
	int gPageLength;

	//公告类型
	int NoticeType;

public:
	// CListCtrl游戏服务器列表
	CListCtrl listServer;

	// CListCtrl公告信息
	CListCtrl listNotice;

	// CComboBox公告翻页
	CComboBox cmbPage;

	// CDateTimeCtrl开始日期
	CDateTimeCtrl dtcStartDate;

	// CDateTimeCtrl结束日期
	CDateTimeCtrl dtcEndDate;

	// CDateTimeCtrl开始时间
	CDateTimeCtrl dtcStartTime;

	// CDateTimeCtrl结束时间
	CDateTimeCtrl dtcEndTime;

	// CheckBox立即发送
	CButton checkSendImme;

	// CComboBox公告状态
	CComboBox cmbStatus;

	// CEdit发送间隔
	CEdit txtInterval;

	// 指示对话框当前状态
	int dlgStatus;

	// 初始化对话框
	virtual BOOL OnInitDialog();

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 初始化显示字符
	void InitUI();

	// 自动改变大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 选择所有游戏服务器进行发送
	afx_msg void OnBnClickedCheckselectall();

	// 查看公告信息
	afx_msg void OnBnClickedBtnnoticeinfo();

	// 查看公告信息
	void NoticeInfo();

	// 翻页查看公告信息
	afx_msg void OnCbnSelchangeCmbpage();

	// 双击公告信息进行删除公告///maple add
	afx_msg void OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult);

	// 发送或编辑公告
	afx_msg void OnBnClickedBtnnotice();

	// 是否立即发送公告
	afx_msg void OnBnClickedCheckimme();

	// 发送公告
	void AddNotice();

	//编辑公告
	void EditNotice();

	//编辑公告
	void DelNotice();

	//返回要发送公告的游戏服务器列表
	CString ReturnServerIP();

	//返回要发送公告的游戏服务器名称列表
	CString ReturnServerName();

	//返回所有游戏服务器列表
	CString ReturnAllServerIP();

	//返回所有游戏服务器名称列表
	CString ReturnAllServerName();	

	void ReturnAllServerIP(char* allServerIP);
	// 重置信息
	afx_msg void OnBnClickedBtnreset();	

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击公告信息的列名进行排序
	afx_msg void OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnClose();

};
