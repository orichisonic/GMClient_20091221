#include "StdAfx.h"
#include ".\packethead.h"
#include ".\Des.h"


CPacketHead::CPacketHead(void)
{
	lpDatabuf = NULL;
	lpsendbuf = NULL;
}

CPacketHead::~CPacketHead(void)
{
	Destroy();
}

// 构造数据包
int CPacketHead::AddPacketHead(unsigned char * lpDes, CGlobalStruct::PACKETHEAD m_packethead, unsigned char* lpSou)
{
	int length=0;
	memcpy(lpDes,(unsigned int*)&m_packethead.uId,4);
	memcpy(lpDes+4,(short int*)&m_packethead.m_msg_category,2);
	memcpy(lpDes+6,(short int*)&m_packethead.m_servicekey,2);

	memcpy(lpDes+8,m_packethead.SystemData,6);

	memcpy(lpDes+14,(short int*)&m_packethead.bodylen,4);

	memcpy(lpDes+18,lpSou,m_packethead.bodylen);
	length=m_packethead.bodylen+18;
	return length;
}

// 获取当前时间保存在数据包中
bool CPacketHead::GetNowTime(void)
{
	SYSTEMTIME str_systemtime;
	GetLocalTime(&str_systemtime);
	m_packethead.SystemData[0]=str_systemtime.wYear-1900;
	m_packethead.SystemData[1]=str_systemtime.wMonth;
	m_packethead.SystemData[2]=str_systemtime.wDay;
	m_packethead.SystemData[3]=str_systemtime.wHour;
	m_packethead.SystemData[4]=str_systemtime.wMinute;
	m_packethead.SystemData[5]=str_systemtime.wSecond;
	return false;
}

// 解析数据包
bool CPacketHead::DeHead(unsigned char * lpbuf,int length)
{
	unsigned char *lptmpsendbuf = new unsigned char[(length+20)*2];//加密前
	ZeroMemory(lptmpsendbuf, (length+20)*2);
	int nowlength=0;
	nowlength = DecodeMessage(lptmpsendbuf,length,lpbuf);

	if(nowlength <= 32)
	{
		return false;
	}

	//进行CRC32校验
	CCrc m_CRC(32, 0xA42F3D65, 0, 0xFFFFFFFF);
	unsigned char *lptmpbuf = new unsigned char[(length+20)*2];//加密前
	ZeroMemory(lptmpbuf, (length+20)*2);
	memcpy(lptmpbuf, lptmpsendbuf, nowlength - 8);
	nowlength = nowlength - 8;
	DWORD m_CRCNum = m_CRC.Calc(lptmpbuf, nowlength);
	DWORD m_SRCNum = *(DWORD*)(lptmpsendbuf + nowlength);
	if(m_CRCNum != m_SRCNum)
	{
		return false;
	}

	//解密校验后的正确数据包
	//if(!des.Des_Go((char *)lpDatabuf ,(char *)lptmpsendbuf ,nowlength ,"*12*23*2",8,DECRYPT))
	if(!des.Des_Go((char *)lpDatabuf ,(char *)lptmpbuf ,nowlength ,"*12*23*2",8,DECRYPT))
	{
		return false;
	}
	nowlength = DePacketHead(lpDatabuf);
	GetMessageID();
	if(lptmpbuf != NULL)
	{
		delete[] lptmpbuf;
		lptmpbuf=NULL;
	}
	if(lptmpsendbuf != NULL)
	{
		delete[] lptmpsendbuf;
		lptmpsendbuf=NULL;
	}
	return true;
}

