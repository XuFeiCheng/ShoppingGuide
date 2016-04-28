
// ShoppingGuideDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShoppingGuide.h"
#include "ShoppingGuideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShoppingGuideDlg 对话框



CShoppingGuideDlg::CShoppingGuideDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShoppingGuideDlg::IDD, pParent)
	, m_Pname(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CShoppingGuideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_Search);

	DDX_Control(pDX, IDC_COMBO_FLOOR, m_Floor);
	DDX_Control(pDX, IDC_COMBO_ENTER, m_Enter);
	DDX_Control(pDX, IDC_COMBO_GOODS, m_Pros);
	DDX_Control(pDX, IDC_COMBO_ENTER2, m_Discount);
	DDX_Text(pDX, IDC_EDIT1, m_Pname);
}

BEGIN_MESSAGE_MAP(CShoppingGuideDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CShoppingGuideDlg::OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_FLOOR, &CShoppingGuideDlg::OnCbnSelchangeComboFloor)
	ON_CBN_SELCHANGE(IDC_COMBO_GOODS, &CShoppingGuideDlg::OnCbnSelchangeComboGoods)
	ON_BN_CLICKED(IDC_BUTTON_FEEDBACK, &CShoppingGuideDlg::OnBnClickedButtonFeedback)
	ON_WM_SETCURSOR()
	ON_CBN_SELCHANGE(IDC_COMBO_DISCOUNT, &CShoppingGuideDlg::OnCbnSelchangeComboDiscount)
END_MESSAGE_MAP()


// CShoppingGuideDlg 消息处理程序

BOOL CShoppingGuideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	InitShopData();



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShoppingGuideDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShoppingGuideDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShoppingGuideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// 初始化商场所有信息
void CShoppingGuideDlg::InitShopData()
{
	CRect rc;
	GetClientRect(rc);
	rc.left = 322;        
	rc.top = 18;
	rc.bottom = rc.top + 600;
	rc.right = rc.left + 860;

	m_Map.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_MAP);
	
	GetClientRect(rc);


	rc.top = 285;
	rc.bottom = rc.top+290;	
	rc.left = 5;
	rc.right = rc.left+290;

	m_Pic.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_PROLOG);

	//shopLOG
	GetClientRect(rc);

//	rc.left = (rc.Width() - 1024) / 2;
	rc.top = rc.bottom-40;
	rc.right = 1024;
//	rc.bottom = rc.top + 40;
	m_ShopLog.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_SHOPLOG);
	m_ShopLog.SetMoveText(CString(_T("~欢迎光临XX商场~")), 30,RGB(133,202,125));


	//BottomTime
	GetClientRect(rc);
	rc.top = rc.bottom - 40;
	rc.left = 1024;
	m_BottomTime.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_WND_BOTTOMTIME);
	m_BottomTime.SetBottomTime();

	if (!LinkDB())
	{
		AfxMessageBox(_T("链接数据库失败！"));
		exit(0);
	}
	//获取楼层
	GetAllFloor();


	//折扣
	InitDiscount();
	//获取商品及价格
	GetProByFNO(m_vFloor[m_Floor.GetCurSel()].nID, m_vDiscount[m_Discount.GetCurSel()]);
	//设置入口
	SetFloorEnter(m_vFloor[m_Floor.GetCurSel()].nID);
	//LOGO
	m_Pic.DrawWnd(m_vPros[m_Pros.GetCurSel()].nPic);
	//导航图
	m_Map.DrawWnd(m_vFloor[m_Floor.GetCurSel()].nPic);


	SetTimer(1, 1000, NULL);
}


// 销毁控件
void CShoppingGuideDlg::DestoryCtrls()
{
	if (m_Map.GetSafeHwnd() != NULL)
	{
		m_Map.DestroyWindow();
	}

	if (CShoppingGuideApp::staffDB.IsOpen())
	{
		CShoppingGuideApp::staffDB.Close();
	}
	if (m_ShopLog.GetSafeHwnd() != NULL)
	{
		m_ShopLog.DestroyWindow();
	}
	if (m_Pic.GetSafeHwnd() != NULL)
	{
		m_Pic.DestroyWindow();
	}
	if (m_BottomTime.GetSafeHwnd() != NULL)
	{
		m_BottomTime.DestroyWindow();
	}
	m_Road.Clear();
}


void CShoppingGuideDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	DestoryCtrls();
}


void CShoppingGuideDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值



	CTime tm = CTime::GetCurrentTime();
	CString strTime = tm.Format(_T("%Y/%m/%d %H:%M:%S"));

	CString strTitle;
	strTitle.Format(_T("XX商场导购系统   %s"),strTime);
	SetWindowText(strTitle);

	CDialogEx::OnTimer(nIDEvent);
}

