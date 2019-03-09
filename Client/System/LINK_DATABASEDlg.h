
// LINK_DATABASEDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "AdoSql.h"
#include "ClientSocket.h"

class CLINK_DATABASEDlg : public CDialogEx
{
// ����
public:
	CLINK_DATABASEDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINK_DATABASE_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
// ʵ��
protected:
	HICON m_hIcon;
	CString SocketIp ;
	CClientSocket *IndexSocketClient;
    AdoSql mysql;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	//int nRadioButton;
	afx_msg void OnBnClickedButton1();
	CEdit Text;
	CEdit Pwd;
	afx_msg void OnEnChangeEdit2();
//	afx_msg void OnBnClickedButton2();
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnKillfocusEdit1();
	afx_msg void OnKillfocusEdit2();
//	afx_msg void OnClickedStat1();
	afx_msg void OnClickedCheck2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSetfocusEdit2();
	
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	CButton nRadioButton;
	int nMyRadioButton;
	afx_msg void OnKillFocus(CWnd* pNewWnd);
//	virtual void OnOK();
};
