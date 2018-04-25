#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSDORateSet 对话框

class CSDORateSet : public CDialog
{
	DECLARE_DYNAMIC(CSDORateSet)

public:
	CSDORateSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSDORateSet();

// 对话框数据
	enum { IDD = IDD_DLGRATESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;
	CMap<int,int,int,int> ItemCodeList;//道具列表
	CMap<int,int,int,int> ItemCodeListF;//女性道具列表

	// 判断是否需要翻页
	bool pageInfo;

	// 游戏服务器Name
	CString ServerName;

	// 游戏服务器IP
	CString ServerIP;

	//道具名称
	CString ItemName;

	//输入的玩家帐号和角色名
//	CString Account, Name;

	// 获得的玩家帐号和角色名
//	CString UserAccount, UserName;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;

	int iType;//大类值

	int iSort;//小类值

	//比率值
	int iRate;

	//使用次数
	int iUseTimes;

	//使用期限
	int iUseLimit;

	int iItemCode,iItemCode1,iItemCode2;

	//道具名称1，道具名称2
	CString ItemName1,ItemName2;
public:
	// CGroupBox搜索条件
	CStatic GrpSearch;

	// CComboBox游戏服务器
	CComboBox cmbServer;

	// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	//玩家信息翻页组合框
	CStatic GrpPage;

	// CListCtrl结果显示
	CListCtrl listItem;

	//翻页组合框
	CComboBox cmbPage;

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

	// 显示角色资料信息
	void ShowUserInfo();

	// 显示其它信息
	void ShowOtherInfo();

	// 单击道具列表保存当前行号
	afx_msg void OnNMClickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	// 双击道具列表删除
	afx_msg void OnNMDblclkListitem(NMHDR *pNMHDR, LRESULT *pResult);

	// 切换选项卡进行查询
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//处理快捷键响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//单击结果信息的列名进行排序
	afx_msg void OnLvnColumnclickListitem(NMHDR *pNMHDR, LRESULT *pResult);

	//查询道具信息
	afx_msg void OnBnClickedSearch();

	//添加或者编辑道具
	afx_msg void OnBnClickedBtok();

	//道具类别导入数据
	void ItemType();

	//切换大类
	afx_msg void OnCbnSelchangeCmbbigtypem();

	//切换小类
	afx_msg void OnCbnSelchangeCmbsmalltypem();

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);
	CComboBox cmbBigTypeM;
	CComboBox cmbSmallTypeM;
	CComboBox cmbGoods;

	//查询男性道具
	void MaleItem();

	//增加比率
	void AddRate();

	//编辑比率
	void UpdateRate();

	//性别
	CComboBox cmbSex;

	//删除比率
	void DelRate();
};
