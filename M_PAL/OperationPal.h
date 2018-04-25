#ifndef OPERATIONAU_H_
#define OPERATIONAU_H_

#include <afxtempl.h>

#include "..\\Event\\Event.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

#include "resource.h"		// ������

#define DF_DEFAULT_LENGTH 2048

class OperationPAL
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
	OperationPAL();
	~OperationPAL();

	//�����趨�Ƿ��ڷ���
	int* intPAL;

	//����SOCKET
	void initSocket(SOCKET m_Socket);

	// ��ȡ��Ϸ�������б�
	bool GetServerList();

	//���Ͳ�ѯ����
	bool SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey);

	//���Ͳ�ѯ��־����
	bool SendLogQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey);

	//�ٴη���ͬ����Query
	bool SendSameQuery();

	// ���츴ѡ��
	bool BuildCombox(CSocketData* socketData,CComboBox* cmbSelect);

	// ���츴ѡ��,�����ó�ʼֵ
	bool BuildComboxs(CSocketData* socketData,CComboBox* cmbSelect);

	bool BuildMapCombox(CSocketData* socketData,CComboBox* cmbSelect);

	// ����ListBox
	bool BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount);

	// ��ȡini�ļ������ֵ
	CString ReadValue(CString strSection,CString strKey);

	// ��ȡini�ļ����������
	int ReadIntValue(CString strSection,CString strKey);

	//ͨ���кź������õ���Ӧ��ֵ
	CString GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName);

	//�Լ�����ĸ��ƺ���
	void CopyListInfo(CListCtrl* m_listCtrl);

	//�Լ������������
	void SortListInfo(CListCtrl* m_listCtrl, NMHDR *pNMHDR, LRESULT *pResult);

	// TagNameת����CString����
	char* tagToStr(CEnumCore::TagName tag);

	// ��ʾ�������
	void ShowResult(CString result);

	// ��ȡ����ȼ�ID
	int GuildLevelStrToInt(CString m_str);

	// ��ȡ����ȼ�����
	CString GuildLevelIntToStr(int iLevel);
};
#endif