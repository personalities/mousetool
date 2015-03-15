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

// DlgWndTypeDesc.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "DlgWndTypeDesc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWndTypeDesc dialog


CDlgWndTypeDesc::CDlgWndTypeDesc(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWndTypeDesc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWndTypeDesc)
	m_edtDescription = _T("");
	//}}AFX_DATA_INIT
}


void CDlgWndTypeDesc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWndTypeDesc)
	DDX_Text(pDX, IDC_EDT_TYPE_DESCRIPTION, m_edtDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWndTypeDesc, CDialog)
	//{{AFX_MSG_MAP(CDlgWndTypeDesc)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_NCLBUTTONDOWN, 	OnNCLDown )
	ON_MESSAGE( WM_NCLBUTTONUP, 	OnNCLUp )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWndTypeDesc message handlers


// Monitor nonclient mouse messages.
// If the user minimizes or closes, handle it here.
// (Otherwise the program waits on the up click before processing timer...)
void CDlgWndTypeDesc::OnNCLDown(UINT nHitTest, POINTS point)
{

}


void CDlgWndTypeDesc::OnNCLUp(UINT nHitTest, POINTS point)
{
}
