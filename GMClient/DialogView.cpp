// DialogView.cpp : 实现文件
//

#include "stdafx.h"
#include "GMClient.h"
#include "DialogView.h"


// CDialogView

IMPLEMENT_DYNCREATE(CDialogView, CView)

CDialogView::CDialogView()
{
}

CDialogView::~CDialogView()
{
}

BEGIN_MESSAGE_MAP(CDialogView, CView)
END_MESSAGE_MAP()


// CDialogView 绘图

void CDialogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CDialogView 诊断

#ifdef _DEBUG
void CDialogView::AssertValid() const
{
	CView::AssertValid();
}

void CDialogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CDialogView 消息处理程序
