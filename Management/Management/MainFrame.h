#pragma once
#include "afxcmn.h"

#include "ManagementDlg.h"
//#include "Management.h"
#include <vector>
//#include "afxwin.h"
#include "ShowWnd.h"
#pragma comment(lib,"ShopResDll.lib")
using namespace std;
// CMainFrame �Ի���


//ɵ�Ʊ�����������
class CManagementDlg;

class CMainFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CMainFrame)

public:
	CMainFrame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainFrame();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAINFRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ʼ�����пؼ�
	void InitCtrls();
	// ����
	void DestoryCtrls();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	CListCtrl m_ListInfo;
private:
	// ������ָ��
	CManagementDlg *m_pParent;
	CShowWnd m_Logo;
private:
	// ��ʼ��������Ʒ��Ϣ
	void InitAllInfo();
public:
	// ��ȡ¥��
	void GetFloor();
	vector<CString> m_vFloor;
	// ��ȡ�ۿ���
	void GetDiscountByFNO();
	vector<CString> m_vDiscount;
	// ��ȡ��Ʒ��Ϣ
	void GetInfoByFNO_Discount();
	vector<int> m_vProPicID;
	CComboBox m_Floor;
	CComboBox m_Discount;


	afx_msg void OnCbnSelchangeComboFloor();
	afx_msg void OnCbnSelchangeComboDiscount();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMClickListInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonModifty();
};
