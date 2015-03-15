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

// ProcessHandler.cpp: implementation of the CProcessHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DlgWndTypeDesc.h"
#include "ProcessHandler.h"
#include "clickinfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//The key for the list of classes for which smart drag in scrollbars hsould be disabled.
static const char *NO_SMART_SCROLL_KEY="NoSmartScroll";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcessHandler::CProcessHandler()
{
//	m_bEnableContexts = true;
	m_nCurrentClickType = DRAGMODE;
	strSeparator = " -- ";
	m_nCurrentContext = CONTEXT_DEFAULT;
	m_bEnableContext = true;
	m_bPressingButton = false;
	m_bUserIsClicking = false;
	m_nSentClickCount = 0;
	m_bOverride = false;
		
	// preload a few classes for testing
	CClickInfo ci;
	ci.strExeName = "Class";
	ci.strWinName = "Class";
	ci.nContext = CONTEXT_DOUBLE_CLICK;

	LoadContexts();

}

CProcessHandler::~CProcessHandler()
{
//	FreeLibrary(hModDLL);
}


bool CProcessHandler::AddAppsToListBox(CListBox &lst)
{
	POSITION pos;
	CString str;
	CClickInfo ci;

	// First, clear the box
	while (lst.GetCount())
		lst.DeleteString(0);

	// Then add elements
	pos = m_mApps.GetStartPosition();
	while (pos) {
		m_mApps.GetNextAssoc(pos, str, ci);
		str += ": ";
		str += ci.strWinName;
		lst.AddString(str);
	}
	return true;
}

bool CProcessHandler::AddClassesToListBox(CListBox &lst)
{
	POSITION pos;
	CString str;
	CClickInfo ci;

	// First, clear the box
	while (lst.GetCount())
		lst.DeleteString(0);

	// Then add elements
	pos = m_mClasses.GetStartPosition();
	m_nNumContexts = 0;
	while (pos) {
		m_nNumContexts++;
		m_mClasses.GetNextAssoc(pos, str, ci);
		ci.strWinName = "Comment goes here";
		str += strSeparator;
		str += ci.strComment;
		lst.AddString(str);
	}
	return true;
}

bool CProcessHandler::InDragMode()
{
	return false;
}

int CProcessHandler::GetNumContexts()
{
	return m_nNumContexts;
}

int CProcessHandler::GetLeftClickType()
{
	return LEFTMODE;
}

int CProcessHandler::GetDblClickType()
{
	return DOUBLEMODE;
}

int CProcessHandler::GetRightClickType()
{
	return RIGHTMODE;
}

// set the context for the app with exename of key
void CProcessHandler::SetAppContext(const char *key, const int nContext)
{
	CClickInfo ci;

	if (m_mApps.Lookup(key, ci)) {		// this should always be true
		ci.nContext = nContext;
		m_mApps.SetAt(key, ci);
	} 
}
// set the context for the class with classname of key
void CProcessHandler::SetClassContext(const char *key, const int nContext)
{
	CClickInfo ci;

	if (m_mClasses.Lookup(key, ci)) {		 // if it is already defined
			ci.nContext = nContext;
			m_mClasses.SetAt(key, ci);
	} else {
		CDlgWndTypeDesc dlg;
		if (dlg.DoModal()==IDOK) 
		{
			CClickInfo ci2;				// I don't _know_ that ci is still defined
			ci2.nContext = nContext;
			ci2.strWinName = "Class";
			ci2.strComment = dlg.m_edtDescription;
			m_mClasses.SetAt(key, ci2);
		}
	}
}

bool CProcessHandler::SetClassClickInfo(const char *key,const CClickInfo &ci)
{
	CClickInfo tmp;
	if(m_mClasses.Lookup(key,tmp)) {
		m_mClasses.SetAt(key,ci);
		return true;
	}
	return false;
}

int CProcessHandler::GetAppContext(CString key)
{
	CClickInfo ci;

	if (m_mApps.Lookup(key, ci)) {		// this should always be true
		return ci.nContext;
	} 
	return CONTEXT_DEFAULT;				// but if it's NOT, return default
}

int CProcessHandler::GetClassContext(CString key)
{
	CClickInfo ci;

//	AfxMessageBox(key);
	if (m_mClasses.Lookup(key, ci)) {	
		return ci.nContext;
	} 
//	AfxMessageBox("Can't find class.  Returning default.");
	return CONTEXT_DEFAULT;				// but if it's NOT, return default
}

