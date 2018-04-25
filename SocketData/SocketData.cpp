#include "StdAfx.h"
#include "SocketData.h"
#include ".\socketdata.h"

#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")

CSocketData::CSocketData(void)
: lpDes(NULL)
{
}

CSocketData::CSocketData(int querynum,int tflvnum)
{
	allquery = querynum;
	colTFLV = tflvnum;
	alltflv = querynum*tflvnum;
	lpDes=NULL;
	
}
CSocketData::~CSocketData(void)
{
	//Destroy();
}

// 返回要发送的数据
unsigned char * CSocketData::getDes()
{
	return lpDes;
}

// 分配数据包的数据单元数
bool CSocketData::Create(int m_alltflv)
{
	Destroy();
	alltflv = m_alltflv;
	return false;
}

// 初始化分配数据包的行列数
bool CSocketData::InitCreate(int querynum,int tflvnum)//querynum是行数,tflvnum是列数
{
	Destroy();
	allquery=querynum;//数据单元的行数
	colTFLV = tflvnum;
	alltflv=querynum*tflvnum;//所有的数据单元数
	tflvNum = 0;
	lpDes=new unsigned char[alltflv * sizeof(CGlobalStruct::TFLV)];
	return false;
}

// 添加数据单元
bool CSocketData::AddTFLV(CEnumCore::TagName tag, CEnumCore::TagFormat tagFormat, int length, unsigned char * lpdata)
{	
	CGlobalStruct::TFLV m_tflv;
	int i=0,j=0;
	for(i=0;i<allquery;i++)
	{
		for(j=0;j<colTFLV;j++)
		{
			if(i*colTFLV+j+1 > tflvNum)
			{
				m_tflv.nIndex=i*colTFLV+j+1;//数据单元的索引号
				m_tflv.m_tagName=tag;//数据单元的tagName
				m_tflv.m_tagFormat=tagFormat;//数据单元的tagFormat
				m_tflv.m_tvlength=length;//数据单元的字节数
				wsprintf((LPSTR)&m_tflv.lpdata,"%s",lpdata);//将数据单元保存到数据包中
				InnerList.AddTail(m_tflv);
				tflvNum++;
				return TRUE;	
			}
		}
	}
	return FALSE;	
}
bool CSocketData::AddTFLV(CEnumCore::TagName tag, CEnumCore::TagFormat tagFormat, size_t length, unsigned char * lpdata)
{
	CGlobalStruct::TFLV m_tflv;
	int i=0,j=0;
	for(i=0;i<allquery;i++)
	{
		for(j=0;j<colTFLV;j++)
		{
			if(i*colTFLV+j+1 > tflvNum)
			{
				m_tflv.nIndex=i*colTFLV+j+1;//数据单元的索引号
				m_tflv.m_tagName=tag;//数据单元的tagName
				m_tflv.m_tagFormat=tagFormat;//数据单元的tagFormat
				m_tflv.m_tvlength= (unsigned int)length;//数据单元的字节数
				wsprintf((LPSTR)&m_tflv.lpdata,"%s",lpdata);//将数据单元保存到数据包中
				InnerList.AddTail(m_tflv);
				tflvNum++;
				return TRUE;	
			}
		}
	}
	return FALSE;	
}

