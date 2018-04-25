#include "stdafx.h"
#include "OperationWA.h"
#include ".\OperationWA.h"

OperationWA::OperationWA()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//��ȫ�ֱ�������
	intWA = NULL;
}
OperationWA::~OperationWA()
{
	selfSocket.MyDestory();
	packethead.Destroy();
	if(intWA != NULL)
	{
		intWA = NULL;
	}
}

//����SOCKET
void OperationWA::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// ��ȡini�ļ������ֵ
CString OperationWA::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MWA.ini");
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)
	{
		return (LPSTR)&strValue;
	}
	return "";
}

// ��ȡini�ļ����������
int OperationWA::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MWA.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//ͨ���кź������õ���Ӧ��ֵ
CString OperationWA::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
{
	CString ItemInfo = "";
	LVCOLUMN pColumn;   
	pColumn.mask = LVCF_TEXT;   

	char buff[255];   
	pColumn.pszText = buff;   
	pColumn.cchTextMax = 255;   

	if((listCtrlS->GetItemCount() > 0) && (nIndex >= 0))
	{
		for(int i=0;i < listCtrlS->GetHeaderCtrl()->GetItemCount();i++)
		{
			listCtrlS->GetColumn(i, &pColumn);   
			if(!strcmp(ColName, pColumn.pszText))
			{
				ItemInfo = listCtrlS->GetItemText(nIndex, i);
				break;
			}
		}
	}
	return ItemInfo;
}

// ��ȡ��Ϸ�������б�
bool OperationWA::GetServerList()
{
	try
	{
		CIni mIni;
		//MessageBox(NULL,"EE","",0);
		CSocketData socketdata;
		socketdata.InitCreate(1,2);
		char strInt[10];

		int gameID = ReadIntValue("MWA","gameID_WA");
		int gameDBID = ReadIntValue("MWA","gameDBID_WA");

		_itoa(gameID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);

		_itoa(gameDBID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::ServerInfo_GameDBID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);
		CString gamename="M_WA";
		//gamename=theApp.operWA.ReadValue("MWA","WA_GAMENAME");
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(gamename),(unsigned char *)mIni.wcharToChar(gamename));//��Ϸ����
		int alllength = socketdata.EnBody();

		packethead.Create(alllength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::COMMON,CEnumCore::ServiceKey::SERVERINFO_IP_QUERY,alllength);

		packethead.EnSendBuf(&alllength,(unsigned char *)socketdata.getDes(),packethead.m_packethead.bodylen);
		packetLength = alllength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),alllength))
		{
			MessageBox(NULL,ReadValue("MWA","Main_UI_SENDDATAERROR"),ReadValue("MWA","ERROR"),MB_OK);
			socketdata.Destroy();
			return false;
		}
		*intWA = 7;

		socketdata.Destroy();		
	}
	catch(...)
	{
	}
	return true;
}

//���Ͳ�ѯ����
bool OperationWA::SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		//MessageBox(NULL,"test","",0);
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::WA_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		//selfSocket.SetSocket(theApp.mSocket);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MWA","Main_UI_SENDDATAERROR"),ReadValue("MWA","ERROR"),MB_OK);
			return false;
		}
		*intWA = 7;
	}
	catch(...)
	{
	}
	return true;
}

//���Ͳ�ѯ��־����
bool OperationWA::SendLogQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::WA_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MWA","Main_UI_SENDDATAERROR"),ReadValue("MWA","ERROR"),MB_OK);
			return false;
		}
		*intWA = 7;
	}
	catch(...)
	{
	}
	return true;
}

//�ٴη���ͬ����Query
bool OperationWA::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//��������
		{
			MessageBox(NULL,ReadValue("MWA","Main_UI_SENDDATAERROR"),ReadValue("MWA","ERROR"),MB_OK);
			return false;
		}
	}
	catch(...)
	{
	}
	return true;
}

