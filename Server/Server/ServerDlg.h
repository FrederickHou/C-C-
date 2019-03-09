
// ServerDlg.h : 头文件
//

#pragma once

#include "afxwin.h"
#include "MyReceive.h"
#include "AdoSql.h"
// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CEdit ReceiveText;
//	CButton ListenButton;
//	CButton ReceiveButton;
	afx_msg void OnBnClickedButton1();
//	CEdit ReceiveText;
//	CEdit SendText;
	HANDLE handle_1 = 0;
	HANDLE handle_2 = 0;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
//	CEdit SocketReceText;
	MyReceive *SocketServer;
	CEdit Text;
	CEdit SendText;
	AdoSql SqlConnect;
	CEdit CLogNum;
	afx_msg void OnEnChangeEdit1();
};
