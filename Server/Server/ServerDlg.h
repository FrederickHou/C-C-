
// ServerDlg.h : ͷ�ļ�
//

#pragma once

#include "afxwin.h"
#include "MyReceive.h"
#include "AdoSql.h"
// CServerDlg �Ի���
class CServerDlg : public CDialogEx
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

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
