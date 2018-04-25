#ifndef GLOBALSTRUCT_H_
#define GLOBALSTRUCT_H_

#include "..\\Global\\Global.h"
#pragma comment(lib,"..\\Global\\Debug\\Global.lib")

class __declspec(dllexport) CGlobalStruct
{
public:
	CGlobalStruct(void);
	~CGlobalStruct(void);

public:
	// ���ݵ�Ԫ�Ķ���
	struct TFLV
	{
		unsigned int nIndex;
		CEnumCore::TagName m_tagName;//2���ֽ�
		CEnumCore::TagFormat m_tagFormat;//2���ֽ�
		unsigned int m_tvlength;//4���ֽ�
		unsigned char lpdata[2048];
		TFLV()
		{
			nIndex=0;
			ZeroMemory(lpdata, 2048);
		}  
	};

	// ���ݰ��Ķ���
	struct PACKETHEAD
	{
		unsigned int uId;//4���ֽ�
		CEnumCore::Msg_Category m_msg_category;//2���ֽ�
		CEnumCore::ServiceKey m_servicekey;//2���ֽ�
		unsigned char SystemData[6];//6���ֽ�
		unsigned int bodylen;//4���ֽ�
	};
};

#endif