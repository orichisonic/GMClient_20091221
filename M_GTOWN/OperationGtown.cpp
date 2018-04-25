#include "stdafx.h"
#include "OperationGtown.h"
#include ".\operationgtown.h"

OperationGTOWN::OperationGTOWN()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//��ȫ�ֱ�������
	intGTOWN = NULL;
}

OperationGTOWN::~OperationGTOWN()
{
	selfSocket.MyDestory();
	packethead.Destroy();
	if(intGTOWN != NULL)
	{
		intGTOWN = NULL;
	}
}

//����SOCKET
void OperationGTOWN::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// ��ȡini�ļ������ֵ
CString OperationGTOWN::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MGTOWN.ini");
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)
	{
		return (LPSTR)&strValue;
	}
	return "";
}

// ��ȡini�ļ����������
int OperationGTOWN::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MGTOWN.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//ͨ���кź������õ���Ӧ��ֵ
CString OperationGTOWN::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
{
	CString ItemInfo = "";
	LVCOLUMN pColumn;   
	pColumn.mask = LVCF_TEXT;   

	char buff[255];   
	pColumn.pszText = buff;   
	pColumn.cchTextMax = 255;   

	for(int i=0;i < listCtrlS->GetHeaderCtrl()->GetItemCount();i++)
	{
		listCtrlS->GetColumn(i, &pColumn);   
		if(!strcmp(ColName, pColumn.pszText))
		{
			ItemInfo = listCtrlS->GetItemText(nIndex, i);
			break;
		}
	}
	return ItemInfo;
}

// ��ȡ��Ϸ�������б�
bool OperationGTOWN::GetServerList()
{
	try
	{
		CSocketData socketdata;
		socketdata.InitCreate(1,2);
		char strInt[10];

		int gameID = ReadIntValue("MGTOWN","gameID_GTOWN");////maple add
		int gameDBID = ReadIntValue("MGTOWN","gameDBID_GTOWN");

		_itoa(gameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(gameDBID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameDBID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		int alllength = socketdata.EnBody();

		packethead.Create(alllength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::SERVERINFO_IP_QUERY,alllength);

		packethead.EnSendBuf(&alllength,(unsigned char *)socketdata.getDes(),packethead.m_packethead.bodylen);
		packetLength = alllength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),alllength))
		{
			MessageBox(NULL,ReadValue("MGTOWN","Main_UI_SENDDATAERROR"),ReadValue("MGTOWN","ERROR"),MB_OK);
			socketdata.Destroy();
			return false;
		}
		*intGTOWN = 3;
		socketdata.Destroy();		
	}
	catch(...)
	{
	}
	return true;
}

//���Ͳ�ѯ����(�ӿ�)
bool OperationGTOWN::SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::GT_OP_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		//selfSocket.SetSocket(theApp.mSocket);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MGTOWN","Main_UI_SENDDATAERROR"),ReadValue("MGTOWN","ERROR"),MB_OK);
			return false;
		}
		*intGTOWN = 3;
	}
	catch(...)
	{
	}
	return true;
}

//���Ͳ�ѯ��־����(���ݿ�)
bool OperationGTOWN::SendLogQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::GTOWN_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MGTOWN","Main_UI_SENDDATAERROR"),ReadValue("MGTOWN","ERROR"),MB_OK);
			return false;
		}
		*intGTOWN = 3;
	}
	catch(...)
	{
	}
	return true;
}

//�ٴη���ͬ����Query
bool OperationGTOWN::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//��������
		{
			MessageBox(NULL,ReadValue("MGTOWN","Main_UI_SENDDATAERROR"),ReadValue("MGTOWN","ERROR"),MB_OK);
			return false;
		}
	}
	catch(...)
	{
	}
	return true;
}

