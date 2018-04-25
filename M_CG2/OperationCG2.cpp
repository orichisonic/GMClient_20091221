#include "stdafx.h"
#include "OperationCG2.h"

OperationCG2::OperationCG2()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
}
OperationCG2::~OperationCG2()
{
}
//设置SOCKET
void OperationCG2::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// 读取ini文件里面的值
CString OperationCG2::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH);
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MCG2.ini");
	if(GetPrivateProfileString(strSection,strKey,"",strValue,1024,filepath)!=-1)
	{
		return (LPSTR)&strValue;
	}
	return "";

}

// 读取ini文件里面的数字
int OperationCG2::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MCG2.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//通过行号和列名得到相应的值
CString OperationCG2::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
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

// 获取游戏服务器列表
bool OperationCG2::GetServerList()
{
	try
	{
		CSocketData socketdata;
		CPacketHead packethead;

		socketdata.InitCreate(1,2);
		char strInt[10];

		int gameID = ReadIntValue("MCG2","gameID_CG2");
		int gameDBID = ReadIntValue("MCG2","gameDBID_CG2");

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
		*intCG2 = 4;

		socketdata.Destroy();
	}
	catch(...)
	{
	}
	return true;
}

//发送查询请求
bool OperationCG2::SendQuery(unsigned char* sendData,int allLength,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		CPacketHead packethead;
		
		packethead.Create(allLength);
		packethead.AddHeader(1,CEnumCore::Msg_Category::CG2_ADMIN,m_ServiceKey,allLength);
		
		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))
		{
			MessageBox(NULL,ReadValue("MCG2","Main_UI_SENDDATAERROR"),ReadValue("MCG2","ERROR"),MB_OK);
			return false;
		}
		*intCG2 = 4;
	}
	catch(...)
	{
	}
	return true;
}

