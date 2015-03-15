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

// OptionsSheet.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "MouseToolDlg.h"
#include "OptionsSheet.h"
#include "AbtDlg.h"
//#include "Afxpriv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

IMPLEMENT_DYNAMIC(COptionsSheet, CPropertySheet)

COptionsSheet::COptionsSheet()
{
	CPropertySheet("Options", NULL, 0);
	AddPage(&m_pgGeneral);
	AddPage(&m_pgKeys);
	AddPage(&m_pgContext);
	m_bNCDragging = false;
	m_nPageToOpen = 0;
	
	ModifyStyle(WS_SYSMENU, 0);
}

COptionsSheet::COptionsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_pgGeneral);
	AddPage(&m_pgKeys);
	AddPage(&m_pgContext);
	m_bNCDragging = false;
	ModifyStyle(WS_SYSMENU, 0);
	m_nPageToOpen = 0;
}

COptionsSheet::COptionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_pgGeneral);
	AddPage(&m_pgKeys);
	AddPage(&m_pgContext);
	m_bNCDragging = false;
	m_nPageToOpen = 0;
}

COptionsSheet::~COptionsSheet()
{
}


BEGIN_MESSAGE_MAP(COptionsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(COptionsSheet)
	ON_WM_HELPINFO()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_NCLBUTTONDOWN, 	OnNCLDown )
	ON_MESSAGE( WM_NCLBUTTONUP, 	OnNCLUp )
	ON_BN_CLICKED(ID_HELP, OnHelpButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet message handlers

// void COptionsSheet::OnHook(UINT wParam, LONG lParam) 
// {                                                    
// 	m_pgKeys.OnHook(wParam, lParam);                    
// }                                                    

//void COptionsSheet::OnKeyHook(LONG wParam, LONG lParam)
//{
//	m_pgKeys.OnKeyHook(wParam, lParam);
//}

int COptionsSheet::DoModal() 
{
//	ModifyStyle(WS_SYSMENU, 0);
	return CPropertySheet::DoModal();
}

/*---------------------------------------------**
** This event happens whenever the mouse moves **
**---------------------------------------------*/
LONG COptionsSheet::OnHook(UINT wParam, LONG lParam)
{
	if (!m_hWnd)
		return 0;

// there is a bug here.  Uncomment this to allow about box to be dragged by mouse,
// but it also (at some point) causes an access violation.
/*
	if (m_pgGeneral.m_bIsShowingAbt) 		// move the about box if necessary
		((CAbtDlg *)	 m_pgGeneral.m_pdlgAbt)->OnHook(wParam, lParam);
*/
	m_pgKeys.m_dlgGetHotkey.OnHook(wParam, lParam);
		
	if (m_bNCDragging) {			// If we're dragging the MouseTool window
		CPoint ptNewWndPos;
		GetCursorPos(&ptNewWndPos);

		ptNewWndPos.x -= m_ptDragStartPointMouse.x;			// ptNewWndPos is now the change in position
		ptNewWndPos.y -= m_ptDragStartPointMouse.y;			// ptNewWndPos is now the change in position
		ptNewWndPos += m_ptDragStartPointWnd;			// ptNewWndPos is now the new app position

		SetWindowPos(0, ptNewWndPos.x, ptNewWndPos.y, 0,0, SWP_NOSIZE | SWP_NOZORDER);
	}
	return 0;
}

void COptionsSheet::OnNCLUp(UINT nHitTest, POINTS point)
{
	if (m_bStopDragging)
		m_bNCDragging = false;					// Handle dragging of MT ourselves
	m_bStopDragging = true;
}

// Monitor nonclient mouse messages.
// If the user minimizes or closes, handle it here.
// (Otherwise the program waits on the up click before processing timer...)
void COptionsSheet::OnNCLDown(UINT nHitTest, POINTS point)
{
	CString str;
//	static count=0;
	RECT rect;
	CPoint p;

	// point is in screen coordinates.  Convert those to relative coords.
	GetWindowRect(&rect);
//	str.Format("(%d, %d)", rect.left, rect.top);
//	MessageBox(str);
	
	p.x = point.x-rect.left;
	p.y = point.y-rect.top;

//  Did user click on system buttons?  Respond.
	if (p.x > m_nxButtonLeft)	{
		CPropertySheet::EndDialog(IDCANCEL);
		return;
	}
	if (p.x > m_nqButtonLeft)	{
		EnterHelpMode();
		return;
	}


	// handle dragging	
//	CPoint pt(point.x, point.y);
//	OnNcLButtonDown(nHitTest, pt );
	
	
	m_bNCDragging = true;					 
	m_bStopDragging = false;
	((CMouseToolDlg *)GetParent())->MouseLUp();						   
	
	m_ptDragStartPointMouse.x = point.x;
	m_ptDragStartPointMouse.y = point.y;
	GetWindowRect(&rect);
	m_ptDragStartPointWnd.x = rect.left;
	m_ptDragStartPointWnd.y = rect.top;

}

BOOL COptionsSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	SetActivePage(m_nPageToOpen);
	m_nPageToOpen = 0;

//	m_hNormalCursor = GetWindowLong(m_hWnd, cursor?
//	SetWindowLong(m_hWnd, GCL_HCURSOR, LoadCursor(NULL, IDC_HELP));
	
//	Add a "?" button
	ModifyStyleEx(0, WS_EX_CONTEXTHELP);		

//	Get the measurements for the "x" and "?" (system) buttons
	GetSysButtonBorder();

	// remove Apply button
	HWND hWnd = ::GetDlgItem(m_hWnd, ID_APPLY_NOW);
	if (NULL != hWnd)
	{
		::ShowWindow(hWnd, SW_HIDE);
		::EnableWindow(hWnd, FALSE);
	}
	
	m_bStopDragging = true;
//	m_bInHelpMode = false;

	// Move OK and Cancel
	HWND hwOk		= ::GetDlgItem(m_hWnd, IDOK);
	HWND hwCancel	= ::GetDlgItem(m_hWnd, IDCANCEL);
	HWND hwHelp		= ::GetDlgItem(m_hWnd, IDHELP);

	if ( (hwOk!=NULL) && (hwCancel!=NULL) && (hwHelp!=NULL) )
	{
		CRect rectOk, rectCancel, rectHelp;

		::GetWindowRect(hwOk, &rectOk);
		ScreenToClient(&rectOk);
		::GetWindowRect(hwCancel, &rectCancel);
		ScreenToClient(&rectCancel);
		::GetWindowRect(hwHelp, &rectHelp);
		ScreenToClient(&rectHelp);

		int nSep = rectCancel.left - rectOk.left;	// distance between button lefts

		// now actually move them...
		::SetWindowPos(hwCancel, NULL, rectHelp.left - nSep, rectCancel.top, 
			0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
		::SetWindowPos(hwOk,	 NULL, rectHelp.left - (2*nSep), rectOk.top, 
			0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
	return bResult;
}

BOOL COptionsSheet::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	char progfile[MAX_PATH];
	char sPath[MAX_PATH];

	// Get the full path of the MouseTool.exe file
	if ( GetModuleFileName( NULL, sPath, MAX_PATH) != 0) {
		* ( strrchr( sPath, '\\' ) + 1 ) = '\0';
	}
	strcpy (progfile, sPath);
	strcat (progfile, "\\MouseTool.hlp>Wnd");		// does the string already end in "\" ?
	
	WinHelp(0x2066);

	return TRUE;
}

void COptionsSheet::WinHelp(DWORD dwData, UINT nCmd) 
{
	char progfile[MAX_PATH];
	char sPath[MAX_PATH];

	// Get the full path of the MouseTool.exe file
	if ( GetModuleFileName( NULL, sPath, MAX_PATH) != 0) {
		* ( strrchr( sPath, '\\' ) + 1 ) = '\0';
	}
	strcpy (progfile, sPath);

	if (progfile[strlen(progfile)] == '\\')		// append a backslash if needed
		strcat (progfile, "\\");

	strcat (progfile, "MouseTool.hlp>Wnd");		// does the string already end in "\" ?
	
	::WinHelp(m_hWnd, progfile, nCmd, dwData);
}

void COptionsSheet::OnHelpButton()
{
	WinHelp(0x2066);

	ASSERT_VALID(this);
	CPropertyPage* pPage = GetActivePage();
	ASSERT_VALID(pPage);
	if (*pPage==m_pgGeneral)
		WinHelp(0x20B3);
	if (*pPage==m_pgKeys)
		WinHelp(0x20B6);
	if (*pPage==m_pgContext)
		WinHelp(0x20B7);
//	return AfxCallWndProc(pPage, pPage->m_hWnd, WM_COMMANDHELP, wParam, lParam);
}

// We need to know the bounds of the system buttons so we can see
// if the user clicked on them.
void COptionsSheet::GetSysButtonBorder()
{
// Have to get size and position of caption buttons, relative to window.
// See "title bar size.txt" for details
	RECT rect;
	GetWindowRect(&rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);

	m_nxButtonLeft = w - 5 - ncm.iCaptionWidth;
	m_nqButtonLeft = w - 5 - 2*ncm.iCaptionWidth - 2;
}

void COptionsSheet::OnMouseMove(UINT nFlags, CPoint point) 
{
//	SetCursor(LoadCursor(NULL, IDC_HELP));	
//	CPropertySheet::OnMouseMove(nFlags, point);
}

BOOL COptionsSheet::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_pProcHandler->IsInHelpMode())
		SetCursor(LoadCursor(NULL, IDC_HELP));	
	else
		SetCursor(LoadCursor(NULL, IDC_ARROW));	
	
	return TRUE;
//	return CPropertySheet::OnSetCursor(pWnd, nHitTest, message);
}

