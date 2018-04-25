#include "stdafx.h"
#include "OperationJW2.h"

OperationJW2::OperationJW2()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
}
OperationJW2::~OperationJW2()
{
}
//����SOCKET
void OperationJW2::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}
// ��ȡini�ļ������ֵ
CString OperationJW2::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MJW2.ini");
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)
	{
		return (LPSTR)&strValue;
	}
	return "";
}

// ��ȡini�ļ����������
int OperationJW2::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MJW2.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//ͨ���кź������õ���Ӧ��ֵ
CString OperationJW2::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
{
	CString ItemInfo = "";
	LVCOLUMN pColumn;   
	pColumn.mask = LVCF_TEXT;   

	char buff[255];   
	pColumn.pszText = buff;   
	pColumn.cchTextMax = 255; 
	int n=listCtrlS->GetHeaderCtrl()->GetItemCount();

	//for(int i=0;i < listCtrlS->GetHeaderCtrl()->GetItemCount();i++)
	for(int i=0;i<n;i++)
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
bool OperationJW2::GetServerList()
{
	try
	{

		CSocketData socketdata;
		CPacketHead packethead;

		socketdata.InitCreate(1,2);
		char strInt[10];

		int gameID = ReadIntValue("MJW2","gameID_JW2");
		int gameDBID = ReadIntValue("MJW2","gameDBID_JW2");

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
			MessageBox(NULL,ReadValue("MCG2","Main_UI_SENDDATAERROR"),ReadValue("MCG2","ERROR"),MB_OK);
			socketdata.Destroy();
			return false;
		}
		*intJW2 = 6;

		socketdata.Destroy();
	}
	catch(...)
	{
	}
	return true;
}

//���Ͳ�ѯ����
bool OperationJW2::SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{

		CPacketHead packethead;

		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::JW2_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MCG2","Main_UI_SENDDATAERROR"),ReadValue("MJW2","ERROR"),MB_OK);
			return false;
		}
		*intJW2 = 6;
	}
	catch(...)
	{
	}
	return true;
}

//���Ͳ�ѯ����
bool OperationJW2::SendQuery(unsigned char* sendData,int allLength,CEnumCore::Msg_Category m_category,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		CPacketHead packethead;

		packethead.Create(allLength);
		packethead.AddHeader(1,m_category,m_ServiceKey,allLength);//�����ݰ����ͷ��Ϣ

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);//���첢�������Ҫ���͵����ݰ�
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))//��������
		{
			MessageBox(NULL,ReadValue("MCG2","Main_UI_SENDDATAERROR"),ReadValue("MJW2","ERROR"),MB_OK);
			return false;
		}
		

	/*	packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::JW2_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MCG2","Main_UI_SENDDATAERROR"),ReadValue("MJW2","ERROR"),MB_OK);
			return false;
		}*/
		*intJW2 = 6;
	}
	catch(...)
	{
	}
	return true;
}
//�ٴη���ͬ����Query
bool OperationJW2::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//��������
		{
			MessageBox(NULL,ReadValue("MJW2","Main_UI_SENDDATAERROR"),ReadValue("MJW2","ERROR"),MB_OK);
			return false;
		}
	}
	catch(...)
	{
	}
	return true;
}

