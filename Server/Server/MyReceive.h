#pragma once
// MyReceive ÃüÁîÄ¿±ê

class MyReceive : public CSocket
{
public:
	MyReceive();	
	virtual ~MyReceive();
	int nNum;
	MyReceive * SocketRecv;
	MyReceive *pGetSocketAd;
public:
	virtual void OnReceive(int nErrorCode);
//	virtual void AssertValid() const;
	virtual void OnAccept(int nErrorCode);
	//virtual void OnSend(int nErrorCode);
};


