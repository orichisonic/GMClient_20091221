#pragma once

// CDialogView 视图

class CDialogView : public CView
{
	DECLARE_DYNCREATE(CDialogView)

protected:
	CDialogView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDialogView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制此视图
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


