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

// KeyHandler.h: interface for the CKeyHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYHANDLER_H__A427A071_A4D1_11D1_8334_00207811D6EB__INCLUDED_)
#define AFX_KEYHANDLER_H__A427A071_A4D1_11D1_8334_00207811D6EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define KH_UNRECOGNIZED		0
#define KH_DBL_MODE_KEY		1
#define KH_RIGHT_MODE_KEY	2

class CKeyHandler  
{
public:
	bool IsPressed();
	int GetVKey();
	CKeyHandler();
	CKeyHandler(LONG);
	virtual ~CKeyHandler();
	int 	ProcessWParam(LONG);
	bool 	equals(CKeyHandler);
	CString GetWParamString();
	CString GetWParamString(LONG val);
	CString GetStrVal(int nKey);


	int m_vkey;
	bool m_bShift;
	bool m_bAlt;
	bool m_bCtrl;
};

#endif // !defined(AFX_KEYHANDLER_H__A427A071_A4D1_11D1_8334_00207811D6EB__INCLUDED_)