// 构造数据单元
int CSocketData::MakeTLV(unsigned char * lpDes, CGlobalStruct::TFLV m_tflv)
{
	int length=0;
	int tmpint=0;
	memcpy(lpDes,(short int  *)&m_tflv.m_tagName,sizeof(short int));
	memcpy(lpDes+sizeof(short int),(short int  *)&m_tflv.m_tagFormat,sizeof(short int));
	memcpy(lpDes+sizeof(short int)+sizeof(short int),(int *)&m_tflv.m_tvlength,sizeof(unsigned int));
	switch(m_tflv.m_tagFormat)
	{
	case CEnumCore::TagFormat::TLV_INTEGER://添加数据类型的数据单元
		{
				tmpint=StrToInt((LPCSTR)m_tflv.lpdata);
				memcpy(lpDes+sizeof(short int)+sizeof(short int)+sizeof(unsigned int),(int *)&tmpint,4);
				length=4+sizeof(short int)+sizeof(unsigned int)+sizeof(short int);
		}
		break;
	case CEnumCore::TagFormat::TLV_STRING://添加string类型的数据单元
		{
			memcpy(lpDes+sizeof(short int)+sizeof(short int)+sizeof(unsigned int),m_tflv.lpdata,m_tflv.m_tvlength);
			length=m_tflv.m_tvlength+sizeof(short int)+sizeof(unsigned int)+sizeof(short int);
		}
		break;
	default:
		{
			memcpy(lpDes+sizeof(short int)+sizeof(short int)+sizeof(unsigned int),m_tflv.lpdata,m_tflv.m_tvlength);
			length=m_tflv.m_tvlength+sizeof(short int)+sizeof(unsigned int)+sizeof(short int);
		}
		break;
	}
	return length;
}

// 加密数据包
int CSocketData::EnBody(void)
{
	int length=0;
	POSITION pos = InnerList.GetHeadPosition();
	for (int i=0;i < InnerList.GetCount();i++)
	{
		length=length+MakeTLV(lpDes+length,InnerList.GetNext(pos));//数据包的字节数
	}
	return length;
}

// 解析接收到的数据
BOOL CSocketData::DeBody(unsigned char* lpSou, int bodylength)
{
	int lengthdata=0;
	int i=0,j=0;
	int mJudge = 0;

	int actlength=0;
	while(lengthdata<bodylength)
	{
		i++;
		InnerList.AddTail(DeMakeTLV(lpSou+lengthdata, &actlength, i, &mJudge));
		if(mJudge == 2)
		{
			return FALSE;
		}
		else if(mJudge == 1)
		{
		    lengthdata=lengthdata+actlength;
		}
	}
	alltflv=i;

	////////////////////////////////////////一维变成二维/////////////////////////////////
	CGlobalStruct::TFLV m_basetflv;
	CGlobalStruct::TFLV m_Nexttflv;

	POSITION pos = InnerList.GetHeadPosition();
	m_basetflv = InnerList.GetAt(pos);
	m_Nexttflv = getTLVByTag(m_basetflv.m_tagName,1);
	if(m_Nexttflv.nIndex!=0)
	{
		colTFLV = m_Nexttflv.nIndex-1;
	}
	else
	{
		colTFLV = alltflv;		
	}
	allquery = alltflv/colTFLV;

	return TRUE;
}

// 解析接收到的数据并封装
CGlobalStruct::TFLV CSocketData::DeMakeTLV(unsigned char * lpSou,int* m_length, int index, int* m_Judge)
{
	CGlobalStruct::TFLV	m_tflv;
	try
	{		
		unsigned char tmptag[2];
		memcpy(&tmptag,lpSou,2);
		m_tflv.m_tagName=*(short int *)&tmptag;
		unsigned char tmpformat[2];
		memcpy(&tmpformat,lpSou+2,2);
		m_tflv.m_tagFormat=*(short int *)&tmpformat;

		unsigned char tmplength[4];
		memcpy(&tmplength,lpSou+2+2,4);
		m_tflv.m_tvlength=*(int *)&tmplength;

		if(m_tflv.m_tvlength > 2048)
		{
			*m_Judge = 2;
		    CGlobalStruct::TFLV	tmp_tflv;
		    return tmp_tflv;
		}

		unsigned char tmpint[4];
		int actlength=0;
		switch(m_tflv.m_tagFormat)
		{
		case CEnumCore::TagFormat::TLV_INTEGER:
			{
				memcpy(&tmpint,lpSou+2+2+4,4);
				actlength=wsprintf((LPSTR)m_tflv.lpdata,"%i",*(int *)&tmpint);
				m_tflv.lpdata[actlength]='\0';
				*m_length=8+4;
			}
			break;
		case CEnumCore::TagFormat::TLV_STRING:
			{
				memcpy(m_tflv.lpdata,lpSou+2+2+4,m_tflv.m_tvlength);
				m_tflv.lpdata[m_tflv.m_tvlength]='\0';
				*m_length=8+m_tflv.m_tvlength;
			}
			break;
		default:
			{
				memcpy(m_tflv.lpdata,lpSou+2+2+4,m_tflv.m_tvlength);
				m_tflv.lpdata[m_tflv.m_tvlength]='\0';
				*m_length=8+m_tflv.m_tvlength;
			}
			break;
		}
		m_tflv.nIndex = index;
	}
	catch(...)
	{
		*m_Judge = 2;
		CGlobalStruct::TFLV	tmp_tflv;
		return tmp_tflv;
	}
	*m_Judge = 1;
	return m_tflv;
}