bool CProcessHandler::GetClassClickInfo(CString key,CClickInfo &ci) {
	return !!m_mClasses.Lookup(key,ci);
}

/*
int CProcessHandler::GetMouseContext()
{
	POINT MousePt;
	char buf[MAX_PATH];
	CClickInfo ci;

	// Get the class name
	GetCursorPos(&MousePt);
	HWND hWnd = ::WindowFromPoint(MousePt);
	if (IsMouseToolWnd(hWnd)) {
		if (m_bInHelpMode) {
			m_nCurrentContext = CONTEXT_HELPMODE;
			return CONTEXT_HELPMODE;
		}
		m_nCurrentContext = CONTEXT_DEFAULT;
		return CONTEXT_DEFAULT;
	}
//		AfxMessageBox("MouseTool Window");			// qqqq
	GetClassName(hWnd, buf, MAX_PATH);

	// check if a context is defined for that class
	if (m_mClasses.Lookup(buf, ci)) {
		if (ci.nContext>4) {				 
			AfxMessageBox("Context out of range");
			exit(0);
		}
		if (ci.nContext<0) {
			AfxMessageBox("Context out of range");
			exit(0);
		}
		m_nCurrentContext = ci.nContext;
//	return 2;				// qqqqq
		return m_nCurrentContext;
	}

	m_nCurrentContext = CONTEXT_DEFAULT;

//	AfxMessageBox("Unk Context");
	// no class context?  Check for App name context
//	m_nCurrentContext = GetAppContextFromPt();	
//	return m_nCurrentContext;

//	m_edtForeWnd.SetWindowText(buf);
	return CONTEXT_DEFAULT;
}
*/


bool CProcessHandler::GetWindowClickInfo(HWND hWnd,CClickInfo &context) {
	static char classNameBuf[256];
	return !IsMouseToolWnd(hWnd)&&
		::GetClassName(hWnd,classNameBuf,sizeof classNameBuf)&&
		m_mClasses.Lookup(classNameBuf, context);
}

bool CProcessHandler::GetMouseClickInfo(CClickInfo &context) {
	POINT mousePt;
	::GetCursorPos(&mousePt);
	return GetWindowClickInfo(::WindowFromPoint(mousePt),context);
}

int CProcessHandler::GetMouseContext() {
	POINT mousePt;
	::GetCursorPos(&mousePt);
	HWND hWnd=::WindowFromPoint(mousePt);
	CClickInfo context;
	m_nCurrentContext=CONTEXT_DEFAULT;
	if(GetWindowClickInfo(hWnd,context)) {
		m_nCurrentContext=context.nContext;
	} else {
		if(IsMouseToolWnd(hWnd)&&m_bInHelpMode) {
			m_nCurrentContext=CONTEXT_HELPMODE;
		}
	}
	return m_nCurrentContext;
}

// The compiler didn't like it when I tried to pass a map.
// Rather than spend any time at all working out the syntax, I'm passing an index:
// 0 = m_mApps
// 1 = m_mClasses
// Contexts are saved in he registry with the format:
// <App/Class name> <"Class" or "App"> <nContext>
bool CProcessHandler::SaveContexts(int nContextNum)
{
	HKEY hKey=NULL;
	char szKeyName[70];
	POSITION pos;
	DWORD nCount = 0;
	char buf[MAX_PATH];
	
	int nLen;
	
	strcpy(szKeyName, "Software\\JR Software\\MouseTool");
	
	LONG res = RegOpenKeyEx(HKEY_CURRENT_USER, szKeyName, 0, KEY_WRITE, &hKey);

	if (res == ERROR_SUCCESS) 
	{
		CString KeyName, str;
		CClickInfo ci;
		std::string noSmartScroll;
		
		pos = m_mClasses.GetStartPosition();
		while (pos) 
		{
			m_mClasses.GetNextAssoc(pos, str, ci);
			if(ci.bDontDragInScrollbars) {
				noSmartScroll+="\""+std::string(LPCTSTR(str))+"\" ";
			}
			str += " ";
			str += "Class ";
//			str += ci.strComment;
			sprintf(buf, "%s %d <<%s", LPCTSTR(str), ci.nContext, LPCTSTR(ci.strComment));
			nLen = strlen(buf);
			sprintf(szKeyName, "Key%d", nCount++);

			RegSetValueEx(hKey, szKeyName, 0, REG_SZ, (unsigned char *)buf, nLen);
		}
		RegSetValueEx(hKey, "NumKeys", 0, REG_DWORD, (unsigned char *) &nCount, sizeof(DWORD));

		RegSetValueEx(hKey,NO_SMART_SCROLL_KEY,0,REG_SZ,
			reinterpret_cast<const BYTE *>(noSmartScroll.c_str()),
			noSmartScroll.length());

		RegCloseKey(hKey);
	} 

	return true;
		
}	

