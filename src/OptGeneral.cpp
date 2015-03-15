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

// OptGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "OptGeneral.h"
#include "AbtDlg.h"
#include "OptionsSheet.h"
#include "DlgAlertSmartDrag.h"
#include "DlgAlertNextClick.h"
#include "DlgAlertCheckIfClicking.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptGeneral property page

IMPLEMENT_DYNCREATE(COptGeneral, CPropertyPage)

COptGeneral::COptGeneral() : CPropertyPage(COptGeneral::IDD)
{
	m_bIsShowingAbt = false;
	//{{AFX_DATA_INIT(COptGeneral)
	m_bSetTopmost = FALSE;
	m_AudibleTick = FALSE;
	m_bShowDrag = FALSE;
	m_bSmartDragCheck = FALSE;
	m_nSmartDragDelay = 0;
	m_nDwellTime = 0;
	m_nDwellZoneSize = 0;
	m_bStartupCheck = FALSE;
	m_nStretchTimerDelay = 0;
	m_nMinsToGo = 0;
	m_bEnableStretchTimer = FALSE;
	m_bOverrideNextOnly = FALSE;
	m_bCheckIfMouseIsDown = FALSE;
	//}}AFX_DATA_INIT
	m_nSmartDragDelay = 30;
	m_bUserHasBeenWarned = false;
}

COptGeneral::~COptGeneral()
{
}

void COptGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptGeneral)
	DDX_Control(pDX, IDC_MINSTOWAIT, m_edtStretchTimer);
	DDX_Control(pDX, IDC_STAT_MINS_TO_NEXT_BREAK, m_statMinsToGo);
	DDX_Control(pDX, IDC_TIME_TO_GO, m_edtMinsToGo);
	DDX_Control(pDX, IDC_STAT_MINS_BTWN_BREAK, m_statMinsBtwnStretches);
	DDX_Control(pDX, IDC_STATIC_STRETCH_FRAME, m_statStretchTimerFrame);
	DDX_Control(pDX, IDC_STRETCH_TIMER_CHECK, m_ckEnableStretchTimer);
	DDX_Control(pDX, IDC_SMART_DRAG_DELAY_EDIT, m_edtSmartDrag);
	DDX_Control(pDX, IDC_SMART_DRAG_FRAME, m_frmSmartDrag);
	DDX_Control(pDX, IDC_SMART_DRAG_CHECK, m_ckSmartDragCheck);
	DDX_Control(pDX, IDC_STAT_SMART_DRAG, m_statSmartDrag);
	DDX_Control(pDX, IDC_STARTUPCHECK, m_ckStartupCheck);
	DDX_Control(pDX, IDC_SHOW_DRAG_CHECK, m_ckShowDrag);
	DDX_Control(pDX, IDC_AUDIBLE_TICK, m_ckAudibleTick);
	DDX_Control(pDX, IDC_KEEP_ON_TOP, m_ckKeepOnTop);
	DDX_Check(pDX,		IDC_KEEP_ON_TOP, m_bSetTopmost);
	DDX_Check(pDX,		IDC_AUDIBLE_TICK, m_AudibleTick);
	DDX_Check(pDX,		IDC_SHOW_DRAG_CHECK, m_bShowDrag);
	DDX_Check(pDX,		IDC_SMART_DRAG_CHECK, m_bSmartDragCheck);
	DDX_Text(pDX,		IDC_SMART_DRAG_DELAY_EDIT, m_nSmartDragDelay);
	DDX_Text(pDX,		IDC_TICKS, m_nDwellTime);
	DDX_Text(pDX,		IDC_EDT_DWELL_ZONE, m_nDwellZoneSize);
	DDX_Check(pDX,		IDC_STARTUPCHECK, m_bStartupCheck);
	DDX_Text(pDX,		IDC_MINSTOWAIT, m_nStretchTimerDelay);
	DDX_Text(pDX,		IDC_TIME_TO_GO, m_nMinsToGo);
	DDX_Check(pDX,		IDC_STRETCH_TIMER_CHECK, m_bEnableStretchTimer);
	DDX_Check(pDX,		IDC_CK_OVERRIDE_NEXT_CLICK, m_bOverrideNextOnly);
	DDX_Check(pDX, IDC_CK_MOUSE_DN, m_bCheckIfMouseIsDown);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(COptGeneral)
	ON_BN_CLICKED(IDC_SMART_DRAG_CHECK, OnSmartDragCheck)
	ON_BN_CLICKED(IDC_STRETCH_TIMER_CHECK, OnStretchTimerCheck)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_BN_CLICKED(IDC_CK_OVERRIDE_NEXT_CLICK, OnCkOverrideNextClick)
	ON_WM_TCARD()
	ON_WM_HELPINFO()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_CK_MOUSE_DN, OnCkMouseDn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptGeneral message handlers

BOOL COptGeneral::OnSetActive() 
{
	m_bPopulatingDlg = true;			// used in SmartDragCheck

	OnStretchTimerCheck();

	m_bSmartDragCheck = m_pProcHandler->m_bSmartDragEnabled;
	m_bOverrideNextOnly = m_pProcHandler->m_bOverrideNextOnly;

	UpdateData(FALSE);
//	VerifyValues();
	OnSmartDragCheck();

	m_bPopulatingDlg = false;
//	m_ckAudibleTick.SetCheck(m_AudibleTick);
	return CPropertyPage::OnSetActive();
}

