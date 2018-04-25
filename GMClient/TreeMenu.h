#pragma once
#include "afxcmn.h"



// CTreeMenu ������ͼ

class CTreeMenu : public CFormView
{
	DECLARE_DYNCREATE(CTreeMenu)

protected:
	CTreeMenu();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTreeMenu();

public:
	enum { IDD = IDD_DLGTREE };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
    //������
	HTREEITEM m_root[50];

	//CTreeCtrl����
	CTreeCtrl tMenuList;

	//��ʼ������
	virtual void OnInitialUpdate();

	//����Form
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//�Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//������Ϣ
	LRESULT OnRecView(WPARAM wParam, LPARAM lParam);

	//˫��CTreeCtrl
	afx_msg void OnNMDblclkTreemenu(NMHDR *pNMHDR, LRESULT *pResult);

	//�Ҽ����CTreeCtrl�����˵�
	afx_msg void OnNMRclickTreemenu(NMHDR *pNMHDR, LRESULT *pResult);

	//���ˢ�²˵�ʱ���еĲ���
	afx_msg void OnRefresh();
};


