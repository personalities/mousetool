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

// DlgWarnLeftHotkey.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "DlgWarnLeftHotkey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWarnLeftHotkey dialog


CDlgWarnLeftHotkey::CDlgWarnLeftHotkey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWarnLeftHotkey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWarnLeftHotkey)
	m_bDontShowAgain = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgWarnLeftHotkey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWarnLeftHotkey)
	DDX_Check(pDX, IDC_CK_DONT_SHOW_AGAIN, m_bDontShowAgain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWarnLeftHotkey, CDialog)
	//{{AFX_MSG_MAP(CDlgWarnLeftHotkey)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_NCLBUTTONDOWN, ncLDown )
	ON_MESSAGE( WM_NCLBUTTONUP, ncLUp )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWarnLeftHotkey message handlers

void CDlgWarnLeftHotkey::ncLUp(UINT nHitTest, POINTS point)
{

}


void CDlgWarnLeftHotkey::ncLDown(UINT nHitTest, POINTS point)
{

}