// ���츴ѡ��
bool OperationWA::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MWA","Result"),0);
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
		MessageBox(NULL,ReadValue("MWA","UM_Error_BuildComboBox"),ReadValue("MWA","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

//���츴ѡ��
bool OperationWA::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect,int nItem)
{
	try
	{
		CGlobalStruct::TFLV m_TFLV;
		m_TFLV.nIndex=0;

		m_TFLV = socketData->getTLV(1,1);
		if(m_TFLV.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_TFLV.lpdata,ReadValue("MWA","Result"),0);
			return false;
		}

		cmbSelect->ResetContent();
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_TFLV=socketData->getTLV(i,nItem);
			cmbSelect->AddString((LPCTSTR)&m_TFLV.lpdata);
		}
		cmbSelect->SetCurSel(0);

	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MWA","UM_Error_BuildComboBox"),ReadValue("MWA","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// ���츴ѡ��
bool OperationWA::BuildComboxs(CSocketData* socketData,CComboBox* cmbSelect,CEnumCore::TagName tag)
{
	try
	{
		CGlobalStruct::TFLV m_TFLV;
		m_TFLV.nIndex=0;

		m_TFLV = socketData->getTLV(1,1);
		if(m_TFLV.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_TFLV.lpdata,ReadValue("MWA","Result"),0);
			return false;
		}

		cmbSelect->ResetContent();
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_TFLV=socketData->getTLVByName(i,tag);
			cmbSelect->AddString((LPCTSTR)&m_TFLV.lpdata);
		}
		cmbSelect->SetCurSel(0);

	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MWA","UM_Error_BuildComboBox"),ReadValue("MWA","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// ����ListBox
bool OperationWA::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
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
			CString temp;
			temp.Format("%s",(LPCTSTR)&m_BGS.lpdata);
			if(temp=="���ݿ�Ϊ��")
			{
               MessageBox(NULL,"û�в��ҵ��������",ReadValue("MWA","Error"),MB_ICONWARNING+MB_OK);
			   return false;
			}
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MWA","Error"),MB_ICONWARNING+MB_OK);
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
				ReadValue("MWA",tagToStr(m_BGS.m_tagName));
				listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//������
				//MessageBox(NULL,tagToStr(m_BGS.m_tagName),"",0);
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
					else
					{
						if(m_ConGS.m_tagName == CEnumCore::TagName::WA_Status)
						{
							CString temp;
							temp.Format("%s",(LPCTSTR)m_ConGS.lpdata);
							//MessageBox(NULL,(LPCTSTR)&m_ConGS.lpdata,"",0);
							//if(temp.Find('0')>=0)
							//{
							//	//listCtrlS->SetItemText(nRow,k-1,"δ����");
							//}
							//else if(temp.Find('1')>=0)
							//{
							//	listCtrlS->SetItemText(nRow,k-1,"�����");
							//}
							//else if(temp.Find('2')>=0)
							//{
							//	listCtrlS->SetItemText(nRow,k-1,"���ڷ���");
							//}
							//else
							{

								listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
							}
							// listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
						else
						{
							if(m_ConGS.m_tagFormat==CEnumCore::TagFormat::TLV_INTEGER)
							{

							}
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
							//MessageBox(NULL,(LPCTSTR)&m_ConGS.lpdata,"",0);
							//MessageBox(NULL,(LPCTSTR)&m_ConGS.,"",0);
						}
					}

				}
				//else
				//{
				//	if(m_ConGS.m_tagName == CEnumCore::TagName::PageCount)
				//	{
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::WA_GUILDPOWERLEVEL)
				//	{
				//		listCtrlS->SetItemText(nRow,k-1,GuildLevelIntToStr(atoi((LPCTSTR)&m_ConGS.lpdata)));
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::WA_QUESTTYPE)//��������
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//����Ϊ1�Ļ�
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_ITEM_Finished"));//��ʾΪ�����
				//		}
				//		else//���Ͳ�Ϊ1�Ļ�
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_ITEM_Received"));//��ʾΪ�ѽ�
				//		}
				//	}
				//	else if((m_ConGS.m_tagName == CEnumCore::TagName::WA_NPCTRADE) || (m_ConGS.m_tagName == CEnumCore::TagName::WA_USERTRADE))
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_Code_Can"));
				//		}
				//		else
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_Code_Cant"));
				//		}
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::WA_ITEMMALLGOODS)
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_Code_Is"));
				//		}
				//		else
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_Code_Isnt"));
				//		}
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::WA_STATUS)
				//	{
				//		if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","NI_UI_UnSend"));
				//		}
				//		else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","NI_UI_Sending"));
				//		}
				//		else
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","NI_UI_Sended"));
				//		}
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::WA_MONEYTYPE)
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","RM_ITEM_MONEYINBANK"));
				//		}
				//		else
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","RM_ITEM_PERSONALMONEY"));
				//		}
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::WA_LOGINIP)//����IP
				//	{
				//		if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))//IP��ַΪ��
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_Code_NotOnline"));//��ʾΪ������
				//		}
				//		else//IP��ַ��Ϊ��
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
				//		}
				//	}
				//	else
				//	{
				//		listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
				//	}
				//}
			}
			listCtrlS->SetItemData(j-1,j-1);
		}
	}
	catch (...)
	{
		MessageBox(NULL,ReadValue("MWA","UM_Error_BuildList"),ReadValue("MWA","Error"),0);
	}
	return false;
}