//点击查询按钮事件
void CShoppingGuideDlg::OnBnClickedButtonSearch()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);



	int nPro = m_vPros[m_Pros.GetCurSel()].nID;
	int nPic = m_vPros[m_Pros.GetCurSel()].nPic;
	if (!m_Pname.IsEmpty())
	{
		
		nPro = FindProbyName(nPic);
		if (nPro == -1)
		{
			AfxMessageBox(L"本楼层没有该商品，请换个楼层试试。");
			return;
		}
		
	}
	m_Pic.DrawWnd(nPic);
	//初始化图
	InitRoad();


	m_Road.find_the_path(m_vEnter[m_Enter.GetCurSel()], nPro);//寻路

	m_Road.m_road.push_back(nPro);//插入商品位置

	CPoint start;
	start.x = m_vLocation[m_vEnter[m_Enter.GetCurSel()]].x;
	start.y = m_vLocation[m_vEnter[m_Enter.GetCurSel()]].y;

	
	vector<CPoint > locat;
	locat.push_back(start);
	for (UINT i = 0; i < m_Road.m_road.size(); i++)
	{
		locat.push_back(CPoint(m_vLocation[m_Road.m_road[i]].x, m_vLocation[m_Road.m_road[i]].y));
	}

	m_Map.DrawLine(locat);

	m_Pname = L"";
	UpdateData(FALSE);

}


// 链接数据库
BOOL CShoppingGuideDlg::LinkDB()
{
	CString SVname;
	CString DBname;
	CString Account;
	CString PassWord;
	//读取配置文件
	//服务器名字
	GetPrivateProfileString(_T("DataBaseConfig"), _T("ServerName "), _T("读取错误"), SVname.GetBuffer(20), 20, _T(".\\DB.ini"));
	SVname.ReleaseBuffer();
	//登陆账号
	GetPrivateProfileString(_T("DataBaseConfig"), _T("Account"), _T("读取错误"), Account.GetBuffer(20), 20, _T(".\\DB.ini"));
	Account.ReleaseBuffer();
	//登陆密码
	GetPrivateProfileString(_T("DataBaseConfig"), _T("PassWord"), _T("读取错误"), PassWord.GetBuffer(20), 20, _T(".\\DB.ini"));
	PassWord.ReleaseBuffer();
	//连接数据库的名字
	GetPrivateProfileString(_T("PrivateConfig"), _T("DataBaseName "), _T("读取错误"), DBname.GetBuffer(20), 20, _T(".\\DB.ini"));
	DBname.ReleaseBuffer();


	if (SVname.Compare(_T("读取错误")) == 0 || DBname.Compare(_T("读取错误")) == 0 || Account.Compare(_T("读取错误")) == 0 || PassWord.Compare(_T("读取错误")) == 0)
	{
		MessageBox(_T("应用程序配置文件读取错误！"), _T("系统提示"), MB_ICONSTOP);
		exit(0);
	}





	CString strConnect;
	strConnect.Format(_T("Provider=sqloledb;Data Source=%s;Initial Catalog=%s;User Id=%s;Password=%s;"), SVname,DBname, Account, PassWord);
	return CShoppingGuideApp::staffDB.Open(strConnect);
}


// 获取楼层并初始化控件
void CShoppingGuideDlg::GetAllFloor()
{
	m_vFloor.clear();
	m_Floor.ResetContent();
	CString strSQL = _T("select * from tbFloor");

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	if (rs.Open(strSQL))
	{
		CString strField;
		Data t;
		while (!rs.IsEof())
		{
			rs.GetFieldValue(_T("FNO"), strField);
			int i = _ttoi(strField);
			t.nID = i;

			rs.GetFieldValue(_T("PS"), strField);
			CString str;
			str.Format(_T("%d楼(%s)"), i, strField);
			m_Floor.AddString(str);


			rs.GetFieldValue(_T("PicID"), strField);
			i = _ttoi(strField);
			t.nPic = i;


			rs.GetFieldValue(_T("Matrix"), strField);
			t.tbMatrix = strField;
			rs.GetFieldValue(_T("Location"), strField);
			t.tbLocation = strField;
			m_vFloor.push_back(t);

			rs.MoveNext();
		}
		rs.Close();
	}
	m_Floor.SetCurSel(0);
	GetFloorPosition();
}


