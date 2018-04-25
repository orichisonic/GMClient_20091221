// PopedomManage.cpp : 实现文件
//

#include "stdafx.h"
#include "M_GM.h"
#include "PopedomManage.h"
#include ".\popedommanage.h"


// CPopedomManage 对话框

IMPLEMENT_DYNAMIC(CPopedomManage, CDialog)
CPopedomManage::CPopedomManage(CWnd* pParent /*=NULL*/)
	: CDialog(CPopedomManage::IDD, pParent)
{
}

CPopedomManage::~CPopedomManage()
{
}

void CPopedomManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTGAME, listGame);
	DDX_Control(pDX, IDC_LISTMODULE, listModule);
}


BEGIN_MESSAGE_MAP(CPopedomManage, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(UM_RECEIVE,OnMessageReceive)
	ON_NOTIFY(NM_CLICK, IDC_LISTGAME, OnNMClickListgame)
	ON_NOTIFY(NM_CLICK, IDC_LISTMODULE, OnNMClickListmodule)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// 初始化对话框
BOOL CPopedomManage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitUI();// 初始化显示字符

	//OperationGM operGM;

	listGame.SetExtendedStyle(listGame.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);
	listGame.InsertColumn(0,theApp.operGM.ReadValue("MGM","PM_UI_GameList"),LVCFMT_CENTER,250,-1);	

	listModule.SetExtendedStyle(listModule.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);
	listModule.InsertColumn(0,theApp.operGM.ReadValue("MGM","PM_UI_ModuleList"),LVCFMT_CENTER,250,-1);	

	listGame.DeleteAllItems();
	listModule.DeleteAllItems();

	InitGameList();

	return TRUE;
}

// 初始化显示字符
void CPopedomManage::InitUI()
{
	//OperationGM operGM;

	SetWindowText(theApp.operGM.ReadValue("MGM","PM_UI_PopedomManage"));

	SetDlgItemText(IDC_LBLGAMEPOPEDOM,theApp.operGM.ReadValue("MGM","PM_UI_GamePopedom"));
	SetDlgItemText(IDOK,theApp.operGM.ReadValue("MGM","MakeSure"));
	SetDlgItemText(IDCANCEL,theApp.operGM.ReadValue("MGM","Cancel"));
}

// 初始化私有变量
void CPopedomManage::initVar(CString uName,int uID)
{
	userName = uName;
	userID = uID;
}

// 创建对话框
int CPopedomManage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;	

	return 0;
}

// 请求所有游戏列表
void CPopedomManage::InitGameList()
{
	//OperationGM operGM;
	try
	{		
		CIni mIni;

		CSocketData socketdata;		
		socketdata.InitCreate(1,2);//共有两个参数，玩家帐号和玩家ID
		char strInt[10];

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char *)mIni.wcharToChar(userName));//玩家帐号

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::GAME_ADMIN,CEnumCore::ServiceKey::GAME_MODULE_QUERY))//发送查询游戏模块信息的请求
		{
		    ::EnableWindow(this->GetParent()->GetParent()->m_hWnd,false);//发送请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}	
}