// ���츴ѡ��
bool OperationJW2::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MAU","Result"),0);
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
		MessageBox(NULL,ReadValue("MAU","UM_Error_BuildComboBox"),ReadValue("MAU","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// �����û��б�
bool OperationJW2::BuildComboxUser(CSocketData* psocketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;
		cmbSelect->ResetContent();//��ո�ѡ�������

		m_tSvrCity = psocketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGM","Result"),0);
			return false;
		}

		for(int i=1;i<=psocketData->getQueryNum();i++)
		{
			//////m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::RealName);//��ȡҪ��ӵ���������//////UserName
			m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::UserName);//maple add
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);//���õ����������ݱ����ڸ�ѡ����
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MGM","UM_Error_BuildComboBox"),ReadValue("MGM","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// ����ListBox
bool OperationJW2::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
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
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MJW2","Error"),MB_ICONWARNING+MB_OK);
			return false;
		}

		for(int i=1;i<socketData->getColTFLVNum();i++)
		{
			m_BGS = socketData->getTLV(1,i);
			ReadValue("MJW2",tagToStr(m_BGS.m_tagName));
			listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//������
		}
		m_BGS = socketData->getTLV(1,socketData->getColTFLVNum());
		*pageCount = atoi((char *)&m_BGS.lpdata);

		listCtrlS->DeleteAllItems();
		int nRow=0;
		for(int j=1;j<=socketData->getQueryNum();j++)
		{
			for(int k=1;k<socketData->getColTFLVNum();k++)
			{
				m_ConGS = socketData->getTLV(j,k);
				if(k==1)
				{
					nRow=listCtrlS->InsertItem(j-1,(LPCTSTR)&m_ConGS.lpdata);
				}
				else
				{
					if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_Sex)//�Ա���Ҫ��������ʾ
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//�Ա�Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_Male"));//��ʾΪ��
						}
						else//�Ա�Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_Female"));//��ʾΪŮ
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_UseItem)//��ʾ�Ƿ���ʹ����
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_IsUse"));//��ʹ����
						}
						else//״̬��Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_NotUse"));//û����ʹ��
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_GOODSTYPE)//��ʾ��������
					{
						if(!strcmp("77", (LPTSTR)&m_ConGS.lpdata))//״̬ΪM�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_BuyByM"));//��ʾ��M�ҹ���
						}
						else if(!strcmp("71", (LPTSTR)&m_ConGS.lpdata))//״̬ΪG�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_BuyByG"));//��ʾ��G�ҹ���
						}
						else//����״̬
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_ALL"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_BUGLETYPE)//��ʾ��������
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ0�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_BugleTypeM"));//��ʾ��M�ҷ��͵�С����
						}
						else if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_AllBugleTypeM"));//��ʾ��M�ҷ��͵�ȫ������
						}
						else if(!strcmp("10", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ0�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_BugleTypeP"));//��ʾ�û��ַ��͵�С����
						}
						else if(!strcmp("11", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_AllBugleTypeP"));//��ʾ�û��ַ��͵�ȫ������
						}
						else//����״̬
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_Status)//��ʾ���淢������
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ0�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","NI_UI_UnSend"));//��ʾΪδ����
						}
						else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ2�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","NI_UI_Sending"));//��ʾΪ������
						}
						else//����״̬
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_LOGINTYPE)//��ʾ��½����
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ0�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","LI_UI_Login"));//��ʾΪ����
						}
						else if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","LI_UI_Logout"));//��ʾΪ�ǳ�
						}
						else//����״̬
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_ItemPos)//��ʾ��Ʒλ��
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ0�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","IM_Pos_Body"));//��ʾΪ����
						}
						else if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","IM_Pos_WuBin"));//��ʾΪ��Ʒ��
						}
						else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ2�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","IM_Pos_liWu"));//��ʾΪ������
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_MoneyType)//��ʾ��������
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ0�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,"ι������m��");//��ʾΪ����
						}
						else if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,"��������m��");//��ʾΪ��Ʒ��
						}
						else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ2�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,"����m��");//��ʾΪ������
						}
						else if(!strcmp("3", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ2�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,"��ֽm��");//��ʾΪ������
						}
						else if(!strcmp("4", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ0�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,"����g��");//��ʾΪ����
						}
						else if(!strcmp("5", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ1�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,"��������g��");//��ʾΪ��Ʒ��
						}
						else if(!strcmp("6", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ2�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,"��������M��");//��ʾΪ������
						}
						else if(!strcmp("7", (LPTSTR)&m_ConGS.lpdata))//״̬Ϊ2�Ļ�
						{
							listCtrlS->SetItemText(nRow,k-1,"����ɫm��");//��ʾΪ������
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else
					{
					    listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
					}
				}
			}
		}
	}
	catch (...)
	{
		MessageBox(NULL,ReadValue("MAU","UM_Error_BuildList"),ReadValue("MJW2","Error"),0);
	}
	return false;
}