void CProcessHandler::LoadContexts()
{
	HKEY hKey;
	char szKeyName[70];
//	char szTest[30];
//	POSITION pos;
	DWORD nCount = 0;
	DWORD dwType, dwSize;
	TCHAR buf[MAX_PATH];
//		, szComment[MAX_PATH];
	char szName[30], szType[30];
	int nContext;
	int nClassStringCount;
	
	unsigned int n;
	dwSize = sizeof(DWORD);
	
	strcpy(szKeyName, "Software\\JR Software\\MouseTool");
	
	LONG res = RegOpenKeyEx(HKEY_CURRENT_USER, szKeyName, 0, KEY_READ, &hKey);

	if (res != ERROR_SUCCESS) 
		RestoreDefaultContexts();
	else
	{
		CString KeyName, str;
		CClickInfo ci;

		res = RegQueryValueEx(hKey, "NumKeys", NULL, &dwType, (unsigned char *) &nCount, &dwSize);		
		if (res != ERROR_SUCCESS) 		// if NumKeys isn't in the registry
		{
			nCount = 0;
			RestoreDefaultContexts();
		}

		//Get the list of classes that have smart drag in scroll bars
		//disabled. TOM TODO this is lame, put this in with the main cfg stuff.
		std::set<std::string,uti::string_lessthan_nocase> noSmartScroll;
		{
			DWORD dataSize;
			res=RegQueryValueEx(hKey,NO_SMART_SCROLL_KEY,0,&dwType,0,&dataSize);
			if(res==ERROR_SUCCESS&&dwType==REG_SZ) {
				std::string str;
				str.resize(dataSize);
				res=RegQueryValueEx(hKey,NO_SMART_SCROLL_KEY,0,&dwType,
					reinterpret_cast<BYTE *>(&str[0]),&dataSize);
				MTASSERT(res!=ERROR_MORE_DATA);
				if(res==ERROR_SUCCESS) {
					std::vector<std::string> tokens;
					uti::TokenizeString(str," ",tokens,uti::TOK_HANDLE_QUOTES);
					std::copy(tokens.begin(),tokens.end(),std::inserter(noSmartScroll,noSmartScroll.begin()));
				}
			}
		}
		
		for (n=0; n<nCount; n++)
		{
			sprintf(szKeyName, "Key%d", n);
			dwSize = MAX_PATH;
			res = RegQueryValueEx(hKey, szKeyName, NULL, &dwType, (unsigned char *) buf, &dwSize);		
			if (res==ERROR_SUCCESS) 
			{
				str = buf;					// make a CString variable
				// modified 10/6/98
//				TCHAR *pstrClass = _tcsstr(buf, "Class");

				int nLen = str.Find("<<");
				int nLenClass = 0;
				int nTotal = 0;
				bool bFound = false;
				nClassStringCount = 0;
//				AfxMessageBox(str);

// We've found '<<'.  
// Now search backwards until we find the first 'C'
// This will be the beginning of 'Class'
				int n = nLen;
				while (n>0) {
					if (str[n] == 'C')
						break;
					n--;
				}
				if (n > 0)
					nClassStringCount = n;
				
				nTotal = nClassStringCount - 1;

// at this point, nTotal is the number of characters in the window class name
// nLen is the offset of the "<<" delimiter 
// nClassStringCount is the offset of the last 'Class' substring before the '>>'
// and buf is the full content of the current registry entry

// Now that we know where things are, let's parse the string, and store the parts

				if (nTotal > 0) 
				{
					// Get Name.  Copy to szName.
					CString str2;
					str2 = str.Left(nTotal);
					strcpy(szName, str2);

					// Get Context.  Put in nContext.
					sscanf(str.Mid(nTotal+8, 1), "%d", &nContext);		// (1-digit wide)
					if(nContext==5) {
						//old smart scroll bar context
						nContext=CONTEXT_DISABLE_SMART_DRAG;
						//which is what you want.
					}
					ci.nContext = nContext;

					// Make sure it's a 'Class'
					strcpy(szType, str.Mid(nClassStringCount, 5));

					// Get Comment.  put in szComment.
					if (nLen > 0)
						nLen = str.GetLength() - nLen - 2;
					else
						nLen = 0;
					str = str.Right(nLen);
					ci.strComment = str;

					ci.bDontDragInScrollbars=noSmartScroll.count(szName)>0;

					if (!strcmp(szType, "Class")) 
					{
						m_mClasses.SetAt(szName, ci);
					}
				}
			}
			
		}		// for 
		RegCloseKey(hKey);
	} 
}	

