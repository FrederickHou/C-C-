// Redist_Dlog.cpp : 实现文件
//

#include "stdafx.h"
#include "LINK_DATABASE.h"
#include "Redist_Dlog.h"
#include "afxdialogex.h"
#include "ClientSocket.h"
#include "AdoSql.h"
#include <atlconv.h>//宽字节转换
#include <cstdlib>
#include <string>
#include <regex>//Regular Expression
#include<iostream>
#include <stdlib.h>
using namespace std;
extern CClientSocket *pIndexRedistSocket;
extern AdoSql *MysqlRegist;
CRedist_Dlog *pRedistDlog;
IMPLEMENT_DYNAMIC(CRedist_Dlog, CDialogEx)
CRedist_Dlog::CRedist_Dlog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_nSelection(0)
{
	killfocus = 0;
	pRedistDlog = this;
}

CRedist_Dlog::~CRedist_Dlog()
{
}

void CRedist_Dlog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT5, Regist);
	//  DDX_Control(pDX, IDC_EDIT5, Regist);
	DDX_Control(pDX, IDC_EDIT4, Reg_Pwd);
	DDX_Control(pDX, IDC_EDIT3, Reg_Correct);
	DDX_Control(pDX, IDC_EDIT5, Reg_Log);
	DDX_Control(pDX, IDC_RADIO1, m_conRadioPhonBtn);
	DDX_Radio(pDX, IDC_RADIO1, m_nSelection);
}


BEGIN_MESSAGE_MAP(CRedist_Dlog, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO2, &CRedist_Dlog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CRedist_Dlog::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT5, &CRedist_Dlog::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_RADIO1, &CRedist_Dlog::OnBnClickedRadio1)
//	ON_EN_KILLFOCUS(IDC_EDIT5, &CRedist_Dlog::OnKillfocusEdit5)
//	ON_EN_KILLFOCUS(IDC_EDIT4, &CRedist_Dlog::OnKillfocusEdit4)
//	ON_WM_KILLFOCUS()
//	ON_EN_KILLFOCUS(IDC_EDIT5, &CRedist_Dlog::OnKillfocusEdit5)
	ON_EN_CHANGE(IDC_EDIT4, &CRedist_Dlog::OnChangeEdit4)
//	ON_EN_KILLFOCUS(IDC_EDIT4, &CRedist_Dlog::OnKillfocusEdit4)
//ON_EN_KILLFOCUS(IDC_EDIT4, &CRedist_Dlog::OnKillfocusEdit4)
//ON_EN_KILLFOCUS(IDC_EDIT5, &CRedist_Dlog::OnKillfocusEdit5)
ON_EN_KILLFOCUS(IDC_EDIT4, &CRedist_Dlog::OnKillfocusEdit4)
//ON_EN_KILLFOCUS(IDC_EDIT3, &CRedist_Dlog::OnKillfocusEdit3)
ON_EN_SETFOCUS(IDC_EDIT4, &CRedist_Dlog::OnEnSetfocusEdit4)
ON_WM_KILLFOCUS()
ON_EN_SETFOCUS(IDC_EDIT5, &CRedist_Dlog::OnSetfocusEdit5)
ON_EN_KILLFOCUS(IDC_EDIT5, &CRedist_Dlog::OnKillfocusEdit5)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CRedist_Dlog 消息处理程序


void CRedist_Dlog::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSelection = 1;
	
}



