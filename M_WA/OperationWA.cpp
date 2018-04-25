#include "stdafx.h"
#include "OperationWA.h"
#include ".\OperationWA.h"

OperationWA::OperationWA()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//将全局变量置零
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

//设置SOCKET
void OperationWA::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// 读取ini文件里面的值
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

// 读取ini文件里面的数字
int OperationWA::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MWA.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//通过行号和列名得到相应的值
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

// 获取游戏服务器列表
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
		socketdata.AddTFLV(CEnumCore::TagName::GameName,CEnumCore::TagFormat::TLV_STRING,strlen(gamename),(unsigned char *)mIni.wcharToChar(gamename));//游戏名称
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

//发送查询请求
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

//发送查询日志请求
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

//再次发送同样的Query
bool OperationWA::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//发送数据
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

// 构造复选框
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

//构造复选框
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

// 构造复选框
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

// 构造ListBox
bool OperationWA::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
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
			CString temp;
			temp.Format("%s",(LPCTSTR)&m_BGS.lpdata);
			if(temp=="数据库为空")
			{
               MessageBox(NULL,"没有查找到相关数据",ReadValue("MWA","Error"),MB_ICONWARNING+MB_OK);
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
						if(m_ConGS.m_tagName == CEnumCore::TagName::WA_Status)
						{
							CString temp;
							temp.Format("%s",(LPCTSTR)m_ConGS.lpdata);
							//MessageBox(NULL,(LPCTSTR)&m_ConGS.lpdata,"",0);
							//if(temp.Find('0')>=0)
							//{
							//	//listCtrlS->SetItemText(nRow,k-1,"未发送");
							//}
							//else if(temp.Find('1')>=0)
							//{
							//	listCtrlS->SetItemText(nRow,k-1,"已完成");
							//}
							//else if(temp.Find('2')>=0)
							//{
							//	listCtrlS->SetItemText(nRow,k-1,"正在发送");
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
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::WA_QUESTTYPE)//任务类型
				//	{
				//		if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//类型为1的话
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_ITEM_Finished"));//显示为已完成
				//		}
				//		else//类型不为1的话
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_ITEM_Received"));//显示为已接
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
				//	else if(m_ConGS.m_tagName == CEnumCore::TagName::WA_LOGINIP)//登入IP
				//	{
				//		if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))//IP地址为空
				//		{
				//			listCtrlS->SetItemText(nRow,k-1,ReadValue("MWA","UIC_Code_NotOnline"));//显示为不在线
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
		MessageBox(NULL,ReadValue("MWA","UM_Error_BuildList"),ReadValue("MWA","Error"),0);
	}
	return false;
}

