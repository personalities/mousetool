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

////////////////////////////////////////////////////////////////
// CTrayIcon Copyright 1996 Microsoft Systems Journal.
//
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.

#include "stdafx.h"
#include "trayicon.h"
#include "resource.h"
#include <afxpriv.h>		// for AfxLoadString

CWnd *pWnd;

IMPLEMENT_DYNAMIC(CTrayIcon, CCmdTarget)

CTrayIcon::CTrayIcon(UINT uID)
{
	m_bInTray = false;

	// Initialize NOTIFYICONDATA
	memset(&m_nid, 0 , sizeof(m_nid));
	m_nid.cbSize = sizeof(m_nid);
	m_nid.uID = uID;	// never changes after construction

	// Use resource string as tip if there is one
	AfxLoadString(uID, m_nid.szTip, sizeof(m_nid.szTip));
}

CTrayIcon::~CTrayIcon()
{
	SetIcon(0); // remove icon from system tray
}

//////////////////
// Set notification window. It must created already.
//
void CTrayIcon::SetNotificationWnd(CWnd* pNotifyWnd, UINT uCbMsg)
{
	// If the following assert fails, you're probably
	// calling me before you created your window. Oops.
	ASSERT(pNotifyWnd==NULL || ::IsWindow(pNotifyWnd->GetSafeHwnd()));
	m_nid.hWnd = pNotifyWnd->GetSafeHwnd();

	pWnd = pNotifyWnd;

	ASSERT(uCbMsg==0 || uCbMsg>=WM_USER);
	m_nid.uCallbackMessage = uCbMsg;
}

//////////////////
// This is the main variant for setting the icon.
// Sets both the icon and tooltip from resource ID
// To remove the icon, call SetIcon(0)
//
BOOL CTrayIcon::SetIcon(UINT uID)
{ 
	m_bInTray = false;

	HICON hicon=NULL;
	if (uID) {
		m_bInTray = true;
		AfxLoadString(uID, m_nid.szTip, sizeof(m_nid.szTip));
		hicon = AfxGetApp()->LoadIcon(uID);
	}
	return SetIcon(hicon, NULL);
}

//////////////////
// Common SetIcon for all overloads. 
//
BOOL CTrayIcon::SetIcon(HICON hicon, LPCSTR lpTip) 
{
	UINT msg;
	m_nid.uFlags = 0;

	// Set the icon
	if (hicon) {
		m_bInTray = true;
		// Add or replace icon in system tray
		msg = m_nid.hIcon ? NIM_MODIFY : NIM_ADD;
		m_nid.hIcon = hicon;
		m_nid.uFlags |= NIF_ICON;
	} else { // remove icon from tray
		m_bInTray = false;
		if (m_nid.hIcon==NULL)
			return TRUE;		// already deleted
		msg = NIM_DELETE;
	}

	// Use the tip, if any
	if (lpTip)
		strncpy(m_nid.szTip, lpTip, sizeof(m_nid.szTip));
	if (m_nid.szTip[0])
		m_nid.uFlags |= NIF_TIP;

	// Use callback if any
	if (m_nid.uCallbackMessage && m_nid.hWnd)
		m_nid.uFlags |= NIF_MESSAGE;

	// Do it
	BOOL bRet = Shell_NotifyIcon(msg, &m_nid);
	if (msg==NIM_DELETE || !bRet)
		m_nid.hIcon = NULL;	// failed
	return bRet;
}

/////////////////
// Default event handler handles right-menu and doubleclick.
// Call this function from your own notification handler.
//
LRESULT CTrayIcon::OnTrayNotification(WPARAM wID, LPARAM lEvent)
{
	if (wID!=m_nid.uID || (lEvent!=WM_RBUTTONUP && lEvent!=WM_LBUTTONDBLCLK))
		return 0;

	// If there's a resource menu with the same ID as the icon, use it as 
	// the right-button popup menu. CTrayIcon will interprets the first
	// item in the menu as the default command for WM_LBUTTONDBLCLK
	// 

	CMenu menu;
	CMenu optionsMenu;

	menu.CreatePopupMenu( );
	optionsMenu.CreatePopupMenu( );
	optionsMenu.AppendMenu(MF_STRING, ID_TRAYMENU_OPENGENERAL, "General Options");
	optionsMenu.AppendMenu(MF_STRING, ID_TRAYMENU_OPENKEYS, "Hotkeys Options");
	optionsMenu.AppendMenu(MF_STRING, ID_TRAYMENU_OPENCONTEXT, "Context Options");

	if (m_bMouseToolIsGoing)
		menu.AppendMenu(MF_STRING | MF_ENABLED, ID_TRAYMENU_STOPMOUSETOOL, "Stop MouseTool");
	else
		menu.AppendMenu(MF_STRING | MF_ENABLED, ID_TRAYMENU_STOPMOUSETOOL, "Start MouseTool");

	menu.AppendMenu(MF_STRING, ID_TRAYMENU_CLOSEMOUSETOOL, "Close MouseTool");
	menu.AppendMenu(MF_STRING, ID_TRAYMENU_RESTORE, "Restore from Tray");
	menu.AppendMenu(MF_STRING, ID_TRAYMENU_LEFTCLICK, "Left Click");
	menu.AppendMenu(MF_STRING, ID_TRAYMENU_RIGHTCLICK, "Right click");
	menu.AppendMenu(MF_STRING, ID_TRAYMENU_DOUBLECLICK, "Double click");
/*
	if (m_bOverrideNextOnly)
		menu.AppendMenu(MF_STRING, ID_TRAYMENU_NEXTONLY, "Make changes permanent");
	else
		menu.AppendMenu(MF_STRING, ID_TRAYMENU_NEXTONLY, "Make changes for next only");
*/

	menu.AppendMenu(MF_POPUP, (UINT)optionsMenu.GetSafeHmenu(), "Options");

	if (lEvent==WM_LBUTTONDBLCLK)		 // double click: execute first menu item
		::SendMessage(m_nid.hWnd, WM_COMMAND, menu.GetMenuItemID(0), 0);
	else {
		// Make first menu item the default (bold font)
		::SetMenuDefaultItem(menu.m_hMenu, 0, TRUE);

		// Display the menu at the current mouse location. There's a "bug"
		// (Microsoft calls it a feature) in Windows 95 that requires calling
		// SetForegroundWindow. To find out more, search for Q135788 in MSDN.
		//
		CPoint mouse;
		GetCursorPos(&mouse);
		::SetForegroundWindow(m_nid.hWnd);	
		TrackPopupMenu(menu.m_hMenu, 0, mouse.x, mouse.y, 0, m_nid.hWnd, NULL);
	} 

	return 1; // handled
}

void CTrayIcon::SetFlags(bool bIsGoing, bool bNextOnly)
{
	m_bMouseToolIsGoing = bIsGoing;
	m_bOverrideNextOnly = bNextOnly;
}

bool CTrayIcon::IsInTray()
{
	return m_bInTray;
}
