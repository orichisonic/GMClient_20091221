#include "stdafx.h"
#include "OperationGM.h"

OperationGM::OperationGM()
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );//将全局变量置零
	intGM = NULL;
}
OperationGM::~OperationGM()
{
	selfSocket.MyDestory();
	packethead.Destroy();
	if(intGM != NULL)
	{
	    intGM = NULL;
	}
}

//设置SOCKET
void OperationGM::initSocket(SOCKET m_Socket)
{
	selfSocket.SetSocket(m_Socket);
}

// 读取ini文件里面的值
CString OperationGM::ReadValue(CString strSection,CString strKey)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MGM.ini");//获取配置文件的地址
	if(GetPrivateProfileString(strSection,strKey,"",strValue,2048,filepath)!=-1)//获得想要读取的值，以CString的形式输出
	{
		return (LPSTR)&strValue;
	}
	return "";
}

// 读取ini文件里面的数字
int OperationGM::ReadIntValue(CString strSection,CString strKey)
{
	char path[256];
	GetCurrentDirectory(256,path);
	char filepath[256];
	wsprintf(filepath,"%s%s",path,"\\Config\\MGM.ini");
	int result = GetPrivateProfileInt(strSection,strKey,0,filepath);
	return result;
}

//通过行号和列名得到相应的值
CString OperationGM::GetValueByColName(CListCtrl* listCtrlS, int nIndex, CString ColName)
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

// 发送Query
bool OperationGM::SendQuery(unsigned char* sendData,int allLength,CEnumCore::Msg_Category m_category,CEnumCore::ServiceKey m_ServiceKey)
{
	try
	{
		packethead.Create(allLength);
		packethead.AddHeader(1,m_category,m_ServiceKey,allLength);//给数据包添加头信息
		
		packethead.EnSendBuf(&allLength,sendData,packethead.m_packethead.bodylen);//构造并加密最后要发送的数据包
		packetLength = allLength;
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),allLength))//发送数据
		{
			MessageBox(NULL,ReadValue("MGM","GM_ERROR_SENDDATAERROR"),ReadValue("MGM","ERROR"),MB_OK);
			return false;
		}
		*intGM = 1;
	}
	catch(...)
	{
	}
	return true;
}

//再次发送同样的Query
bool OperationGM::SendSameQuery()
{
	try
	{
		if(!selfSocket.SendData((char*)packethead.getSendBuf(),packetLength))//发送数据
		{
			MessageBox(NULL,ReadValue("MGM","GM_ERROR_SENDDATAERROR"),ReadValue("MGM","ERROR"),MB_OK);
			return false;
		}
	}
	catch(...)
	{
	}
	return true;
}

// 构造复选框
bool OperationGM::BuildCombox(CSocketData* psocketData,CComboBox* cmbSelect)
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
			m_tSvrCity = psocketData->getTLV(i,2);//获取要添加的数据内容
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

// 构造复选框
bool OperationGM::BuildComboxs(CSocketData* psocketData,CComboBox* cmbSelect,int bItem,CEnumCore::TagName m_TegName)
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

		for(int i=bItem;i<=psocketData->getQueryNum();i++)
		{
			m_tSvrCity = psocketData->getTLVByName(i,m_TegName);//获取要添加的数据内容
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

// 构造用户列表
bool OperationGM::BuildComboxUser(CSocketData* psocketData,CComboBox* cmbSelect)
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
			m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::RealName);//获取要添加的数据内容
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

//构造游戏列表
bool OperationGM::BuildComboxGame(CSocketData* psocketData,CComboBox* cmbSelect)
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

		cmbSelect->AddString(ReadValue("MGM","OL_UI_AllGame"));
		for(int i=1;i<=psocketData->getQueryNum();i++)
		{
			m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::GameName);//获取要添加的数据内容
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

