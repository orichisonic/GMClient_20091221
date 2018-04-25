#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSDOITEMSET �Ի���

class CSDOITEMSET : public CDialog
{
	DECLARE_DYNAMIC(CSDOITEMSET)

public:
	CSDOITEMSET(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSDOITEMSET();

// �Ի�������
	enum { IDD = IDD_DLGITEMSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	// �����û��б�õ��к�
	int nItem;

	int nSelect,mItem;

	// ���з�������Ϣ
	CMap<int,int,CString,CString> ServerList;
		//�����б�
	CMap<int,int,int,int> ItemCodeList;

	// �ж��Ƿ���Ҫ��ҳ
	bool pageInfo;

	// ��Ϸ������Name
	CString ServerName;

	// ��Ϸ������IP
	CString ServerIP;

	//���������ʺźͽ�ɫ��
	CString Account, Name;

	// ��õ�����ʺźͽ�ɫ��
	CString UserAccount, UserName;

	//�����ؼ��ĸ߶�
	int grpHeight, tbcHeight,grpPHeight;

	//���ID
	int UserID;

	//��ҵȼ�
	int iLevel;

	//����ֵ
	int iExperience;

	//�ܾ���
	int iTotal;

	//ʤ����
	int iWin;

	//ƽ����
	int iBalance;

	//������
	int iFall;

	//����ֵ
	int iReputation;

	//G��
	int iGCash;

	//M��
	int iMCash;

	//�罻ֵ
	int iSocial;
	//����ֵ
	int iLucky;

	int iSex;//�Ա�

	int iType;//����ֵ
	int iSort;//С��ֵ

	int iItemCode;//���߱��
	CString ItemName;//��������

	int iItemCode1;//��ӵ��ߵı��
public:
	// CGroupBox��������
	CStatic GrpSearch;

	// CComboBox��Ϸ������
	CComboBox cmbServer;

	// CTabCtrlѡ�����
	CTabCtrl tbcResult;

	//��ҳ����
	CStatic GrpPage;

	//��ҳ��Ͽ�
	CComboBox cmbPage;
	CComboBox cmbUPage;

	//��ʾ�����Ϣ�б��
	CListCtrl listUser;

	// CListCtrlװ��
	CListCtrl listResult;

		//�������Ϣ�б�
	CListCtrl listGiftBox;

	// ָʾ�Ի���ǰ״̬
	int dlgStatus;

	// ��ʼ���Ի���
	virtual BOOL OnInitDialog();

	// ��ʼ����ʾ�ַ�
	void InitUI();

	// �Զ��ı��С
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//���ñ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// �رնԻ���
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();

	// ��ʾ��ɫ������Ϣ
	void ShowUserInfo(void);

	//��ʾ�޸Ľ�ɫ����
	void ShowUpdateUser();

	//��ʾװ��
	void ShowEquipment();

	//��ʾ�����
	void ShowGiftBox();

	//��ʾ��ӵ���
	void ShowAddItem();

	// �����û��б��浱ǰ�к�
	afx_msg void OnNMClickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//˫��װ����Ϣ�б�ɾ��
	afx_msg void OnNMDblclkListresult(NMHDR *pNMHDR, LRESULT *pResult);

	//˫���������Ϣ�б�ɾ��
	afx_msg void OnNMDblclkListgiftbox(NMHDR *pNMHDR, LRESULT *pResult);

	//�����ݼ���Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//����������������
	afx_msg void OnLvnColumnclickListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListresult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListgiftbox(NMHDR *pNMHDR, LRESULT *pResult);

	//�л���ҳ��Ͽ�
	afx_msg void OnCbnSelchangeCmbpage();
	afx_msg void OnCbnSelchangeCmbuipage();

	//��ѯ���������Ϣ
	afx_msg void OnBnClickedSearch();

	//�л�tabCtrl
	afx_msg void OnTcnSelchangeTabresult(NMHDR *pNMHDR, LRESULT *pResult);

	//װ����ѯ
	void EquipmentInfo();

	//����в�ѯ
	void GiftBoxInfo();

	//�޸Ľ�ɫ��Ϣ
	afx_msg void OnBnClickedBtupdate();

	//���ý�ɫ��Ϣ
	afx_msg void OnBnClickedBtreset();
	CComboBox cmbBigType;//����
	CComboBox cmbSmallType;//С��
	CComboBox cmbGoods;//��Ʒ����

	//���ർ������
	void BigTypeData();

	//�л�����
	afx_msg void OnCbnSelchangeCmbbigtype();

	//�л�С��
	afx_msg void OnCbnSelchangeCmbsmalltype();

	//���߲�ѯ
	void MaleItem();

	//ģ����ѯ����
	afx_msg void OnBnClickedBtquery();

	afx_msg void OnBnClickedCheck1();
	CButton btnDark;//ģ����ѯ

	//��ӵ���
	afx_msg void OnBnClickedBtadd();

	//ģ����ѯ�ĵ����б�
	CListBox listItem;

	// ���շ�����Ϣ
	LRESULT OnMessageReceive(WPARAM wParam, LPARAM lParam);

	//ɾ������װ��
	void DeleteEquipment();

	//ɾ�������
	void DeleteGiftBox();

	//˫����ɫ��Ϣ�б�
	afx_msg void OnNMDblclkListuserinfo(NMHDR *pNMHDR, LRESULT *pResult);

	//�޸��罻ֵ
	afx_msg void OnBnClickedBtnsocial();

	//�޸�����ֵ
	afx_msg void OnBnClickedBtnlucky();
};
