#ifndef OPERATIONAU_H_
#define OPERATIONAU_H_

#include <afxtempl.h>

#include "..\\Event\\Event.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

#include "resource.h"		// 主符号

#define DF_DEFAULT_LENGTH 2048

class OperationPAL
{
private:

	//保存从ini文件里面读取到的数据
	char strValue[DF_DEFAULT_LENGTH];

	//用于发送数据
	CMSocket selfSocket;

	//用于保存要发送的数据
	CPacketHead packethead;

	//用于保存要发送的数据的长度
	int packetLength;

public:
	OperationPAL();
	~OperationPAL();

	//用于设定是否在发送
	int* intPAL;

	//设置SOCKET
	void initSocket(SOCKET m_Socket);

	// 获取游戏服务器列表
	bool GetServerList();

	//发送查询请求
	bool SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey);

	//发送查询日志请求
	bool SendLogQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey);

	//再次发送同样的Query
	bool SendSameQuery();

	// 构造复选框
	bool BuildCombox(CSocketData* socketData,CComboBox* cmbSelect);

	// 构造复选框,不设置初始值
	bool BuildComboxs(CSocketData* socketData,CComboBox* cmbSelect);

	bool BuildMapCombox(CSocketData* socketData,CComboBox* cmbSelect);

	// 构造ListBox
	bool BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount);

	// 读取ini文件里面的值
	CString ReadValue(CString strSection,CString strKey);

	// 读取ini文件里面的数字
	int ReadIntValue(CString strSection,CString strKey);

	//通过行号和列名得到相应的值
	CString GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName);

	//自己定义的复制函数
	void CopyListInfo(CListCtrl* m_listCtrl);

	//自己定义的排序函数
	void SortListInfo(CListCtrl* m_listCtrl, NMHDR *pNMHDR, LRESULT *pResult);

	// TagName转换成CString类型
	char* tagToStr(CEnumCore::TagName tag);

	// 显示操作结果
	void ShowResult(CString result);

	// 获取公会等级ID
	int GuildLevelStrToInt(CString m_str);

	// 获取公会等级名称
	CString GuildLevelIntToStr(int iLevel);
};
#endif