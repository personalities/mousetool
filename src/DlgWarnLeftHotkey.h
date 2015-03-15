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

#if !defined(AFX_DLGWARNLEFTHOTKEY_H__AD2C01C1_DBC1_11D2_A6F5_006008C4A30F__INCLUDED_)
#define AFX_DLGWARNLEFTHOTKEY_H__AD2C01C1_DBC1_11D2_A6F5_006008C4A30F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWarnLeftHotkey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWarnLeftHotkey dialog

class CDlgWarnLeftHotkey : public CDialog
{
// Construction
public:
	void ncLDown(UINT nHitTest, POINTS point);
	CDlgWarnLeftHotkey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWarnLeftHotkey)
	enum { IDD = IDD_DLG_WARN_LEFT_HOTKEY };
	BOOL	m_bDontShowAgain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWarnLeftHotkey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWarnLeftHotkey)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ncLUp(UINT nHitTest, POINTS point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWARNLEFTHOTKEY_H__AD2C01C1_DBC1_11D2_A6F5_006008C4A30F__INCLUDED_)
