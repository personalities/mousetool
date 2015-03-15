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

// AbtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "MouseToolDlg.h"
#include "AbtDlg.h"
#include "constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbtDlg dialog


CAbtDlg::CAbtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAbtDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbtDlg)
	m_strVersion = _T("");
	//}}AFX_DATA_INIT
	m_bNCDragging = false;
}


void CAbtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbtDlg)
	DDX_Control(pDX, IDC_STATIC1, m_Static1Control);
	DDX_Text(pDX, IDC_STATIC_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbtDlg, CDialog)
	//{{AFX_MSG_MAP(CAbtDlg)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_NCLBUTTONDOWN, 	OnNCLDown )
	ON_MESSAGE( WM_NCLBUTTONUP, 	OnNCLUp )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbtDlg message handlers

BOOL CAbtDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_strVersion = CString("MouseTool Version ") + CString(VERSION);
	UpdateData(FALSE);

	CString str;

	str = "MouseTool is donationware.  Please use it and share it freely with anyone who might find it useful.  If you find that it helps you, please consider making a $20 donation to a charity of your choice.  Enjoy!";

	m_Static1Control.SetWindowText(str);

	return TRUE; 
}

/*---------------------------------------------**
** This event happens whenever the mouse moves **
**---------------------------------------------*/
LONG CAbtDlg::OnHook(UINT wParam, LONG lParam)
{
	if (!m_hWnd)
		return 0;
		
	
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

void CAbtDlg::OnNCLUp(UINT nHitTest, POINTS point)
{
	/*
	if (m_bStopDragging)
		m_bNCDragging = false;					// Handle dragging of MT ourselves
	m_bStopDragging = true;
	*/
}

// Monitor nonclient mouse messages.
// If the user minimizes or closes, handle it here.
// (Otherwise the program waits on the up click before processing timer...)
void CAbtDlg::OnNCLDown(UINT nHitTest, POINTS point)
{
/*
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

	// handle dragging	
	m_bNCDragging = true;					 
	m_bStopDragging = false;
	((CMouseToolDlg *)GetParent())->MouseLUp();						   
	
	m_ptDragStartPointMouse.x = point.x;
	m_ptDragStartPointMouse.y = point.y;
	GetWindowRect(&rect);
	m_ptDragStartPointWnd.x = rect.left;
	m_ptDragStartPointWnd.y = rect.top;
*/
}
