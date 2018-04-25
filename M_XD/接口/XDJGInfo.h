#pragma once

#include "OperatorXDJG.h"

#include "..\\GameIOCP\\GameInfo.h"

class  CXDJGInfo : public CGameInfo
{
public:
	CXDJGInfo(void);
	~CXDJGInfo(void);
 public:
	COperVector * initialize(CSession * pSess,CEnumCore::Message_Tag_ID MessageTagID, unsigned char * pbuf, int length);
	vector <CGlobalStruct::TFLV> XDJG_Net_UserInfo(char * UserName, int type, int iIndex, int iPageSize);
	bool getUserInfoDataset(vector <CGlobalStruct::TFLV> &DataSetTFLV, vector<string> vectorCol, int iIndex, int iPageSize, int iCol);
	vector <CGlobalStruct::TFLV> XDJG_Net_KickPlayer(int userByID, char * UserName, char * Account);
	vector <CGlobalStruct::TFLV> XDJG_Net_ClosePlayer(int userByID, char * UserName,int iTime,int iReason);
	vector <CGlobalStruct::TFLV> XDJG_Net_OpenPlayer(int userByID, char * UserName,int iReason);
	vector <CGlobalStruct::TFLV> XDJG_Net_BoardTasker_Oper(int userByID, int op_type,char *content, char *begintime, int interval, int repeat, char * begindate, char *enddate, int notice_index/*=0*/); 
	vector <CGlobalStruct::TFLV> XDJG_Net_BoardTasker_Query(int iIndex, int iPageSize);
	bool getBoardTaskerDetail(vector<string> &vectorDetail, int notice_index);

private:
	//记录日志信息
	char strLog[2048];

	//服务器IP地址
	char serverip[30];

	//服务器端口号
	int port;

	COperatorXDJG m_operXDJG;
};