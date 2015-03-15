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

// MouseTool.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MouseTool.h"
#include "MouseToolDlg.h"
#include <direct.h>
#include <objbase.h>		// for testing
#include <shlobj.h>
#include "DlgOldSystemFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct _DllVersionInfo
{
    DWORD cbSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformID;
}DLLVERSIONINFO;
typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO *);


bool GetSystemDir(char *buf);
void CreateLink(char *, char *);
BOOL GetSpecialFolder(int flags, char *buffer);

/////////////////////////////////////////////////////////////////////////////
// CMouseToolApp

BEGIN_MESSAGE_MAP(CMouseToolApp, CWinApp)
	//{{AFX_MSG_MAP(CMouseToolApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseToolApp construction

CMouseToolApp::CMouseToolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMouseToolApp object

CMouseToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMouseToolApp initialization

BOOL CMouseToolApp::InitInstance()
{
	HINSTANCE   hComCtl;

	//load the DLLh
	hComCtl = LoadLibrary(TEXT("comctl32.dll"));
	if(hComCtl)   
	{
		DLLGETVERSIONPROC pDllGetVersion;
		
		// if comctl32 doesn't have DllGetVersion, then user needs to get a newer version
		//		If GetProcAddress fails, then the DLL is a version previous to the one 
		//		shipped with IE 3.x.
		pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hComCtl, TEXT("DllGetVersion"));

// Only proceed if new version of comctl32
		if(pDllGetVersion)
		{
			AfxEnableControlContainer();		// does this go here?

			// Standard initialization
			// If you are not using these features and wish to reduce the size
			//  of your final executable, you should remove from the following
			//  the specific initialization routines you do not need.

		#ifdef _AFXDLL
			Enable3dControls();			// Call this when using MFC in a shared DLL
		#else
			Enable3dControlsStatic();	// Call this when linking to MFC statically
		#endif

			SetRegistryKey("JR Software");

			CMouseToolDlg dlg;
			m_pMainWnd = &dlg;

			int nResponse = dlg.DoModal();
		}
		else		// there are old system files
		{
			CDlgOldSystemFiles dlg;

			dlg.m_strComUpdate = "401comupd.exe";

			dlg.DoModal();
		}
		FreeLibrary(hComCtl);
	}


/////////////////////////////////////////////////////////


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}





void WriteStr(const char *cVal, const char *cName, unsigned char *cstr, int len)
{
	HKEY hKey;

	LONG res = RegOpenKeyEx(HKEY_CURRENT_USER, cVal, 0, KEY_WRITE, &hKey);

	if (res == ERROR_SUCCESS) {
		RegSetValueEx(hKey, cName, 0, REG_SZ, cstr, len);
	}
	RegCloseKey(hKey);
}


// Assumption:  cstr is larg enough to hold return string
LONG ReadStr(const char *cVal, const char *cName, unsigned char *cstr)
{
	HKEY hKey;
	DWORD dwType;
	DWORD len;


	LONG res;
	res = RegOpenKeyEx(HKEY_CURRENT_USER, cVal, 0, KEY_QUERY_VALUE, &hKey);

	len = 0;
	if (res == ERROR_SUCCESS) {
		res = RegQueryValueEx(hKey, cName, NULL, &dwType, (LPBYTE) NULL, &len);
		if (res != ERROR_SUCCESS) {
			RegCloseKey(hKey);
			return res;
		}
		res = RegQueryValueEx(hKey, cName, NULL, &dwType, (LPBYTE) cstr, &len);
		if (res == ERROR_SUCCESS) {
			RegCloseKey(hKey);
			return res;
		}
		RegCloseKey(hKey);
	}
	return res;
}


// *************************************************************

/* str is an encoded date:
To Encode:
	year   = 5000 - year;
	month *= 2;
	day   *= 3;
To decode:
	year   = 5000 - year;
	month /= 2;
	day   /= 3;
*/ 
CTime DateFromString(char *str)
{
	int year, month, day;
	int res;
	CTime ctBlankDate(1972,1,1, 0,0,0);

	res = sscanf(str, "%u %u %u", &year, &month, &day);
	if (res == 0)
		return ctBlankDate;

	year   = 5000 - year;
	month /= 2;
	day   /= 3;

	return CTime (year, month, day, 1,1,1);
}	
void StringFromDate(CTime date, char *str)
{
	int year, month, day;

	year   = date.GetYear();
	month  = date.GetMonth();
	day    = date.GetDay();

	year   = 5000 - year;
	month *= 2;
	day   *= 3;

	sprintf(str, "%d %d %d", year, month, day);
}


// buf is: buf[MAX_PATH];
// This returns the windows directory (e.g. "C:\Windows")
// bool GetSystemDir(char *buf)
bool GetSystemDir(char *buf)
{
	HKEY hCU;
	DWORD lpType;
	ULONG size = MAX_PATH;
	long res;
//	char buf[MAX_PATH];
	char key[MAX_PATH];

	OSVERSIONINFO info;

	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&info);

//	if (!GetVersionEx(&info))
//		MessageBox ("Call failed!");
//	if (dwPlatformID == VER_PLATFORM_WIN32s) 

	if (info.dwPlatformId == VER_PLATFORM_WIN32_NT) 
		strcpy(key, "Software\\Microsoft\\Windows NT\\CurrentVersion");
	else
		strcpy(key, "Software\\Microsoft\\Windows\\CurrentVersion");

// Software\Microsoft\Windows NT\CurrentVersion


