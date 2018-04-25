// GMClientDoc.cpp :  CGMClientDoc 类的实现
//

#include "stdafx.h"
#include "GMClient.h"

#include "GMClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGMClientDoc

IMPLEMENT_DYNCREATE(CGMClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CGMClientDoc, CDocument)
END_MESSAGE_MAP()


// CGMClientDoc 构造/析构

CGMClientDoc::CGMClientDoc()
{
	// TODO: 在此添加一次性构造代码

}

CGMClientDoc::~CGMClientDoc()
{
}

BOOL CGMClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGMClientDoc 序列化

void CGMClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGMClientDoc 诊断

#ifdef _DEBUG
void CGMClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGMClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGMClientDoc 命令
