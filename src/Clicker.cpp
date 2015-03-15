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

// Clicker.cpp: implementation of the CClicker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "MouseHook.h"
#include "Clicker.h"

LRESULT	CALLBACK ClickMouseProc (int nCode, WPARAM wParam, LPARAM lParam );
HHOOK hHook;
UINT uMessage;
int nClicksLeft;
int nXpos, nYpos;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClicker::CClicker()
{
	hHook = 0;
}

CClicker::~CClicker()
{

}

void CClicker::click(int nClickType, int x, int y) 
{
	if (m_bButtonsReversed) 
		switch (nClickType)
		{
		case LEFTDOWN:
			nClickType = RIGHTDOWN;
			break;
		case LEFTUP:
			nClickType = RIGHTUP;
			break;
		case LEFTCLICK:
			nClickType = RIGHTCLICK;
			break;
		case RIGHTDOWN:
			nClickType = LEFTDOWN;
			break;
		case RIGHTUP:
			nClickType = LEFTUP;
			break;
		case RIGHTCLICK:
			nClickType = LEFTCLICK;
			break;
		}


	// can we get threading to help the RICHEDIT bug?
//		AfxBeginThread(CClicker::ClickThread, (LPVOID) nClickType);
//		return;


// Two ways of generating clicks.
// Comment out the first or last section to choose.

////////////////////////////////////////////////////////////////
// First method of generating clicks
	// Left click messages

	if (nClickType == LEFTDOWN) 
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, GetMessageExtraInfo());

	if (nClickType == LEFTUP) 
		mouse_event(MOUSEEVENTF_LEFTUP,   x, y, 0, GetMessageExtraInfo());

	if (nClickType == LEFTCLICK) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_LEFTUP,   x, y, 0, GetMessageExtraInfo());
	}

	// Right click messages
	if (nClickType == RIGHTDOWN) 
		mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, GetMessageExtraInfo());

	if (nClickType == RIGHTUP) 
		mouse_event(MOUSEEVENTF_RIGHTUP,   x, y, 0, GetMessageExtraInfo());

	if (nClickType == RIGHTCLICK) {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_RIGHTUP,   x, y, 0, GetMessageExtraInfo());
	}
	
// First method ends
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
// Second method of generating clicks
/*
	if (hHook)
		return;

	nXpos = x;
	nYpos = y;

	// Left click messages
	if (nClickType == LEFTDOWN) {
		nClicksLeft = 1;
		uMessage = WM_LBUTTONDOWN;
	}
	if (nClickType == LEFTUP) {
		nClicksLeft = 1;
		uMessage = WM_LBUTTONUP;
	}
	if (nClickType == LEFTCLICK) {
		nClicksLeft = 2;
		uMessage = WM_LBUTTONDOWN;
	}

	// Right click messages
	if (nClickType == RIGHTDOWN) {
		nClicksLeft = 1;
		uMessage = WM_RBUTTONDOWN;
	}
	if (nClickType == RIGHTUP) {
		nClicksLeft = 1;
		uMessage = WM_RBUTTONUP;
	}
	if (nClickType == RIGHTCLICK) {
		nClicksLeft = 2;
		uMessage = WM_RBUTTONDOWN;
	}
	

	
	hHook = SetWindowsHookEx(WH_JOURNALPLAYBACK, 
								 (HOOKPROC) ClickMouseProc, 
								 AfxGetApp()->m_hInstance, 
								 0);
*/
// Second method ends
////////////////////////////////////////////////////////////////

}


LRESULT	CALLBACK ClickMouseProc (int nCode, WPARAM wParam, LPARAM lParam )
{
	LPEVENTMSG lpEvent;

	if (nCode>0) 
	{

		if (nCode==HC_GETNEXT) {
			lpEvent = (LPEVENTMSG) lParam;
			lpEvent->message = uMessage;
			lpEvent->paramL  = nXpos;
			lpEvent->paramH  = nYpos;
			lpEvent->time    = 0;
		}

		if (nCode==HC_SKIP) {
			nClicksLeft--;
			if (!nClicksLeft)
			{
				UnhookWindowsHookEx(hHook);
				hHook = NULL;
			}
			else {										// we need to send an upclick
				if (uMessage == WM_LBUTTONDOWN)
					uMessage = WM_LBUTTONUP;			// left
				else
					uMessage = WM_RBUTTONUP;			// right
			}
		}

	}
	return (CallNextHookEx(hHook, nCode, wParam, lParam));
}

UINT CClicker::ClickThread(LPVOID pParam)
{
	int nClickType = (int) pParam;

	POINT MousePos;
	GetCursorPos(&MousePos);

	if (nClickType == LEFTDOWN) 
		mouse_event(MOUSEEVENTF_LEFTDOWN, MousePos.x, MousePos.y, 0, GetMessageExtraInfo());

	if (nClickType == LEFTUP) 
		mouse_event(MOUSEEVENTF_LEFTUP,   MousePos.x, MousePos.y, 0, GetMessageExtraInfo());

	if (nClickType == LEFTCLICK) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, MousePos.x, MousePos.y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_LEFTUP,   MousePos.x, MousePos.y, 0, GetMessageExtraInfo());
	}

	// Right click messages
	if (nClickType == RIGHTDOWN) 
		mouse_event(MOUSEEVENTF_RIGHTDOWN, MousePos.x, MousePos.y, 0, GetMessageExtraInfo());

	if (nClickType == RIGHTUP) 
		mouse_event(MOUSEEVENTF_RIGHTUP,   MousePos.x, MousePos.y, 0, GetMessageExtraInfo());

	if (nClickType == RIGHTCLICK) {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, MousePos.x, MousePos.y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_RIGHTUP,   MousePos.x, MousePos.y, 0, GetMessageExtraInfo());
	}
	

	return 0;
}
