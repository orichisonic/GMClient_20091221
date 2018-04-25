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
	
	// �������ݰ�
	int AddPacketHead(unsigned char * lpDes, CGlobalStruct::PACKETHEAD m_packethead, unsigned char* lpSou);

	// ��ȡ��ǰʱ�䱣�������ݰ���
	bool GetNowTime(void);

	// �������յ�������
	int DePacketHead(unsigned char* lpDes, unsigned char* lpSou);

	// ��ȡ��ϢID
	CEnumCore::Message_Tag_ID GetMessageID(void);

	// ������Ϣ
	int EncodeMessage(unsigned char* lpDes, int deslength,unsigned char* lpSou);

	// ������Ϣ
	int DecodeMessage(unsigned char* lpDes, int soulength,unsigned char * lpSou);

	// �����Ϣ
	bool AddHeader(unsigned int nid,CEnumCore::Msg_Category m_msg_category,CEnumCore::ServiceKey m_servicekey,unsigned int bodyLen);

	// �������ݰ�
	unsigned char * EnSendBuf(int* alllength, unsigned char * pbodybuf,int bodylen);	

	// ��ʼ�����ݰ�
	bool Create(int length);

	// �������ݰ�
	bool Destroy(void);

    // �������յ�������
	int DePacketHead(unsigned char* lpSou);

	// �������ݰ�
	bool DeHead(unsigned char * lpbuf,int length);	

	// ��ȡ���͵�����
	unsigned char *getSendBuf();

	// ��ȡ���յ�����
	unsigned char *getDataBuf();
};
#endif
