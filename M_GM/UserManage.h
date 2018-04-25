#pragma once

#include <afxtempl.h>
#include ".\popedommanage.h"
#include "OperationGM.h"
// CUserManage �Ի���

class CUserManage : public CDialog
{
	DECLARE_DYNAMIC(CUserManage)

public:
	CUserManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserManage();

// �Ի�������
	enum { IDD = IDD_DLGUSERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	// �����û��б�õ��к�
	int nItem;

	// ���в�����Ϣ
	CMap<int,int,CString,CString> DepartData;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	//�����ؼ��ĸ߶�
	int grpHeight,tbcHeight;

	//Ȩ�޹�����
	CPopedomManage popedomManage;

public:
	// TabCtrl����
	CTabCtrl tbcResult;

	// ListCtrl����
	CListCtrl listUser;

	// ͣ�ø��ʺ�
	CButton cBtnExit;

	// �û�����
	CButton cBtnOnline;

	// ϵͳ����Ա
	CButton cBtnSysAdmin;

	// ���Ź���Ա
	CButton cBtnDepartAdmin;

	// ʹ��ʱЧ
	CDateTimeCtrl dtpEndTime;

	// �û��б��ҳ��
	CComboBox cmbPage;

	// GroupBox
	CStatic GrpSearch;

	// ������ڲ���
	CComboBox cmbDepart;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

public:
	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	//�����ݼ���Ӧ����
    virtual BOOL PreTranslateMessage(MSG* pMsg);

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// ���������û���Ϣ�б�
	void InitUserList();

	// ��ҳ��ѯ�û��б�
	afx_msg void OnCbnSelchangeCmbpage();

	// �л�ѡ����в���
	afx_msg void OnTcnSelchangeTabusermanage(NMHDR *pNMHDR, LRESULT *pResult);

	// �������в����б�
	void DepartList();

	// ��ӻ��޸��û���Ϣ
	afx_msg void OnBnClickedAdduser();

	// ����û���Ϣ
	void AddUser();

	// �޸��û���Ϣ
	void EditUser();

	// ������Ϣ
	afx_msg void OnBnClickedReset();

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuser(NMHDR *pNMHDR, LRESULT *pResult);

	// ˫���û��б����ɾ��
	afx_msg void OnNMDblclkListuser(NMHDR *pNMHDR, LRESULT *pResult);

	// �Ҽ�����û��б����Ȩ��
	afx_msg void OnNMRclickListuser(NMHDR *pNMHDR, LRESULT *pResult);

	//�޸��û�����
	afx_msg void OnModiUserPwd();

	// ��ѡ���û�����Ȩ��
	afx_msg void OnPopedomManage();

	//�����û�MAC
	afx_msg void OnUpdateUserMAC();

	// �����ʺ�Ϊϵͳ����Ա
	afx_msg void OnBnClickedChecksysmanage();

	// �����ʺ�Ϊ���Ź���Ա
	afx_msg void OnBnClickedCheckdepart();

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//�رնԻ���
	afx_msg void OnClose();
};
