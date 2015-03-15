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

#if !defined(AFX_OPTIONSSHEET_H__63274224_9C9E_11D1_82EA_000000000000__INCLUDED_)
#define AFX_OPTIONSSHEET_H__63274224_9C9E_11D1_82EA_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OptionsSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

#include "OptGeneral.h"
#include "OptTiming.h"
#include "Optkeys.h"
#include "OptContext.h"
#include "ProcessHandler.h"


class COptionsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(COptionsSheet)
	COptGeneral		m_pgGeneral;
	COptKeys		m_pgKeys;
	COptContext		m_pgContext;
	int				m_nxButtonLeft, m_nqButtonLeft;
	bool			m_bInHelpMode;
	CWnd			*m_pMouseToolWnd;
	bool			m_bMouseToolIsOn;
	int				m_nPageToOpen;

// Construction
public:
	COptionsSheet();
	COptionsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	COptionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CProcessHandler *m_pProcHandler;

	void			OpenAtPage(int);
	void			OnKeyHook(LONG wParam, LONG lParam);
	void			OnHelpButton();
	void			GetSysButtonBorder();
	void			EnterHelpMode();
	long			GetHelpMapOffset();

	// To handle the user dragging the window using MouseTool
	LONG 			OnHook(UINT wParam, LONG lParam);
	void 			OnNCLUp(UINT nHitTest, POINTS point);
	void 			OnNCLDown(UINT nHitTest, POINTS point);
	bool			m_bStopDragging;
	bool			m_bNCDragging;
	POINT			m_ptDragStartPointMouse;
	POINT			m_ptDragStartPointWnd;
	// end handle user drag

//	void OnHook(UINT wParam, LONG lParam);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsSheet)
	public:
	virtual int DoModal();
	virtual BOOL OnInitDialog();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptionsSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionsSheet)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSSHEET_H__63274224_9C9E_11D1_82EA_000000000000__INCLUDED_)
