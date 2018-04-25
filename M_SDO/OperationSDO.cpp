#include "stdafx.h"
#include "OperationSDO.h"
#include ".\operationSDO.h"

OperationSDO::OperationSDO()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//将全局变量置零
	intSDO = NULL;
}

OperationSDO::~OperationSDO()
{
	selfSocket.MyDestory();
	packethead.Destroy();
	if(intSDO != NULL)
	{
		intSDO = NULL;
	}
}

//设置SOCKET
void OperationSDO::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// 读取ini文件里面的值
CString OperationSDO::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MSDO.ini");
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)
	{
		return (LPSTR)&strValue;
	}
	return "";
}

// 读取ini文件里面的数字
int OperationSDO::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MSDO.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//通过行号和列名得到相应的值
CString OperationSDO::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
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
bool OperationSDO::GetServerList()
{
	try
	{
		CSocketData socketdata;
		socketdata.InitCreate(1,2);
		char strInt[10];

		int gameID = ReadIntValue("MSDO","gameID_SDO");////maple add
		int gameDBID = ReadIntValue("MSDO","gameDBID_SDO");

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
			MessageBox(NULL,ReadValue("MSDO","Main_UI_SENDDATAERROR"),ReadValue("MSDO","ERROR"),MB_OK);
			socketdata.Destroy();
			return false;
		}
		*intSDO = 5;
		socketdata.Destroy();		
	}
	catch(...)
	{
	}
	return true;
}

//发送查询请求(接口)
bool OperationSDO::SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::SDO_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		//selfSocket.SetSocket(theApp.mSocket);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MSDO","Main_UI_SENDDATAERROR"),ReadValue("MSDO","ERROR"),MB_OK);
			return false;
		}
		*intSDO= 5;
	}
	catch(...)
	{
	}
	return true;
}

//发送查询日志请求(数据库)
bool OperationSDO::SendLogQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::SDO_ADMIN,m_ServiceKey,allLength);

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MSDO","Main_UI_SENDDATAERROR"),ReadValue("MSDO","ERROR"),MB_OK);
			return false;
		}
		*intSDO = 5;
	}
	catch(...)
	{
	}
	return true;
}

//再次发送同样的Query
bool OperationSDO::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//发送数据
		{
			MessageBox(NULL,ReadValue("MSDO","Main_UI_SENDDATAERROR"),ReadValue("MSDO","ERROR"),MB_OK);
			return false;
		}
	}
	catch(...)
	{
	}
	return true;
}

// 构造复选框
bool OperationSDO::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MSDO","Result"),0);
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
		MessageBox(NULL,ReadValue("MSDO","UM_Error_BuildComboBox"),ReadValue("MSDO","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// 构造复选框,不设置初始值
bool OperationSDO::BuildComboxs(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);//获取第一行第一列的值
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)//如果是MESSAGE
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MSDO","Result"),0);//显示MESSAGE的信息
			return false;
		}

		cmbSelect->ResetContent();//重置复选框的内容
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_tSvrCity =socketData->getTLVByName(i,CEnumCore::TagName::SDO_ItemName); //socketData->getTLV(i,2);//maple add
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MSDO","UM_Error_BuildComboBox"),ReadValue("MSDO","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

