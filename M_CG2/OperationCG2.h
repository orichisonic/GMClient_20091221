#ifndef OPERATIONCG2_H_
#define OPERATIONCG2_H_

#include <afxtempl.h>

#include "..\\Event\\Event.h"
#pragma comment(lib,"..\\Event\\Debug\\Event.lib")

#include "resource.h"		// ������


#define DF_DEFAULT_LENGTH 2048

class OperationCG2
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
	OperationCG2();
	~OperationCG2();

	//�����趨�Ƿ��ڷ���
	int* intCG2;

	//����SOCKET
	void initSocket(SOCKET m_Socket);

	// ��ȡ��Ϸ�������б�
	bool GetServerList();

	//���Ͳ�ѯ����
	bool SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey);

	//ͨ���кź������õ���Ӧ��ֵ
	CString GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName);

	// ���츴ѡ��
	bool BuildCombox(CSocketData* socketData,CComboBox* cmbSelect);

	//����ְҵ��ѡ��
	bool BuildJobCombox(CSocketData* socketData,CComboBox* cmbSelect);

	//��������
	bool BuildPetCombox(CSocketData* socketData,CComboBox* cmbSelect);

	// ����ListBox
	bool BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount);

	// ��ȡini�ļ������ֵ
	CString ReadValue(CString strSection,CString strKey);

	// ��ȡini�ļ����������
	int ReadIntValue(CString strSection,CString strKey);

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