#ifndef OPERATIONGM_H_
#define OPERATIONGM_H_

#pragma warning(disable: 4996)

#include "..\\Event\\Event.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

#include "resource.h"		// 主符号

#include "odbcinst.h"
#include "afxdb.h"
#include "comdef.h"

#include <iostream>
using std::cout;
using std::endl;

#define DF_DEFAULT_LENGTH 2048

class OperationGM
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
	OperationGM();
	~OperationGM();

	//用于设定是否在发送
	int* intGM;

	//设置SOCKET
	void initSocket(SOCKET m_Socket);

	// 发送Query
	bool SendQuery(unsigned char* sendData,int allLength,CEnumCore::Msg_Category m_category,CEnumCore::ServiceKey m_ServiceKey);

	//再次发送同样的Query
	bool SendSameQuery();

	// 构造复选框
	bool BuildCombox(CSocketData* psocketData,CComboBox* cmbSelect);

	// 构造复选框
	bool BuildComboxs(CSocketData* psocketData,CComboBox* cmbSelect,int bItem,CEnumCore::TagName m_TegName);

	//构造用户列表
	bool BuildComboxUser(CSocketData* psocketData,CComboBox* cmbSelect);

	//构造游戏列表
	bool BuildComboxGame(CSocketData* psocketData,CComboBox* cmbSelect);

	//构造大区列表
	bool BuildComboxCity(CSocketData* psocketData,CComboBox* cmbSelect);

	// 构造ListBox
	bool BuildDataTable(CSocketData* psocketData,CListCtrl* listCtrlS,int* pageCount);

	// 读取ini文件里面的值
	CString ReadValue(CString strSection,CString strKey);

	// 读取ini文件里面的数字
	int ReadIntValue(CString strSection,CString strKey);

	//通过行号和列名得到相应的值
	CString GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName);

	// TagName转换成CString类型
	char* tagToStr(CEnumCore::TagName tag);

	// 显示操作结果
	void ShowResult(CString result);

	//自己定义的复制函数
	void CopyListInfo(CListCtrl* m_listCtrl);

	//自己定义的排序函数
	void SortListInfo(CListCtrl* m_listCtrl, NMHDR *pNMHDR, LRESULT *pResult);

	//获取ODBC驱动(Excel,Sql Server,...)
	CString GetExcelDriver(char * driverName);

	//将CListCtrl中的数据导出至Excel
	bool ExportCListCtrlToExcel(CListCtrl* pList, CString sExcelFile, CString sSheetName);

	//将Excel文件导入到CListCtrl
	bool ImportCListCtrlFromExcel(CListCtrl* pList, CString sExcelFile, CString sSheetName);

	//显示返回的vip帐号
	bool ShowVIP(CSocketData* pCSock, CListCtrl* plist);

	void ConsoleLog(CString msg);
	

};
#endif