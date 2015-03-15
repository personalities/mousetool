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

#if !defined(AFX_OPTGENERAL_H__63274221_9C9E_11D1_82EA_000000000000__INCLUDED_)
#define AFX_OPTGENERAL_H__63274221_9C9E_11D1_82EA_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OptGeneral.h : header file
//
#include "processhandler.h"

/////////////////////////////////////////////////////////////////////////////
// COptGeneral dialog

class COptGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(COptGeneral)

// Construction
public:
	void VerifyValues();
	COptGeneral();
	~COptGeneral();

	bool		m_bPopulatingDlg;
	bool		m_bUserHasBeenWarned;
	bool		m_bUserHasBeenWarnedNC;
	bool		m_bUserHasBeenWarnedCC;
	bool 		m_bIsShowingAbt;

	CProcessHandler *m_pProcHandler;
	CDialog 	*m_pdlgAbt;

// Dialog Data
	//{{AFX_DATA(COptGeneral)
	enum { IDD = IDD_OPT_GENERAL };
	CEdit	m_edtStretchTimer;
	CStatic	m_statMinsToGo;
	CEdit	m_edtMinsToGo;
	CStatic	m_statMinsBtwnStretches;
	CButton	m_statStretchTimerFrame;
	CButton	m_ckEnableStretchTimer;
	CEdit	m_edtSmartDrag;
	CButton	m_frmSmartDrag;
	CButton	m_ckSmartDragCheck;
	CStatic	m_statSmartDrag;
	CButton	m_ckStartupCheck;
	CButton	m_ckShowDrag;
	CButton	m_ckAudibleTick;
	CButton	m_ckKeepOnTop;
	BOOL	m_bSetTopmost;
	BOOL	m_AudibleTick;
	BOOL	m_bShowDrag;
	BOOL	m_bSmartDragCheck;
	int		m_nSmartDragDelay;
	int		m_nDwellTime;
	int		m_nDwellZoneSize;
	BOOL	m_bStartupCheck;
	int		m_nStretchTimerDelay;
	int		m_nMinsToGo;
	BOOL	m_bEnableStretchTimer;
	BOOL	m_bOverrideNextOnly;
	BOOL	m_bCheckIfMouseIsDown;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptGeneral)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptGeneral)
	afx_msg void OnSmartDragCheck();
	afx_msg void OnStretchTimerCheck();
	afx_msg void OnButtonAbout();
	afx_msg void OnCkOverrideNextClick();
	afx_msg void OnTCard(UINT idAction, DWORD dwActionData);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCkMouseDn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTGENERAL_H__63274221_9C9E_11D1_82EA_000000000000__INCLUDED_)