//�Լ�����ĸ��ƺ���
void OperationJW2::CopyListInfo(CListCtrl* m_listCtrl)
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
void OperationJW2::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
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
char* OperationJW2::tagToStr(CEnumCore::TagName tag)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tag)
	{
	case CEnumCore::TagName::JW2_ACCOUNT:
		sprintf(strValue,"%s","JW2_ACCOUNT");
		break;
	case CEnumCore::TagName::JW2_UserNick:
		sprintf(strValue,"%s","JW2_UserNick");
		break;
	case CEnumCore::TagName::JW2_Reason:
		sprintf(strValue,"%s","JW2_Reason");
		break;
	case CEnumCore::TagName::JW2_BanDate:
		sprintf(strValue,"%s","JW2_BanDate");
		break;
	case CEnumCore::TagName::JW2_State:
		sprintf(strValue,"%s","JW2_State");
		break;
	case CEnumCore::TagName::JW2_ServerIP:
		sprintf(strValue,"%s","JW2_ServerIP");
		break;
	case CEnumCore::TagName::JW2_UserSN:
		sprintf(strValue,"%s","JW2_UserSN");
		break;
	case CEnumCore::TagName::JW2_GSServerIP:
		sprintf(strValue,"%s","JW2_GSServerIP");
		break;
	case CEnumCore::TagName::JW2_UserID:
		sprintf(strValue,"%s","JW2_UserID");
		break;
	case CEnumCore::TagName::JW2_Sex:
		sprintf(strValue,"%s","JW2_Sex");
		break;
	case CEnumCore::TagName::JW2_AvatarItem://����ID
		sprintf(strValue,"%s","JW2_AvatarItem");
		break;
	case CEnumCore::TagName::JW2_ExpireDate:
		sprintf(strValue,"%s","JW2_ExpireDate");
		break;
	case CEnumCore::TagName::JW2_Exp:
		sprintf(strValue,"%s","JW2_Exp");
		break;
	case CEnumCore::TagName::JW2_Money:
		sprintf(strValue,"%s","JW2_Money");
		break;
	case CEnumCore::TagName::JW2_Cash:
		sprintf(strValue,"%s","JW2_Cash");
		break;
	case CEnumCore::TagName::JW2_Level:
		sprintf(strValue,"%s","JW2_Level");
		break;
	case CEnumCore::TagName::JW2_UseItem:
		sprintf(strValue,"%s","JW2_UseItem");
		break;
	case CEnumCore::TagName::JW2_RemainCount:
		sprintf(strValue,"%s","JW2_RemainCount");
		break;
	case CEnumCore::TagName::JW2_BeginTime:
		sprintf(strValue,"%s","JW2_BeginTime");
		break;
	case CEnumCore::TagName::JW2_EndTime:
		sprintf(strValue,"%s","JW2_EndTime");
		break;
	case CEnumCore::TagName::JW2_BoardMessage:
		sprintf(strValue,"%s","JW2_BoardMessage");
		break;
	case CEnumCore::TagName::JW2_TaskID:
		sprintf(strValue,"%s","JW2_TaskID");
		break;
	case CEnumCore::TagName::JW2_Status:
		sprintf(strValue,"%s","JW2_Status");
		break;
	case CEnumCore::TagName::JW2_Interval:
		sprintf(strValue,"%s","JW2_Interval");
		break;
	case CEnumCore::TagName::JW2_UseTime:
		sprintf(strValue,"%s","JW2_UseTime");
		break;
	case CEnumCore::TagName::JW2_POWER:
		sprintf(strValue,"%s","JW2_POWER");
		break;
	case CEnumCore::TagName::JW2_GoldMedal:
		sprintf(strValue,"%s","JW2_GoldMedal");
		break;
	case CEnumCore::TagName::JW2_SilverMedal:
		sprintf(strValue,"%s","JW2_SilverMedal");
		break;
	case CEnumCore::TagName::JW2_CopperMedal:
		sprintf(strValue,"%s","JW2_CopperMedal");
		break;
	case CEnumCore::TagName::JW2_Region:
		sprintf(strValue,"%s","JW2_Region");
		break;
	case CEnumCore::TagName::JW2_QQ:
		sprintf(strValue,"%s","JW2_QQ");
		break;
	case CEnumCore::TagName::JW2_PARA:
		sprintf(strValue,"%s","JW2_PARA");
		break;
	case CEnumCore::TagName::JW2_ATONCE:
		sprintf(strValue,"%s","JW2_ATONCE");
		break;
	case CEnumCore::TagName::JW2_BOARDSN:
		sprintf(strValue,"%s","JW2_BOARDSN");
		break;
	case CEnumCore::TagName::JW2_BUGLETYPE:
		sprintf(strValue,"%s","JW2_BUGLETYPE");
		break;
	case CEnumCore::TagName::JW2_Chapter:
		sprintf(strValue,"%s","JW2_Chapter");
		break;
	case CEnumCore::TagName::JW2_CurStage:
		sprintf(strValue,"%s","JW2_CurStage");
		break;
	case CEnumCore::TagName::JW2_MaxStage:
		sprintf(strValue,"%s","JW2_MaxStage");
		break;
	case CEnumCore::TagName::JW2_Stage0:
		sprintf(strValue,"%s","JW2_Stage0");
		break;
	case CEnumCore::TagName::JW2_Stage1:
		sprintf(strValue,"%s","JW2_Stage1");
		break;
	case CEnumCore::TagName::JW2_Stage2:
		sprintf(strValue,"%s","JW2_Stage2");
		break;
	case CEnumCore::TagName::JW2_Stage3:
		sprintf(strValue,"%s","JW2_Stage3");
		break;
	case CEnumCore::TagName::JW2_Stage4:
		sprintf(strValue,"%s","JW2_Stage4");
		break;
	case CEnumCore::TagName::JW2_Stage5:
		sprintf(strValue,"%s","JW2_Stage5");
		break;
	case CEnumCore::TagName::JW2_Stage6:
		sprintf(strValue,"%s","JW2_Stage6");
		break;
	case CEnumCore::TagName::JW2_Stage7:
		sprintf(strValue,"%s","JW2_Stage7");
		break;
	case CEnumCore::TagName::JW2_Stage8:
		sprintf(strValue,"%s","JW2_Stage8");
		break;
	case CEnumCore::TagName::JW2_Stage9:
		sprintf(strValue,"%s","JW2_Stage9");
		break;
	case CEnumCore::TagName::JW2_Stage10:
		sprintf(strValue,"%s","JW2_Stage10");
		break;
	case CEnumCore::TagName::JW2_Stage11:
		sprintf(strValue,"%s","JW2_Stage11");
		break;
	case CEnumCore::TagName::JW2_Stage12:
		sprintf(strValue,"%s","JW2_Stage12");
		break;
	case CEnumCore::TagName::JW2_Stage13:
		sprintf(strValue,"%s","JW2_Stage13");
		break;
	case CEnumCore::TagName::JW2_Stage14:
		sprintf(strValue,"%s","JW2_Stage14");
		break;
	case CEnumCore::TagName::JW2_Stage15:
		sprintf(strValue,"%s","JW2_Stage15");
		break;
	case CEnumCore::TagName::JW2_Stage16:
		sprintf(strValue,"%s","JW2_Stage16");
		break;
	case CEnumCore::TagName::JW2_Stage17:
		sprintf(strValue,"%s","JW2_Stage17");
		break;
	case CEnumCore::TagName::JW2_Stage18:
		sprintf(strValue,"%s","JW2_Stage18");
		break;
	case CEnumCore::TagName::JW2_Stage19:
		sprintf(strValue,"%s","JW2_Stage19");
		break;
	case CEnumCore::TagName::JW2_BUYSN:
		sprintf(strValue,"%s","JW2_BUYSN");
		break;
	case CEnumCore::TagName::JW2_GOODSTYPE:
		sprintf(strValue,"%s","JW2_GOODSTYPE");
		break;
	case CEnumCore::TagName::JW2_RECESN:
		sprintf(strValue,"%s","JW2_RECESN");
		break;
	case CEnumCore::TagName::JW2_GOODSINDEX:
		sprintf(strValue,"%s","JW2_GOODSINDEX");
		break;
	case CEnumCore::TagName::JW2_BUYDATE:
		sprintf(strValue,"%s","JW2_BUYDATE");
		break;
	case CEnumCore::TagName::JW2_RECEID://�����˵�ID�������ͬ�Ǳ��ˣ�
		sprintf(strValue,"%s","JW2_RECEID");
		break;
	case CEnumCore::TagName::JW2_AvatarItemName://��������
		sprintf(strValue,"%s","JW2_AvatarItemName");
		break;
	case CEnumCore::TagName::JW2_MALESN://����SN
		sprintf(strValue,"%s","JW2_MALESN");
		break;
	case CEnumCore::TagName::JW2_MALEUSERNAME://�����û���
		sprintf(strValue,"%s","JW2_MALEUSERNAME");
		break;
	case CEnumCore::TagName::JW2_MALEUSERNICK://�����ǳ�
		sprintf(strValue,"%s","JW2_MALEUSERNICK");
		break;
	case CEnumCore::TagName::JW2_FEMAILESN://Ů��SN
		sprintf(strValue,"%s","JW2_FEMAILESN");
		break;
	case CEnumCore::TagName::JW2_FEMALEUSERNAME://Ů���û���
		sprintf(strValue,"%s","JW2_FEMALEUSERNAME");
		break;
	case CEnumCore::TagName::JW2_FEMAILEUSERNICK://Ů���ǳ�
		sprintf(strValue,"%s","JW2_FEMAILEUSERNICK");
		break;
	case CEnumCore::TagName::JW2_WEDDINGDATE://���ʱ��
		sprintf(strValue,"%s","JW2_WEDDINGDATE");
		break;
	case CEnumCore::TagName::JW2_UNWEDDINGDATE://���ʱ��
		sprintf(strValue,"%s","JW2_UNWEDDINGDATE");
		break;
	case CEnumCore::TagName::JW2_WEDDINGNAME://��������
		sprintf(strValue,"%s","JW2_WEDDINGNAME");
		break;
	case CEnumCore::TagName::JW2_WEDDINGVOW://��������
		sprintf(strValue,"%s","JW2_WEDDINGVOW");
		break;
	case CEnumCore::TagName::JW2_RINGLEVEL://��ָ�ȼ�
		sprintf(strValue,"%s","JW2_RINGLEVEL");
		break;
	case CEnumCore::TagName::JW2_REDHEARTNUM://��������
		sprintf(strValue,"%s","JW2_REDHEARTNUM");
		break;
	case CEnumCore::TagName::JW2_WEDDINGNO://�������
		sprintf(strValue,"%s","JW2_WEDDINGNO");
		break;
	case CEnumCore::TagName::JW2_CONFIRMSN://��֤��SN
		sprintf(strValue,"%s","JW2_CONFIRMSN");
		break;
	case CEnumCore::TagName::JW2_CONFIRMUSERNAME://��֤���û���
		sprintf(strValue,"%s","JW2_CONFIRMUSERNAME");
		break;
	case CEnumCore::TagName::JW2_CONFIRMUSERNICK://��֤���ǳ�
		sprintf(strValue,"%s","JW2_CONFIRMUSERNICK");
		break;
	case CEnumCore::TagName::JW2_COUPLEDATE://��������
		sprintf(strValue,"%s","JW2_COUPLEDATE");
		break;
	case CEnumCore::TagName::JW2_KISSNUM://kiss����
		sprintf(strValue,"%s","JW2_KISSNUM");
		break;
	case CEnumCore::TagName::JW2_LASTKISSDATE://���һ��Kissʱ��
		sprintf(strValue,"%s","JW2_LASTKISSDATE");
		break;
	case CEnumCore::TagName::JW2_BREAKDATE://����ʱ��
		sprintf(strValue,"%s","JW2_BREAKDATE");
		break;
	case CEnumCore::TagName::JW2_CMBREAKDATE://ȷ�Ϸ���ʱ��
		sprintf(strValue,"%s","JW2_CMBREAKDATE");
		break;
	case CEnumCore::TagName::JW2_BREAKSN://���SN
		sprintf(strValue,"%s","JW2_BREAKSN");
		break;
	case CEnumCore::TagName::JW2_BREAKUSERNAME://����û���
		sprintf(strValue,"%s","JW2_BREAKUSERNAME");
		break;
	case CEnumCore::TagName::JW2_BREAKUSERNICK://����ǳ�
		sprintf(strValue,"%s","JW2_BREAKUSERNICK");
		break;
	case CEnumCore::TagName::JW2_LASTLOGINDATE://����½ʱ��
		sprintf(strValue,"%s","JW2_LASTLOGINDATE");
		break;
	case CEnumCore::TagName::JW2_REGISTDATE://����ʱ��
		sprintf(strValue,"%s","JW2_REGISTDATE");
		break;
	case CEnumCore::TagName::JW2_FCMSTATUS://������״̬
		sprintf(strValue,"%s","JW2_FCMSTATUS");
		break;
	case CEnumCore::TagName::JW2_FAMILYID://����ID
		sprintf(strValue,"%s","JW2_FAMILYID");
		break;
	case CEnumCore::TagName::JW2_FAMILYNAME://��������
		sprintf(strValue,"%s","JW2_FAMILYNAME");
		break;
	case CEnumCore::TagName::JW2_DUTYID://ְҵ��
		sprintf(strValue,"%s","JW2_DUTYID");
		break;
	case CEnumCore::TagName::JW2_DUTYNAME://ְҵ��
		sprintf(strValue,"%s","JW2_DUTYNAME");
		break;
	case CEnumCore::TagName::JW2_ATTENDTIME://����ʱ��
		sprintf(strValue,"%s","JW2_ATTENDTIME");
		break;
	case CEnumCore::TagName::JW2_COUPLESN://�������
		sprintf(strValue,"%s","JW2_COUPLESN");
		break;
	case CEnumCore::TagName::JW2_CREATETIME://����ʱ��
		sprintf(strValue,"%s","JW2_CREATETIME");
		break;
	case CEnumCore::TagName::JW2_CNT://����
		sprintf(strValue,"%s","JW2_CNT");
		break;
	case CEnumCore::TagName::JW2_POINT://����
		sprintf(strValue,"%s","JW2_POINT");
		break;
	case CEnumCore::TagName::JW2_LOGINTYPE://����0���룬1�ǳ�
		sprintf(strValue,"%s","JW2_LOGINTYPE");
		break;
	case CEnumCore::TagName::JW2_TIME://ʱ��
		sprintf(strValue,"%s","JW2_TIME");
		break;
	case CEnumCore::TagName::JW2_IP://IP��ַ
		sprintf(strValue,"%s","JW2_IP");
		break;
	case CEnumCore::TagName::JW2_ItemPos://��Ʒλ��
		sprintf(strValue,"JW2_ItemPos");
		break;
	case CEnumCore::TagName::JW2_MailTitle://��Ʒ����
		sprintf(strValue,"JW2_MailTitle");
		break;
	case CEnumCore::TagName::JW2_MailContent://�ʼ�����
		sprintf(strValue,"JW2_MailContent");
		break;
	case CEnumCore::TagName::JW2_ItemNo://��Ʒ���
		sprintf(strValue,"JW2_ItemNo");
		break;
	case CEnumCore::TagName::JW2_Repute://����
		sprintf(strValue,"JW2_Repute");
		break;
	case CEnumCore::TagName::JW2_NowTitle://�ƺ�
		sprintf(strValue,"JW2_NowTitle");
		break;
	case CEnumCore::TagName::JW2_FamilyLevel://�ȼ�
		sprintf(strValue,"JW2_FamilyLevel");
		break;
	case CEnumCore::TagName::JW2_AttendRank://��������
		sprintf(strValue,"JW2_AttendRank");
		break;
	case CEnumCore::TagName::JW2_MoneyRank://�Ƹ�����
		sprintf(strValue,"JW2_MoneyRank");
		break;
	case CEnumCore::TagName::JW2_PowerRank://ʵ������
		sprintf(strValue,"JW2_PowerRank");
		break;
	case CEnumCore::TagName::JW2_ItemCode://����ID
		sprintf(strValue,"JW2_ItemCode");
		break;
	case CEnumCore::TagName::JW2_ItemName://��������
		sprintf(strValue,"JW2_ItemName");
		break;
	case CEnumCore::TagName::JW2_Productid://��ƷID
		sprintf(strValue,"JW2_Productid");
		break;
	case CEnumCore::TagName::JW2_ProductName://��Ʒ����
		sprintf(strValue,"JW2_ProductName");
		break;
	case CEnumCore::TagName::JW2_FamilyPoint://�������
		sprintf(strValue,"JW2_FamilyPoint");
		break;
	case CEnumCore::TagName::JW2_PetSn://����ID
		sprintf(strValue,"JW2_PetSn");
		break;
	case CEnumCore::TagName::JW2_PetName://��������
		sprintf(strValue,"JW2_PetName");
		break;
	case CEnumCore::TagName::JW2_PetNick://�����Զ�������
		sprintf(strValue,"JW2_PetNick");
		break;
	case CEnumCore::TagName::JW2_PetLevel://����ȼ�
		sprintf(strValue,"JW2_PetLevel");
		break;
	case CEnumCore::TagName::JW2_PetExp://���ﾭ��
		sprintf(strValue,"JW2_PetExp");
		break;
	case CEnumCore::TagName::JW2_PetEvol://��������
		sprintf(strValue,"JW2_PetEvol");
		break;
	case CEnumCore::TagName::JW2_MailSn://���к�
		sprintf(strValue,"JW2_MailSn");
		break;
	case CEnumCore::TagName::JW2_SendNick://�������ǳ�
		sprintf(strValue,"JW2_SendNick");
		break;
	case CEnumCore::TagName::JW2_SendDate://��������
		sprintf(strValue,"JW2_SendDate");
		break;
	case CEnumCore::TagName::JW2_Num://����
		sprintf(strValue,"JW2_Num");
		break;
	case CEnumCore::TagName::JW2_Rate://��Ů����
		sprintf(strValue,"JW2_Rate");
		break;
	case CEnumCore::TagName::JW2_ShaikhNick://�峤����
		sprintf(strValue,"JW2_ShaikhNick");
		break;
	case CEnumCore::TagName::JW2_SubFamilyName://������������
		sprintf(strValue,"JW2_SubFamilyName");
		break;
	case CEnumCore::TagName::JW2_MoneyType://��������
		sprintf(strValue,"JW2_MoneyType");
		break;
	case CEnumCore::TagName::JW2_BeforeCash://����ǰǮ
		sprintf(strValue,"JW2_BeforeCash");
		break;
	case CEnumCore::TagName::JW2_AfterCash://����ǰǮ
		sprintf(strValue,"JW2_AfterCash");
		break;
	case CEnumCore::TagName::JW2_ProductPrice://���ߵ���
		sprintf(strValue,"JW2_ProductPrice");
		break;
	case CEnumCore::TagName::JW2_ServerName://����������
		sprintf(strValue,"JW2_ServerName");
		break;
	case CEnumCore::TagName::UserName:
		sprintf(strValue,"UserName");
		break;
	default:
		sprintf(strValue,"%s","UnKnown");
		break;
	}
	return strValue;
}

// ��ʾ�������
void OperationJW2::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MJW2","Success"),ReadValue("MJW2","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MJW2","Failure"),ReadValue("MJW2","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MJW2","Result"),0);
	}
}