// 获取本层的商品信息
void CShoppingGuideDlg::GetProByFNO(int Fno, CString& Discount)
{
	m_vPros.clear();

	CString strSQL;
	if (Discount.Compare(L"-1") == 0)
	{
		strSQL.Format(_T("select * from tbPro where FNO = %d"), Fno);
	}
	else
	{
		strSQL.Format(_T("select * from tbPro where FNO=%d AND PID IN (select PID from tbPrice where Pdiscount='%s') order by PID ASC"), Fno, Discount);
	}

	

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	if (rs.Open(strSQL))
	{
		
		if (0 == rs.GetRecordCount())
		{
			
			//重新查找
			m_Discount.SetCurSel(0);
			GetProByFNO(Fno, m_vDiscount[0]);
			CString str;
			str.Format(_T("无%s折扣商品"), Discount);
			AfxMessageBox(str);
			rs.Close();
			return;
		}


		CString strField;
		Data t;
		while (!rs.IsEof())
		{

		//	rs.GetFieldValue(_T("Pname"), strField);
		//	m_Pros.AddString(strField);


			rs.GetFieldValue(_T("PicID"), strField);
			int i = _ttoi(strField);
			t.nPic = i;
		
			rs.GetFieldValue(_T("PosID"), strField);
			 i = _ttoi(strField);
			t.nID = i;

			m_vPros.push_back(t);

			rs.MoveNext();
		}
		rs.Close();
	}
	//m_Pros.SetCurSel(0);
	InitPrice(Fno, Discount);
}

//楼层改变
void CShoppingGuideDlg::OnCbnSelchangeComboFloor()
{
	// TODO:  在此添加控件通知处理程序代码

	//设置楼层图

	m_Map.DrawWnd(m_vFloor[m_Floor.GetCurSel()].nPic);

	//设置楼层入口
	SetFloorEnter(m_vFloor[m_Floor.GetCurSel()].nID);

	//获取楼层位置信息
	GetFloorPosition();
	//获取本楼层折扣信息
	InitDiscount();

	//获取折扣商品
	GetProByFNO(m_vFloor[m_Floor.GetCurSel()].nID, m_vDiscount[m_Discount.GetCurSel()]);

	//设置商品图
	m_Pic.DrawWnd(m_vPros[m_Pros.GetCurSel()].nPic);
	


	

	m_Road.Clear();
	
}


void CShoppingGuideDlg::SetFloorEnter(int Fno)
{
	m_vEnter.clear();
	m_Enter.ResetContent();
	CString strSQL;
	strSQL.Format(_T("select * from tbEnter where FNO = %d"), Fno);

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	if (rs.Open(strSQL))
	{
		CString strField;
		while (!rs.IsEof())
		{

			rs.GetFieldValue(_T("PosNO"), strField);
			int i = _ttoi(strField);
			m_vEnter.push_back(i);

			rs.GetFieldValue(_T("PS"), strField);

			m_Enter.AddString(strField);

			rs.MoveNext();
		}
		rs.Close();
	}
	m_Enter.SetCurSel(0);
}

//商品名改变
void CShoppingGuideDlg::OnCbnSelchangeComboGoods()
{
	// TODO:  在此添加控件通知处理程序代码

	//设置商品图片
	m_Pic.DrawWnd(m_vPros[m_Pros.GetCurSel()].nPic);


}


// 获取楼层位置信息
void CShoppingGuideDlg::GetFloorPosition()
{
	m_vLocation.clear();

	CString strSQL;
	strSQL.Format(_T("select * from %s"), m_vFloor[m_Floor.GetCurSel()].tbLocation);

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	
	if (rs.Open(strSQL))
	{
		CString strField;
		LocatPosition t;
		int i;
		while (!rs.IsEof())
		{
		
			rs.GetFieldValue(_T("LID"), strField);
			i = _ttoi(strField);
			t.nID = i;

			rs.GetFieldValue(_T("Lx"), strField);
			i = _ttoi(strField);
			t.x = i;

			rs.GetFieldValue(_T("Ly"), strField);
			int i = _ttoi(strField);
			t.y = i;
			m_vLocation.push_back(t);//存入所有节点位置信息
			rs.MoveNext();
		}
		rs.Close();
	}

}


// 创建图;//创建图并存入节点信息
void CShoppingGuideDlg::InitRoad()
{
	
	m_Road.Clear();//如有信息则清空
	m_Road.CreateMap(m_vLocation.size());//初始化图的节点数


	

	CString strSQL;
	strSQL.Format(_T("select * from %s"), m_vFloor[m_Floor.GetCurSel()].tbMatrix);

	CADORecordset rs(&CShoppingGuideApp::staffDB);

	if (rs.Open(strSQL))
	{
		CString strField;
		int LID1, LID2, Edge;
		while (!rs.IsEof())
		{

			rs.GetFieldValue(_T("LID1"), strField);
			LID1 = _ttoi(strField);
			

			rs.GetFieldValue(_T("LID2"), strField);
			LID2 = _ttoi(strField);

			rs.GetFieldValue(_T("Edge"), strField);
			Edge = _ttoi(strField);
			m_Road.setEdge(LID1, LID2, Edge);
			m_Road.setEdge(LID2, LID1, Edge);
			rs.MoveNext();
		}
		rs.Close();
	}
}