//构造大区列表
bool OperationGM::BuildComboxCity(CSocketData* psocketData,CComboBox* cmbSelect)
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

		cmbSelect->AddString(ReadValue("MGM","OL_UI_AllCity"));
		for(int i=1;i<=psocketData->getQueryNum();i++)
		{
			m_tSvrCity = psocketData->getTLVByName(i,CEnumCore::TagName::ServerInfo_City);//获取要添加的数据内容
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

// 构造CListCtrl
bool OperationGM::BuildDataTable(CSocketData* psocketData,CListCtrl* listCtrlS,int* pageCount)
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

		while(listCtrlS->DeleteColumn(0)){}	//清空CListCtrl的内容

		CGlobalStruct::TFLV m_BGS,m_ConGS;
		m_BGS = psocketData->getTLV(1,1);//获取第一个要添加的数据内容
		if(m_BGS.m_tagName == CEnumCore::TagName::MESSAGE) //如果第一个要添加的数据内容是失败信息的话
		{
			MessageBox(NULL,(LPCTSTR)&m_BGS.lpdata,"Error",MB_ICONWARNING+MB_OK);//显示失败信息并返回
			return false;
		}

		for(int i=1;i<=psocketData->getColTFLVNum();i++)//添加得到的数据包中所有的TagName
		{
			m_BGS = psocketData->getTLV(1,i);
			if(m_BGS.m_tagName != CEnumCore::TagName::PageCount)//页数信息不能添加到CListCtrl中
			{
				ReadValue("MGM",tagToStr(m_BGS.m_tagName));//获取TagName的对应字符名称
				listCtrlS->InsertColumn( i, this->strValue, LVCFMT_LEFT, 80 );//将TagName的字符名称插入到CListCtrl中，做为列名
			}
		}
		m_BGS = psocketData->getTLV(1,psocketData->getColTFLVNum());
		*pageCount = atoi((char *)&m_BGS.lpdata);//获取页数信息

		listCtrlS->DeleteAllItems();//清除CListCtrl所有项的内容
		int nRow=0;
		for(int j=1;j<=psocketData->getQueryNum();j++)
		{
			for(int k=1;k<=psocketData->getColTFLVNum();k++)
			{
				m_ConGS = psocketData->getTLV(j,k);
				if(k==1)
				{
					nRow=listCtrlS->InsertItem(j-1,(LPCTSTR)&m_ConGS.lpdata);//逐行逐列的将所获得的信息插入到CListCtrl中
				}
				else
				{
					if(m_ConGS.m_tagName == CEnumCore::TagName::PageCount)
					{
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::OnlineActive)//在线状态需要用文字显示
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//在线状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGM","UM_Code_Online"));//显示为在线
						}
						else//在线状态不为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGM","UM_Code_NotOnline"));//显示为不在线
						}
					}
					else if(m_ConGS.m_tagName == CEnumCore::TagName::SysAdmin)//是否系统管理员需要用文字显示
					{
						if(!strcmp("1", (LPTSTR)&m_ConGS.lpdata))//系统管理员状态为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGM","UM_Code_SysAdmin"));//显示为系统管理员
						}
						else//系统管理员状态不为1的话
						{
							listCtrlS->SetItemText(nRow,k-1,ReadValue("MGM","UM_Code_DepartAdmin"));//显示为部门管理员
						}
					}
					else
					{
						listCtrlS->SetItemText(nRow,k-1,(LPCTSTR)&m_ConGS.lpdata);//逐行逐列的将所获得的信息插入到CListCtrl中
					}
				}
			}
		}
	}
	catch (...)
	{
		MessageBox(NULL,ReadValue("MGM","UM_Error_BuildList"),ReadValue("MGM","Error"),0);
	}
	return false;
}

