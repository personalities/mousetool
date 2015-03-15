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

// Splash.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
//#include "Splash.h"
#include "constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplash dialog


CSplash::CSplash(CWnd* pParent /*=NULL*/)
	: CDialog(CSplash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplash)
	m_strVersion = _T("");
	//}}AFX_DATA_INIT
}


void CSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplash)
	DDX_Text(pDX, IDC_STATIC_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplash, CDialog)
	//{{AFX_MSG_MAP(CSplash)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplash message handlers

BOOL CSplash::Create(CWnd* pParentWnd) 
{

	return CDialog::Create(IDD, pParentWnd);
}


void CSplash::UpdateStatic(int n)
{
	CString str;

	str.Format("Count: %d", n);
//	m_Static1Control.SetWindowText(str);
}

void CSplash::OnTimer(UINT nIDEvent) 
{
	static int count = 0;

	if (nIDEvent == SPLASH_TIMER_ID)
		if (count++ > 4) {
			KillTimer(SPLASH_TIMER_ID);
			DestroyWindow();
		} else 
			CDialog::OnTimer(nIDEvent);
}

void CSplash::PostNcDestroy() 
{
//	delete this;			// do this if referenced only by pointers.
	
	CDialog::PostNcDestroy();
}

BOOL CSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	int nWidth = 375;
	int nHeight = 74;

	SetWindowPos(&wndTop, (nScreenWidth-nWidth)/2,(nScreenHeight-nHeight)/2, 375,74, SWP_NOOWNERZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSplash::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap bmp;
	bmp.LoadBitmap(IDB_SPLASH);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SelectObject(&bmp);


	dc.BitBlt(0,0, 375,74, &dcMem, 0,0, SRCCOPY);
	dc.SetBkColor(0x00ccffff);
	CString strVersion;

	strVersion.Format("Version %s", VERSION);

	CFont font;
	font.CreatePointFont(100, "Arial", &dc);		// arial, 10pt
	dc.SelectObject(font);
	dc.TextOut(10,55, strVersion);




//	dc.ExtTextOut(10,55, 0, NULL, strVersion, NULL);
}
