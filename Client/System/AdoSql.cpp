#include "stdafx.h"
#include "AdoSql.h"
#include <afxwin.h>
AdoSql  *MysqlRegist;
AdoSql::AdoSql()
{
	MysqlRegist = this;
}

AdoSql::~AdoSql()
{
}


bool AdoSql::OnInitADOConn()
{
	::CoInitialize(NULL);
	try
	{
	
		m_pConnection.CreateInstance("ADODB.Connection");
		_bstr_t strConnect = "Provider=SQLOLEDB;Server=CANDY\\SQL2012;Database=Room;uid=sa;pwd=hjh111000;";
		m_pConnection->Open(strConnect, _T("sa"), "hjh111000", adModeUnknown);
		//CString Message;
		//Message.Format(_T("数据库连接成功"));
		//AfxMessageBox(Message);
		return 1;
	}
	catch (_com_error e)
	{	
		CString errormessage;
		errormessage.Format(_T("数据库连接失败!\r\n错误信息：%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);
		return 0;
	}
}
void AdoSql::ExitConnect()
{
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	::CoUninitialize();
}

