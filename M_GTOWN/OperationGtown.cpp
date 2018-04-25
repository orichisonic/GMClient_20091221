#include "stdafx.h"
#include "OperationGtown.h"
#include ".\operationgtown.h"

OperationGTOWN::OperationGTOWN()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//将全局变量置零
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

//设置SOCKET
void OperationGTOWN::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// 读取ini文件里面的值
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

// 读取ini文件里面的数字
int OperationGTOWN::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MGTOWN.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//通过行号和列名得到相应的值
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

// 获取游戏服务器列表
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

//发送查询请求(接口)
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

//发送查询日志请求(数据库)
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

//再次发送同样的Query
bool OperationGTOWN::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//发送数据
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

// 构造复选框
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

// 构造复选框,不设置初始值
bool OperationGTOWN::BuildComboxs(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);//获取第一行第一列的值
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)//如果是MESSAGE
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGTOWN","Result"),0);//显示MESSAGE的信息
			return false;
		}

		cmbSelect->ResetContent();//重置复选框的内容
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

// 构造ListBox
bool OperationGTOWN::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
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
				listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//插入列
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
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_QUESTTYPE)//任务类型
					{
					if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//类型为1的话
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_ITEM_Finished"));//显示为已完成
					}
					else//类型不为1的话
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_ITEM_Received"));//显示为已接
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
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_LOGINIP)//登入IP
					{
					if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))//IP地址为空
					{
					listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotOnline"));//显示为不在线
					}
					else//IP地址不为空
					{
					listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
					}
					}*/
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_Sex)//性别
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//性别为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_male"));//显示为男
						}
						else//性别不为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_female"));//显示为女
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_IsOnline)//是否在线
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1为在线
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_CODE_Online"));
						}
						else if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//0为不在线
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotOnline"));
						}
						else//直接显示
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}

					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_HaveInamorato)//是否有情侣
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1为有情侣
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_HaveInamorato"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotHaveInamorato"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_IsMarried)//是否结婚
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1为有情侣
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_Married"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotMarried"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_IsShaikh)//是否族长
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1为族长
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_Shaikh"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGTOWN","UIC_Code_NotShaikh"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_Interval)//时间/60
					{
						int tmpTime=atoi((LPTSTR)&m_ConGS.lpdata);
						int actTime=tmpTime/60;
						char strInt[10];
						_itoa(actTime,strInt,10);
						listCtrlS->SetItemText(nRow,k-1,strInt);
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::GT_IsBlueIdent)//是否蓝标//GT_IsBlueIdent
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1为蓝标
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
// 构造ListBox
bool OperationGTOWN::BuildNoDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount,int iIndex,int iPageSize)
{
	try
	{
		char strBaseNo[10];
		int iBaseNo=(iIndex-1)*iPageSize+1;
		
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
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MGTOWN","Error"),MB_ICONWARNING+MB_OK);
			return false;
		}
		listCtrlS->InsertColumn( 1, "名次", LVCFMT_LEFT, 80 );//插入列

		for(int i=1;i<=socketData->getColTFLVNum();i++)
		{
			m_BGS = socketData->getTLV(1,i);
			if(m_BGS.m_tagName == CEnumCore::TagName::PageCount)
			{
			}
			else
			{
				ReadValue("MGTOWN",tagToStr(m_BGS.m_tagName));
				listCtrlS->InsertColumn( i+1, this->strValue, LVCFMT_LEFT, 80 );//插入列
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
//自己定义的复制函数
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
void OperationGTOWN::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
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
char* OperationGTOWN::tagToStr(CEnumCore::TagName tag)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tag)
	{
	case CEnumCore::TagName::GT_ServerIP://服务器IP
		sprintf(strValue,"%s","GT_ServerIP");
		break;
	case CEnumCore::TagName::GT_ServerName://服务器名称
		sprintf(strValue,"%s","GT_ServerName");
		break;
	case CEnumCore::TagName::GT_UserID://玩家ID
		sprintf(strValue,"%s","GT_UserID");
		break;
	case CEnumCore::TagName::GT_Account://玩家帐号
		sprintf(strValue,"%s","GT_Account");
		break;
	case CEnumCore::TagName::GT_UserNick://玩家昵称
		sprintf(strValue,"%s","GT_UserNick");
		break;
	case CEnumCore::TagName::GT_StartTime://开始时间
		sprintf(strValue,"%s","GT_StartTime");
		break;
	case CEnumCore::TagName::GT_EndTime://结束时间
		sprintf(strValue,"%s","GT_EndTime");
		break;
	case CEnumCore::TagName::GT_Sex://性别
		sprintf(strValue,"%s","GT_Sex");
		break;
	case CEnumCore::TagName::GT_CurPosition://当前位置
		sprintf(strValue,"%s","GT_CurPosition");
		break;
	case CEnumCore::TagName::GT_GCash://G币
		sprintf(strValue,"%s","GT_GCash");
		break;
	case CEnumCore::TagName::GT_MCash://M币
		sprintf(strValue,"%s","GT_MCash");
		break;

	case CEnumCore::TagName::GT_TotalPoint://积分数量
		sprintf(strValue,"%s","GT_TotalPoint");
		break;
	case CEnumCore::TagName::GT_IsOnline://是否在线
		sprintf(strValue,"%s","GT_IsOnline");
		break;
	case CEnumCore::TagName::GT_Physical://体力值
		sprintf(strValue,"%s","GT_Physical");
		break;
	case CEnumCore::TagName::GT_Smart://脑力值
		sprintf(strValue,"%s","GT_Smart");
		break;
	case CEnumCore::TagName::GT_Financial://财力值
		sprintf(strValue,"%s","GT_Financial");
		break;
	case CEnumCore::TagName::GT_Charm://魅力值
		sprintf(strValue,"%s","GT_Charm");
		break;
	case CEnumCore::TagName::GT_Title://称号
		sprintf(strValue,"%s","GT_Title");
		break;
	case CEnumCore::TagName::GT_HouseNum://房屋数量
		sprintf(strValue,"%s","GT_HouseNum");
		break;
	case CEnumCore::TagName::GT_InFamily://所在家族
		sprintf(strValue,"%s","GT_InFamily");
		break;
	case CEnumCore::TagName::GT_FriendNum://好友数量
		sprintf(strValue,"%s","GT_FriendNum");
		break;
	case CEnumCore::TagName::GT_HaveInamorato://是否有情侣
		sprintf(strValue,"%s","GT_HaveInamorato");
		break;
	case CEnumCore::TagName::GT_IsMarried://是否结婚
		sprintf(strValue,"%s","GT_IsMarried");
		break;
	case CEnumCore::TagName::GT_IsShaikh://是否族长
		sprintf(strValue,"%s","GT_IsShaikh");
		break;
	case CEnumCore::TagName::GT_InamoratoNick://情侣昵称
		sprintf(strValue,"%s","GT_InamoratoNick");
		break;
	case CEnumCore::TagName::GT_LoverNick ://对方角色昵称
		sprintf(strValue,"%s","GT_LoverNick ");
		break;
	case CEnumCore::TagName::GT_Interval://时间间隔
		sprintf(strValue,"%s","GT_Interval");
		break;
	case CEnumCore::TagName::GT_IsImmediate://是否立即发送
		sprintf(strValue,"%s","GT_IsImmediate");
		break;
	case CEnumCore::TagName::GT_BoardMessage://公告内容
		sprintf(strValue,"%s","GT_BoardMessage");
		break;
	case CEnumCore::TagName::GT_BanReason://封停原因
		sprintf(strValue,"%s","GT_BanReason");
		break;
	case CEnumCore::TagName::GT_UnbindReason://解封原因
		sprintf(strValue,"%s","GT_UnbindReason");
		break;

	case CEnumCore::TagName::GT_NoticeID://公告ID
		sprintf(strValue,"%s","GT_NoticeID");
		break;
	case CEnumCore::TagName::GT_UserState://用户状态(玩家是否封停)
		sprintf(strValue,"%s","GT_UserState");
		break;
	case CEnumCore::TagName::GT_FamilyID://家族ID
		sprintf(strValue,"%s","GT_FamilyID");
		break;
	case CEnumCore::TagName::GT_Type://类型
		sprintf(strValue,"%s","GT_Type");
		break;
	case CEnumCore::TagName::GT_ZoneID://大区ID
		sprintf(strValue,"%s","GT_ZoneID");
		break;
	case CEnumCore::TagName::GT_MID://商品ID
		sprintf(strValue,"%s","GT_MID");
		break;
	case CEnumCore::TagName::GT_TimesLimit://使用次数
		sprintf(strValue,"%s","GT_TimesLimit");
		break;
	case CEnumCore::TagName::GT_DaysLimit://使用天数
		sprintf(strValue,"%s","GT_DaysLimit");
		break;
	case CEnumCore::TagName::GT_RoomName://房屋名称
		sprintf(strValue,"%s","GT_RoomName");
		break;
	case CEnumCore::TagName::GT_RoomPos://所在坐标
		sprintf(strValue,"%s","GT_RoomPos");
		break;
	case CEnumCore::TagName::GT_decorationName://房屋内装饰品名称
		sprintf(strValue,"%s","GT_decorationName");
		break;
	case CEnumCore::TagName::GT_RoomLimit://到期时间
		sprintf(strValue,"%s","GT_RoomLimit");
		break;
	case CEnumCore::TagName::GT_FamilyName://家族名称
		sprintf(strValue,"%s","GT_FamilyName");
		break;
	case CEnumCore::TagName::GT_FamilyCreate://创建时间
		sprintf(strValue,"%s","GT_FamilyCreate");
		break;
	case CEnumCore::TagName::GT_MemberNum://成员人数
		sprintf(strValue,"%s","GT_MemberNum");
		break;
	case CEnumCore::TagName::GT_FamilyLeader://族长名称
		sprintf(strValue,"%s","GT_FamilyLeader");
		break;
	case CEnumCore::TagName::GT_FamilyLeaderID://族长ID
		sprintf(strValue,"%s","GT_FamilyLeaderID");
		break;
	case CEnumCore::TagName::GT_MemberName://成员名称
		sprintf(strValue,"%s","GT_MemberName");
		break;
	case CEnumCore::TagName::GT_JoinTime://加入时间
		sprintf(strValue,"%s","GT_JoinTime");
		break;
	case CEnumCore::TagName::GT_PetName://宠物名称
		sprintf(strValue,"%s","GT_PetName");
		break;
	case CEnumCore::TagName::GT_PetPos://当前位置
		sprintf(strValue,"%s","GT_PetPos");
		break;
	case CEnumCore::TagName::GT_PetLimit://到期时间
		sprintf(strValue,"%s","GT_PetLimit");
		break;
	case CEnumCore::TagName::GT_ItemID://道具ID
		sprintf(strValue,"%s","GT_ItemID");
		break;
	case CEnumCore::TagName::GT_ItemName://道具名称
		sprintf(strValue,"%s","GT_ItemName");
		break;
	case CEnumCore::TagName::GT_IsBlueIdent://是否蓝标
		sprintf(strValue,"%s","GT_IsBlueIdent");
		break;
	case CEnumCore::TagName::GT_Limit://到期时间
		sprintf(strValue,"%s","GT_Limit");
		break;
	case CEnumCore::TagName::GT_FriendName://好友名称
		sprintf(strValue,"%s","GT_FriendName");
		break;
	case CEnumCore::TagName::GT_BlackFName://黑友名称
		sprintf(strValue,"%s","GT_BlackFName");
		break;
	case CEnumCore::TagName::GT_DarkFName://暗友名称
		sprintf(strValue,"%s","GT_DarkFName");
		break;
	case CEnumCore::TagName::GT_OpenTime://开启时间
		sprintf(strValue,"%s","GT_OpenTime");
		break;
	case CEnumCore::TagName::GT_GetReward://获得奖励
		sprintf(strValue,"%s","GT_GetReward");
		break;
	case CEnumCore::TagName::GT_FamilyDuty://家族职务
		sprintf(strValue,"%s","GT_FamilyDuty");
		break;

	case CEnumCore::TagName::GT_BanTime://封停时间
		sprintf(strValue,"%s","GT_BanTime");
		break;
	case CEnumCore::TagName::GT_SenderNick://发送昵称
		sprintf(strValue,"%s","GT_SenderNick");
		break;
	case CEnumCore::TagName::GT_ReceiverNick://接收方昵称
		sprintf(strValue,"%s","GT_ReceiverNick");
		break;
	case CEnumCore::TagName::GT_TradeTime://交易时间
		sprintf(strValue,"%s","GT_TradeTime");
		break;
	case CEnumCore::TagName::GT_TradeItemID://交易物品ID
		sprintf(strValue,"%s","GT_TradeItemID");
		break;
	case CEnumCore::TagName::GT_TradeItemName://物品名称
		sprintf(strValue,"%s","GT_TradeItemName");
		break;
	case CEnumCore::TagName::GT_TradeItemNum://物品数量
		sprintf(strValue,"%s","GT_TradeItemNum");
		break;
	case CEnumCore::TagName::GT_MailTime://发送邮件时间
		sprintf(strValue,"%s","GT_MailTime");
		break;
	case CEnumCore::TagName::GT_MailContent://邮件内容
		sprintf(strValue,"%s","GT_MailContent");
		break;
	case CEnumCore::TagName::GT_TaskName://任务名称
		sprintf(strValue,"%s","GT_TaskName");
		break;
	case CEnumCore::TagName::GT_TaskTime://完成时间
		sprintf(strValue,"%s","GT_TaskTime");
		break;
	case CEnumCore::TagName::GT_TaskReward://任务完成奖励1
		sprintf(strValue,"%s","GT_TaskReward");
		break;
	case CEnumCore::TagName::GT_UseItemName://使用道具名称
		sprintf(strValue,"%s","GT_UseItemName");
		break;
	case CEnumCore::TagName::GT_UseItemNum://使用道具数量
		sprintf(strValue,"%s","GT_UseItemNum");
		break;
	case CEnumCore::TagName::GT_UseItemTime://使用道具时间
		sprintf(strValue,"%s","GT_UseItemTime");
		break;
	case CEnumCore::TagName::GT_MailTitle://邮件标题
		sprintf(strValue,"%s","GT_MailTitle");
		break;
	case CEnumCore::TagName::GT_OnlineTime://在线时长
		sprintf(strValue,"%s","GT_OnlineTime");
		break;
	case CEnumCore::TagName::GT_RewardItemName://获得奖励道具名称
		sprintf(strValue,"%s","GT_RewardItemName");
		break;
	case CEnumCore::TagName::GT_RewardGetTime://获得时间
		sprintf(strValue,"%s","GT_RewardGetTime");
		break;
	case CEnumCore::TagName::GT_SenderAccount://发送帐号
		sprintf(strValue,"%s","GT_SenderAccount");
		break;
	case CEnumCore::TagName::GT_SendTime://发送时间
		sprintf(strValue,"%s","GT_SendTime");
		break;
	case CEnumCore::TagName::GT_SendContent://发送内容
		sprintf(strValue,"%s","GT_SendContent");
		break;
	case CEnumCore::TagName::GT_LoginTime://登录时间
		sprintf(strValue,"%s","GT_LoginTime");
		break;
	case CEnumCore::TagName::GT_LogoutTime://登出时间
		sprintf(strValue,"%s","GT_LogoutTime");
		break;
	case CEnumCore::TagName::GT_UserIP://玩家IP
		sprintf(strValue,"%s","GT_UserIP");
		break;
	case CEnumCore::TagName::GT_SendNick://发送昵称
		sprintf(strValue,"%s","GT_SendNick");
		break;
	case CEnumCore::TagName::GT_TreasureBox_Type://宝箱类型
		sprintf(strValue,"%s","GT_TreasureBox_Type");
		break;
	case CEnumCore::TagName::GT_TaskReward2://任务完成奖励2
		sprintf(strValue,"%s","GT_TaskReward2");
		break;
	case CEnumCore::TagName::GT_ChooseReward://任务可选奖励
		sprintf(strValue,"%s","GT_ChooseReward");
		break;
	case CEnumCore::TagName::GT_BuyTime://购买时间
		sprintf(strValue,"%s","GT_BuyTime");
		break;
	case CEnumCore::TagName::GT_TimeLimit://使用期限
		sprintf(strValue,"%s","GT_TimeLimit");
		break;
	case CEnumCore::TagName::GT_ChargeTime://充值到账时间
		sprintf(strValue,"%s","GT_ChargeTime");
		break;
	case CEnumCore::TagName::GT_ChargeMoney://充值金额
		sprintf(strValue,"%s","GT_ChargeMoney");
		break;
	case CEnumCore::TagName::GT_Money://金钱
		sprintf(strValue,"%s","GT_Money");
		break;
	case CEnumCore::TagName::GT_Resume://个性签名
		sprintf(strValue,"%s","GT_Resume");
		break;
	case CEnumCore::TagName::GT_Card://名片
		sprintf(strValue,"%s","GT_Card");
		break;
	case CEnumCore::TagName::GT_Male://男方名
		sprintf(strValue,"%s","GT_Male");
		break;
	case CEnumCore::TagName::GT_Female://女方名
		sprintf(strValue,"%s","GT_Female");
		break;
	case CEnumCore::TagName::GT_MarryPeople://婚礼人数
		sprintf(strValue,"%s","GT_MarryPeople");
		break;
	case CEnumCore::TagName::GT_Pktimes://Pk数
		sprintf(strValue,"%s","GT_Pktimes");
		break;
	case CEnumCore::TagName::GT_Win://胜利数
		sprintf(strValue,"%s","GT_Win");
		break;
	case CEnumCore::TagName::GT_Cowin://失败数
		sprintf(strValue,"%s","GT_Cowin");
		break;
	case CEnumCore::TagName::GT_Times://次数
		sprintf(strValue,"%s","GT_Times");
		break;
	case CEnumCore::TagName::GT_Lustful://花痴度
		sprintf(strValue,"%s","GT_Lustful");
		break;
	case CEnumCore::TagName::GT_Fanta://迷人度
		sprintf(strValue,"%s","GT_Fanta");
		break;
	case CEnumCore::TagName::GT_Allexp://综合指数
		sprintf(strValue,"%s","GT_Allexp");
		break;
	case CEnumCore::TagName::GT_SlaveCount://奴隶数
		sprintf(strValue,"%s","GT_SlaveCount");
		break;
	case CEnumCore::TagName::GT_SlaveSum://总资产
		sprintf(strValue,"%s","GT_SlaveSum");
		break;
	case CEnumCore::TagName::GT_Coin://现金
		sprintf(strValue,"%s","GT_Coin");
		break;
	case CEnumCore::TagName::GT_SlaveID://奴隶ID
		sprintf(strValue,"%s","GT_SlaveID");
		break;
	case CEnumCore::TagName::GT_SlaveAccount://奴隶名称
		sprintf(strValue,"%s","GT_SlaveAccount");
		break;
	case CEnumCore::TagName::GT_SlaveNick://奴隶昵称
		sprintf(strValue,"%s","GT_SlaveNick");
		break;
	case CEnumCore::TagName::GT_Price://身价
		sprintf(strValue,"%s","GT_Price");
		break;
	case CEnumCore::TagName::GT_IsSell://是否被买卖
		sprintf(strValue,"%s","GT_IsSell");
		break;
	case CEnumCore::TagName::GT_DateRecord://发生时间
		sprintf(strValue,"%s","GT_DateRecord");
		break;
	case CEnumCore::TagName::GT_Discount://打折数
		sprintf(strValue,"%s","GT_Discount");
		break;
	case CEnumCore::TagName::GT_JW2Name://对应JW2大区名
		sprintf(strValue,"%s","GT_JW2Name");
		break;
	case CEnumCore::TagName::GT_ID://序号
		sprintf(strValue,"%s","GT_ID");
		break;	
	default:
		break;
	}
	return strValue;
}

// 显示操作结果
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

// 获取公会等级ID
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

// 获取公会等级名称
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