// TagName转换成CString类型
char* OperationGM::tagToStr(CEnumCore::TagName tag)
{
	ZeroMemory( strValue, DF_DEFAULT_LENGTH );
	switch(tag)
	{
	case CEnumCore::TagName::UserName: //Format:STRING 用户名
		sprintf(strValue,"%s","UserName");
		break;
	case CEnumCore::TagName::PassWord: //Format:STRING 密码
		sprintf(strValue,"%s","PassWord");
		break;
	case CEnumCore::TagName::MAC: //Format:STRING  MAC码
		sprintf(strValue,"%s","MAC");
		break;
	case CEnumCore::TagName::Limit://Format:DateTime GM帐号使用时效
		sprintf(strValue,"%s","Limit");
		break;
	case CEnumCore::TagName::User_Status://Format:INT 状态信息
		sprintf(strValue,"%s","User_Status");
		break;
	case CEnumCore::TagName::UserByID://Format:INT 操作员ID
		sprintf(strValue,"%s","UserByID");
		break;
	case CEnumCore::TagName::RealName://Format:STRING 中文名
		sprintf(strValue,"%s","RealName");
		break;
	case CEnumCore::TagName::DepartID://Format:INT 部门ID
		sprintf(strValue,"%s","DepartID");
		break;
	case CEnumCore::TagName::DepartName://Format:STRING 部门名称
		sprintf(strValue,"%s","DepartName");
		break;
	case CEnumCore::TagName::DepartRemark://Format:STRING 部门描述
		sprintf(strValue,"%s","DepartRemark");
		break;
	case CEnumCore::TagName::OnlineActive://Format:Integer 在线状态
		sprintf(strValue,"%s","OnlineActive");
		break;
	case CEnumCore::TagName::UpdateFileName://Format:String 文件名
		sprintf(strValue,"%s","UpdateFileName");
		break;
	case CEnumCore::TagName::UpdateFileVersion://Format:String 文件版本
		sprintf(strValue,"%s","UpdateFileVersion");
		break;
	case CEnumCore::TagName::UpdateFilePath://Format:String 文件路径
		sprintf(strValue,"%s","UpdateFilePath");
		break;
	case CEnumCore::TagName::UpdateFileSize://Format:Integer 文件大小
		sprintf(strValue,"%s","UpdateFileSize");
		break;
	case CEnumCore::TagName::Process_Reason://Format tring
		sprintf(strValue,"%s","Process_Reason");
		break;
	case CEnumCore::TagName::userIP://Format::STRING IP地址(新加)
		sprintf(strValue,"%s","userIP");
		break;
	case CEnumCore::TagName::DepartStrGameID://Format:STRING部门游戏ID总和(新加)
		sprintf(strValue,"%s","DepartStrGameID");
		break;
	case CEnumCore::TagName::DugID:////Format:STRINGBBugID(新加)
		sprintf(strValue,"%s","DugID");
		break;
	case CEnumCore::TagName::DugSubject:////Format:STRINGBBug主题(新加)
		sprintf(strValue,"%s","DugSubject");
		break;
	case CEnumCore::TagName::DugType:////Format:INTBug类型(新加)
		sprintf(strValue,"%s","DugType");
		break;
	case CEnumCore::TagName::DugContent:////Format:STRINGBug内容(新加)
		sprintf(strValue,"%s","DugContent");
		break;
	case CEnumCore::TagName::DugResult:////Format:STRINGBug结果(新加)
		sprintf(strValue,"%s","DugResult");
		break;
	case CEnumCore::TagName::ServerInfo_IP://Format:String 服务器IP
		sprintf(strValue,"%s","ServerInfo_IP");
		break;
	case CEnumCore::TagName::ServerInfo_City://Format:String 城市
		sprintf(strValue,"%s","ServerInfo_City");
		break;
	case CEnumCore::TagName::ServerInfo_GameID://Format:Integer 游戏ID
		sprintf(strValue,"%s","ServerInfo_GameID");
		break;
	case CEnumCore::TagName::ServerInfo_GameName://Format:String 游戏名
		sprintf(strValue,"%s","ServerInfo_GameName");
		break;
	case CEnumCore::TagName::ServerInfo_GameDBID://Format:Integer 游戏数据库类型
		sprintf(strValue,"%s","ServerInfo_GameDBID");
		break;
	case CEnumCore::TagName::ServerInfo_GameFlag://Format:Integer 游戏服务器状态
		sprintf(strValue,"%s","ServerInfo_GameFlag");
		break;
	case CEnumCore::TagName::ServerInfo_Idx:
		sprintf(strValue,"%s","ServerInfo_Idx");
		break;
	case CEnumCore::TagName::ServerInfo_DBName:
		sprintf(strValue,"%s","ServerInfo_DBName");
		break;

	case CEnumCore::TagName::ServerInfo_UserName:////Format:STRING服务器用户名(新加)
		sprintf(strValue,"%s","ServerInfo_UserName");
		break;
	case CEnumCore::TagName::ServerInfo_PassWord:////Format:STRINGB服务器密码(新加)
		sprintf(strValue,"%s","ServerInfo_PassWord");
		break;

	case CEnumCore::TagName::GameID: //Format:INTEGER 消息ID
		sprintf(strValue,"%s","GameID");
		break;
	case CEnumCore::TagName::ModuleName: //Format:STRING 模块名称
		sprintf(strValue,"%s","ModuleName");
		break;
	case CEnumCore::TagName::ModuleClass://Format:STRING 模块分类
		sprintf(strValue,"%s","ModuleClass");
		break;
	case CEnumCore::TagName::ModuleContent: //Format:STRING 模块描述
		sprintf(strValue,"%s","ModuleContent");
		break;

	case CEnumCore::TagName::Module_ID: //Format:INTEGER 模块ID
		sprintf(strValue,"%s","Module_ID");
		break;
	case CEnumCore::TagName::User_ID: //Format:INTEGER 用户ID
		sprintf(strValue,"%s","User_ID");
		break;
	case CEnumCore::TagName::ModuleList: //Format:String 模块列表
		sprintf(strValue,"%s","ModuleList");
		break;
	case CEnumCore::TagName::SysAdmin://Format:Integer 是否是系统管理员
		sprintf(strValue,"%s","SysAdmin");
		break;
	case CEnumCore::TagName::Host_Addr: //Format:STRING
		sprintf(strValue,"%s","Host_Addr");
		break;
	case CEnumCore::TagName::Host_Port: //Format:STRING
		sprintf(strValue,"%s","Host_Port");
		break;
	case CEnumCore::TagName::Host_Pat:  //Format:STRING
		sprintf(strValue,"%s","Host_Pat");
		break;
	case CEnumCore::TagName::Conn_Time: //Format:DateTime 请求和响应时间
		sprintf(strValue,"%s","Conn_Time");
		break;
	case CEnumCore::TagName::Connect_Msg://Format:STRING 请求连接信息
		sprintf(strValue,"%s","Connect_Msg");
		break;
	case CEnumCore::TagName::DisConnect_Msg://Format:STRING	 请求端开信息
		sprintf(strValue,"%s","DisConnect_Msg");
		break;
	case CEnumCore::TagName::Author_Msg: //Format:STRING 验证用户的信息
		sprintf(strValue,"%s","Author_Msg");
		break;
	case CEnumCore::TagName::Status://Format:STRING 操作结果
		sprintf(strValue,"%s","Status");
		break;
	case CEnumCore::TagName::Index: //Format:Integer 记录集序号
		sprintf(strValue,"%s","Index");
		break;
	case CEnumCore::TagName::PageSize://Format:Integer 记录页显示长度
		sprintf(strValue,"%s","PageSize");
		break;
	case CEnumCore::TagName::PageCount://Format:Integer 显示总页数
		sprintf(strValue,"%s","PageCount");
		break;
	case CEnumCore::TagName::SP_Name://Format:Integer 存储过程名
		sprintf(strValue,"%s","SP_Name");
		break;
	case CEnumCore::TagName::Real_ACT://Format:String 操作的内容
		sprintf(strValue,"%s","Real_ACT");
		break;
	case CEnumCore::TagName::ACT_Time://Format:TimeStamp 操作时间
		sprintf(strValue,"%s","ACT_Time");
		break;
	case CEnumCore::TagName::BeginTime://Format:Date 开始日期
		sprintf(strValue,"%s","BeginTime");
		break;
	case CEnumCore::TagName::EndTime://Format:Date 结束日期
		sprintf(strValue,"%s","EndTime");
		break;
	case CEnumCore::TagName::GameName: //Format:STRING 游戏名称
		sprintf(strValue,"%s","GameName");
		break;
	case CEnumCore::TagName::GameContent: //Format:STRING 消息描述
		sprintf(strValue,"%s","GameContent");
		break;
	case CEnumCore::TagName::Letter_ID://Format:Integer 
		sprintf(strValue,"%s","Letter_ID");
		break;
	case CEnumCore::TagName::Letter_Sender: //Format:String
		sprintf(strValue,"%s","Letter_Sender");
		break;
	case CEnumCore::TagName::Letter_Receiver: //Format:String
		sprintf(strValue,"%s","Letter_Receiver");
		break;
	case CEnumCore::TagName::Letter_Subject: //Format:String
		sprintf(strValue,"%s","Letter_Subject");
		break;
	case CEnumCore::TagName::Letter_Text: //Format:String
		sprintf(strValue,"%s","Letter_Text");
		break;
	case CEnumCore::TagName::Send_Date: //Format:Date
		sprintf(strValue,"%s","Send_Date");
		break;
	case CEnumCore::TagName::Process_Man: //Format:Integer
		sprintf(strValue,"%s","Process_Man");
		break;
	case CEnumCore::TagName::Process_Date: //Format:Date
		sprintf(strValue,"%s","Process_Date");
		break;
	case CEnumCore::TagName::Transmit_Man: //Format:Integer
		sprintf(strValue,"%s","Transmit_Man");
		break;
	case CEnumCore::TagName::Is_Process: //Format:Integer
		sprintf(strValue,"%s","Is_Process");
		break;
	case CEnumCore::TagName::LINKER_NAME:
		sprintf(strValue,"%s","LINKER_NAME");
		break;
	case CEnumCore::TagName::LINKER_CONTENT:
		sprintf(strValue,"%s","LINKER_CONTENT");
		break;
	case CEnumCore::TagName::ToolProcTypeID:
		sprintf(strValue,"%s","ToolProcTypeID");
		break;
	case CEnumCore::TagName::PlayerAccount:
		sprintf(strValue,"%s","PlayerAccount");
		break;
	case CEnumCore::TagName::PlayerName:
		sprintf(strValue,"%s","PlayerName");
		break;
	case CEnumCore::TagName::ToolProcPath:
		sprintf(strValue,"%s","ToolProcPath");
		break;
	case CEnumCore::TagName::KickProcTime:
		sprintf(strValue,"%s","KickProcTime");
		break;
	case CEnumCore::TagName::PlayerInServer:
		sprintf(strValue,"%s","PlayerInServer");
		break;
	case CEnumCore::TagName::RealmIP:
		sprintf(strValue,"%s","RealmIP");
		break;
	default:
		sprintf(strValue,"%s","UnKnown");
		break;
	}	
	return strValue;
}