// 解析接收到的数据
int CPacketHead::DePacketHead(unsigned char* lpDes, unsigned char* lpSou)
{
	unsigned char tmpuid[4];
	memcpy(&tmpuid,lpSou,4);
	m_packethead.uId=*(unsigned int *)&tmpuid;

	unsigned char tmpm_msg_category[2];
	memcpy(&tmpm_msg_category,lpSou+4,2);
	m_packethead.m_msg_category=*(short int *)&tmpm_msg_category;

	unsigned char tmpm_servicekey[2];
	memcpy(&tmpm_servicekey,lpSou+4+2,2);
	m_packethead.m_servicekey=*(short int *)&tmpm_servicekey;

	memcpy(m_packethead.SystemData,lpSou+4+2+2,6);

	unsigned char tmpbodylen[4];
	memcpy(&tmpbodylen,lpSou+4+2+2+6,4);
	m_packethead.bodylen=*(short int *)&tmpbodylen;

	memcpy(lpDes,lpSou+18,m_packethead.bodylen);

	return m_packethead.bodylen;
}

// 解析接收到的数据
int CPacketHead::DePacketHead(unsigned char* lpSou)
{
	unsigned char tmpuid[4];
	memcpy(&tmpuid,lpSou,4);
	m_packethead.uId=*(unsigned int *)&tmpuid;

	unsigned char tmpm_msg_category[2];
	memcpy(&tmpm_msg_category,lpSou+4,2);
	m_packethead.m_msg_category=*(short int *)&tmpm_msg_category;

	unsigned char tmpm_servicekey[2];
	memcpy(&tmpm_servicekey,lpSou+4+2,2);
	m_packethead.m_servicekey=*(short int *)&tmpm_servicekey;

	memcpy(m_packethead.SystemData,lpSou+4+2+2,6);

	unsigned char tmpbodylen[4];
	memcpy(&tmpbodylen,lpSou+4+2+2+6,4);
	m_packethead.bodylen=*(unsigned int *)&tmpbodylen;

	return m_packethead.bodylen;
}

// 获取消息ID
CEnumCore::Message_Tag_ID CPacketHead::GetMessageID(void)
{
	unsigned int uiID;
	unsigned int bCategory = (unsigned short int)m_packethead.m_msg_category;

	unsigned int bServicekey = (unsigned short int )m_packethead.m_servicekey;
	uiID =(unsigned int)(bCategory<<16) + (unsigned int)bServicekey;
	return uiID;
}

// 加密0xFE和0xEF消息
int CPacketHead::EncodeMessage(unsigned char* lpDes, int deslength,unsigned char * lpSou)
{
	unsigned char headendflag;
	headendflag=0xFE;
	unsigned char addflag;
	memcpy(lpDes,(char*)&headendflag,1);
	int nowlength=1;
	///////////////////////////////////////////////////
	for (int i = 0; i < deslength; i++)
	{
		switch (*(lpSou+i))
		{

		case 0xFE:
			addflag=0xFD;
			memcpy(lpDes+nowlength,(char*)&addflag,1);
			nowlength=nowlength+1;

			addflag=0x01;
			memcpy(lpDes+nowlength,(char*)&addflag,1);
			nowlength=nowlength+1;

			break;
		case 0xEF:
			addflag=0xFD;
			memcpy(lpDes+nowlength,(char*)&addflag,1);
			nowlength=nowlength+1;

			addflag=0xF2;
			memcpy(lpDes+nowlength,(char*)&addflag,1);
			nowlength=nowlength+1;
			break;
		case 0xFD:
			addflag=0xFD;
			memcpy(lpDes+nowlength,(char*)&addflag,1);
			nowlength=nowlength+1;

			addflag=0x00;
			memcpy(lpDes+nowlength,(char*)&addflag,1);
			nowlength=nowlength+1;
			break;
		default:
			memcpy(lpDes+nowlength,lpSou+i,1);
			nowlength=nowlength+1;
			break;
		}
	}

	/////////////////////////////////
	headendflag=0xEF;
	memcpy(lpDes+nowlength,(char*)&headendflag,1);
	///////////////////////////////////////////////////////
	nowlength=nowlength+1;
	return nowlength;
}

