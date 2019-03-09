// MyServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "MyServer.h"
#include "ServerDlg.h"
#include "MyReceive.h"
#include <afxwin.h>

// MyServer
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MyServer::MyServer(CServerDlg *pSockDlg1)
{
	pSockDlg= pSockDlg1;
}

MyServer::~MyServer()
{
}


// MyServer ��Ա����


void MyServer::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	CSocket::OnReceive(nErrorCode);
}


void MyServer::OnAccept(int nErrorCode)
{
//	CSocket::OnAccept(nErrorCode);	
	MyReceive *pSocketRecv;
	if (pSocketRecv = new MyReceive(this->pSockDlg))
	{
		if (Accept(*pSocketRecv))
		{
			pSocketRecv->pSockFile = new CSocketFile(pSocketRecv);
			pSocketRecv->pArcIn = new CArchive(pSocketRecv->pSockFile, CArchive::load);
			pSocketRecv->pArcOut = new CArchive(pSocketRecv->pSockFile, CArchive::store);
			pSockDlg->SocketRecv = pSocketRecv;
			pSocketRecv = NULL;
		}
		else
		{
			//pSockDlg->m_list.AddString("����ʧ�ܣ���������������");
			delete pSocketRecv;
		}
	}
	else
		//pSockDlg->m_list.AddString("����ʧ�ܣ�����������");
		AfxMessageBox(_T(""));

}
