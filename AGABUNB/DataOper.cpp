#include "StdAfx.h"
#include "DataOper.h"

CDataOper::CDataOper(void)
{
}

CDataOper::~CDataOper(void)
{
}

void CDataOper::SetSocket(SOCKET sock)
{
	m_socketRecvSend.SetSocket(sock);
}

BOOL CDataOper::SendQuery(CSocketData &socketdata, CEnumCore::Msg_Category ecategory, CEnumCore::ServiceKey eServiceKey)
{
	// TFLV �ṹ�ܳ���.
	int nDataLen = socketdata.EnBody();
	ASSERT(0 < nDataLen);

	//������ͷ
	CPacketHead packethead;	
	packethead.Create(nDataLen);
	packethead.AddHeader(1, ecategory, eServiceKey, nDataLen);

	// ������ܺ�����ݰ�.
	int nAllDataLen = nDataLen;	//���ݰ��ܳ���.
	packethead.EnSendBuf(&nAllDataLen, (unsigned char*)socketdata.getDes(), packethead.m_packethead.bodylen);

	//��������
	if(!m_socketRecvSend.SendData((char*)packethead.getSendBuf(), nAllDataLen))
	{
//		MessageBox(NULL,ReadValue("MGM","GM_ERROR_SENDDATAERROR"),ReadValue("MGM","ERROR"),MB_OK);
		return false;
	}

	return TRUE;
}