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

// KeyHandler.cpp: implementation of the CKeyHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mtNTTest.h"
#include "KeyHandler.h"
#include <winuser.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKeyHandler::CKeyHandler()
{
	m_bShift = false;
	m_bAlt   = false;
	m_bCtrl  = false;
	m_vkey = 0;
}


CKeyHandler::CKeyHandler(LONG val)
{
	m_bShift = false;
	m_bAlt   = false;
	m_bCtrl  = false;
	m_vkey = val;
	
	if (GetAsyncKeyState(VK_SHIFT)<0) {
		m_bShift = true;
	}
	if (GetAsyncKeyState(VK_CONTROL)<0) {
		m_bCtrl  = true;
	}
	if (GetAsyncKeyState(VK_MENU)<0) {
		m_bAlt   = true;
	}
}


CKeyHandler::~CKeyHandler()
{

}

int CKeyHandler::ProcessWParam(LONG val)
{
	return val;
}

CString CKeyHandler::GetWParamString()
{
	if (m_vkey == 0)
		return "";

	CString str, strShift, strCtrl, strAlt, str2, strVal;

	if (m_bShift) {
		strShift = "Shift+ ";
	}
	if (m_bCtrl) {
		strCtrl  = "Control+ ";
	}
	if (m_bAlt) {
		strAlt   = "Alt+ ";
	}

	if ( ('0'<=m_vkey) && (m_vkey<='9') )			// it's a number
		strVal = m_vkey;
	else if ( ('A'<=m_vkey) && (m_vkey<='Z') )			// it's a letter
		strVal = m_vkey;
	else
		strVal = GetStrVal(m_vkey);

	str = strShift + strCtrl + strAlt + strVal;
	return str;

}

// call it with wParam set to the vkey value.
CString CKeyHandler::GetWParamString(LONG val)
{
	CString str, strShift, strCtrl, strAlt, str2, strVal;

	m_bShift = false;
	m_bAlt   = false;
	m_bCtrl  = false;
	m_vkey = val;
	
	if (GetAsyncKeyState(VK_SHIFT)<0) {
		m_bShift = true;
		strShift = "Shift+ ";
	}
	if (GetAsyncKeyState(VK_CONTROL)<0) {
		m_bCtrl  = true;
		strCtrl  = "Control+ ";
	}
	if (GetAsyncKeyState(VK_MENU)<0) {
		m_bAlt   = true;
		strAlt   = "Alt+ ";
	}

	if ( ('0'<=val) && (val<='9') )			// it's a number
		strVal = CString(char(val));
	else if ( ('A'<=val) && (val<='Z') )			// it's a letter
		strVal = CString(char(val));
	else
		strVal = GetStrVal(val);
//		strVal.Format("%d", val);

	str = strShift + strCtrl + strAlt + strVal;
//	str2.Format("%s %d", str, val);
	return str;
}


bool CKeyHandler::equals(CKeyHandler kh)
{
	if (m_vkey!=kh.m_vkey)
		return false;

	if (m_bShift!=kh.m_bShift)
		return false;

	if (m_bCtrl!=kh.m_bCtrl)
		return false;

	if (m_bAlt!=kh.m_bAlt)
		return false;

	return true;
}

