#pragma once
#import "E:\C\2\LINK_DATABASE\LINK_DATABASE\Debug\msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")

class AdoSql
{
public:
	AdoSql();
	~AdoSql();
	_ConnectionPtr   m_pConnection; // Êý¾Ý¿â
	_RecordsetPtr    m_pRecordset; // ÃüÁî 
	_CommandPtr      m_pCommand; // ¼ÇÂ¼
	
	bool OnInitADOConn();
	void ExitConnect();
	
	

};

