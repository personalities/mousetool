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

// ModeChanger.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "ModeChanger.h"
#include "constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeChanger

CModeChanger::CModeChanger()
{
}

CModeChanger::~CModeChanger()
{
	m_bitmap.DeleteObject();
}


BEGIN_MESSAGE_MAP(CModeChanger, CStatic)
	//{{AFX_MSG_MAP(CModeChanger)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeChanger message handlers


void CModeChanger::SetBitmaps(UINT unFlat, UINT unUp, UINT unDown, UINT unInactive, UINT unDrag)
{
	m_unFlat     = unFlat;
	m_unUp       = unUp;
	m_unDown     = unDown;
	m_unInactive = unInactive;
	m_unDrag	 = unDrag;

	m_unCurrent	 = m_unFlat;
#if defined EYE_TRACKING
	SetWindowPos(&wndTop, 1,1, 22, 100, SWP_NOMOVE);
#endif
}

void CModeChanger::SetImage(UINT unBitmapNum)
{
	m_bitmap.DeleteObject();
//	HBITMAP hb;
//	hb = (HBITMAP) LoadImage( AfxGetApp()->m_hInstance, 
//					MAKEINTRESOURCE(unBitmapNum),
//					IMAGE_BITMAP,
//					22,19,
//					LR_LOADTRANSPARENT |
//					LR_DEFAULTCOLOR
//				   );
//
//	m_bitmap.FromHandle(hb);
	m_bitmap.LoadMappedBitmap(unBitmapNum);
	SetBitmap(m_bitmap);
#if defined EYE_TRACKING
//	SetWindowPos(&wndTop, 1,1, 22, 100, SWP_NOMOVE);
#endif
}

void CModeChanger::Flatten()
{
	if (m_unCurrent == m_unFlat)	// 12-3-97
		return;

	m_unCurrent = m_unFlat;
	SetImage(m_unCurrent);
}

void CModeChanger::Up()
{
	if (m_unCurrent == m_unUp)		// 12-3-97
		return;

	if (m_unCurrent != m_unDown)
		SetImage(m_unUp);
}

void CModeChanger::Down()
{
	if (m_unCurrent == m_unDown)	// 12-3-97
		return;

	m_unCurrent = m_unDown;
	SetImage(m_unCurrent);
}

void CModeChanger::Activate(bool bActivate)
{
	m_nTicksWithFocus = 0;		// Activate is called when mouse is found outside of app window

	if (bActivate) {
		SetImage(m_unCurrent);
	} else {
		SetImage(m_unInactive);
	}
}

void CModeChanger::SetDrag(bool bDrag)
{
	if (bDrag) {
		SetImage(m_unDrag);
	} else {
		SetImage(m_unCurrent);
	}
}

void CModeChanger::SetDelay(const int &TicksToWait)
{
//	CString str;
//	str.Format("TicksToWait = %d", TicksToWait);
//	MessageBox(str);

	m_TicksToWait = TicksToWait;
	m_nTicksWithFocus = 0;
}

// called when mouse is in app window.  
// bMouseInRect indicates whether mouse is in this object or not
bool CModeChanger::Timer(const bool &bMouseInRect)
{
	return false;

	if (bMouseInRect) {
		m_nTicksWithFocus++;
		if (m_nTicksWithFocus > m_TicksToWait) {
			m_nTicksWithFocus = m_TicksToWait;
			return true;
		}
	} else
		m_nTicksWithFocus = 0;

	return false;
}

void CModeChanger::ClickedOn()
{
	m_unCurrent = m_unDown;
}