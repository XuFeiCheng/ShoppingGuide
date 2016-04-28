#pragma once
#include "afxcmn.h"

#include "ManagementDlg.h"
//#include "Management.h"
#include <vector>
//#include "afxwin.h"
#include "ShowWnd.h"
#pragma comment(lib,"ShopResDll.lib")
using namespace std;
// CMainFrame 对话框


//傻逼编译器！！！
class CManagementDlg;

class CMainFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CMainFrame)

public:
	CMainFrame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainFrame();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAINFRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 初始化所有控件
	void InitCtrls();
	// 销毁
	void DestoryCtrls();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	CListCtrl m_ListInfo;
private:
	// 父窗口指针
	CManagementDlg *m_pParent;
	CShowWnd m_Logo;
private:
	// 初始化所有商品信息
	void InitAllInfo();
public:
	// 获取楼层
	void GetFloor();
	vector<CString> m_vFloor;
	// 获取折扣率
	void GetDiscountByFNO();
	vector<CString> m_vDiscount;
	// 获取商品信息
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
