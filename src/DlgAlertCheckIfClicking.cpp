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

// DlgAlertCheckIfClicking.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "DlgAlertCheckIfClicking.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlertCheckIfClicking dialog


CDlgAlertCheckIfClicking::CDlgAlertCheckIfClicking(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlertCheckIfClicking::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlertCheckIfClicking)
	m_bDontWarn = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAlertCheckIfClicking::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlertCheckIfClicking)
	DDX_Check(pDX, IDC_CK_DONT_WARN_CK_CLICK, m_bDontWarn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlertCheckIfClicking, CDialog)
	//{{AFX_MSG_MAP(CDlgAlertCheckIfClicking)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlertCheckIfClicking message handlers


int CDlgAlertCheckIfClicking::DoModal() 
{
	if (m_bDontWarn)
		return IDOK;

	return CDialog::DoModal();
}