bool CProcessHandler::IsMouseToolWnd(HWND hWnd)
{
	char buf[MAX_PATH];
	
	while (hWnd)
	{
		GetWindowText(hWnd, buf, MAX_PATH);
		CString str = buf;
		if (str.Compare("MouseTool")==0)
		{
//			AfxMessageBox("Found Mousetool!");
			return true;
		}
		hWnd = GetParent(hWnd);
	}
	return false;
}	

// Get the class name and set it in m_PrevClassUnderMouse
void CProcessHandler::SetClassAtMouse()
{
	POINT MousePt;
	char buf[MAX_PATH];

//	CString str = WinNameFromPt();
//	if (str.Find("MouseTool")>-1)		// if str contains "MouseTool" return
//		return;

	GetCursorPos(&MousePt);
	HWND hWnd = ::WindowFromPoint(MousePt);

	if (IsMouseToolWnd(hWnd)) {
		if (m_bInHelpMode) 
			m_nCurrentContext = CONTEXT_HELPMODE;
	} else {
		GetClassName(hWnd, buf, MAX_PATH);
		m_PrevClassUnderMouse = buf;
	}
}

void CProcessHandler::SetClickType(int nType)
{
	m_nCurrentClickType = nType;
	m_bOverride = true;
}	

int CProcessHandler::GetClickType()
{
// Added 9-28-98
// test to check mouse button awareness

//	UINT nState = GetKeyState(VK_LBUTTON);
//	nState -= 1;
//	if (nState > 0)
//		return CONTEXT_DISABLE_MOUSETOOL;

// end added 9-28-98

	if (m_nCurrentContext == CONTEXT_HELPMODE)
		return HELPMODE;

	if (m_bOverride)
	{
		if (m_nCurrentClickType == LEFTMODE) {
			if (m_bSmartDragEnabled)
				return DRAGMODE;
			else
				return LEFTMODE;
		} else
			return m_nCurrentClickType;
	}

	if (!m_bEnableContext)
	{
		return m_nCurrentClickType;
	}
	
	switch (m_nCurrentContext)
	{
		case CONTEXT_DEFAULT:
			if (m_nCurrentClickType == LEFTMODE) {
				if (m_bSmartDragEnabled)
					return DRAGMODE;
				else
					return LEFTMODE;
			}
			else
				return m_nCurrentClickType;
			
		case CONTEXT_DISABLE_SMART_DRAG:
			if (m_nCurrentClickType == DRAGMODE)
				return LEFTMODE;
			else
				return m_nCurrentClickType;
				
		case CONTEXT_DOUBLE_CLICK:
			return DOUBLEMODE;
			
		case CONTEXT_RIGHT_CLICK:
			return RIGHTMODE;
	}
	
	return m_nCurrentClickType;
}	

BOOL CProcessHandler::DeleteClassContext(CString key)
{
	return m_mClasses.RemoveKey(key);
	
}	


// Once this is set:
// When ClickType is set, it remains set only until ResetOverride is called.
// Then ClickType returns to previous value.
void CProcessHandler::SetOverrideNextOnly(bool bVal)
{
	m_bOverrideNextOnly = bVal;
}	

void CProcessHandler::ToggleOverrideNextOnly()
{
	m_bOverrideNextOnly = !m_bOverrideNextOnly;
}	

bool CProcessHandler::GetOverrideNextOnly()
{
	return m_bOverrideNextOnly;
}	

// reset the override, but only if contexts are enabled.
void CProcessHandler::ResetOverride()
{
	// if mode changes override indefinitely, return
	if (!m_bOverrideNextOnly)
	{
		return;
	}
	
	if (m_bEnableContext)
	{
		m_bOverride = false;
		m_nCurrentClickType = LEFTMODE;
	}
}	

