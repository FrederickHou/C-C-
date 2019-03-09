#pragma once


// CPWDEdit

class CPWDEdit : public CEdit
{
	DECLARE_DYNAMIC(CPWDEdit)

public:
	CPWDEdit();
	virtual ~CPWDEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


