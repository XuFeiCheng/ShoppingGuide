// ShowWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "ShowWnd.h"


// CShowWnd

IMPLEMENT_DYNAMIC(CShowWnd, CWnd)

CShowWnd::CShowWnd()
{
	m_nPic = 130;
	m_TextPosX = 5;
	m_strText = _T("");
}

CShowWnd::~CShowWnd()
{
}


BEGIN_MESSAGE_MAP(CShowWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CShowWnd 消息处理程序



//重写创建窗口
BOOL CShowWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO:  在此添加专用代码和/或调用基类

	BOOL res =  CWnd::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID);
	InitDC();
	//时间种子

	srand((unsigned)time(NULL));

	return res;
}


void CShowWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect rc;
	GetClientRect(rc);

	dc.BitBlt(0,0,rc.Width(),rc.Height(),&m_dc,0,0,SRCCOPY);
}


BOOL CShowWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return TRUE;//CWnd::OnEraseBkgnd(pDC);
}


void CShowWnd::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	DestoryDC();
}


void CShowWnd::InitDC()
{
	DestoryDC();
	CDC *pDC = GetDC();
	m_dc.CreateCompatibleDC(pDC);

	CRect rc;
	GetClientRect(rc);
	m_bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	
	m_dc.SelectObject(&m_bmp);


	m_picDC.CreateCompatibleDC(pDC);
	ReleaseDC(pDC);
}


void CShowWnd::DestoryDC()
{
	if (m_bmp.GetSafeHandle() != NULL)
	{
		m_bmp.DeleteObject();
	}
	if (m_dc.GetSafeHdc() != NULL)
	{
		m_dc.DeleteDC();
	}
	if (m_picBMP.GetSafeHandle() != NULL)
	{
		m_picBMP.DeleteObject();

	}
	if (m_picDC.GetSafeHdc() != NULL)
	{
		m_picDC.DeleteDC();
	}

	if (m_TextFont.GetSafeHandle() != NULL)
	{
		m_TextFont.DeleteObject();
		KillTimer(1);
		KillTimer(2);
	}

}


// 绘制窗口
void CShowWnd::DrawWnd(int nPic)
{


	CRect rc;
	GetClientRect(rc);

	m_dc.FillSolidRect(rc, RGB(0, 0, 0));

	m_nPic = nPic;


	//重新加载位图
	if (m_picBMP.GetSafeHandle() != NULL)
	{
		m_picBMP.DeleteObject();
	}
	m_picBMP.LoadBitmapW(nPic);

	m_picDC.SelectObject(&m_picBMP);

	//贴
	m_dc.BitBlt(0, 0, rc.Width(), rc.Height(), &m_picDC, 0, 0, SRCCOPY);

	Invalidate();


}



//划线
/*
void CShowWnd::DrawLine(vector<CPoint> loca)
{
	if (loca.size() <= 1)
	{
		AfxMessageBox(_T("输入数据错误！"));
		return;
	}
	DrawWnd(m_nPic);
	m_dc.SetBkMode(TRANSPARENT);

	m_dc.SetTextColor(RGB(255, 255, 100));
	CPen pen(PS_SOLID, 6, RGB(0, 255, 0));
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
*/



// 设置滚动字幕
void CShowWnd::SetMoveText(CString& str, int time, COLORREF color, int nPic)
{
	m_strText = str;

	if (nPic < 101 || nPic > 107)
	{
		nPic = rand() % 7 + 101;
	}
	m_nPic = nPic;
	//if (m_nPic == 103)
	//{
	//	DrawWnd(m_nPic);
	//}
	//else
	//{

	
		//初始化字体
		VERIFY(m_TextFont.CreateFont(
			30,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			DEFAULT_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("微软雅黑")));                 // lpszFacename
		//设置字体

		m_dc.SelectObject(&m_TextFont);
		m_dc.SetBkMode(TRANSPARENT);
		//字体颜色
		m_dc.SetTextColor(color);
		SetTimer(1, time, NULL);
//	}

}


void CShowWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{

	case 1:
		DrawMoveText();
		break;
	case 2:
		DrawTime();
		break;
	default:
		break;
	}
	CWnd::OnTimer(nIDEvent);
}


// 绘制移动字幕
void CShowWnd::DrawMoveText()
{
	CRect rc;
	GetClientRect(rc);
	m_dc.FillSolidRect(rc, RGB(0, 0, 0));
	rc.right = rc.Width();

	//重新加载位图
	if (m_picBMP.GetSafeHandle() != NULL)
	{
		m_picBMP.DeleteObject();
	}
	m_picBMP.LoadBitmapW(m_nPic);

	m_picDC.SelectObject(&m_picBMP);

	//贴
	m_dc.BitBlt(0, 0, rc.Width(), rc.Height(), &m_picDC, 0, 0, SRCCOPY);


	//写字

	//int nWidth = m_strText.GetLength() *23 + 10;
	//int nCount = rc.Width() / nWidth;
	//for (int i = 0; i < nCount;i++)
	//{
	//	m_dc.TextOutW(m_TextPosX + i*nWidth, 5, m_strText);
	//}
	m_dc.TextOutW(m_TextPosX, 5, m_strText);

	m_TextPosX = m_TextPosX + 2;
	if (m_TextPosX >= rc.Width() )
	{
		m_TextPosX = 0;
	}
	

	Invalidate();

}

CString Week[] = { _T("Sunday"), L"Monday", L"Tuesday", L"Wednesday", L"Thursday", L"Friday", L"Saturday" };

// 底栏时间区
void CShowWnd::DrawTime()
{
	CRect rc;
	GetClientRect(rc);
	m_dc.FillSolidRect(rc, RGB(20, 20, 20));
	//rc.left = rc.Width() - 200;

	CTime tm = CTime::GetCurrentTime();
	CString strTime = tm.Format(_T("%Y/%m/%d %H:%M:%S"));

	CString strTitle;
	strTitle.Format(_T("%s\r\n%s"), strTime, Week[tm.GetDayOfWeek()-1]);
	
	m_dc.DrawText(strTitle, rc, DT_CENTER);

	Invalidate();
}


// 开启底栏时间
void CShowWnd::SetBottomTime(COLORREF color)
{
	//初始化字体
	VERIFY(m_TextFont.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		DEFAULT_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("微软雅黑")));                 // lpszFacename
	//设置字体

	m_dc.SelectObject(&m_TextFont);
	m_dc.SetBkMode(TRANSPARENT);
	//字体颜色
	m_dc.SetTextColor(color);

	SetTimer(2, 1000, NULL);
}