void CRedist_Dlog::OnBnClickedButton1()
{
	if (0==m_nSelection)
	{
		m_nSelection = 1;
	}
	else if(1==m_nSelection)
	{
		m_nSelection = -1;
	}
		try
		{
			
			CString Relog, RegPwd, RegCorrect;
			Reg_Log.GetWindowTextW(Relog);
			Reg_Pwd.GetWindowTextW(RegPwd);
			Reg_Correct.GetWindowTextW(RegCorrect);
			
			if (_T("")==Relog)
			{
				CString Remder;
				Remder = _T("账号不能为空");
				Reg_Pwd.SetWindowTextW(Remder);
				Reg_Pwd.SetSel(0, -1);
				Reg_Pwd.Clear();
				Reg_Correct.SetSel(0,-1);
				Reg_Correct.Clear();
				return;
			}
			
			if ((_T("") == RegPwd))
			{
				CString Remder;
				Remder = _T("请输入密码");
				AfxMessageBox(Remder);
				
				return;
			}
			if ((_T("") == RegCorrect))
			{
				CString Remder;
				Remder = _T("请输入确认密码");
				AfxMessageBox(Remder);
				return;
			}

			if (RegPwd != RegCorrect)
			{
				CString Remder;
				Remder = _T("密码不一致");
				AfxMessageBox(Remder);
				return;
			}
				
			if (1 == m_nSelection)//手机号登录
			{
				char *p;
				_bstr_t  MyXML = _T("<?xml version =\"1.0\" encoding=\"UTF-8\"?>\n<Root><Node><Node1><ID>1</ID><Account>") + Relog + ("</Account><Pwd>") + RegPwd + ("</Pwd></Node1></Node></Root>");
				p = (LPSTR)(LPCTSTR)MyXML;//Cstring转Char*
				pIndexRedistSocket->Send(p, 1024, 0);
				return;
			}
			else if (-1== m_nSelection)//邮箱登录
			{
				char *p;
				_bstr_t  MyXML = _T("<?xml version =\"1.0\" encoding=\"UTF-8\"?>\n<Root><Node><Node1><ID>-1</ID><Account>") + Relog + ("</Account><Pwd>") + RegPwd + ("</Pwd></Node1></Node></Root>");
				p = (LPSTR)(LPCTSTR)MyXML;//Cstring转Char*
				pIndexRedistSocket->Send(p, 1024, 0);
				return;
			}

			}
		
		catch (_com_error e)
		{
			CString errormessage;
			errormessage.Format(_T("错误！"));
			AfxMessageBox(errormessage);
			
			return;
		}
	
}



void CRedist_Dlog::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CRedist_Dlog::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSelection = 0;
}


BOOL CRedist_Dlog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	//mysql.OnInitADOConn();//连接到数据库
	// TODO:  在此添加额外的初始化
	//MysqlRegist.OnInitADOConn();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


/*void CRedist_Dlog::OnKillfocusEdit5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strGetEmile;
	CString Remder;
	Reg_Log.GetWindowTextW(strGetEmile);
	regex pattern("([0-9A-Za-z]+[0-9A-Za-z\\-\\_\\.]+)@([0-9a-zA-Z]+\\.[a-zA-Z]{2,3})");
	USES_CONVERSION;
	string Transprants = W2CA((LPCWSTR)(strGetEmile));
	if (regex_match(Transprants, pattern))
	{
		
		Remder = _T("合法的邮箱格式");
		AfxMessageBox(Remder);
		return;
	}
	else
	{
		
		Remder = _T("不合法的邮箱格式");
		AfxMessageBox(Remder);
		Reg_Log.SetSel(0, -1);
		Reg_Log.Clear();
		return;
	}
}*/


/*void CRedist_Dlog::OnKillfocusEdit4()
{
	// TODO: 在此添加控件通知处理程序代码
	
}*/


//void CRedist_Dlog::OnKillFocus(CWnd* pNewWnd)
//{
//	
//	if (pNewWnd->GetDlgCtrlID() == IDC_EDIT5)
//	{
//		AfxMessageBox(_T("邮箱失去了焦点。"));
//	}
//	else if (pNewWnd->GetDlgCtrlID() == IDC_EDIT4)
//	{
//		AfxMessageBox(_T("密码失去了焦点。"));
//	}
//	CDialogEx::OnKillFocus(pNewWnd);
//
//}


	// TODO: 在此处添加消息处理程序代码



//void CRedist_Dlog::OnKillfocusEdit5()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//}


void CRedist_Dlog::OnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


//void CRedist_Dlog::OnKillfocusEdit4()
//{
//	AfxMessageBox(_T("密码您好。"));
//	// TODO: 在此添加控件通知处理程序代码
//}


//void CRedist_Dlog::OnKillfocusEdit4()
//{
//	AfxMessageBox(_T("密码您好。"));
//	// TODO: 在此添加控件通知处理程序代码
//}


