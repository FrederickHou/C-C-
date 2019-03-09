// PWDEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "LINK_DATABASE.h"
#include "PWDEdit.h"


// CPWDEdit

IMPLEMENT_DYNAMIC(CPWDEdit, CEdit)

CPWDEdit::CPWDEdit()
{

}

CPWDEdit::~CPWDEdit()
{
}


BEGIN_MESSAGE_MAP(CPWDEdit, CEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CPWDEdit 消息处理程序




void CPWDEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	AfxMessageBox(_T("2222222222222222222222222密码失去了焦点。"));
	// TODO: 在此处添加消息处理程序代码
}
