
// DemoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "afxdialogex.h"
#include "Subway.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemoDlg 对话框



CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cb1);
	DDX_Control(pDX, IDC_COMBO3, m_cb2);
	DDX_Control(pDX, IDC_COMBO2, m_cb3);
	DDX_Control(pDX, IDC_COMBO4, m_cb4);
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDemoDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDemoDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CDemoDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDemoDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT2, &CDemoDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CDemoDlg::OnEnChangeEdit3)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDemoDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CDemoDlg::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CDemoDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDCANCEL, &CDemoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDemoDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT4, &CDemoDlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CDemoDlg 消息处理程序

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	// TODO: 在此添加额外的初始化代码



	//加载数据 
	yanshi.getstationNum();
	yanshi.getSubwayLineNumber();
	yanshi.creatMap();
	//初始化COMBOBOX
	setCombobox1();
	setCombobox3();

	CString Ctxt;
	string txt;
	txt = "SUMMARY:\r\n1.动态开辟内存，能在信息文本weight.txt中添加任意站点、线路信息,方便了信息的增改。\r\n2.操作简便，设计时使用COMBO BOX控件，用户仅使用鼠标就可以完成操作。\r\n3.能检索全北京所有站点（特殊地铁站点除外）。\r\n感谢您的使用和支持 -----通信1604-邓泽一";
	Ctxt = txt.c_str();
	GetDlgItem(IDC_EDIT4)->SetWindowText(Ctxt);


	txt = "使用说明:\r\n\r\n1.依次在下拉菜单中选择起点站、终点站的地铁线和地铁站。\r\n\r\n2.点击出发按钮。\r\n\r\n3.能检索全北京所有站点（特殊地铁站点除外）。\r\n\r\n4.若需添加、删改站点信息,请在weight.txt中参照格式修改即可并重启程序。";
	Ctxt = txt.c_str();
	GetDlgItem(IDC_EDIT5)->SetWindowText(Ctxt);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoDlg::OnCbnSelchangeCombo1()
{
	setCombobox2();
	// TODO: 在此添加控件通知处理程序代码
}


void CDemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString begin;
	CString end;
	string beginName;
	string endName;
	string path;
	//UpdateData(TRUE);                       //这个函数的使用请参考数据交换UpdateData，那篇文章  
	m_cb2.GetLBText(m_cb2.GetCurSel(), begin);
	beginName = CT2A(begin);
	m_cb4.GetLBText(m_cb4.GetCurSel(), end);
	endName = CT2A(end);
	yanshi.origin = beginName;
	yanshi.destine = endName;
	yanshi.getPoint();
	yanshi.InitializeDis();
	yanshi.caculate();
	path=yanshi.printPath();

	CString Cpath;
	Cpath = path.c_str();
	GetDlgItem(IDC_EDIT1)->SetWindowText(Cpath);

	CString Cdistance;
	string distance;
	distance = yanshi.getDistance();
	Cdistance = distance.c_str();
	GetDlgItem(IDC_EDIT2)->SetWindowText(Cdistance);
	//MessageBox(Cpath);

	CString Cprice;
	string price;
	price = yanshi.getPrice();
	Cprice = price.c_str();
	GetDlgItem(IDC_EDIT3)->SetWindowText(Cprice);

}


void CDemoDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDemoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString begin;
	GetDlgItem(IDC_EDIT1)->GetWindowText(begin);
	string beginName;
	beginName = CT2A(begin);
	 
	CString end;
	GetDlgItem(IDC_EDIT2)->GetWindowText(end);
	string endName;
	endName = CT2A(end);

	yanshi.origin = beginName;
	yanshi.destine = endName;
	yanshi.getPoint();
	yanshi.InitializeDis();
	yanshi.caculate();
	yanshi.printPath();
	
	CString Cpath;
	Cpath = (yanshi.dis[yanshi.destineNumber].path).c_str();
	MessageBox(Cpath);

}


void CDemoDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDemoDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CDemoDlg::setCombobox1()
{
	//COMBO BOX初始化
	//设置出发地铁线
	m_cb1.AddString(_T("一号线"));   //添加字符串 
	m_cb1.AddString(_T("二号线"));
	m_cb1.AddString(_T("五号线"));
	m_cb1.AddString(_T("六号线"));
	m_cb1.AddString(_T("七号线"));
	m_cb1.AddString(_T("八号线"));
	m_cb1.AddString(_T("九号线"));
	m_cb1.AddString(_T("十号线"));
	m_cb1.AddString(_T("十三号线"));
	m_cb1.AddString(_T("十四号线"));
	m_cb1.AddString(_T("十五号线"));
	m_cb1.AddString(_T("房山线"));
	m_cb1.AddString(_T("亦庄线"));
	m_cb1.AddString(_T("昌平线"));
	m_cb1.AddString(_T("八通线"));


}

void CDemoDlg::setCombobox2()
{
	//设置出发站点
	CString name;
	CString strCBText;
	string temp;
	//读取所选项
	m_cb2.ResetContent();
	m_cb1.GetLBText(m_cb1.GetCurSel(), strCBText);
	temp = CT2A(strCBText);
	for (int i = 0; i < yanshi.stationNum; i++)
	{
		for (int j = 0; j < yanshi.sta[i].subwayLineNumber; j++)
		{
			if (temp==yanshi.sta[i].subwayLine[j])
			{
				name = (yanshi.sta[i].name).c_str();
				m_cb2.AddString(name);
			}
		}
	}
	
}

void CDemoDlg::setCombobox3()
{
	//设置到达地铁站
	m_cb3.AddString(_T("一号线"));   //添加字符串 
	m_cb3.AddString(_T("二号线"));
	m_cb3.AddString(_T("五号线"));
	m_cb3.AddString(_T("六号线"));
	m_cb3.AddString(_T("七号线"));
	m_cb3.AddString(_T("八号线"));
	m_cb3.AddString(_T("九号线"));
	m_cb3.AddString(_T("十号线"));
	m_cb3.AddString(_T("十三号线"));
	m_cb3.AddString(_T("十四号线"));
	m_cb3.AddString(_T("十五号线"));
	m_cb3.AddString(_T("房山线"));
	m_cb3.AddString(_T("亦庄线"));
	m_cb3.AddString(_T("昌平线"));
	m_cb3.AddString(_T("八通线"));
	//m_cb3.SetCurSel(0);   //默认选择第一个  
}

void CDemoDlg::setCombobox4()
{
	CString name;
	CString strCBText;
	string temp;
	//设置到达地铁站
	m_cb4.ResetContent();
	m_cb3.GetLBText(m_cb3.GetCurSel(), strCBText);
	temp = CT2A(strCBText);
	for (int i = 0; i < yanshi.stationNum; i++)
	{
		for (int j = 0; j < yanshi.sta[i].subwayLineNumber; j++)
		{
			if (temp == yanshi.sta[i].subwayLine[j])
			{
				name = (yanshi.sta[i].name).c_str();
				m_cb4.AddString(name);
			}
		}
	}
}


void CDemoDlg::OnCbnSelchangeCombo2()
{
	setCombobox4();
	// TODO: 在此添加控件通知处理程序代码
}


void CDemoDlg::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDemoDlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDemoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CDemoDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
