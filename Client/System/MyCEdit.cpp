// MyCEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "LINK_DATABASE.h"
#include "MyCEdit.h"


// MyCEdit

IMPLEMENT_DYNAMIC(MyCEdit, CEdit)

MyCEdit::MyCEdit()
{

}

MyCEdit::~MyCEdit()
{
}


BEGIN_MESSAGE_MAP(MyCEdit, CEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// MyCEdit 消息处理程序




void MyCEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	
		AfxMessageBox(_T("1111111111111111邮箱失去了焦点。"));
	
	// TODO: 在此处添加消息处理程序代码
}
