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

// Clicker.h: interface for the CClicker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLICKER_H__C40DF3C1_BDE6_11D2_8764_006008C4A90D__INCLUDED_)
#define AFX_CLICKER_H__C40DF3C1_BDE6_11D2_8764_006008C4A90D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClicker  
{
public:
	CClicker();
	virtual ~CClicker();

	bool m_bButtonsReversed;
	void click(int nClickType, int x, int y);
private:
	static UINT ClickThread(LPVOID);
};

#define LEFTDOWN	0
#define LEFTUP		1
#define LEFTCLICK	2
#define RIGHTDOWN	3
#define RIGHTUP		4
#define RIGHTCLICK	5


#endif // !defined(AFX_CLICKER_H__C40DF3C1_BDE6_11D2_8764_006008C4A90D__INCLUDED_)