//void CRedist_Dlog::OnKillfocusEdit5()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CRedist_Dlog::OnKillfocusEdit4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (2 == killfocus)
	{

		CString strGetEmile;
		CString Remder;
		Reg_Pwd.GetWindowTextW(strGetEmile);
		if (_T("") != strGetEmile)
		{
			
			regex pattern("^[a-zA-Z]\\w{5,17}");
			USES_CONVERSION;
			string Transprants = W2CA((LPCWSTR)(strGetEmile));
			if (regex_match(Transprants, pattern))
			{


				return;
			}
			else
			{
				Reg_Pwd.SetSel(0, -1);
				Reg_Pwd.Clear();
				//Reg_Pwd.SetWindowTextW(_T("密码格式错误"));
				AfxMessageBox(_T("密码格式错误\r\n正确格式为：\r\n以字母开头，长度在6~18之间，\r\n只能包含字符、数字和下划线。"));
				//GetDlgItem(IDC_EDIT4)->SetFocus();
				return;
			}
		}
	}
	/*if (0==killfocus)
	{
		Reg_Pwd.SetSel(0, -1);
		Reg_Pwd.Clear();
		AfxMessageBox(_T("请先输入账号"));
	}
	if (1 == killfocus)
	{
		CString strGetEmile;
		Reg_Pwd.GetWindowTextW(strGetEmile);
		if (_T("") != strGetEmile)
		{
			return;
		}
		else 
		{
			AfxMessageBox(_T("请先输入账号"));
		}
	}*/
//	GetDlgItem(IDC_EDIT5)->SetFocus();
	
}


//void CRedist_Dlog::OnKillfocusEdit3()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	AfxMessageBox(_T("确认密码您好。"));
//	CDialogEx::OnKillFocus(this);
//}


void CRedist_Dlog::OnEnSetfocusEdit4()
{
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox(_T("获得焦点。"));
}


void CRedist_Dlog::OnKillFocus(CWnd* pNewWnd)
{
	CDialogEx::OnKillFocus(pNewWnd);
	
	// TODO: 在此处添加消息处理程序代码
}


void CRedist_Dlog::OnSetfocusEdit5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cstrGetText;
	Reg_Log.GetWindowTextW(cstrGetText);
	if ((_T("手机格式错误") == cstrGetText) || (_T("邮箱格式错误") == cstrGetText)|| (_T("该账户已存在") == cstrGetText))
	{
		Reg_Log.SetSel(0, -1);
		Reg_Log.Clear();
	}
}


void CRedist_Dlog::OnKillfocusEdit5()
{

		if (1 == m_nSelection)
		{
			CString strGetEmile;
			CString Remder;
			Reg_Log.GetWindowTextW(strGetEmile);
			if ((_T("") != strGetEmile)&&(_T("邮箱格式错误") != strGetEmile))
			{
				regex pattern("([0-9A-Za-z]+[0-9A-Za-z\\-\\_\\.]+)@([0-9a-zA-Z]+\\.[a-zA-Z]{2,3})");
				USES_CONVERSION;
				string Transprants = W2CA((LPCWSTR)(strGetEmile));
				if (regex_match(Transprants, pattern))
				{
					killfocus = 2;
					return;
				}
				else
				{
					Reg_Log.SetSel(0, -1);
					Reg_Log.Clear();
					Reg_Log.SetWindowTextW(_T("邮箱格式错误"));
					killfocus = 1;
					GetDlgItem(IDC_EDIT4)->SetFocus();
					return;
				}
	
			}
		}
		if (0==m_nSelection)
		{
			CString strGetEmile;
			CString Remder;
			Reg_Log.GetWindowTextW(strGetEmile);
			if ((_T("") != strGetEmile) && (_T("手机格式错误") != strGetEmile))
			{
				regex pattern("^[1]+[0-9]{10}$");
				USES_CONVERSION;
				string Transprants = W2CA((LPCWSTR)(strGetEmile));
				if (regex_match(Transprants, pattern))
				{
	
					killfocus = 2;
					return;
				}
				else
				{
					Reg_Log.SetSel(0, -1);
					Reg_Log.Clear();
					Reg_Log.SetWindowTextW(_T("手机格式错误"));
					killfocus = 1;
					GetDlgItem(IDC_EDIT4)->SetFocus();
					return;
				}
	
			}
		}
	}



HBRUSH CRedist_Dlog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString GetAccount;
	Reg_Log.GetWindowTextW(GetAccount);
	if ((_T("该账户已存在")==GetAccount)|| (_T("手机格式错误") == GetAccount)|| (_T("邮箱格式错误") == GetAccount))
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	return hbr;
}


void CRedist_Dlog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}
