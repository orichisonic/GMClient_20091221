// GMClientView.cpp : CGMClientView 类的实现
//

#include "stdafx.h"
#include "GMClient.h"

#include "GMClientDoc.h"
#include "GMClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGMClientView

IMPLEMENT_DYNCREATE(CGMClientView, CView)

BEGIN_MESSAGE_MAP(CGMClientView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGMClientView 构造/析构

CGMClientView::CGMClientView()
{
	// TODO: 在此处添加构造代码

}

CGMClientView::~CGMClientView()
{
}

BOOL CGMClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CGMClientView 绘制

void CGMClientView::OnDraw(CDC* /*pDC*/)
{
	CGMClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGMClientView 打印

BOOL CGMClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGMClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CGMClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CGMClientView 诊断

#ifdef _DEBUG
void CGMClientView::AssertValid() const
{
	CView::AssertValid();
}

void CGMClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGMClientDoc* CGMClientView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGMClientDoc)));
	return (CGMClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CGMClientView 消息处理程序
