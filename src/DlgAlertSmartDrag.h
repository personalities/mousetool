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

#if !defined(AFX_DLGALERTSMARTDRAG_H__D536CA62_C665_11D2_901F_006008C4A30F__INCLUDED_)
#define AFX_DLGALERTSMARTDRAG_H__D536CA62_C665_11D2_901F_006008C4A30F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlertSmartDrag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlertSmartDrag dialog

class CDlgAlertSmartDrag : public CDialog
{
// Construction
public:
	CDlgAlertSmartDrag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlertSmartDrag)
	enum { IDD = IDD_DLG_ALERT_SD };
	BOOL	m_bDontRemind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlertSmartDrag)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlertSmartDrag)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ncLUp(UINT nHitTest, POINTS point);
	void ncLDown(UINT nHitTest, POINTS point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALERTSMARTDRAG_H__D536CA62_C665_11D2_901F_006008C4A30F__INCLUDED_)
