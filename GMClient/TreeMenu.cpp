// TreeMenu.cpp : 实现文件
//

#include "stdafx.h"
#include "GMClient.h"
#include "TreeMenu.h"
#include ".\treemenu.h"
#include "MainFrm.h"


// CTreeMenu

IMPLEMENT_DYNCREATE(CTreeMenu, CFormView)

CTreeMenu::CTreeMenu()
	: CFormView(CTreeMenu::IDD)
{
}

CTreeMenu::~CTreeMenu()
{
}

void CTreeMenu::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREEMENU, tMenuList);
}

BEGIN_MESSAGE_MAP(CTreeMenu, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_TREEMENU, OnNMDblclkTreemenu)
	ON_MESSAGE(UM_RESVIEW,OnRecView)
	ON_NOTIFY(NM_RCLICK, IDC_TREEMENU, OnNMRclickTreemenu)
	ON_COMMAND(ID__REFRESH, OnRefresh)
END_MESSAGE_MAP()


// CTreeMenu 诊断

#ifdef _DEBUG
void CTreeMenu::AssertValid() const
{
	CFormView::AssertValid();
}

void CTreeMenu::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CTreeMenu 消息处理程序
void CTreeMenu::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CIni mIni;
	SetDlgItemText(ID__REFRESH,mIni.ReadValue("Global","Refresh"));

	DWORD dwStyle = GetWindowLong(tMenuList.m_hWnd,GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;

    SetWindowLong(tMenuList.m_hWnd,GWL_STYLE,dwStyle);

	CRect rs;
	GetClientRect(rs);
	tMenuList.MoveWindow(rs);//设置好m_ResTree的位置
}

//创建Form
int CTreeMenu::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

//自动改变大小
void CTreeMenu::OnSize(UINT nType, int cx, int cy)
{
	CRect rs;
	GetClientRect(rs);
	if(tMenuList.m_hWnd!=NULL)
	{
		tMenuList.MoveWindow(rs);//设置好m_ResTree的位置
	}
	CFormView::OnSize(nType, cx, cy);
}

//接收消息
LRESULT CTreeMenu::OnRecView(WPARAM wParam, LPARAM lParam)
{
	int num=0;

	unsigned char* lpReceive=(unsigned char*)wParam;
	int bodyLength = (int)lParam;

	CIni mIni;
	CPacketHead packethead;		
	packethead.Create(bodyLength);
	try
	{
		bool b_result=packethead.DeHead(lpReceive,bodyLength);
		if(b_result)
		{
			theApp.m_SendCount = 0;//重复发送次数为0
			switch((unsigned int)packethead.GetMessageID())
			{	
			case CEnumCore::Message_Tag_ID::USER_MODULE_QUERY_RESP://如果返回的是模块信息
				{
					tMenuList.DeleteAllItems();

					CSocketData socketdata;
					socketdata.Create(packethead.m_packethead.bodylen/8);
					socketdata.DeBody(packethead.getDataBuf()+18,packethead.m_packethead.bodylen);

					CGlobalStruct::TFLV m_tflv,m_tflv1,tmpm_tflv;

					m_tflv=socketdata.getTLV(1,1);//获取第一个TFLV
					if(m_tflv.m_tagName == CEnumCore::TagName::MESSAGE)
					{
						socketdata.Destroy();
						return false;
					}

					m_tflv=socketdata.getTLVByTag(CEnumCore::TagName::GameName,0);//获取第一个游戏名称
					m_root[num]=tMenuList.InsertItem((LPCSTR)&m_tflv.lpdata);//将第一个游戏名称插入到树的根部
					tmpm_tflv=m_tflv;
					m_tflv1=socketdata.getTLVByTag(CEnumCore::TagName::ModuleClass,tmpm_tflv.nIndex);//获取第一个模块名称
					//m_tflv1=socketdata.getTLVByName(1, CEnumCore::TagName::ModuleClass);


					tMenuList.InsertItem(mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata),m_root[num]);//将第一个模块名称插入到第一个游戏名称的下面
					while(tmpm_tflv.nIndex!=0)
					{
						tmpm_tflv=socketdata.getTLVByTag( CEnumCore::TagName::GameName,tmpm_tflv.nIndex+1);//获取下一个游戏名称
						if(!strcmp((char *)&tmpm_tflv.lpdata,(char *)&m_tflv.lpdata))//如果前后两个游戏名称相同
						{
							m_tflv1=socketdata.getTLVByTag(CEnumCore::TagName::ModuleClass,tmpm_tflv.nIndex);//获取下一个模块名称
							tMenuList.InsertItem(mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata),m_root[num]);//将下一个模块名称直接插入到游戏名称的下面
						}
						else//如果前后两个游戏名称不同
						{
							num++;
							m_tflv=tmpm_tflv;//赋值为新的游戏名称
							if(m_tflv.nIndex!=0)
							{
								m_root[num]=tMenuList.InsertItem((LPCSTR)&m_tflv.lpdata);//将新的游戏名称插入到树的根部
							}
							m_tflv1=socketdata.getTLVByTag(CEnumCore::TagName::ModuleClass,tmpm_tflv.nIndex);//获取下一个模块名称
							if(m_tflv.nIndex!=0)
							{
								tMenuList.InsertItem(mIni.ReadValue("Global",(LPCSTR)m_tflv1.lpdata),m_root[num]);//将模块名称插入到游戏名称的下面
							}
						}
					}
					socketdata.Destroy();
				}
			}
		}	
		else
		{
			if(theApp.m_SendCount<5)//如果重复发送次数小于5次
			{
				OnRefresh();//发送原来的请求
				theApp.m_SendCount++;//重复发送次数加1
			}
			else
			{
				::EnableWindow(this->m_hWnd,true);//接收到返回信息之后，让整个界面都变成Enable的状态，此时可以发新的请求
				::SetWindowPos(this->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
				MessageBox(mIni.ReadValue("GLOBAL","Main_UI_ParseData"),mIni.ReadValue("GLOBAL","ERROR"),MB_OK);//数据解析异常
				return false;
			}
		}
	}
	catch(...)
	{
	}	
	return true;
}

