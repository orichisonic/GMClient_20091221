#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCG2UpdateSkill 对话框
#include "OperationCG2.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

class CCG2UpdateSkill : public CDialog
{
	DECLARE_DYNCREATE(CCG2UpdateSkill)

public:
	CCG2UpdateSkill(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCG2UpdateSkill();


// 对话框数据
	enum { IDD = IDD_DLGUPDATESKILL};//, IDH = IDR_HTML_CG2UPDATESKILL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

	public:
	// 初始化显示字符
	void InitUI();

	private:
	// 单击用户列表得到行号
	int nItem;

	// 所有服务器信息
	CMap<int,int,CString,CString> ServerList;

	// 判断是否需要翻页
	bool pageInfo;

	// 判断用户列表是否需要翻页
	bool pageUInfo;

	// 游戏服务器IP
	CString ServerIP;

	// 玩家ID
	CString UserID;

	// 输入的玩家帐号
	CString UserName;

	// 输入的玩家昵称
	CString UserNick;

	//玩家角色技能名称
	CString UserSkill;
	
	//玩家角色技能等级
	int UserSkillLevel;

	//玩家技能ID
	CString SkillID;

	//玩家角色号
	int iCharNo;

	//各个控件的高度
	int grpHeight, tbcHeight,grpPHeight;
public:
	//游戏服务器组合框
	CComboBox cmbServer;

	//翻页组合框
	CComboBox cmbPage;

	//显示列表框
	CListCtrl listUser;

	//搜索容器
	CStatic GrpSearch;

	//翻页容器
	CStatic GrpPage;

	// 指示对话框当前状态
	int dlgStatus;

	//初始化对话框
	virtual BOOL OnInitDialog();

	//// CTabCtrl选项卡控制
	CTabCtrl tbcResult;

	//关闭对话框
	afx_msg void OnClose();
	afx_msg void OnBnClickedUicancel();

	//自动调节大小
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//设置背景颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 接收返回信息
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	void UserInfo();//玩家资料信息
	afx_msg void OnBnClickedUisearch();

	//新技能等级
	CComboBox cmbNewLevel;

	//切换tabCtrl
	afx_msg void OnTcnSelchangeTabuiresult(NMHDR *pNMHDR, LRESULT *pResult);

	//单击玩家资料信息列表框
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//双击玩家资料信息列表框
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//技能信息列表框
	CListCtrl listSkill;

	//技能信息翻页组合框
	CComboBox cmbSkillPage;

	//技能等级数初始化
	void SetLevel();


	//单击技能信息列表框
	afx_msg void OnNMClickListskillinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//双击技能信息列表框
	afx_msg void OnNMDblclkListskillinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//技能信息查询
	void SkillInfo();

	//修改技能等级
	afx_msg void OnBnClickedBtupdate();

	//重置修改技能等级
	afx_msg void OnBnClickedBtreset();

	//添加技能信息
	afx_msg void OnBnClickedBtaddskill();

	//重置添加技能信息
	afx_msg void OnBnClickedBtresetskill();

	//查询技能类别
	void SkillType();

	//技能类型组合框
	CComboBox cmbSkillType;

	//技能名称组合框
	CComboBox cmbSkillName;

	//技能名称查询
	afx_msg void OnCbnSelchangeCmbskilltype();



};
