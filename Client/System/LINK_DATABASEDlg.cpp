
// LINK_DATABASEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LINK_DATABASE.h"
#include "LINK_DATABASEDlg.h"
#include "afxdialogex.h"
#include "AdoSql.h"
#include "Redist_Dlog.h"
#include"Login_Dlog.h"
#include<afxsock.h>
#include "ClientSocket.h"
#include <regex>
#include <string>
#include <atlconv.h>//宽字节转换
#include <cstdlib>
#import"msxml3.dll"
using namespace MSXML2;
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CLINK_DATABASEDlg *pLogDlg;
extern CClientSocket *IndexSocket;
CString cstrGetAccount;
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


// CLINK_DATABASEDlg 对话框



CLINK_DATABASEDlg::CLINK_DATABASEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LINK_DATABASE_DIALOG, pParent)
	, nMyRadioButton(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SocketIp = _T("127.0.0.1");
	pLogDlg = this;
	cstrGetAccount =_T("");

	//  nMyRadioButton = 0;
}

void CLINK_DATABASEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, Text);
	DDX_Control(pDX, IDC_EDIT1, Pwd);
	DDX_Control(pDX, IDC_RADIO4, nRadioButton);
	//  DDX_Radio(pDX, IDC_RADIO4, kkkk);
	DDX_Radio(pDX, IDC_RADIO4, nMyRadioButton);
}

BEGIN_MESSAGE_MAP(CLINK_DATABASEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLINK_DATABASEDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CLINK_DATABASEDlg::OnEnChangeEdit2)
//	ON_BN_CLICKED(IDC_BUTTON2, &CLINK_DATABASEDlg::OnBnClickedButton2)
	//ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CLINK_DATABASEDlg::OnNMClickSyslink1)
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK2, &CLINK_DATABASEDlg::OnNMClickSyslink2)
	ON_BN_CLICKED(IDC_RADIO1, &CLINK_DATABASEDlg::OnBnClickedRadio1)
	ON_EN_CHANGE(IDC_EDIT1, &CLINK_DATABASEDlg::OnEnChangeEdit1)
//	ON_EN_KILLFOCUS(IDC_EDIT1, &CLINK_DATABASEDlg::OnKillfocusEdit1)
ON_EN_KILLFOCUS(IDC_EDIT2, &CLINK_DATABASEDlg::OnKillfocusEdit2)
//ON_STN_CLICKED(IDC_STAT1, &CLINK_DATABASEDlg::OnClickedStat1)
ON_BN_CLICKED(IDC_CHECK2, &CLINK_DATABASEDlg::OnClickedCheck2)
ON_WM_CTLCOLOR()
ON_EN_SETFOCUS(IDC_EDIT2, &CLINK_DATABASEDlg::OnSetfocusEdit2)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_RADIO4, &CLINK_DATABASEDlg::OnBnClickedRadio4)
ON_BN_CLICKED(IDC_RADIO5, &CLINK_DATABASEDlg::OnBnClickedRadio5)
ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CLINK_DATABASEDlg 消息处理程序

BOOL CLINK_DATABASEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();	


	//mysql.OnInitADOConn();//连接到数据库
	AfxSocketInit();//Csocket初始化
	if (IndexSocketClient = new CClientSocket())
	{
		if (IndexSocketClient->Create())
		{
		
		}
		else
		{
			MessageBox(_T("初始化失败，请重启动程序1"), _T("warnig"), MB_OK);
			delete IndexSocketClient;
		}
	}
	else
	{
		MessageBox(_T("初始化失败，请重启动程序"), _T("warnig"), MB_OK);
		delete IndexSocketClient;
	}
	if (IndexSocketClient->Connect(SocketIp, 6000))
	{
	}
	else
	{
		MessageBox(_T("服务器连接失败，请开启服务器"), _T("Warnig"), MB_OK);
	}
	Text.SetWindowTextW(_T("手机号/邮箱"));
	
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
	/*HBITMAP hBitmap;
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP1));
	((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap);*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLINK_DATABASEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLINK_DATABASEDlg::OnPaint()
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


		//设置背景图片
		/*CPaintDC dc(this);
		CRect   rect;
		GetClientRect(&rect);
		CDC dcmap;
		dcmap.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP4);
		BITMAP  m_bitmap;
		bmpBackground.GetBitmap(&m_bitmap);
		CBitmap *pbmpOld = dcmap.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), 
		&dcmap, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);*/
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLINK_DATABASEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLINK_DATABASEDlg::OnBnClickedButton1()
{
	
		CString  Account,strpassword;
		_variant_t RecordsAffected;
		_bstr_t Select;
		CString sctrAccount;
		sctrAccount = cstrGetAccount;
		Pwd.GetWindowText(strpassword);
		Text.GetWindowTextW(Account);
		if ((_T("手机号/邮箱")==Account)|| (_T("") == Account))
		{
			CString message;
			Text.SetWindowTextW(_T("账号不能为空"));
			return;
		}
		if (_T("") == strpassword)
		{
			AfxMessageBox(_T("请输入密码"));
		}
		else if (_T("")!=strpassword)
		{
			USES_CONVERSION;
			string Transprants = W2CA((LPCWSTR)(strpassword));
			regex pattern("^[a-zA-Z]\\w{5,17}");
			if (regex_match(Transprants, pattern))
			{
				if (0 == nMyRadioButton)//手机号登录
				{
					char *p;
					_bstr_t  MyXML = _T("<?xml version =\"1.0\" encoding=\"UTF-8\"?>\n<Root><Node><Node1><ID>2</ID><Account>") + sctrAccount + ("</Account><Pwd>") + strpassword + ("</Pwd></Node1></Node></Root>");
					p = (LPSTR)(LPCTSTR)MyXML;//Cstring转Char*
					IndexSocket->Send(p, 1024, 0);
					return;
				}
				else if(1 == nMyRadioButton)//邮箱登录
				{
					char *p;
					_bstr_t  MyXML = _T("<?xml version =\"1.0\" encoding=\"UTF-8\"?>\n<Root><Node><Node1><ID>3</ID><Account>") + sctrAccount + ("</Account><Pwd>") + strpassword + ("</Pwd></Node1></Node></Root>");
					p = (LPSTR)(LPCTSTR)MyXML;//Cstring转Char*
					IndexSocket->Send(p, 1024, 0);
					return;
				}
			}
			else
			{
				AfxMessageBox(_T("密码格式输入错误"));
			}
			
		}
}




