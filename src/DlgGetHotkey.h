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

#if !defined(AFX_DLGGETHOTKEY_H__24EB5681_A7AA_11D1_8341_00207811D6EB__INCLUDED_)
#define AFX_DLGGETHOTKEY_H__24EB5681_A7AA_11D1_8341_00207811D6EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgGetHotkey.h : header file
//

#include "KeyHandler.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgGetHotkey dialog


class CDlgGetHotkey : public CDialog
{
// Construction
public:
	CDlgGetHotkey(CWnd* pParent = NULL);   // standard constructor

	CKeyHandler m_khHotkey;
	void OnKeyHook(UINT wParam, LONG lParam);


	// To handle the user dragging the window using MouseTool
	LONG 			OnHook(UINT wParam, LONG lParam);
	void 			OnNCLUp(UINT nHitTest, POINTS point);
	void 			OnNCLDown(UINT nHitTest, POINTS point);
	bool			m_bStopDragging;
	bool			m_bNCDragging;
	POINT			m_ptDragStartPointMouse;
	POINT			m_ptDragStartPointWnd;
	// end handle user drag


// Dialog Data
	//{{AFX_DATA(CDlgGetHotkey)
	enum { IDD = IDD_DLG_GET_HOTKEY };
	CString	m_strHotkeyBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGetHotkey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGetHotkey)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETHOTKEY_H__24EB5681_A7AA_11D1_8341_00207811D6EB__INCLUDED_)
