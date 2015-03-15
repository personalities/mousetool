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

// DlgAlertSmartDrag.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "DlgAlertSmartDrag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlertSmartDrag dialog


CDlgAlertSmartDrag::CDlgAlertSmartDrag(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlertSmartDrag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlertSmartDrag)
	m_bDontRemind = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAlertSmartDrag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlertSmartDrag)
	DDX_Check(pDX, IDC_CK_DONT_REMIND, m_bDontRemind);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlertSmartDrag, CDialog)
	//{{AFX_MSG_MAP(CDlgAlertSmartDrag)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_NCLBUTTONDOWN, ncLDown )
	ON_MESSAGE( WM_NCLBUTTONUP, ncLUp )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlertSmartDrag message handlers

int CDlgAlertSmartDrag::DoModal() 
{
	if (m_bDontRemind)
		return IDOK;
	
	return CDialog::DoModal();
}

void CDlgAlertSmartDrag::ncLDown(UINT nHitTest, POINTS point)
{

}

void CDlgAlertSmartDrag::ncLUp(UINT nHitTest, POINTS point)
{

}
