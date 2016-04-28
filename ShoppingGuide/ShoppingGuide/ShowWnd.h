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
	// ���ƴ���
	
	void DrawWnd(int nPic);

	//ģ��vector�洢���Ƶ����Ϣ
	template<class T>
	void DrawLine(vector<T> loca);

private:
	CBitmap m_picBMP;
	CDC m_picDC;
	int m_TextPosX;
	CString m_strText;

	CFont m_TextFont;

public:
	// ��������ʱ��
	void SetBottomTime(COLORREF color = RGB(129, 170, 190));
	// ���ù�����Ļ
	void SetMoveText(CString& str, int time, COLORREF color=RGB(130, 170, 220),int nPic = 0);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	// �����ƶ���Ļ
	void DrawMoveText();
	// ����ʱ����
	void DrawTime();
public:

};


//ģ��vector�洢���Ƶ����Ϣ

template<class T>
void CShowWnd::DrawLine(vector<T> loca)
{
	if (loca.size() <= 1)
	{
		AfxMessageBox(_T("�������ݴ���"));
		return;
	}
	DrawWnd(m_nPic);
	m_dc.SetBkMode(TRANSPARENT);

	m_dc.SetTextColor(RGB(255, 255, 100));
	CPen pen(PS_SOLID, 4, RGB(0, 255, 0));
	CPen *old = m_dc.SelectObject(&pen);

	CPoint pre = loca[0];
	m_dc.TextOutW(loca[0].x + 6, loca[0].y, _T("���λ��"));
	UINT i;
	for (i = 1; i < loca.size(); i++)
	{
		m_dc.MoveTo(pre);
		m_dc.LineTo(loca[i]);
		pre = loca[i];
	}

	m_dc.Ellipse(loca[i - 1].x - 10, loca[i - 1].y - 10, loca[i - 1].x + 10, loca[i - 1].y + 10);


	m_dc.TextOutW(loca[i - 1].x + 10, loca[i - 1].y + 10, _T("�յ�"));




	m_dc.SelectObject(old);
	pen.DeleteObject();
	Invalidate();
}
