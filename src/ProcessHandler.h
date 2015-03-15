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

// ProcessHandler.h: interface for the CProcessHandler class.
//
//////////////////////////////////////////////////////////////////////

#include <afxtempl.h>
//#include <map>
#include "ClickInfo.h"
// using namespace std;

#if !defined(AFX_PROCESSHANDLER_H__C791C97F_998C_11D1_82D9_000000000000__INCLUDED_)
#define AFX_PROCESSHANDLER_H__C791C97F_998C_11D1_82D9_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef	BOOL (WINAPI* LPFOREAPP)(char *, int);
typedef	BOOL (WINAPI* LPGETWINAPP)(HWND, char *, int);

#include "constants.h"

class CProcessHandler  
{
	int			m_nNumContexts;
	int 		m_nCurrentClickType;
	int 		m_nCurrentContext;
	bool 		m_bDLLLoaded;
	bool		m_bOverride;
	HMODULE 	hModDLL;
	CMap<CString, LPCSTR, CClickInfo, const CClickInfo&> m_mApps;
	CMap<CString, LPCSTR, CClickInfo, const CClickInfo&> m_mClasses;
	CMap<CString, LPCSTR, CClickInfo, const CClickInfo&> m_mClassesBackup;

	bool		m_bInHelpMode;
	bool		m_bPressingButton;
	bool		m_bUserIsClicking;
	int			m_nSentClickCount;

public:
	void RestoreDefaultContexts();
	void ClearClickCount();
	void		IncClickCount();
	int			DecClickCount();
	bool		m_bAlertNCIsShowing;
	bool		UserIsClicking();

	void		ToggleOverrideNextOnly();
	void		SetOverrideNextOnly(bool);
	bool 		GetOverrideNextOnly();
	void 		ResetOverrideNextOnly();
	void		SetEnableContext(bool);
	void 		ResetOverride();
	void		EnterHelpMode();
	void		ExitHelpMode();
	bool		IsInHelpMode();
	bool 		IsMouseToolWnd(HWND hWnd);
	int			GetChildHelpIdAtMouse();
	int			GetNumContexts();
	bool		GetPressingButton();
	void		SetPressingButton(bool);

	// These let us cancel changes made in COptContext
	void		MakeBackupContextMap();
	void		RestoreContextsFromBackup();
	
	bool		m_bOverrideNextOnly;
	bool		m_bSmartDragEnabled;
	bool		m_bEnableContext;
//	bool		m_bEnableContexts;
	CString 	m_PrevClassUnderMouse;
	CString		strSeparator;

	// save to and load from the registry
	bool 		SaveContexts(int);
	void 		LoadContexts();

	BOOL 		DeleteClassContext(CString);
	int			GetClickType();
	int			GetClassContext(CString key);
	bool		GetClassClickInfo(CString key,CClickInfo &ci);
	int 		GetMouseContext();
	bool		GetMouseClickInfo(CClickInfo &ci);
	bool		GetWindowClickInfo(HWND hWnd,CClickInfo &ci);
	int 		GetAppContext(CString);
	int 		GetLeftClickType();
	int 		GetDblClickType();
	int 		GetRightClickType();
	CString 	GetForeApp();
	CString 	WinNameFromPt();
	void		SetClickType(int);
	void		SetClassAtMouse();
	void 		SetAppContext(const char *, const int);
	void 		SetClassContext(const char *, const int);
	bool		SetClassClickInfo(const char *key,const CClickInfo &ci);
	bool 		AddAppsToListBox(CListBox &);
	bool 		AddClassesToListBox(CListBox &);
	bool 		InDragMode();
	void		OnClickHook(int nIsDown, UINT wParam, LONG lParam);


	virtual 	~CProcessHandler();
				CProcessHandler();

};

#endif // !defined(AFX_PROCESSHANDLER_H__C791C97F_998C_11D1_82D9_000000000000__INCLUDED_)


