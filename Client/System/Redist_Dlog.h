#pragma once
#include "afxwin.h"
#include "AdoSql.h"
#include "MyCEdit.h"
#include"PWDEdit.h"

// CRedist_Dlog 对话框

class CRedist_Dlog : public CDialogEx
{
	DECLARE_DYNAMIC(CRedist_Dlog)

public:
	CRedist_Dlog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRedist_Dlog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton1();
//	CEdit Regist;
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedRadio1();
private:
	_CommandPtr      m_pCommand;
	_ConnectionPtr   m_pConnection;
	
public:
//	CEdit Regist;
	CEdit Reg_Pwd;
	CEdit Reg_Correct;
	CEdit Reg_Log;
	virtual BOOL OnInitDialog();
	int killfocus;
	CButton m_conRadioPhonBtn;
	int m_nSelection;
//	afx_msg void OnKillfocusEdit5();
//	afx_msg void OnKillfocusEdit4();
//	afx_msg void OnKillFocus(CWnd* pNewWnd);
//	afx_msg void OnKillfocusEdit5();
	afx_msg void OnChangeEdit4();
//	afx_msg void OnKillfocusEdit4();
	afx_msg void OnSetfocusEdit4();
//	afx_msg void OnKillfocusEdit4();
//	afx_msg void OnKillfocusEdit5();
	afx_msg void OnKillfocusEdit4();
//	afx_msg void OnKillfocusEdit3();
	afx_msg void OnEnSetfocusEdit4();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetfocusEdit5();
	afx_msg void OnKillfocusEdit5();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
};
