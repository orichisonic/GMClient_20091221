#ifndef OPERATIONGM_H_
#define OPERATIONGM_H_

#pragma warning(disable: 4996)

#include "..\\Event\\Event.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

#include "resource.h"		// ������

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
	//�����ini�ļ������ȡ��������
	char strValue[DF_DEFAULT_LENGTH];

	//���ڷ�������
	CMSocket selfSocket;

	//���ڱ���Ҫ���͵�����
	CPacketHead packethead;

	//���ڱ���Ҫ���͵����ݵĳ���
	int packetLength;

public:
	OperationGM();
	~OperationGM();

	//�����趨�Ƿ��ڷ���
	int* intGM;

	//����SOCKET
	void initSocket(SOCKET m_Socket);

	// ����Query
	bool SendQuery(unsigned char* sendData,int allLength,CEnumCore::Msg_Category m_category,CEnumCore::ServiceKey m_ServiceKey);

	//�ٴη���ͬ����Query
	bool SendSameQuery();

	// ���츴ѡ��
	bool BuildCombox(CSocketData* psocketData,CComboBox* cmbSelect);

	// ���츴ѡ��
	bool BuildComboxs(CSocketData* psocketData,CComboBox* cmbSelect,int bItem,CEnumCore::TagName m_TegName);

	//�����û��б�
	bool BuildComboxUser(CSocketData* psocketData,CComboBox* cmbSelect);

	//������Ϸ�б�
	bool BuildComboxGame(CSocketData* psocketData,CComboBox* cmbSelect);

	//��������б�
	bool BuildComboxCity(CSocketData* psocketData,CComboBox* cmbSelect);

	// ����ListBox
	bool BuildDataTable(CSocketData* psocketData,CListCtrl* listCtrlS,int* pageCount);

	// ��ȡini�ļ������ֵ
	CString ReadValue(CString strSection,CString strKey);

	// ��ȡini�ļ����������
	int ReadIntValue(CString strSection,CString strKey);

	//ͨ���кź������õ���Ӧ��ֵ
	CString GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName);

	// TagNameת����CString����
	char* tagToStr(CEnumCore::TagName tag);

	// ��ʾ�������
	void ShowResult(CString result);

	//�Լ�����ĸ��ƺ���
	void CopyListInfo(CListCtrl* m_listCtrl);

	//�Լ������������
	void SortListInfo(CListCtrl* m_listCtrl, NMHDR *pNMHDR, LRESULT *pResult);

	//��ȡODBC����(Excel,Sql Server,...)
	CString GetExcelDriver(char * driverName);

	//��CListCtrl�е����ݵ�����Excel
	bool ExportCListCtrlToExcel(CListCtrl* pList, CString sExcelFile, CString sSheetName);

	//��Excel�ļ����뵽CListCtrl
	bool ImportCListCtrlFromExcel(CListCtrl* pList, CString sExcelFile, CString sSheetName);

	//��ʾ���ص�vip�ʺ�
	bool ShowVIP(CSocketData* pCSock, CListCtrl* plist);

	void ConsoleLog(CString msg);
	

};
#endif