// 构造复选框
bool OperationCG2::BuildCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;

		m_tSvrCity = socketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MCG2","Result"),0);
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
		MessageBox(NULL,ReadValue("MCG2","UM_Error_BuildComboBox"),ReadValue("MCG2","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}
//maple add
//构造职业复选框
bool OperationCG2::BuildJobCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		//CGlobalStruct::TFLV m_tSvrCity;
		CGlobalStruct::TFLV m_tJobName;
		m_tJobName.nIndex=0;

		m_tJobName = socketData->getTLV(1,1);
		if(m_tJobName.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tJobName.lpdata,ReadValue("MCG2","Result"),0);
			return false;
		}

		cmbSelect->ResetContent();
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_tJobName=socketData->getTLV(i,1);
			cmbSelect->AddString((LPCTSTR)&m_tJobName.lpdata);
		}
		cmbSelect->SetCurSel(0);

	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MCG2","UM_Error_BuildComboBox"),ReadValue("MCG2","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;
}
//构造宠物下拉框
bool OperationCG2::BuildPetCombox(CSocketData* socketData,CComboBox* cmbSelect)
{
	try
	{
		//CGlobalStruct::TFLV m_tSvrCity;
		CGlobalStruct::TFLV m_tJobName;
		m_tJobName.nIndex=0;

		m_tJobName = socketData->getTLV(1,1);
		if(m_tJobName.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tJobName.lpdata,ReadValue("MCG2","Result"),0);
			return false;
		}

		cmbSelect->ResetContent();
		for(int i=1;i<=socketData->getQueryNum();i++)
		{
			m_tJobName=socketData->getTLV(i,2);
			cmbSelect->AddString((LPCTSTR)&m_tJobName.lpdata);
		}
		cmbSelect->SetCurSel(0);

	}
	catch(...)
	{
		MessageBox(NULL,ReadValue("MCG2","UM_Error_BuildComboBox"),ReadValue("MCG2","Error"),MB_ICONWARNING+MB_OK);
		return false;
	}
	return true;


}
// 构造ListBox
bool OperationCG2::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
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
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MCG2","Error"),MB_ICONWARNING+MB_OK);
			return false;
		}

		for(int i=1;i<socketData->getColTFLVNum();i++)
		{
			m_BGS = socketData->getTLV(1,i);
			ReadValue("MCG2",tagToStr(m_BGS.m_tagName));
			listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//插入列
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
					listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_Sex)//性别需要用文字显示
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//性别为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_male"));//显示为男
						}
						else//性别不为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_female"));//显示为女
						}
					}
					
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_GuildName)//公会名称需要用文字显示
					{
						if(!strcmp("NULL", (LPTSTR)&m_ConGS.lpdata)
							||!strcmp("0", (LPTSTR)&m_ConGS.lpdata)
							||!strcmp("", (LPTSTR)&m_ConGS.lpdata))//公会ID为0的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoGuild"));//显示为无公会
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_IsOnline)
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIA_Code_isOnline"));
						}
						else if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIA_Code_notOnline"));
						}

					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_Ip)
					{
						if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIA_Code_noIP"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_JobID)
					{
						if(!strcmp("NULL", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoProfession"));
						}
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoProfession"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_MapID)
					{
						if(!strcmp("NULL", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoMap"));
						}
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoMap"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_SkillName)
					{
						if(!strcmp("NULL", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoSkillName"));
						}
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoSkillName"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_InPrison)
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NotInPrison"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_InPrison"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_isUse)
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","SL_Hint_isUse"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_isChairman)
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_IsChairman"));
						}
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoChairman"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_tempRank)
					{
						if(!strcmp("NULL", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoRank"));
						}
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoRank"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_ProHonorRank)
					{
						if(!strcmp("NULL", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoRank"));
						}
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoRank"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_PetNewName)
					{
						if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoPetNewName"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_OwnName)
					{
						if(!strcmp("", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_NoOwnName"));
						}
					}
					if(m_ConGS.m_tagName == CEnumCore::TagName::CG2_category)
					{
						if(!strcmp("pet", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_CatePet"));
						}
						else if(!strcmp("item", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_CateItem"));
						}
						else if(!strcmp("skill", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_CateSkill"));
						}
						else if(!strcmp("char", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_CateChar"));
						}
						else if(!strcmp("account", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_CateAccount"));
						}
						else if(!strcmp("gold", (LPTSTR)&m_ConGS.lpdata))
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","UIC_Code_CateGold"));
						}
					}
					if(m_ConGS.m_tagName==CEnumCore::TagName::CG2_TypeName)
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//typename为0
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","BU_UI_STRBANTYPEROLE"));
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MCG2","BU_UI_STRBANTYPEACCOUNT"));
						}
					}
					
					/*else
					{
						listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
					}*/
				}

			}
		}
	}
	catch (...)
	{
		MessageBox(NULL,ReadValue("MCG2","UM_Error_BuildList"),ReadValue("MCG2","Error"),0);
	}
	return false;
}

//自己定义的复制函数
void OperationCG2::CopyListInfo(CListCtrl* m_listCtrl)
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
void OperationCG2::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
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
char* OperationCG2::tagToStr(CEnumCore::TagName tag)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH);
	switch(tag)
	{
	case CEnumCore::TagName::CG2_UserName:
		sprintf(strValue,"%s","CG2_UserName");
		break;
	case CEnumCore::TagName::CG2_UserID:
		sprintf(strValue,"%s","CG2_UserID");
		break;
	case CEnumCore::TagName::CG2_CharacterNum:
		sprintf(strValue,"%s","CG2_CharacterNum");
		break;
	case CEnumCore::TagName::CG2_Level:
		sprintf(strValue,"%s","CG2_Level");
		break;
	case CEnumCore::TagName::CG2_Exp:
		sprintf(strValue,"%s","CG2_Exp");
		break;
	case CEnumCore::TagName::CG2_Sex:
		sprintf(strValue,"%s","CG2_Sex");
		break;
	case CEnumCore::TagName::CG2_Money:
		sprintf(strValue,"%s","CG2_Money");
		break;
	case CEnumCore::TagName::CG2_Profession:
		sprintf(strValue,"%s","CG2_Profession");
		break;
	case CEnumCore::TagName::CG2_Guild:
		sprintf(strValue,"%s","CG2_Guild");
		break;
	case CEnumCore::TagName::CG2_CreateTime:
		sprintf(strValue,"%s","CG2_CreateTime");
		break;
	case CEnumCore::TagName::CG2_IsOnline:
		sprintf(strValue,"%s","CG2_IsOnline");
		break;
	case CEnumCore::TagName::CG2_Blood:
		sprintf(strValue,"%s","CG2_Blood");
		break;
	case CEnumCore::TagName::CG2_Magic:
		sprintf(strValue,"%s","CG2_Magic");
		break;
	case CEnumCore::TagName::CG2_MapID:
		sprintf(strValue,"%s","CG2_MapID");
		break;
	case CEnumCore::TagName::CG2_Coordinate:
		sprintf(strValue,"%s","CG2_Coordinate");
		break;
	case CEnumCore::TagName::CG2_Injured:
		sprintf(strValue,"%s","CG2_Injured");
		break;
	case CEnumCore::TagName::CG2_Status:
		sprintf(strValue,"%s","CG2_Status");
		break;
	case CEnumCore::TagName::CG2_ProfessionLevel:
		sprintf(strValue,"%s","CG2_ProfessionLevel");
		break;
	case CEnumCore::TagName::CG2_Honor:
		sprintf(strValue,"%s","CG2_Honor");
		break;
	case CEnumCore::TagName::CG2_SpecialName:
		sprintf(strValue,"%s","CG2_SpecialName");
		break;
	case CEnumCore::TagName::CG2_Charm:
		sprintf(strValue,"%s","CG2_Charm");
		break;
	case CEnumCore::TagName::CG2_InPrison:
		sprintf(strValue,"%s","CG2_InPrison");
		break;
	case CEnumCore::TagName::CG2_CharacterName:
		sprintf(strValue,"%s","CG2_CharacterName");
		break;
	case CEnumCore::TagName::CG2_OwnName:
		sprintf(strValue,"%s","CG2_OwnName");
		break;
	case CEnumCore::TagName::CG2_Fight:
		sprintf(strValue,"%s","CG2_Fight");
		break;
	case CEnumCore::TagName::CG2_LeftPoint:
		sprintf(strValue,"%s","CG2_LeftPoint");
		break;
	case CEnumCore::TagName::CG2_Physical:
		sprintf(strValue,"%s","CG2_Physical");
		break;
	case CEnumCore::TagName::CG2_Power:
		sprintf(strValue,"%s","CG2_Power");
		break;
	case CEnumCore::TagName::CG2_Smart:
		sprintf(strValue,"%s","CG2_Smart");
		break;
	case CEnumCore::TagName::CG2_Speed:
		sprintf(strValue,"%s","CG2_Speed");
		break;
	case CEnumCore::TagName::CG2_Spirit:
		sprintf(strValue,"%s","CG2_Spirit");
		break;
	case CEnumCore::TagName::CG2_MaxBlood:
		sprintf(strValue,"%s","CG2_MaxBlood");
		break;
	case CEnumCore::TagName::CG2_MaxMag:
		sprintf(strValue,"%s","CG2_MaxMag");
		break;
	case CEnumCore::TagName::CG2_Attack:
		sprintf(strValue,"%s","CG2_Attack");
		break;
	case CEnumCore::TagName::CG2_Defend:
		sprintf(strValue,"%s","CG2_Defend");
		break;
	case CEnumCore::TagName::CG2_MagAttack:
		sprintf(strValue,"%s","CG2_MagAttack");
		break;
	case CEnumCore::TagName::CG2_MagDefend:
		sprintf(strValue,"%s","CG2_MagDefend");
		break;
	case CEnumCore::TagName::CG2_Recover:
		sprintf(strValue,"%s","CG2_Recover");
		break;
	case CEnumCore::TagName::CG2_Hit:
		sprintf(strValue,"%s","CG2_Hit");
		break;
	case CEnumCore::TagName::CG2_Avoid:
		sprintf(strValue,"%s","CG2_Avoid");
		break;
	case CEnumCore::TagName::CG2_Critical:
		sprintf(strValue,"%s","CG2_Critical");
		break;
	case CEnumCore::TagName::CG2_Retort:
		sprintf(strValue,"%s","CG2_Retort");
		break;
	case CEnumCore::TagName::CG2_isChairman:
		sprintf(strValue,"%s","CG2_isChairman");
		break;
	case CEnumCore::TagName::CG2_ProHonorRank:
		sprintf(strValue,"%s","CG2_ProHonorRank");
		break;
	case CEnumCore::TagName::CG2_tempRank:
		sprintf(strValue,"%s","CG2_tempRank");
		break;
	case CEnumCore::TagName::CG2_RankID:
		sprintf(strValue,"%s","CG2_RankID");
		break;
	case CEnumCore::TagName::CG2_FriendIDKey:
		sprintf(strValue,"%s","CG2_FriendIDKey");
		break;
	case CEnumCore::TagName::CG2_FriendCharNum:
		sprintf(strValue,"%s","CG2_FriendCharNum");
		break;
	case CEnumCore::TagName::CG2_FriendShip:
		sprintf(strValue,"%s","CG2_FriendShip");
		break;
	case CEnumCore::TagName::CG2_SlotNum:
		sprintf(strValue,"%s","CG2_SlotNum");
		break;
	case CEnumCore::TagName::CG2_SkillName:
		sprintf(strValue,"%s","CG2_SkillName");
		break;
	case CEnumCore::TagName::CG2_SkillLevel:
		sprintf(strValue,"%s","CG2_SkillLevel");
		break;
	case CEnumCore::TagName::CG2_SkillExp:
		sprintf(strValue,"%s","CG2_SkillExp");
		break;
	case CEnumCore::TagName::CG2_EquipNum:
		sprintf(strValue,"%s","CG2_EquipNum");
		break;
	case CEnumCore::TagName::CG2_ItemColNum:
		sprintf(strValue,"%s","CG2_ItemColNum");
		break;
	case CEnumCore::TagName::CG2_CombineNum:
		sprintf(strValue,"%s","CG2_CombineNum");
		break;
	case CEnumCore::TagName::CG2_ItemName:
		sprintf(strValue,"%s","CG2_ItemName");
		break;
	case CEnumCore::TagName::CG2_QualityLevel:
		sprintf(strValue,"%s","CG2_QualityLevel");
		break;
	case CEnumCore::TagName::CG2_CurEndure:
		sprintf(strValue,"%s","CG2_CurEndure");
		break;
	case CEnumCore::TagName::CG2_MaxEndure:
		sprintf(strValue,"%s","CG2_MaxEndure");
		break;
	case CEnumCore::TagName::CG2_FixTimes:
		sprintf(strValue,"%s","CG2_FixTimes");
		break;
	case CEnumCore::TagName::CG2_ComposeTimes:
		sprintf(strValue,"%s","CG2_ComposeTimes");
		break;
	case CEnumCore::TagName::CG2_ComposeItemID:
		sprintf(strValue,"%s","CG2_ComposeItemID");
		break;
	case CEnumCore::TagName::CG2_StorageMoney:
		sprintf(strValue,"%s","CG2_StorageMoney");
		break;
	case CEnumCore::TagName::CG2_Serverip:
		sprintf(strValue,"%s","CG2_Serverip");
		break;
	case CEnumCore::TagName::CG2_nickname:
		sprintf(strValue,"%s","CG2_nickname");
		break;
	case CEnumCore::TagName::CG2_JobID:
		sprintf(strValue,"%s","CG2_JobID");
		break;
	case CEnumCore::TagName::CG2_GuildID:
		sprintf(strValue,"%s","CG2_GuildID");
		break;
	case CEnumCore::TagName::CG2_ProHonorRankID:
		sprintf(strValue,"%s","CG2_ProHonorRankID");
		break;
	case CEnumCore::TagName::CG2_logtime:
		sprintf(strValue,"%s","CG2_logtime");
		break;
	case CEnumCore::TagName::CG2_category:
		sprintf(strValue,"%s","CG2_category");
		break;
	case CEnumCore::TagName::CG2_action:
		sprintf(strValue,"%s","CG2_action");
		break;
	case CEnumCore::TagName::CG2_targetName:
		sprintf(strValue,"%s","CG2_targetName");
		break;
	case CEnumCore::TagName::CG2_targetIDKey:
		sprintf(strValue,"%s","CG2_targetIDKey");
		break;
	case CEnumCore::TagName::CG2_mgvalue:
		sprintf(strValue,"%s","CG2_mgvalue");
		break;
	case CEnumCore::TagName::CG2_mgstring:
		sprintf(strValue,"%s","CG2_mgstring");
		break;
	case CEnumCore::TagName::CG2_PetID:
		sprintf(strValue,"%s","CG2_PetID");
		break;
	case CEnumCore::TagName::CG2_PetStatus:
		sprintf(strValue,"%s","CG2_PetStatus");
		break;
	case CEnumCore::TagName::CG2_PetExp:
		sprintf(strValue,"%s","CG2_PetExp");
		break;
	case CEnumCore::TagName::CG2_PetBlood:
		sprintf(strValue,"%s","CG2_PetBlood");
		break;
	case CEnumCore::TagName::CG2_PetMag:
		sprintf(strValue,"%s","CG2_PetMag");
		break;
	case CEnumCore::TagName::CG2_PetInjured:
		sprintf(strValue,"%s","CG2_PetInjured");
		break;
	case CEnumCore::TagName::CG2_PetLostSoul:
		sprintf(strValue,"%s","CG2_PetLostSoul");
		break;
	case CEnumCore::TagName::CG2_PetRace:
		sprintf(strValue,"%s","CG2_PetRace");
		break;
	case CEnumCore::TagName::CG2_PetMaxSkillCol:
		sprintf(strValue,"%s","CG2_PetMaxSkillCol");
		break;
	case CEnumCore::TagName::CG2_PetSrcName:
		sprintf(strValue,"%s","CG2_PetSrcName");
		break;
	case CEnumCore::TagName::CG2_PetNewName:
		sprintf(strValue,"%s","CG2_PetNewName");
		break;
	case CEnumCore::TagName::CG2_PetFaith:
		sprintf(strValue,"%s","CG2_PetFaith");
		break;
	case CEnumCore::TagName::CG2_PetLeftPoint:
		sprintf(strValue,"%s","CG2_PetLeftPoint");
		break;
	case CEnumCore::TagName::CG2_PetPhysical:
		sprintf(strValue,"%s","CG2_PetPhysical");
		break;
	case CEnumCore::TagName::CG2_PetPower:
		sprintf(strValue,"%s","CG2_PetPower");
		break;
	case CEnumCore::TagName::CG2_PetSmart:
		sprintf(strValue,"%s","CG2_PetSmart");
		break;
	case CEnumCore::TagName::CG2_PetSpeed:
		sprintf(strValue,"%s","CG2_PetSpeed");
		break;
	case CEnumCore::TagName::CG2_PetSpirit:
		sprintf(strValue,"%s","CG2_PetSpirit");
        break;
	case CEnumCore::TagName::CG2_PetMaxBlood:
		sprintf(strValue,"%s","CG2_PetMaxBlood");
		break;
	case CEnumCore::TagName::CG2_PetMaxMag:
		sprintf(strValue,"%s","CG2_PetMaxMag");
		break;
	case CEnumCore::TagName::CG2_PetAttack:
		sprintf(strValue,"%s","CG2_PetAttack");
		break;
	case CEnumCore::TagName::CG2_PetDefend:
		sprintf(strValue,"%s","CG2_PetDefend");
		break;
	case CEnumCore::TagName::CG2_PetCheesy:
		sprintf(strValue,"%s","CG2_PetCheesy");
		break;
	case CEnumCore::TagName::CG2_PetMagAttack:
		sprintf(strValue,"%s","CG2_PetMagAttack");
		break;
	case CEnumCore::TagName::CG2_PetMagDefend:
		sprintf(strValue,"%s","CG2_PetMagDefend");
		break;
	case CEnumCore::TagName::CG2_PetRecover:
		sprintf(strValue,"%s","CG2_PetRecover");
		break;
	case CEnumCore::TagName::CG2_PetHit:
		sprintf(strValue,"%s","CG2_PetHit");
		break;
	case CEnumCore::TagName::CG2_PetAvoid:
		sprintf(strValue,"%s","CG2_PetAvoid");
		break;
	case CEnumCore::TagName::CG2_PetCritical:
		sprintf(strValue,"%s","CG2_PetCritical");
		break;
	case CEnumCore::TagName::CG2_PetRetort:
		sprintf(strValue,"%s","CG2_PetRetort");
		break;
	case CEnumCore::TagName::CG2_PetEvolveTimes:
		sprintf(strValue,"%s","CG2_PetEvolveTimes");
		break;
	case CEnumCore::TagName::CG2_PetSatisfLvl:
		sprintf(strValue,"%s","CG2_PetSatisfLvl");
		break;
	case CEnumCore::TagName::CG2_PetFullLvl:
		sprintf(strValue,"%s","CG2_PetFullLvl");
		break;
	case CEnumCore::TagName::CG2_PetColNum:
		sprintf(strValue,"%s","CG2_PetColNum");
		break;
	case CEnumCore::TagName::CG2_PetItemCol:
		sprintf(strValue,"%s","CG2_PetItemCol");
		break;
	case CEnumCore::TagName::CG2_PetItemID:
		sprintf(strValue,"%s","CG2_PetItemID");
		break;
	case CEnumCore::TagName::CG2_PetItemGetTime:
		sprintf(strValue,"%s","CG2_PetItemGetTime");
		break;
	case CEnumCore::TagName::CG2_PetCombineNum:
		sprintf(strValue,"%s","CG2_PetCombineNum");
		break;
	case CEnumCore::TagName::CG2_PetQulityLvl:
		sprintf(strValue,"%s","CG2_PetQulityLvl");
		break;
	case CEnumCore::TagName::CG2_PetCurEndure:
		sprintf(strValue,"%s","CG2_PetCurEndure");
		break;
	case CEnumCore::TagName::CG2_PetMaxEndure:
		sprintf(strValue,"%s","CG2_PetMaxEndure");
		break;
	case CEnumCore::TagName::CG2_PetFixTimes:
		sprintf(strValue,"%s","CG2_PetFixTimes");
		break;
	case CEnumCore::TagName::CG2_PetComposeTimes:
		sprintf(strValue,"%s","CG2_PetComposeTimes");
		break;
	case CEnumCore::TagName::CG2_PetComposeItemID:
		sprintf(strValue,"%s","CG2_PetComposeItemID");
		break;
	case CEnumCore::TagName::CG2_PetSkillID:
		sprintf(strValue,"%s","CG2_PetSkillID");
		break;
	case CEnumCore::TagName::CG2_PetSkillLvl:
		sprintf(strValue,"%s","CG2_PetSkillLvl");
		break;
	case CEnumCore::TagName::CG2_PetSkillExp:
		sprintf(strValue,"%s","CG2_PetSkillExp");
		break;
	case CEnumCore::TagName::CG2_PetSkillColNum:
		sprintf(strValue,"%s","CG2_PetSkillColNum");
		break;
	case CEnumCore::TagName::CG2_UserNum:
		sprintf(strValue,"%s","CG2_UserNum");
		break;
	case CEnumCore::TagName::CG2_LatestLoginTime:
		sprintf(strValue,"%s","CG2_LatestLoginTime");
		break;
	case CEnumCore::TagName::CG2_LatestLogoutTime:
		sprintf(strValue,"%s","CG2_LatestLogoutTime");
		break;
	case CEnumCore::TagName::CG2_LoginIP:
		sprintf(strValue,"%s","CG2_LoginIP");
		break;
	case CEnumCore::TagName::CG2_isAdult:
		sprintf(strValue,"%s","CG2_isAdult");
		break;
	case CEnumCore::TagName::CG2_hasLockedItem:
		sprintf(strValue,"%s","CG2_hasLockedItem");
		break;
	case CEnumCore::TagName::CG2_Fame:
		sprintf(strValue,"%s","CG2_Fame");
		break;
	case CEnumCore::TagName::CG2_titleFlags1:
		sprintf(strValue,"%s","CG2_titleFlags1");
		break;
	case CEnumCore::TagName::CG2_titleFlags2:
		sprintf(strValue,"%s","CG2_titleFlags2");
		break;
	case CEnumCore::TagName::CG2_titleFlags3:
		sprintf(strValue,"%s","CG2_titleFlags3");
		break;
	case CEnumCore::TagName::CG2_titleFlags4:
		sprintf(strValue,"%s","CG2_titleFlags4");
		break;
	case CEnumCore::TagName::CG2_titleFlags5:
		sprintf(strValue,"%s","CG2_titleFlags5");
		break;
	case CEnumCore::TagName::CG2_titleFlags6:
		sprintf(strValue,"%s","CG2_titleFlags6");
		break;
	case CEnumCore::TagName::CG2_titleFlags7:
		sprintf(strValue,"%s","CG2_titleFlags7");
		break;
	case CEnumCore::TagName::CG2_titleFlags8:
		sprintf(strValue,"%s","CG2_titleFlags8");
		break;
	case CEnumCore::TagName::CG2_titleFlags9:
		sprintf(strValue,"%s","CG2_titleFlags9");
		break;
	case CEnumCore::TagName::CG2_titleFlags10:
		sprintf(strValue,"%s","CG2_titleFlags10");
		break;
	case CEnumCore::TagName::CG2_titleFlags11:
		sprintf(strValue,"%s","CG2_titleFlags11");
		break;
	case CEnumCore::TagName::CG2_titleFlags12:
		sprintf(strValue,"%s","CG2_titleFlags12");
		break;
	case CEnumCore::TagName::CG2_titleFlags13:
		sprintf(strValue,"%s","CG2_titleFlags13");
		break;
	case CEnumCore::TagName::CG2_titleFlags14:
		sprintf(strValue,"%s","CG2_titleFlags14");
		break;
	case CEnumCore::TagName::CG2_titleFlags15:
		sprintf(strValue,"%s","CG2_titleFlags15");
		break;
	case CEnumCore::TagName::CG2_titleFlags16:
		sprintf(strValue,"%s","CG2_titleFlags16");
		break;
	case CEnumCore::TagName::CG2_titleFlags17:
		sprintf(strValue,"%s","CG2_titleFlags17");
		break;
	case CEnumCore::TagName::CG2_titleFlags18:
		sprintf(strValue,"%s","CG2_titleFlags18");
		break;
	case CEnumCore::TagName::CG2_titleFlags19:
		sprintf(strValue,"%s","CG2_titleFlags19");
		break;
	case CEnumCore::TagName::CG2_titleFlags20:
		sprintf(strValue,"%s","CG2_titleFlags20");
		break;
	case CEnumCore::TagName::CG2_titleFlags21:
		sprintf(strValue,"%s","CG2_titleFlags21");
		break;
	case CEnumCore::TagName::CG2_titleFlags22:
		sprintf(strValue,"%s","CG2_titleFlags22");
		break;
	case CEnumCore::TagName::CG2_titleFlags23:
		sprintf(strValue,"%s","CG2_titleFlags23");
		break;
	case CEnumCore::TagName::CG2_titleFlags24:
		sprintf(strValue,"%s","CG2_titleFlags24");
		break;
	case CEnumCore::TagName::CG2_titleFlags25:
		sprintf(strValue,"%s","CG2_titleFlags25");
		break;
	case CEnumCore::TagName::CG2_titleFlags26:
		sprintf(strValue,"%s","CG2_titleFlags26");
		break;
	case CEnumCore::TagName::CG2_titleFlags27:
		sprintf(strValue,"%s","CG2_titleFlags27");
		break;
	case CEnumCore::TagName::CG2_titleFlags28:
		sprintf(strValue,"%s","CG2_titleFlags28");
		break;
	case CEnumCore::TagName::CG2_titleFlags29:
		sprintf(strValue,"%s","CG2_titleFlags29");
    	break;
	case CEnumCore::TagName::CG2_titleFlags30:
		sprintf(strValue,"%s","CG2_titleFlags30");
		break;
	case CEnumCore::TagName::CG2_MapName:
		sprintf(strValue,"%s","CG2_MapName");
		break;
	case CEnumCore::TagName::CG2_TypeName:
		sprintf(strValue,"%s","CG2_TypeName");
		break;
	case CEnumCore::TagName::CG2_TypeID:
		sprintf(strValue,"%s","CG2_TypeID");
		break;
	case CEnumCore::TagName::CG2_CharNo:
		sprintf(strValue,"%s","CG2_CharNo");
		break;
	case CEnumCore::TagName::CG2_Title:
		sprintf(strValue,"%s","CG2_Title");
		break;
	case CEnumCore::TagName::CG2_Content:
		sprintf(strValue,"%s","CG2_Content");
		break;
	case CEnumCore::TagName::CG2_BanTime:
		sprintf(strValue,"%s","CG2_BanTime");
		break;
	case CEnumCore::TagName::CG2_NoteContent:
		sprintf(strValue,"%s","CG2_NoteContent");
		break;
	case CEnumCore::TagName::CG2_Interval:
		sprintf(strValue,"%s","CG2_Interval");
		break;
	case CEnumCore::TagName::CG2_StartTime:
		sprintf(strValue,"%s","CG2_StartTime");
		break;
	case CEnumCore::TagName::CG2_EndTime:
		sprintf(strValue,"%s","CG2_EndTime");
		break;
	case CEnumCore::TagName::CG2_NoticeID:
		sprintf(strValue,"%s","CG2_NoticeID");
		break;
	case CEnumCore::TagName::CG2_Times:
		sprintf(strValue,"%s","CG2_Times");
		break;
	case CEnumCore::TagName::CG2_Cheesy:
		sprintf(strValue,"%s","CG2_Cheesy");
		break;
	case CEnumCore::TagName::CG2_GuildName:
		sprintf(strValue,"%s","CG2_GuildName");
		break;
	case CEnumCore::TagName::CG2_GuildNum:
		sprintf(strValue,"%s","CG2_GuildNum");
		break;
	case CEnumCore::TagName::CG2_GuildHoro:
		sprintf(strValue,"%s","CG2_GuildHoro");
		break;
	case CEnumCore::TagName::CG2_GuildRank:
		sprintf(strValue,"%s","CG2_GuildRank");
		break;
	case CEnumCore::TagName::CG2_Master:
		sprintf(strValue,"%s","CG2_Master");
		break;
	case CEnumCore::TagName::CG2_MasterIdkey:
		sprintf(strValue,"%s","CG2_MasterIdkey");
		break;
	case CEnumCore::TagName::CG2_Ip:
		sprintf(strValue,"%s","CG2_Ip");
		break;
	case CEnumCore::TagName::CG2_SkillID:
		sprintf(strValue,"%s","CG2_SkillID");
		break;
	case CEnumCore::TagName::CG2_SkillType:
		sprintf(strValue,"%s","CG2_SkillType");
		break;
	case CEnumCore::TagName::CG2_PetSkillName:
		sprintf(strValue,"%s","CG2_PetSkillName");
		break;
	case CEnumCore::TagName::CG2_ItemNum:
		sprintf(strValue,"%s","CG2_ItemNum");
		break;
	case CEnumCore::TagName::CG2_Palette:
		sprintf(strValue,"%s","CG2_Palette");
		break;
	case CEnumCore::TagName::CG2_Wind:
		sprintf(strValue,"%s","CG2_Wind");
		break;
	case CEnumCore::TagName::CG2_Frie:
		sprintf(strValue,"%s","CG2_Frie");
		break;
	case CEnumCore::TagName::CG2_Water:
		sprintf(strValue,"%s","CG2_Water");
		break;
	case CEnumCore::TagName::CG2_Soil:
		sprintf(strValue,"%s","CG2_Soil");
		break;
	case CEnumCore::TagName::CG2_userItemName:
		sprintf(strValue,"%s","CG2_userItemName");
		break;
	case CEnumCore::TagName::CG2_Sn:
		sprintf(strValue,"%s","CG2_Sn");
		break;
	case CEnumCore::TagName::CG2_ServerName:
		sprintf(strValue,"%s","CG2_ServerName");
		break;
	case CEnumCore::TagName::CG2_Date:
		sprintf(strValue,"%s","CG2_Date");
		break;
	case CEnumCore::TagName::CG2_isVIP:
		sprintf(strValue,"%s","CG2_isVIP");
		break;
	case CEnumCore::TagName::CG2_isUse:
		sprintf(strValue,"%s","CG2_isUse");
		break;
	case CEnumCore::TagName::CG2_Email:
		sprintf(strValue,"%s","CG2_Email");
		break;
	case CEnumCore::TagName::CG2_ItemPass:
		sprintf(strValue,"%s","CG2_ItemPass");
		break;
	case CEnumCore::TagName::CG2_TempPwd:
		sprintf(strValue,"%s","CG2_TempPwd");
		break;
	case CEnumCore::TagName::CG2_SendUser:
		sprintf(strValue,"%s","CG2_SendUser");
		break;
	case CEnumCore::TagName::CG2_RecvUser:
		sprintf(strValue,"%s","CG2_RecvUser");
		break;
	case CEnumCore::TagName::CG2_ItemType:
		sprintf(strValue,"%s","CG2_ItemType");
		break;
	case CEnumCore::TagName::CG2_LimitTime:
		sprintf(strValue,"%s","CG2_LimitTime");
		break;
	case CEnumCore::TagName::CG2_GetTime:
		sprintf(strValue,"%s","CG2_GetTime");
		break;
	case CEnumCore::TagName::CG2_Pwd:
		sprintf(strValue,"%s","CG2_Pwd");
		break;

	case CEnumCore::TagName::SD_UserName_Old:
		sprintf(strValue,"%s","SD_UserName_Old");
		break;
	case CEnumCore::TagName::CG2_From_PetID:
		sprintf(strValue,"%s","CG2_From_PetID");
		break;
	case CEnumCore::TagName::CG2_To_PetID:
		sprintf(strValue,"%s","CG2_To_PetID");
		break;
	case CEnumCore::TagName::CG2_From_PetName:
		sprintf(strValue,"%s","CG2_From_PetName");
		break;
	case CEnumCore::TagName::CG2_To_PetName:
		sprintf(strValue,"%s","CG2_To_PetName");
		break;
	case CEnumCore::TagName::CG2_getMoney:
		sprintf(strValue,"%s","CG2_getMoney");
		break;
	case CEnumCore::TagName::CG2_From_UserName:
		sprintf(strValue,"%s","CG2_From_UserName");
		break;
	case CEnumCore::TagName::CG2_To_UserName:
		sprintf(strValue,"%s","CG2_To_UserName");
		break;
	case CEnumCore::TagName::CG2_From_UserID:
		sprintf(strValue,"%s","CG2_From_UserID");
		break;
	case CEnumCore::TagName::CG2_To_UserID:
		sprintf(strValue,"%s","CG2_To_UserID");
		break;
	case CEnumCore::TagName::CG2_LeftMoney:
		sprintf(strValue,"%s","CG2_LeftMoney");
		break;
	case CEnumCore::TagName::UserByID:
		sprintf(strValue,"%s","UserByID");
		break;
	case CEnumCore::TagName::BeginTime:
		sprintf(strValue,"%s","BeginTime");
		break;
	case CEnumCore::TagName::EndTime:
		sprintf(strValue,"%s","EndTime");
		break;
	case CEnumCore::TagName::ServerInfo_IP :
		sprintf(strValue,"%s","ServerInfo_IP ");
		break;
		//maple add
	case CEnumCore::TagName::CG2_CharName:
		sprintf(strValue,"%s","CG2_CharName");
		break;
	case CEnumCore::TagName::CG2_LevelValue:
		sprintf(strValue,"%s","CG2_LevelValue");
		break;
	case CEnumCore::TagName::CG2_LevelResult:
		sprintf(strValue,"%s","CG2_LevelResult");
		break;
	case CEnumCore::TagName::CG2_ActionTime:
		sprintf(strValue,"%s","CG2_ActionTime");
		break;
	//new add
	case CEnumCore::TagName::CG2_iReserve00:
		sprintf(strValue,"%s","CG2_iReserve00");
		break;
	case CEnumCore::TagName::CG2_BugIndex:
		sprintf(strValue,"%s","CG2_BugIndex");
		break;
	case CEnumCore::TagName::CG2_SoilIndex:
		sprintf(strValue,"%s","CG2_SoilIndex");
		break;
	case CEnumCore::TagName::CG2_NutrientIndex:
		sprintf(strValue,"%s","CG2_NutrientIndex");
		break;
	case CEnumCore::TagName::CG2_TreeState:
		sprintf(strValue,"%s","CG2_TreeState");
		break;
	case CEnumCore::TagName::CG2_FruitNum:
		sprintf(strValue,"%s","CG2_FruitNum");
		break;

	case CEnumCore::TagName::CG2_Dates:
		sprintf(strValue,"%s","CG2_Dates");
		break;
	case CEnumCore::TagName::CG2_Marriage:
		sprintf(strValue,"%s","CG2_Marriage");
		break;
	case CEnumCore::TagName::CG2_Spouse:
		sprintf(strValue,"%s","CG2_Spouse");
		break;
	case CEnumCore::TagName::CG2_MyIndex:
		sprintf(strValue,"%s","CG2_MyIndex");
		break;
	case CEnumCore::TagName::CG2_IsBooking:
		sprintf(strValue,"%s","CG2_IsBooking");
		break;
	case CEnumCore::TagName::CG2_MarriageTime:
		sprintf(strValue,"%s","CG2_MarriageTime");
		break;
	case CEnumCore::TagName::CG2_Gmsv:
		sprintf(strValue,"%s","CG2_Gmsv");
		break;
	case CEnumCore::TagName::CG2_ID:
		sprintf(strValue,"%s","CG2_ID");
		break;
	case CEnumCore::TagName::CG2_Shop_RECYCLE:
		sprintf(strValue,"%s","CG2_Shop_RECYCLE");
		break;
	default:
		sprintf(strValue,"%s","UnKnown");
		break;
	}
	return strValue;
}

// 显示操作结果
void OperationCG2::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MCG2","Success"),ReadValue("MCG2","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MCG2","Failure"),ReadValue("MCG2","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MCG2","Result"),0);
	}
}
