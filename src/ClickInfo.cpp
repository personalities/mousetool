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

// ClickInfo.cpp: implementation of the CClickInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mtNTTest.h"
#include "ClickInfo.h"

#define LEFTMODE	0
#define DOUBLEMODE	1
#define DRAGMODE	2
#define RIGHTMODE	3


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClickInfo::CClickInfo()
{
	nDefaultClickType = LEFTMODE;
	nContext = CONTEXT_DEFAULT;
	bDontDragInScrollbars=false;
}

CClickInfo::~CClickInfo()
{

}