// ���츴ѡ��
bool OperationGTOWN::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGTOWN","Result"),0);
			return false;
		}

		cmbSelect->ResetContent();
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_tSvrCity = socketData->getTLVByName(i,CEnumCore::TagName::ServerInfo_City);
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MGTOWN","UM_Error_BuildComboBox"),ReadValue("MGTOWN","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// ���츴ѡ��,�����ó�ʼֵ
bool OperationGTOWN::BuildComboxs(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);//��ȡ��һ�е�һ�е�ֵ
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)//�����MESSAGE
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGTOWN","Result"),0);//��ʾMESSAGE����Ϣ
			return false;
		}

		cmbSelect->ResetContent();//���ø�ѡ�������
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_tSvrCity = socketData->getTLV(i,2);
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);
		}
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MGTOWN","UM_Error_BuildComboBox"),ReadValue("MGTOWN","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// ����ListBox
bool OperationGTOWN::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
{
	try
	{
		LONG lStyle;
		lStyle = GetWindowLong(listCtrlS->m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
		lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
		lStyle |= LVS_REPORT; //����style
		SetWindowLong(listCtrlS->m_hWnd, GWL_STYLE, lStyle);//����style

		DWORD dwStyle = listCtrlS->GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
		listCtrlS->SetExtendedStyle(dwStyle); //������չ���

		while(listCtrlS->DeleteColumn(0)){}		
		CGlobalStruct::TFLV m_BGS,m_ConGS;

		m_BGS = socketData->getTLV(1,1);
		if(m_BGS.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MGTOWN","Error"),MB_ICONWARNING+MB_OK);
			return false;
		}

		for(int i=1;i<=socketData->getColTFLVNum();i++)
		{
			m_BGS = socketData->getTLV(1,i);
			if(m_BGS.m_tagName == CEnumCore::TagName::PageCount)
			{
			}
			else
			{
				ReadValue("MGTOWN",tagToStr(m_BGS.m_tagName));
				listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//������
			}
		}
		m_BGS = socketData->getTLV(1,socketData->getColTFLVNum());
		*pageCount = atoi((char *)&m_BGS.lpdata);

		listCtrlS->DeleteAllItems();
		int nRow=0;
		for(int j=1;j<=socketData->getQueryNum();j++)
		{			
			for(int k=1;k<=socketData->getColTFLVNum();k++)
			{				
				m_ConGS = socketData->getTLV(j,k);
				if(k==1)
				{
					nRow=listCtrlS->InsertItem(j-1,(LPCTSTR)&m_ConGS.lpdata);
				}
				else
				{
					if(m_ConGS.m_tagName == CEnumCore::TagName::PageCount)
					{
					}
					/*else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_GUILDPOWERLEVEL)
					{
					listCtrlS->SetItemText(nRow,k-1,GuildLevelIntToStr(atoi((LPCTSTR)&m_ConGS.lpdata)));
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_QUESTTYPE)//��������
					{
					if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//����Ϊ1�Ļ�
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_ITEM_Finished"));//��ʾΪ�����
					}
					else//���Ͳ�Ϊ1�Ļ�
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_ITEM_Received"));//��ʾΪ�ѽ�
					}
					}
					else if((m_ConGS.m_tagName == CEnumCore::TagName::PAL_NPCTRADE) || (m_ConGS.m_tagName == CEnumCore::TagName::PAL_USERTRADE))
					{
					if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_Can"));
					}
					else
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_Cant"));
					}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_ITEMMALLGOODS)
					{
					if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_Is"));
					}
					else
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_Isnt"));
					}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_STATUS)
					{
					if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","NI_UI_UnSend"));
					}
					else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","NI_UI_Sending"));
					}
					else
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","NI_UI_Sended"));
					}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_MONEYTYPE)
					{
					if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","RM_ITEM_MONEYINBANK"));
					}
					else
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","RM_ITEM_PERSONALMONEY"));
					}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_LOGINIP)//����IP
					{
					if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))//IP��ַΪ��
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotOnline"));//��ʾΪ������
					}
					else//IP��ַ��Ϊ��
					{
					listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
					}
					}*/
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_Sex)//�Ա�
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//�Ա�Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_male"));//��ʾΪ��
						}
						else//�Ա�Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_female"));//��ʾΪŮ
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_IsOnline)//�Ƿ�����
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1Ϊ����
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_CODE_Online"));
						}
						else if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//0Ϊ������
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotOnline"));
						}
						else//ֱ����ʾ
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}

					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_HaveInamorato)//�Ƿ�������
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1Ϊ������
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_HaveInamorato"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotHaveInamorato"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_IsMarried)//�Ƿ���
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1Ϊ������
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_Married"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotMarried"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_IsShaikh)//�Ƿ��峤
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1Ϊ�峤
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_Shaikh"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotShaikh"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_Interval)//ʱ��/60
					{
						int tmpTime=atoi((LPTSTR)&m_ConGS.lpdata);
						int actTime=tmpTime/60;
						char strInt[10];
						_itoa(actTime,strInt,10);
						listCtrlS->SetItemText(nRow,k-1,strInt);
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_IsBlueIdent)//�Ƿ�����//GT_IsBlueIdent
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1Ϊ����
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_BlueIdent"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotBlueIdent"));
						}
					}
					else
					{
						listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
					}
				}
			}
			listCtrlS->SetItemData(j-1,j-1);
		}
	}
	catch (...)
	{
		MessageBox(NULL,ReadValue("MGTOWN","UM_Error_BuildList"),ReadValue("MGTOWN","Error"),0);
	}
	return false;
}
// ����ListBox
bool OperationGTOWN::BuildNoDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount,int iIndex,int iPageSize)
{
	try
	{
		char strBaseNo[10];
		int iBaseNo=(iIndex-1)*iPageSize+1;
		
		LONG lStyle;
		lStyle = GetWindowLong(listCtrlS->m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
		lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
		lStyle |= LVS_REPORT; //����style
		SetWindowLong(listCtrlS->m_hWnd, GWL_STYLE, lStyle);//����style

		DWORD dwStyle = listCtrlS->GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
		listCtrlS->SetExtendedStyle(dwStyle); //������չ���

		while(listCtrlS->DeleteColumn(0)){}		
		CGlobalStruct::TFLV m_BGS,m_ConGS;

		m_BGS = socketData->getTLV(1,1);
		if(m_BGS.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MGTOWN","Error"),MB_ICONWARNING+MB_OK);
			return false;
		}
		listCtrlS->InsertColumn( 1, "����", LVCFMT_LEFT, 80 );//������

		for(int i=1;i<=socketData->getColTFLVNum();i++)
		{
			m_BGS = socketData->getTLV(1,i);
			if(m_BGS.m_tagName == CEnumCore::TagName::PageCount)
			{
			}
			else
			{
				ReadValue("MGTOWN",tagToStr(m_BGS.m_tagName));
				listCtrlS->InsertColumn( i+1, this->strValue, LVCFMT_LEFT, 80 );//������
			}
		}
		m_BGS = socketData->getTLV(1,socketData->getColTFLVNum());
		*pageCount = atoi((char *)&m_BGS.lpdata);

		listCtrlS->DeleteAllItems();
		int nRow=0;
		for(int j=1;j<=socketData->getQueryNum();j++)
		{			
			for(int k=1;k<=socketData->getColTFLVNum();k++)
			{				
				m_ConGS = socketData->getTLV(j,k);
				if(k==1)
				{
					itoa(iBaseNo,strBaseNo,10);
					nRow=listCtrlS->InsertItem(j-1,strBaseNo);
					iBaseNo++;
					listCtrlS->SetItemText(nRow,k,(LPCTSTR)&m_ConGS.lpdata);
				}
				else
				{
					if(m_ConGS.m_tagName == CEnumCore::TagName::PageCount)
					{
					}
					else
					{
						listCtrlS->SetItemText(nRow,k,(LPCTSTR)&m_ConGS.lpdata);
					}
				}
			}
			listCtrlS->SetItemData(j-1,j-1);
		}
	}
	catch (...)
	{
		MessageBox(NULL,ReadValue("MGTOWN","UM_Error_BuildList"),ReadValue("MGTOWN","Error"),0);
	}
	return false;
	return false;
}
//�Լ�����ĸ��ƺ���
void OperationGTOWN::CopyListInfo(CListCtrl* m_listCtrl)
{
	try
	{
		POSITION pos = m_listCtrl->GetFirstSelectedItemPosition();  
		if (pos != NULL)
		{			
			char strCopy[10240];
			ZeroMemory(strCopy, 10240);

			LVCOLUMN lvcol;
			char str[256];
			int nColNum;

			nColNum = 0;
			lvcol.mask = LVCF_TEXT;
			lvcol.pszText = str;
			lvcol.cchTextMax = 256;
			while(m_listCtrl->GetColumn(nColNum, &lvcol))
			{
				if(nColNum == 0)
				{
					sprintf(strCopy,"%s%s",strCopy,lvcol.pszText);
				}
				else
				{
					sprintf(strCopy,"%s\t%s",strCopy,lvcol.pszText);				
				}							
				nColNum++;
			}
			sprintf(strCopy,"%s\r\n",strCopy);
			int nItem = 0;

			while(pos)
			{
				nItem = m_listCtrl->GetNextSelectedItem(pos);
				for(int j=0; j < m_listCtrl->GetHeaderCtrl()->GetItemCount(); j++)
				{
					if(j == 0)
					{
						sprintf(strCopy,"%s%s",strCopy,m_listCtrl->GetItemText(nItem,j));
					}
					else
					{
						sprintf(strCopy,"%s\t%s",strCopy,m_listCtrl->GetItemText(nItem,j));				
					}				
				}
				sprintf(strCopy,"%s\r\n",strCopy);
			}
			HGLOBAL clipBuff;   
			clipBuff=::GlobalAlloc(GMEM_DDESHARE,10240);   
			char* p;   
			p=(char*)GlobalLock(clipBuff);
			strcpy(p,strCopy);
			GlobalUnlock(clipBuff);   
			if(OpenClipboard(NULL))   
			{   
				if(EmptyClipboard())   
				{   
					SetClipboardData(CF_TEXT,clipBuff);   
					CloseClipboard();   
				}   
			}
		}	
		else
		{
			HGLOBAL clipBuff;   
			clipBuff=::GlobalAlloc(GMEM_DDESHARE,10240);   
			char* p;   
			p=(char*)GlobalLock(clipBuff);
			strcpy(p,"");
			GlobalUnlock(clipBuff);   
			if(OpenClipboard(NULL))   
			{   
				if(EmptyClipboard())   
				{   
					SetClipboardData(CF_TEXT,clipBuff);   
					CloseClipboard();   
				}   
			}
		}
	}
	catch(...)
	{
	}
}

struct MyData{
	CListCtrl *listctrl;       //CListCtrl�ؼ�ָ��
	int isub;        //l�к�
	int seq;        //1Ϊ����0Ϊ����
}; 

//����ص�����
int CALLBACK SortListProc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
	CIni mIni;
	MyData *p=(MyData *)lParamSort;
	CListCtrl* list =p->listctrl;
	int isub=p->isub;

	LVFINDINFO findInfo;
	findInfo.flags = LVFI_PARAM;
	findInfo.lParam = lParam1;
	int iItem1 = list->FindItem(&findInfo, -1);
	findInfo.lParam = lParam2;
	int iItem2 = list->FindItem(&findInfo, -1);

	CString strItem1 =list->GetItemText(iItem1,isub);
	CString strItem2 =list->GetItemText(iItem2,isub);

	int iCompRes;

	if (mIni.bIsNumber(strItem1) && mIni.bIsNumber(strItem2))
	{
		int nStr1 = atoi(mIni.wcharToChar(strItem1));
		int nStr2 = atoi(mIni.wcharToChar(strItem2));
		if (nStr1 > nStr2)
			iCompRes = 1;
		else if (nStr1 == nStr2)
			iCompRes = 0;
		else
			iCompRes = -1;
	}
	else
	{
		if(strItem1 > strItem2)
			iCompRes = 1;
		else if(strItem1 == strItem2)
			iCompRes = 0;
		else
			iCompRes = -1;
	}

	if(p->seq)
		return iCompRes;
	else
		return -iCompRes;
}

