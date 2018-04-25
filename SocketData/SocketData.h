#ifndef SOCKETDATA_H_
#define SOCKETDATA_H_

#include "CIni.h"
#include "PacketHead.h"

#include <afxtempl.h>

#include "Resource.h"

class __declspec(dllexport) CSocketData
{
public:
	CSocketData(void);
	CSocketData(int querynum,int tflvnum);
	~CSocketData(void);

private:
	//���ݰ��е����ݵ�Ԫ����Query������
	int alltflv,allquery,colTFLV;

	//��ǰTFLV��nIndex
	int tflvNum;

	//����TFLV��CList
	CList<CGlobalStruct::TFLV,CGlobalStruct::TFLV&> InnerList;

	//���͵�����
	unsigned char *lpDes;

public:		

	// ����Ҫ���͵�����
	unsigned char * getDes();

	// �������ݰ������ݵ�Ԫ��
	bool Create(int m_alltflv);

	// ��ʼ���������ݰ���������
	bool InitCreate(int querynum,int tflvnum);

	// �����������
	void AddQuery(void);

	// ������ݵ�Ԫ
	bool AddTFLV(CEnumCore::TagName tag, CEnumCore::TagFormat tagFormat, int length, unsigned char * lpdata);
	bool AddTFLV(CEnumCore::TagName tag, CEnumCore::TagFormat tagFormat, size_t length, unsigned char * lpdata);

	// ����Ҫ���͵����ݵ�Ԫ
	int MakeTLV(unsigned char * lpDes,CGlobalStruct::TFLV m_tflv);

	// �������ݰ�
	int EnBody(void);

	// �������յ�������
	BOOL DeBody(unsigned char* lpSou, int bodylength);

	// �������յ������ݲ���װ
	CGlobalStruct::TFLV DeMakeTLV(unsigned char * lpSou,int* m_length, int index, int* m_Judge);

	// ��ȡ���е�TFLV��Ŀ
	int getAllTFLV();

	// ��ȡ���е�Query��Ŀ
	int getQueryNum();

	// ��ȡ���е�����
	int getColTFLVNum();

	// �������ݵ�Ԫ��TagName�Ϳ�ʼ������ѯ���ݵ�Ԫ
	CGlobalStruct::TFLV getTLVByTag(CEnumCore::TagName tag,int beginIndex);
	
	// �������ݵ�Ԫ��������ѯ���ݵ�Ԫ
	CGlobalStruct::TFLV getTLVBynIndex(int nIndex);

	// �������ݵ�Ԫ���С��кŲ�ѯ���ݵ�Ԫ
	CGlobalStruct::TFLV getTLV(int nRow,int nCol);

	// �������ݵ�Ԫ���кź�������ѯ���ݵ�Ԫ
	CGlobalStruct::TFLV getTLVByName(int nRow,CEnumCore::TagName tag);

	// �������ݰ�
	bool Destroy(void);
};

#endif