// 解密0xFE和0xEF消息
int CPacketHead::DecodeMessage(unsigned char* lpDes, int soulength,unsigned char * lpSou)
{
	int head = 0, tail = 0;
	int nowlength=0;
	unsigned char addflag;

	for (; head < soulength; head++)
		if (*(lpSou+head)== 0xFE)
			break;
	for (tail = head; tail < soulength; tail++)
		if (*(lpSou+tail) == 0xEF)
			break;
	if (tail >= soulength)
		return false;

	for (int i = head + 1; i < tail; i++)
	{
		if (*(lpSou+i) == 0xFD)
		{
			i=i+1;
			switch (*(lpSou+i))
			{
			case 0x01:
				addflag=0xFE;
				memcpy(lpDes+nowlength,(char*)&addflag,1);
				nowlength=nowlength+1;
				break;
			case 0x00:
				addflag=0xFD;
				memcpy(lpDes+nowlength,(char*)&addflag,1);
				nowlength=nowlength+1;
				break;
			case 0xF2:
				addflag=0xEF;
				memcpy(lpDes+nowlength,(char*)&addflag,1);
				nowlength=nowlength+1;
				break;
			default:
				return false;
			}
		}
		else
		{
			memcpy(lpDes+nowlength,lpSou+i,1);
			nowlength=nowlength+1;
		}
	}
	return nowlength;
}

// 添加消息
bool CPacketHead::AddHeader(unsigned int nid,CEnumCore::Msg_Category m_msg_category,CEnumCore::ServiceKey m_servicekey,unsigned int bodyLen)
{
	m_packethead.uId=nid;
	m_packethead.m_msg_category=m_msg_category;
	m_packethead.m_servicekey=m_servicekey;
	GetNowTime();
	m_packethead.bodylen=bodyLen;
	return false;
}

// 加密数据包
unsigned char * CPacketHead::EnSendBuf(int* alllength, unsigned char * pbodybuf,int bodylen)
{
	int actlength=0;
	unsigned char *lptmpbuf=new unsigned char[bodylen+18];
	ZeroMemory(lptmpbuf, bodylen+18);

	actlength=AddPacketHead(lptmpbuf,m_packethead,pbodybuf);//加头后大小
	
	actlength = ((actlength + 7) /8) *8;
	unsigned char *lptmpsendbuf = new unsigned char[actlength*2];//加密前
	ZeroMemory(lptmpsendbuf, actlength*2);

	des.Des_Go((char *)lptmpsendbuf,(char *)lptmpbuf,actlength,"*12*23*2",8,ENCRYPT);

	CCrc m_CRC(32, 0xA42F3D65, 0, 0xFFFFFFFF);  
	DWORD crcNum = m_CRC.Calc(lptmpsendbuf, actlength);
	memcpy(lptmpsendbuf + actlength, (DWORD*)&crcNum, 8);
	actlength = actlength + 8;

	actlength=EncodeMessage(lpsendbuf,actlength,lptmpsendbuf);
	
	*alllength=actlength;
	
	if(lptmpbuf != NULL)
	{
		delete[] lptmpbuf;
		lptmpbuf=NULL;
	}
	if(lptmpsendbuf != NULL)
	{
		delete[] lptmpsendbuf;
		lptmpsendbuf=NULL;
	}
	return lpsendbuf;
}

// 初始化数据包
bool CPacketHead::Create(int length)
{
	Destroy();
	lpsendbuf=new unsigned char[(((length+20)*2+7)/8)*8];	//加密后
	ZeroMemory(lpsendbuf, (((length+20)*2+7)/8)*8);
	lpDatabuf=new unsigned char[length*2];
	ZeroMemory(lpDatabuf, length*2);

	return false;
}

// 销毁数据包
bool CPacketHead::Destroy(void)
{
	if(lpsendbuf!=NULL)
	{
		delete[] lpsendbuf;
		lpsendbuf=NULL;
	}
	if(lpDatabuf!=NULL)
	{
		delete[] lpDatabuf;
		lpDatabuf=NULL;
	}
	return false;
}

// 获取发送的数据
unsigned char* CPacketHead::getSendBuf()
{
	return lpsendbuf;
}

// 获取接收的数据
unsigned char* CPacketHead::getDataBuf()
{
	return lpDatabuf;
}