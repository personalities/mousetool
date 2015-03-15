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

#if !defined(AFX_OPTCONTEXT_H__28842301_A21E_11D1_8323_00207811D6EB__INCLUDED_)
#define AFX_OPTCONTEXT_H__28842301_A21E_11D1_8323_00207811D6EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OptContext.h : header file
//

#include "processhandler.h"


/////////////////////////////////////////////////////////////////////////////
// COptContext dialog

class COptContext : public CPropertyPage
{
	DECLARE_DYNCREATE(COptContext)
	void		EnableRadios(BOOL);
	bool		m_bBackupContext;
	CString		GetSelectedApp();
	bool		m_bPopulatingDlg;
	bool		m_bEnableContextsBackup;

// Construction
public:
	COptContext();
	~COptContext();

//	void OnRadio();
	void UpdateContext();//updates current context with dialog settings.
	void SetClassAtMouse();
	CProcessHandler *m_pProcHandler;

// Dialog Data
	//{{AFX_DATA(COptContext)
	enum { IDD = IDD_DLG_CONTEXT };
	CButton	m_ckDisableSmartDragInScrollbars;
	CButton	m_statAction;
	CStatic	m_statWndTypes;
	CButton	m_btDeleteContext;
	CButton	m_btAddContext;
	CStatic	m_statPrevWindow;
	CEdit	m_edtPrevContext;
	CListBox	m_lstApps;
	CButton	m_ckEnableContext;
	CButton	m_Radio1;
	int		m_nRadio;
	BOOL	m_bEnableContext;
	BOOL	m_bDisableSmartDragInScrollbars;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptContext)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptContext)
	afx_msg void OnCkEnableContext();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnSelchangeLstApps();
	afx_msg void OnButtonAddContext();
	afx_msg void OnButtonDeleteContext();
	afx_msg void OnRadio5();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTCONTEXT_H__28842301_A21E_11D1_8323_00207811D6EB__INCLUDED_)