// 获取所有的TFLV数目
int CSocketData::getAllTFLV()
{
	return alltflv;
}

// 获取所有的Query数目
int CSocketData::getQueryNum()
{
	return allquery;
}

// 获取所有的列数
int CSocketData::getColTFLVNum()
{
	return colTFLV;
}

// 利用数据单元的TagName和开始索引查询数据单元
CGlobalStruct::TFLV CSocketData::getTLVByTag(CEnumCore::TagName tag,int beginIndex)
{
	CGlobalStruct::TFLV m_basetflv;
	CGlobalStruct::TFLV m_tflv;
	m_tflv.nIndex=0;
	POSITION pos = InnerList.GetHeadPosition();
	for(int i=0;i<beginIndex;i++)
	{
		m_basetflv = InnerList.GetNext(pos);
	}
	for(int i=beginIndex;i<alltflv;i++)
	{
	    m_basetflv = InnerList.GetNext(pos);
		if(m_basetflv.m_tagName == tag)
		{
			m_tflv = m_basetflv;
			break;
		}
	}
	return m_tflv;
}

// 利用数据单元的索引查询数据单元
CGlobalStruct::TFLV CSocketData::getTLVBynIndex(int nIndex)
{
	CGlobalStruct::TFLV m_basetflv;
	CGlobalStruct::TFLV m_tflv;
	m_tflv.nIndex=0;
	POSITION pos = InnerList.GetHeadPosition();
	for(int i=0;i<alltflv;i++)
	{
		m_basetflv = InnerList.GetNext(pos);
		if(m_basetflv.nIndex==(UINT)nIndex)
		{
			m_tflv = m_basetflv;
			break;
		}
	}
	return m_tflv;
}

// 利用数据单元的行、列号查询数据单元
CGlobalStruct::TFLV CSocketData::getTLV(int nRow,int nCol)
{
	CGlobalStruct::TFLV m_basetflv;
	CGlobalStruct::TFLV m_tflv;
	m_tflv.nIndex=0;
	int index = (nRow-1)*colTFLV + nCol;
	POSITION pos = InnerList.GetHeadPosition();
	for(int i=0;i<InnerList.GetCount();i++)
	{
		m_basetflv = InnerList.GetNext(pos);
		if(m_basetflv.nIndex==(UINT)index)
		{
			m_tflv = m_basetflv;
			break;
		}
	}
	return m_tflv;
}

// 利用数据单元的行号和索引查询数据单元
CGlobalStruct::TFLV CSocketData::getTLVByName(int nRow,CEnumCore::TagName tag)
{
	CGlobalStruct::TFLV m_basetflv;
	CGlobalStruct::TFLV m_tflv;
	m_tflv.nIndex=0;
	POSITION pos = InnerList.GetHeadPosition();
	for(int i=0;i<(nRow-1)*colTFLV;i++)
	{
		m_basetflv = InnerList.GetNext(pos);
	}
	for(int i=(nRow-1)*colTFLV;i < nRow*colTFLV;i++)
	{
		m_basetflv = InnerList.GetNext(pos);
		if(m_basetflv.m_tagName == tag)
		{
			m_tflv = m_basetflv;
			break;
		}
	}
	return m_tflv;
}

// 销毁数据包
bool CSocketData::Destroy(void)
{
	if(!InnerList.IsEmpty())
	{
	    InnerList.RemoveAll();
	}
	if(lpDes!=NULL)
	{
		delete[] lpDes;
		lpDes=NULL;
	}
	return false;
}

