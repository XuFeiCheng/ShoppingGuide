
// ShoppingGuideDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "FeedBack.h"
#include "vector"
#include "FindRoad.h"
using namespace std;
//���붯̬���ӿ�
#include "ShowWnd.h"
#pragma comment(lib,"ShopResDll.lib")
//CShoppingGuideDlg �Ի���
class CShoppingGuideDlg : public CDialogEx
{
// ����
public:
	CShoppingGuideDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SHOPPINGGUIDE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CButton m_Search;

	// ��ʼ���̳�������Ϣ
	void InitShopData();
	// ���ٿؼ�
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
	// �������ݿ�
	BOOL LinkDB();

	// ��ȡ¥�㲢��ʼ���ؼ�
	void GetAllFloor();
	// ��ȡ�������Ʒ��Ϣ
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

	vector<Data> m_vFloor;//¥��ͼƬ����Ӧ������Ϣ
	vector<Data> m_vPros;// ��ƷͼƬID,λ����Ϣ
	vector<int> m_vEnter;//¥����ڱ��

	vector<LocatPosition> m_vLocation;//λ�ñ�ţ�λ������

	//vector<Data> m_vtbLoca;//�洢������Ϣ����
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
	// ��ȡ¥��λ����Ϣ
	void GetFloorPosition();
	// ����ͼ
	void InitRoad();

public:
	afx_msg void OnBnClickedButtonFeedback();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
private:
	// �ۿ�
	CComboBox m_Discount;
	// ��ʼ���ۿ�����
	void InitDiscount();
	vector<CString> m_vDiscount;
public:
	afx_msg void OnCbnSelchangeComboDiscount();
private:
	// ��Ʒ��
	CString m_Pname;
	int FindProbyName(int& nPic);
public:
	// ��ʼ����ǰ��Ʒ�۸�
	void InitPrice(int Fno, CString& Discount);
};
