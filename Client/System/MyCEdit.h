#pragma once


// MyCEdit

class MyCEdit : public CEdit
{
	DECLARE_DYNAMIC(MyCEdit)

public:
	MyCEdit();
	virtual ~MyCEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


