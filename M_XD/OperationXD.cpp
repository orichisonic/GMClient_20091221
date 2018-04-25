#include "stdafx.h"
#include "OperationXD.h"
#include ".\OperationXD.h"

OperationXD::OperationXD()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//将全局变量置零
	intXD = NULL;
}
OperationXD::~OperationXD()
{
	selfSocket.MyDestory();
	packethead.Destroy();
	if(intXD != NULL)
	{
		intXD = NULL;
	}
}

//设置SOCKET
void OperationXD::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// 读取ini文件里面的值
CString OperationXD::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MXD.ini");
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)
	{
		return (LPSTR)&strValue;
	}
	return "";
}

// 读取ini文件里面的数字
int OperationXD::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MXD.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//通过行号和列名得到相应的值
CString OperationXD::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
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

// 获取游戏服务器列表
bool OperationXD::GetServerList()
{
	try
	{
		//MessageBox(NULL,"EE","",0);
		CSocketData socketdata;
		socketdata.InitCreate(1,2);
		char strInt[10];

		int gameID = ReadIntValue("MXD","gameID_XD");
		int gameDBID = ReadIntValue("MXD","gameDBID_XD");

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
			MessageBox(NULL,ReadValue("MXD","Main_UI_SENDDATAERROR"),ReadValue("MXD","ERROR"),MB_OK);
			socketdata.Destroy();
			return false;
		}
		*intXD = 8;
		
		socketdata.Destroy();		
	}
	catch(...)
	{
	}
	return true;
}

//发送查询请求
bool OperationXD::SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		//MessageBox(NULL,"test","",0);
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::XDJG_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		//selfSocket.SetSocket(theApp.mSocket);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MXD","Main_UI_SENDDATAERROR"),ReadValue("MXD","ERROR"),MB_OK);
			return false;
		}
		*intXD = 8;
	}
	catch(...)
	{
	}
	return true;
}

//再次发送同样的Query
bool OperationXD::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//发送数据
		{
			MessageBox(NULL,ReadValue("MXD","Main_UI_SENDDATAERROR"),ReadValue("MXD","ERROR"),MB_OK);
			return false;
		}
	}
	catch(...)
	{
	}
	return true;
}