CString CKeyHandler::GetStrVal(int nKey)
{
	CString str;
	
	switch (nKey)
	{
		case VK_BACK:
			str = "Backspace";
			break;
		case VK_TAB:
			str = "Tab";
			break;
		case VK_CLEAR:
			str = "Clear";
			break;
		case VK_RETURN:
			str = "Enter";
			break;
		case VK_PAUSE:
			str = "Pause";
			break;
		case VK_CAPITAL:
			str = "CapsLock";
			break;
		case VK_ESCAPE:
			str = "Escape";
			break;
		case VK_SPACE:
			str = "Space";
			break;
		case VK_PRIOR:
			str = "PageUp";
			break;
		case VK_NEXT:
			str = "PageDown";
			break;
		case VK_END:
			str = "End";
			break;
		case VK_HOME:
			str = "Home";
			break;
		case VK_LEFT:
			str = "Left";
			break;
		case VK_UP:
			str = "Up";
			break;
		case VK_RIGHT:
			str = "Right";
			break;
		case VK_DOWN:
			str = "Down";
			break;
		case VK_SNAPSHOT:
			str = "PrintScreen";
			break;
		case VK_INSERT:
			str = "Insert";
			break;
		case VK_DELETE:
			str = "Delete";
			break;
//		case VK_HELP:
//			str = "F1";
//			break;
		case VK_NUMPAD0:
			str = "Keypad0";
			break;
		case VK_NUMPAD1:
			str = "Keypad1";
			break;
		case VK_NUMPAD2:
			str = "Keypad2";
			break;
		case VK_NUMPAD3:
			str = "Keypad3";
			break;
		case VK_NUMPAD4:
			str = "Keypad4";
			break;
		case VK_NUMPAD5:
			str = "Keypad5";
			break;
		case VK_NUMPAD6:
			str = "Keypad6";
			break;
		case VK_NUMPAD7:
			str = "Keypad7";
			break;
		case VK_NUMPAD8:
			str = "Keypad8";
			break;
		case VK_NUMPAD9:
			str = "Keypad9";
			break;
		case VK_MULTIPLY:
			str = "Keypad *";
			break;
		case VK_ADD:
			str = "Keypad +";
			break;
		case VK_SUBTRACT:
			str = "Keypad -";
			break;
		case VK_DIVIDE:
			str = "Keypad /";
			break;
		case VK_F1:
			str = "F1";
			break;
		case VK_F2:
			str = "F2";
			break;
		case VK_F3:
			str = "F3";
			break;
		case VK_F4:
			str = "F4";
			break;
		case VK_F5:
			str = "F5";
			break;
		case VK_F6:
			str = "F6";
			break;
		case VK_F7:
			str = "F7";
			break;
		case VK_F8:
			str = "F8";
			break;
		case VK_F9:
			str = "F9";
			break;
		case VK_F10:
			str = "F10";
			break;
		case VK_F11:
			str = "F11";
			break;
		case VK_F12:
			str = "F12";
			break;
		case VK_F13:
			str = "F13";
			break;
		case VK_F14:
			str = "F14";
			break;
		case VK_F15:
			str = "F15";
			break;
		case VK_F16:
			str = "F16";
			break;
		case VK_NUMLOCK:
			str = "NumLock";
			break;
		case 0x91:
			str = "ScrollLock";				// Begin OEM-specific
			break;
		case 0xBA:
			str = ";";
			break;
		case 0xBB:
			str = "+";
			break;
		case 0xBC:
			str = ",";
			break;
		case 0xBD:
			str = "-";
			break;
		case 0xBE:
			str = ".";
			break;
		case 0xBF:
			str = "/";
			break;
		case 0xC0:
			str = "`";
			break;
		case 0xDB:
			str = "[";
			break;
		case 0xDC:
			str = "\\";
			break;
		case 0xDD:
			str = "]";
			break;
		case 0xDE:
			str = "'";
			break;
		default:
			break;
	}
	return str;
}	

int CKeyHandler::GetVKey()
{
	return(m_vkey);
	
}

bool CKeyHandler::IsPressed()
{
	if ( !(GetAsyncKeyState(m_vkey) & 0x8000) )
		return(false);

	if (m_bAlt)
		if (!(GetAsyncKeyState(VK_MENU) & 0x8000) )
			return(false);

	if (m_bCtrl)
		if (!(GetAsyncKeyState(VK_CONTROL) & 0x8000) )
			return(false);

	if (m_bShift)
		if (!(GetAsyncKeyState(VK_CONTROL) & 0x8000) )
			return(false);
		
	return(true);
}

