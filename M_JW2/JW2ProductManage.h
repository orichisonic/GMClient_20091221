#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CJW2ProductManage 对话框

class CJW2ProductManage : public CDialog
{
	DECLARE_DYNAMIC(CJW2ProductManage)

public:
	CJW2ProductManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJW2ProductManage();

// 对话框数据
	enum { IDD = IDD_DLGPRODUCTMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击公告列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 相应的玩家信息
	CMap<int,int,int,int> UserList;

	// 判断是否需要翻页
	bool pageInfo;

	// 发送还是编辑公告
	bool addOrEdit;

	// 是否在所有大区发送公告
	bool AllServer;

	// 服务器IP
	CString ServerIP;

	// 权限ID
	int ProductID;

	//服务器列表宽度
	int listRWidth;

	//公告内容高度
	int contentLength;

	//翻页内容高度
	int gPageLength;

public:
	// CListCtrl游戏服务器列表
	CListCtrl listResult;

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

	// 选择所有游戏服务器进行发送
//	afx_msg void OnBnClickedCheckselectall();

	// 查看公告信息
//////	afx_msg void OnBnClickedBtnnoticeinfo();

	// 查看公告信息
//////	void NoticeInfo();

	// 翻页查看公告信息
/////	afx_msg void OnCbnSelchangeCmbuipage();

	// 双击公告信息进行编辑
/////	afx_msg void OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult);	

	// 增加权限
	afx_msg void OnBnClickedBtnnotice();	

	// 是否立即发送公告
/////	afx_msg void OnBnClickedCheckimme();

	// 发送公告
/////	void AddNotice();

	//编辑公告
//////	void EditNotice();

	//返回要发送公告的游戏服务器列表
	CString ReturnServerIP();

	// 重置信息
	afx_msg void OnBnClickedBtnreset();	

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//单击公告信息的列名进行排序
	afx_msg void OnLvnColumnclickListnotice(NMHDR *pNMHDR, LRESULT *pResult);

	// 关闭对话框
	afx_msg void OnClose();		

	//获取所有的用户名称
	void QueryUserList();
	CComboBox cmbRealName;
	afx_msg void OnBnClickedButton3();
	CListCtrl listItem;
	afx_msg void OnBnClickedButton1();
	CListCtrl listItemResult;
	afx_msg void OnBnClickedButton2();

	int addItem;
	int delItem;
	CString selectItemID;//防止重复添加

	int MulAddItem[100];


	void MulInsertListCtrl(int nSel);
	//int ii;
	//maple add

	int CountItemPrice;//总额

	afx_msg void OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);


/////////	CComboBox cmbGM;


	CButton m_ckServer;//全选checkBox
	afx_msg void OnBnClickedCheckselectall();

	//查看权限
	afx_msg void OnBnClickedBtnnoticeinfo();

	//双击删除权限
	afx_msg void OnNMDblclkListnotice(NMHDR *pNMHDR, LRESULT *pResult);

	void DelProductManager();
	//翻页查看权限
	afx_msg void OnCbnSelchangeCmbuipage();

	//验证权限
	afx_msg void OnBnClickedBtnvalidate();
};
