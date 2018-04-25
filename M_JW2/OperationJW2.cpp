#include "stdafx.h"
#include "OperationJW2.h"

OperationJW2::OperationJW2()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
}
OperationJW2::~OperationJW2()
{
}
//设置SOCKET
void OperationJW2::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}
// 读取ini文件里面的值
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

// 读取ini文件里面的数字
int OperationJW2::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MJW2.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//通过行号和列名得到相应的值
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

// 获取游戏服务器列表
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

//发送查询请求
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

//发送查询请求
bool OperationJW2::SendQuery(unsigned char* sendData,int allLength,CEnumCore::Msg_Category m_category,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		CPacketHead packethead;

		packethead.Create(allLength);
		packethead.AddHeader(1,m_category,m_ServiceKey,allLength);//给数据包添加头信息

		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);//构造并加密最后要发送的数据包
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))//发送数据
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
//再次发送同样的Query
bool OperationJW2::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//发送数据
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

// 构造复选框
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

// 构造用户列表
bool OperationJW2::BuildComboxUser(CSocketData* psocketData,CComboBox* cmbSelect)
{
	try
	{
		CGlobalStruct::TFLV m_tSvrCity;
		cmbSelect->ResetContent();//清空复选框的内容

		m_tSvrCity = psocketData->getTLV(1,1);
		if(m_tSvrCity.m_tagName == CEnumCore::TagName::MESSAGE)
		{
			MessageBox(NULL,(LPCSTR)&m_tSvrCity.lpdata,ReadValue("MGM","Result"),0);
			return false;
		}

		for(int i=1;i<=psocketData->getQueryNum();i++)
		{
			//////m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::RealName);//获取要添加的数据内容//////UserName
			m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::UserName);//maple add
			cmbSelect->AddString((LPCTSTR)&m_tSvrCity.lpdata);//将得到的数据内容保存在复选框中
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

// 构造ListBox
bool OperationJW2::BuildDataTable(CSocketData* socketData,CListCtrl* listCtrlS,int* pageCount)
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
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,ReadValue("MJW2","Error"),MB_ICONWARNING+MB_OK);
			return false;
		}

		for(int i=1;i<socketData->getColTFLVNum();i++)
		{
			m_BGS = socketData->getTLV(1,i);
			ReadValue("MJW2",tagToStr(m_BGS.m_tagName));
			listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//插入列
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
					if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_Sex)//性别需要用文字显示
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//性别为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_Male"));//显示为男
						}
						else//性别不为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_Female"));//显示为女
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_UseItem)//显示是否在使用中
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_IsUse"));//在使用中
						}
						else//状态不为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_NotUse"));//没有在使用
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_GOODSTYPE)//显示购买类型
					{
						if(!strcmp("77", (LPTSTR)&m_ConGS.lpdata))//状态为M的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_BuyByM"));//显示用M币购买
						}
						else if(!strcmp("71", (LPTSTR)&m_ConGS.lpdata))//状态为G的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_BuyByG"));//显示用G币购买
						}
						else//其它状态
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_ALL"));
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_BUGLETYPE)//显示喇叭类型
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//状态为0的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_BugleTypeM"));//显示用M币发送的小喇叭
						}
						else if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_AllBugleTypeM"));//显示用M币发送的全区喇叭
						}
						else if(!strcmp("10", (LPTSTR)&m_ConGS.lpdata))//状态为0的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_BugleTypeP"));//显示用积分发送的小喇叭
						}
						else if(!strcmp("11", (LPTSTR)&m_ConGS.lpdata))//状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","UIC_Code_AllBugleTypeP"));//显示用积分发送的全区喇叭
						}
						else//其它状态
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_Status)//显示公告发送类型
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//状态为0的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","NI_UI_UnSend"));//显示为未发送
						}
						else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))//状态为2的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","NI_UI_Sending"));//显示为发送中
						}
						else//其它状态
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_LOGINTYPE)//显示登陆类型
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//状态为0的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","LI_UI_Login"));//显示为登入
						}
						else if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","LI_UI_Logout"));//显示为登出
						}
						else//其它状态
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_ItemPos)//显示物品位置
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//状态为0的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","IM_Pos_Body"));//显示为身上
						}
						else if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","IM_Pos_WuBin"));//显示为物品栏
						}
						else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))//状态为2的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MJW2","IM_Pos_liWu"));//显示为礼物栏
						}
						else
						{
							listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::JW2_MoneyType)//显示消费类型
					{
						if(!strcmp("0", (LPTSTR)&m_ConGS.lpdata))//状态为0的话
						{
							listCtrlS->SetItemText(nRow,k-1,"喂养宠物m币");//显示为身上
						}
						else if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,"进化宠物m币");//显示为物品栏
						}
						else if(!strcmp("2", (LPTSTR)&m_ConGS.lpdata))//状态为2的话
						{
							listCtrlS->SetItemText(nRow,k-1,"买动作m币");//显示为礼物栏
						}
						else if(!strcmp("3", (LPTSTR)&m_ConGS.lpdata))//状态为2的话
						{
							listCtrlS->SetItemText(nRow,k-1,"信纸m币");//显示为礼物栏
						}
						else if(!strcmp("4", (LPTSTR)&m_ConGS.lpdata))//状态为0的话
						{
							listCtrlS->SetItemText(nRow,k-1,"发信g币");//显示为身上
						}
						else if(!strcmp("5", (LPTSTR)&m_ConGS.lpdata))//状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,"创建家族g币");//显示为物品栏
						}
						else if(!strcmp("6", (LPTSTR)&m_ConGS.lpdata))//状态为2的话
						{
							listCtrlS->SetItemText(nRow,k-1,"创建家族M币");//显示为礼物栏
						}
						else if(!strcmp("7", (LPTSTR)&m_ConGS.lpdata))//状态为2的话
						{
							listCtrlS->SetItemText(nRow,k-1,"换肤色m币");//显示为礼物栏
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

//自己定义的复制函数
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
void OperationJW2::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
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
	case CEnumCore::TagName::JW2_AvatarItem://道具ID
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
	case CEnumCore::TagName::JW2_RECEID://接受人的ID（如果相同是本人）
		sprintf(strValue,"%s","JW2_RECEID");
		break;
	case CEnumCore::TagName::JW2_AvatarItemName://道具名称
		sprintf(strValue,"%s","JW2_AvatarItemName");
		break;
	case CEnumCore::TagName::JW2_MALESN://男性SN
		sprintf(strValue,"%s","JW2_MALESN");
		break;
	case CEnumCore::TagName::JW2_MALEUSERNAME://男性用户名
		sprintf(strValue,"%s","JW2_MALEUSERNAME");
		break;
	case CEnumCore::TagName::JW2_MALEUSERNICK://男性昵称
		sprintf(strValue,"%s","JW2_MALEUSERNICK");
		break;
	case CEnumCore::TagName::JW2_FEMAILESN://女性SN
		sprintf(strValue,"%s","JW2_FEMAILESN");
		break;
	case CEnumCore::TagName::JW2_FEMALEUSERNAME://女性用户名
		sprintf(strValue,"%s","JW2_FEMALEUSERNAME");
		break;
	case CEnumCore::TagName::JW2_FEMAILEUSERNICK://女性昵称
		sprintf(strValue,"%s","JW2_FEMAILEUSERNICK");
		break;
	case CEnumCore::TagName::JW2_WEDDINGDATE://结婚时间
		sprintf(strValue,"%s","JW2_WEDDINGDATE");
		break;
	case CEnumCore::TagName::JW2_UNWEDDINGDATE://离婚时间
		sprintf(strValue,"%s","JW2_UNWEDDINGDATE");
		break;
	case CEnumCore::TagName::JW2_WEDDINGNAME://婚礼名称
		sprintf(strValue,"%s","JW2_WEDDINGNAME");
		break;
	case CEnumCore::TagName::JW2_WEDDINGVOW://婚礼誓言
		sprintf(strValue,"%s","JW2_WEDDINGVOW");
		break;
	case CEnumCore::TagName::JW2_RINGLEVEL://戒指等级
		sprintf(strValue,"%s","JW2_RINGLEVEL");
		break;
	case CEnumCore::TagName::JW2_REDHEARTNUM://红心数量
		sprintf(strValue,"%s","JW2_REDHEARTNUM");
		break;
	case CEnumCore::TagName::JW2_WEDDINGNO://婚姻序号
		sprintf(strValue,"%s","JW2_WEDDINGNO");
		break;
	case CEnumCore::TagName::JW2_CONFIRMSN://见证者SN
		sprintf(strValue,"%s","JW2_CONFIRMSN");
		break;
	case CEnumCore::TagName::JW2_CONFIRMUSERNAME://见证者用户名
		sprintf(strValue,"%s","JW2_CONFIRMUSERNAME");
		break;
	case CEnumCore::TagName::JW2_CONFIRMUSERNICK://见证者昵称
		sprintf(strValue,"%s","JW2_CONFIRMUSERNICK");
		break;
	case CEnumCore::TagName::JW2_COUPLEDATE://情侣日期
		sprintf(strValue,"%s","JW2_COUPLEDATE");
		break;
	case CEnumCore::TagName::JW2_KISSNUM://kiss次数
		sprintf(strValue,"%s","JW2_KISSNUM");
		break;
	case CEnumCore::TagName::JW2_LASTKISSDATE://最后一次Kiss时间
		sprintf(strValue,"%s","JW2_LASTKISSDATE");
		break;
	case CEnumCore::TagName::JW2_BREAKDATE://分手时间
		sprintf(strValue,"%s","JW2_BREAKDATE");
		break;
	case CEnumCore::TagName::JW2_CMBREAKDATE://确认分手时间
		sprintf(strValue,"%s","JW2_CMBREAKDATE");
		break;
	case CEnumCore::TagName::JW2_BREAKSN://提出SN
		sprintf(strValue,"%s","JW2_BREAKSN");
		break;
	case CEnumCore::TagName::JW2_BREAKUSERNAME://提出用户名
		sprintf(strValue,"%s","JW2_BREAKUSERNAME");
		break;
	case CEnumCore::TagName::JW2_BREAKUSERNICK://提出昵称
		sprintf(strValue,"%s","JW2_BREAKUSERNICK");
		break;
	case CEnumCore::TagName::JW2_LASTLOGINDATE://最后登陆时间
		sprintf(strValue,"%s","JW2_LASTLOGINDATE");
		break;
	case CEnumCore::TagName::JW2_REGISTDATE://激活时间
		sprintf(strValue,"%s","JW2_REGISTDATE");
		break;
	case CEnumCore::TagName::JW2_FCMSTATUS://防沉迷状态
		sprintf(strValue,"%s","JW2_FCMSTATUS");
		break;
	case CEnumCore::TagName::JW2_FAMILYID://家族ID
		sprintf(strValue,"%s","JW2_FAMILYID");
		break;
	case CEnumCore::TagName::JW2_FAMILYNAME://家族名称
		sprintf(strValue,"%s","JW2_FAMILYNAME");
		break;
	case CEnumCore::TagName::JW2_DUTYID://职业号
		sprintf(strValue,"%s","JW2_DUTYID");
		break;
	case CEnumCore::TagName::JW2_DUTYNAME://职业名
		sprintf(strValue,"%s","JW2_DUTYNAME");
		break;
	case CEnumCore::TagName::JW2_ATTENDTIME://加入时间
		sprintf(strValue,"%s","JW2_ATTENDTIME");
		break;
	case CEnumCore::TagName::JW2_COUPLESN://情侣序号
		sprintf(strValue,"%s","JW2_COUPLESN");
		break;
	case CEnumCore::TagName::JW2_CREATETIME://创建时间
		sprintf(strValue,"%s","JW2_CREATETIME");
		break;
	case CEnumCore::TagName::JW2_CNT://人数
		sprintf(strValue,"%s","JW2_CNT");
		break;
	case CEnumCore::TagName::JW2_POINT://积分
		sprintf(strValue,"%s","JW2_POINT");
		break;
	case CEnumCore::TagName::JW2_LOGINTYPE://类型0登入，1登出
		sprintf(strValue,"%s","JW2_LOGINTYPE");
		break;
	case CEnumCore::TagName::JW2_TIME://时间
		sprintf(strValue,"%s","JW2_TIME");
		break;
	case CEnumCore::TagName::JW2_IP://IP地址
		sprintf(strValue,"%s","JW2_IP");
		break;
	case CEnumCore::TagName::JW2_ItemPos://物品位置
		sprintf(strValue,"JW2_ItemPos");
		break;
	case CEnumCore::TagName::JW2_MailTitle://物品主题
		sprintf(strValue,"JW2_MailTitle");
		break;
	case CEnumCore::TagName::JW2_MailContent://邮件内容
		sprintf(strValue,"JW2_MailContent");
		break;
	case CEnumCore::TagName::JW2_ItemNo://物品序号
		sprintf(strValue,"JW2_ItemNo");
		break;
	case CEnumCore::TagName::JW2_Repute://声望
		sprintf(strValue,"JW2_Repute");
		break;
	case CEnumCore::TagName::JW2_NowTitle://称号
		sprintf(strValue,"JW2_NowTitle");
		break;
	case CEnumCore::TagName::JW2_FamilyLevel://等级
		sprintf(strValue,"JW2_FamilyLevel");
		break;
	case CEnumCore::TagName::JW2_AttendRank://人气排名
		sprintf(strValue,"JW2_AttendRank");
		break;
	case CEnumCore::TagName::JW2_MoneyRank://财富排名
		sprintf(strValue,"JW2_MoneyRank");
		break;
	case CEnumCore::TagName::JW2_PowerRank://实力排名
		sprintf(strValue,"JW2_PowerRank");
		break;
	case CEnumCore::TagName::JW2_ItemCode://道具ID
		sprintf(strValue,"JW2_ItemCode");
		break;
	case CEnumCore::TagName::JW2_ItemName://道具名称
		sprintf(strValue,"JW2_ItemName");
		break;
	case CEnumCore::TagName::JW2_Productid://商品ID
		sprintf(strValue,"JW2_Productid");
		break;
	case CEnumCore::TagName::JW2_ProductName://商品名称
		sprintf(strValue,"JW2_ProductName");
		break;
	case CEnumCore::TagName::JW2_FamilyPoint://家族点数
		sprintf(strValue,"JW2_FamilyPoint");
		break;
	case CEnumCore::TagName::JW2_PetSn://宠物ID
		sprintf(strValue,"JW2_PetSn");
		break;
	case CEnumCore::TagName::JW2_PetName://宠物名称
		sprintf(strValue,"JW2_PetName");
		break;
	case CEnumCore::TagName::JW2_PetNick://宠物自定义名称
		sprintf(strValue,"JW2_PetNick");
		break;
	case CEnumCore::TagName::JW2_PetLevel://宠物等级
		sprintf(strValue,"JW2_PetLevel");
		break;
	case CEnumCore::TagName::JW2_PetExp://宠物经验
		sprintf(strValue,"JW2_PetExp");
		break;
	case CEnumCore::TagName::JW2_PetEvol://宠物名称
		sprintf(strValue,"JW2_PetEvol");
		break;
	case CEnumCore::TagName::JW2_MailSn://序列号
		sprintf(strValue,"JW2_MailSn");
		break;
	case CEnumCore::TagName::JW2_SendNick://发件人昵称
		sprintf(strValue,"JW2_SendNick");
		break;
	case CEnumCore::TagName::JW2_SendDate://发送日期
		sprintf(strValue,"JW2_SendDate");
		break;
	case CEnumCore::TagName::JW2_Num://数量
		sprintf(strValue,"JW2_Num");
		break;
	case CEnumCore::TagName::JW2_Rate://男女比例
		sprintf(strValue,"JW2_Rate");
		break;
	case CEnumCore::TagName::JW2_ShaikhNick://族长名称
		sprintf(strValue,"JW2_ShaikhNick");
		break;
	case CEnumCore::TagName::JW2_SubFamilyName://隶属家族名称
		sprintf(strValue,"JW2_SubFamilyName");
		break;
	case CEnumCore::TagName::JW2_MoneyType://消费类型
		sprintf(strValue,"JW2_MoneyType");
		break;
	case CEnumCore::TagName::JW2_BeforeCash://消费前钱
		sprintf(strValue,"JW2_BeforeCash");
		break;
	case CEnumCore::TagName::JW2_AfterCash://消费前钱
		sprintf(strValue,"JW2_AfterCash");
		break;
	case CEnumCore::TagName::JW2_ProductPrice://道具单价
		sprintf(strValue,"JW2_ProductPrice");
		break;
	case CEnumCore::TagName::JW2_ServerName://服务器名称
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

// 显示操作结果
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