//�Լ�����ĸ��ƺ���
void OperationWA::CopyListInfo(CListCtrl* m_listCtrl)
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
void OperationWA::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
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
char* OperationWA::tagToStr(CEnumCore::TagName tag)
{
	unsigned short tmpTagName = tag;
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tmpTagName)
	{
	case CEnumCore::TagName::WA_ServerName://����������
		sprintf(strValue,"%s","WA_ServerName");
		break;
	case CEnumCore::TagName::WA_ServerIP://������IP
		sprintf(strValue,"%s","WA_ServerIP");
		break;
	case CEnumCore::TagName::WA_Account://�ʺ�
		sprintf(strValue,"%s","WA_Account");
		break;
	case CEnumCore::TagName::WA_UserNick://�ǳ�
		sprintf(strValue,"%s","WA_UserNick");
		break;
	case CEnumCore::TagName::WA_BeginTime://��ʼʱ��
		sprintf(strValue,"%s","WA_BeginTime");
		break;
	case CEnumCore::TagName::WA_EndTime://����ʱ��
		sprintf(strValue,"%s","WA_EndTime");
		break;
	case CEnumCore::TagName::WA_AccountID://�ʺ�ID
		sprintf(strValue,"%s","WA_AccountID");
		break;
	case CEnumCore::TagName::WA_NickID://��ɫID
		sprintf(strValue,"%s","WA_NickID");
		break;
	case CEnumCore::TagName::WA_Time://ʱ��
		sprintf(strValue,"%s","WA_Time");
		break;
	case CEnumCore::TagName::WA_RealmId://����ID
		sprintf(strValue,"%s","WA_RealmId");
		break;
	case CEnumCore::TagName::WA_ClusterID://������ID
		sprintf(strValue,"%s","WA_ClusterID");
		break;
	case CEnumCore::TagName::WA_TitleName1://��ɫ��ν1
		sprintf(strValue,"%s","WA_TitleName1");
		break;
	case CEnumCore::TagName::WA_TitleName2://��ɫ��ν2
		sprintf(strValue,"%s","WA_TitleName2");
		break;
	case CEnumCore::TagName::WA_CharType://��ɫ����
		sprintf(strValue,"%s","WA_CharType");
		break;
	case CEnumCore::TagName::WA_Profession://��ɫְҵ
		sprintf(strValue,"%s","WA_Profession");
		break;
	case CEnumCore::TagName::WA_Sex://��ɫ�Ա�
		sprintf(strValue,"%s","WA_Sex");
		break;
	case CEnumCore::TagName::WA_IsDelete://�Ƿ�ɾ��
		sprintf(strValue,"%s","WA_IsDelete");
		break;
	case CEnumCore::TagName::WA_IsOnline://�Ƿ�����
		sprintf(strValue,"%s","WA_IsOnline");
		break;
	case CEnumCore::TagName::WA_IsClosed://�Ƿ��ͣ
		sprintf(strValue,"%s","WA_IsClosed");
		break;
	case CEnumCore::TagName::WA_Level://�ȼ�
		sprintf(strValue,"%s","WA_Level");
		break;
	case CEnumCore::TagName::WA_Money://��Ϸ������
		sprintf(strValue,"%s","WA_Money");
		break;
	case CEnumCore::TagName::WA_NineyouMoney://9�α�����
		sprintf(strValue,"%s","WA_NineyouMoney");
		break;
	case CEnumCore::TagName::WA_ReserveMoney://������
		sprintf(strValue,"%s","WA_ReserveMoney");
		break;
	case CEnumCore::TagName::WA_CurSceneID://��ǰ���ڳ���ID
		sprintf(strValue,"%s","WA_CurSceneID");
		break;
	case CEnumCore::TagName::WA_CurSceneName://��ǰ���ڳ�������
		sprintf(strValue,"%s","WA_CurSceneName");
		break;
	case CEnumCore::TagName::WA_CurScenePos://��ǰ���ڳ�������
		sprintf(strValue,"%s","WA_CurScenePos");
		break;
	case CEnumCore::TagName::WA_Hp://����ֵ
		sprintf(strValue,"%s","WA_Hp");
		break;
	case CEnumCore::TagName::WA_Mp://ħ��ֵ
		sprintf(strValue,"%s","WA_Mp");
		break;
	case CEnumCore::TagName::WA_Vitality://����ֵ
		sprintf(strValue,"%s","WA_Vitality");
		break;
	case CEnumCore::TagName::WA_GoodEvil://�ƶ�ֵ
		sprintf(strValue,"%s","WA_GoodEvil");
		break;
	case CEnumCore::TagName::WA_PhysicalAttack://������
		sprintf(strValue,"%s","WA_PhysicalAttack");
		break;
	case CEnumCore::TagName::WA_PhysicalDefense://�������
		sprintf(strValue,"%s","WA_PhysicalDefense");
		break;
	case CEnumCore::TagName::WA_MagicAttack://ħ������
		sprintf(strValue,"%s","WA_MagicAttack");
		break;
	case CEnumCore::TagName::WA_MagicDefense://ħ������
		sprintf(strValue,"%s","WA_MagicDefense");
		break;
	case CEnumCore::TagName::WA_Critical://������
		sprintf(strValue,"%s","WA_Critical");
		break;
	case CEnumCore::TagName::WA_Strength://����
		sprintf(strValue,"%s","WA_Strength");
		break;
	case CEnumCore::TagName::WA_Dexterity://����
		sprintf(strValue,"%s","WA_Dexterity");
		break;
	case CEnumCore::TagName::WA_Intellect://����
		sprintf(strValue,"%s","WA_Intellect");
		break;
	case CEnumCore::TagName::WA_Corporeity://����
		sprintf(strValue,"%s","WA_Corporeity");
		break;
	case CEnumCore::TagName::WA_PotentialPoint://Ǳ��
		sprintf(strValue,"%s","WA_PotentialPoint");
		break;
	case CEnumCore::TagName::WA_Exp://����
		sprintf(strValue,"%s","WA_Exp");
		break;
	case CEnumCore::TagName::WA_ExpNextLevel://��������
		sprintf(strValue,"%s","WA_ExpNextLevel");
		break;
	case CEnumCore::TagName::WA_PhysicalResist://������
		sprintf(strValue,"%s","WA_PhysicalResist");
		break;
	case CEnumCore::TagName::WA_MagicResist://��������
		sprintf(strValue,"%s","WA_MagicResist");
		break;
	case CEnumCore::TagName::WA_FireResist://���濹��
		sprintf(strValue,"%s","WA_FireResist");
		break;
	case CEnumCore::TagName::WA_ColdResist://��������
		sprintf(strValue,"%s","WA_ColdResist");
		break;
	case CEnumCore::TagName::WA_PoisonResist://���ؿ���
		sprintf(strValue,"%s","WA_PoisonResist");
		break;
	case CEnumCore::TagName::WA_Reason://ԭ��
		sprintf(strValue,"%s","WA_Reason");
		break;
	case CEnumCore::TagName::WA_RemainTime://ʣ��ʱ��
		sprintf(strValue,"%s","WA_RemainTime");
		break;
	case CEnumCore::TagName::WA_TaskID://����ID
		sprintf(strValue,"%s","WA_TaskID");
		break;
	case CEnumCore::TagName::WA_BoardMessage://��������
		sprintf(strValue,"%s","WA_BoardMessage");
		break;
	case CEnumCore::TagName::WA_Interval://���ʱ��
		sprintf(strValue,"%s","WA_Interval");
		break;
	case CEnumCore::TagName::WA_Status://״̬
		sprintf(strValue,"%s","WA_Status");
		break;

	case CEnumCore::TagName::WA_friendIndex://���ѽ�ɫID
		sprintf(strValue,"%s","WA_friendIndex");
		break;
	case CEnumCore::TagName::WA_friendName://��������
		sprintf(strValue,"%s","WA_friendName");
		break;
	case CEnumCore::TagName::WA_friendTypeId://���ѵĽ�ɫ����
		sprintf(strValue,"%s","WA_friendTypeId");
		break;
	case CEnumCore::TagName::WA_friendLevel://���ѵȼ�
		sprintf(strValue,"%s","WA_friendLevel");
		break;
	case CEnumCore::TagName::WA_friendIni://���ܶ�
		sprintf(strValue,"%s","WA_friendIni");
		break;
	case CEnumCore::TagName::WA_LastLoginTime://�ϴε�¼ʱ��
		sprintf(strValue,"%s","WA_LastLoginTime");
		break;
	case CEnumCore::TagName::WA_EnableTime://��ͣ����ʱ��
		sprintf(strValue,"%s","WA_EnableTime");
		break;
	case CEnumCore::TagName::WA_itemIndex://��Ʒ���
		sprintf(strValue,"%s","WA_itemIndex");
	
		break;
	case CEnumCore::TagName::WA_itemTypeId://����ID
		sprintf(strValue,"%s","WA_itemTypeId");
		break;
	case CEnumCore::TagName::WA_itemName://��Ʒ����
		sprintf(strValue,"%s","WA_itemName");
		break;
	case CEnumCore::TagName::WA_itemUniqueId://ΨһID
		sprintf(strValue,"%s","WA_itemUniqueId");
		break;
	case CEnumCore::TagName::WA_itemCount://����
		sprintf(strValue,"%s","WA_itemCount");
		break;
	case CEnumCore::TagName::WA_itemDur://�;�
		sprintf(strValue,"%s","WA_itemDur");
		break;

		//�������������
	case CEnumCore::TagName::WA_medalTypeId://����ID
		sprintf(strValue,"%s","WA_medalTypeId");
		break;
	case CEnumCore::TagName::WA_medalName://��������
		sprintf(strValue,"%s","WA_medalName");
		break;
	case CEnumCore::TagName::WA_medalDur://�;�
		sprintf(strValue,"%s","WA_medalDur");

		break;
	case CEnumCore::TagName::WA_medalBringUp://����
		sprintf(strValue,"%s","WA_medalBringUp");
		break;
	case CEnumCore::TagName::WA_medalPetIndex://������ų���ֵ255Ϊ�޳���
		sprintf(strValue,"%s","WA_medalPetIndex");
		break;
	case CEnumCore::TagName::WA_medalPos://�����ڳ��ﱳ����λ�� 255Ϊװ����
		sprintf(strValue,"%s","WA_medalPos");
		break;
	case CEnumCore::TagName::WA_petTypeId://����ID
		sprintf(strValue,"%s","WA_petTypeId");
		break;
	case CEnumCore::TagName::WA_petName://��������
		sprintf(strValue,"%s","WA_petName");
		break;
	case CEnumCore::TagName::WA_petLevel://�ȼ�
		sprintf(strValue,"%s","WA_petLevel");

		break;
	case CEnumCore::TagName::WA_petNature://�Ը�
		sprintf(strValue,"%s","WA_petNature");
		break;
	case CEnumCore::TagName::WA_petGrowth://�ɳ���
		sprintf(strValue,"%s","WA_petGrowth");
		break;
	case CEnumCore::TagName::WA_healthe://������
		sprintf(strValue,"%s","WA_healthe");
		break;
	case CEnumCore::TagName::WA_FireAttack://���湥��
		sprintf(strValue,"%s","WA_FireAttack");
		break;
	case CEnumCore::TagName::WA_ColdAttack://��������
		sprintf(strValue,"%s","WA_ColdAttack");
		break;
	case CEnumCore::TagName::WA_PoisonAttack://���ع���
		sprintf(strValue,"%s","WA_PoisonAttack");

		break;
	case CEnumCore::TagName::WA_Description://��ͣ����
		sprintf(strValue,"%s","WA_Description");
		break;
	case CEnumCore::TagName::WA_ItemPos://����λ��
		sprintf(strValue,"%s","WA_ItemPos");
		break;
	case CEnumCore::TagName::WA_SrcCharId://��Դ��ɫID
		sprintf(strValue,"%s","WA_SrcCharId");
		break;
	case CEnumCore::TagName::WA_SrcCharName://��Դ��ɫ����
		sprintf(strValue,"%s","WA_SrcCharName");
		break;
	case CEnumCore::TagName::WA_DateTime://����ʱ��
		sprintf(strValue,"%s","WA_DateTime");
		break;
	case CEnumCore::TagName::WA_DstCharId://Ŀ���ɫID
		sprintf(strValue,"%s","WA_DstCharId");
		break;
	case CEnumCore::TagName::WA_DstCharName://Ŀ���ɫ����
		sprintf(strValue,"%s","WA_DstCharName");
		break;
	case CEnumCore::TagName::WA_BindReward1://�󶨽���1
		sprintf(strValue,"%s","WA_BindReward1");
		break;
	case CEnumCore::TagName::WA_BindRewardValue1://�󶨽�����ֵ1
		sprintf(strValue,"%s","WA_BindRewardValue1");
		break;
	case CEnumCore::TagName::WA_BindReward2://�󶨽���2
		sprintf(strValue,"%s","WA_BindReward2");
		break;
	case CEnumCore::TagName::WA_BindRewardValue2://�󶨽�����ֵ1
		sprintf(strValue,"%s","WA_BindRewardValue2");
		break;
	case CEnumCore::TagName::WA_ConsumeItemTypeId://���������ƷID
		sprintf(strValue,"%s","WA_ConsumeItemTypeId");
		break;	
	case CEnumCore::TagName::WA_BoothType://��������
		sprintf(strValue,"%s","WA_BoothType");
		break;
	case CEnumCore::TagName::WA_ItemTimeLimit://��Ʒ��ʹ������
		sprintf(strValue,"%s","WA_ItemTimeLimit");
		break;	
	case CEnumCore::TagName::WA_CraftType://װ����������
		sprintf(strValue,"%s","WA_CraftType");
		break;
	case CEnumCore::TagName::WA_RecipeId://ͼֽID
		sprintf(strValue,"%s","WA_RecipeId");
		break;
	case CEnumCore::TagName::WA_MaterialId1://����ID1
		sprintf(strValue,"%s","WA_MaterialId1");
		break;	
	case CEnumCore::TagName::WA_MaterialId2://����ID2
		sprintf(strValue,"%s","WA_MaterialId2");
		break;
	case CEnumCore::TagName::WA_MaterialId3://����ID3
		sprintf(strValue,"%s","WA_MaterialId3");
		break;	
	case CEnumCore::TagName::WA_MaterialId4://����ID4
		sprintf(strValue,"%s","WA_MaterialId4");
		break;
	case CEnumCore::TagName::WA_MaterialId5://����ID5
		sprintf(strValue,"%s","WA_MaterialId5");
		break;
	case CEnumCore::TagName::WA_MaterialId6://����ID6
		sprintf(strValue,"%s","WA_MaterialId6");
		break;	
	case CEnumCore::TagName::WA_ProductId://��ƷID
		sprintf(strValue,"%s","WA_ProductId");
		break;
	case CEnumCore::TagName::WA_ProductName://��Ʒ����
		sprintf(strValue,"%s","WA_ProductName");
		break;	
	case CEnumCore::TagName::WA_ConsumeHammer://��������
		sprintf(strValue,"%s","WA_ConsumeHammer");
		break;	
	case CEnumCore::TagName::WA_ConsumeStithy://��������
		sprintf(strValue,"%s","WA_ConsumeStithy");
		break;
	case CEnumCore::TagName::WA_ConsumeMoney://���Ľ�Ǯ
		sprintf(strValue,"%s","WA_ConsumeMoney");
		break;	
	case CEnumCore::TagName::WA_OldColor://�Ŀ�ǰ��ɫ
		sprintf(strValue,"%s","WA_OldColor");
		break;
	case CEnumCore::TagName::WA_NewColor://�Ŀ׺���ɫ
		sprintf(strValue,"%s","WA_NewColor");
		break;	
	case CEnumCore::TagName::WA_OldStarCount://����ǰ����
		sprintf(strValue,"%s","WA_OldStarCount");
		break;
	case CEnumCore::TagName::WA_NewStarCount://���Ǻ�����
		sprintf(strValue,"%s","WA_NewStarCount");
		break;
	case CEnumCore::TagName::WA_GemOperation://��ʯ����
		sprintf(strValue,"%s","WA_GemOperation");
		break;	
	case CEnumCore::TagName::WA_GemType:///��ʯ����
		sprintf(strValue,"%s","WA_GemType");
		break;
	case CEnumCore::TagName::WA_GemLevel://��ʯ�ȼ�
		sprintf(strValue,"%s","WA_GemLevel");
		break;
	case CEnumCore::TagName::WA_MaterialId://ԭ����ID
		sprintf(strValue,"%s","WA_MaterialId");
		break;	
	case CEnumCore::TagName::WA_MaterialName://ԭ��������
		sprintf(strValue,"%s","WA_MaterialName");
		break;
	case CEnumCore::TagName::WA_PropItemId://�ɹ��ʵ���
		sprintf(strValue,"%s","WA_PropItemId");
		break;
	case CEnumCore::TagName::WA_ChangeType://�һ�����
		sprintf(strValue,"%s","WA_ChangeType");
		break;	
	case CEnumCore::TagName::WA_ConsumeIntegral://���Ļ���
		sprintf(strValue,"%s","WA_ConsumeIntegral");
		break;
	case CEnumCore::TagName::WA_ChangePoint://�õ��ľ������Ǯ
		sprintf(strValue,"%s","WA_ChangePoint");
		break;
	case CEnumCore::TagName::WA_GetMoney://��ý�Ǯ����
		sprintf(strValue,"%s","WA_GetMoney");
		break;	
	case CEnumCore::TagName::WA_SrcId:///��ԴID
		sprintf(strValue,"%s","WA_SrcId");
		break;
	case CEnumCore::TagName::WA_SrcName://��Դ����
		sprintf(strValue,"%s","WA_SrcName");
		break;
	case CEnumCore::TagName::WA_LoseMoney://ʧȥ��Ǯ����
		sprintf(strValue,"%s","WA_LoseMoney");
		break;	
	case CEnumCore::TagName::WA_DstId://Ŀ��ID
		sprintf(strValue,"%s","WA_DstId");
		break;
	case CEnumCore::TagName::WA_DstName://Ŀ������
		sprintf(strValue,"%s","WA_DstName");
		break;
	case CEnumCore::TagName::WA_QuestId://����ID
		sprintf(strValue,"%s","WA_QuestId");
		break;
	case CEnumCore::TagName::WA_QuestName://��������
		sprintf(strValue,"%s","WA_QuestName");
		break;	
	case CEnumCore::TagName::WA_RewardMoney://�����Ľ�Ǯ
		sprintf(strValue,"%s","WA_RewardMoney");
		break;
	case CEnumCore::TagName::WA_RewardItemId://��������Ʒ
		sprintf(strValue,"%s","WA_RewardItemId");
		break;
	case CEnumCore::TagName::WA_RewardItemName://��������Ʒ����
		sprintf(strValue,"%s","WA_RewardItemName");
		break;	
	case CEnumCore::TagName::WA_GiveItemId://ʧȥ����ƷID
		sprintf(strValue,"%s","WA_GiveItemId");
		break;
	case CEnumCore::TagName::WA_GiveItemName://ʧȥ����Ʒ����
		sprintf(strValue,"%s","WA_GiveItemName");
		break;
	case CEnumCore::TagName::WA_MailId://�ʼ�ID
		sprintf(strValue,"%s","WA_MailId");
		break;
	case CEnumCore::TagName::WA_MailMoney://��Ǯ����
		sprintf(strValue,"%s","WA_MailMoney");
		break;
	case CEnumCore::TagName::WA_Item1://��Ʒ1
		sprintf(strValue,"%s","WA_Item1");
		break;	
	case CEnumCore::TagName::WA_Item2://��Ʒ2
		sprintf(strValue,"%s","WA_Item2");
		break;
	case CEnumCore::TagName::WA_Item3://��Ʒ3
		sprintf(strValue,"%s","WA_Item3");
		break;
	case CEnumCore::TagName::WA_Item4:///��Ʒ4
		sprintf(strValue,"%s","WA_Item4");
		break;
	case CEnumCore::TagName::WA_Item5://��Ʒ5
		sprintf(strValue,"%s","WA_Item5");
		break;
	case CEnumCore::TagName::WA_Item1Count://��Ʒ1����
		sprintf(strValue,"%s","WA_Item1Count");
		break;	
	case CEnumCore::TagName::WA_Item2Count://��Ʒ2����
		sprintf(strValue,"%s","WA_Item2Count");
		break;
	case CEnumCore::TagName::WA_Item3Count://��Ʒ3����
		sprintf(strValue,"%s","WA_Item3Count");
		break;
	case CEnumCore::TagName::WA_Item4Count://��Ʒ4����
		sprintf(strValue,"%s","WA_Item4Count");
		break;
	case CEnumCore::TagName::WA_Item5Count://��Ʒ5����
		sprintf(strValue,"%s","WA_Item5Count");
		break;
	case CEnumCore::TagName::WA_MailTitle://�ʼ�����
		sprintf(strValue,"%s","WA_MailTitle");
		break;	
	case CEnumCore::TagName::WA_OpType://����
		sprintf(strValue,"%s","WA_OpType");
		break;
	case CEnumCore::TagName::WA_InstanceId://����ID
		sprintf(strValue,"%s","WA_InstanceId");
		break;
	case CEnumCore::TagName::WA_InstanceName:///��������
		sprintf(strValue,"%s","WA_InstanceName");
		break;
	case CEnumCore::TagName::WA_USERTYPE://�û����ͣ�1������ 2������
		sprintf(strValue,"%s","WA_USERTYPE");
		break;	
	case CEnumCore::TagName::WA_SkillName://��������
		sprintf(strValue,"%s","WA_SkillName");
		break;
	case CEnumCore::TagName::WA_NewPasswd://������
		sprintf(strValue,"%s","WA_NewPasswd");
		break;
	case CEnumCore::TagName::WA_ItemID://����ID
		sprintf(strValue,"%s","WA_ItemID");
		break;
	case CEnumCore::TagName::WA_TYPE://��������
		sprintf(strValue,"%s","WA_TYPE");
		break;
	case CEnumCore::TagName::WA_NewRole://�µĽ�ɫ��
		sprintf(strValue,"%s","WA_NewRole");
		break;
	case CEnumCore::TagName::WA_SkillID://����ID
		sprintf(strValue,"%s","WA_SkillID");
		break;
	case CEnumCore::TagName::WA_SkillLvl://���ܵȼ�
		sprintf(strValue,"%s","WA_SkillLvl");
		break;
	case CEnumCore::TagName::WA_cluster_id://��ID
		sprintf(strValue,"%s","WA_cluster_id");
		break;
	case CEnumCore::TagName::WA_realm_id://����ID
		sprintf(strValue,"%s","WA_realm_id");
		break;
	case CEnumCore::TagName::WA_ItemType://��������
		sprintf(strValue,"%s","WA_ItemType");
		break;
	case CEnumCore::TagName::WA_MailorName://����������
		sprintf(strValue,"%s","WA_MailorName");
		break;
	case CEnumCore::TagName::WA_ItemPrice://��Ʒ�۸�
		sprintf(strValue,"%s","WA_ItemPrice");
		break;
	case CEnumCore::TagName::WA_UNBindRewardValue1://���Ļ�ý���1
		sprintf(strValue,"%s","WA_UNBindRewardValue1");
		break;
	case CEnumCore::TagName::WA_UNBindRewardValue2://���Ļ�ý���2
		sprintf(strValue,"%s","WA_UNBindRewardValue2");
		break;
	case CEnumCore::TagName::WA_GetTime://���ʱ��
		sprintf(strValue,"%s","WA_GetTime");
		break;
	case CEnumCore::TagName::WA_Content://��ͣ����
		sprintf(strValue,"%s","WA_Content");
		break;
	case CEnumCore::TagName::WA_GuildName://��������
		sprintf(strValue,"%s","WA_GuildName");
		break;
	case CEnumCore::TagName::WA_NewProfession://תְ��ְҵ
		sprintf(strValue,"%s","WA_NewProfession");
		break;
	case CEnumCore::TagName::WA_ConsumeItem://������Ʒ
		sprintf(strValue,"%s","WA_ConsumeItem");
		break;
	case CEnumCore::TagName::WA_GuildLevel://����ȼ�
		sprintf(strValue,"%s","WA_GuildLevel");
		break;
	case CEnumCore::TagName::WA_NewGuildName://�¹�������
		sprintf(strValue,"%s","WA_NewGuildName");
		break;
	case CEnumCore::TagName::WA_GuildMemCount://��������
		sprintf(strValue,"%s","WA_GuildMemCount");
		break;
	case CEnumCore::TagName::WA_RecipeName://ͼֽ����
		sprintf(strValue,"%s","WA_RecipeName");
		break;
	case CEnumCore::TagName::WA_MaterialName1://��������1
		sprintf(strValue,"%s","WA_MaterialName1");
		break;
	case CEnumCore::TagName::WA_MaterialName2://��������2
		sprintf(strValue,"%s","WA_MaterialName2");
		break;
	case CEnumCore::TagName::WA_MaterialName3://��������3
		sprintf(strValue,"%s","WA_MaterialName3");
		break;
	case CEnumCore::TagName::WA_MaterialName4://��������4
		sprintf(strValue,"%s","WA_MaterialName4");
		break;
	case CEnumCore::TagName::WA_MaterialName5://��������5
		sprintf(strValue,"%s","WA_MaterialName5");
		break;
	case CEnumCore::TagName::WA_MaterialName6://��������6
		sprintf(strValue,"%s","WA_MaterialName6");
		break;
	case CEnumCore::TagName::WA_ItemNum://��������
		sprintf(strValue,"%s","WA_ItemNum");
		break;
	case CEnumCore::TagName::WA_LoginIP://��½IP
		sprintf(strValue,"%s","WA_LoginIP");
		break;
	case CEnumCore::TagName::WA_MemLevel://ְ��
		sprintf(strValue,"%s","WA_MemLevel");
		break;
	case CEnumCore::TagName::WA_MailTag://�Ƿ�Ⱥ���ʼ�
		sprintf(strValue,"%s","WA_MailTag");
		break;
	case CEnumCore::TagName::WA_ItemGen://����Ʒ��
		sprintf(strValue,"%s","WA_ItemGen");
		break;
	case CEnumCore::TagName::WA_MailSubject://�ʼ�����
		sprintf(strValue,"%s","WA_MailSubject");
		break;
	case CEnumCore::TagName::WA_MailContent://�ʼ�����
		sprintf(strValue,"%s","WA_MailContent");
		break;
	case CEnumCore::TagName::WA_SendMoney://���ͽ�Ǯ
		sprintf(strValue,"%s","WA_SendMoney");
		break;
	case CEnumCore::TagName::WA_ItemExpire://��ƷʱЧ
		sprintf(strValue,"%s","WA_ItemExpire");
		break;
	case CEnumCore::TagName::WA_GuildID://����ID
		sprintf(strValue,"%s","WA_GuildID");
		break;
	case CEnumCore::TagName::WA_PetUniqId://����ΨһID
		sprintf(strValue,"%s","WA_PetUniqId");
		break;
	case CEnumCore::TagName::WA_CurMoney://��ǰ��Ϸ������
		sprintf(strValue,"%s","WA_CurMoney");
		break;
	default:
		sprintf(strValue,"%s","Unknown");
		break;
	}
	return strValue;
}

