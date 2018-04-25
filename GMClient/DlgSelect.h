#pragma once
#include "afxcmn.h"



// CDlgSelect ������ͼ

class CDlgSelect : public CFormView
{
	DECLARE_DYNCREATE(CDlgSelect)

protected:
	CDlgSelect();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDlgSelect();

public:
	enum { IDD = IDD_DLGTABSELECT };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	//�ڱ�ǩ������ӹرշ���
	CImageList m_imagetab;

public:
	//CTabCtrl�����л��Ի���
	CTabCtrl tbcSelect;

	//��ʼ������
	virtual void OnInitialUpdate();

	//�Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//����ͼ����йر�
	afx_msg void OnNMClickTabselect(NMHDR *pNMHDR, LRESULT *pResult);

	//ѡ��ͬ��CTabCtrl�����л��Ի���
	afx_msg void OnTcnSelchangeTabselect(NMHDR *pNMHDR, LRESULT *pResult);

	//���մ򿪶Ի������Ϣ
	LRESULT OnRecView(WPARAM wParam, LPARAM lParam);

	//������ʾ�Ի������Ϣ
	LRESULT OnShowDlg(WPARAM wParam, LPARAM lParam);

	//��ӦWM_CLOSE��Ϣ
	afx_msg void OnClose();

	//��ʾ�Ի���
	void ShowDialog(CString GameName,CString DlgName);

	void CloseDialog(CString GameName,CString DlgName);
	afx_msg void OnPaint();
};