// 显示操作结果
void OperationGM::ShowResult(CString result)
{
	if (result == "SCUESS")
	{
		MessageBox(NULL,ReadValue("MGM","Success"),ReadValue("MGM","Result"),0);
	}
	else if (result == "FAILURE")
	{
		MessageBox(NULL,ReadValue("MGM","Failure"),ReadValue("MGM","Result"),0);
	}
	else
	{
		MessageBox(NULL,result,ReadValue("MGM","Result"),0);
	}
}

//自己定义的复制函数
void OperationGM::CopyListInfo(CListCtrl* m_listCtrl)
{
	try
	{
		POSITION pos = m_listCtrl->GetFirstSelectedItemPosition();  
		if (pos != NULL)
		{			
			char strCopy[40960];
			ZeroMemory(strCopy, 40960);

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
			clipBuff=::GlobalAlloc(GMEM_DDESHARE,40960);   
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
			clipBuff=::GlobalAlloc(GMEM_DDESHARE,40960);   
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
void OperationGM::SortListInfo(CListCtrl* m_listCtrl,NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

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

//导出CListCtrl中的数据到xls文件
bool OperationGM::ExportCListCtrlToExcel(CListCtrl* pList, CString sExcelFile, CString sSheetName)
{
	if (pList->GetItemCount() < 1) 
	{
		MessageBox(NULL, "无可用数据", NULL, MB_OK|MB_TOPMOST);
		return FALSE;
	}

	//检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"
	CString sDriver;
	sDriver = GetExcelDriver("Excel");
	if (sDriver.IsEmpty())
	{
		MessageBox(NULL, "您没有安装EXCEL!\n请先安装EXCEL再使用本功能.", NULL, MB_OK|MB_TOPMOST);
		return FALSE;
	}

	//创建进行存取的字符串
	CString sSql;

	sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

	//创建表结构(即xls文件)
	CDatabase database;
	if(database.OpenEx(sSql, CDatabase::noOdbcDialog))
	{
		LVCOLUMN columnData;
		CString columnName;
		CString strH;
		CString strV;
		
		columnData.mask = LVCF_TEXT;
		columnData.pszText = columnName.GetBuffer(128);
		columnData.cchTextMax = 128;

		sSql = "";
		strH = "";
		int i, columnNum = 0;
		for (i = 0; pList->GetColumn(i, &columnData); i++)
		{
			if(i != 0)
			{
				sSql = sSql + ",";
				strH = strH + ",";
			}
			sSql = sSql + columnData.pszText + " TEXT";
			strH = strH + columnData.pszText + " ";
		}
		columnName.ReleaseBuffer();
		columnNum = i;
		
		sSql = "CREATE TABLE " + sSheetName + " (" + sSql + " )";
		database.ExecuteSQL(sSql);

		//插入数据项
		int nItemIndex;
		for (nItemIndex = 0; nItemIndex < pList->GetItemCount(); nItemIndex++)
		{
			strV = "";
			for (i = 0; i < columnNum; i++)
			{
				if (i != 0)
					strV = strV + ",";
				strV = strV + "'" + pList->GetItemText(nItemIndex, i) + "'";
			}
			//sSql = "DELETE * FROM [" + sSheetName + "$]";
			//database.ExecuteSQL(sSql);
			

			//sSql = "INSERT INTO [" + sSheetName + "$] (" + strH + ")" + " VALUES(" + strV + ")";
			sSql = "INSERT INTO " + sSheetName + " (" + strH + ")" + " VALUES(" + strV + ")";
			database.ExecuteSQL(sSql);
		}

		database.Close();
		CString strTip;
		strTip.Format("导出文件保存于: %s", sExcelFile);
		MessageBox(NULL, strTip, NULL, MB_OK | MB_TOPMOST);
		return TRUE;
	}
	return FALSE;
}

//获取驱动
CString OperationGM::GetExcelDriver(char* driverName)
{
	CString sDriver = "";

	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;

	//获取已经安装的驱动名称
	if(!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
		return "";

	char* pszBuf = szBuf;
	do 
	{
		if (strstr(pszBuf, driverName) != NULL)
		{
			//发现excel驱动
			sDriver = CString(pszBuf);
			break;
		}
		pszBuf = strchr(pszBuf,'\0') + 1;

	} while (pszBuf[1] !='\0'); 

	return sDriver;
}




//将Excel文件导入CListCtrl
bool OperationGM::ImportCListCtrlFromExcel(CListCtrl* pList, CString sExcelFile, CString sSheetName)
{

	CString sDriver;
	sDriver = GetExcelDriver("Excel");
	if (sDriver.IsEmpty())
	{
		MessageBox(NULL, "您没有安装EXCEL!\n请先安装EXCEL再使用本功能.", NULL, MB_OK|MB_TOPMOST);
		return FALSE;
	}

	//创建进行存取的字符串
	CString sSql;
	sSql.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sExcelFile);
	
	CDatabase database;
	if(database.Open(NULL, FALSE, FALSE, sSql))
	{
		CRecordset record(&database);
		
		sSql.ReleaseBuffer();
		sSql = "SELECT * FROM [" + sSheetName + "$]";      //
		record.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
		
		CODBCFieldInfo fieldinfo;
		int i;
		int fieldCount =  record.GetODBCFieldCount();
		
		int col = pList->GetHeaderCtrl()->GetItemCount();
		for (i=0; i < col ; i++)
			pList->DeleteColumn(0);


		for(i = 0; i <fieldCount; i++)
		{
			record.GetODBCFieldInfo(i, fieldinfo);
			pList->InsertColumn(i, fieldinfo.m_strName, LVCFMT_LEFT, 160);
		}

		CString sItem;
		int rowNum = 0;
		while ( !record.IsEOF() )
		{
			pList->InsertItem(rowNum,"");
			for(i = 0; i < fieldCount; i++)
			{
				record.GetFieldValue(i, sItem);	
				
				pList->SetItemText(rowNum,i,sItem);
			}
			record.MoveNext();	
			rowNum++;
		}
		record.Close();
		database.Close();
	}
}

bool OperationGM::ShowVIP(CSocketData *socketdata, CListCtrl* pList)
{
	//MessageBox(NULL, "接收到服务器端消息", MB_OK | MB_TOPMOST);
	CGlobalStruct::TFLV m_BGS;
	m_BGS = socketdata->getTLV(1,1);//获取第一个要添加的数据内容

	pList->InsertItem(0, (LPCTSTR)m_BGS.lpdata);
	


	return true;
}

void OperationGM::ConsoleLog(CString msg)
{
	if(AllocConsole())
	{
		freopen("CONOUT$","w+t", stdout);
		cout<<(LPCTSTR)msg<<endl;
		fclose(stdout);
		FreeConsole();
	}
}