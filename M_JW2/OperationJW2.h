#ifndef OperationJW2_H_
#define OperationJW2_H_

#include <afxtempl.h>


#include "..\\Event\\Event.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

#include "resource.h"		// ������


#define DF_DEFAULT_LENGTH 2048

class OperationJW2
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
	OperationJW2();
	~OperationJW2();

	//�����趨�Ƿ��ڷ���
	int* intJW2;

	//����SOCKET
	void initSocket(SOCKET m_Socket);

	// ��ȡ��Ϸ�������б�
	bool GetServerList();

	//���Ͳ�ѯ����
	bool SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey);

	//���Ͳ�ѯ����
	bool SendQuery(unsigned char* sendData,int allLength,CEnumCore::Msg_Category m_category,CEnumCore::ServiceKey m_ServiceKey);


	//�ٴη���ͬ����Query
	bool SendSameQuery();
	// ���츴ѡ��
	bool BuildCombox(CSocketData* socketData,CComboBox* cmbSelect);

	// �����û��б�
	bool BuildComboxUser(CSocketData* psocketData,CComboBox* cmbSelect);

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
};
#endif