void CShoppingGuideDlg::OnBnClickedButtonFeedback()
{
	CFeedBack m_FeedBack(this);
	if (IDOK == m_FeedBack.DoModal())
	{
		MessageBox(L"太感谢你的反馈啦",L"Thanks");
	}
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CShoppingGuideDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//设置光标
	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	SetCursor(hCursor);
	return TRUE;//CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


// 初始化折扣数据

void CShoppingGuideDlg::InitDiscount()
{
	m_Discount.ResetContent();
	m_vDiscount.clear();
	int FNO = m_vFloor[m_Floor.GetCurSel()].nID;
	//查询折扣表，并去重
	CString strSQL;
	strSQL.Format(_T("select Pdiscount from tbPrice where PID IN(select PID from tbPro where FNO =%d) group by Pdiscount order by Pdiscount ASC"), FNO);

	CADORecordset rs(&CShoppingGuideApp::staffDB);
	//默认值
	m_Discount.AddString(L"不选择");
	m_vDiscount.push_back(L"-1");

	if (rs.Open(strSQL))
	{
		CString strDiscount;
		CString strField;
		//特殊值
		m_Discount.AddString(L"原价");
		m_vDiscount.push_back(L"0");
		rs.MoveNext();
		while (!rs.IsEof())
		{

			rs.GetFieldValue(_T("Pdiscount"), strField);
			m_vDiscount.push_back(strField);
			strDiscount.Format(_T("%s折"), strField);
			m_Discount.AddString(strDiscount);
	
			rs.MoveNext();
		}
		rs.Close();
	}



	

	m_Discount.SetCurSel(0);

}

//改变折扣
void CShoppingGuideDlg::OnCbnSelchangeComboDiscount()
{
	// TODO:  在此添加控件通知处理程序代码

	//查询该折扣的所有商品
	GetProByFNO(m_vFloor[m_Floor.GetCurSel()].nID, m_vDiscount[m_Discount.GetCurSel()]);

}

//文本查找商品信息
int CShoppingGuideDlg::FindProbyName(int& nPic)
{
	CString strSQL;
	strSQL.Format(_T("select PicID,PosID from tbPro where Pname = '%s' AND FNO = %d"), m_Pname, m_vFloor[m_Floor.GetCurSel()]);

	CADORecordset rs(&CShoppingGuideApp::staffDB);

	if (rs.Open(strSQL))
	{
		if (rs.GetRecordCount() == 0)
		{
			rs.Close();
			return -1;
		}


		CString strField;
		rs.GetFieldValue(_T("PicID"), strField);
		nPic = _ttoi(strField);
	
		rs.GetFieldValue(_T("PosID"), strField);
	
	

		rs.Close();
		return _ttoi(strField);
		}

	return -1;
}


// 初始化当前商品价格
void CShoppingGuideDlg::InitPrice(int Fno, CString& Discount)
{

	m_Pros.ResetContent();
	CString strSQL;
	if (Discount.Compare(L"-1") == 0)
	{
		strSQL.Format(_T("select  tbPro.PID,tbPro.Pname,tbPrice.Price from tbPro,tbPrice where tbPro.PID=tbPrice.PID AND tbPro.FNO=%d order by PID ASC"), Fno);
	}
	else
	{
		strSQL.Format(_T("select  tbPro.PID,tbPro.Pname,tbPrice.Price from tbPro,tbPrice where tbPro.PID=tbPrice.PID AND tbPro.FNO=%d AND tbPrice.Pdiscount = '%s' order by PID ASC"), Fno, Discount);
	}

	CADORecordset rs(&CShoppingGuideApp::staffDB);

	if (rs.Open(strSQL))
	{
		CString strDiscount;
		CString strField;
	
		CString strPro;
		double price = 0;
		double discount = 0;
		while (!rs.IsEof())
		{
			
			rs.GetFieldValue(_T("Pname"), strField);
	
			rs.GetFieldValue(_T("Price"), strDiscount);
			//字符转浮点数
			price = _ttof(strDiscount);
			discount = _ttof(m_vDiscount[m_Discount.GetCurSel()]);
			if (0 == m_Discount.GetCurSel())
			{
				strPro.Format(_T("%s(原价:%s)"), strField, strDiscount);

			}
			else if (1 == m_Discount.GetCurSel())
			{
				discount = discount + 1;
				strPro.Format(_T("%s(原价:%s,当前价格:%.2f)"), strField, strDiscount, price*discount);
			}
			else
			{
				discount = discount*0.1;
				strPro.Format(_T("%s(原价:%s,当前价格:%.2f)"), strField, strDiscount, price*discount);
			}
		
		
			m_Pros.AddString(strPro);
			rs.MoveNext();
		}
		rs.Close();
	}
	//
	m_Pros.SetCurSel(0);


	//绘制商品LOGO
	m_Pic.DrawWnd(m_vPros[m_Pros.GetCurSel()].nPic);
}