void CProcessHandler::SetEnableContext(bool bVal)
{
	m_bEnableContext = bVal;
//	m_bEnableContext = false;
//	AfxMessageBox("Resetting context");
}



// These two functions let us cancel changes made in COptContext
void CProcessHandler::MakeBackupContextMap()
{
	CString str;
	CClickInfo ci;

	// first, clear backup
	m_mClassesBackup.RemoveAll();

	// Now, copy from m_mClasses to m_mClassesBackup
	POSITION pos = m_mClasses.GetStartPosition();
	while (pos) {
		m_mClasses.GetNextAssoc(pos, str, ci);
		m_mClassesBackup.SetAt(str, ci);
//		AfxMessageBox(str);
	}
 }
void CProcessHandler::RestoreContextsFromBackup()
{
	CString str;
	CClickInfo ci;

	// first, clear map
	m_mClasses.RemoveAll();

	// Now, copy from m_mClasses to m_mClassesBackup
	POSITION pos = m_mClassesBackup.GetStartPosition();
	while (pos) {
		m_mClassesBackup.GetNextAssoc(pos, str, ci);
		m_mClasses.SetAt(str, ci);
//		AfxMessageBox(str);
	}
}

void CProcessHandler::EnterHelpMode()
{
	m_bInHelpMode = true;
}

void CProcessHandler::ExitHelpMode()
{
	m_bInHelpMode = false;
}

bool CProcessHandler::IsInHelpMode()
{
	return m_bInHelpMode;
}

int CProcessHandler::GetChildHelpIdAtMouse()
{
	POINT MousePt;

	GetCursorPos(&MousePt);
	HWND hWnd = ::WindowFromPoint(MousePt);

	if (IsMouseToolWnd(hWnd)) {
		int nId = GetDlgCtrlID(hWnd);
		return nId;
	}
	return 0;
}

bool CProcessHandler::GetPressingButton()
{
	return m_bPressingButton;
}

void CProcessHandler::SetPressingButton(bool bVal)
{
	m_bPressingButton = bVal;
}

void CProcessHandler::OnClickHook(int nIsDown, UINT wParam, LONG lParam)
{
	m_bUserIsClicking = (nIsDown==KEY_DOWN);
}

bool CProcessHandler::UserIsClicking()
{
	if (m_bAlertNCIsShowing)		// this is a hack.  Sigh.
	{
		m_bAlertNCIsShowing = false;
		m_bUserIsClicking = false;
		return false;
	}

	return m_bUserIsClicking;
}

void CProcessHandler::IncClickCount()
{
	m_nSentClickCount++;
}

int	CProcessHandler::DecClickCount()
{
	m_nSentClickCount--;
	if (m_nSentClickCount<0)
		m_nSentClickCount = 0;

	return m_nSentClickCount;
}

void CProcessHandler::ClearClickCount()
{
	m_nSentClickCount = 0;
}

void CProcessHandler::RestoreDefaultContexts()
{
	CString KeyName, str;
	CClickInfo ci;

	ci.strComment = "System Tray";
	ci.strExeName = "one";			// not used
	ci.strWinName = "one";			// not used
	ci.nDefaultClickType = 0;		// not used
	ci.nContext = 3;
	m_mClasses.SetAt("TrayNotifyWnd", ci);

	ci.strComment = "Docking toolbar in Word";
	ci.nContext = 1;
	m_mClasses.SetAt("MsoCommandBarDock", ci);

	ci.strComment = "Start Menu";
	ci.nContext = 1;
	m_mClasses.SetAt("#32768", ci);

	ci.strComment = "Clock in System Tray";
	ci.nContext = 2;
	m_mClasses.SetAt("TrayClockWClass", ci);

	ci.strComment = "Docking toolbar in Word";
	ci.nContext = 1;
	m_mClasses.SetAt("MsoCommandBar", ci);

	ci.strComment = "IE Toolbar or Win 98 Start Menu";
	ci.nContext = 1;
	m_mClasses.SetAt("ToolbarWindow32", ci);

	ci.strComment = "Menu in Netscape";
	ci.nContext = 1;
	m_mClasses.SetAt("Afx:400000:b:10008:6:14400af", ci);

	ci.strComment = "Menu in Netscape";
	ci.nContext = 1;
	m_mClasses.SetAt("Afx:400000:8:10008:10:0", ci);

	ci.strComment = "Standard Button";
	ci.nContext = 1;
	m_mClasses.SetAt("Button", ci);

	SaveContexts(1);
}
