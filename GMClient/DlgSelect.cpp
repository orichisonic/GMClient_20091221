// DlgSelect.cpp : 实现文件
//

#include "stdafx.h"
#include "GMClient.h"
#include "DlgSelect.h"
#include ".\dlgselect.h"


// CDlgSelect

IMPLEMENT_DYNCREATE(CDlgSelect, CFormView)

CDlgSelect::CDlgSelect()
	: CFormView(CDlgSelect::IDD)
{
}

CDlgSelect::~CDlgSelect()
{
}

void CDlgSelect::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABSELECT, tbcSelect);
}

BEGIN_MESSAGE_MAP(CDlgSelect, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABSELECT, OnTcnSelchangeTabselect)
	ON_WM_SIZE()
	ON_MESSAGE(UM_RESVIEW,OnRecView)
	ON_MESSAGE(UM_RECEIVE,OnShowDlg)
	ON_NOTIFY(NM_CLICK, IDC_TABSELECT, OnNMClickTabselect)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

#ifdef _DEBUG
void CDlgSelect::AssertValid() const
{
	CFormView::AssertValid();
}

void CDlgSelect::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

// CTabSelect 消息处理程序
void CDlgSelect::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_imagetab.Create(16,16,TRUE,1,1);
	m_imagetab.Add(AfxGetApp()->LoadIcon(IDI_ICONCLOSE));
	tbcSelect.SetImageList(&m_imagetab);

	CRect rs;
	GetClientRect(rs);
	if(tbcSelect.m_hWnd!=NULL)
	{
		tbcSelect.MoveWindow(rs);//设置好tbcSelect的位置
	}
}


//自动改变大小
void CDlgSelect::OnSize(UINT nType, int cx, int cy)
{
	CRect rs;
	GetClientRect(rs);
	if(tbcSelect.m_hWnd!=NULL)
	{
		tbcSelect.MoveWindow(rs);//设置好tbcSelect的位置
	}
	CFormView::OnSize(nType, cx, cy);
}

//单击选项卡进行关闭
void CDlgSelect::OnNMClickTabselect(NMHDR *pNMHDR, LRESULT *pResult)
{
	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

	tbcSelect.ScreenToClient(&point);

	TCHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = TCHT_ONITEMICON;

	int nItem = tbcSelect.HitTest(&lvinfo);
	if(nItem > -1)  
	{  
		CRect rect;  
		tbcSelect.GetItemRect( nItem, &rect);
		rect.left = rect.left + 8 ;
		rect.right = rect.left + 16;//PADDING是ICON和四边的间距...  
		if(::PtInRect(rect,point))  
		{  
			char szItemName[100];
			TC_ITEM m_PTCItem;   
			memset( &m_PTCItem, 0, sizeof( TC_ITEM ) );   
			m_PTCItem.mask = TCIF_TEXT;   
			m_PTCItem.pszText = szItemName;   
			m_PTCItem.cchTextMax = 100;   
			m_PTCItem.iImage = 0;   

			tbcSelect.GetItem(nItem, &m_PTCItem);
			CString tabName=m_PTCItem.pszText;
			CString DlgName=tabName.Right(tabName.GetLength()-tabName.Find('-')-1);
			CString GameName=tabName.Left(tabName.Find('-'));


			ShowDialog(GameName,DlgName);
			


			tbcSelect.DeleteItem(nItem);//删去对应标签页

			
			CloseDialog(GameName,DlgName);
			//nItem = tbcSelect.GetCurSel();
			nItem=0;
			tbcSelect.GetItem(nItem, &m_PTCItem);
			tabName=m_PTCItem.pszText;
			DlgName=tabName.Right(tabName.GetLength()-tabName.Find('-')-1);
			GameName=tabName.Left(tabName.Find('-'));

			ShowDialog(GameName,DlgName);

		}
	}   

	*pResult = 0;
}

//选择不同的CTabCtrl对象，切换对话框
void CDlgSelect::OnTcnSelchangeTabselect(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		int selectItem = tbcSelect.GetCurSel();//获取被选中的标签页次序

		char szItemName[100];
		TC_ITEM m_PTCItem;   
		memset( &m_PTCItem, 0, sizeof( TC_ITEM ) );   
		m_PTCItem.mask = TCIF_TEXT;   
		m_PTCItem.pszText = szItemName;   
		m_PTCItem.cchTextMax = 100;   
		m_PTCItem.iImage = -1;   

		tbcSelect.GetItem(selectItem, &m_PTCItem);
		CString tabName=m_PTCItem.pszText;
		CString DlgName=tabName.Right(tabName.GetLength()-tabName.Find('-')-1);
		CString GameName=tabName.Left(tabName.Find('-'));
		Ctabname::tabname=tabName;//把tab名称赋予tabname 彭根国  090901
		ShowDialog(GameName,DlgName);
	}
	catch(...)
	{
	}

	*pResult = 0;
}