// 单击游戏列表，获取相应的模块列表
void CPopedomManage::OnNMClickListgame(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listGame.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		UINT nFlag;
		int selectItem = listGame.HitTest(point,&nFlag);//保存在用户列表中选中的行号	
		listModule.DeleteAllItems();

		CGlobalStruct::TFLV m_tflv;
		CGlobalStruct::TFLV tmp_tflv;
		if(nFlag == LVHT_ONITEMSTATEICON) 
		{			
			if(!listGame.GetCheck(selectItem))
			{
				CString gameName = listGame.GetItemText(selectItem,0);
				CString moduleName = "";
				CString gameModule="";
				int num = 0;
				for(int i=1;i <= ModuleData.getQueryNum();i++)
				{
					m_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::GameName);
					tmp_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::ModuleName);
					if(!strcmp((LPCSTR)m_tflv.lpdata,gameName))
					{
						moduleName = (LPCSTR)tmp_tflv.lpdata;
						gameModule.Format("%s-%s",gameName,moduleName);
						listModule.InsertItem(num, gameModule);//将和选中的游戏相关的所有模块信息都插入到列表中

						POSITION pos = SendData.GetStartPosition(); //获取已分配的模块中的第一个
						int nKey;
						CString pt;
						while (pos != NULL)//循环遍历CMap类的对象
						{
							SendData.GetNextAssoc(pos, nKey, pt);//获取CMap类的对象中下面一项的内容，pos为位置，nkey为键值，pt为保存的内容
							if(!strcmp(pt,gameModule))//如果该模块名称在用户模块中已经存在的话
							{
								listModule.SetCheck(num);//设置为选定状态
							}
						}
						num++;
					}
				}
			}
		} 
		else if(listGame.GetCheck(selectItem))
		{
			CString gameName = listGame.GetItemText(selectItem,0);
			CString moduleName = "";
			CString gameModule="";
			int num = 0;
			for(int i=1;i <= ModuleData.getQueryNum();i++)
			{
				m_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::GameName);
				tmp_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::ModuleName);
				if(!strcmp((LPCSTR)m_tflv.lpdata,gameName))
				{
					moduleName = (LPCSTR)tmp_tflv.lpdata;
					gameModule.Format("%s-%s",gameName,moduleName);
					listModule.InsertItem(num, gameModule);//将和选中的游戏相关的所有模块信息都插入到列表中
				

					POSITION pos = SendData.GetStartPosition(); //获取已分配的模块中的第一个
					int nKey;
					CString pt;
					while (pos != NULL)//循环遍历CMap类的对象
					{
						SendData.GetNextAssoc(pos, nKey, pt);//获取CMap类的对象中下面一项的内容，pos为位置，nkey为键值，pt为保存的内容
						if(!strcmp(pt,gameModule))//如果该模块名称在用户模块中已经存在的话
						{
							listModule.SetCheck(num);//设置为选定状态
						}
					}
					num++;
				}
			}
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}
//
//// 单击模块列表，保存相应的信息
void CPopedomManage::OnNMClickListmodule(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		listModule.ScreenToClient(&point);

		LVHITTESTINFO lvinfo;
		lvinfo.pt = point;
		lvinfo.flags = LVHT_ABOVE;

		UINT nFlag;
		int selectItem = listModule.HitTest(point,&nFlag);//保存在用户列表中选中的行号	
		CIni mIni;

		if(selectItem >= 0)
		{
			CString moduleName = "";
			CString GameName="";
	
			CGlobalStruct::TFLV m_tflv;
			CGlobalStruct::TFLV tmp_tflv;
			CGlobalStruct::TFLV game_tflv;
			CString gameModule="";
			if(nFlag == LVHT_ONITEMSTATEICON) //如果选中了复选框
			{
				if(!listModule.GetCheck(selectItem))//如果原来不是选中状态
				{
					moduleName = listModule.GetItemText(selectItem,0);
					int moduleID = 0;
					for(int i = 1;i <= ModuleData.getQueryNum();i++)
					{
						game_tflv=ModuleData.getTLVByName(i, CEnumCore::TagName::GameName);
						m_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::ModuleName);
						tmp_tflv = ModuleData.getTLVByName(i, CEnumCore::TagName::Module_ID);
						gameModule.Format("%s-%s",game_tflv.lpdata,m_tflv.lpdata);
						if(!strcmp(gameModule,moduleName))
						{
							moduleID = atoi((LPCSTR)tmp_tflv.lpdata);//获取模块ID
							SendData.SetAt(moduleID,moduleName);//将模块ID和对应的模块名称保存到CMap类的对象中
						}
					}
				}
				else//如果原来是选中状态
				{
					moduleName = listModule.GetItemText(selectItem,0);//获取模块名称
					POSITION pos = SendData.GetStartPosition();//查找CMap类的对象
					int nKey;
					CString pt;
					while (pos != NULL)
					{
						SendData.GetNextAssoc( pos, nKey, pt );
						if (pt == moduleName)//如果用户原来被分配过相应的模块
						{
							SendData.RemoveKey( nKey );//从CMap类的对象中移除相应的模块
						}
					}
				}
			} 			
		}
	}
	catch(...)
	{
	}
	*pResult = 0;
}
//
////给玩家分配游戏权限
void CPopedomManage::OnBnClickedOk()
{
	try
	{
		CIni mIni;//主要用于将CString类型的字符转换为char*类型的
		//OperationGM operGM;	//公共类，用于读取配置文件、发送Query、构造复选框和CListCtrl	

		CString moduleList;
		CString moduleID;
		POSITION pos = SendData.GetStartPosition();//查找CMap类的对象
		int nKey;
		CString pt;
		while (pos != NULL)
		{
			SendData.GetNextAssoc( pos, nKey, pt );
			moduleID.Format("%i",nKey);//将要添加的模块ID转换为CString类型
			moduleList += moduleID;
			moduleList += ",";
		}
		SendData.RemoveAll();
		
		CSocketData socketdata;
		socketdata.InitCreate(1,4); //共发送三个参数：操作者ID、用户ID、用户名、模块列表
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::UserByID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作者ID，登录时已经确定

		_itoa(userID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//要分配权限的用户ID

		socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char*)mIni.wcharToChar(userName));//要分配权限的用户名
		socketdata.AddTFLV(CEnumCore::TagName::ModuleList,CEnumCore::TagFormat::TLV_STRING,strlen(moduleList),(unsigned char*)mIni.wcharToChar(moduleList));//要分配给用户的模块ID

		int midlength = socketdata.EnBody();
		if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_UPDATE))//发送分配权限请求
		{
		    ::EnableWindow(this->GetParent()->GetParent()->m_hWnd,false);//发送一个请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
			dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
		}
		socketdata.Destroy();//销毁CSocketData局部变量
	}
	catch(...)
	{
	}
}
//
//// 接收返回信息
LRESULT CPopedomManage::OnMessageReceive(WPARAM wParam, LPARAM lParam)
{
	unsigned char* lpReceive=(unsigned char*)wParam;//接收到的数据指针
	int bodyLength = (int)lParam;//接收到的长度
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Receive");//当前的状态为接收到了返回信息
	
	CIni mIni;
	//OperationGM operGM;

	switch(theApp.m_tag_id)
	{
	case CEnumCore::Message_Tag_ID::GAME_MODULE_QUERY_RESP://如果返回的是对请求游戏模块列表的响应
		{
			ModuleData.Create(bodyLength/8);
			if(!ModuleData.DeBody(lpReceive,bodyLength))
			{
				::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
				::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
				ModuleData.Destroy();
				return false;
			}

			listGame.DeleteAllItems();			
			int i=1;
			CGlobalStruct::TFLV m_tflv;
			CGlobalStruct::TFLV tmp_tflv;
			m_tflv = ModuleData.getTLVByName(i,CEnumCore::TagName::GameName);//获取第一个返回的游戏名称
			if(m_tflv.nIndex != 0)//如果该游戏名称存在的话
			{
				listGame.InsertItem(i,(LPCTSTR)ModuleData.getTLVByTag(CEnumCore::TagName::GameName,0).lpdata);//添加到CListCtrl的对象中
			}
			for(i = 2;i <= ModuleData.getQueryNum();i++)//循环将所有的游戏名称插入到CListCtrl的对象中
			{
				tmp_tflv = ModuleData.getTLVByName(i,CEnumCore::TagName::GameName);
				if(strcmp((LPCSTR)tmp_tflv.lpdata,(LPCSTR)m_tflv.lpdata))
				{
					listGame.InsertItem(i,(LPCSTR)tmp_tflv.lpdata);
				}
				m_tflv=ModuleData.getTLVByName(i,CEnumCore::TagName::GameName);
			}

			CSocketData socketdata;		
			socketdata.InitCreate(1,2);//共有两个参数，玩家帐号和玩家ID
			char strInt[10];

			socketdata.AddTFLV(CEnumCore::TagName::UserName,CEnumCore::TagFormat::TLV_STRING,strlen(userName),(unsigned char *)mIni.wcharToChar(userName));//玩家帐号

			_itoa(userID,strInt,10);
			socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//玩家ID

			int midlength = socketdata.EnBody();
			if(theApp.operGM.SendQuery((unsigned char *)socketdata.getDes(),midlength,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_QUERY))//发送查询用户模块信息的请求
			{
			    ::EnableWindow(this->GetParent()->GetParent()->m_hWnd,false);//发送请求时，让整个界面都变成Disable的状态，避免客户端同时发出多个请求
				dlgStatus = theApp.operGM.ReadIntValue("MGM","Send");//当前的状态为发送查询请求
			}
			socketdata.Destroy();//销毁CSocketData局部变量
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_MODULE_QUERY_RESP://如果返回的是对请求用户模块列表的响应
		{
			UserModule.Create(bodyLength/8);
			if(!UserModule.DeBody(lpReceive,bodyLength))
			{
				::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
				::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
				UserModule.Destroy();
				return false;
			}

			CGlobalStruct::TFLV m_tflv;
			CGlobalStruct::TFLV tmp_tflv;
			CGlobalStruct::TFLV gameName_tflv;
			char gameModule[256];
			m_tflv = UserModule.getTLVByName(1,CEnumCore::TagName::GameName);//获取第一个返回的游戏名称
			if(m_tflv.nIndex != 0)//如果该游戏名称存在的话
			{
				for(int i=0;i<listGame.GetItemCount();i++)
				{
					if(!strcmp((LPCSTR)m_tflv.lpdata,listGame.GetItemText(i,0)))
					{
						listGame.SetCheck(i);
					}				
				}
			}
			else
			{
				break;
			}
			for(int j = 2;j <= UserModule.getQueryNum();j++)//循环将所有的游戏名称插入到CListCtrl的对象中
			{
				tmp_tflv = UserModule.getTLVByName(j,CEnumCore::TagName::GameName);
				if(strcmp((LPCSTR)tmp_tflv.lpdata,(LPCSTR)m_tflv.lpdata))
				{
					m_tflv=UserModule.getTLVByName(j,CEnumCore::TagName::GameName);
					for(int k=0;k<listGame.GetItemCount();k++)
					{
						if(!strcmp((LPCSTR)m_tflv.lpdata,listGame.GetItemText(k,0)))
						{
							listGame.SetCheck(k);
						}				
					}				
				}				
			}
			for(int index = 1;index<=UserModule.getQueryNum();index++)
			{
				gameName_tflv=UserModule.getTLVByName(index,CEnumCore::TagName::GameName);
				m_tflv=UserModule.getTLVByName(index,CEnumCore::TagName::Module_ID);
				tmp_tflv = UserModule.getTLVByName(index,CEnumCore::TagName::ModuleName);
				sprintf(gameModule,"%s-%s",gameName_tflv.lpdata,tmp_tflv.lpdata);
				SendData.SetAt(atoi((LPCSTR)m_tflv.lpdata),(LPCSTR)gameModule);//将用户当前的模块权限信息添加到CMap类的对象中
			}
		}
		break;
	case CEnumCore::Message_Tag_ID::USER_MODULE_UPDATE_RESP://如果返回的是操作类请求的响应
		{
			CSocketData socketdata;
			socketdata.Create(bodyLength/8);
			if(!socketdata.DeBody(lpReceive,bodyLength))
			{
				::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
				::SetWindowPos(this->GetParent()->m_hWnd,HWND_TOP,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),0);		
				socketdata.Destroy();
				return false;
			}

			CGlobalStruct::TFLV m_tflv=socketdata.getTLVByName(1,CEnumCore::TagName::MESSAGE);//操作类的都只返回一个MESSAGE，指示操作有没有成功
			CString result = (LPCTSTR)&m_tflv.lpdata;
			theApp.operGM.ShowResult(result);//显示操作结果
			
			::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
			::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
			socketdata.Destroy();
			ModuleData.Destroy();
	        UserModule.Destroy();
			OnCancel();
		}
		break;
	default:
		{
			MessageBox("Error","Error",0);
		}
		break;
	}
	return true;
}

//关闭对话框
void CPopedomManage::OnBnClickedCancel()
{
	dlgStatus = theApp.operGM.ReadIntValue("MGM","Close");//关闭窗体
	::EnableWindow(this->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	::EnableWindow(this->GetParent()->GetParent()->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
	if(!SendData.IsEmpty())
	{
	    SendData.RemoveAll();
	}
	ModuleData.Destroy();
	UserModule.Destroy();
	OnCancel();
}