//�Լ������������
void OperationGTOWN::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	MyData *tmpData=new MyData;

	tmpData->listctrl = m_listCtrl;
	tmpData->isub=pNMListView->iSubItem;

	int sortnum=(int)GetProp(m_listCtrl->GetSafeHwnd(),"�����к�");
	int sortasc=(int)GetProp(m_listCtrl->GetSafeHwnd(),"����˳��");

	if(sortnum==pNMListView->iSubItem){
		sortasc=(sortasc+1)%2;
		SetProp(m_listCtrl->GetSafeHwnd(),"����˳��",(HANDLE)sortasc);
	}
	SetProp(m_listCtrl->GetSafeHwnd(),"�����к�",(HANDLE)pNMListView->iSubItem);
	tmpData->seq=sortasc;//ѡ�������ǽ���
	m_listCtrl->SortItems(SortListProc,(LPARAM)tmpData);//��������

	*pResult = 0;
}

// TagNameת����CString����
char* OperationGTOWN::tagToStr(CEnumCore::TagName tag)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tag)
	{
	case CEnumCore::TagName::GT_ServerIP://������IP
		sprintf(strValue,"%s","GT_ServerIP");
		break;
	case CEnumCore::TagName::GT_ServerName://����������
		sprintf(strValue,"%s","GT_ServerName");
		break;
	case CEnumCore::TagName::GT_UserID://���ID
		sprintf(strValue,"%s","GT_UserID");
		break;
	case CEnumCore::TagName::GT_Account://����ʺ�
		sprintf(strValue,"%s","GT_Account");
		break;
	case CEnumCore::TagName::GT_UserNick://����ǳ�
		sprintf(strValue,"%s","GT_UserNick");
		break;
	case CEnumCore::TagName::GT_StartTime://��ʼʱ��
		sprintf(strValue,"%s","GT_StartTime");
		break;
	case CEnumCore::TagName::GT_EndTime://����ʱ��
		sprintf(strValue,"%s","GT_EndTime");
		break;
	case CEnumCore::TagName::GT_Sex://�Ա�
		sprintf(strValue,"%s","GT_Sex");
		break;
	case CEnumCore::TagName::GT_CurPosition://��ǰλ��
		sprintf(strValue,"%s","GT_CurPosition");
		break;
	case CEnumCore::TagName::GT_GCash://G��
		sprintf(strValue,"%s","GT_GCash");
		break;
	case CEnumCore::TagName::GT_MCash://M��
		sprintf(strValue,"%s","GT_MCash");
		break;

	case CEnumCore::TagName::GT_TotalPoint://��������
		sprintf(strValue,"%s","GT_TotalPoint");
		break;
	case CEnumCore::TagName::GT_IsOnline://�Ƿ�����
		sprintf(strValue,"%s","GT_IsOnline");
		break;
	case CEnumCore::TagName::GT_Physical://����ֵ
		sprintf(strValue,"%s","GT_Physical");
		break;
	case CEnumCore::TagName::GT_Smart://����ֵ
		sprintf(strValue,"%s","GT_Smart");
		break;
	case CEnumCore::TagName::GT_Financial://����ֵ
		sprintf(strValue,"%s","GT_Financial");
		break;
	case CEnumCore::TagName::GT_Charm://����ֵ
		sprintf(strValue,"%s","GT_Charm");
		break;
	case CEnumCore::TagName::GT_Title://�ƺ�
		sprintf(strValue,"%s","GT_Title");
		break;
	case CEnumCore::TagName::GT_HouseNum://��������
		sprintf(strValue,"%s","GT_HouseNum");
		break;
	case CEnumCore::TagName::GT_InFamily://���ڼ���
		sprintf(strValue,"%s","GT_InFamily");
		break;
	case CEnumCore::TagName::GT_FriendNum://��������
		sprintf(strValue,"%s","GT_FriendNum");
		break;
	case CEnumCore::TagName::GT_HaveInamorato://�Ƿ�������
		sprintf(strValue,"%s","GT_HaveInamorato");
		break;
	case CEnumCore::TagName::GT_IsMarried://�Ƿ���
		sprintf(strValue,"%s","GT_IsMarried");
		break;
	case CEnumCore::TagName::GT_IsShaikh://�Ƿ��峤
		sprintf(strValue,"%s","GT_IsShaikh");
		break;
	case CEnumCore::TagName::GT_InamoratoNick://�����ǳ�
		sprintf(strValue,"%s","GT_InamoratoNick");
		break;
	case CEnumCore::TagName::GT_LoverNick ://�Է���ɫ�ǳ�
		sprintf(strValue,"%s","GT_LoverNick ");
		break;
	case CEnumCore::TagName::GT_Interval://ʱ����
		sprintf(strValue,"%s","GT_Interval");
		break;
	case CEnumCore::TagName::GT_IsImmediate://�Ƿ���������
		sprintf(strValue,"%s","GT_IsImmediate");
		break;
	case CEnumCore::TagName::GT_BoardMessage://��������
		sprintf(strValue,"%s","GT_BoardMessage");
		break;
	case CEnumCore::TagName::GT_BanReason://��ͣԭ��
		sprintf(strValue,"%s","GT_BanReason");
		break;
	case CEnumCore::TagName::GT_UnbindReason://���ԭ��
		sprintf(strValue,"%s","GT_UnbindReason");
		break;

	case CEnumCore::TagName::GT_NoticeID://����ID
		sprintf(strValue,"%s","GT_NoticeID");
		break;
	case CEnumCore::TagName::GT_UserState://�û�״̬(����Ƿ��ͣ)
		sprintf(strValue,"%s","GT_UserState");
		break;
	case CEnumCore::TagName::GT_FamilyID://����ID
		sprintf(strValue,"%s","GT_FamilyID");
		break;
	case CEnumCore::TagName::GT_Type://����
		sprintf(strValue,"%s","GT_Type");
		break;
	case CEnumCore::TagName::GT_ZoneID://����ID
		sprintf(strValue,"%s","GT_ZoneID");
		break;
	case CEnumCore::TagName::GT_MID://��ƷID
		sprintf(strValue,"%s","GT_MID");
		break;
	case CEnumCore::TagName::GT_TimesLimit://ʹ�ô���
		sprintf(strValue,"%s","GT_TimesLimit");
		break;
	case CEnumCore::TagName::GT_DaysLimit://ʹ������
		sprintf(strValue,"%s","GT_DaysLimit");
		break;
	case CEnumCore::TagName::GT_RoomName://��������
		sprintf(strValue,"%s","GT_RoomName");
		break;
	case CEnumCore::TagName::GT_RoomPos://��������
		sprintf(strValue,"%s","GT_RoomPos");
		break;
	case CEnumCore::TagName::GT_decorationName://������װ��Ʒ����
		sprintf(strValue,"%s","GT_decorationName");
		break;
	case CEnumCore::TagName::GT_RoomLimit://����ʱ��
		sprintf(strValue,"%s","GT_RoomLimit");
		break;
	case CEnumCore::TagName::GT_FamilyName://��������
		sprintf(strValue,"%s","GT_FamilyName");
		break;
	case CEnumCore::TagName::GT_FamilyCreate://����ʱ��
		sprintf(strValue,"%s","GT_FamilyCreate");
		break;
	case CEnumCore::TagName::GT_MemberNum://��Ա����
		sprintf(strValue,"%s","GT_MemberNum");
		break;
	case CEnumCore::TagName::GT_FamilyLeader://�峤����
		sprintf(strValue,"%s","GT_FamilyLeader");
		break;
	case CEnumCore::TagName::GT_FamilyLeaderID://�峤ID
		sprintf(strValue,"%s","GT_FamilyLeaderID");
		break;
	case CEnumCore::TagName::GT_MemberName://��Ա����
		sprintf(strValue,"%s","GT_MemberName");
		break;
	case CEnumCore::TagName::GT_JoinTime://����ʱ��
		sprintf(strValue,"%s","GT_JoinTime");
		break;
	case CEnumCore::TagName::GT_PetName://��������
		sprintf(strValue,"%s","GT_PetName");
		break;
	case CEnumCore::TagName::GT_PetPos://��ǰλ��
		sprintf(strValue,"%s","GT_PetPos");
		break;
	case CEnumCore::TagName::GT_PetLimit://����ʱ��
		sprintf(strValue,"%s","GT_PetLimit");
		break;
	case CEnumCore::TagName::GT_ItemID://����ID
		sprintf(strValue,"%s","GT_ItemID");
		break;
	case CEnumCore::TagName::GT_ItemName://��������
		sprintf(strValue,"%s","GT_ItemName");
		break;
	case CEnumCore::TagName::GT_IsBlueIdent://�Ƿ�����
		sprintf(strValue,"%s","GT_IsBlueIdent");
		break;
	case CEnumCore::TagName::GT_Limit://����ʱ��
		sprintf(strValue,"%s","GT_Limit");
		break;
	case CEnumCore::TagName::GT_FriendName://��������
		sprintf(strValue,"%s","GT_FriendName");
		break;
	case CEnumCore::TagName::GT_BlackFName://��������
		sprintf(strValue,"%s","GT_BlackFName");
		break;
	case CEnumCore::TagName::GT_DarkFName://��������
		sprintf(strValue,"%s","GT_DarkFName");
		break;
	case CEnumCore::TagName::GT_OpenTime://����ʱ��
		sprintf(strValue,"%s","GT_OpenTime");
		break;
	case CEnumCore::TagName::GT_GetReward://��ý���
		sprintf(strValue,"%s","GT_GetReward");
		break;
	case CEnumCore::TagName::GT_FamilyDuty://����ְ��
		sprintf(strValue,"%s","GT_FamilyDuty");
		break;

	case CEnumCore::TagName::GT_BanTime://��ͣʱ��
		sprintf(strValue,"%s","GT_BanTime");
		break;
	case CEnumCore::TagName::GT_SenderNick://�����ǳ�
		sprintf(strValue,"%s","GT_SenderNick");
		break;
	case CEnumCore::TagName::GT_ReceiverNick://���շ��ǳ�
		sprintf(strValue,"%s","GT_ReceiverNick");
		break;
	case CEnumCore::TagName::GT_TradeTime://����ʱ��
		sprintf(strValue,"%s","GT_TradeTime");
		break;
	case CEnumCore::TagName::GT_TradeItemID://������ƷID
		sprintf(strValue,"%s","GT_TradeItemID");
		break;
	case CEnumCore::TagName::GT_TradeItemName://��Ʒ����
		sprintf(strValue,"%s","GT_TradeItemName");
		break;
	case CEnumCore::TagName::GT_TradeItemNum://��Ʒ����
		sprintf(strValue,"%s","GT_TradeItemNum");
		break;
	case CEnumCore::TagName::GT_MailTime://�����ʼ�ʱ��
		sprintf(strValue,"%s","GT_MailTime");
		break;
	case CEnumCore::TagName::GT_MailContent://�ʼ�����
		sprintf(strValue,"%s","GT_MailContent");
		break;
	case CEnumCore::TagName::GT_TaskName://��������
		sprintf(strValue,"%s","GT_TaskName");
		break;
	case CEnumCore::TagName::GT_TaskTime://���ʱ��
		sprintf(strValue,"%s","GT_TaskTime");
		break;
	case CEnumCore::TagName::GT_TaskReward://������ɽ���1
		sprintf(strValue,"%s","GT_TaskReward");
		break;
	case CEnumCore::TagName::GT_UseItemName://ʹ�õ�������
		sprintf(strValue,"%s","GT_UseItemName");
		break;
	case CEnumCore::TagName::GT_UseItemNum://ʹ�õ�������
		sprintf(strValue,"%s","GT_UseItemNum");
		break;
	case CEnumCore::TagName::GT_UseItemTime://ʹ�õ���ʱ��
		sprintf(strValue,"%s","GT_UseItemTime");
		break;
	case CEnumCore::TagName::GT_MailTitle://�ʼ�����
		sprintf(strValue,"%s","GT_MailTitle");
		break;
	case CEnumCore::TagName::GT_OnlineTime://����ʱ��
		sprintf(strValue,"%s","GT_OnlineTime");
		break;
	case CEnumCore::TagName::GT_RewardItemName://��ý�����������
		sprintf(strValue,"%s","GT_RewardItemName");
		break;
	case CEnumCore::TagName::GT_RewardGetTime://���ʱ��
		sprintf(strValue,"%s","GT_RewardGetTime");
		break;
	case CEnumCore::TagName::GT_SenderAccount://�����ʺ�
		sprintf(strValue,"%s","GT_SenderAccount");
		break;
	case CEnumCore::TagName::GT_SendTime://����ʱ��
		sprintf(strValue,"%s","GT_SendTime");
		break;
	case CEnumCore::TagName::GT_SendContent://��������
		sprintf(strValue,"%s","GT_SendContent");
		break;
	case CEnumCore::TagName::GT_LoginTime://��¼ʱ��
		sprintf(strValue,"%s","GT_LoginTime");
		break;
	case CEnumCore::TagName::GT_LogoutTime://�ǳ�ʱ��
		sprintf(strValue,"%s","GT_LogoutTime");
		break;
	case CEnumCore::TagName::GT_UserIP://���IP
		sprintf(strValue,"%s","GT_UserIP");
		break;
	case CEnumCore::TagName::GT_SendNick://�����ǳ�
		sprintf(strValue,"%s","GT_SendNick");
		break;
	case CEnumCore::TagName::GT_TreasureBox_Type://��������
		sprintf(strValue,"%s","GT_TreasureBox_Type");
		break;
	case CEnumCore::TagName::GT_TaskReward2://������ɽ���2
		sprintf(strValue,"%s","GT_TaskReward2");
		break;
	case CEnumCore::TagName::GT_ChooseReward://�����ѡ����
		sprintf(strValue,"%s","GT_ChooseReward");
		break;
	case CEnumCore::TagName::GT_BuyTime://����ʱ��
		sprintf(strValue,"%s","GT_BuyTime");
		break;
	case CEnumCore::TagName::GT_TimeLimit://ʹ������
		sprintf(strValue,"%s","GT_TimeLimit");
		break;
	case CEnumCore::TagName::GT_ChargeTime://��ֵ����ʱ��
		sprintf(strValue,"%s","GT_ChargeTime");
		break;
	case CEnumCore::TagName::GT_ChargeMoney://��ֵ���
		sprintf(strValue,"%s","GT_ChargeMoney");
		break;
	case CEnumCore::TagName::GT_Money://��Ǯ
		sprintf(strValue,"%s","GT_Money");
		break;
	case CEnumCore::TagName::GT_Resume://����ǩ��
		sprintf(strValue,"%s","GT_Resume");
		break;
	case CEnumCore::TagName::GT_Card://��Ƭ
		sprintf(strValue,"%s","GT_Card");
		break;
	case CEnumCore::TagName::GT_Male://�з���
		sprintf(strValue,"%s","GT_Male");
		break;
	case CEnumCore::TagName::GT_Female://Ů����
		sprintf(strValue,"%s","GT_Female");
		break;
	case CEnumCore::TagName::GT_MarryPeople://��������
		sprintf(strValue,"%s","GT_MarryPeople");
		break;
	case CEnumCore::TagName::GT_Pktimes://Pk��
		sprintf(strValue,"%s","GT_Pktimes");
		break;
	case CEnumCore::TagName::GT_Win://ʤ����
		sprintf(strValue,"%s","GT_Win");
		break;
	case CEnumCore::TagName::GT_Cowin://ʧ����
		sprintf(strValue,"%s","GT_Cowin");
		break;
	case CEnumCore::TagName::GT_Times://����
		sprintf(strValue,"%s","GT_Times");
		break;
	case CEnumCore::TagName::GT_Lustful://���ն�
		sprintf(strValue,"%s","GT_Lustful");
		break;
	case CEnumCore::TagName::GT_Fanta://���˶�
		sprintf(strValue,"%s","GT_Fanta");
		break;
	case CEnumCore::TagName::GT_Allexp://�ۺ�ָ��
		sprintf(strValue,"%s","GT_Allexp");
		break;
	case CEnumCore::TagName::GT_SlaveCount://ū����
		sprintf(strValue,"%s","GT_SlaveCount");
		break;
	case CEnumCore::TagName::GT_SlaveSum://���ʲ�
		sprintf(strValue,"%s","GT_SlaveSum");
		break;
	case CEnumCore::TagName::GT_Coin://�ֽ�
		sprintf(strValue,"%s","GT_Coin");
		break;
	case CEnumCore::TagName::GT_SlaveID://ū��ID
		sprintf(strValue,"%s","GT_SlaveID");
		break;
	case CEnumCore::TagName::GT_SlaveAccount://ū������
		sprintf(strValue,"%s","GT_SlaveAccount");
		break;
	case CEnumCore::TagName::GT_SlaveNick://ū���ǳ�
		sprintf(strValue,"%s","GT_SlaveNick");
		break;
	case CEnumCore::TagName::GT_Price://���
		sprintf(strValue,"%s","GT_Price");
		break;
	case CEnumCore::TagName::GT_IsSell://�Ƿ�����
		sprintf(strValue,"%s","GT_IsSell");
		break;
	case CEnumCore::TagName::GT_DateRecord://����ʱ��
		sprintf(strValue,"%s","GT_DateRecord");
		break;
	case CEnumCore::TagName::GT_Discount://������
		sprintf(strValue,"%s","GT_Discount");
		break;
	case CEnumCore::TagName::GT_JW2Name://��ӦJW2������
		sprintf(strValue,"%s","GT_JW2Name");
		break;
	case CEnumCore::TagName::GT_ID://���
		sprintf(strValue,"%s","GT_ID");
		break;	
	default:
		break;
	}
	return strValue;
}