// 构造复选框
bool OperationXD::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MXD","Result"),0);
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
		MessageBox(NULL,ReadValue("MXD","UM_Error_BuildComboBox"),ReadValue("MXD","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

//构造复选框
bool OperationXD::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect,int nItem)
{
	try
	{
		CGlobalStruct::TFLV m_TFLV;
		m_TFLV.nIndex=0;

		m_TFLV = socketData->getTLV(1,1);
		if(m_TFLV.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_TFLV.lpdata,ReadValue("MXD","Result"),0);
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
		MessageBox(NULL,ReadValue("MXD","UM_Error_BuildComboBox"),ReadValue("MXD","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// 构造复选框
bool OperationXD::BuildComboxs(CSocketData* socketData,CComboBox* cmbSelect,CEnumCore::TagName tag)
{
	try
	{
		CGlobalStruct::TFLV m_TFLV;
		m_TFLV.nIndex=0;

		m_TFLV = socketData->getTLV(1,1);
		if(m_TFLV.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_TFLV.lpdata,ReadValue("MXD","Result"),0);
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
		MessageBox(NULL,ReadValue("MXD","UM_Error_BuildComboBox"),ReadValue("MXD","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// 构造ListBox
bool OperationXD::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
{
	try
	{
		LONG lStyle;
		lStyle = GetWindowLong(listCtrlS->m_hWnd, GWL_STYLE);//获取当前窗口style
		lStyle &= ~LVS_TYPEMASK; //清除显示方式位
		lStyle |= LVS_REPORT; //设置style
		SetWindowLong(listCtrlS->m_hWnd, GWL_STYLE, lStyle);//设置style

		DWORD dwStyle = listCtrlS->GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
		dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
		listCtrlS->SetExtendedStyle(dwStyle); //设置扩展风格

		while(listCtrlS->DeleteColumn(0)){}		
		CGlobalStruct::TFLV m_BGS,m_ConGS;

		m_BGS = socketData->getTLV(1,1);
		if(m_BGS.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MXD","Error"),MB_ICONWARNING+MB_OK);
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
				ReadValue("MXD",tagToStr(m_BGS.m_tagName));
				listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//插入列
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
						if(m_ConGS.m_tagName == CEnumCore::TagName::XDJG_Status)
						{
							CString temp;
							temp.Format("%s",(LPCTSTR)m_ConGS.lpdata);
							//MessageBox(NULL,(LPCTSTR)&m_ConGS.lpdata,"",0);
							if(temp.Find('0')>=0)
							{
                             listCtrlS->SetItemText(nRow,k-1,"未发送");
							}
							else if(temp.Find('1')>=0)
							{
								listCtrlS->SetItemText(nRow,k-1,"已完成");
							}
							else if(temp.Find('2')>=0)
							{
								listCtrlS->SetItemText(nRow,k-1,"正在发送");
							}
							else
							{

                             listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
							}
                       // listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
						else
						{
                           listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}

				}
				//else
				//{
				//	if(m_ConGS.m_tagName == CEnumCore::TagName::PageCount)
				//	{
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_GUILDPOWERLEVEL)
				//	{
				//		listCtrlS->SetItemText(nRow,k-1,GuildLevelIntToStr(atoi((LPCTSTR)&m_ConGS.lpdata)));
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_QUESTTYPE)//任务类型
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//类型为1的话
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","UIC_ITEM_Finished"));//显示为已完成
				//		}
				//		else//类型不为1的话
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","UIC_ITEM_Received"));//显示为已接
				//		}
				//	}
				//	else if((m_ConGS.m_tagName == CEnumCore::TagName::PAL_NPCTRADE) || (m_ConGS.m_tagName == CEnumCore::TagName::PAL_USERTRADE))
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","UIC_Code_Can"));
				//		}
				//		else
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","UIC_Code_Cant"));
				//		}
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_ITEMMALLGOODS)
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","UIC_Code_Is"));
				//		}
				//		else
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","UIC_Code_Isnt"));
				//		}
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_STATUS)
				//	{
				//		if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","NI_UI_UnSend"));
				//		}
				//		else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","NI_UI_Sending"));
				//		}
				//		else
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","NI_UI_Sended"));
				//		}
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_MONEYTYPE)
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","RM_ITEM_MONEYINBANK"));
				//		}
				//		else
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","RM_ITEM_PERSONALMONEY"));
				//		}
				//	}
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_LOGINIP)//登入IP
				//	{
				//		if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))//IP地址为空
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MXD","UIC_Code_NotOnline"));//显示为不在线
				//		}
				//		else//IP地址不为空
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
		MessageBox(NULL,ReadValue("MXD","UM_Error_BuildList"),ReadValue("MXD","Error"),0);
	}
	return false;
}

//自己定义的复制函数
void OperationXD::CopyListInfo(CListCtrl* m_listCtrl)
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
	CListCtrl *listctrl;       //CListCtrl控件指针
	int isub;        //l列号
	int seq;        //1为升序，0为降序
}; 

//排序回调函数
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

//自己定义的排序函数
void OperationXD::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	MyData *tmpData=new MyData;

	tmpData->listctrl = m_listCtrl;
	tmpData->isub=pNMListView->iSubItem;

	int sortnum=(int)GetProp(m_listCtrl->GetSafeHwnd(),"排序列号");
	int sortasc=(int)GetProp(m_listCtrl->GetSafeHwnd(),"排序顺序");

	if(sortnum==pNMListView->iSubItem){
		sortasc=(sortasc+1)%2;
		SetProp(m_listCtrl->GetSafeHwnd(),"排序顺序",(HANDLE)sortasc);
	}
	SetProp(m_listCtrl->GetSafeHwnd(),"排序列号",(HANDLE)pNMListView->iSubItem);
	tmpData->seq=sortasc;//选择升序还是降序
	m_listCtrl->SortItems(SortListProc,(LPARAM)tmpData);//进行排序

	*pResult = 0;
}

// TagName转换成CString类型
char* OperationXD::tagToStr(CEnumCore::TagName tag)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tag)
	{
	case CEnumCore::TagName::XDJG_Account:
		sprintf(strValue,"%s","XDJG_Account");
		break;
	case CEnumCore::TagName::XDJG_AccountID:
		sprintf(strValue,"%s","XDJG_AccountID");
		break;
	case CEnumCore::TagName::XDJG_BeginDate:
		sprintf(strValue,"%s","XDJG_BeginDate");
		break;
	case CEnumCore::TagName::XDJG_BoardMessage:
		sprintf(strValue,"%s","XDJG_BoardMessage");
		break;
	case CEnumCore::TagName::XDJG_EndDate:
		sprintf(strValue,"%s","XDJG_EndDate");
		break;
	case CEnumCore::TagName::XDJG_ExecTimes:
		sprintf(strValue,"%s","XDJG_ExecTimes");
		break;
	case CEnumCore::TagName::XDJG_Exp:
		sprintf(strValue,"%s","XDJG_Exp");
		break;
	case CEnumCore::TagName::XDJG_ServerName:
		sprintf(strValue,"%s","XDJG_ServerName");
		break;
	case CEnumCore::TagName::XDJG_Interval:
		sprintf(strValue,"%s","XDJG_Interval");
		break;
	case CEnumCore::TagName::XDJG_Level:
		sprintf(strValue,"%s","XDJG_Level");
		break;
	case CEnumCore::TagName::XDJG_Money:
		sprintf(strValue,"%s","XDJG_Money");
		break;
	case CEnumCore::TagName::XDJG_NextTime:
		sprintf(strValue,"%s","XDJG_NextTime");
		break;
	case CEnumCore::TagName::XDJG_CharacterID:
		sprintf(strValue,"%s","XDJG_CharacterID");
		break;
	case CEnumCore::TagName::XDJG_Onoff:
		sprintf(strValue,"%s","XDJG_Onoff");
		break;
	case CEnumCore::TagName::XDJG_Position:
		sprintf(strValue,"%s","XDJG_Position");
		break;
	case CEnumCore::TagName::XDJG_Profession:
		sprintf(strValue,"%s","XDJG_Profession");
		break;
	case CEnumCore::TagName::XDJG_Repeat:
		sprintf(strValue,"%s","XDJG_RepeatE");
		break;
	case CEnumCore::TagName::XDJG_SceneInstanceID:
		sprintf(strValue,"%s","XDJG_SceneInstanceID");
		break;
	case CEnumCore::TagName::XDJG_SceneTypeID:
		sprintf(strValue,"%s","XDJG_SceneTypeID");
		break;
	case CEnumCore::TagName::XDJG_ServerIP:
		sprintf(strValue,"%s","XDJG_ServerIP");
		break;
	case CEnumCore::TagName::XDJG_Sex:
		sprintf(strValue,"%s","XDJG_Sex");
		break;
	case CEnumCore::TagName::XDJG_StartTime:
		sprintf(strValue,"%s","XDJG_StartTime");
		break;
	case CEnumCore::TagName::XDJG_EndTime:
		sprintf(strValue,"%s","XDJG_EndTime");
		break;
	case CEnumCore::TagName::XDJG_TaskID:
		sprintf(strValue,"%s","XDJG_TaskID");
		break;
	case CEnumCore::TagName::XDJG_Time:
		sprintf(strValue,"%s","XDJG_Time");
		break;
	case CEnumCore::TagName::XDJG_Character:
		sprintf(strValue,"%s","XDJG_Character");
		break;
	case CEnumCore::TagName::XDJG_BeginTime:
		sprintf(strValue,"%s","XDJG_BeginTime");
		break;
	case CEnumCore::TagName::XDJG_Status:
		sprintf(strValue,"%s","XDJG_Status");
		break;
	case CEnumCore::TagName::XDJG_BANREASON:
		sprintf(strValue,"%s","XDJG_BANREASON");
		break;
	case CEnumCore::TagName::XDJG_BANTIME:
		sprintf(strValue,"%s","XDJG_BANTIME");
		break;
	case CEnumCore::TagName::XDJG_BANBEGINTIME:
		sprintf(strValue,"%s","XDJG_BANBEGINTIME");
		break;
	case CEnumCore::TagName::XDJG_BANENDTIME:
		sprintf(strValue,"%s","XDJG_BANENDTIME");
		break;
	case CEnumCore::TagName::XDJG_BANTYPE:
		sprintf(strValue,"%s","XDJG_BANTYPE");
		break;
	case CEnumCore::TagName::XDJG_Strength:
		sprintf(strValue,"%s","XDJG_Strength");
		break;
	case CEnumCore::TagName::XDJG_Agility:
		sprintf(strValue,"%s","XDJG_Agility");
		break;
	case CEnumCore::TagName::XDJG_Stamina:
		sprintf(strValue,"%s","XDJG_Stamina");
		break;
	case CEnumCore::TagName::XDJG_Spirit:
		sprintf(strValue,"%s","XDJG_Spirit");
		break;
	case CEnumCore::TagName::XDJG_Magic:
		sprintf(strValue,"%s","XDJG_Magic");
		break;
	case CEnumCore::TagName::XDJG_NearPa:
		sprintf(strValue,"%s","XDJG_NearPa");
		break;
	case CEnumCore::TagName::XDJG_FarPa:
		sprintf(strValue,"%s","XDJG_FarPa");
		break;
	case CEnumCore::TagName::XDJG_SuperAttack:
		sprintf(strValue,"%s","XDJG_SuperAttack");
		break;
	case CEnumCore::TagName::XDJG_PerfectRate:
		sprintf(strValue,"%s","XDJG_PerfectRate");
		break;
	case CEnumCore::TagName::XDJG_StrengthCritRate:
		sprintf(strValue,"%s","XDJG_StrengthCritRate");
		break;
	case CEnumCore::TagName::XDJG_SpiritCritRate:
		sprintf(strValue,"%s","XDJG_SpiritCritRate");
		break;
	case CEnumCore::TagName::XDJG_IsOnLine:
		sprintf(strValue,"%s","XDJG_IsOnLine");
		break;
	case CEnumCore::TagName::XDJG_Armor:
		sprintf(strValue,"%s","XDJG_Armor");
		break;
	case CEnumCore::TagName::XDJG_DodgeRate:
		sprintf(strValue,"%s","XDJG_DodgeRate");
		break;
	case CEnumCore::TagName::XDJG_WardRate:
		sprintf(strValue,"%s","XDJG_WardRate");
		break;
	case CEnumCore::TagName::XDJG_ParryRate:
		sprintf(strValue,"%s","XDJG_ParryRate");
		break;
	case CEnumCore::TagName::XDJG_FatalResistanceRate:
		sprintf(strValue,"%s","XDJG_FatalResistanceRate");
		break;
	case CEnumCore::TagName::XDJG_FlameResistance:
		sprintf(strValue,"%s","XDJG_FlameResistance");
		break;
	case CEnumCore::TagName::XDJG_ThunderResistance:
		sprintf(strValue,"%s","XDJG_ThunderResistance");
		break;
	case CEnumCore::TagName::XDJG_FrostResistance:
		sprintf(strValue,"%s","XDJG_FrostResistance");
		break;
	case CEnumCore::TagName::XDJG_CorrosionResistance:
		sprintf(strValue,"%s","XDJG_CorrosionResistance");
		break;
	case CEnumCore::TagName::XDJG_EnergyResistance:
		sprintf(strValue,"%s","XDJG_EnergyResistance");
		break;
	case CEnumCore::TagName::XDJG_SpiritResistance:
		sprintf(strValue,"%s","XDJG_SpiritResistance");
		break;
	case CEnumCore::TagName::XDJG_PK:
		sprintf(strValue,"%s","XDJG_PK");
		break;
	case CEnumCore::TagName::XDJG_GoodEvil:
		sprintf(strValue,"%s","XDJG_GoodEvil");
		break;
	case CEnumCore::TagName::XDJG_RedNameTime:
		sprintf(strValue,"%s","XDJG_RedNameTime");
		break;
	case CEnumCore::TagName::XDJG_RoleID1:
		sprintf(strValue,"%s","XDJG_RoleID1");
		break;
	case CEnumCore::TagName::XDJG_RoleID2:
		sprintf(strValue,"%s","XDJG_RoleID2");
		break;
	case CEnumCore::TagName::XDJG_RoleID3:
		sprintf(strValue,"%s","XDJG_RoleID3");
		break;
	case CEnumCore::TagName::XDJG_RoleID4:
		sprintf(strValue,"%s","XDJG_RoleID4");
		break;
	case CEnumCore::TagName::XDJG_RoleID5:
		sprintf(strValue,"%s","XDJG_RoleID5");
		break;
	case CEnumCore::TagName::XDJG_RoleID6:
		sprintf(strValue,"%s","XDJG_RoleID6");
		break;
	case CEnumCore::TagName::XDJG_RoleID7:
		sprintf(strValue,"%s","XDJG_RoleID7");
		break;
	case CEnumCore::TagName::XDJG_RoleID8:
		sprintf(strValue,"%s","XDJG_RoleID8");
		break;
	case CEnumCore::TagName::XDJG_LifeSkill1:
		sprintf(strValue,"%s","XDJG_LifeSkill1");
		break;
	case CEnumCore::TagName::XDJG_LifeSkill2:
		sprintf(strValue,"%s","XDJG_LifeSkill2");
		break;
	case CEnumCore::TagName::XDJG_LifeSkill3:
		sprintf(strValue,"%s","XDJG_LifeSkill3");
		break;
	case CEnumCore::TagName::XDJG_LifeSkill4:
		sprintf(strValue,"%s","XDJG_LifeSkill4");
		break;
	case CEnumCore::TagName::XDJG_LifeSkill5:
		sprintf(strValue,"%s","XDJG_LifeSkill5");
		break;
	case CEnumCore::TagName::XDJG_LifeSkill6:
		sprintf(strValue,"%s","XDJG_LifeSkill6");
		break;
	case CEnumCore::TagName::XDJG_LifeSkill7:
		sprintf(strValue,"%s","XDJG_LifeSkill7");
		break;
	case CEnumCore::TagName::XDJG_LifeSkill8:
		sprintf(strValue,"%s","XDJG_LifeSkill8");
		break;
	case CEnumCore::TagName::XDJG_SkillID:
		sprintf(strValue,"%s","XDJG_SkillID");
		break;
	case CEnumCore::TagName::XDJG_ItemID:
		sprintf(strValue,"%s","XDJG_ItemID");
		break;
	case CEnumCore::TagName::XDJG_ItemNum:
		sprintf(strValue,"%s","XDJG_ItemNum");
		break;
	case CEnumCore::TagName::XDJG_QueryIP:
		sprintf(strValue,"%s","XDJG_QueryIP");
		break;
	case CEnumCore::TagName::XDJG_QueryType:
		sprintf(strValue,"%s","XDJG_QueryType");
		break;
	case CEnumCore::TagName::XDJG_LoginType:
		sprintf(strValue,"%s","XDJG_LoginType");
		break;
	case CEnumCore::TagName::XDJG_LogTime:
		sprintf(strValue,"%s","XDJG_LogTime");
		break;
	case CEnumCore::TagName::XDJG_LogInOutIP:
		sprintf(strValue,"%s","XDJG_LogInOutIP");
		break;
	case CEnumCore::TagName::XDJG_ItemName:
		sprintf(strValue,"%s","XDJG_ItemName");
		break;
	case CEnumCore::TagName::XDJG_TempItemID:
		sprintf(strValue,"%s","XDJG_TempItemID");
		break;
	case CEnumCore::TagName::XDJG_AccountBuyer:
		sprintf(strValue,"%s","XDJG_AccountBuyer");
		break;
	case CEnumCore::TagName::XDJG_RoleBuyer:
		sprintf(strValue,"%s","XDJG_RoleBuyer");
		break;
	case CEnumCore::TagName::XDJG_AccountReceiver:
		sprintf(strValue,"%s","XDJG_AccountReceiver");
		break;
	case CEnumCore::TagName::XDJG_RoleReceiver:
		sprintf(strValue,"%s","XDJG_RoleReceiver");
		break;
	case CEnumCore::TagName::XDJG_ItemType:
		sprintf(strValue,"%s","XDJG_ItemType");
		break;
	case CEnumCore::TagName::XDJG_CharacterFrom:
		sprintf(strValue,"%s","XDJG_CharacterFrom");
		break;
	case CEnumCore::TagName::XDJG_TempItemId:
		sprintf(strValue,"%s","XDJG_TempItemId");
		break;
	case CEnumCore::TagName::XDJG_MoneyType:
		sprintf(strValue,"%s","XDJG_MoneyType");
		break;
	case CEnumCore::TagName::XDJG_Property:
		sprintf(strValue,"%s","XDJG_Property");
		break;
	case CEnumCore::TagName::XDJG_Cooldowns:
		sprintf(strValue,"%s","XDJG_Cooldowns");
		break;
	case CEnumCore::TagName::XDJG_Titles:
		sprintf(strValue,"%s","XDJG_Titles");
		break;
	case CEnumCore::TagName::XDJG_SendAccount:
		sprintf(strValue,"%s","XDJG_SendAccount");
		break;
	case CEnumCore::TagName::XDJG_SendCharacter:
		sprintf(strValue,"%s","XDJG_SendCharacter");
		break;
	case CEnumCore::TagName::XDJG_Title:
		sprintf(strValue,"%s","XDJG_Title");
		break;
	case CEnumCore::TagName::XDJG_ReceiveTime:
		sprintf(strValue,"%s","XDJG_ReceiveTime");
		break;
	case CEnumCore::TagName::XDJG_sssTitles:
		sprintf(strValue,"%s","XDJG_sssTitles");
		break;
	case CEnumCore::TagName::XDJG_IsBind:
		sprintf(strValue,"%s","XDJG_IsBind");
		break;
	case CEnumCore::TagName::XDJG_QualityEquip:
		sprintf(strValue,"%s","XDJG_QualityEquip");
		break;
	case CEnumCore::TagName::XDJG_SuperpositionNum:
		sprintf(strValue,"%s","XDJG_SuperpositionNum");
		break;
	case CEnumCore::TagName::XDJG_CreaterID:
		sprintf(strValue,"%s","XDJG_CreaterID");
		break;
	case CEnumCore::TagName::XDJG_CreateTime:
		sprintf(strValue,"%s","XDJG_CreateTime");
		break;
	case CEnumCore::TagName::XDJG_DurableValue:
		sprintf(strValue,"%s","XDJG_DurableValue");
		break;
	case CEnumCore::TagName::XDJG_IncreaseType:
		sprintf(strValue,"%s","XDJG_IncreaseType");
		break;
	case CEnumCore::TagName::XDJG_IncreaseValue:
		sprintf(strValue,"%s","XDJG_IncreaseValue");
		break;
	case CEnumCore::TagName::XDJG_IncreaseEndValue:
		sprintf(strValue,"%s","XDJG_IncreaseEndValue");
		break;
	case CEnumCore::TagName::XDJG_IncreaseNum:
		sprintf(strValue,"%s","XDJG_IncreaseNum");
		break;
	case CEnumCore::TagName::XDJG_AssemblyID:
		sprintf(strValue,"%s","XDJG_AssemblyID");
		break;
	case CEnumCore::TagName::XDJG_PowerEffect:
		sprintf(strValue,"%s","XDJG_PowerEffect");
		break;
	case CEnumCore::TagName::XDJG_PowerStartTime:
		sprintf(strValue,"%s","XDJG_PowerStartTime");
		break;
	case CEnumCore::TagName::XDJG_EquipSlotID1:
		sprintf(strValue,"%s","XDJG_EquipSlotID1");
		break;
	case CEnumCore::TagName::XDJG_EquipSlotID2:
		sprintf(strValue,"%s","XDJG_EquipSlotID2");
		break;
	case CEnumCore::TagName::XDJG_EquipSlotID3:
		sprintf(strValue,"%s","XDJG_EquipSlotID3");
		break;
	case CEnumCore::TagName::XDJG_StarsLevel:
		sprintf(strValue,"%s","XDJG_StarsLevel");
		break;
	case CEnumCore::TagName::XDJG_UnlockTime:
		sprintf(strValue,"%s","XDJG_UnlockTime");
		break;
	case CEnumCore::TagName::XDJG_RandomProperty:
		sprintf(strValue,"%s","XDJG_RandomProperty");
		break;
	case CEnumCore::TagName::XDJG_Pwd:
		sprintf(strValue,"%s","XDJG_Pwd");
		break;
	case CEnumCore::TagName::XDJG_ItemID1:
		sprintf(strValue,"%s","XDJG_ItemID1");
		break;
	case CEnumCore::TagName::XDJG_ItemID2:
		sprintf(strValue,"%s","XDJG_ItemID2");
		break;
	case CEnumCore::TagName::XDJG_ItemID3:
		sprintf(strValue,"%s","XDJG_ItemID3");
		break;
	case CEnumCore::TagName::XDJG_ItemID4:
		sprintf(strValue,"%s","XDJG_ItemID4");
		break;
	case CEnumCore::TagName::XDJG_ItemID5:
		sprintf(strValue,"%s","XDJG_ItemID5");
		break;
	case CEnumCore::TagName::XDJG_ItemID6:
		sprintf(strValue,"%s","XDJG_ItemID6");
		break;
	case CEnumCore::TagName::XDJG_ItemID7:
		sprintf(strValue,"%s","XDJG_ItemID7");
		break;
	case CEnumCore::TagName::XDJG_ItemID8:
		sprintf(strValue,"%s","XDJG_ItemID8");
		break;
	case CEnumCore::TagName::XDJG_ItemNum1:
		sprintf(strValue,"%s","XDJG_ItemNum1");
		break;
	case CEnumCore::TagName::XDJG_ItemNum2:
		sprintf(strValue,"%s","XDJG_ItemNum2");
		break;
	case CEnumCore::TagName::XDJG_ItemNum3:
		sprintf(strValue,"%s","XDJG_ItemNum3");
		break;
	case CEnumCore::TagName::XDJG_ItemNum4:
		sprintf(strValue,"%s","XDJG_ItemNum4");
		break;
	case CEnumCore::TagName::XDJG_ItemNum5:
		sprintf(strValue,"%s","XDJG_ItemNum5");
		break;
	case CEnumCore::TagName::XDJG_ItemNum6:
		sprintf(strValue,"%s","XDJG_ItemNum6");
		break;
	case CEnumCore::TagName::XDJG_ItemNum7:
		sprintf(strValue,"%s","XDJG_ItemNum7");
		break;
	case CEnumCore::TagName::XDJG_ItemNum8:
		sprintf(strValue,"%s","XDJG_ItemNum8");
		break;
	case CEnumCore::TagName::XDJG_TempItemId1:
		sprintf(strValue,"%s","XDJG_TempItemId1");
		break;
	case CEnumCore::TagName::XDJG_TempItemId2:
		sprintf(strValue,"%s","XDJG_TempItemId2");
		break;
	case CEnumCore::TagName::XDJG_TempItemId3:
		sprintf(strValue,"%s","XDJG_TempItemId3");
		break;
	case CEnumCore::TagName::XDJG_TempItemId4:
		sprintf(strValue,"%s","XDJG_TempItemId4");
		break;
	case CEnumCore::TagName::XDJG_TempItemId5:
		sprintf(strValue,"%s","XDJG_TempItemId5");
		break;
	case CEnumCore::TagName::XDJG_TempItemId6:
		sprintf(strValue,"%s","XDJG_TempItemId6");
		break;
	case CEnumCore::TagName::XDJG_TempItemId7:
		sprintf(strValue,"%s","XDJG_TempItemId7");
		break;
	case CEnumCore::TagName::XDJG_TempItemId8:
		sprintf(strValue,"%s","XDJG_TempItemId8");
		break;
	case CEnumCore::TagName::XDJG_Task_ID:
		sprintf(strValue,"%s","XDJG_Task_ID");
		break;
	case CEnumCore::TagName::XDJG_Task_Name:
		sprintf(strValue,"%s","XDJG_Task_Name");
		break;
	case CEnumCore::TagName::XDJG_TaskType:
		sprintf(strValue,"%s","XDJG_TaskType");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowID1:
		sprintf(strValue,"%s","XDJG_ItemThrowID1");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowID2:
		sprintf(strValue,"%s","XDJG_ItemThrowID2");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowID3:
		sprintf(strValue,"%s","XDJG_ItemThrowID3");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowID4:
		sprintf(strValue,"%s","XDJG_ItemThrowID4");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowID5:
		sprintf(strValue,"%s","XDJG_ItemThrowID5");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowID6:
		sprintf(strValue,"%s","XDJG_ItemThrowID6");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowID7:
		sprintf(strValue,"%s","XDJG_ItemThrowID7");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowID8:
		sprintf(strValue,"%s","XDJG_ItemThrowID8");
		break;
	case CEnumCore::TagName::XDJG_TempItemThrowId1:
		sprintf(strValue,"%s","XDJG_TempItemThrowId1");
		break;
	case CEnumCore::TagName::XDJG_TempItemThrowId2:
		sprintf(strValue,"%s","XDJG_TempItemThrowId2");
		break;
	case CEnumCore::TagName::XDJG_TempItemThrowId3:
		sprintf(strValue,"%s","XDJG_TempItemThrowId3");
		break;
	case CEnumCore::TagName::XDJG_TempItemThrowId4:
		sprintf(strValue,"%s","XDJG_TempItemThrowId4");
		break;
	case CEnumCore::TagName::XDJG_TempItemThrowId5:
		sprintf(strValue,"%s","XDJG_TempItemThrowId5");
		break;
	case CEnumCore::TagName::XDJG_TempItemThrowId6:
		sprintf(strValue,"%s","XDJG_TempItemThrowId6");
		break;
	case CEnumCore::TagName::XDJG_TempItemThrowId7:
		sprintf(strValue,"%s","XDJG_TempItemThrowId7");
		break;
	case CEnumCore::TagName::XDJG_TempItemThrowId8:
		sprintf(strValue,"%s","XDJG_TempItemThrowId8");
		break;	
	case CEnumCore::TagName::XDJG_ItemThrowNum1:
		sprintf(strValue,"%s","XDJG_ItemThrowNum1");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowNum2:
		sprintf(strValue,"%s","XDJG_ItemThrowNum2");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowNum3:
		sprintf(strValue,"%s","XDJG_ItemThrowNum3");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowNum4:
		sprintf(strValue,"%s","XDJG_ItemThrowNum4");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowNum5:
		sprintf(strValue,"%s","XDJG_ItemThrowNum5");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowNum6:
		sprintf(strValue,"%s","XDJG_ItemThrowNum6");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowNum7:
		sprintf(strValue,"%s","XDJG_ItemThrowNum7");
		break;
	case CEnumCore::TagName::XDJG_ItemThrowNum8:
		sprintf(strValue,"%s","XDJG_ItemThrowNum8");
		break;
	case CEnumCore::TagName::XDJG_Items:
		sprintf(strValue,"%s","XDJG_Items");
		break;
	case CEnumCore::TagName::XDJG_SurplusTime:
		sprintf(strValue,"%s","XDJG_SurplusTime");
		break;
	case CEnumCore::TagName::XDJG_AuctionPrice:
		sprintf(strValue,"%s","XDJG_AuctionPrice");
		break;
	case CEnumCore::TagName::XDJG_Deposit:
		sprintf(strValue,"%s","XDJG_Deposit");
		break;
	case CEnumCore::TagName::XDJG_SkillName:
		sprintf(strValue,"%s","XDJG_SkillName");
		break;
	case CEnumCore::TagName::XDJG_UpdateType:
		sprintf(strValue,"%s","XDJG_UpdateType");
		break;
	case CEnumCore::TagName::XDJG_Prototype:
		sprintf(strValue,"%s","XDJG_Prototype");
		break;
	case CEnumCore::TagName::XDJG_MailTitle:
		sprintf(strValue,"%s","XDJG_MailTitle");
		break;
	case CEnumCore::TagName::XDJG_MailContent:
		sprintf(strValue,"%s","XDJG_MailContent");
		break;
	case CEnumCore::TagName::XDJG_PropertyId:
		sprintf(strValue,"%s","XDJG_PropertyId");
		break;
	case CEnumCore::TagName::XDJG_PropertyValue:
		sprintf(strValue,"%s","XDJG_PropertyValue");
		break;
	case CEnumCore::TagName::XDJG_SlotNum:
		sprintf(strValue,"%s","XDJG_SlotNum");
		break;
	case CEnumCore::TagName::XDJG_CarID:
		sprintf(strValue,"%s","XDJG_CarID");
		break;
	case CEnumCore::TagName::XDJG_cpValue:
		sprintf(strValue,"%s","XDJG_cpValue");
		break;
	case CEnumCore::TagName::XDJG_LookID:
		sprintf(strValue,"%s","XDJG_LookID");
		break;
	case CEnumCore::TagName::XDJG_IsLock:
		sprintf(strValue,"%s","XDJG_IsLock");
		break;
	case CEnumCore::TagName::XDJG_SkillStrValue:
		sprintf(strValue,"%s","XDJG_SkillStrValue");
		break;
	case CEnumCore::TagName::XDJG_TimePlugNum:
		sprintf(strValue,"%s","XDJG_TimePlugNum");
		break;
	case CEnumCore::TagName::XDJG_TimePlugSlot1:
		sprintf(strValue,"%s","XDJG_TimePlugSlot1");
		break;
	case CEnumCore::TagName::XDJG_TimePlugSlot2:
		sprintf(strValue,"%s","XDJG_TimePlugSlot2");
		break;
	case CEnumCore::TagName::XDJG_BrandCreateTime:
		sprintf(strValue,"%s","XDJG_BrandCreateTime");
		break;
	case CEnumCore::TagName::XDJG_BrandID:
		sprintf(strValue,"%s","XDJG_BrandID");
		break;
	case CEnumCore::TagName::XDJG_GuildID:
		sprintf(strValue,"%s","XDJG_GuildID");
		break;
	case CEnumCore::TagName::XDJG_GuildName:
		sprintf(strValue,"%s","XDJG_GuildName");
		break;
	case CEnumCore::TagName::XDJG_GuildLevel:
		sprintf(strValue,"%s","XDJG_GuildLevel");
		break;
	case CEnumCore::TagName::XDJG_GuildLeader:
		sprintf(strValue,"%s","XDJG_GuildLeader");
		break;
	case CEnumCore::TagName::XDJG_Guildmember:
		sprintf(strValue,"%s","XDJG_Guildmember");
		break;
	case CEnumCore::TagName::XDJG_JoinGuildTime:
		sprintf(strValue,"%s","XDJG_JoinGuildTime");
		break;
	case CEnumCore::TagName::XDJG_TaskStep:
		sprintf(strValue,"%s","XDJG_TaskStep");
		break;
	case CEnumCore::TagName::XDJG_Guildmembers:
		sprintf(strValue,"%s","XDJG_Guildmembers");
		break;
	case CEnumCore::TagName::XDJG_OperateTime:
		sprintf(strValue,"%s","XDJG_OperateTime");
		break;
	case CEnumCore::TagName::XDJG_Operatetype:
		sprintf(strValue,"%s","XDJG_Operatetype");
		break;
	case CEnumCore::TagName::XDJG_MoneyLose:
		sprintf(strValue,"%s","XDJG_MoneyLose");
		break;
	case CEnumCore::TagName::XDJG_TempCharacter:
		sprintf(strValue,"%s","XDJG_TempCharacter");
		break;
	case CEnumCore::TagName::XDJG_JoinTime:
		sprintf(strValue,"%s","XDJG_JoinTime");
		break;
	case CEnumCore::TagName::XDJG_GuildLog:
		sprintf(strValue,"%s","XDJG_GuildLog");
		break;
	case CEnumCore::TagName::XDJG_LeaveTime:
		sprintf(strValue,"%s","XDJG_LeaveTime");
		break;
	case CEnumCore::TagName::XDJG_ExitGuildType:
		sprintf(strValue,"%s","XDJG_ExitGuildType");
		break;
	case CEnumCore::TagName::XDJG_LeaderChangedTime:
		sprintf(strValue,"%s","XDJG_LeaderChangedTime");
		break;
	case CEnumCore::TagName::XDJG_TempSkillId:
		sprintf(strValue,"%s","XDJG_TempSkillId");
		break;
	case CEnumCore::TagName::XDJG_GuildPosition:
		sprintf(strValue,"%s","XDJG_GuildPosition");
		break;
	case CEnumCore::TagName::XDJG_GuildTransferedPosition:
		sprintf(strValue,"%s","XDJG_GuildTransferedPosition");
		break;
	case CEnumCore::TagName::XDJG_ConsumeItem:
		sprintf(strValue,"%s","XDJG_ConsumeItem");
		break;
	case CEnumCore::TagName::XDJG_CarName:
		sprintf(strValue,"%s","XDJG_CarName");
		break;
	case CEnumCore::TagName::XDJG_TempTaskId:
		sprintf(strValue,"%s","XDJG_TempTaskId");
		break;
	case CEnumCore::TagName::XDJG_IsDeleted:
		sprintf(strValue,"%s","XDJG_IsDeleted");
		break;
	case CEnumCore::TagName::XDJG_RoleProperty:
		sprintf(strValue,"%s","XDJG_RoleProperty");
		break;
	case CEnumCore::TagName::XDJG_ActivityName:
		sprintf(strValue,"%s","XDJG_ActivityName");
		break;
	case CEnumCore::TagName::XDJG_GoodsName:
		sprintf(strValue,"%s","XDJG_GoodsName");
		break;
	case CEnumCore::TagName::XDJG_GoodsUsedOff:
		sprintf(strValue,"%s","XDJG_GoodsUsedOff");
		break;
	case CEnumCore::TagName::XDJG_GetTime:
		sprintf(strValue,"%s","XDJG_GetTime");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemID1:
		sprintf(strValue,"%s","XDJG_ChoiceItemID1");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemID2:
		sprintf(strValue,"%s","XDJG_ChoiceItemID2");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemID3:
		sprintf(strValue,"%s","XDJG_ChoiceItemID3");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemID4:
		sprintf(strValue,"%s","XDJG_ChoiceItemID4");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemID5:
		sprintf(strValue,"%s","XDJG_ChoiceItemID5");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemID6:
		sprintf(strValue,"%s","XDJG_ChoiceItemID6");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemNum1:
		sprintf(strValue,"%s","XDJG_ChoiceItemNum1");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemNum2:
		sprintf(strValue,"%s","XDJG_ChoiceItemNum2");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemNum3:
		sprintf(strValue,"%s","XDJG_ChoiceItemNum3");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemNum4:
		sprintf(strValue,"%s","XDJG_ChoiceItemNum4");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemNum5:
		sprintf(strValue,"%s","XDJG_ChoiceItemNum5");
		break;
	case CEnumCore::TagName::XDJG_ChoiceItemNum6:
		sprintf(strValue,"%s","XDJG_ChoiceItemNum6");
		break;
	case CEnumCore::TagName::XDJG_TitleID:
		sprintf(strValue,"%s","XDJG_TitleID");
		break;
	case CEnumCore::TagName::XDJG_BuffID:
		sprintf(strValue,"%s","XDJG_BuffID");
		break;
	case CEnumCore::TagName::XDJG_PositionX:
		sprintf(strValue,"%s","XDJG_PositionX");
		break;
	case CEnumCore::TagName::XDJG_PositionY:
		sprintf(strValue,"%s","XDJG_PositionY");
		break;
	case CEnumCore::TagName::XDJG_PositionZ:
		sprintf(strValue,"%s","XDJG_PositionZ");
		break;
	case CEnumCore::TagName::XDJG_TargetCharacter:
		sprintf(strValue,"%s","XDJG_TargetCharacter");
		break;
	case CEnumCore::TagName::XDJG_TitleName:
		sprintf(strValue,"%s","XDJG_TitleName");
		break;
	case CEnumCore::TagName::XDJG_BuffName:
		sprintf(strValue,"%s","XDJG_BuffName");
		break;
	default:
		sprintf(strValue,"%s","Unknown");
		break;
	}
	return strValue;
}

