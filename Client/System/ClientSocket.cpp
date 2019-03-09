// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LINK_DATABASE.h"
#include "ClientSocket.h"
#include "LINK_DATABASEDlg.h"
#include <afxwin.h>
#include "Login_Dlog.h"
#include "Redist_Dlog.h"
// CClientSocket

extern CLINK_DATABASEDlg *pLogDlg;
extern CString cstrGetAccount;
extern CRedist_Dlog *pRedistDlog;
CClientSocket *IndexSocket;
CClientSocket *pIndexRedistSocket;
CClientSocket::CClientSocket()
{
	IndexSocket = this;
	pIndexRedistSocket = this;
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��Ա����


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	char buf[255] = { 0 };
	CString strServerRecText;
	Receive(buf, 255);
	strServerRecText.Format(_T("%s"), buf);
	if (_T("�˺Ų�����")==strServerRecText)
	{
		pLogDlg->Text.SetWindowTextW(_T("�˺Ų�����"));
	}
	if (_T("2")==strServerRecText)
	{
		pLogDlg->SendMessage(WM_CLOSE);
	 Login_Dlog My_Login_Dlog;
	 My_Login_Dlog.DoModal();
	}
	else if(_T("21") ==strServerRecText)
	{
		AfxMessageBox(_T("�������"));
	}
	if (_T("3") == strServerRecText)
	{
		pLogDlg->SendMessage(WM_CLOSE);
		Login_Dlog My_Login_Dlog;
		My_Login_Dlog.DoModal();
		
	
	}
	else if (_T("32") == strServerRecText)
	{
		AfxMessageBox(_T("�������"));
	}
	else if (_T("31") == strServerRecText)
	{
		AfxMessageBox(_T("�������"));
	}
	else if (_T("41") == strServerRecText)
	{
		CString Account;
		CString LinkAccount;
		pLogDlg->Text.GetWindowTextW(Account);
		cstrGetAccount = Account;
		LinkAccount = Account + _T("          (��)");
		pLogDlg->Text.SetWindowTextW(LinkAccount);
	}
	else if (_T("4") == strServerRecText)
	{
		pLogDlg->Text.SetWindowTextW(_T("�˺Ų�����"));
	}
	else if (_T("51") == strServerRecText)
	{
		CString Account;
		CString LinkAccount;
		pLogDlg->Text.GetWindowTextW(Account);
		cstrGetAccount = Account;
		LinkAccount = Account + _T("   (��)");
		pLogDlg->Text.SetWindowTextW(LinkAccount);
	}
	else if (_T("5") == strServerRecText)
	{
		pLogDlg->Text.SetWindowTextW(_T("�˺Ų�����"));
	}
	else if (_T("1") == strServerRecText)
	{
		AfxMessageBox(_T("ע��ɹ�"));
		pRedistDlog->SendMessage(WM_CLOSE);
	}
	else if (_T("11") == strServerRecText)
	{
	pRedistDlog->Reg_Pwd.SetSel(0, -1);
	pRedistDlog->Reg_Pwd.Clear();
	pRedistDlog->Reg_Correct.SetSel(0, -1);
	pRedistDlog->Reg_Correct.Clear();
	pRedistDlog->Reg_Log.SetWindowTextW(_T("���˻��Ѵ���"));
	}
	else if (_T("0") == strServerRecText)
	{
		AfxMessageBox(_T("ע��ɹ�"));
		CRedist_Dlog MyCRedist_Dlog;
		pRedistDlog->SendMessage(WM_CLOSE);
	}
	else if (_T("10") == strServerRecText)
	{
		pRedistDlog->Reg_Pwd.SetSel(0, -1);
		pRedistDlog->Reg_Pwd.Clear();
		pRedistDlog->Reg_Correct.SetSel(0, -1);
		pRedistDlog->Reg_Correct.Clear();
		pRedistDlog->Reg_Log.SetWindowTextW(_T("���˻��Ѵ���"));
	}	
	CSocket::OnReceive(nErrorCode);
}