//双击CTreeCtrl
void CTreeMenu::OnNMDblclkTreemenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM m_hTreeItem = tMenuList.GetSelectedItem();//获取选中的树节点
	HTREEITEM m_hParentTreeItem=tMenuList.GetParentItem(m_hTreeItem);//获取选中的树节点的父结点
	if(m_hTreeItem!=NULL&&m_hParentTreeItem!=NULL)
	{
		CIni mIni;
		char m_treemessage[150],m_parenttreemessage[150];
		sprintf(m_treemessage,"%s",mIni.wcharToChar(tMenuList.GetItemText(m_hTreeItem)));
		sprintf(m_parenttreemessage,"%s",mIni.wcharToChar(tMenuList.GetItemText(m_hParentTreeItem)));
	
		CMainFrame* pMainFrame=(CMainFrame*)this->GetParent()->GetParent();//获取主界面的指针
		::SendMessage(pMainFrame->wndSplitDlg.GetPane(0,0)->m_hWnd,UM_RESVIEW,(WPARAM)(m_treemessage),(LPARAM)m_parenttreemessage);//将接收到的模块信息传递给CDlgSelect类
	}
	

	*pResult = 0;
}

//右键点击CTreeCtrl弹出菜单
void CTreeMenu::OnNMRclickTreemenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
    {
        DWORD dwPos = GetMessagePos();//获取当前点击的位置
        CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

        CMenu menu;
		VERIFY( menu.LoadMenu(IDR_TMENU));//加载刷新菜单
        CMenu* popup = menu.GetSubMenu(0);//获取子菜单
        ASSERT( popup != NULL );
        popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
		popup->DestroyMenu();
		popup=NULL;
		menu.DestroyMenu();
    } 
	catch(...)
	{
	}
    *pResult = 0;
}

//点击刷新菜单时进行的操作
void CTreeMenu::OnRefresh()
{
	try
	{
		theApp.menuflag = false;

		CSocketData socketdata;
		socketdata.InitCreate(1,1);	//只有一个参数，操作员ID
		char strInt[10];

		_itoa(theApp.UserByID,strInt,10);
		socketdata.AddTFLV(CEnumCore::TagName::User_ID,CEnumCore::TagFormat::TLV_INTEGER,sizeof(int),(unsigned char *)&strInt);//操作员ID

		int alllength=socketdata.EnBody();

		CPacketHead packethead;		
		packethead.Create(alllength);

		packethead.AddHeader(1,CEnumCore::Msg_Category::USER_MODULE_ADMIN,CEnumCore::ServiceKey::USER_MODULE_QUERY,alllength);//发送用户模块请求

		packethead.EnSendBuf(&alllength,socketdata.getDes(),packethead.m_packethead.bodylen);
		theApp.m_clientsocket.Send(packethead.getSendBuf(),alllength);//发送刷新菜单的请求
	}
	catch(...)
	{
	}
}
