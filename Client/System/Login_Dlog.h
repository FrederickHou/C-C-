#pragma once
#include "afxwin.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"


// Login_Dlog 对话框

class Login_Dlog : public CDialogEx
{
	DECLARE_DYNAMIC(Login_Dlog)

public:
	Login_Dlog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Login_Dlog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	CButton CameraButton;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	double angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0);
	CvSeq *findSquares(IplImage* img, CvMemStorage* storage);
	void drawSquares(IplImage** cpy, IplImage* img, CvSeq* squares);
	HANDLE CSerialOpen(LPCTSTR COMx, DWORD baudrate, BYTE PortByteSize, BYTE PortParity, BYTE PortStopBits);
	int nMySign;

private:
	CRect rect;
	int nWidth;
	int nHeight;
	CString strGetport ;
	CString strGetFrequence ;
	CString strGetCorrect ;
	CString strGetData ;
	CString strGetStop;
	CString strComProtocol;
	HANDLE hCom;//串口句柄s
	bool flage;
	int PortSendSign;
public:
	afx_msg void OnEnChangeEdit1();
	CEdit CarHeight;
	CEdit CarWidth;
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox Cport;
	CComboBox Cfrequence;
	CComboBox Ccorrect;
	CComboBox Cdata;
	CComboBox Cstop;
	int CRadioSign;
	afx_msg void OnBnClickedButton2();
	CButton CPortButton;
	CButton CPortSendButton;
	CEdit CPortState;
	CEdit CPortTX;
	CEdit CPortRX;
	afx_msg void OnBnClickedButton3();
	BOOL WriteChar(HANDLE hCom, BYTE* m_szWriteBuffer, DWORD m_nToSend);
	CEdit CSendText;
	CButton CMyRadioButton;
	int nMyRadioButton;
};