/*
Source file for MouseTool
MouseTool clicks the mouse when the user pauses it,
helping reduce strain caused by using the mouse.
Copyright (C) 2000 by Jeff Roush
www.mousetool.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
Or www.gnu.org/home.html
*/

#if !defined(AFX_OPTKEYS_H__A15303A2_A185_11D1_8322_00207811D6EB__INCLUDED_)
#define AFX_OPTKEYS_H__A15303A2_A185_11D1_8322_00207811D6EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OptKeys.h : header file
//

#include "KeyHandler.h"

/////////////////////////////////////////////////////////////////////////////
// COptKeys dialog

#include "DlgGetHotkey.h"

class COptKeys : public CPropertyPage
{
	DECLARE_DYNCREATE(COptKeys)
	POINT ptNewWndPos;

	bool			m_bEnableHotkeysBackup;

	CKeyHandler		m_khDblBackup;
	CKeyHandler		m_khRightBackup;
	CKeyHandler		m_khStopBackup;

	CKeyHandler		m_khBtnLeftBack;
	CKeyHandler		m_khBtnRightBack;
	CKeyHandler		m_khBtnDoubleBack;
	CKeyHandler		m_khBtnToggleBack;
	HWND			m_hwndMouseToolWnd;
	
// Construction
public:
	void UnRegisterAllHotkeys();
	void RegisterAllHotkeys();
	void SetMainWnd(HWND hWnd);
	COptKeys();
	~COptKeys();
	int 			OnKeyHook(int nKeyDown, UINT wParam, LONG lParam);

	bool			m_bGettingHotkey;
	bool			m_bWarnLeftHotkey;

	CDlgGetHotkey	m_dlgGetHotkey;
	CKeyHandler		m_khDblKey;
	CKeyHandler		m_khRightKey;
	CKeyHandler		m_khStopKey;

	CKeyHandler		m_khBtnLeft;
	CKeyHandler		m_khBtnRight;
	CKeyHandler		m_khBtnDouble;
	CKeyHandler		m_khBtnToggleLeft;

	void			ChangeHotkey(CKeyHandler *, CEdit *, int);


// Dialog Data
	//{{AFX_DATA(COptKeys)
	enum { IDD = IDD_OPT_KEYS };
	CStatic	m_statToggleLeft;
	CEdit	m_edtToggleLeft;
	CButton	m_btnToggleLeft;
	CButton	m_statFrameBtns;
	CStatic	m_statRightBtn;
	CStatic	m_statLeftBtn;
	CStatic	m_statDblBtn;
	CButton	m_btnLeftBtn;
	CButton	m_btnRightBtn;
	CButton	m_btnDblBtn;
	CEdit	m_edtBtnLeft;
	CEdit	m_edtBtnRight;
	CEdit	m_edtBtnDouble;
	CButton	m_btnStopKey;
	CEdit	m_edtStopKey;
	CStatic	m_statStopKey;
	CStatic	m_statRightKey;
	CStatic	m_statDblKey;
	CButton	m_btnRightKey;
	CButton	m_statHotkeys;
	CButton	m_btnDblKey;
	CEdit	m_edtRightKey;
	CEdit	m_edtDblKey;
	BOOL	m_bEnableHotkeys;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptKeys)
	public:
	virtual BOOL OnSetActive();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptKeys)
	afx_msg void OnButtonDblKey();
	afx_msg void OnButtonRightKey();
	afx_msg void OnCkEnableHotkeys();
	afx_msg void OnButtonStopKey();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonRight();
	afx_msg void OnButtonDouble();
	afx_msg void OnButtonToggle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void RegisterHotkey(CKeyHandler *pKey, int nHotkeyID);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTKEYS_H__A15303A2_A185_11D1_8322_00207811D6EB__INCLUDED_)
