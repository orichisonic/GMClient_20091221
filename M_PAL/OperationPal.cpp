#include "stdafx.h"
#include "OperationPAL.h"
#include ".\operationpal.h"

OperationPAL::OperationPAL()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//将全局变量置零
	intPAL = NULL;
}
OperationPAL::~OperationPAL()
{
	selfSocket.MyDestory();
	packethead.Destroy();
	if(intPAL != NULL)
	{
	    intPAL = NULL;
	}
}

//设置SOCKET
void OperationPAL::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// 读取ini文件里面的值
CString OperationPAL::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MPAL.ini");
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)
	{
		return (LPSTR)&strValue;
	}
	return "";
}

// 读取ini文件里面的数字
int OperationPAL::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MPAL.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//通过行号和列名得到相应的值
CString OperationPAL::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
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
bool OperationPAL::GetServerList()
{
	try
	{
		CSocketData socketdata;
		socketdata.InitCreate(1,2);
		char strInt[10];

		int gameID = ReadIntValue("MPAL","gameID_PAL");
		int gameDBID = ReadIntValue("MPAL","gameDBID_PAL");

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
			MessageBox(NULL,ReadValue("MPAL","Main_UI_SENDDATAERROR"),ReadValue("MPAL","ERROR"),MB_OK);
			socketdata.Destroy();
			return false;
		}
		*intPAL = 2;
		socketdata.Destroy();		
	}
	catch(...)
	{
	}
	return true;
}

//发送查询请求
bool OperationPAL::SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::PAL_ADMIN,m_ServiceKey,allLength);
		
		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		//selfSocket.SetSocket(theApp.mSocket);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MPAL","Main_UI_SENDDATAERROR"),ReadValue("MPAL","ERROR"),MB_OK);
			return false;
		}
		*intPAL = 2;
	}
	catch(...)
	{
	}
	return true;
}

//发送查询日志请求
bool OperationPAL::SendLogQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::PALLOG_ADMIN,m_ServiceKey,allLength);
		
		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MPAL","Main_UI_SENDDATAERROR"),ReadValue("MPAL","ERROR"),MB_OK);
			return false;
		}
		*intPAL = 2;
	}
	catch(...)
	{
	}
	return true;
}

//再次发送同样的Query
bool OperationPAL::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//发送数据
		{
			MessageBox(NULL,ReadValue("MPAL","Main_UI_SENDDATAERROR"),ReadValue("MPAL","ERROR"),MB_OK);
			return false;
		}
	}
	catch(...)
	{
	}
	return true;
}

// 构造复选框
bool OperationPAL::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MPAL","Result"),0);
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
		MessageBox(NULL,ReadValue("MPAL","UM_Error_BuildComboBox"),ReadValue("MPAL","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}
// 构造复选框
bool OperationPAL::BuildMapCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MPAL","Result"),0);
			return false;
		}

		cmbSelect->ResetContent();
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_tSvrCity = socketData->getTLVByName(i,CEnumCore::TagName::PAL_Map);
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);
		}
		cmbSelect->SetCurSel(0);
	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MPAL","UM_Error_BuildComboBox"),ReadValue("MPAL","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}
// 构造复选框,不设置初始值
bool OperationPAL::BuildComboxs(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);//获取第一行第一列的值
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)//如果是MESSAGE
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MPAL","Result"),0);//显示MESSAGE的信息
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
		MessageBox(NULL,ReadValue("MPAL","UM_Error_BuildComboBox"),ReadValue("MPAL","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}

// 构造ListBox
bool OperationPAL::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
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
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MPAL","Error"),MB_ICONWARNING+MB_OK);
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
				ReadValue("MPAL",tagToStr(m_BGS.m_tagName));
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
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_GUILDPOWERLEVEL)
					{
						listCtrlS->SetItemText(nRow,k-1,GuildLevelIntToStr(atoi((LPCTSTR)&m_ConGS.lpdata)));
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_QUESTTYPE)//任务类型
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//类型为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","UIC_ITEM_Finished"));//显示为已完成
						}
						else//类型不为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","UIC_ITEM_Received"));//显示为已接
						}
					}
					else if((m_ConGS.m_tagName == CEnumCore::TagName::PAL_NPCTRADE) || (m_ConGS.m_tagName == CEnumCore::TagName::PAL_USERTRADE))
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","UIC_Code_Can"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","UIC_Code_Cant"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_ITEMMALLGOODS)
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","UIC_Code_Is"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","UIC_Code_Isnt"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_STATUS)
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","NI_UI_UnSend"));
						}
						else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","NI_UI_Sending"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","NI_UI_Sended"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_MONEYTYPE)
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","RM_ITEM_MONEYINBANK"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","RM_ITEM_PERSONALMONEY"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::PAL_LOGINIP)//登入IP
					{
						if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))//IP地址为空
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MPAL","UIC_Code_NotOnline"));//显示为不在线
						}
						else//IP地址不为空
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
		MessageBox(NULL,ReadValue("MPAL","UM_Error_BuildList"),ReadValue("MPAL","Error"),0);
	}
	return false;
}