// 显示操作结果
void OperationXD::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MXD","Success"),ReadValue("MXD","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MXD","Failure"),ReadValue("MXD","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MXD","Result"),0);
	}
}

// 获取公会等级ID
int OperationXD::GuildLevelStrToInt(CString m_str)
{
	if(!strcmp(m_str,ReadValue("MXD","GuildLvl_Member")))
	{
		return 0;
	}
	else if(!strcmp(m_str,ReadValue("MXD","GuildLvl_BCadre")))
	{
		return 1;
	}
	else if(!strcmp(m_str,ReadValue("MXD","GuildLvl_ACadre")))
	{
		return 2;
	}
	else if(!strcmp(m_str,ReadValue("MXD","GuildLvl_VChairman")))
	{
		return 3;
	}
	else if(!strcmp(m_str,ReadValue("MXD","GuildLvl_Chairman")))
	{
		return 4;
	}
	return -1;
}

// 获取公会等级名称
CString OperationXD::GuildLevelIntToStr(int iLevel)
{
	switch(iLevel)
	{
	case 0:
		return ReadValue("MXD","GuildLvl_Member");
	case 1:
		return ReadValue("MXD","GuildLvl_BCadre");
	case 2:
		return ReadValue("MXD","GuildLvl_ACadre");
	case 3:
		return ReadValue("MXD","GuildLvl_VChairman");
	case 4:
		return ReadValue("MXD","GuildLvl_Chairman");
	}
	return "";
}
