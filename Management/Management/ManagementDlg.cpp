
// ManagementDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Management.h"
#include "ManagementDlg.h"
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


// CManagementDlg 对话框



CManagementDlg::CManagementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagementDlg::IDD, pParent)
	, m_Uname(_T(""))
	, m_Upwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UNAME, m_Uname);
	DDX_Text(pDX, IDC_EDIT_UPWD, m_Upwd);
}

BEGIN_MESSAGE_MAP(CManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CManagementDlg::OnBnClickedButtonLogin)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CManagementDlg 消息处理程序

BOOL CManagementDlg::OnInitDialog()
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
	//初始化控件
	InitCtrls();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CManagementDlg::OnPaint()
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
HCURSOR CManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CManagementDlg::OnBnClickedButtonLogin()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMainFrame dlg(this);
	if (m_Uname.Compare(_T("admin")) == 0 && m_Upwd.Compare(_T("admin")) == 0)
	{
		if (!LinkDB())
		{
			MessageBox(_T("链接数据库失败！"), _T("系统提示"), MB_ICONSTOP);
		}
		else
		{
			KillTimer(1);
			
			dlg.DoModal();
		}
	}
	else
	{
		MessageBox(_T("登陆信息错误！"), _T("系统提示"), MB_ICONSTOP);
	}
}


BOOL CManagementDlg::LinkDB()
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
	strConnect.Format(_T("Provider=sqloledb;Data Source=%s;Initial Catalog=%s;User Id=%s;Password=%s;"), SVname, DBname, Account, PassWord);
	return CManagementApp::MarketDB.Open(strConnect);

}


void CManagementDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (CManagementApp::MarketDB.IsOpen())
	{
		CManagementApp::MarketDB.Close();
	}


	CDialogEx::OnClose();
}


void CManagementDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	static int _num = 20;
	if (_num == 0)
	{
		KillTimer(1);
		this->OnCancel();
	}
	CString time;
	time.Format(_T("XX商场后台管理系统   请在 %d 秒内登陆"), _num);
	SetWindowText(time);
	_num--;

	CDialogEx::OnTimer(nIDEvent);
}


void CManagementDlg::InitCtrls()
{
	SetTimer(1, 1000, NULL);
	SetWindowText(_T("XX商场后台管理系统"));
	GetDlgItem(IDC_EDIT_UNAME)->SetFocus();
}