//接收打开对话框的消息
LRESULT CDlgSelect::OnRecView(WPARAM wParam, LPARAM lParam)
{
	//theApp.XD_OpenDialog("查询玩家信息");
	char* strDlgName = (char*)wParam;//获取要打开的模块名称
	char* strGameName=(char *)lParam;
	
	CString DlgName = "";
	DlgName.Format("%s",strDlgName);//初始化要打开的模块名称


	char tabName[256];
	sprintf(tabName,"%s-%s",strGameName,strDlgName);

	TC_ITEM m_PTCItem;
	m_PTCItem.mask = TCIF_TEXT|TCIF_IMAGE;	
	m_PTCItem.pszText =(char *)&tabName;//设定游戏名称
	CIni mIni;
	if(tbcSelect.GetItemCount() == 0)//Tab Control中没有任何选项
	{	
		if(!strcmp(strDlgName, mIni.ReadValue("Global","AGABUNB"))||!strcmp(strDlgName, mIni.ReadValue("Global","AccountQuery"))||!strcmp(strDlgName, mIni.ReadValue("Global","BanQuery")))
		{
			// AGABUNB 所有游戏帐号解封和封停.
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);
			tbcSelect.SetCurSel(0);

			theApp.m_pOpenCAGABUNBDlgFun(DlgName);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","GM_Name")))
		{
			theApp.GM_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
			tbcSelect.SetCurSel(0);

		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","PAL_Name")))
		{
			theApp.PAL_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","CG2_Name")))
		{
			theApp.CG2_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","GT_Name")))
		{
			theApp.GTOWN_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","SDO_Name")))
		{
			theApp.SDO_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","JW2_Name")))
		{
			theApp.JW2_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
			tbcSelect.SetCurSel(0);
		}
		else if(!strcmp(strGameName,mIni.ReadValue("Global","WA_Name")))
		{
		
			theApp.WA_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
			tbcSelect.SetCurSel(0);
		}
		//////////////////////peng start 侠盗
		else if(!strcmp(strGameName,mIni.ReadValue("Global","XD_Name")))
		{
			theApp.XD_OpenDialog(DlgName);
			m_PTCItem.iImage = 0;
			tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
			tbcSelect.SetCurSel(0);
		}
		/////////////////////peng end

	}
	else
	{
		int nIndex = -1;
		CString curName = "";
		CString actName="";

		char szItemName[100];
		TC_ITEM s_PTCItem;   //用于保存已经被打开的标签页信息
		memset( &s_PTCItem, 0, sizeof( TC_ITEM ) );   
		s_PTCItem.mask = TCIF_TEXT;   
		s_PTCItem.pszText = szItemName;
		s_PTCItem.cchTextMax = 100;   

		int i=0;
		for(i=0;i<tbcSelect.GetItemCount();i++)
		{
			tbcSelect.GetItem(i, &s_PTCItem);
			curName = s_PTCItem.pszText;//获取每一个标签页的名称
			actName=curName.Right(curName.GetLength()-curName.Find('-')-1);
			if(!strcmp(DlgName, actName))//如果对话框已经被打开
			{
				nIndex = i;
				break;
			}
		}
		if(nIndex < 0)//没有打开过对话框
		{
			if(!strcmp(strDlgName, mIni.ReadValue("Global","AGABUNB"))||!strcmp(strDlgName, mIni.ReadValue("Global","AccountQuery"))||!strcmp(strDlgName, mIni.ReadValue("Global","BanQuery")))
			{
				// AGABUNB 所有游戏帐号解封和封停.
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);
				tbcSelect.SetCurSel(0);

				theApp.m_pOpenCAGABUNBDlgFun(DlgName);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","GM_Name")))
			{
				theApp.GM_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
				tbcSelect.SetCurSel(0);

			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","PAL_Name")))
			{
				theApp.PAL_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","CG2_Name")))
			{
				theApp.CG2_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","GT_Name")))
			{
				theApp.GTOWN_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","SDO_Name")))
			{
				theApp.SDO_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","JW2_Name")))
			{
				theApp.JW2_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
				tbcSelect.SetCurSel(0);
			}
			else if(!strcmp(strGameName,mIni.ReadValue("Global","WA_Name")))
			{
				theApp.WA_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
				tbcSelect.SetCurSel(0);
			}

			//////////////////////peng start 侠盗
			else if(!strcmp(strGameName,mIni.ReadValue("Global","XD_Name")))
			{
				theApp.XD_OpenDialog(DlgName);
				m_PTCItem.iImage = 0;
				tbcSelect.InsertItem(0,&m_PTCItem);//把需要的标签页添加进去
				tbcSelect.SetCurSel(0);
			}
			/////////////////////peng end
		}
		else//对话框已经被打开
		{
			tbcSelect.SetCurSel(nIndex);//切换到相应的标签页
			ShowDialog(strGameName,DlgName);
		}
	}

	return true;
}

//接收显示对话框的消息
LRESULT CDlgSelect::OnShowDlg(WPARAM wParam, LPARAM lParam)
{
	try
	{
		int selectItem = tbcSelect.GetCurSel();//获取被选中的标签页次序

		if(selectItem> -1)
		{
			char szItemName[100];
			TC_ITEM m_PTCItem;   
			memset( &m_PTCItem, 0, sizeof( TC_ITEM ) );   
			m_PTCItem.mask = TCIF_TEXT;   
			m_PTCItem.pszText = szItemName;   
			m_PTCItem.cchTextMax = 100;   
			m_PTCItem.iImage = -1;   

			tbcSelect.GetItem(selectItem, &m_PTCItem);
			CString DlgName = m_PTCItem.pszText;//获取被选中的标签页名称

			theApp.GM_ShowDialog(DlgName);//显示新的TOP标签页对应的对话框
			theApp.PAL_ShowDialog(DlgName);
			theApp.GTOWN_ShowDialog(DlgName);
			theApp.CG2_ShowDialog(DlgName);

			//maple add
			theApp.SDO_ShowDialog(DlgName);
			theApp.JW2_ShowDialog(DlgName);
			theApp.WA_ShowDialog(DlgName);
			theApp.m_pShowGABUNBDlgFun(DlgName);
		}
		
	}
	catch(...)
	{
	}
	return true;
}


//关闭对话框
void CDlgSelect::OnClose()
{
	if(tbcSelect.GetItemCount() != 0)
	{
		tbcSelect.DeleteAllItems();
	}
	m_imagetab.DeleteImageList();
	CFormView::OnClose();
}

void CDlgSelect::ShowDialog(CString GameName,CString DlgName)
{
	CIni mIni;
	if(!strcmp(DlgName, mIni.ReadValue("Global","AGABUNB"))||!strcmp(DlgName, mIni.ReadValue("Global","AccountQuery"))||!strcmp(DlgName, mIni.ReadValue("Global","BanQuery")))
	{
		// AGABUNB 所有游戏帐号解封和封停.
		theApp.m_pShowGABUNBDlgFun(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","GM_Name")))
	{
		theApp.GM_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","PAL_Name")))
	{
		theApp.PAL_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","CG2_Name")))
	{
		theApp.CG2_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","GT_Name")))
	{
		theApp.GTOWN_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","SDO_Name")))
	{
		theApp.SDO_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","JW2_Name")))
	{
		theApp.JW2_ShowDialog(DlgName);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","WA_Name")))
	{
		theApp.WA_ShowDialog(DlgName);
	}
	///////peng begin
	else if(!strcmp(GameName,mIni.ReadValue("Global","XD_Name")))
	{
		theApp.XD_ShowDialog(DlgName);
	}
	//////peng end
}
void CDlgSelect::CloseDialog(CString GameName,CString DlgName)
{
	CIni mIni;
	if(!strcmp(GameName,mIni.ReadValue("Global","GM_Name")))
	{
		theApp.GM_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","PAL_Name")))
	{
		theApp.PAL_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","CG2_Name")))
	{
		theApp.CG2_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","GT_Name")))
	{
		theApp.GTOWN_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","SDO_Name")))
	{
		theApp.SDO_DialogMsg(DlgName,WM_CLOSE,0,0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","JW2_Name")))
	{
		theApp.JW2_DialogMsg(DlgName,WM_CLOSE,0,0);
	}
	else if(!strcmp(GameName,mIni.ReadValue("Global","WA_Name")))
	{
		theApp.WA_DialogMsg(DlgName,WM_CLOSE,0,0);
	}
	if(!strcmp(DlgName, mIni.ReadValue("Global","AGABUNB")))
	{
		// AGABUNB 所有游戏帐号解封和封停.
		theApp.m_pCloseDialogFun(DlgName);//"AGABUNB");//maple update
	}
	else if(!strcmp(DlgName, mIni.ReadValue("Global","AccountQuery")))
	{
		// AGABUNB 所有游戏帐号解封和封停.
		theApp.m_pCloseDialogFun(DlgName);//"AccountQuery");//maple update
	}
	else if(!strcmp(DlgName, mIni.ReadValue("Global","BanQuery")))
	{
		// AGABUNB 所有游戏帐号解封和封停.
		theApp.m_pCloseDialogFun(DlgName);//"AccountQuery");//maple update
	}
	/////////////peng begin
	else if(!strcmp(GameName, mIni.ReadValue("Global","XD_Name")))
	{
		// AGABUNB 所有游戏帐号解封和封停.
		theApp.XD_DialogMsg(DlgName, WM_CLOSE, 0, 0);
	}
	////////////peng end
}

void CDlgSelect::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
	int selectItem = tbcSelect.GetCurSel();//获取被选中的标签页次序

	if(selectItem> -1)
	{
		char szItemName[100];
		TC_ITEM m_PTCItem;   
		memset( &m_PTCItem, 0, sizeof( TC_ITEM ) );   
		m_PTCItem.mask = TCIF_TEXT;   
		m_PTCItem.pszText = szItemName;   
		m_PTCItem.cchTextMax = 100;   
		m_PTCItem.iImage = -1;   

		tbcSelect.GetItem(selectItem, &m_PTCItem);
		CString DlgName = m_PTCItem.pszText;//获取被选中的标签页名称
		Ctabname::tabname=DlgName;

	}
}
