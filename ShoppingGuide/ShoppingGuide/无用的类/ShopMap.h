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
	// ��ʼ��DC
	void InitUserCtrls();
	void DestoryUserCtrls();
public:
	// //����������ͼ����
	void DrawWnd(int nPic);
	// ��·��
	void DrawLine(vector<CPoint> loca);
};