// ��ʾ�������
void OperationWA::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MWA","Success"),ReadValue("MWA","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MWA","Failure"),ReadValue("MWA","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MWA","Result"),0);
	}
}

// ��ȡ����ȼ�ID
int OperationWA::GuildLevelStrToInt(CString m_str)
{
	if(!strcmp(m_str,ReadValue("MWA","GuildLvl_Member")))
	{
		return 0;
	}
	else if(!strcmp(m_str,ReadValue("MWA","GuildLvl_BCadre")))
	{
		return 1;
	}
	else if(!strcmp(m_str,ReadValue("MWA","GuildLvl_ACadre")))
	{
		return 2;
	}
	else if(!strcmp(m_str,ReadValue("MWA","GuildLvl_VChairman")))
	{
		return 3;
	}
	else if(!strcmp(m_str,ReadValue("MWA","GuildLvl_Chairman")))
	{
		return 4;
	}
	return -1;
}

// ��ȡ����ȼ�����
CString OperationWA::GuildLevelIntToStr(int iLevel)
{
	switch(iLevel)
	{
	case 0:
		return ReadValue("MWA","GuildLvl_Member");
	case 1:
		return ReadValue("MWA","GuildLvl_BCadre");
	case 2:
		return ReadValue("MWA","GuildLvl_ACadre");
	case 3:
		return ReadValue("MWA","GuildLvl_VChairman");
	case 4:
		return ReadValue("MWA","GuildLvl_Chairman");
	}
	return "";
}
