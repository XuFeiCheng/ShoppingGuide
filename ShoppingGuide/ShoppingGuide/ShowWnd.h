#pragma once

#include "Resource.h"
#include "afxwin.h"

#include <vector>
using namespace std;

class AFX_EXT_CLASS CShowWnd : public CWnd
{
	DECLARE_DYNAMIC(CShowWnd)

public:
	CShowWnd();
	virtual ~CShowWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
private:
	CDC m_dc;
	int m_nPic;
	CBitmap m_bmp;
	void InitDC();
	void DestoryDC();
public:
	// 绘制窗口
	
	void DrawWnd(int nPic);

	//模板vector存储绘制点的信息
	template<class T>
	void DrawLine(vector<T> loca);

private:
	CBitmap m_picBMP;
	CDC m_picDC;
	int m_TextPosX;
	CString m_strText;

	CFont m_TextFont;

public:
	// 开启底栏时间
	void SetBottomTime(COLORREF color = RGB(129, 170, 190));
	// 设置滚动字幕
	void SetMoveText(CString& str, int time, COLORREF color=RGB(130, 170, 220),int nPic = 0);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	// 绘制移动字幕
	void DrawMoveText();
	// 底栏时间区
	void DrawTime();
public:

};


//模板vector存储绘制点的信息

template<class T>
void CShowWnd::DrawLine(vector<T> loca)
{
	if (loca.size() <= 1)
	{
		AfxMessageBox(_T("输入数据错误！"));
		return;
	}
	DrawWnd(m_nPic);
	m_dc.SetBkMode(TRANSPARENT);

	m_dc.SetTextColor(RGB(255, 255, 100));
	CPen pen(PS_SOLID, 4, RGB(0, 255, 0));
	CPen *old = m_dc.SelectObject(&pen);

	CPoint pre = loca[0];
	m_dc.TextOutW(loca[0].x + 6, loca[0].y, _T("你的位置"));
	UINT i;
	for (i = 1; i < loca.size(); i++)
	{
		m_dc.MoveTo(pre);
		m_dc.LineTo(loca[i]);
		pre = loca[i];
	}

	m_dc.Ellipse(loca[i - 1].x - 10, loca[i - 1].y - 10, loca[i - 1].x + 10, loca[i - 1].y + 10);


	m_dc.TextOutW(loca[i - 1].x + 10, loca[i - 1].y + 10, _T("终点"));




	m_dc.SelectObject(old);
	pen.DeleteObject();
	Invalidate();
}