//构造场景复选框
bool OperationSDO::BuildComboxScene(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);//获取第一行第一列的值
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)//如果是MESSAGE
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MSDO","Result"),0);//显示MESSAGE的信息
			return false;
		}

		cmbSelect->ResetContent();//重置复选框的内容
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_tSvrCity =socketData->getTLVByName(i,CEnumCore::TagName::SDO_Sence); 
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MSDO","UM_Error_BuildComboBox"),ReadValue("MSDO","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// 构造ListBox
bool OperationSDO::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
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
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MSDO","Error"),MB_ICONWARNING+MB_OK);
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
				ReadValue("MSDO",tagToStr(m_BGS.m_tagName));
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
					unsigned short tmpTagName=m_ConGS.m_tagName;
					if(tmpTagName == CEnumCore::TagName::PageCount)
					{
					}
					
					else if(tmpTagName == CEnumCore::TagName::SDO_SEX)//性别
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//性别为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Code_male"));//
						}
						else//性别不为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Code_female"));//
						}
					}
					else if(tmpTagName == CEnumCore::TagName::SDO_Ispad)//是否已注册跳舞毯
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Code_Registed"));
						}
						else if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Code_UnRegisted"));
						}
						else//直接显示
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}

					}
					else if(tmpTagName == CEnumCore::TagName::SDO_Online)//是否在线
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//1为在线
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_CODE_Online"));//UIC_Code_BlueIdent
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Code_NotOnline"));//UIC_Code_NotBlueIdent
						}
					}
					else if(tmpTagName == CEnumCore::TagName::SDO_TimesLimit)//SDO_TimesLimit
					{
						if(!strcmp("-1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,"0");
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(tmpTagName == CEnumCore::TagName::SDO_ActiveStatus)//激活状态
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Code_Actived"));//已激活
						}
						else if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Code_UnActived"));//未激活
						}
					}
					else if(tmpTagName == CEnumCore::TagName::SDO_State)//状态
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//休息
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Status_relax"));
						}
						else if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//携带
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Status_take"));
						}
						else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))//出走
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Status_leave"));
						}
						else if(!strcmp("3", (LPTSTR)&m_ConGS.lpdata))//探险
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Status_exploration"));
						}
					}
					else if(tmpTagName == CEnumCore::TagName::SDO_Rank)//排名//UIC_Code_UnRank
					{
						if(!strcmp("-1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","UIC_Code_UnRank"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(tmpTagName == CEnumCore::TagName::SDO_WeekDay)//星期几
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","Sun"));
						}
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","Mon"));
						}
						if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","Tues"));
						}
						if(!strcmp("3", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","Wens"));
						}
						if(!strcmp("4", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","Thus"));
						}
						if(!strcmp("5", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","Fri"));
						}
						if(!strcmp("6", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","Sat"));
						}
					}
					else if(tmpTagName == CEnumCore::TagName::SDO_IsBattle)//比赛类型
					{
						if(!strcmp("10", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","XF_UI_Type1"));
						}
						if(!strcmp("11", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","XF_UI_Type4"));
						}
						if(!strcmp("12", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","XF_UI_Type3"));
						}
						if(!strcmp("13", (LPTSTR)&m_ConGS.lpdata))//
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MSDO","XF_UI_Type2"));
						}
					}
					else if(tmpTagName == CEnumCore::TagName::SDO_DaysLimit)
					{
						if(!strcmp("-1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,"0");
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
			listCtrlS->SetItemData(j-1,j-1);
		}
	}
	catch (...)
	{
		MessageBox(NULL,ReadValue("MSDO","UM_Error_BuildList"),ReadValue("MSDO","Error"),0);
	}
	return false;
}

//自己定义的复制函数
void OperationSDO::CopyListInfo(CListCtrl* m_listCtrl)
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
void OperationSDO::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
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
char* OperationSDO::tagToStr(CEnumCore::TagName tag)
{
	unsigned short tmpTagName = tag;
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tmpTagName)
	{
	case CEnumCore::TagName::SDO_ServerIP://服务器IP
		sprintf(strValue,"%s","SDO_ServerIP");
		break;
	case CEnumCore::TagName::SDO_UserIndexID://玩家用户ID
		sprintf(strValue,"%s","SDO_UserIndexID");
		break;
	case CEnumCore::TagName::SDO_Account://玩家的帐号
		sprintf(strValue,"%s","SDO_Account");
		break;
	case CEnumCore::TagName::SDO_CoupleUserName://女性帐号
		sprintf(strValue,"%s","SDO_CoupleUserName");
		break;
	case CEnumCore::TagName::SDO_Level://玩家的等级
		sprintf(strValue,"%s","SDO_Level");
		break;
	case CEnumCore::TagName::SDO_Exp://玩家的当前经验值
		sprintf(strValue,"%s","SDO_Exp");
		break;
	case CEnumCore::TagName::SDO_GameTotal://总局数
		sprintf(strValue,"%s","SDO_GameTotal");
		break;
	case CEnumCore::TagName::SDO_GameWin://胜局数
		sprintf(strValue,"%s","SDO_GameWin");
		break;
	case CEnumCore::TagName::SDO_DogFall://平局数
		sprintf(strValue,"%s","SDO_DogFall");
		break;
	case CEnumCore::TagName::SDO_GameFall://负局数
		sprintf(strValue,"%s","SDO_GameFall");
		break;
	case CEnumCore::TagName::SDO_Reputation://声望值
		sprintf(strValue,"%s","SDO_Reputation");
		break;
	case CEnumCore::TagName::SDO_GCash://G币
		sprintf(strValue,"%s","SDO_GCash");
		break;
	case CEnumCore::TagName::SDO_MCash://M币
		sprintf(strValue,"%s","SDO_MCash");
		break;
	case CEnumCore::TagName::SDO_Address://地址
		sprintf(strValue,"%s","SDO_Address");
		break;
	case CEnumCore::TagName::SDO_Age://年龄
		sprintf(strValue,"%s","SDO_Age");
		break;
	case CEnumCore::TagName::SDO_ProductID://商品编号
		sprintf(strValue,"%s","SDO_ProductID");
		break;
	case CEnumCore::TagName::SDO_ProductName://商品名称
		sprintf(strValue,"%s","SDO_ProductName");
		break;
	case CEnumCore::TagName::SDO_ItemCode://道具编号
		sprintf(strValue,"%s","SDO_ItemCode");
		break;
	case CEnumCore::TagName::SDO_ItemName://道具名称
		sprintf(strValue,"%s","SDO_ItemName");
		break;
	case CEnumCore::TagName::SDO_TimesLimit://使用次数
		sprintf(strValue,"%s","SDO_TimesLimit");
		break;
	case CEnumCore::TagName::SDO_DateLimit://使用时效
		sprintf(strValue,"%s","SDO_DateLimit");
		break;
	case CEnumCore::TagName::SDO_MoneyType://货币类型
		sprintf(strValue,"%s","SDO_MoneyType");
		break;
	case CEnumCore::TagName::SDO_MoneyCost://道具的价格
		sprintf(strValue,"%s","SDO_MoneyCost");
		break;
	case CEnumCore::TagName::SDO_ShopTime://消费时间
		sprintf(strValue,"%s","SDO_ShopTime");
		break;
	case CEnumCore::TagName::SDO_MAINCH://服务器
		sprintf(strValue,"%s","SDO_MAINCH");
		break;
	case CEnumCore::TagName::SDO_SUBCH://房间
		sprintf(strValue,"%s","SDO_SUBCH");
		break;
	case CEnumCore::TagName::SDO_Online://是否在线
		sprintf(strValue,"%s","SDO_Online");
		break;
	case CEnumCore::TagName::SDO_LoginTime://上线时间
		sprintf(strValue,"%s","SDO_LoginTime");
		break;
	case CEnumCore::TagName::SDO_LogoutTime://下线时间
		sprintf(strValue,"%s","SDO_LogoutTime");
		break;
	case CEnumCore::TagName::SDO_AREANAME://大区名字
		sprintf(strValue,"%s","SDO_AREANAME");
		break;
	case CEnumCore::TagName::SDO_City://玩家所住城市
		sprintf(strValue,"%s","SDO_City");
		break;
	case CEnumCore::TagName::SDO_Title://道具主题
		sprintf(strValue,"%s","SDO_Title");
		break;
	case CEnumCore::TagName::SDO_Context://道具描述
		sprintf(strValue,"%s","SDO_Context");
		break;
	case CEnumCore::TagName::SDO_MinLevel://所带道具的最小等级
		sprintf(strValue,"%s","SDO_MinLevel");
		break;
	case CEnumCore::TagName::SDO_ActiveStatus://激活状态
		sprintf(strValue,"%s","SDO_ActiveStatus");
		break;
	case CEnumCore::TagName::SDO_StopStatus://封停状态
		sprintf(strValue,"%s","SDO_StopStatus");
		break;
	case CEnumCore::TagName::SDO_NickName://呢称
		sprintf(strValue,"%s","SDO_NickName");
		break;
	case CEnumCore::TagName::SDO_9YouAccount://9you的帐号
		sprintf(strValue,"%s","SDO_9YouAccount");
		break;
	case CEnumCore::TagName::SDO_SEX://性别
		sprintf(strValue,"%s","SDO_SEX");
		break;
	case CEnumCore::TagName::SDO_RegistDate://注册日期
		sprintf(strValue,"%s","SDO_RegistDate");
		break;
	case CEnumCore::TagName::SDO_FirstLogintime://第一次登录时间
		sprintf(strValue,"%s","SDO_FirstLogintime");
		break;
	case CEnumCore::TagName::SDO_LastLogintime://最后一次登录时间
		sprintf(strValue,"%s","SDO_LastLogintime");
		break;
	case CEnumCore::TagName::SDO_Ispad://是否已注册跳舞毯
		sprintf(strValue,"%s","SDO_Ispad");
		break;
	case CEnumCore::TagName::SDO_Desc://道具描述
		sprintf(strValue,"%s","SDO_Desc");
		break;
	case CEnumCore::TagName::SDO_Postion://道具位置
		sprintf(strValue,"%s","SDO_Postion");
		break;
	case CEnumCore::TagName::SDO_BeginTime://消费记录开始时间
		sprintf(strValue,"%s","SDO_BeginTime");
		break;
	case CEnumCore::TagName::SDO_EndTime://消费记录结束时间
		sprintf(strValue,"%s","SDO_EndTime");
		break;
	case CEnumCore::TagName::SDO_SendTime://道具送人日期
		sprintf(strValue,"%s","SDO_SendTime");
		break;
	case CEnumCore::TagName::SDO_SendIndexID://发送人的ID
		sprintf(strValue,"%s","SDO_SendIndexID");
		break;
	case CEnumCore::TagName::SDO_SendUserID://发送人帐号
		sprintf(strValue,"%s","SDO_SendUserID");
		break;
	case CEnumCore::TagName::SDO_ReceiveNick://接受人呢称
		sprintf(strValue,"%s","SDO_ReceiveNick");
		break;
	case CEnumCore::TagName::SDO_BigType://道具大类
		sprintf(strValue,"%s","SDO_BigType");
		break;
	case CEnumCore::TagName::SDO_SmallType://道具小类
		sprintf(strValue,"%s","SDO_SmallType");
		break;
	case CEnumCore::TagName::SDO_REASON://停封理由
		sprintf(strValue,"%s","SDO_REASON");
		break;
	case CEnumCore::TagName::SDO_StopTime://停封时间
		sprintf(strValue,"%s","SDO_StopTime");
		break;
	case CEnumCore::TagName::SDO_DaysLimit://使用天数
		sprintf(strValue,"%s","SDO_DaysLimit");
		break;
	case CEnumCore::TagName::SDO_Email://邮件
		sprintf(strValue,"%s","SDO_Email");
		break;
	case CEnumCore::TagName::SDO_ChargeSum://充值合计
		sprintf(strValue,"%s","SDO_ChargeSum");
		break;
	case CEnumCore::TagName::SDO_KeyID://
		sprintf(strValue,"%s","SDO_KeyID");
		break;
	case CEnumCore::TagName::SDO_KeyWord://
		sprintf(strValue,"%s","SDO_KeyWord");
		break;
	case CEnumCore::TagName::SDO_MasterID://
		sprintf(strValue,"%s","SDO_MasterID");
		break;
	case CEnumCore::TagName::SDO_Master://
		sprintf(strValue,"%s","SDO_Master");
		break;
	case CEnumCore::TagName::SDO_SlaverID://
		sprintf(strValue,"%s","SDO_SlaverID");
		break;
	case CEnumCore::TagName::SDO_Slaver://
		sprintf(strValue,"%s","SDO_Slaver");
		break;
	case CEnumCore::TagName::SDO_ChannelList://
		sprintf(strValue,"%s","SDO_ChannelList");
		break;
	case CEnumCore::TagName::SDO_BoardMessage://
		sprintf(strValue,"%s","SDO_BoardMessage");
		break;
	case CEnumCore::TagName::SDO_wPlanetID://
		sprintf(strValue,"%s","SDO_wPlanetID");
		break;
	case CEnumCore::TagName::SDO_wChannelID://
		sprintf(strValue,"%s","SDO_wChannelID");
		break;
	case CEnumCore::TagName::SDO_iLimitUser://
		sprintf(strValue,"%s","SDO_iLimitUser");
		break;
	case CEnumCore::TagName::SDO_iCurrentUser://
		sprintf(strValue,"%s","SDO_iCurrentUser");
		break;
	case CEnumCore::TagName::SDO_ipaddr://
		sprintf(strValue,"%s","SDO_ipaddr");
		break;
	case CEnumCore::TagName::SDO_Interval://
		sprintf(strValue,"%s","SDO_Interval");
		break;
	case CEnumCore::TagName::SDO_TaskID://
		sprintf(strValue,"%s","SDO_TaskID");
		break;
	case CEnumCore::TagName::SDO_Status://
		sprintf(strValue,"%s","SDO_Status");
		break;
	case CEnumCore::TagName::SDO_Score://
		sprintf(strValue,"%s","SDO_Score");
		break;
	case CEnumCore::TagName::SDO_FirstPadTime://跳舞毯第一次使用时间
		sprintf(strValue,"%s","SDO_FirstPadTime");
		break;
	case CEnumCore::TagName::SDO_BanDate://停封多少天
		sprintf(strValue,"%s","SDO_BanDate");
		break;
	case CEnumCore::TagName::SDO_Passwd://
		sprintf(strValue,"%s","SDO_Passwd");
		break;
	case CEnumCore::TagName::SDO_OnlineTime://
		sprintf(strValue,"%s","SDO_OnlineTime");
		break;
	case CEnumCore::TagName::SDO_LevPercent://
		sprintf(strValue,"%s","SDO_LevPercent");
		break;
	case CEnumCore::TagName::SDO_ItemCodeBy://
		sprintf(strValue,"%s","SDO_ItemCodeBy");
		break;
	case CEnumCore::TagName::SDO_Punish_Status://
		sprintf(strValue,"%s","SDO_Punish_Status");
		break;
	case CEnumCore::TagName::SDO_fragment_num://
		sprintf(strValue,"%s","SDO_fragment_num");
		break;
	case CEnumCore::TagName::SDO_fragment_id://
		sprintf(strValue,"%s","SDO_fragment_id");
		break;
	case CEnumCore::TagName::SDO_BuyTimes://
		sprintf(strValue,"%s","SDO_BuyTimes");
		break;
	case CEnumCore::TagName::SDO_CoupleIndexID://对方ID
		sprintf(strValue,"%s","SDO_CoupleIndexID");
		break;
	case CEnumCore::TagName::SDO_CoupleNickName://
		sprintf(strValue,"%s","SDO_CoupleNickName");
		break;
	case CEnumCore::TagName::SDO_RingLevel://
		sprintf(strValue,"%s","SDO_RingLevel");
		break;
	case CEnumCore::TagName::SDO_NewRingLevel://
		sprintf(strValue,"%s","SDO_NewRingLevel");
		break;
	case CEnumCore::TagName::SDO_MarriageApp_Date://
		sprintf(strValue,"%s","SDO_MarriageApp_Date");
		break;
	case CEnumCore::TagName::SDO_DivorceApp_Date://
		sprintf(strValue,"%s","SDO_DivorceApp_Date");
		break;
	case CEnumCore::TagName::SDO_Marriage_Date://结婚日期
		sprintf(strValue,"%s","SDO_Marriage_Date");
		break;
	case CEnumCore::TagName::SDO_Divorce_Date://
		sprintf(strValue,"%s","SDO_Divorce_Date");
		break;
	case CEnumCore::TagName::SDO_RewardItemTime://
		sprintf(strValue,"%s","SDO_RewardItemTime");
		break;
	case CEnumCore::TagName::SDO_PCash://
		sprintf(strValue,"%s","SDO_PCash");
		break;
	case CEnumCore::TagName::SDO_PunishTimes://
		sprintf(strValue,"%s","SDO_PunishTimes");
		break;
	case CEnumCore::TagName::SDO_DelTimes://
		sprintf(strValue,"%s","SDO_DelTimes");
		break;
	case CEnumCore::TagName::SDO_DATE://
		sprintf(strValue,"%s","SDO_DATE");
		break;
	case CEnumCore::TagName::SDO_IsBattle://
		sprintf(strValue,"%s","SDO_IsBattle");
		break;
	case CEnumCore::TagName::SDO_SenceID://
		sprintf(strValue,"%s","SDO_SenceID");
		break;
	case CEnumCore::TagName::SDO_WeekDay://
		sprintf(strValue,"%s","SDO_WeekDay");
		break;
	case CEnumCore::TagName::SDO_MatPtHR://
		sprintf(strValue,"%s","SDO_MatPtHR");
		break;
	case CEnumCore::TagName::SDO_MatPtMin://
		sprintf(strValue,"%s","SDO_MatPtMin");
		break;
	case CEnumCore::TagName::SDO_StPtHR://
		sprintf(strValue,"%s","SDO_StPtHR");
		break;
	case CEnumCore::TagName::SDO_StPtMin://
		sprintf(strValue,"%s","SDO_StPtMin");
		break;
	case CEnumCore::TagName::SDO_EdPtHR://
		sprintf(strValue,"%s","SDO_EdPtHR");
		break;
	case CEnumCore::TagName::SDO_EdPtMin://
		sprintf(strValue,"%s","SDO_EdPtMin");
		break;
	case CEnumCore::TagName::SDO_Sence://
		sprintf(strValue,"%s","SDO_Sence");
		break;
	case CEnumCore::TagName::SDO_MusicID1://
		sprintf(strValue,"%s","SDO_MusicID1");
		break;
	case CEnumCore::TagName::SDO_MusicName1://
		sprintf(strValue,"%s","SDO_MusicName1");
		break;
	case CEnumCore::TagName::SDO_LV1://
		sprintf(strValue,"%s","SDO_LV1");
		break;
	case CEnumCore::TagName::SDO_MusicID2://
		sprintf(strValue,"%s","SDO_MusicID2");
		break;
	case CEnumCore::TagName::SDO_MusicName2://
		sprintf(strValue,"%s","SDO_MusicName2");
		break;
	case CEnumCore::TagName::SDO_LV2://
		sprintf(strValue,"%s","SDO_LV2");
		break;
	case CEnumCore::TagName::SDO_MusicID3://
		sprintf(strValue,"%s","SDO_MusicID3");
		break;
	case CEnumCore::TagName::SDO_MusicName3://
		sprintf(strValue,"%s","SDO_MusicName3");
		break;
	case CEnumCore::TagName::SDO_LV3://
		sprintf(strValue,"%s","SDO_LV3");
		break;
	case CEnumCore::TagName::SDO_MusicID4://
		sprintf(strValue,"%s","SDO_MusicID4");
		break;
	case CEnumCore::TagName::SDO_MusicName4://
		sprintf(strValue,"%s","SDO_MusicName4");
		break;
	case CEnumCore::TagName::SDO_LV4://
		sprintf(strValue,"%s","SDO_LV4");
		break;
	case CEnumCore::TagName::SDO_MusicID5://
		sprintf(strValue,"%s","SDO_MusicID5");
		break;
	case CEnumCore::TagName::SDO_MusicName5://
		sprintf(strValue,"%s","SDO_MusicName5");
		break;
	case CEnumCore::TagName::SDO_LV5://
		sprintf(strValue,"%s","SDO_LV5");
		break;
	case CEnumCore::TagName::SDO_Precent://
		sprintf(strValue,"%s","SDO_Precent");
		break;
	case CEnumCore::TagName::SDO_Type://
		sprintf(strValue,"%s","SDO_Type");
		break;
	case CEnumCore::TagName::SDO_Usedate://
		sprintf(strValue,"%s","SDO_Usedate");
		break;
	case CEnumCore::TagName::SDO_Area://
		sprintf(strValue,"%s","SDO_Area");
		break;
	case CEnumCore::TagName::SDO_Padstatus://
		sprintf(strValue,"%s","SDO_Padstatus");
		break;
	case CEnumCore::TagName::SDO_expcash://
		sprintf(strValue,"%s","SDO_expcash");
		break;
	case CEnumCore::TagName::SDO_usecash://
		sprintf(strValue,"%s","SDO_usecash");
		break;
	case CEnumCore::TagName::SDO_State://状态
		sprintf(strValue,"%s","SDO_State");
		break;
	case CEnumCore::TagName::SDO_mood://心情值
		sprintf(strValue,"%s","SDO_mood");
		break;
	case CEnumCore::TagName::SDO_Food://饱食度
		sprintf(strValue,"%s","SDO_Food");
		break;
	case CEnumCore::TagName::SDO_ItemCode1://道具ID
		sprintf(strValue,"%s","SDO_ItemCode1");
		break;
	case CEnumCore::TagName::SDO_DateLimit1://日期限制
		sprintf(strValue,"%s","SDO_DateLimit1");
		break;
	case CEnumCore::TagName::SDO_TimeLimit1://次数限制
		sprintf(strValue,"%s","SDO_TimeLimit1");
		break;
	case CEnumCore::TagName::SDO_ItemCode2://次数限制
		sprintf(strValue,"%s","SDO_ItemCode2");
		break;
	case CEnumCore::TagName::SDO_DateLimit2://日期限制
		sprintf(strValue,"%s","SDO_DateLimit2");
		break;
	case CEnumCore::TagName::SDO_TimeLimit2://次数限制
		sprintf(strValue,"%s","SDO_TimeLimit2");
		break;
	case CEnumCore::TagName::SDO_ItemCode3://次数限制
		sprintf(strValue,"%s","SDO_ItemCode3");
		break;
	case CEnumCore::TagName::SDO_DateLimit3://日期限制
		sprintf(strValue,"%s","SDO_DateLimit3");
		break;
	case CEnumCore::TagName::SDO_TimeLimit3://次数限制
		sprintf(strValue,"%s","SDO_TimeLimit3");
		break;
	case CEnumCore::TagName::SDO_ItemCode4://次数限制
		sprintf(strValue,"%s","SDO_ItemCode4");
		break;
	case CEnumCore::TagName::SDO_DateLimit4://日期限制
		sprintf(strValue,"%s","SDO_DateLimit4");
		break;
	case CEnumCore::TagName::SDO_TimeLimit4://次数限制
		sprintf(strValue,"%s","SDO_TimeLimit4");
		break;
	case CEnumCore::TagName::SDO_ItemCode5://次数限制
		sprintf(strValue,"%s","SDO_ItemCode5");
		break;
	case CEnumCore::TagName::SDO_DateLimit5://日期限制
		sprintf(strValue,"%s","SDO_DateLimit5");
		break;
	case CEnumCore::TagName::SDO_TimeLimit5://次数限制
		sprintf(strValue,"%s","SDO_TimeLimit5");
		break;
	case CEnumCore::TagName::SDO_ItemName1://道具ID
		sprintf(strValue,"%s","SDO_ItemName1");
		break;
	case CEnumCore::TagName::SDO_ItemName2://道具ID
		sprintf(strValue,"%s","SDO_ItemName2");
		break;
	case CEnumCore::TagName::SDO_ItemName3://道具ID
		sprintf(strValue,"%s","SDO_ItemName3");
		break;
	case CEnumCore::TagName::SDO_ItemName4://道具ID
		sprintf(strValue,"%s","SDO_ItemName4");
		break;
	case CEnumCore::TagName::SDO_ItemName5://道具ID
		sprintf(strValue,"%s","SDO_ItemName5");
		break;
	case CEnumCore::TagName::SDO_KeyPress://
		sprintf(strValue,"%s","SDO_KeyPress");
		break;
	case CEnumCore::TagName::SDO_LoginErr://
		sprintf(strValue,"%s","SDO_LoginErr");
		break;
	case CEnumCore::TagName::SDO_PreValue://最小值
		sprintf(strValue,"%s","SDO_PreValue");
		break;
	case CEnumCore::TagName::SDO_EndValue://最大值
		sprintf(strValue,"%s","SDO_EndValue");
		break;
	case CEnumCore::TagName::SDO_NorProFirst://第一次打开的概率
		sprintf(strValue,"%s","SDO_NorProFirst");
		break;
	case CEnumCore::TagName::SDO_NorPro://普通宝箱的概率
		sprintf(strValue,"%s","SDO_NorPro");
		break;
	case CEnumCore::TagName::SDO_SpePro://特殊宝箱的概率
		sprintf(strValue,"%s","SDO_SpePro");
		break;
	case CEnumCore::TagName::SDO_baoxiangid://
		sprintf(strValue,"%s","SDO_baoxiangid");
		break;
	case CEnumCore::TagName::SDO_Mark://标识
		sprintf(strValue,"%s","SDO_Mark");
		break;
	case CEnumCore::TagName::SDO_RemoteIp://
		sprintf(strValue,"%s","SDO_RemoteIp");
		break;
	case CEnumCore::TagName::SDO_MsgID://
		sprintf(strValue,"%s","SDO_MsgID");
		break;
	case CEnumCore::TagName::SDO_channelname://
		sprintf(strValue,"%s","SDO_channelname");
		break;
	case CEnumCore::TagName::SDO_type://
		sprintf(strValue,"%s","SDO_type");
		break;
	case CEnumCore::TagName::SDO_UserName://
		sprintf(strValue,"%s","SDO_UserName");
		break;
	case CEnumCore::TagName::SDO_Message://
		sprintf(strValue,"%s","SDO_Message");
		break;
	case CEnumCore::TagName::SDO_datetime://
		sprintf(strValue,"%s","SDO_datetime");
		break;
	case CEnumCore::TagName::SDO_ServerName://
		sprintf(strValue,"%s","SDO_ServerName");
		break;
	case CEnumCore::TagName::SDO_ChannelID://频道id
		sprintf(strValue,"%s","SDO_ChannelID");
		break;
	case CEnumCore::TagName::SDO_PlanetID://星球id
		sprintf(strValue,"%s","SDO_PlanetID");
		break;
	case CEnumCore::TagName::SDO_PlanetName://星球名
		sprintf(strValue,"%s","SDO_PlanetName");
		break;
	case CEnumCore::TagName::SDO_ChannelName://频道名
		sprintf(strValue,"%s","SDO_ChannelName");
		break;
	case CEnumCore::TagName::SDO_FamilyName://家族名称
		sprintf(strValue,"%s","SDO_FamilyName");
		break;
	case CEnumCore::TagName::SDO_FamilyID://家族ID
		sprintf(strValue,"%s","SDO_FamilyID");
		break;
	case CEnumCore::TagName::SDO_BuyUserNick://购买用户呢称
		sprintf(strValue,"%s","SDO_BuyUserNick");
		break;
	case CEnumCore::TagName::SDO_BeforeMoney://购买前家族M币数量
		sprintf(strValue,"%s","SDO_BeforeMoney");
		break;
	case CEnumCore::TagName::SDO_Shaikh://家族族长
		sprintf(strValue,"%s","SDO_Shaikh");
		break;
	case CEnumCore::TagName::SDO_Contribute://家族贡献
		sprintf(strValue,"%s","SDO_Contribute");
		break;
	case CEnumCore::TagName::SDO_Popular://家族人气值
		sprintf(strValue,"%s","SDO_Popular");
		break;
	case CEnumCore::TagName::SDO_Curdaypopular://当天累计家族人气值
		sprintf(strValue,"%s","SDO_Curdaypopular");
		break;
	case CEnumCore::TagName::SDO_Opensign://开放标志
		sprintf(strValue,"%s","SDO_Opensign");
		break;
	case CEnumCore::TagName::SDO_Fmlevel://家族等级
		sprintf(strValue,"%s","SDO_Fmlevel");
		break;
	case CEnumCore::TagName::SDO_Maxmember://家族最大成员
		sprintf(strValue,"%s","SDO_Maxmember");
		break;
	case CEnumCore::TagName::SDO_Curmember://家族现有成员
		sprintf(strValue,"%s","SDO_Curmember");
		break;
	case CEnumCore::TagName::SDO_Fortune://家族财富
		sprintf(strValue,"%s","SDO_Fortune");
		break;
	case CEnumCore::TagName::SDO_Found_Date://创建时间
		sprintf(strValue,"%s","SDO_Found_Date");
		break;
	case CEnumCore::TagName::SDO_Rank://家族荣誉
		sprintf(strValue,"%s","SDO_Rank");
		break;
	case CEnumCore::TagName::SDO_Honor://家族荣誉排名
		sprintf(strValue,"%s","SDO_Honor");
		break;
	case CEnumCore::TagName::SDO_UseCost://使用的G币
		sprintf(strValue,"%s","SDO_UseCost");
		break;
	case CEnumCore::TagName::SDO_Duty://家族权限(255表示族长0普通会员1管理员)
		sprintf(strValue,"%s","SDO_Duty");
		break;
	case CEnumCore::TagName::SDO_Formal://加入情况(0表示申请加入，1表示现在加入)
		sprintf(strValue,"%s","SDO_Formal");
		break;
	case CEnumCore::TagName::SDO_Emblemtype://勋章类型
		sprintf(strValue,"%s","SDO_Emblemtype");
		break;
	case CEnumCore::TagName::SDO_Emblemnum://勋章数量
		sprintf(strValue,"%s","SDO_Emblemnum");
		break;
	case CEnumCore::TagName::SDO_MoneyTime://捐献时间
		sprintf(strValue,"%s","SDO_MoneyTime");
		break;
	case CEnumCore::TagName::SDO_PetLevel://宠物等级
		sprintf(strValue,"%s","SDO_PetLevel");
		break;
	case CEnumCore::TagName::SDO_PetExperience://宠物经验
		sprintf(strValue,"%s","SDO_PetExperience");
		break;
	case CEnumCore::TagName::SDO_JoinDate://加入时间
		sprintf(strValue,"%s","SDO_JoinDate");
		break;
	case CEnumCore::TagName::SDO_Money://玩家钱币
		sprintf(strValue,"%s","SDO_Money");
		break;
	case CEnumCore::TagName::SDO_SocialValue://社交值
		sprintf(strValue,"%s","SDO_SocialValue");
		break;
	case CEnumCore::TagName::SDO_Lucky://幸运值
		sprintf(strValue,"%s","SDO_Lucky");
		break;
	default:
		break;
	}
	return strValue;
}

// 显示操作结果
void OperationSDO::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MSDO","Success"),ReadValue("MSDO","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MSDO","Failure"),ReadValue("MSDO","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MSDO","Result"),0);
	}
}

