// PWDEdit.cpp : ʵ���ļ�
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



// CPWDEdit ��Ϣ�������




void CPWDEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	AfxMessageBox(_T("2222222222222222222222222����ʧȥ�˽��㡣"));
	// TODO: �ڴ˴������Ϣ����������
}