//	strcpy(tempbuf, "c:\\");
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		"Software\\Microsoft\\Windows\\CurrentVersion",
		0, KEY_QUERY_VALUE,
		&hCU) == ERROR_SUCCESS)
	{
		res = RegQueryValueEx( hCU, "SystemRoot", NULL, &lpType,
			(unsigned char *) buf, &size);
//		res = ERROR_SUCCESS;		// debugging line only

		if (res == ERROR_SUCCESS) 
		{
				RegCloseKey(hCU);
				return TRUE;
		} else
			RegCloseKey(hCU);
	}
	return FALSE;
}

/*
// Sets the security file contents to today.
void SetSecurityFileContents()
{
	FILE *fp;
	char buf[MAX_PATH];
	UINT year, month, day;
	char sf[] = "]tfdg/tzt";

	DecodeStr(sf);

	GetSystemDirectory(buf, MAX_PATH);
	strcat(buf, sf);

	CTime temptime = CTime::GetCurrentTime();
	day = temptime.GetDay()*3;
	month = temptime.GetMonth()*2;
	year = 5000-temptime.GetYear();

	fp = fopen(buf, "w");
	fprintf(fp, "%u %u %u", year, month, day);
	fclose(fp);
}
*/
void CMouseToolApp::SetFileTime(char *szSecFileName)
{
	CTime tmStartTime(1994, 11,30, 0,0,0);
	CFileStatus fsStatus;
	CFile fSecFile(szSecFileName, CFile::modeReadWrite);

	fSecFile.GetStatus(fsStatus);
	fsStatus.m_ctime = tmStartTime;
	fsStatus.m_mtime = tmStartTime;
	fsStatus.m_atime = tmStartTime;
	CFile::SetStatus(szSecFileName, fsStatus);
}



bool CMouseToolApp::DoShortcut(int shortcutFlag)
{
	HKEY hCU;
	DWORD lpType;
	ULONG ulSize = MAX_PATH;
	char linkPath[MAX_PATH];

	// First, get path to link
	if (RegOpenKeyEx(HKEY_CURRENT_USER, 
		"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",0,KEY_QUERY_VALUE,&hCU) == ERROR_SUCCESS)
	{
		RegQueryValueEx (hCU,"Startup",NULL,&lpType,(unsigned char *)&linkPath,&ulSize);
	    RegCloseKey(hCU);
		strcat(linkPath, "\\MouseTool.lnk");
	} else
		return false;

	// Then check to see what we do
	if (shortcutFlag == STARTUP_CHECKSTARTUP) {
		CFileStatus status;
		return (CFile::GetStatus(linkPath, status)==TRUE);
	}
	if (shortcutFlag == STARTUP_SETSTARTUP) {
	    CoInitialize(NULL);
		CreateShortcut();
		CoUninitialize();
		return true;
	}
	if (shortcutFlag == STARTUP_REMOVESTARTUP) {
		try 
		{
			CFile::Remove( linkPath );
		}
		catch( CFileException e )
		{
			return false;
		}
	}
	return false;
}


HRESULT CMouseToolApp::CreateShortcut()
{
    HRESULT hres;
    IShellLink *psl;
	DWORD cchCurDir = MAX_PATH;
	char progfile[MAX_PATH];
	char sPath[MAX_PATH];

	char pszDesc[] = "New Shortcut";

	// Get the full path of the MouseTool.exe file
	if ( GetModuleFileName( NULL, sPath, MAX_PATH) != 0) {
		* ( strrchr( sPath, '\\' ) + 1 ) = '\0';
//		AfxMessageBox( acPath );   // Use it 
	}
	strcpy (progfile, sPath);
	strcat (progfile, "\\MouseTool.exe");		// does the string already end in "\" ?

	HKEY hCU;
	DWORD lpType;
	ULONG ulSize = MAX_PATH;
	char szLink[MAX_PATH];
	if (RegOpenKeyEx(HKEY_CURRENT_USER, 
		"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",0,KEY_QUERY_VALUE,&hCU) == ERROR_SUCCESS)
	{
		RegQueryValueEx (hCU,"Startup",NULL,&lpType,(unsigned char *)&szLink,&ulSize);
		RegCloseKey(hCU);
	}

	strcat(szLink, "\\MouseTool.lnk");
	// Create an IShellLink object and get a pointer to the IShellLink
	// interface (returned from CoCreateInstance).
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,IID_IShellLink, (void **)&psl);
    if (SUCCEEDED(hres))
    {
       IPersistFile *ppf;
       
	   // Query IShellLink for the IPersistFile interface for
	   // saving the shortcut in persistent storage.
       hres = psl->QueryInterface(IID_IPersistFile, (void **)&ppf);
	   if (SUCCEEDED(hres))
	   {   
	        WORD wsz[MAX_PATH];   // buffer for Unicode string

			hres = psl->SetWorkingDirectory(sPath);

	   		// Set the path to the shortcut target.
          	hres = psl->SetPath(progfile);

			if (!SUCCEEDED(hres))
				AfxMessageBox("SetPath failed!");

            // Set the description of the shortcut.
          	hres = psl->SetDescription(pszDesc);

			if (!SUCCEEDED(hres))
				AfxMessageBox("SetDescription failed!");

	     	// Ensure that the string consists of ANSI characters.
	     	MultiByteToWideChar(CP_ACP, 0, szLink, -1, wsz, MAX_PATH);

          	// Save the shortcut via the IPersistFile::Save member function.
          	hres = ppf->Save(wsz, TRUE);

//			if (!SUCCEEDED(hres))
//				AfxMessageBox("Save failed!");

            // Release the pointer to IPersistFile.
          	ppf->Release();
       }
       // Release the pointer to IShellLink.
       psl->Release();
    }
    return hres;
}

