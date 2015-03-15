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

// DlgOldSystemFiles.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "DlgOldSystemFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOldSystemFiles dialog


CDlgOldSystemFiles::CDlgOldSystemFiles(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOldSystemFiles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOldSystemFiles)
	m_strComUpdate = _T("");
	//}}AFX_DATA_INIT
}


void CDlgOldSystemFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOldSystemFiles)
	DDX_Text(pDX, IDC_STAT_COMUPD, m_strComUpdate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOldSystemFiles, CDialog)
	//{{AFX_MSG_MAP(CDlgOldSystemFiles)
	ON_BN_CLICKED(IDC_BUTTON_GET_FILES, OnButtonGetFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOldSystemFiles message handlers

void CDlgOldSystemFiles::OnButtonGetFiles() 
{
	ShellExecute(m_hWnd, "open", "http://www.mousetool.com/updates.html", 0, "", 0);	
}