void COptionsSheet::EnterHelpMode()
{
	if (!m_bMouseToolIsOn) 
	{
		char progfile[MAX_PATH];
		char sPath[MAX_PATH];

		// Get the full path of the MouseTool.exe file
		if ( GetModuleFileName( NULL, sPath, MAX_PATH) != 0) {
			* ( strrchr( sPath, '\\' ) + 1 ) = '\0';
		}
		strcpy (progfile, sPath);
		strcat (progfile, "\\MouseTool.hlp>Wnd");		// does the string already end in "\" ?
		
		::WinHelp(m_hWnd, progfile, HELP_CONTEXT, 999);
		return;
	}

	m_bInHelpMode = true;
	m_pProcHandler->EnterHelpMode();
//	((CMouseToolDlg *)m_pMouseToolWnd)->EnterHelpMode();
}

// These numbers were found empirically.
// See Translation.xls
long COptionsSheet::GetHelpMapOffset()
{
	int nIndex = GetActiveIndex();
	switch (nIndex) {
		case 0:
			return long(2159214592U);
		case 1:
			return long(2159411200U);
		case 2:
			return long(2159476736U);
	}

	return 0;
}

void COptionsSheet::OpenAtPage(int nPageIndex)
{
	m_nPageToOpen = nPageIndex;
}