//自己定义的复制函数
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
void OperationWA::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
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
char* OperationWA::tagToStr(CEnumCore::TagName tag)
{
	unsigned short tmpTagName = tag;
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tmpTagName)
	{
	case CEnumCore::TagName::WA_ServerName://服务器名称
		sprintf(strValue,"%s","WA_ServerName");
		break;
	case CEnumCore::TagName::WA_ServerIP://服务器IP
		sprintf(strValue,"%s","WA_ServerIP");
		break;
	case CEnumCore::TagName::WA_Account://帐号
		sprintf(strValue,"%s","WA_Account");
		break;
	case CEnumCore::TagName::WA_UserNick://昵称
		sprintf(strValue,"%s","WA_UserNick");
		break;
	case CEnumCore::TagName::WA_BeginTime://开始时间
		sprintf(strValue,"%s","WA_BeginTime");
		break;
	case CEnumCore::TagName::WA_EndTime://结束时间
		sprintf(strValue,"%s","WA_EndTime");
		break;
	case CEnumCore::TagName::WA_AccountID://帐号ID
		sprintf(strValue,"%s","WA_AccountID");
		break;
	case CEnumCore::TagName::WA_NickID://角色ID
		sprintf(strValue,"%s","WA_NickID");
		break;
	case CEnumCore::TagName::WA_Time://时间
		sprintf(strValue,"%s","WA_Time");
		break;
	case CEnumCore::TagName::WA_RealmId://大区ID
		sprintf(strValue,"%s","WA_RealmId");
		break;
	case CEnumCore::TagName::WA_ClusterID://服务组ID
		sprintf(strValue,"%s","WA_ClusterID");
		break;
	case CEnumCore::TagName::WA_TitleName1://角色称谓1
		sprintf(strValue,"%s","WA_TitleName1");
		break;
	case CEnumCore::TagName::WA_TitleName2://角色称谓2
		sprintf(strValue,"%s","WA_TitleName2");
		break;
	case CEnumCore::TagName::WA_CharType://角色类型
		sprintf(strValue,"%s","WA_CharType");
		break;
	case CEnumCore::TagName::WA_Profession://角色职业
		sprintf(strValue,"%s","WA_Profession");
		break;
	case CEnumCore::TagName::WA_Sex://角色性别
		sprintf(strValue,"%s","WA_Sex");
		break;
	case CEnumCore::TagName::WA_IsDelete://是否被删除
		sprintf(strValue,"%s","WA_IsDelete");
		break;
	case CEnumCore::TagName::WA_IsOnline://是否在线
		sprintf(strValue,"%s","WA_IsOnline");
		break;
	case CEnumCore::TagName::WA_IsClosed://是否封停
		sprintf(strValue,"%s","WA_IsClosed");
		break;
	case CEnumCore::TagName::WA_Level://等级
		sprintf(strValue,"%s","WA_Level");
		break;
	case CEnumCore::TagName::WA_Money://游戏币数量
		sprintf(strValue,"%s","WA_Money");
		break;
	case CEnumCore::TagName::WA_NineyouMoney://9游币数量
		sprintf(strValue,"%s","WA_NineyouMoney");
		break;
	case CEnumCore::TagName::WA_ReserveMoney://储备金
		sprintf(strValue,"%s","WA_ReserveMoney");
		break;
	case CEnumCore::TagName::WA_CurSceneID://当前所在场景ID
		sprintf(strValue,"%s","WA_CurSceneID");
		break;
	case CEnumCore::TagName::WA_CurSceneName://当前所在场景名称
		sprintf(strValue,"%s","WA_CurSceneName");
		break;
	case CEnumCore::TagName::WA_CurScenePos://当前所在场景坐标
		sprintf(strValue,"%s","WA_CurScenePos");
		break;
	case CEnumCore::TagName::WA_Hp://生命值
		sprintf(strValue,"%s","WA_Hp");
		break;
	case CEnumCore::TagName::WA_Mp://魔法值
		sprintf(strValue,"%s","WA_Mp");
		break;
	case CEnumCore::TagName::WA_Vitality://活力值
		sprintf(strValue,"%s","WA_Vitality");
		break;
	case CEnumCore::TagName::WA_GoodEvil://善恶值
		sprintf(strValue,"%s","WA_GoodEvil");
		break;
	case CEnumCore::TagName::WA_PhysicalAttack://物理攻击
		sprintf(strValue,"%s","WA_PhysicalAttack");
		break;
	case CEnumCore::TagName::WA_PhysicalDefense://物理防御
		sprintf(strValue,"%s","WA_PhysicalDefense");
		break;
	case CEnumCore::TagName::WA_MagicAttack://魔法攻击
		sprintf(strValue,"%s","WA_MagicAttack");
		break;
	case CEnumCore::TagName::WA_MagicDefense://魔法防御
		sprintf(strValue,"%s","WA_MagicDefense");
		break;
	case CEnumCore::TagName::WA_Critical://暴击率
		sprintf(strValue,"%s","WA_Critical");
		break;
	case CEnumCore::TagName::WA_Strength://力量
		sprintf(strValue,"%s","WA_Strength");
		break;
	case CEnumCore::TagName::WA_Dexterity://敏捷
		sprintf(strValue,"%s","WA_Dexterity");
		break;
	case CEnumCore::TagName::WA_Intellect://智力
		sprintf(strValue,"%s","WA_Intellect");
		break;
	case CEnumCore::TagName::WA_Corporeity://体质
		sprintf(strValue,"%s","WA_Corporeity");
		break;
	case CEnumCore::TagName::WA_PotentialPoint://潜力
		sprintf(strValue,"%s","WA_PotentialPoint");
		break;
	case CEnumCore::TagName::WA_Exp://经验
		sprintf(strValue,"%s","WA_Exp");
		break;
	case CEnumCore::TagName::WA_ExpNextLevel://升级经验
		sprintf(strValue,"%s","WA_ExpNextLevel");
		break;
	case CEnumCore::TagName::WA_PhysicalResist://物理抗性
		sprintf(strValue,"%s","WA_PhysicalResist");
		break;
	case CEnumCore::TagName::WA_MagicResist://法术抗性
		sprintf(strValue,"%s","WA_MagicResist");
		break;
	case CEnumCore::TagName::WA_FireResist://火焰抗性
		sprintf(strValue,"%s","WA_FireResist");
		break;
	case CEnumCore::TagName::WA_ColdResist://冰冻抗性
		sprintf(strValue,"%s","WA_ColdResist");
		break;
	case CEnumCore::TagName::WA_PoisonResist://毒素抗性
		sprintf(strValue,"%s","WA_PoisonResist");
		break;
	case CEnumCore::TagName::WA_Reason://原因
		sprintf(strValue,"%s","WA_Reason");
		break;
	case CEnumCore::TagName::WA_RemainTime://剩余时间
		sprintf(strValue,"%s","WA_RemainTime");
		break;
	case CEnumCore::TagName::WA_TaskID://公告ID
		sprintf(strValue,"%s","WA_TaskID");
		break;
	case CEnumCore::TagName::WA_BoardMessage://公告内容
		sprintf(strValue,"%s","WA_BoardMessage");
		break;
	case CEnumCore::TagName::WA_Interval://间隔时间
		sprintf(strValue,"%s","WA_Interval");
		break;
	case CEnumCore::TagName::WA_Status://状态
		sprintf(strValue,"%s","WA_Status");
		break;

	case CEnumCore::TagName::WA_friendIndex://好友角色ID
		sprintf(strValue,"%s","WA_friendIndex");
		break;
	case CEnumCore::TagName::WA_friendName://好友名字
		sprintf(strValue,"%s","WA_friendName");
		break;
	case CEnumCore::TagName::WA_friendTypeId://好友的角色类型
		sprintf(strValue,"%s","WA_friendTypeId");
		break;
	case CEnumCore::TagName::WA_friendLevel://好友等级
		sprintf(strValue,"%s","WA_friendLevel");
		break;
	case CEnumCore::TagName::WA_friendIni://亲密度
		sprintf(strValue,"%s","WA_friendIni");
		break;
	case CEnumCore::TagName::WA_LastLoginTime://上次登录时间
		sprintf(strValue,"%s","WA_LastLoginTime");
		break;
	case CEnumCore::TagName::WA_EnableTime://封停结束时间
		sprintf(strValue,"%s","WA_EnableTime");
		break;
	case CEnumCore::TagName::WA_itemIndex://物品序号
		sprintf(strValue,"%s","WA_itemIndex");
	
		break;
	case CEnumCore::TagName::WA_itemTypeId://类型ID
		sprintf(strValue,"%s","WA_itemTypeId");
		break;
	case CEnumCore::TagName::WA_itemName://物品名字
		sprintf(strValue,"%s","WA_itemName");
		break;
	case CEnumCore::TagName::WA_itemUniqueId://唯一ID
		sprintf(strValue,"%s","WA_itemUniqueId");
		break;
	case CEnumCore::TagName::WA_itemCount://数量
		sprintf(strValue,"%s","WA_itemCount");
		break;
	case CEnumCore::TagName::WA_itemDur://耐久
		sprintf(strValue,"%s","WA_itemDur");
		break;

		//徽章与宠物属性
	case CEnumCore::TagName::WA_medalTypeId://类型ID
		sprintf(strValue,"%s","WA_medalTypeId");
		break;
	case CEnumCore::TagName::WA_medalName://徽章名字
		sprintf(strValue,"%s","WA_medalName");
		break;
	case CEnumCore::TagName::WA_medalDur://耐久
		sprintf(strValue,"%s","WA_medalDur");

		break;
	case CEnumCore::TagName::WA_medalBringUp://培差度
		sprintf(strValue,"%s","WA_medalBringUp");
		break;
	case CEnumCore::TagName::WA_medalPetIndex://宠物序号超所值255为无宠物
		sprintf(strValue,"%s","WA_medalPetIndex");
		break;
	case CEnumCore::TagName::WA_medalPos://徽章在宠物背包中位置 255为装备中
		sprintf(strValue,"%s","WA_medalPos");
		break;
	case CEnumCore::TagName::WA_petTypeId://类型ID
		sprintf(strValue,"%s","WA_petTypeId");
		break;
	case CEnumCore::TagName::WA_petName://宠物名字
		sprintf(strValue,"%s","WA_petName");
		break;
	case CEnumCore::TagName::WA_petLevel://等级
		sprintf(strValue,"%s","WA_petLevel");

		break;
	case CEnumCore::TagName::WA_petNature://性格
		sprintf(strValue,"%s","WA_petNature");
		break;
	case CEnumCore::TagName::WA_petGrowth://成长率
		sprintf(strValue,"%s","WA_petGrowth");
		break;
	case CEnumCore::TagName::WA_healthe://健康度
		sprintf(strValue,"%s","WA_healthe");
		break;
	case CEnumCore::TagName::WA_FireAttack://火焰攻击
		sprintf(strValue,"%s","WA_FireAttack");
		break;
	case CEnumCore::TagName::WA_ColdAttack://冰冻攻击
		sprintf(strValue,"%s","WA_ColdAttack");
		break;
	case CEnumCore::TagName::WA_PoisonAttack://毒素攻击
		sprintf(strValue,"%s","WA_PoisonAttack");

		break;
	case CEnumCore::TagName::WA_Description://封停类型
		sprintf(strValue,"%s","WA_Description");
		break;
	case CEnumCore::TagName::WA_ItemPos://道具位置
		sprintf(strValue,"%s","WA_ItemPos");
		break;
	case CEnumCore::TagName::WA_SrcCharId://来源角色ID
		sprintf(strValue,"%s","WA_SrcCharId");
		break;
	case CEnumCore::TagName::WA_SrcCharName://来源角色名字
		sprintf(strValue,"%s","WA_SrcCharName");
		break;
	case CEnumCore::TagName::WA_DateTime://交易时间
		sprintf(strValue,"%s","WA_DateTime");
		break;
	case CEnumCore::TagName::WA_DstCharId://目标角色ID
		sprintf(strValue,"%s","WA_DstCharId");
		break;
	case CEnumCore::TagName::WA_DstCharName://目标角色名字
		sprintf(strValue,"%s","WA_DstCharName");
		break;
	case CEnumCore::TagName::WA_BindReward1://绑定奖励1
		sprintf(strValue,"%s","WA_BindReward1");
		break;
	case CEnumCore::TagName::WA_BindRewardValue1://绑定奖励数值1
		sprintf(strValue,"%s","WA_BindRewardValue1");
		break;
	case CEnumCore::TagName::WA_BindReward2://绑定奖励2
		sprintf(strValue,"%s","WA_BindReward2");
		break;
	case CEnumCore::TagName::WA_BindRewardValue2://绑定奖励数值1
		sprintf(strValue,"%s","WA_BindRewardValue2");
		break;
	case CEnumCore::TagName::WA_ConsumeItemTypeId://解绑消耗物品ID
		sprintf(strValue,"%s","WA_ConsumeItemTypeId");
		break;	
	case CEnumCore::TagName::WA_BoothType://操作类型
		sprintf(strValue,"%s","WA_BoothType");
		break;
	case CEnumCore::TagName::WA_ItemTimeLimit://物品的使用期限
		sprintf(strValue,"%s","WA_ItemTimeLimit");
		break;	
	case CEnumCore::TagName::WA_CraftType://装备制作类型
		sprintf(strValue,"%s","WA_CraftType");
		break;
	case CEnumCore::TagName::WA_RecipeId://图纸ID
		sprintf(strValue,"%s","WA_RecipeId");
		break;
	case CEnumCore::TagName::WA_MaterialId1://材料ID1
		sprintf(strValue,"%s","WA_MaterialId1");
		break;	
	case CEnumCore::TagName::WA_MaterialId2://材料ID2
		sprintf(strValue,"%s","WA_MaterialId2");
		break;
	case CEnumCore::TagName::WA_MaterialId3://材料ID3
		sprintf(strValue,"%s","WA_MaterialId3");
		break;	
	case CEnumCore::TagName::WA_MaterialId4://材料ID4
		sprintf(strValue,"%s","WA_MaterialId4");
		break;
	case CEnumCore::TagName::WA_MaterialId5://材料ID5
		sprintf(strValue,"%s","WA_MaterialId5");
		break;
	case CEnumCore::TagName::WA_MaterialId6://材料ID6
		sprintf(strValue,"%s","WA_MaterialId6");
		break;	
	case CEnumCore::TagName::WA_ProductId://产品ID
		sprintf(strValue,"%s","WA_ProductId");
		break;
	case CEnumCore::TagName::WA_ProductName://产品名字
		sprintf(strValue,"%s","WA_ProductName");
		break;	
	case CEnumCore::TagName::WA_ConsumeHammer://消耗铁锤
		sprintf(strValue,"%s","WA_ConsumeHammer");
		break;	
	case CEnumCore::TagName::WA_ConsumeStithy://消耗铁砧
		sprintf(strValue,"%s","WA_ConsumeStithy");
		break;
	case CEnumCore::TagName::WA_ConsumeMoney://消耗金钱
		sprintf(strValue,"%s","WA_ConsumeMoney");
		break;	
	case CEnumCore::TagName::WA_OldColor://改孔前颜色
		sprintf(strValue,"%s","WA_OldColor");
		break;
	case CEnumCore::TagName::WA_NewColor://改孔后颜色
		sprintf(strValue,"%s","WA_NewColor");
		break;	
	case CEnumCore::TagName::WA_OldStarCount://升星前星数
		sprintf(strValue,"%s","WA_OldStarCount");
		break;
	case CEnumCore::TagName::WA_NewStarCount://升星后星数
		sprintf(strValue,"%s","WA_NewStarCount");
		break;
	case CEnumCore::TagName::WA_GemOperation://宝石操作
		sprintf(strValue,"%s","WA_GemOperation");
		break;	
	case CEnumCore::TagName::WA_GemType:///宝石类型
		sprintf(strValue,"%s","WA_GemType");
		break;
	case CEnumCore::TagName::WA_GemLevel://宝石等级
		sprintf(strValue,"%s","WA_GemLevel");
		break;
	case CEnumCore::TagName::WA_MaterialId://原材料ID
		sprintf(strValue,"%s","WA_MaterialId");
		break;	
	case CEnumCore::TagName::WA_MaterialName://原材料名字
		sprintf(strValue,"%s","WA_MaterialName");
		break;
	case CEnumCore::TagName::WA_PropItemId://成功率道具
		sprintf(strValue,"%s","WA_PropItemId");
		break;
	case CEnumCore::TagName::WA_ChangeType://兑换类型
		sprintf(strValue,"%s","WA_ChangeType");
		break;	
	case CEnumCore::TagName::WA_ConsumeIntegral://消耗积分
		sprintf(strValue,"%s","WA_ConsumeIntegral");
		break;
	case CEnumCore::TagName::WA_ChangePoint://得到的经验或是钱
		sprintf(strValue,"%s","WA_ChangePoint");
		break;
	case CEnumCore::TagName::WA_GetMoney://获得金钱数量
		sprintf(strValue,"%s","WA_GetMoney");
		break;	
	case CEnumCore::TagName::WA_SrcId:///来源ID
		sprintf(strValue,"%s","WA_SrcId");
		break;
	case CEnumCore::TagName::WA_SrcName://来源名字
		sprintf(strValue,"%s","WA_SrcName");
		break;
	case CEnumCore::TagName::WA_LoseMoney://失去金钱数量
		sprintf(strValue,"%s","WA_LoseMoney");
		break;	
	case CEnumCore::TagName::WA_DstId://目标ID
		sprintf(strValue,"%s","WA_DstId");
		break;
	case CEnumCore::TagName::WA_DstName://目标名字
		sprintf(strValue,"%s","WA_DstName");
		break;
	case CEnumCore::TagName::WA_QuestId://任务ID
		sprintf(strValue,"%s","WA_QuestId");
		break;
	case CEnumCore::TagName::WA_QuestName://任务名字
		sprintf(strValue,"%s","WA_QuestName");
		break;	
	case CEnumCore::TagName::WA_RewardMoney://奖励的金钱
		sprintf(strValue,"%s","WA_RewardMoney");
		break;
	case CEnumCore::TagName::WA_RewardItemId://奖励的物品
		sprintf(strValue,"%s","WA_RewardItemId");
		break;
	case CEnumCore::TagName::WA_RewardItemName://奖励的物品名字
		sprintf(strValue,"%s","WA_RewardItemName");
		break;	
	case CEnumCore::TagName::WA_GiveItemId://失去的物品ID
		sprintf(strValue,"%s","WA_GiveItemId");
		break;
	case CEnumCore::TagName::WA_GiveItemName://失去的物品名字
		sprintf(strValue,"%s","WA_GiveItemName");
		break;
	case CEnumCore::TagName::WA_MailId://邮件ID
		sprintf(strValue,"%s","WA_MailId");
		break;
	case CEnumCore::TagName::WA_MailMoney://金钱数量
		sprintf(strValue,"%s","WA_MailMoney");
		break;
	case CEnumCore::TagName::WA_Item1://物品1
		sprintf(strValue,"%s","WA_Item1");
		break;	
	case CEnumCore::TagName::WA_Item2://物品2
		sprintf(strValue,"%s","WA_Item2");
		break;
	case CEnumCore::TagName::WA_Item3://物品3
		sprintf(strValue,"%s","WA_Item3");
		break;
	case CEnumCore::TagName::WA_Item4:///物品4
		sprintf(strValue,"%s","WA_Item4");
		break;
	case CEnumCore::TagName::WA_Item5://物品5
		sprintf(strValue,"%s","WA_Item5");
		break;
	case CEnumCore::TagName::WA_Item1Count://物品1数量
		sprintf(strValue,"%s","WA_Item1Count");
		break;	
	case CEnumCore::TagName::WA_Item2Count://物品2数量
		sprintf(strValue,"%s","WA_Item2Count");
		break;
	case CEnumCore::TagName::WA_Item3Count://物品3数量
		sprintf(strValue,"%s","WA_Item3Count");
		break;
	case CEnumCore::TagName::WA_Item4Count://物品4数量
		sprintf(strValue,"%s","WA_Item4Count");
		break;
	case CEnumCore::TagName::WA_Item5Count://物品5数量
		sprintf(strValue,"%s","WA_Item5Count");
		break;
	case CEnumCore::TagName::WA_MailTitle://邮件标题
		sprintf(strValue,"%s","WA_MailTitle");
		break;	
	case CEnumCore::TagName::WA_OpType://类型
		sprintf(strValue,"%s","WA_OpType");
		break;
	case CEnumCore::TagName::WA_InstanceId://副本ID
		sprintf(strValue,"%s","WA_InstanceId");
		break;
	case CEnumCore::TagName::WA_InstanceName:///副本名字
		sprintf(strValue,"%s","WA_InstanceName");
		break;
	case CEnumCore::TagName::WA_USERTYPE://用户类型：1赠送人 2受赠人
		sprintf(strValue,"%s","WA_USERTYPE");
		break;	
	case CEnumCore::TagName::WA_SkillName://技能名称
		sprintf(strValue,"%s","WA_SkillName");
		break;
	case CEnumCore::TagName::WA_NewPasswd://新密码
		sprintf(strValue,"%s","WA_NewPasswd");
		break;
	case CEnumCore::TagName::WA_ItemID://道具ID
		sprintf(strValue,"%s","WA_ItemID");
		break;
	case CEnumCore::TagName::WA_TYPE://属性类型
		sprintf(strValue,"%s","WA_TYPE");
		break;
	case CEnumCore::TagName::WA_NewRole://新的角色名
		sprintf(strValue,"%s","WA_NewRole");
		break;
	case CEnumCore::TagName::WA_SkillID://技能ID
		sprintf(strValue,"%s","WA_SkillID");
		break;
	case CEnumCore::TagName::WA_SkillLvl://技能等级
		sprintf(strValue,"%s","WA_SkillLvl");
		break;
	case CEnumCore::TagName::WA_cluster_id://组ID
		sprintf(strValue,"%s","WA_cluster_id");
		break;
	case CEnumCore::TagName::WA_realm_id://领域ID
		sprintf(strValue,"%s","WA_realm_id");
		break;
	case CEnumCore::TagName::WA_ItemType://道具类型
		sprintf(strValue,"%s","WA_ItemType");
		break;
	case CEnumCore::TagName::WA_MailorName://发件人名称
		sprintf(strValue,"%s","WA_MailorName");
		break;
	case CEnumCore::TagName::WA_ItemPrice://物品价格
		sprintf(strValue,"%s","WA_ItemPrice");
		break;
	case CEnumCore::TagName::WA_UNBindRewardValue1://解绑的获得奖励1
		sprintf(strValue,"%s","WA_UNBindRewardValue1");
		break;
	case CEnumCore::TagName::WA_UNBindRewardValue2://解绑的获得奖励2
		sprintf(strValue,"%s","WA_UNBindRewardValue2");
		break;
	case CEnumCore::TagName::WA_GetTime://获得时间
		sprintf(strValue,"%s","WA_GetTime");
		break;
	case CEnumCore::TagName::WA_Content://封停描述
		sprintf(strValue,"%s","WA_Content");
		break;
	case CEnumCore::TagName::WA_GuildName://公会名称
		sprintf(strValue,"%s","WA_GuildName");
		break;
	case CEnumCore::TagName::WA_NewProfession://转职后职业
		sprintf(strValue,"%s","WA_NewProfession");
		break;
	case CEnumCore::TagName::WA_ConsumeItem://消耗物品
		sprintf(strValue,"%s","WA_ConsumeItem");
		break;
	case CEnumCore::TagName::WA_GuildLevel://公会等级
		sprintf(strValue,"%s","WA_GuildLevel");
		break;
	case CEnumCore::TagName::WA_NewGuildName://新公会名称
		sprintf(strValue,"%s","WA_NewGuildName");
		break;
	case CEnumCore::TagName::WA_GuildMemCount://公会人数
		sprintf(strValue,"%s","WA_GuildMemCount");
		break;
	case CEnumCore::TagName::WA_RecipeName://图纸名称
		sprintf(strValue,"%s","WA_RecipeName");
		break;
	case CEnumCore::TagName::WA_MaterialName1://材料名称1
		sprintf(strValue,"%s","WA_MaterialName1");
		break;
	case CEnumCore::TagName::WA_MaterialName2://材料名称2
		sprintf(strValue,"%s","WA_MaterialName2");
		break;
	case CEnumCore::TagName::WA_MaterialName3://材料名称3
		sprintf(strValue,"%s","WA_MaterialName3");
		break;
	case CEnumCore::TagName::WA_MaterialName4://材料名称4
		sprintf(strValue,"%s","WA_MaterialName4");
		break;
	case CEnumCore::TagName::WA_MaterialName5://材料名称5
		sprintf(strValue,"%s","WA_MaterialName5");
		break;
	case CEnumCore::TagName::WA_MaterialName6://材料名称6
		sprintf(strValue,"%s","WA_MaterialName6");
		break;
	case CEnumCore::TagName::WA_ItemNum://道具数量
		sprintf(strValue,"%s","WA_ItemNum");
		break;
	case CEnumCore::TagName::WA_LoginIP://登陆IP
		sprintf(strValue,"%s","WA_LoginIP");
		break;
	case CEnumCore::TagName::WA_MemLevel://职级
		sprintf(strValue,"%s","WA_MemLevel");
		break;
	case CEnumCore::TagName::WA_MailTag://是否群发邮件
		sprintf(strValue,"%s","WA_MailTag");
		break;
	case CEnumCore::TagName::WA_ItemGen://道具品质
		sprintf(strValue,"%s","WA_ItemGen");
		break;
	case CEnumCore::TagName::WA_MailSubject://邮件标题
		sprintf(strValue,"%s","WA_MailSubject");
		break;
	case CEnumCore::TagName::WA_MailContent://邮件正文
		sprintf(strValue,"%s","WA_MailContent");
		break;
	case CEnumCore::TagName::WA_SendMoney://发送金钱
		sprintf(strValue,"%s","WA_SendMoney");
		break;
	case CEnumCore::TagName::WA_ItemExpire://物品时效
		sprintf(strValue,"%s","WA_ItemExpire");
		break;
	case CEnumCore::TagName::WA_GuildID://公会ID
		sprintf(strValue,"%s","WA_GuildID");
		break;
	case CEnumCore::TagName::WA_PetUniqId://宠物唯一ID
		sprintf(strValue,"%s","WA_PetUniqId");
		break;
	case CEnumCore::TagName::WA_CurMoney://当前游戏币数量
		sprintf(strValue,"%s","WA_CurMoney");
		break;
	default:
		sprintf(strValue,"%s","Unknown");
		break;
	}
	return strValue;
}

// 显示操作结果
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

// 获取公会等级ID
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

// 获取公会等级名称
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
