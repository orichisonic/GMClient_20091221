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

// ����Ҫ���͵�����
unsigned char * CSocketData::getDes()
{
	return lpDes;
}

// �������ݰ������ݵ�Ԫ��
bool CSocketData::Create(int m_alltflv)
{
	Destroy();
	alltflv = m_alltflv;
	return false;
}

// ��ʼ���������ݰ���������
bool CSocketData::InitCreate(int querynum,int tflvnum)//querynum������,tflvnum������
{
	Destroy();
	allquery=querynum;//���ݵ�Ԫ������
	colTFLV = tflvnum;
	alltflv=querynum*tflvnum;//���е����ݵ�Ԫ��
	tflvNum = 0;
	lpDes=new unsigned char[alltflv * sizeof(CGlobalStruct::TFLV)];
	return false;
}

// ������ݵ�Ԫ
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
				m_tflv.nIndex=i*colTFLV+j+1;//���ݵ�Ԫ��������
				m_tflv.m_tagName=tag;//���ݵ�Ԫ��tagName
				m_tflv.m_tagFormat=tagFormat;//���ݵ�Ԫ��tagFormat
				m_tflv.m_tvlength=length;//���ݵ�Ԫ���ֽ���
				wsprintf((LPSTR)&m_tflv.lpdata,"%s",lpdata);//�����ݵ�Ԫ���浽���ݰ���
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
				m_tflv.nIndex=i*colTFLV+j+1;//���ݵ�Ԫ��������
				m_tflv.m_tagName=tag;//���ݵ�Ԫ��tagName
				m_tflv.m_tagFormat=tagFormat;//���ݵ�Ԫ��tagFormat
				m_tflv.m_tvlength= (unsigned int)length;//���ݵ�Ԫ���ֽ���
				wsprintf((LPSTR)&m_tflv.lpdata,"%s",lpdata);//�����ݵ�Ԫ���浽���ݰ���
				InnerList.AddTail(m_tflv);
				tflvNum++;
				return TRUE;	
			}
		}
	}
	return FALSE;	
}

// �������ݵ�Ԫ
int CSocketData::MakeTLV(unsigned char * lpDes, CGlobalStruct::TFLV m_tflv)
{
	int length=0;
	int tmpint=0;
	memcpy(lpDes,(short int  *)&m_tflv.m_tagName,sizeof(short int));
	memcpy(lpDes+sizeof(short int),(short int  *)&m_tflv.m_tagFormat,sizeof(short int));
	memcpy(lpDes+sizeof(short int)+sizeof(short int),(int *)&m_tflv.m_tvlength,sizeof(unsigned int));
	switch(m_tflv.m_tagFormat)
	{
	case CEnumCore::TagFormat::TLV_INTEGER://����������͵����ݵ�Ԫ
		{
				tmpint=StrToInt((LPCSTR)m_tflv.lpdata);
				memcpy(lpDes+sizeof(short int)+sizeof(short int)+sizeof(unsigned int),(int *)&tmpint,4);
				length=4+sizeof(short int)+sizeof(unsigned int)+sizeof(short int);
		}
		break;
	case CEnumCore::TagFormat::TLV_STRING://���string���͵����ݵ�Ԫ
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

// �������ݰ�
int CSocketData::EnBody(void)
{
	int length=0;
	POSITION pos = InnerList.GetHeadPosition();
	for (int i=0;i < InnerList.GetCount();i++)
	{
		length=length+MakeTLV(lpDes+length,InnerList.GetNext(pos));//���ݰ����ֽ���
	}
	return length;
}

// �������յ�������
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

	////////////////////////////////////////һά��ɶ�ά/////////////////////////////////
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

// �������յ������ݲ���װ
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

// ��ȡ���е�TFLV��Ŀ
int CSocketData::getAllTFLV()
{
	return alltflv;
}

// ��ȡ���е�Query��Ŀ
int CSocketData::getQueryNum()
{
	return allquery;
}

// ��ȡ���е�����
int CSocketData::getColTFLVNum()
{
	return colTFLV;
}

// �������ݵ�Ԫ��TagName�Ϳ�ʼ������ѯ���ݵ�Ԫ
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

// �������ݵ�Ԫ��������ѯ���ݵ�Ԫ
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

// �������ݵ�Ԫ���С��кŲ�ѯ���ݵ�Ԫ
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

// �������ݵ�Ԫ���кź�������ѯ���ݵ�Ԫ
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

// �������ݰ�
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