//自己定义的复制函数
void OperationPAL::CopyListInfo(CListCtrl* m_listCtrl)
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
void OperationPAL::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
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
char* OperationPAL::tagToStr(CEnumCore::TagName tag)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tag)
	{
	case CEnumCore::TagName::PAL_WORLDID:
		sprintf(strValue,"%s","PAL_WORLDID");
		break;
	case CEnumCore::TagName::PAL_ACCOUNT:
		sprintf(strValue,"%s","PAL_ACCOUNT");
		break;
	case CEnumCore::TagName::PAL_ZONEID:
		sprintf(strValue,"%s","PAL_ZONEID");
		break;
	case CEnumCore::TagName::PAL_ZONENAME:
		sprintf(strValue,"%s","PAL_ZONENAME");
		break;
	case CEnumCore::TagName::PAL_LOGINTIME:
		sprintf(strValue,"%s","PAL_LOGINTIME");
		break;
	case CEnumCore::TagName::PAL_LOGINIP:
		sprintf(strValue,"%s","PAL_LOGINIP");
		break;
	case CEnumCore::TagName::PAL_ROLENAME:
		sprintf(strValue,"%s","PAL_ROLENAME");
		break;
	case CEnumCore::TagName::PAL_BAGTYPE:
		sprintf(strValue,"%s","PAL_BAGTYPE");
		break;
	case CEnumCore::TagName::PAL_ITEMNAME:
		sprintf(strValue,"%s","PAL_ITEMNAME");
		break;
	case CEnumCore::TagName::PAL_ITEMPOS:
		sprintf(strValue,"%s","PAL_ITEMPOS");
		break;
	case CEnumCore::TagName::PAL_ITEMTYPE:
		sprintf(strValue,"%s","PAL_ITEMTYPE");
		break;
	case CEnumCore::TagName::PAL_ORGOBJID:
		sprintf(strValue,"%s","PAL_ORGOBJID");
		break;
	case CEnumCore::TagName::PAL_LOCALTIME:
		sprintf(strValue,"%s","PAL_LOCALTIME");
		break;
	case CEnumCore::TagName::PAL_ITEMSERIAL:
		sprintf(strValue,"%s","PAL_ITEMSERIAL");
		break;
	case CEnumCore::TagName::PAL_LIVETIME:
		sprintf(strValue,"%s","PAL_LIVETIME");
		break;
	case CEnumCore::TagName::PAL_COOLDOWN:
		sprintf(strValue,"%s","PAL_COOLDOWN");
		break;
	case CEnumCore::TagName::PAL_NPCTRADE:
		sprintf(strValue,"%s","PAL_NPCTRADE");
		break;
	case CEnumCore::TagName::PAL_USERTRADE:
		sprintf(strValue,"%s","PAL_USERTRADE");
		break;
	case CEnumCore::TagName::PAL_ITEMMALLGOODS:
		sprintf(strValue,"%s","PAL_ITEMMALLGOODS");
		break;
	case CEnumCore::TagName::PAL_ITEMCOUNT:
		sprintf(strValue,"%s","PAL_ITEMCOUNT");
		break;
	case CEnumCore::TagName::PAL_ITEMSELLCOST:
		sprintf(strValue,"%s","PAL_ITEMSELLCOST");
		break;
	case CEnumCore::TagName::PAL_ITEMDURABLE:
		sprintf(strValue,"%s","PAL_ITEMDURABLE");
		break;
	case CEnumCore::TagName::PAL_INHERITID0:
		sprintf(strValue,"%s","PAL_INHERITID0");
		break;
	case CEnumCore::TagName::PAL_INHERITID1:
		sprintf(strValue,"%s","PAL_INHERITID1");
		break;
	case CEnumCore::TagName::PAL_INHERITID2:
		sprintf(strValue,"%s","PAL_INHERITID2");
		break;
	case CEnumCore::TagName::PAL_INHERITID3:
		sprintf(strValue,"%s","PAL_INHERITID3");
		break;
	case CEnumCore::TagName::PAL_INHERITID4:
		sprintf(strValue,"%s","PAL_INHERITID4");
		break;
	case CEnumCore::TagName::PAL_INHERITID5:
		sprintf(strValue,"%s","PAL_INHERITID5");
		break;
	case CEnumCore::TagName::PAL_INHERITID6:
		sprintf(strValue,"%s","PAL_INHERITID6");
		break;
	case CEnumCore::TagName::PAL_INHERITID7:
		sprintf(strValue,"%s","PAL_INHERITID7");
		break;
	case CEnumCore::TagName::PAL_INHERITID8:
		sprintf(strValue,"%s","PAL_INHERITID8");
		break;
	case CEnumCore::TagName::PAL_INHERITID9:
		sprintf(strValue,"%s","PAL_INHERITID9");
		break;
	case CEnumCore::TagName::PAL_PETEXP:
		sprintf(strValue,"%s","PAL_PETEXP");
		break;
	case CEnumCore::TagName::PAL_PETNOWHP:
		sprintf(strValue,"%s","PAL_PETNOWHP");
		break;
	case CEnumCore::TagName::PAL_PETINDEX:
		sprintf(strValue,"%s","PAL_PETINDEX");
		break;
	case CEnumCore::TagName::PAL_PETRENEWCOUNT:
		sprintf(strValue,"%s","PAL_PETRENEWCOUNT");
		break;
	case CEnumCore::TagName::PAL_PETLV:
		sprintf(strValue,"%s","PAL_PETLV");
		break;
	case CEnumCore::TagName::PAL_PETGENERATION:
		sprintf(strValue,"%s","PAL_PETGENERATION");
		break;
	case CEnumCore::TagName::PAL_PETMIXCOUNT:
		sprintf(strValue,"%s","PAL_PETMIXCOUNT");
		break;
	case CEnumCore::TagName::PAL_PETGROWTHRATE:
		sprintf(strValue,"%s","PAL_PETGROWTHRATE");
		break;
	case CEnumCore::TagName::PAL_PETATTRQUALITY:
		sprintf(strValue,"%s","PAL_PETATTRQUALITY");
		break;
	case CEnumCore::TagName::PAL_PETHP:
		sprintf(strValue,"%s","PAL_PETHP");
		break;
	case CEnumCore::TagName::PAL_PETWUSHU:
		sprintf(strValue,"%s","PAL_PETWUSHU");
		break;
	case CEnumCore::TagName::PAL_PETSPIRIT:
		sprintf(strValue,"%s","PAL_PETSPIRIT");
		break;
	case CEnumCore::TagName::PAL_PETCONSTITUTION:
		sprintf(strValue,"%s","PAL_PETCONSTITUTION");
		break;
	case CEnumCore::TagName::PAL_PETQUALITY:
		sprintf(strValue,"%s","PAL_PETQUALITY");
		break;
	case CEnumCore::TagName::PAL_PETDEXTERITY:
		sprintf(strValue,"%s","PAL_PETDEXTERITY");
		break;
	case CEnumCore::TagName::PAL_PETFATE:
		sprintf(strValue,"%s","PAL_PETFATE");
		break;
	case CEnumCore::TagName::PAL_PETHPPLUS:
		sprintf(strValue,"%s","PAL_PETHPPLUS");
		break;
	case CEnumCore::TagName::PAL_PETWUSHUPLUS:
		sprintf(strValue,"%s","PAL_PETWUSHUPLUS");
		break;
	case CEnumCore::TagName::PAL_PETSPIRITPLUS:
		sprintf(strValue,"%s","PAL_PETSPIRITPLUS");
		break;
	case CEnumCore::TagName::PAL_PETCONSTITUTIONPLUS:
		sprintf(strValue,"%s","PAL_PETCONSTITUTIONPLUS");
		break;
	case CEnumCore::TagName::PAL_PETQUALITYPLUS:
		sprintf(strValue,"%s","PAL_PETQUALITYPLUS");
		break;
	case CEnumCore::TagName::PAL_PETDEXTERITYPLUS:
		sprintf(strValue,"%s","PAL_PETDEXTERITYPLUS");
		break;
	case CEnumCore::TagName::PAL_PETFATEPLUS:
		sprintf(strValue,"%s","PAL_PETFATEPLUS");
		break;
	case CEnumCore::TagName::PAL_PETSKILL0:
		sprintf(strValue,"%s","PAL_PETSKILL0");
		break;
	case CEnumCore::TagName::PAL_PETSKILL1:
		sprintf(strValue,"%s","PAL_PETSKILL1");
		break;
	case CEnumCore::TagName::PAL_PETSKILL2:
		sprintf(strValue,"%s","PAL_PETSKILL2");
		break;
	case CEnumCore::TagName::PAL_PETSKILL3:
		sprintf(strValue,"%s","PAL_PETSKILL3");
		break;
	case CEnumCore::TagName::PAL_PETSKILL4:
		sprintf(strValue,"%s","PAL_PETSKILL4");
		break;
	case CEnumCore::TagName::PAL_PETSKILL5:
		sprintf(strValue,"%s","PAL_PETSKILL5");
		break;
	case CEnumCore::TagName::PAL_FRIENDNAME:
		sprintf(strValue,"%s","PAL_FRIENDNAME");
		break;
	case CEnumCore::TagName::PAL_RELATION:
		sprintf(strValue,"%s","PAL_RELATION");
		break;
	case CEnumCore::TagName::PAL_NICKNAME:
		sprintf(strValue,"%s","PAL_NICKNAME");
		break;
	case CEnumCore::TagName::PAL_GUILDNAME:
		sprintf(strValue,"%s","PAL_GUILDNAME");
		break;
	case CEnumCore::TagName::PAL_GUILDPOWERLEVEL:
		sprintf(strValue,"%s","PAL_GUILDPOWERLEVEL");
		break;
	case CEnumCore::TagName::PAL_VOC:
		sprintf(strValue,"%s","PAL_VOC");
		break;
	case CEnumCore::TagName::PAL_LEVEL:
		sprintf(strValue,"%s","PAL_LEVEL");
		break;
	case CEnumCore::TagName::PAL_EXP:
		sprintf(strValue,"%s","PAL_EXP");
		break;
	case CEnumCore::TagName::PAL_BODYMONEY:
		sprintf(strValue,"%s","PAL_BODYMONEY");
		break;
	case CEnumCore::TagName::PAL_BANKMONEY:
		sprintf(strValue,"%s","PAL_BANKMONEY");
		break;
	case CEnumCore::TagName::PAL_SEX:
		sprintf(strValue,"%s","PAL_SEX");
		break;
	case CEnumCore::TagName::PAL_FAME:
		sprintf(strValue,"%s","PAL_FAME");
		break;
	case CEnumCore::TagName::PAL_HP:
		sprintf(strValue,"%s","PAL_HP");
		break;
	case CEnumCore::TagName::PAL_MP:
		sprintf(strValue,"%s","PAL_MP");
		break;
	case CEnumCore::TagName::PAL_AP:
		sprintf(strValue,"%s","PAL_AP");
		break;
	case CEnumCore::TagName::PAL_EP:
		sprintf(strValue,"%s","PAL_EP");
		break;
	case CEnumCore::TagName::PAL_SKILLPOINT:
		sprintf(strValue,"%s","PAL_SKILLPOINT");
		break;
	case CEnumCore::TagName::PAL_SKILLTREENODE:
		sprintf(strValue,"%s","PAL_SKILLTREENODE");
		break;
	case CEnumCore::TagName::PAL_REINCARNATION:
		sprintf(strValue,"%s","PAL_REINCARNATION");
		break;
	case CEnumCore::TagName::PAL_DBID:
		sprintf(strValue,"%s","PAL_DBID");
		break;
	case CEnumCore::TagName::PAL_BULLETINID:
		sprintf(strValue,"%s","PAL_BULLETINID");
		break;
	case CEnumCore::TagName::PAL_NEWGUILDNAME:
		sprintf(strValue,"%s","PAL_NEWGUILDNAME");
		break;
	case CEnumCore::TagName::PAL_BULLETINMONTH:
		sprintf(strValue,"%s","PAL_BULLETINMONTH");
		break;
	case CEnumCore::TagName::PAL_BULLETINDAY:
		sprintf(strValue,"%s","PAL_BULLETINDAY");
		break;
	case CEnumCore::TagName::PAL_BULLETINDAYOFWEEK:
		sprintf(strValue,"%s","PAL_BULLETINDAYOFWEEK");
		break;
	case CEnumCore::TagName::PAL_BULLETINHOUR:
		sprintf(strValue,"%s","PAL_BULLETINHOUR");
		break;
	case CEnumCore::TagName::PAL_BULLETINMINUTE:
		sprintf(strValue,"%s","PAL_BULLETINMINUTE");
		break;
	case CEnumCore::TagName::PAL_BULLETINCONTENT:
		sprintf(strValue,"%s","PAL_BULLETINCONTENT");
		break;
	case CEnumCore::TagName::PAL_MAILSUBJECT:
		sprintf(strValue,"%s","PAL_MAILSUBJECT");
		break;
	case CEnumCore::TagName::PAL_MAILCONTENT:
		sprintf(strValue,"%s","PAL_MAILCONTENT");
		break;
	case CEnumCore::TagName::PAL_MAILMONEY:
		sprintf(strValue,"%s","PAL_MAILMONEY");
		break;
	case CEnumCore::TagName::PAL_MAILREASON:
		sprintf(strValue,"%s","PAL_MAILREASON");
		break;
	case CEnumCore::TagName::PAL_MAILGIFTDBID0:
		sprintf(strValue,"%s","PAL_MAILGIFTDBID0");
		break;
	case CEnumCore::TagName::PAL_MAILGIFTDBID1:
		sprintf(strValue,"%s","PAL_MAILGIFTDBID1");
		break;
	case CEnumCore::TagName::PAL_MAILGIFTDBID2:
		sprintf(strValue,"%s","PAL_MAILGIFTDBID2");
		break;
	case CEnumCore::TagName::PAL_MAILGIFTDBID3:
		sprintf(strValue,"%s","PAL_MAILGIFTDBID3");
		break;
	case CEnumCore::TagName::PAL_MAILGIFTDBID4:
		sprintf(strValue,"%s","PAL_MAILGIFTDBID4");
		break;
	case CEnumCore::TagName::PAL_DELAYTIME:
		sprintf(strValue,"%s","PAL_DELAYTIME");
		break;
	case CEnumCore::TagName::PAL_REASON:
		sprintf(strValue,"%s","PAL_REASON");
		break;
	case CEnumCore::TagName::PAL_QUESTID:
		sprintf(strValue,"%s","PAL_QUESTID");
		break;
	case CEnumCore::TagName::PAL_QUESTNAME:
		sprintf(strValue,"%s","PAL_QUESTNAME");
		break;
	case CEnumCore::TagName::PAL_QUESTTYPE:
		sprintf(strValue,"%s","PAL_QUESTTYPE");
		break;
	case CEnumCore::TagName::PAL_GUILDLEVEL:
		sprintf(strValue,"%s","PAL_GUILDLEVEL");
		break;
	case CEnumCore::TagName::PAL_GUILDSCORE:
		sprintf(strValue,"%s","PAL_GUILDSCORE");
		break;
	case CEnumCore::TagName::PAL_GUILDMONEY:
		sprintf(strValue,"%s","PAL_GUILDMONEY");
		break;
	case CEnumCore::TagName::PAL_GUILDJOINTIME:
		sprintf(strValue,"%s","PAL_GUILDJOINTIME");
		break;
	case CEnumCore::TagName::PAL_TASKID:
		sprintf(strValue,"%s","PAL_TASKID");
		break;
	case CEnumCore::TagName::PAL_BEGINTIME:
		sprintf(strValue,"%s","PAL_BEGINTIME");
		break;
	case CEnumCore::TagName::PAL_BOARDMESSAGE:
		sprintf(strValue,"%s","PAL_BOARDMESSAGE");
		break;
	case CEnumCore::TagName::PAL_ENDTIME:
		sprintf(strValue,"%s","PAL_ENDTIME");
		break;
	case CEnumCore::TagName::PAL_INTERVAL:
		sprintf(strValue,"%s","PAL_INTERVAL");
		break;
	case CEnumCore::TagName::PAL_STATUS:
		sprintf(strValue,"%s","PAL_STATUS");
		break;
	case CEnumCore::TagName::PAL_GUILDNOTICE:
		sprintf(strValue,"%s","PAL_GUILDNOTICE");
		break;
	case CEnumCore::TagName::PAL_BANKPW:
		sprintf(strValue,"%s","PAL_BANKPW");
		break;
	case CEnumCore::TagName::PAL_DROPROLEPW:
		sprintf(strValue,"%s","PAL_DROPROLEPW");
		break;
	case CEnumCore::TagName::PAL_MONEYTYPE:
		sprintf(strValue,"%s","PAL_MONEYTYPE");
		break;
	case CEnumCore::TagName::PAL_MONEYCOUNT:
		sprintf(strValue,"%s","PAL_MONEYCOUNT");
		break;
	case CEnumCore::TagName::PAL_ACCOUNTID:
		sprintf(strValue,"%s","PAL_ACCOUNTID");
		break;
	case CEnumCore::TagName::PAL_LOGOUTTIME:
		sprintf(strValue,"%s","PAL_LOGOUTTIME");
		break;
	case CEnumCore::TagName::PAL_ROLEID:
		sprintf(strValue,"%s","PAL_ROLEID");
		break;
	case CEnumCore::TagName::PAL_EVENTTYPE:
		sprintf(strValue,"%s","PAL_EVENTTYPE");
		break;
	case CEnumCore::TagName::PAL_EVENTNAME:
		sprintf(strValue,"%s","PAL_EVENTNAME");
		break;
	case CEnumCore::TagName::PAL_FROMID:
		sprintf(strValue,"%s","PAL_FROMID");
		break;
	case CEnumCore::TagName::PAL_FROMNAME:
		sprintf(strValue,"%s","PAL_FROMNAME");
		break;
	case CEnumCore::TagName::PAL_OFFICERDBID:
		sprintf(strValue,"%s","PAL_OFFICERDBID");
		break;
	case CEnumCore::TagName::PAL_OFFICERNAME:
		sprintf(strValue,"%s","PAL_OFFICERNAME");
		break;
	case CEnumCore::TagName::PAL_OFFICERZONEID:
		sprintf(strValue,"%s","PAL_OFFICERZONEID");
		break;
	case CEnumCore::TagName::PAL_OFFICERZONENAME:
		sprintf(strValue,"%s","PAL_OFFICERZONENAME");
		break;
	case CEnumCore::TagName::PAL_LogBigTypeID:
		sprintf(strValue,"%s","PAL_LogBigTypeID");
		break;
	case CEnumCore::TagName::PAL_LogBigType:
		sprintf(strValue,"%s","PAL_LogBigType");
		break;
	case CEnumCore::TagName::PAL_LogSmallTypeID:
		sprintf(strValue,"%s","PAL_LogSmallTypeID");
		break;
	case CEnumCore::TagName::PAL_LogSmallType:
		sprintf(strValue,"%s","PAL_LogSmallType");
		break;
	case CEnumCore::TagName::PAL_X:
		sprintf(strValue,"%s","PAL_X");
		break;
	case CEnumCore::TagName::PAL_Y:
		sprintf(strValue,"%s","PAL_Y");
		break;
	case CEnumCore::TagName::PAL_Z:
		sprintf(strValue,"%s","PAL_Z");
		break;
	case CEnumCore::TagName::PAL_TARGETID:
		sprintf(strValue,"%s","PAL_TARGETID");
		break;
	case CEnumCore::TagName::PAL_TARGETNAME:
		sprintf(strValue,"%s","PAL_TARGETNAME");
		break;
	case CEnumCore::TagName::PAL_TIME:
		sprintf(strValue,"%s","PAL_TIME");
		break;
	case CEnumCore::TagName::PAL_INHERITID0_NAME:
		sprintf(strValue,"%s","PAL_INHERITID0_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID1_NAME:
		sprintf(strValue,"%s","PAL_INHERITID1_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID2_NAME:
		sprintf(strValue,"%s","PAL_INHERITID2_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID3_NAME:
		sprintf(strValue,"%s","PAL_INHERITID3_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID4_NAME:
		sprintf(strValue,"%s","PAL_INHERITID4_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID5_NAME:
		sprintf(strValue,"%s","PAL_INHERITID5_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID6_NAME:
		sprintf(strValue,"%s","PAL_INHERITID6_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID7_NAME:
		sprintf(strValue,"%s","PAL_INHERITID7_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID8_NAME:
		sprintf(strValue,"%s","PAL_INHERITID8_NAME");
		break;
	case CEnumCore::TagName::PAL_INHERITID9_NAME:
		sprintf(strValue,"%s","PAL_INHERITID9_NAME");
		break;
	case CEnumCore::TagName::PAL_ITEMFLAG:
		sprintf(strValue,"%s","PAL_ITEMFLAG");
		break;
	case CEnumCore::TagName::PAL_BOSSID:
		sprintf(strValue,"%s","PAL_BOSSID");
		break;
	case CEnumCore::TagName::PAL_BOSSNAME:
		sprintf(strValue,"%s","PAL_BOSSNAME");
		break;
	case CEnumCore::TagName::PAL_AWARDMONEY:
		sprintf(strValue,"%s","PAL_AWARDMONEY");
		break;
	case CEnumCore::TagName::PAL_AWARDEXP:
		sprintf(strValue,"%s","PAL_AWARDEXP");
		break;
	case CEnumCore::TagName::PAL_AWARDTITLEID:
		sprintf(strValue,"%s","PAL_AWARDTITLEID");
		break;
	case CEnumCore::TagName::PAL_AWARDTITLENAME:
		sprintf(strValue,"%s","PAL_AWARDTITLENAME");
		break;
	case CEnumCore::TagName::PAL_FAMEID1:
		sprintf(strValue,"%s","PAL_FAMEID1");
		break;
	case CEnumCore::TagName::PAL_FAMENAME1:
		sprintf(strValue,"%s","PAL_FAMENAME1");
		break;
	case CEnumCore::TagName::PAL_FAMEVALUE1:
		sprintf(strValue,"%s","PAL_FAMEVALUE1");
		break;
	case CEnumCore::TagName::PAL_FAMEID2:
		sprintf(strValue,"%s","PAL_FAMEID2");
		break;
	case CEnumCore::TagName::PAL_FAMENAME2:
		sprintf(strValue,"%s","PAL_FAMENAME2");
		break;
	case CEnumCore::TagName::PAL_FAMEVALUE2:
		sprintf(strValue,"%s","PAL_FAMEVALUE2");
		break;
	case CEnumCore::TagName::PAL_ITEMID:
		sprintf(strValue,"%s","PAL_ITEMID");
		break;
	case CEnumCore::TagName::PAL_SKILLID:
		sprintf(strValue,"%s","PAL_SKILLID");
		break;
	case CEnumCore::TagName::PAL_MAGICID:
		sprintf(strValue,"%s","PAL_MAGICID");
		break;
	case CEnumCore::TagName::PAL_MAGICNAME:
		sprintf(strValue,"%s","PAL_MAGICNAME");
		break;
	case CEnumCore::TagName::PAL_PETMIXCOUNTREMAIN:
		sprintf(strValue,"%s","PAL_PETMIXCOUNTREMAIN");
		break;
	case CEnumCore::TagName::PAL_PETNOTE:
		sprintf(strValue,"%s","PAL_PETNOTE");
		break;
	case CEnumCore::TagName::PAL_BANTIME:
		sprintf(strValue,"%s","PAL_BANTIME");
		break;
	case CEnumCore::TagName::PAL_POINT:
		sprintf(strValue,"%s","PAL_POINT");
		break;
	case CEnumCore::TagName::PAL_ITEMBUYCOST:
		sprintf(strValue,"%s","PAL_ITEMBUYCOST");
		break;
	case CEnumCore::TagName::PAL_EXPIREDFLAG://过期标志
		sprintf(strValue,"%s","PAL_EXPIREDFLAG");
		break;
	case CEnumCore::TagName::PAL_EXPIREDDATE://过期时间
		sprintf(strValue,"%s","PAL_EXPIREDDATE");
		break;
	case CEnumCore::TagName::PAL_SELLSTATUS://拍卖状态
		sprintf(strValue,"%s","PAL_SELLSTATUS");
		break;
	case CEnumCore::TagName::PAL_ITEMLEVEL://物品等级
		sprintf(strValue,"%s","PAL_ITEMLEVEL");
		break;
	case CEnumCore::TagName::PAL_TIMETYPE://时间类型
		sprintf(strValue,"%s","PAL_TIMETYPE");
		break;
	case CEnumCore::TagName::PAL_ITEMSUBTYPE://物品小类
		sprintf(strValue,"%s","PAL_ITEMSUBTYPE");
		break;
	case CEnumCore::TagName::PAL_ITEMVOC://道具可装备/使用职业
		sprintf(strValue,"%s","PAL_ITEMVOC");
		break;
	case CEnumCore::TagName::PAL_ITEMEQPOS://道具装备位置
		sprintf(strValue,"%s","PAL_ITEMEQPOS");
		break;
	case CEnumCore::TagName::PAL_GUILDID://帮会ID
		sprintf(strValue,"%s","PAL_GUILDID");
		break;
	case CEnumCore::TagName::PAL_MONEY://金钱
		sprintf(strValue,"%s","PAL_MONEY");
		break;
	case CEnumCore::TagName::PAL_GMSERVERIPNAME://服务器名字
		sprintf(strValue,"%s","PAL_GMSERVERIPNAME");
		break;
	case CEnumCore::TagName::PAL_IDEX://序列号
		sprintf(strValue,"%s","PAL_IDEX");
		break;
	case CEnumCore::TagName::PAL_REWARDID://奖励包ID
		sprintf(strValue,"%s","PAL_REWARDID");
		break;
	case CEnumCore::TagName::PAL_GETTIME://领取时间
		sprintf(strValue,"%s","PAL_GETTIME");
		break;
	case CEnumCore::TagName::PAL_DESCRIBER://描述
		sprintf(strValue,"%s","PAL_DESCRIBER");
		break;
	case CEnumCore::TagName::PAL_ISGOT://是否领取
		sprintf(strValue,"%s","PAL_ISGOT");
		break;
	case CEnumCore::TagName::PAL_GROUPID://组号
		sprintf(strValue,"%s","PAL_GROUPID");
		break;
	case CEnumCore::TagName::PAL_9YOUID://9youid
		sprintf(strValue,"%s","PAL_9YOUID");
		break;
	case CEnumCore::TagName::PAL_WASTEPOINT://消耗元宝
		sprintf(strValue,"%s","PAL_WASTEPOINT");
		break;
	case CEnumCore::TagName::PAL_LOGTYPE://日志类型
		sprintf(strValue,"%s","PAL_LOGTYPE");
		break;
	case CEnumCore::TagName::PAL_CREATETIME://消耗时间
		sprintf(strValue,"%s","PAL_CREATETIME");
		break;
	case CEnumCore::TagName::PAL_USERMEMO://用户行为
		sprintf(strValue,"%s","PAL_USERMEMO");
		break;
	case CEnumCore::TagName::PAL_SYSMEMO://事件日志
		sprintf(strValue,"%s","PAL_SYSMEMO");
		break;
	case CEnumCore::TagName::PAL_SERVERNAME://领取大区
		sprintf(strValue,"%s","PAL_SERVERNAME");
		break;
	case CEnumCore::TagName::PAL_ACTORNAME://领取角色名
		sprintf(strValue,"%s","PAL_ACTORNAME");
		break;
	case CEnumCore::TagName::PAL_ACTORLV://领取角色等级
		sprintf(strValue,"%s","PAL_ACTORLV");
		break;
	case CEnumCore::TagName::PAL_CENDSELL://文钱卖出价格
		sprintf(strValue,"%s","PAL_CENDSELL");
		break;
	case CEnumCore::TagName::PAL_CENTBUY://文钱购买价格
		sprintf(strValue,"%s","PAL_CENTBUY");
		break;
	case CEnumCore::TagName::PAL_UserMailBox://玩家邮箱
		sprintf(strValue,"%s","PAL_UserMailBox");
		break;
	case CEnumCore::TagName::PAL_PETNAME://宠物名称
		sprintf(strValue,"%s","PAL_PETNAME");
		break;
	case CEnumCore::TagName::PAL_MAILID://邮件ID
		sprintf(strValue,"%s","PAL_MAILID");
		break;

	case CEnumCore::TagName::PAL_MurdererCount://邪气值
		sprintf(strValue,"%s","PAL_MurdererCount");
		break;
	case CEnumCore::TagName::PAL_EvilCount://恶业值
		sprintf(strValue,"%s","PAL_EvilCount");
		break;
	case CEnumCore::TagName::PAL_Wushu://武术
		sprintf(strValue,"%s","PAL_Wushu");
		break;
	case CEnumCore::TagName::PAL_Constitution://体质
		sprintf(strValue,"%s","PAL_Constitution");
		break;
	case CEnumCore::TagName::PAL_Spirit://灵性
		sprintf(strValue,"%s","PAL_Spirit");
		break;
	case CEnumCore::TagName::PAL_Quality://灵耐
		sprintf(strValue,"%s","PAL_Quality");
		break;
	case CEnumCore::TagName::PAL_Dexterity://身法
		sprintf(strValue,"%s","PAL_Dexterity");
		break;
	case CEnumCore::TagName::PAL_Fate://身法
		sprintf(strValue,"%s","PAL_Fate");
		break;
	case CEnumCore::TagName::PAL_TitleName0://称号0
		sprintf(strValue,"%s","PAL_TitleName0");
		break;
	case CEnumCore::TagName::PAL_TitleName1://称号1
		sprintf(strValue,"%s","PAL_TitleName1");
		break;
	case CEnumCore::TagName::PAL_TitleName2://称号2
		sprintf(strValue,"%s","PAL_TitleName2");
		break;
	case CEnumCore::TagName::PAL_TitleName3://称号3
		sprintf(strValue,"%s","PAL_TitleName3");
		break;
	case CEnumCore::TagName::PAL_TitleName4://称号4
		sprintf(strValue,"%s","PAL_TitleName4");
		break;
	case CEnumCore::TagName::PAL_TitleName5://称号5
		sprintf(strValue,"%s","PAL_TitleName5");
		break;
	case CEnumCore::TagName::PAL_TitleName6://称号6
		sprintf(strValue,"%s","PAL_TitleName6");
		break;
	case CEnumCore::TagName::PAL_TitleName7://称号7
		sprintf(strValue,"%s","PAL_TitleName7");
		break;
	case CEnumCore::TagName::PAL_TitleName8://称号8
		sprintf(strValue,"%s","PAL_TitleName8");
		break;
	case CEnumCore::TagName::PAL_TitleName9://称号9
		sprintf(strValue,"%s","PAL_TitleName9");
		break;
	case CEnumCore::TagName::PAL_TitleName10://称号10
		sprintf(strValue,"%s","PAL_TitleName10");
		break;
	case CEnumCore::TagName::PAL_TitleName11://称号11
		sprintf(strValue,"%s","PAL_TitleName11");
		break;
	case CEnumCore::TagName::PAL_TitleName12://称号12
		sprintf(strValue,"%s","PAL_TitleName12");
		break;
	case CEnumCore::TagName::PAL_TitleName13://称号13
		sprintf(strValue,"%s","PAL_TitleName13");
		break;
	case CEnumCore::TagName::PAL_TitleName14://称号14
		sprintf(strValue,"%s","PAL_TitleName14");
		break;
	case CEnumCore::TagName::PAL_BlackList0://黑名单0
		sprintf(strValue,"%s","PAL_BlackList0");
		break;
	case CEnumCore::TagName::PAL_BlackList1://黑名单1
		sprintf(strValue,"%s","PAL_BlackList1");
		break;
	case CEnumCore::TagName::PAL_BlackList2://黑名单2
		sprintf(strValue,"%s","PAL_BlackList2");
		break;
	case CEnumCore::TagName::PAL_BlackList3://黑名单3
		sprintf(strValue,"%s","PAL_BlackList3");
		break;
	case CEnumCore::TagName::PAL_BlackList4://黑名单4
		sprintf(strValue,"%s","PAL_BlackList4");
		break;
	case CEnumCore::TagName::PAL_BlackList5://黑名单5
		sprintf(strValue,"%s","PAL_BlackList5");
		break;
	case CEnumCore::TagName::PAL_BlackList6://黑名单6
		sprintf(strValue,"%s","PAL_BlackList6");
		break;
	case CEnumCore::TagName::PAL_BlackList7://黑名单7
		sprintf(strValue,"%s","PAL_BlackList7");
		break;
	case CEnumCore::TagName::PAL_BlackList8://黑名单8
		sprintf(strValue,"%s","PAL_BlackList8");
		break;
	case CEnumCore::TagName::PAL_BlackList9://黑名单9
		sprintf(strValue,"%s","PAL_BlackList9");
		break;
	case CEnumCore::TagName::PAL_BlackList10://黑名单10
		sprintf(strValue,"%s","PAL_BlackList10");
		break;
	case CEnumCore::TagName::PAL_BlackList11://黑名单11
		sprintf(strValue,"%s","PAL_BlackList11");
		break;
	case CEnumCore::TagName::PAL_BlackList12://黑名单12
		sprintf(strValue,"%s","PAL_BlackList12");
		break;
	case CEnumCore::TagName::PAL_BlackList13://黑名单13
		sprintf(strValue,"%s","PAL_BlackList13");
		break;
	case CEnumCore::TagName::PAL_BlackList14://黑名单14
		sprintf(strValue,"%s","PAL_BlackList14");
		break;

	case CEnumCore::TagName::PAL_PlotName0://猎户声望值(停用)
		sprintf(strValue,"%s","PAL_PlotName0");
		break;
	case CEnumCore::TagName::PAL_PlotName1://信差声望值(停用)
		sprintf(strValue,"%s","PAL_PlotName1");
		break;
	case CEnumCore::TagName::PAL_PlotName2://竞技声望
		sprintf(strValue,"%s","PAL_PlotName2");
		break;
	case CEnumCore::TagName::PAL_PlotName3://商家声望值(停用)
		sprintf(strValue,"%s","PAL_PlotName3");
		break;
	case CEnumCore::TagName::PAL_PlotName4://魔缘累计值
		sprintf(strValue,"%s","PAL_PlotName4");
		break;
	case CEnumCore::TagName::PAL_PlotName5://魔缘现有值
		sprintf(strValue,"%s","PAL_PlotName5");
		break;
	case CEnumCore::TagName::PAL_PlotName6://装备知识
		sprintf(strValue,"%s","PAL_PlotName6");
		break;
	case CEnumCore::TagName::PAL_PlotName7://才能知识
		sprintf(strValue,"%s","PAL_PlotName7");
		break;
	case CEnumCore::TagName::PAL_PlotName8://伏魔熟练度
		sprintf(strValue,"%s","PAL_PlotName8");
		break;
	case CEnumCore::TagName::PAL_PlotName9://武器使用熟练度
		sprintf(strValue,"%s","PAL_PlotName9");
		break;
	case CEnumCore::TagName::PAL_PlotName10://技能使用熟练度
		sprintf(strValue,"%s","PAL_PlotName10");
		break;
	case CEnumCore::TagName::PAL_PlotName11://冲装熟练度
		sprintf(strValue,"%s","PAL_PlotName11");
		break;
	case CEnumCore::TagName::PAL_PlotName12://仙缘累计值
		sprintf(strValue,"%s","PAL_PlotName12");
		break;
	case CEnumCore::TagName::PAL_PlotName13://仙缘现有值
		sprintf(strValue,"%s","PAL_PlotName13");
		break;
	case CEnumCore::TagName::PAL_PlotName14://仙缘今日获得
		sprintf(strValue,"%s","PAL_PlotName14");
		break;
	case CEnumCore::TagName::PAL_PlotName15://仙缘今日增加上限
		sprintf(strValue,"%s","PAL_PlotName15");
		break;
	case CEnumCore::TagName::PAL_PlotName16://尘缘累计值
		sprintf(strValue,"%s","PAL_PlotName16");
		break;
	case CEnumCore::TagName::PAL_PlotName17://尘缘现有值
		sprintf(strValue,"%s","PAL_PlotName17");
		break;
	case CEnumCore::TagName::PAL_PlotName18://魔缘今日获得
		sprintf(strValue,"%s","PAL_PlotName18");
		break;
	case CEnumCore::TagName::PAL_PlotName19://魔缘今日增加上限
		sprintf(strValue,"%s","PAL_PlotName19");
		break;
	case CEnumCore::TagName::PAL_SKILLNAME://技能
		sprintf(strValue,"%s","PAL_SKILLNAME");
		break;
	case CEnumCore::TagName::PAL_MobName://伏魔名字
		sprintf(strValue,"%s","PAL_MobName");
		break;
	case CEnumCore::TagName::PAL_MobID://伏魔ID
		sprintf(strValue,"%s","PAL_MobID");
		break;
	case CEnumCore::TagName::PAL_PuzzleMap://图鉴名
		sprintf(strValue,"%s","PAL_PuzzleMap");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID1://图鉴ID1
		sprintf(strValue,"%s","PAL_PuzzleMapID1");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID2://图鉴ID2
		sprintf(strValue,"%s","PAL_PuzzleMapID2");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID3://图鉴ID3
		sprintf(strValue,"%s","PAL_PuzzleMapID3");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID4://图鉴ID4
		sprintf(strValue,"%s","PAL_PuzzleMapID4");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID5://图鉴ID5
		sprintf(strValue,"%s","PAL_PuzzleMapID5");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID6://图鉴ID6
		sprintf(strValue,"%s","PAL_PuzzleMapID6");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID7://图鉴ID7
		sprintf(strValue,"%s","PAL_PuzzleMapID7");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID8://图鉴ID8
		sprintf(strValue,"%s","PAL_PuzzleMapID8");
		break;
	case CEnumCore::TagName::PAL_PuzzleMapID9://图鉴ID9
		sprintf(strValue,"%s","PAL_PuzzleMapID9");
		break;
	default:
		sprintf(strValue,"%s","Unknown");
		break;
	}
	return strValue;
}

// 显示操作结果
void OperationPAL::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MPAL","Success"),ReadValue("MPAL","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MPAL","Failure"),ReadValue("MPAL","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MPAL","Result"),0);
	}
}

// 获取公会等级ID
int OperationPAL::GuildLevelStrToInt(CString m_str)
{
	if(!strcmp(m_str,ReadValue("MPAL","GuildLvl_Member")))
	{
		return 0;
	}
	else if(!strcmp(m_str,ReadValue("MPAL","GuildLvl_BCadre")))
	{
		return 1;
	}
	else if(!strcmp(m_str,ReadValue("MPAL","GuildLvl_ACadre")))
	{
		return 2;
	}
	else if(!strcmp(m_str,ReadValue("MPAL","GuildLvl_VChairman")))
	{
		return 3;
	}
	else if(!strcmp(m_str,ReadValue("MPAL","GuildLvl_Chairman")))
	{
		return 4;
	}
	return -1;
}

// 获取公会等级名称
CString OperationPAL::GuildLevelIntToStr(int iLevel)
{
	switch(iLevel)
	{
	case 0:
		return ReadValue("MPAL","GuildLvl_Member");
	case 1:
		return ReadValue("MPAL","GuildLvl_BCadre");
	case 2:
		return ReadValue("MPAL","GuildLvl_ACadre");
	case 3:
		return ReadValue("MPAL","GuildLvl_VChairman");
	case 4:
		return ReadValue("MPAL","GuildLvl_Chairman");
	}
	return "";
}
