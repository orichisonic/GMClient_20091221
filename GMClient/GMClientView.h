// GMClientView.h : CGMClientView 类的接口
//


#pragma once


class CGMClientView : public CView
{
protected: // 仅从序列化创建
	CGMClientView();
	DECLARE_DYNCREATE(CGMClientView)

// 属性
public:
	CGMClientDoc* GetDocument() const;

// 操作
public:

// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGMClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GMClientView.cpp 的调试版本
inline CGMClientDoc* CGMClientView::GetDocument() const
   { return reinterpret_cast<CGMClientDoc*>(m_pDocument); }
#endif