// ��ʾ�������
void OperationGTOWN::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MGTOWN","Success"),ReadValue("MGTOWN","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MGTOWN","Failure"),ReadValue("MGTOWN","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MGTOWN","Result"),0);
	}
}

// ��ȡ����ȼ�ID
int OperationGTOWN::GuildLevelStrToInt(CString m_str)
{
	if(!strcmp(m_str,ReadValue("MGTOWN","GuildLvl_Member")))
	{
		return 0;
	}
	else if(!strcmp(m_str,ReadValue("MGTOWN","GuildLvl_BCadre")))
	{
		return 1;
	}
	else if(!strcmp(m_str,ReadValue("MGTOWN","GuildLvl_ACadre")))
	{
		return 2;
	}
	else if(!strcmp(m_str,ReadValue("MGTOWN","GuildLvl_VChairman")))
	{
		return 3;
	}
	else if(!strcmp(m_str,ReadValue("MGTOWN","GuildLvl_Chairman")))
	{
		return 4;
	}
	return -1;
}

// ��ȡ����ȼ�����
CString OperationGTOWN::GuildLevelIntToStr(int iLevel)
{
	switch(iLevel)
	{
	case 0:
		return ReadValue("MGTOWN","GuildLvl_Member");
	case 1:
		return ReadValue("MGTOWN","GuildLvl_BCadre");
	case 2:
		return ReadValue("MGTOWN","GuildLvl_ACadre");
	case 3:
		return ReadValue("MGTOWN","GuildLvl_VChairman");
	case 4:
		return ReadValue("MGTOWN","GuildLvl_Chairman");
	}
	return "";
}