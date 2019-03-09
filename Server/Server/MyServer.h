#pragma once
class CServerDlg;
class MyServer;
// MyServer ÃüÁîÄ¿±ê

class MyServer : public CSocket
{
public:
	MyServer(CServerDlg *pSockDlg1);
	virtual ~MyServer();
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
public:
	CServerDlg *pSockDlg;
};


