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
	//数据包中的数据单元数和Query的行数
	int alltflv,allquery,colTFLV;

	//当前TFLV的nIndex
	int tflvNum;

	//保存TFLV的CList
	CList<CGlobalStruct::TFLV,CGlobalStruct::TFLV&> InnerList;

	//发送的数据
	unsigned char *lpDes;

public:		

	// 返回要发送的数据
	unsigned char * getDes();

	// 分配数据包的数据单元数
	bool Create(int m_alltflv);

	// 初始化分配数据包的行列数
	bool InitCreate(int querynum,int tflvnum);

	// 添加数据请求
	void AddQuery(void);

	// 添加数据单元
	bool AddTFLV(CEnumCore::TagName tag, CEnumCore::TagFormat tagFormat, int length, unsigned char * lpdata);
	bool AddTFLV(CEnumCore::TagName tag, CEnumCore::TagFormat tagFormat, size_t length, unsigned char * lpdata);

	// 构造要发送的数据单元
	int MakeTLV(unsigned char * lpDes,CGlobalStruct::TFLV m_tflv);

	// 加密数据包
	int EnBody(void);

	// 解析接收到的数据
	BOOL DeBody(unsigned char* lpSou, int bodylength);

	// 解析接收到的数据并封装
	CGlobalStruct::TFLV DeMakeTLV(unsigned char * lpSou,int* m_length, int index, int* m_Judge);

	// 获取所有的TFLV数目
	int getAllTFLV();

	// 获取所有的Query数目
	int getQueryNum();

	// 获取所有的列数
	int getColTFLVNum();

	// 利用数据单元的TagName和开始索引查询数据单元
	CGlobalStruct::TFLV getTLVByTag(CEnumCore::TagName tag,int beginIndex);
	
	// 利用数据单元的索引查询数据单元
	CGlobalStruct::TFLV getTLVBynIndex(int nIndex);

	// 利用数据单元的行、列号查询数据单元
	CGlobalStruct::TFLV getTLV(int nRow,int nCol);

	// 利用数据单元的行号和索引查询数据单元
	CGlobalStruct::TFLV getTLVByName(int nRow,CEnumCore::TagName tag);

	// 销毁数据包
	bool Destroy(void);
};

#endif