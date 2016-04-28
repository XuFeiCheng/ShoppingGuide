
// ShoppingGuideDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "FeedBack.h"
#include "vector"
#include "FindRoad.h"
using namespace std;
//导入动态链接库
#include "ShowWnd.h"
#pragma comment(lib,"ShopResDll.lib")
//CShoppingGuideDlg 对话框
class CShoppingGuideDlg : public CDialogEx
{
// 构造
public:
	CShoppingGuideDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SHOPPINGGUIDE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CButton m_Search;

	// 初始化商场所有信息
	void InitShopData();
	// 销毁控件
	void DestoryCtrls();
	
	CShowWnd m_Pic;
	CShowWnd m_Map;
	CShowWnd m_ShopLog;
	CShowWnd m_BottomTime;
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:

public:
	afx_msg void OnBnClickedButtonSearch();
private:
	// 链接数据库
	BOOL LinkDB();

	// 获取楼层并初始化控件
	void GetAllFloor();
	// 获取本层的商品信息
	void GetProByFNO(int Fno, CString& Discount);
	typedef struct
	{
		int nID;
		int nPic;
		CString tbLocation;
		CString tbMatrix;
	}Data;
	typedef struct
	{
		int x;
		int y;
		int nID;
	}LocatPosition;

	vector<Data> m_vFloor;//楼层图片，对应矩阵信息
	vector<Data> m_vPros;// 产品图片ID,位置信息
	vector<int> m_vEnter;//楼层入口编号

	vector<LocatPosition> m_vLocation;//位置编号，位置坐标

	//vector<Data> m_vtbLoca;//存储本地信息表名
	CComboBox m_Floor;
	CComboBox m_Enter;
	CComboBox m_Pros;

	CFindRoad m_Road;


public:
	afx_msg void OnCbnSelchangeComboFloor();
private:
	void SetFloorEnter(int Fno);
public:
	afx_msg void OnCbnSelchangeComboGoods();
private:
	// 获取楼层位置信息
	void GetFloorPosition();
	// 创建图
	void InitRoad();

public:
	afx_msg void OnBnClickedButtonFeedback();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
private:
	// 折扣
	CComboBox m_Discount;
	// 初始化折扣数据
	void InitDiscount();
	vector<CString> m_vDiscount;
public:
	afx_msg void OnCbnSelchangeComboDiscount();
private:
	// 商品名
	CString m_Pname;
	int FindProbyName(int& nPic);
public:
	// 初始化当前商品价格
	void InitPrice(int Fno, CString& Discount);
};
