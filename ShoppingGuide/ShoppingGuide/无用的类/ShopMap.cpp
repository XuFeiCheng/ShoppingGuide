// ShopMap.cpp : 实现文件
//

#include "stdafx.h"
#include "ShoppingGuide.h"
#include "ShopMap.h"


// CShopMap

IMPLEMENT_DYNAMIC(CShopMap, CWnd)

CShopMap::CShopMap()
{
	m_nPic = 301;
}

CShopMap::~CShopMap()
{
}


BEGIN_MESSAGE_MAP(CShopMap, CWnd)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CShopMap 消息处理程序




BOOL CShopMap::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO:  在此添加专用代码和/或调用基类

	BOOL res = CWnd::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID);
	InitUserCtrls();
	return res;
}


void CShopMap::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	DestoryUserCtrls();
}


void CShopMap::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect rc;
	GetClientRect(rc);
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &m_dc, 0, 0, SRCCOPY);
}


BOOL CShopMap::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return TRUE;//CWnd::OnEraseBkgnd(pDC);
}


// 初始化DC
void CShopMap::InitUserCtrls()
{
	CDC *pDC = GetDC();
	m_dc.CreateCompatibleDC(pDC);

	CRect rc;
	GetClientRect(rc);
	m_memBMP.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());

	m_dc.SelectObject(&m_memBMP);

	ReleaseDC(pDC);

}


void CShopMap::DestoryUserCtrls()
{
	if (NULL != m_dc.GetSafeHdc())
	{
		m_dc.DeleteDC();
	}
	if (NULL != m_memBMP.GetSafeHandle())
	{
		m_memBMP.DeleteObject();
	}
}


// //绘制整个地图区域
void CShopMap::DrawWnd(int nPic)
{
	m_nPic = nPic;
	CRect rc;
	GetClientRect(rc);
	m_dc.FillSolidRect(rc, RGB(127, 128 ,129));
	CDC *pDC = GetDC();

	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.LoadBitmapW(m_nPic);

	tempDC.SelectObject(&bmp);


	m_dc.BitBlt(0,0,rc.Width(),rc.Height(),&tempDC,0,0,SRCCOPY);

	if (bmp.GetSafeHandle() != NULL)
	{
		bmp.DeleteObject();
	}
	if (tempDC.GetSafeHdc() != NULL)
	{
		tempDC.DeleteDC();
	}
	ReleaseDC(pDC);

	Invalidate();
}


// 画路线
void CShopMap::DrawLine(vector<CPoint> loca)
{
	if (loca.size() <= 1)
	{
		AfxMessageBox(_T("输入数据错误！"));
		return;
	}
	DrawWnd(m_nPic);
	m_dc.SetBkMode(TRANSPARENT);

	m_dc.SetTextColor(RGB(255,255,100));
	CPen pen(PS_SOLID,6,RGB(0,255,0));
	CPen *old = m_dc.SelectObject(&pen);

	CPoint pre = loca[0];
	m_dc.TextOutW(loca[0].x+6, loca[0].y, _T("你的位置"));
	UINT i;
	for (i = 1; i < loca.size();i++)
	{
		m_dc.MoveTo(pre);
		m_dc.LineTo(loca[i]);
		pre = loca[i];
	}

	m_dc.Ellipse(loca[i - 1].x - 10, loca[i - 1].y - 10, loca[i - 1].x + 10, loca[i - 1].y + 10);


	m_dc.TextOutW(loca[i - 1].x+10, loca[i-1].y+10,_T("终点"));




	m_dc.SelectObject(old);
	pen.DeleteObject();
	Invalidate();
}