void COptGeneral::OnSmartDragCheck() 
{
	BOOL bNewState = m_ckSmartDragCheck.GetCheck();

	if (!m_bPopulatingDlg)
	{
		if (bNewState)			// if user is enabling this option
		{
			CDlgAlertSmartDrag dlg;

			dlg.m_bDontRemind = m_bUserHasBeenWarned;
			int nDlgRes = dlg.DoModal();
			m_bUserHasBeenWarned = !!dlg.m_bDontRemind;

			if (IDCANCEL==nDlgRes)			// if user pressed "Cancel"
			{
				m_ckSmartDragCheck.SetCheck(FALSE);
				return;
			}
		}
	}

	m_frmSmartDrag.EnableWindow(bNewState);				// list box
	m_edtSmartDrag.EnableWindow(bNewState);
	m_statSmartDrag.EnableWindow(bNewState);
	m_ckShowDrag.EnableWindow(bNewState);
	UpdateData(TRUE);
	m_pProcHandler->m_bSmartDragEnabled = (m_bSmartDragCheck==TRUE);
}


void COptGeneral::OnStretchTimerCheck() 
{
	BOOL bNewState = m_ckEnableStretchTimer.GetCheck();

	m_statStretchTimerFrame.EnableWindow(bNewState);
	m_edtStretchTimer.EnableWindow(bNewState);
	m_statMinsBtwnStretches.EnableWindow(bNewState);
	m_edtMinsToGo.EnableWindow(bNewState);
	m_statMinsToGo.EnableWindow(bNewState);
}

void COptGeneral::OnButtonAbout() 
{
	m_pdlgAbt = new CAbtDlg;
	m_bIsShowingAbt = true;
	m_pdlgAbt->DoModal();
	m_bIsShowingAbt = false;
	
	delete m_pdlgAbt;
}


void COptGeneral::OnCkOverrideNextClick() 
{
	UpdateData(TRUE);

	if (!m_bPopulatingDlg)
	{
		if (!m_bOverrideNextOnly)			// if user is disabling this option
		{
			CDlgAlertNextClick dlg;

			dlg.m_bDontRemind = m_bUserHasBeenWarnedNC;
			int nDlgRes = dlg.DoModal();
			m_bUserHasBeenWarnedNC = !!dlg.m_bDontRemind;

			if (IDCANCEL==nDlgRes)			// if user pressed "Cancel"
			{
				m_bOverrideNextOnly = TRUE;
				UpdateData(FALSE);
				return;
			}
		}
	}
	m_pProcHandler->m_bOverrideNextOnly = (m_bOverrideNextOnly==TRUE);
}

void COptGeneral::OnTCard(UINT idAction, DWORD dwActionData) 
{
	// TODO: Add your message handler code here
	
}

BOOL COptGeneral::OnHelpInfo(HELPINFO* pHelpInfo) 
{
//	return CPropertyPage::OnHelpInfo(pHelpInfo);
	// TODO: Add your message handler code here and/or call default
	::WinHelp(m_hWnd, "MouseTool.hlp", HELP_CONTEXTPOPUP, pHelpInfo->dwContextId);

	return TRUE;

}

void COptGeneral::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	
}

void COptGeneral::OnRButtonDown(UINT nFlags, CPoint point) 
{
	HWND hChildWnd;

	hChildWnd = ::ChildWindowFromPoint(m_hWnd, point);
	if (hChildWnd == m_hWnd)
		return;

	int nctrlId = ::GetDlgCtrlID(hChildWnd);


	CPropertyPage::OnRButtonDown(nFlags, point);
}

void COptGeneral::OnOK() 
{

	CPropertyPage::OnOK();
}

void COptGeneral::VerifyValues()
{
	bool bNotify = false;

	if (m_nSmartDragDelay<1)
	{
		m_nSmartDragDelay = 3;
		bNotify = true;
	}
	if (m_nSmartDragDelay>50)
	{
		m_nSmartDragDelay = 3;
		bNotify = true;
	}

	if (m_nDwellTime<1)
	{
		m_nDwellTime = 5;
		bNotify = true;
	}
	if (m_nDwellTime>50)
	{
		m_nDwellTime = 5;
		bNotify = true;
	}

	if (m_nStretchTimerDelay<1)
	{
		m_nStretchTimerDelay = 30;
		bNotify = true;
	}
	if (m_nStretchTimerDelay>500)
	{
		m_nStretchTimerDelay = 30;
		bNotify = true;
	}

	if (m_nDwellZoneSize<1)
	{
		m_nDwellZoneSize = 2;
		bNotify = true;
	}
	if (m_nDwellZoneSize>50)
	{
		m_nDwellZoneSize = 2;
		bNotify = true;
	}

	if (bNotify)
		MessageBox("One or more values in the General Tab\nhave been found to be out of range.\n\nThese have been restored to their defaults.");
}

void COptGeneral::OnCkMouseDn() 
{
	UpdateData(TRUE);

	if (!m_bPopulatingDlg)
	{
//		AfxMessageBox("part way there");
		if (m_bCheckIfMouseIsDown)			// if user is enabling this option
		{
			CDlgAlertCheckIfClicking dlg;

			dlg.m_bDontWarn = m_bUserHasBeenWarnedCC;
			int nDlgRes = dlg.DoModal();
			m_bUserHasBeenWarnedCC = !!dlg.m_bDontWarn;

			if (IDCANCEL==nDlgRes)			// if user pressed "Cancel"
			{
				m_bCheckIfMouseIsDown = FALSE;
				UpdateData(FALSE);
				return;
			}
		}
	}
	m_pProcHandler->m_bOverrideNextOnly = (m_bOverrideNextOnly==TRUE);
}
