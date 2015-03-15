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

// TempStrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "TempStrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTempStrDlg dialog


CTempStrDlg::CTempStrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTempStrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTempStrDlg)
	m_TempStr = _T("");
	//}}AFX_DATA_INIT
}


void CTempStrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTempStrDlg)
	DDX_Text(pDX, IDC_EDTTEMP_STR, m_TempStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTempStrDlg, CDialog)
	//{{AFX_MSG_MAP(CTempStrDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTempStrDlg message handlers