void CLINK_DATABASEDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//	LPWSTR lp= Text.GetWindowTextW;
	// TODO:  在此添加控件通知处理程序代码
	return;
}


//void CLINK_DATABASEDlg::OnBnClickedButton2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CRedist_Dlog My_Dog;
//	My_Dog.DoModal();
//}


void CLINK_DATABASEDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
}


void CLINK_DATABASEDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnMouseMove(nFlags, point);
}


void CLINK_DATABASEDlg::OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	
	*pResult = 0;
}


void CLINK_DATABASEDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CLINK_DATABASEDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
}


//void CLINK_DATABASEDlg::OnKillfocusEdit1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}


void CLINK_DATABASEDlg::OnKillfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strname, strpassword;
	_variant_t RecordsAffected;
	_bstr_t Select;
	Text.GetWindowText(strname);
	if (_T("") != strname)
	{
		regex pattern("^[1]+[0-9]{10}$");
		regex pattern1("([0-9A-Za-z]+[0-9A-Za-z\\-\\_\\.]+)@([0-9a-zA-Z]+\\.[a-zA-Z]{2,3})");
		USES_CONVERSION;
		string Transprants = W2CA((LPCWSTR)(strname));
		if (0== nMyRadioButton)
		{
			if (regex_match(Transprants, pattern))
			{
				char *p;
				CString MyXML = _T("<?xml version =\"1.0\" encoding=\"UTF-8\"?>\n<Root><Node><Node1><ID>4</ID><Account>") + strname + _T("</Account></Node1></Node></Root>");
				p = (LPSTR)(LPCTSTR)MyXML;//Cstring转Char*
				IndexSocket->Send(p, 255, 0);
				return;
			}
			else
			{
				Text.SetSel(0, -1);
				Text.Clear();
				Text.SetWindowTextW(_T("手机账号格式错误"));
				return;
			}
		}
		if (1 == nMyRadioButton)
		{
			if (regex_match(Transprants, pattern1))
			{
				char *p;
				CString MyXML = _T("<?xml version =\"1.0\" encoding=\"UTF-8\"?>\n<Root><Node><Node1><ID>5</ID><Account>") + strname + _T("</Account></Node1></Node></Root>");
				p = (LPSTR)(LPCTSTR)MyXML;//Cstring转Char*
				IndexSocket->Send(p, 255, 0);
				return;
			}
			else
			{
				Text.SetSel(0, -1);
				Text.Clear();
				Text.SetWindowTextW(_T("邮箱账号格式错误"));
				return;
			}
		}
	}

}


//void CLINK_DATABASEDlg::OnClickedStat1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	//用户注册
//	CRedist_Dlog  m_dlg;
//	m_dlg.DoModal();
//	AfxMessageBox(_T(""));
//}


void CLINK_DATABASEDlg::OnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	CRedist_Dlog My_Dlog;
	My_Dlog.DoModal();
}


HBRUSH CLINK_DATABASEDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	CString GetAccount;
	Text.GetWindowTextW(GetAccount);
	 if ((_T("账号不存在") == GetAccount)||(_T("账号不能为空") == GetAccount)|| _T("手机账号格式错误") == GetAccount|| _T("邮箱账号格式错误") == GetAccount)
	{
		pDC->SetTextColor(RGB(255,0,0));
	}
	return hbr;
}


void CLINK_DATABASEDlg::OnSetfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	Text.SetSel(0,-1);
	Text.Clear();
	Pwd.SetSel(0,-1);
	Pwd.Clear();
}


void CLINK_DATABASEDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	IndexSocketClient->Close();
	// TODO: 在此处添加消息处理程序代码
}


void CLINK_DATABASEDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	nMyRadioButton = 0;
}


void CLINK_DATABASEDlg::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	nMyRadioButton = 1;
}


void CLINK_DATABASEDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialogEx::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
}


//void CLINK_DATABASEDlg::OnOK()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	//CDialogEx::OnClose();
//	CDialogEx::OnOK();
//}
