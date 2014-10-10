// SmithDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Smith.h"
#include "SmithDlg.h"
#include "OpenGL.h"
#include "Data.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define pi 3.1415926535898 

double num1,num2,num3,num4,num5,num6;


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();


// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmithDlg dialog

CSmithDlg::CSmithDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmithDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmithDlg)
	m_num1 = 50.0;
	m_num2 = 30.0;
	m_num3 = 40.0;
	m_num4 = 0.0;
	m_num5 = 0.0;
	m_num6 = 0.0;
	m_num7 = 0.0;
	m_num8 = 0.0;
	m_num9 = 0.0;
	m_num10 = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    

	// 构造一个新的COpenGL对象
	m_pDisplay = new COpenGL;

}

void CSmithDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmithDlg)
	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT3, m_num3);
	DDX_Text(pDX, IDC_EDIT4, m_num4);
	DDX_Text(pDX, IDC_EDIT5, m_num5);
	DDX_Text(pDX, IDC_EDIT6, m_num6);
	DDX_Text(pDX, IDC_EDIT7, m_num7);
	DDX_Text(pDX, IDC_EDIT8, m_num8);
	DDX_Text(pDX, IDC_EDIT9, m_num9);
	DDX_Text(pDX, IDC_EDIT10, m_num10);
	//}}AFX_DATA_MAP
	
}

BEGIN_MESSAGE_MAP(CSmithDlg, CDialog)
	//{{AFX_MSG_MAP(CSmithDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17)
	ON_BN_CLICKED(IDC_BUTTON18, OnButton18)
	ON_BN_CLICKED(IDC_BUTTON19, OnButton19)
	ON_BN_CLICKED(IDC_BUTTON20, OnButton20)
	ON_BN_CLICKED(IDC_BUTTON23, OnButton23)
	ON_BN_CLICKED(IDC_BUTTON22, OnButton22)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmithDlg message handlers

BOOL CSmithDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// 定义OpenGL绘图窗口的矩形大小
	CRect rect(7, 7, 608, 608);
	

	// 创建COpenGL类对象
	m_pDisplay->Create( NULL,   //缺省的窗口/////////////////////////////////////////////创建窗口，然后自动调用OpenGL类的OnPain函数
						NULL,   //无窗口名称
						WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE,
						        // 定义窗口风格
						rect,   // 窗口的大小
						this,   // 指定当前对话框为其父窗口指针
						0);     
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSmithDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSmithDlg::OnPaint() 
{
	
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSmithDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


// 添加CMyDlgOpenGlg类的虚构函数
CSmithDlg::~CSmithDlg()
{
	if(m_pDisplay)
	{
		delete m_pDisplay;// 释放m_pDisplay指针
	}

}
/////////////////////////////////////////////////////////////////////////////

void CSmithDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	///////////////////////////////////////////////显示等反射系数圆
	m_pDisplay->reflect_show=1;
	
}

void CSmithDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->reflect_show=0;
	
}

void CSmithDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->r_show=1;	
}

void CSmithDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->r_show=0;
	
}

void CSmithDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->k_show=1;
	
}

void CSmithDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->k_show=0;
	
}

void CSmithDlg::OnButton8() //////////////////////////////////点击，进行计算
{
	// TODO: Add your control notification handler code here
	m_pDisplay->tor_normalized_show=1.0f;
	m_pDisplay->pot_normalized_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->tor_normalized_show=0.0f;
	m_pDisplay->r_normalized_show=0.0f;
	m_pDisplay->x_normalized_show=0.0f;
	m_pDisplay->fi_normalized_show=0.0f;
	m_pDisplay->pot_normalized_show=0.0f;
}

void CSmithDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->r_normalized_show=1.0f;
	m_pDisplay->pot_normalized_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton12() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->x_normalized_show=1.0f;
	m_pDisplay->pot_normalized_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton13() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->fi_normalized_show=1.0f;
	m_pDisplay->pot_normalized_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	UpdateData(TRUE);
	
}
void CSmithDlg::OnButton14() 
{
	// TODO: Add your control notification handler code here
	



	m_num4=m_pDisplay->Fi_dis;
	if(num3>=0)
	{
		m_num5=(m_pDisplay->Fi)*180/pi;
	}
	else
		m_num5=-(m_pDisplay->Fi)*180/pi;
	if(m_pDisplay->Fi_dis!=1)
	{
		m_num6=(1+m_pDisplay->Fi_dis)/(1-m_pDisplay->Fi_dis);
	}
	else
		m_num6=99999999999;


	/////////////////////////////////////
	double num7=0.5*((m_pDisplay->theta_y)-(m_pDisplay->theta_c))/(2*pi);////C点对应d1
	double num8=0.5*(m_pDisplay->theta_f)/(2*pi);                         ////F点对应L1
	double num9;////D点对应d2
	double num10=0.5*(m_pDisplay->theta_ff)/(2*pi);///////////////////F'点对应L2
	if((m_pDisplay->y_x)>=(m_pDisplay->c_x))
	{
		num9=0.5*((m_pDisplay->theta_d)-(m_pDisplay->theta_y))/(2*pi);////D点对应d2
	}
	else
	{
		num9=0.5-0.5*((m_pDisplay->theta_d)-(m_pDisplay->theta_y))/(2*pi);////D点对应d2
	}
	if(num7>=0)
	{
		m_num7=num7;
	}
	else
	{
		m_num7=-num7;
	}
	if(num9>=0)
	{
		m_num9=num9;
	}
	else
	{
		m_num9=-num9;
	}
	m_num10=num10;
	m_num8=num8;
	UpdateData(FALSE);
}

void CSmithDlg::OnButton21() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->y_normalized_show=1.0f;
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton11() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->tor2_normalized_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton15() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->g_unit_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton16() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->c_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	if(m_pDisplay->color_cc==0.0f)
	{
		m_pDisplay->color_cc=1.0f;
	}
	else
	{
		m_pDisplay->color_cc=0.0f;
	}

	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton17() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->d_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	if(m_pDisplay->color_dd==0.0f)
	{
		m_pDisplay->color_dd=1.0f;
	}
	else
	{
		m_pDisplay->color_dd=0.0f;
	}
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton18() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->f_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	if(m_pDisplay->color_ff==0.0f)
	{
		m_pDisplay->color_ff=1.0f;
	}
	else
	{
		m_pDisplay->color_ff=0.0f;
	}
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton19() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->ff_show=1.0f;
	UpdateData(TRUE);
	num1=m_num1;
	num2=m_num2;
	num3=m_num3;
	if(m_pDisplay->color_fff==0.0f)
	{
		m_pDisplay->color_fff=1.0f;
	}
	else
	{
		m_pDisplay->color_fff=0.0f;
	}
	UpdateData(TRUE);
	
}

void CSmithDlg::OnButton20() 
{
	// TODO: Add your control notification handler code here
	m_pDisplay->ff_show=0.0f;
	m_pDisplay->f_show=0.0f;
	m_pDisplay->d_show=0.0f;
	m_pDisplay->c_show=0.0f;
	m_pDisplay->g_unit_show=0.0f;
	m_pDisplay->tor2_normalized_show=0.0f;
	m_pDisplay->y_normalized_show=0.0f;

	m_pDisplay->color_cc=1.0f;
	m_pDisplay->color_dd=1.0f;
	m_pDisplay->color_ff=1.0f;
	m_pDisplay->color_fff=1.0f;
	
}

void CSmithDlg::OnButton23() 
{
	// TODO: Add your control notification handler code here
	if(m_pDisplay->x_show==1.0f)
	{
		m_pDisplay->x_show=0.0f;
	}
	else
		m_pDisplay->x_show=1.0f;

	
}

void CSmithDlg::OnButton22() 
{
	// TODO: Add your control notification handler code here
	if(m_pDisplay->y_show==1.0f)
	{
		m_pDisplay->y_show=0.0f;
	}
	else
		m_pDisplay->y_show=1.0f;
	
}

void CSmithDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
	
}
