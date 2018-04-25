#ifndef PACKETHEAD_H_
#define PACKETHEAD_H_

#include "GlobalStruct.h"
#include "Des.h"
#include "CRC.h"

class __declspec(dllexport) CPacketHead
{
public:
	CPacketHead(void);
	~CPacketHead(void);

private:	
	unsigned char *lpsendbuf;
	unsigned char *lpDatabuf;

private:
	CDES des;

public:
	CGlobalStruct::PACKETHEAD m_packethead;

public:
	
	// 构造数据包
	int AddPacketHead(unsigned char * lpDes, CGlobalStruct::PACKETHEAD m_packethead, unsigned char* lpSou);

	// 获取当前时间保存在数据包中
	bool GetNowTime(void);

	// 解析接收到的数据
	int DePacketHead(unsigned char* lpDes, unsigned char* lpSou);

	// 获取消息ID
	CEnumCore::Message_Tag_ID GetMessageID(void);

	// 加密消息
	int EncodeMessage(unsigned char* lpDes, int deslength,unsigned char* lpSou);

	// 解密消息
	int DecodeMessage(unsigned char* lpDes, int soulength,unsigned char * lpSou);

	// 添加消息
	bool AddHeader(unsigned int nid,CEnumCore::Msg_Category m_msg_category,CEnumCore::ServiceKey m_servicekey,unsigned int bodyLen);

	// 加密数据包
	unsigned char * EnSendBuf(int* alllength, unsigned char * pbodybuf,int bodylen);	

	// 初始化数据包
	bool Create(int length);

	// 销毁数据包
	bool Destroy(void);

    // 解析接收到的数据
	int DePacketHead(unsigned char* lpSou);

	// 解析数据包
	bool DeHead(unsigned char * lpbuf,int length);	

	// 获取发送的数据
	unsigned char *getSendBuf();

	// 获取接收的数据
	unsigned char *getDataBuf();
};
#endif
