// MyCEdit.cpp : ʵ���ļ�
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



// MyCEdit ��Ϣ�������




void MyCEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	
		AfxMessageBox(_T("1111111111111111����ʧȥ�˽��㡣"));
	
	// TODO: �ڴ˴������Ϣ����������
}
