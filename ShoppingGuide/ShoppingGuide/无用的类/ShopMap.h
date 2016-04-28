#pragma once


// CShopMap
#include <vector>
using namespace std;
class CShopMap : public CWnd
{
	DECLARE_DYNAMIC(CShopMap)

public:
	CShopMap();
	virtual ~CShopMap();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:

	int m_nPic;

	CDC m_dc;
	CBitmap m_memBMP;
	// 初始化DC
	void InitUserCtrls();
	void DestoryUserCtrls();
public:
	// //绘制整个地图区域
	void DrawWnd(int nPic);
	// 画路线
	void DrawLine(vector<CPoint> loca);
};


