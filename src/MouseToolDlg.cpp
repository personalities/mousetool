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

// MouseToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "MouseToolDlg.h"
//#include "MouseDownDlg.h"
#include <stdlib.h>
#include <shlobj.h>
#include "KeyHandler.h"
#include "OptKeys.h"
#include "DlgWelcome.h"

#include <winbase.h>

#include "WineyesTest.h"

#include "AbtDlg.h"


// define one of the two following tags to either record or play back
// a series of mouse moves for testing.

//#define RECORDMOUSE
//#define READMOUSE

// these two are used to store mouse positions and loop count for testing
#define MOUSEFILE "mousepos.txt"
#define MOUSEREADCOUNTFILE "readcount.txt"

//////////////////////////////////////////////////////////////////////////
// Returns true if the given point is in a scroll bar.
static bool IsPointInScrollBar(const POINT &point) {
	POINT pt=point;
	HWND h=::WindowFromPoint(pt);
	if(!::ScreenToClient(h,&pt)) {
		return false;
	}
	LONG style=::GetWindowLong(h,GWL_STYLE);
	LONG exstyle=::GetWindowLong(h,GWL_EXSTYLE);
	
	RECT client;
	::GetClientRect(h,&client);
	if(style&WS_VSCROLL) {
		RECT sbRect=client;
		if(exstyle&WS_EX_LEFTSCROLLBAR) {
			sbRect.right=sbRect.left;
			sbRect.left-=::GetSystemMetrics(SM_CXVSCROLL);
		} else {
			sbRect.left=sbRect.right;
			sbRect.right+=::GetSystemMetrics(SM_CXVSCROLL);
		}
		if(::PtInRect(&sbRect,pt)) {
			return true;
		}
	}
	if(style&WS_HSCROLL) {
		RECT sbRect=client;
		sbRect.top=sbRect.bottom;
		sbRect.bottom+=::GetSystemMetrics(SM_CYHSCROLL);
		if(::PtInRect(&sbRect,pt)) {
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////
	#if defined(READMOUSE)
		FILE *infile;
	#endif
/////////////////////////////////////////////////////////////////////


int n = 0;


// *************************************************************
// From RegTest

int GetLen(unsigned char *);
void EncodeStr(char *);
void DecodeStr(char *);

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseToolDlg dialog

CMouseToolDlg::CMouseToolDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMouseToolDlg::IDD, pParent), TrayIcon(IDR_MAINFRAME)
{
	//{{AFX_DATA_INIT(CMouseToolDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMouseToolDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Edit1Control);
	DDX_Control(pDX, IDC_SMALLBUTTON, m_SmallButton);
	DDX_Control(pDX, IDC_DSTATIC, m_DStaticControl);
	DDX_Control(pDX, IDC_RSTATIC, m_RStaticControl);
	DDX_Control(pDX, IDC_LSTATIC, m_LStaticControl);
	DDX_Control(pDX, IDC_HELPBUTTON, m_HelpButtonControl);
	DDX_Control(pDX, IDC_JOYPROGRESS, m_JoyProgress);
	DDX_Control(pDX, IDC_OPTIONSBUTTON, m_OptionsControl);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1Control);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMouseToolDlg, CDialog)
	//{{AFX_MSG_MAP(CMouseToolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OPTIONSBUTTON, OnOptionsbutton)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_HELPBUTTON, OnHelpbutton)
	ON_BN_CLICKED(IDC_SMALLBUTTON, OnSmallbutton)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_QUERYENDSESSION, OnShutdown)
	ON_MESSAGE( WM_NCLBUTTONDOWN, ncLDown )
	ON_MESSAGE( WM_NCLBUTTONUP, ncLUp )
	ON_MESSAGE(UWM_MOUSETOOLHOOK, OnHook)
	ON_MESSAGE(UWM_MOUSETOOLKEYHOOK, OnKeyHook)
	ON_MESSAGE(UWM_MOUSETOOLKEYUPHOOK, OnKeyUpHook)
	ON_MESSAGE(UWM_MOUSETOOLCLICKHOOK, OnClickHook)
	ON_MESSAGE(UWM_MOUSETOOLCLICKUPHOOK, OnClickUpHook)
	ON_MESSAGE(UWM_MOUSETOOLTRAY, OnTrayMsg)

	ON_MESSAGE(WM_HOTKEY, OnWmHotkey)

	ON_COMMAND(ID_TRAYMENU_DOUBLECLICK, OnTrayDouble)
	ON_COMMAND(ID_TRAYMENU_LEFTCLICK, OnTrayLeft)
	ON_COMMAND(ID_TRAYMENU_RIGHTCLICK, OnTrayRight)
	ON_COMMAND(ID_TRAYMENU_RESTORE, OnTrayRestore)	
	ON_COMMAND(ID_TRAYMENU_STOPMOUSETOOL, OnTrayStartStop)
	ON_COMMAND(ID_TRAYMENU_CLOSEMOUSETOOL, OnTrayClose)
	ON_COMMAND(ID_TRAYMENU_NEXTONLY, OnTrayNextOnly)
	ON_COMMAND(ID_TRAYMENU_OPENGENERAL, OnTrayOpenGeneral)
	ON_COMMAND(ID_TRAYMENU_OPENKEYS, OnTrayOpenKeys)
	ON_COMMAND(ID_TRAYMENU_OPENCONTEXT, OnTrayOpenContext)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseToolDlg message handlers

BOOL CMouseToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

/////////////////////////////////////////////////////////////////////
	#if defined(READMOUSE)
		infile = fopen(MOUSEFILE, "r");   
	#endif
/////////////////////////////////////////////////////////////////////

// If this gives a problem, set it to false!
	m_bStopDragging = true;

	m_nTicksSinceLastClick = 0;
	ASSERT(m_hWnd);
	ASSERT(this);
	m_bToggleKeyWasPressed = false;
	m_nRightClickInNTicks = 0;
	m_nOldClickType = LEFTMODE;
	m_bSentDownUpLastTick = false;
	m_bUserIsClicking = false;
	m_bClickedOnModeChanger = false;
	m_bClosing = false;
	m_bMTSentLastClick = false;
	m_bSmartDragIsOn = false;
	LongTimerID = UINT(-1);
	m_nSmartDragTimerID = UINT(-1);
	m_bToggleButtonOn = false;
	m_bWaitingForUpclick = false;
	m_bDraggingMouseToolWithToggleKey = false;
//	m_pshtOptions = new COptionsSheet("MouseTool Options", NULL, 0);
	m_pshtOptions = new COptionsSheet("MouseTool Options", this, 0);
	if (m_pshtOptions == NULL) {
		MessageBox("MouseTool was unable to start.  Is memory low?");
		exit(0);
	}
	m_pshtOptions->m_pgContext.m_pProcHandler	= &m_ProcHandler;
	m_pshtOptions->m_pgGeneral.m_pProcHandler	= &m_ProcHandler;
	m_pshtOptions->m_pProcHandler				= &m_ProcHandler;

	m_ProcHandler.SetOverrideNextOnly(true);
	m_ProcHandler.ExitHelpMode();

	m_pshtOptions->m_pgKeys.SetMainWnd(m_hWnd);

	m_bNCDragging = false;

// aaaaa

	TrayIcon.SetNotificationWnd(this, UWM_MOUSETOOLTRAY);
	RestoreConfig();		// This only restores variables from registry.  It 
							// doesn't call any timer routines, or set windows.


  if (m_bFirstTime) 
  {
    CDlgWelcome wdlg;
    wdlg.DoModal();
  }

	if (!setMTHook(m_hWnd, 487)) {
//		MessageBox("Unable to load mt.dll!");
//		exit(0);
	}


	GetMouseReversed();
	SetBitmaps();

	m_Clicker.m_bButtonsReversed = !!m_bButtonsReversed;

	m_LStaticControl.Down();

	// Get the full path of the tap.wav sound file
	if ( GetModuleFileName( NULL, m_TapWaveFile, MAX_PATH) != 0) {
		* ( strrchr( m_TapWaveFile, '\\' ) + 1 ) = '\0';
	} else
		m_TapWaveFile[0] = '\0';
	strcat(m_TapWaveFile, "tap.wav");


	m_bMouseInWindow = false;		// Should I actually check?

	m_bitBigSmall.LoadMappedBitmap(IDB_MAKESMALL);
	m_SmallButton.SetBitmap(m_bitBigSmall);

	m_DragOnly = FALSE;
	DisableControls();
	MoveCount = 0;
	m_StationaryTicks = 0;

	/////////////////////  Customized for Jack Hamilton //////////////////
	/////////////////////  Standard value is 100
	m_Milliseconds = TIMER_INTERVAL_IN_MS;
	//////////////////////////////////////////////////////////////////////
	TimerID = UINT(-1);				// -1 tells SetTimer to start timer
	m_bmpStopBitmap.LoadMappedBitmap(IDB_STOPBITMAP);
	m_bmpGoBitmap.LoadMappedBitmap(IDB_GOBITMAP);
	m_Button1Control.SetBitmap(m_bmpStopBitmap);

	m_DraggingByDelay = FALSE;

	m_LongTimerElapsed = 0;
	LongTimerID = 2;

	int bTemp = m_bMouseToolIsActive;
	m_bMouseToolIsActive = false;		// Turn timer on and off to make sure the timer is running even if it shows itself as off.
	OnButton1();				// we need this to handle hotkeys correctly (to call UnstickHotkey)
	m_bMouseToolIsActive = bTemp;

	m_bMouseToolIsActive = !m_bMouseToolIsActive;		// OnButton1() toggles the timer ...
	OnButton1();

	if (m_LongTimerOn)			// if TimerOn was set in registry
		SetLongTimer(m_LongTimerWait);

// This section was to enable larger buttons for use by an 
// eye-tracking system
#if defined EYE_TRACKING
	RECT rect;

	// move controls to the right to make room for larger button bitmaps
	int nLeft = CHANGEMODE_BITMAP_SPACING;
	int nTop = 2;

	// First, changemode buttons
	m_LStaticControl.SetWindowPos(&wndTop, nLeft, nTop, 1,1, SWP_NOOWNERZORDER | SWP_NOSIZE);

	nLeft += EYE_TRACKING_CHANGEMODE_BITMAP_WIDTH+CHANGEMODE_BITMAP_SPACING;
	m_DStaticControl.SetWindowPos(&wndTop, nLeft, nTop, 1,1, SWP_NOOWNERZORDER | SWP_NOSIZE);

	nLeft += EYE_TRACKING_CHANGEMODE_BITMAP_WIDTH+CHANGEMODE_BITMAP_SPACING;
	m_RStaticControl.SetWindowPos(&wndTop, nLeft, nTop, 1,1, SWP_NOOWNERZORDER | SWP_NOSIZE);

	// then, resize real buttons
	m_SmallButton.SetWindowPos(&wndTop, 1,1, EYE_TRACKING_BUTTON_WIDTH,EYE_TRACKING_BUTTON_WIDTH, SWP_NOOWNERZORDER | SWP_NOMOVE);
	m_Button1Control.SetWindowPos(&wndTop, 1,1, EYE_TRACKING_BUTTON_WIDTH,EYE_TRACKING_BUTTON_WIDTH, SWP_NOOWNERZORDER | SWP_NOMOVE);
	m_OptionsControl.GetClientRect(&rect);
	m_OptionsControl.SetWindowPos(&wndTop, 1,1, rect.right-rect.left,EYE_TRACKING_BUTTON_WIDTH, SWP_NOOWNERZORDER | SWP_NOMOVE);
	m_HelpButtonControl.SetWindowPos(&wndTop, 1,1, EYE_TRACKING_BUTTON_WIDTH,EYE_TRACKING_BUTTON_WIDTH, SWP_NOOWNERZORDER | SWP_NOMOVE);

	// then, move real buttons
	nLeft += EYE_TRACKING_CHANGEMODE_BITMAP_WIDTH+CHANGEMODE_BITMAP_SPACING;
	m_SmallButton.SetWindowPos(&wndTop, nLeft, nTop, 1,1, SWP_NOOWNERZORDER | SWP_NOSIZE);

	m_SmallButton.GetClientRect(&rect);
	nLeft += rect.right-rect.left+CHANGEMODE_BITMAP_SPACING;
	m_Button1Control.SetWindowPos(&wndTop, nLeft, nTop, 1,1, SWP_NOOWNERZORDER | SWP_NOSIZE);

	m_Button1Control.GetClientRect(&rect);
	nLeft += rect.right-rect.left+CHANGEMODE_BITMAP_SPACING;
	m_OptionsControl.SetWindowPos(&wndTop, nLeft, nTop, 1,1, SWP_NOOWNERZORDER | SWP_NOSIZE);

	m_OptionsControl.GetClientRect(&rect);
	nLeft += rect.right-rect.left+CHANGEMODE_BITMAP_SPACING;
	m_HelpButtonControl.SetWindowPos(&wndTop, nLeft, nTop, 1,1, SWP_NOOWNERZORDER | SWP_NOSIZE);


	// now that we've positioned everything, resize window to fit it all ...
	GetWindowRect(&rect);

	int nHeight = rect.bottom-rect.top;
	nHeight += EYE_TRACKING_CHANGEMODE_BITMAP_HEIGHT - 19;	// diff between new and old heights

	// Make room for help button and right border
	int nWidth = nLeft + EYE_TRACKING_BUTTON_WIDTH + 3*CHANGEMODE_BITMAP_SPACING;

	::SetWindowPos(m_hWnd, HWND_TOP, rect.left,rect.top, nWidth, nHeight, SWP_NOOWNERZORDER);
#endif

	SetCaptionRects();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMouseToolDlg::SetBitmaps()
{
#if defined EYE_TRACKING
	if (m_bButtonsReversed) {
		m_LStaticControl.SetBitmaps(IDB_LRG_LFL,  IDB_LRG_LUP,  IDB_LRG_LDN,  IDB_LRG_FLAT, IDB_LRG_LFL);
		m_RStaticControl.SetBitmaps(IDB_LRG_RFL,  IDB_LRG_RUP,  IDB_LRG_RDN,  IDB_LRG_FLAT, IDB_LRG_RDRAG);
		m_DStaticControl.SetBitmaps(IDB_LRG_RDFL, IDB_LRG_RDUP, IDB_LRG_RDDN, IDB_LRG_FLAT, IDB_LRG_RDFL);
	} else {
		m_LStaticControl.SetBitmaps(IDB_LRG_LFL,  IDB_LRG_LUP,  IDB_LRG_LDN,  IDB_LRG_FLAT, IDB_LRG_DRAG);
		m_RStaticControl.SetBitmaps(IDB_LRG_RFL,  IDB_LRG_RUP,  IDB_LRG_RDN,  IDB_LRG_FLAT, IDB_LRG_RFL);
		m_DStaticControl.SetBitmaps(IDB_LRG_DFL,  IDB_LRG_DUP,  IDB_LRG_DDN,  IDB_LRG_FLAT, IDB_LRG_DFL);
	}
#else
	if (m_bButtonsReversed) {
		m_LStaticControl.SetBitmaps(IDB_LFL,  IDB_LUP,  IDB_LDN,  IDB_FLAT, IDB_LFL);
		m_RStaticControl.SetBitmaps(IDB_RFL,  IDB_RUP,  IDB_RDN,  IDB_FLAT, IDB_RDRAG);
		m_DStaticControl.SetBitmaps(IDB_RDFL, IDB_RDUP, IDB_RDDN, IDB_FLAT, IDB_RDFL);
	} else {
		m_LStaticControl.SetBitmaps(IDB_LFL,  IDB_LUP,  IDB_LDN,  IDB_FLAT, IDB_DRAG);
		m_RStaticControl.SetBitmaps(IDB_RFL,  IDB_RUP,  IDB_RDN,  IDB_FLAT, IDB_RFL);
		m_DStaticControl.SetBitmaps(IDB_DFL,  IDB_DUP,  IDB_DDN,  IDB_FLAT, IDB_DFL);
	}
#endif
}

// see if mouse buttons are reversed
void CMouseToolDlg::GetMouseReversed()
{
	m_bButtonsReversed = SwapMouseButton(TRUE);	
	SwapMouseButton(m_bButtonsReversed);
}


void CMouseToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMouseToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (TrayIcon.IsInTray())
			ShowWindow(FALSE);
		else
			CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMouseToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

double CMouseToolDlg::EditValue(CEdit& ed)
{
	CString str;

	ed.GetWindowText(str);
	return atof(str);
}

// The start/stop button.  I was young and foolish then and didn't name it.
// Also, I wasn't sure I was actually starting the program.  I thought I was still 
// just fooling around with tests.
void CMouseToolDlg::OnButton1() 
{
	m_StationaryTicks = 0;

	if (m_bMouseToolIsActive) {					// If we're stopping
		StopTimer();				  
		FlattenAllBitmaps(true);
		DisableControls();
	}
	else {								// if we're starting
		SetTimer(m_Milliseconds, m_TicksToWait);
		FlattenAllBitmaps(false);
		SetClickType();
		EnableControls();
	}
}

bool CMouseToolDlg::SamePoint(POINT pt1, POINT pt2)
{
//	return ((pt1.x==pt2.x) && (pt1.y==pt2.y));
	if (abs(pt1.x-pt2.x)<m_nDwellZoneSize)
		if (abs(pt1.y-pt2.y)<m_nDwellZoneSize)
			return true;
	return false;
	
			
}


void CMouseToolDlg::FlattenAllBitmaps(const bool bFlatten)
{
	if (bFlatten) {
		m_LStaticControl.Activate(false);
		m_RStaticControl.Activate(false);
		m_DStaticControl.Activate(false);
		m_bBitmapsAreFlat = true;
		if (TrayIcon.IsInTray())
		{
			TrayIcon.SetIcon(IDI_ICON_STOPPED);
			m_nOldClickType = DISABLEMODE;
		}
	} else {
		m_LStaticControl.Activate(true);
		m_RStaticControl.Activate(true);
		m_DStaticControl.Activate(true);
		m_bBitmapsAreFlat = false;
	}
}

void CMouseToolDlg::SetDragBitmap(const int throttle)
{
	if (!m_bShowDrag && throttle>0)		// Only show if user wants it.
		return;							// but allow removal of drag indicator

	if (m_DraggingByDelay)
		return;

	if (throttle > THROTTLE_MIN_STEP) {
		m_LStaticControl.SetDrag(true);
		m_RStaticControl.SetDrag(true);
		m_DStaticControl.SetDrag(true);
		if (TrayIcon.IsInTray())
			TrayIcon.SetIcon(IDI_ICON_RED);
	} else {
		m_LStaticControl.SetDrag(false);
		m_RStaticControl.SetDrag(false);
		m_DStaticControl.SetDrag(false);
		if (TrayIcon.IsInTray())
			if (m_bMouseToolIsActive)
				TrayIcon.SetIcon(IDR_MAINFRAME);
			else
				TrayIcon.SetIcon(IDI_ICON_STOPPED);
	}
}


void CMouseToolDlg::MouseDblClick()
{
	if (!m_bButtonsReversed) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, m_MousePos.x, m_MousePos.y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_LEFTUP,   m_MousePos.x, m_MousePos.y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_LEFTDOWN, m_MousePos.x, m_MousePos.y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_LEFTUP,   m_MousePos.x, m_MousePos.y, 0, GetMessageExtraInfo());
	} else {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, m_MousePos.x, m_MousePos.y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_RIGHTUP,   m_MousePos.x, m_MousePos.y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_RIGHTDOWN, m_MousePos.x, m_MousePos.y, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_RIGHTUP,   m_MousePos.x, m_MousePos.y, 0, GetMessageExtraInfo());
	}
}
void CMouseToolDlg::MouseLDownUp()
{
	m_ProcHandler.IncClickCount();

	GetCursorPos(&m_MousePos);
	m_Clicker.click(LEFTCLICK, m_MousePos.x, m_MousePos.y);

	m_bUserIsClicking = false;				// this line doesn't seem to help.  OnClick still receives
											// the message, and sets this true.  In some cases,
											// it never receives up message.  See MouseLUp.
	m_bSentDownUpLastTick = true;			// this line is the fix.
}
void CMouseToolDlg::MouseLDown()
{
//	m_Edit1Control.SetWindowText("Mouse Down");
	m_ProcHandler.IncClickCount();

	GetCursorPos(&m_MousePos);
	m_Clicker.click(LEFTDOWN, m_MousePos.x, m_MousePos.y);
}
void CMouseToolDlg::MouseLUp()
{
// Set m_bUserIsClicking to false.
// Otherwise, there is an obscure bug when viewing help system with MT
// If you only set m_bUserIsClicking false in OnKeyUpHook ...
// 1. Mouse clicks down on help topic link
// 2. Help jumps to new topic.  Window resizes.  Mouse is now NOT over help window.
// 3. MT clicks up.
// 4. MT doesn't hear upclick, apparently because it was not sent to help window.
// 5. MT thinks user is pressing button, and won't click.
//	m_Edit1Control.SetWindowText("Mouse Up");
	m_bUserIsClicking = false;
	m_ProcHandler.IncClickCount();

	GetCursorPos(&m_MousePos);
	m_Clicker.click(LEFTUP, m_MousePos.x, m_MousePos.y);
}
void CMouseToolDlg::MouseRDown()
{
	m_ProcHandler.IncClickCount();

	GetCursorPos(&m_MousePos);
	m_Clicker.click(RIGHTDOWN, m_MousePos.x, m_MousePos.y);
}
void CMouseToolDlg::MouseRUp()
{
	m_ProcHandler.IncClickCount();

	GetCursorPos(&m_MousePos);
	m_Clicker.click(RIGHTUP, m_MousePos.x, m_MousePos.y);
}
void CMouseToolDlg::MouseRDownUp()
{
	MouseRDown();
	MouseRUp();

//	m_ProcHandler.IncClickCount();

//	AfxMessageBox("right");
//	GetCursorPos(&m_MousePos);
//	m_Clicker.click(RIGHTCLICK, m_MousePos.x, m_MousePos.y);
}

void CMouseToolDlg::ClickMouse() 
{
//	if (m_nTicksSinceLastClick < m_TicksToWait)		// if user just clicked manually
//		return;

//	CString str;
//	str.Format("<%d>", m_ProcHandler.UserIsClicking());
//	m_Edit1Control.SetWindowText(str);

// return if user is pressing a button
	// I'd really like to have this working.
//	if (m_ProcHandler.UserIsClicking())
//		return;

// return if user is dragging by using the hotkeys

	if (m_ProcHandler.GetPressingButton())
		return;

//	m_Edit1Control.SetWindowText("ClickMouse 2");
	if (m_bCheckIfMouseDown)
		if (m_bUserIsClicking)
			return;
//	m_Edit1Control.SetWindowText("ClickMouse 3");

	int nType;

	m_pshtOptions->m_pgContext.SetClassAtMouse();

	m_bClickedOnModeChanger = false;
	nType = m_ProcHandler.GetClickType();
	m_ProcHandler.ResetOverride();

	//
	CClickInfo context;
	POINT mousept;

	//If smart drag is enabled, and the current context doesn't disable
	//smart scrolling, and we're in a scroll bar, set up smart drag.

	if(m_ProcHandler.m_bSmartDragEnabled&&
		(!m_ProcHandler.GetMouseClickInfo(context)||!context.bDontDragInScrollbars)&&
		nType!=CONTEXT_HELPMODE&&::GetCursorPos(&mousept)&&IsPointInScrollBar(mousept))
	{
		nType=DRAGMODE;
	}
	
	switch (nType)
	{
	case LEFTMODE:
		PlayTickSound();
		MouseLDownUp();
		break;
	case DOUBLEMODE:
		PlayTickSound();
		MouseDblClick();
		break;
	case RIGHTMODE:
		PlayTickSound();
		MouseRDownUp();
		break;
	case DRAGMODE:
		//	m_Edit1Control.SetWindowText("Calling SD");
		SmartDrag(SD_CLICKDOWN);
		//				SlowClick();
		break;
	case HELPMODE:
		CallContextHelp();
		break;
	}
/*
	switch (nType)
	{
		case LEFTMODE:
				PlayTickSound();
				MouseLDownUp();
			break;
		case DOUBLEMODE:
				PlayTickSound();
				MouseDblClick();
			break;
		case RIGHTMODE:
				PlayTickSound();
				MouseRDownUp();
			break;
		case DRAGMODE:
//	m_Edit1Control.SetWindowText("Calling SD");
				SmartDrag(SD_CLICKDOWN);
//				SlowClick();
			break;
		case HELPMODE:
				CallContextHelp();
			break;
	}
*/
}


// Sets mouse position and timer so MouseTool won't click at current position.
void CMouseToolDlg::DontClickHere()
{
	m_OldMousePos.x = m_MousePos.x;				
	m_OldMousePos.y = m_MousePos.y;				
	m_StationaryTicks = m_TicksToWait + 1;
}

// Gets called by OnTimer.  Keeps modechanger buttons from staying up when
//  user moves mouse away. 
void CMouseToolDlg::CheckMouseInWindow(const CPoint &MousePos)
{
	RECT rectApp;
	GetWindowRect(&rectApp);
	CRect rect(rectApp);
	if (rect.PtInRect(MousePos)) {		// if in the app window, test buttons

		if (!m_bInLStatic)
			m_LStaticControl.Activate(true);

		if (!m_bInRStatic)
			m_RStaticControl.Activate(true);

		if (!m_bInDStatic)
			m_DStaticControl.Activate(true);

		return;
	}
// xxxxx
	m_LStaticControl.Activate(true);
	m_RStaticControl.Activate(true);
	m_DStaticControl.Activate(true);
	m_bMouseInWindow = false;			// Don't call this again until in window again
}

void CMouseToolDlg::OnTimer(UINT nIDEvent) 
{
	int throttle;
	static int nCount;

	m_nTicksSinceLastClick++;

	if (m_nRightClickInNTicks>0)		// set to 2 when hotkey is hit
	{
		m_nRightClickInNTicks--;
		if (m_nRightClickInNTicks==0)
			MouseRDownUp();
		return;
	}

//	if (m_bUserIsClicking)
//		m_Edit1Control.SetWindowText("Clicking");
//	else
//		m_Edit1Control.SetWindowText("Not Clicking");
//	CString str;

//	str.Format("%d", m_StationaryTicks);
//	m_Edit1Control.SetWindowText(str);

	CheckKeys();  // check toggle hotkey
	
	if (m_bCheckIfMouseDown)
		if (m_ProcHandler.GetPressingButton())
			UnstickHotkey();

	// Call event functions for long timer before checking if MT is inactive.
	if (nIDEvent == LongTimerID) 
	{
		LongTimerEvent();
		return;
	}

	if (!m_bMouseToolIsActive)
		return;

	// Set the context.
	// This is also called in OnTimer.  Here it is called just to update the display.
	int nContext = m_ProcHandler.GetMouseContext();		// set context for prochandler

	if (nContext==CONTEXT_DISABLE_MOUSETOOL) {
		FlattenAllBitmaps(true);
		return;
	} 
	
	SetClickType();										// Sets mode-change buttons
	if (m_bSentDownUpLastTick)
		m_bSentDownUpLastTick = false;

	// Call event functions for long timer and double click timer.
	// Call event functions for long timer and double click timer.
	if (nIDEvent == LongTimerID) 
		LongTimerEvent();
	if (nIDEvent == m_nSmartDragTimerID)
		SmartDragTimerEvent();
	else {									// if this is a short timer event

		if (m_bWaitingForUpclick) {			// Let SmartDrag handle it
			SmartDrag(SD_NORMAL_TIMER);
			return;
		}

		GetCursorPos(&m_MousePos);

/////////////////////////////////////////////////////////////////////
		#if defined(RECORDMOUSE)
			FILE *of;

			of = fopen(MOUSEFILE, "a");   
			fprintf(of, "%d %d\n", m_MousePos.x, m_MousePos.y);
			fclose(of);
		#endif
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
		#if defined(READMOUSE)
			if (EOF!=fscanf(infile, "%d %d", &m_MousePos.x, &m_MousePos.y))
				SetCursorPos(m_MousePos.x, m_MousePos.y);
			else				// loop forever ...
			{
				static int nReadCount = 1;

				fclose(infile);
				infile = fopen(MOUSEFILE, "r");   

				FILE *of;

				of = fopen(MOUSEREADCOUNTFILE, "a");   
				fprintf(of, "%d\n", nReadCount++);
				fclose(of);
			}
		#endif
/////////////////////////////////////////////////////////////////////

		if (m_bMouseInWindow)
			CheckMouseInWindow(m_MousePos);

		throttle = 0;
//		ShowPos(m_MousePos);				// for debugging only

		// If no drag, check to see if we've stopped long enough to click.
		if ( SamePoint(m_MousePos, m_OldMousePos) )
			m_StationaryTicks++;
		else
		{
			m_StationaryTicks = 0;
		}

		if (m_StationaryTicks == m_TicksToWait + 2)			// stop counting after the click
			m_StationaryTicks -= 1;

		m_OldMousePos.x = m_MousePos.x;
		m_OldMousePos.y = m_MousePos.y;

		if (m_StationaryTicks == m_TicksToWait) 
			ClickMouse();
		
		CDialog::OnTimer(nIDEvent);
	}
}

void CMouseToolDlg::LongTimerEvent()
{
	CTime now;

	now = CTime::GetCurrentTime();

	if (now >= m_LongTimerStopTime) {
		StopLongTimer();
		SetWindowPos(&wndTopMost, 1,1,1,1, SWP_NOMOVE | SWP_NOSIZE);
		MessageBox("Time for a stretch break.");
		if (!m_SetTopmost)
			SetWindowPos(&wndNoTopMost, 1,1,1,1, SWP_NOMOVE | SWP_NOSIZE);
		SetLongTimer(m_LongTimerWait);
	}
}

// At the moment, this only sets the mode buttons to show click type --
// it doesn't actually change any click type.
void CMouseToolDlg::SetClickType()
{
//	static int m_nOldClickType = LEFTMODE;

	if (!m_bMouseToolIsActive)
	{
		if  (  
//		m_bSmartDragIsOn ||
				m_ProcHandler.GetPressingButton()
			) 
		{
			m_nOldClickType = SHOWDRAGICONMODE;
			if (TrayIcon.IsInTray())
				TrayIcon.SetIcon(IDI_ICON_RED);
			else
				SetDragBitmap(THROTTLE_MIN_STEP+1);	// parameter doesn't matter
		}
		else
		{
			if (TrayIcon.IsInTray())
				TrayIcon.SetIcon(IDI_ICON_STOPPED);
			else
				FlattenAllBitmaps(true);
		}
		return;
	}

	// if timer is going, they shouldn't be flat.
	if (m_bBitmapsAreFlat)
		FlattenAllBitmaps(false);

//	are we dragging?
	if (!m_bClickedOnModeChanger && 
	   		(m_bSmartDragIsOn || m_ProcHandler.GetPressingButton() || m_bSentDownUpLastTick)
	   	) 
	{
		m_nOldClickType = SHOWDRAGICONMODE;
		if (TrayIcon.IsInTray())
			TrayIcon.SetIcon(IDI_ICON_RED);
		else
			SetDragBitmap(THROTTLE_MIN_STEP+1);	// parameter doesn't matter
		return;
	}

	// okay.  Timer's going and we're not dragging.
	int type = m_ProcHandler.GetClickType();

	if (type == m_nOldClickType)
		return;

	if (!m_bClickedOnModeChanger)
	{
		if (m_nOldClickType == SHOWDRAGICONMODE)
		{
			SetDragBitmap(0);
			m_nOldClickType = type;
			return;
		}
	}


// if in system tray, change icon and return
	if (TrayIcon.IsInTray())
	{
		if ((type==LEFTMODE) || (type==DRAGMODE) || ((!!type)==m_bSentDownUpLastTick) )
			TrayIcon.SetIcon(IDR_MAINFRAME);

		if (type==RIGHTMODE)
			TrayIcon.SetIcon(IDI_ICON_REVERSED);

		if (type == DOUBLEMODE)
			TrayIcon.SetIcon(IDI_ICON_DOUBLE);

		m_nOldClickType = type;
		return;
	}

// First, set the old bitmap to flat
	if (!m_bButtonsReversed)
	{
		if ( (m_nOldClickType==LEFTMODE)  || (m_nOldClickType==DRAGMODE) || (m_nOldClickType==SHOWDRAGICONMODE))
			m_LStaticControl.Flatten();

		if (m_nOldClickType == DOUBLEMODE) 
			m_DStaticControl.Flatten();

		if (m_nOldClickType == RIGHTMODE) 
			m_RStaticControl.Flatten();
	}
	else
	{
		if ( (m_nOldClickType==LEFTMODE)  || (m_nOldClickType==DRAGMODE) || (m_nOldClickType==SHOWDRAGICONMODE))
		{
			m_RStaticControl.Flatten();
			m_LStaticControl.Flatten();
		}

		if (m_nOldClickType == DOUBLEMODE) 
			m_DStaticControl.Flatten();

		if (m_nOldClickType == RIGHTMODE) 
			m_LStaticControl.Flatten();
	}


// Then set new bitmap
	if (!m_bButtonsReversed)
	{
		if ( (type==LEFTMODE) || (type==DRAGMODE) || ((!!type)==m_bSentDownUpLastTick) )
			m_LStaticControl.Down();

		if (type == DOUBLEMODE) 
			m_DStaticControl.Down();

		if (type == RIGHTMODE) 
			m_RStaticControl.Down();
	}
	else
	{
		if ( (type==LEFTMODE) || (type==DRAGMODE) || ((!!type)==m_bSentDownUpLastTick) )
			m_RStaticControl.Down();

		if (type == DOUBLEMODE) 
			m_DStaticControl.Down();

		if (type == RIGHTMODE) 
			m_LStaticControl.Down();
	}
		
	if (m_bSentDownUpLastTick)
		m_nOldClickType = SHOWDRAGICONMODE;
	else
		m_nOldClickType = type;

/*
	if (!m_bMouseToolIsActive)
		return;

	if (m_bBitmapsAreFlat)
		FlattenAllBitmaps(false);

	static int m_nOldClickType = LEFTMODE;
	
	int type = m_ProcHandler.GetClickType();

	if (type == m_nOldClickType)
		return;

// if in system tray, change icon and return
	if (TrayIcon.IsInTray())
	{
		if ((type==LEFTMODE) || (type==DRAGMODE))
			TrayIcon.SetIcon(IDR_MAINFRAME);

		if (type==RIGHTMODE)
			TrayIcon.SetIcon(IDI_ICON_REVERSED);

		if (type == DOUBLEMODE)
			TrayIcon.SetIcon(IDI_ICON_DOUBLE);

		m_nOldClickType = type;
		return;
	}

// First, set the old bitmap to flat
	if ( (m_nOldClickType==LEFTMODE)  || (m_nOldClickType==DRAGMODE) )
		m_LStaticControl.Flatten();

	if (m_nOldClickType == DOUBLEMODE) 
		m_DStaticControl.Flatten();

	if (m_nOldClickType == RIGHTMODE) 
		m_RStaticControl.Flatten();


// Then set new bitmap
	if ( (type==LEFTMODE) || (type==DRAGMODE) )
		m_LStaticControl.Down();

	if (type == DOUBLEMODE) 
		m_DStaticControl.Down();

	if (type == RIGHTMODE) 
		m_RStaticControl.Down();
		
	m_nOldClickType = type;
*/
}


// delete
void CMouseToolDlg::ShowContext(int type)
{
	int m_nOldClickType = m_ProcHandler.GetClickType();

//	MessageBox("Show Context");
	
	switch (type)
	{
		case CONTEXT_DEFAULT:
			type = LEFTMODE;
			break;
		case CONTEXT_DISABLE_SMART_DRAG:
			type = LEFTMODE;
			break;
		case CONTEXT_DOUBLE_CLICK:
			type = DOUBLEMODE;
//			MessageBox("Double Click");
			break;
		case CONTEXT_RIGHT_CLICK:
			type = RIGHTMODE;
			break;
	}



	if (type == m_nOldClickType)
		return;

// First, set the old bitmap to flat
	if (m_nOldClickType == LEFTMODE) 
		m_LStaticControl.Flatten();

	if (m_nOldClickType == DOUBLEMODE) 
		m_DStaticControl.Flatten();

	if (m_nOldClickType == RIGHTMODE) 
		m_RStaticControl.Flatten();


// Then set new bitmap

	if (type == LEFTMODE) 
		m_LStaticControl.Down();

	if (type == DOUBLEMODE) 
		m_DStaticControl.Down();

	if (type == RIGHTMODE) 
		m_RStaticControl.Down();
}

	
// ooooo
void CMouseToolDlg::OnOptionsbutton() 
{
	m_pshtOptions->m_pgGeneral.m_bSetTopmost	= m_SetTopmost;
	m_pshtOptions->m_pgGeneral.m_AudibleTick	= m_AudibleTick;
	m_pshtOptions->m_pgGeneral.m_bShowDrag		= m_bShowDrag;
	m_pshtOptions->m_pgGeneral.m_nDwellZoneSize	= m_nDwellZoneSize;
//	m_pshtOptions->m_pgGeneral.m_bSmartDragCheck= m_ProcHandler.m_bSmartDragEnabled;
	m_pshtOptions->m_pgGeneral.m_nSmartDragDelay= m_SmartDragDelay/100;
	m_pshtOptions->m_pgGeneral.m_nDwellTime		= m_TicksToWait;
	m_pshtOptions->m_pgGeneral.m_bOverrideNextOnly  = m_ProcHandler.GetOverrideNextOnly();
	m_pshtOptions->m_pgGeneral.m_nStretchTimerDelay = m_LongTimerWait;
	m_pshtOptions->m_pgGeneral.m_nStretchTimerDelay = m_LongTimerWait;
	m_pshtOptions->m_pgGeneral.m_bCheckIfMouseIsDown = m_bCheckIfMouseDown;


	m_pshtOptions->m_bMouseToolIsOn	= !!m_bMouseToolIsActive;

//	m_pshtOptions->m_pMouseToolWnd = this;
	CTime now;
	CTimeSpan minsToGo;
	now                  = CTime::GetCurrentTime();
	minsToGo             = m_LongTimerStopTime - now;
	if (m_LongTimerOn > 0) {
		m_pshtOptions->m_pgGeneral.m_bEnableStretchTimer = TRUE;
		m_pshtOptions->m_pgGeneral.m_nMinsToGo   = minsToGo.GetTotalMinutes()+1;
	} else {
		m_pshtOptions->m_pgGeneral.m_bEnableStretchTimer = FALSE;
		m_pshtOptions->m_pgGeneral.m_nMinsToGo   = 0;
	}

	m_pshtOptions->m_pgGeneral.VerifyValues();	// check for bad values

	bool ShortcutExists  = ((CMouseToolApp *)AfxGetApp())->DoShortcut(STARTUP_CHECKSTARTUP);
	m_pshtOptions->m_pgGeneral.m_bStartupCheck	= ShortcutExists;
	
	
	if (m_pshtOptions->DoModal() == IDOK) 
	{
		m_pshtOptions->m_pgGeneral.VerifyValues();	// check for bad values

		// set easy variables
		m_bCheckIfMouseDown = !!m_pshtOptions->m_pgGeneral.m_bCheckIfMouseIsDown;
		m_SetTopmost		= m_pshtOptions->m_pgGeneral.m_bSetTopmost;
		m_AudibleTick		= m_pshtOptions->m_pgGeneral.m_AudibleTick;
		m_bShowDrag			= (m_pshtOptions->m_pgGeneral.m_bShowDrag==TRUE);
		m_nDwellZoneSize	= m_pshtOptions->m_pgGeneral.m_nDwellZoneSize;
//		m_SlowClickEnabled	= m_pshtOptions->m_pgGeneral.m_bSmartDragCheck;
		m_SmartDragDelay	= m_pshtOptions->m_pgGeneral.m_nSmartDragDelay * 100;
		m_TicksToWait		= m_pshtOptions->m_pgGeneral.m_nDwellTime;
		m_ProcHandler.SetOverrideNextOnly(
			(m_pshtOptions->m_pgGeneral.m_bOverrideNextOnly==TRUE) );


		// Start MouseTool with Windows?		
		if (m_pshtOptions->m_pgGeneral.m_bStartupCheck != (ShortcutExists==TRUE)) {			// if user changed startup option
			if (m_pshtOptions->m_pgGeneral.m_bStartupCheck)			// if user wants startup option
				((CMouseToolApp *)AfxGetApp())->DoShortcut(STARTUP_SETSTARTUP);
			else
				((CMouseToolApp *)AfxGetApp())->DoShortcut(STARTUP_REMOVESTARTUP);
		}
		
		// Short timer delay
		if (m_bMouseToolIsActive)			// update short timer delay
			SetTimer(m_Milliseconds, m_TicksToWait);

		// Stretch Timer delay (long timer)
 		if (m_LongTimerWait != m_pshtOptions->m_pgGeneral.m_nStretchTimerDelay)	
 			StopLongTimer();                                               
		m_LongTimerWait = m_pshtOptions->m_pgGeneral.m_nStretchTimerDelay;
 		if (m_pshtOptions->m_pgGeneral.m_bEnableStretchTimer) {		// Stretch Timer enabled?
 			if (!m_LongTimerOn)                                            
 				SetLongTimer(m_pshtOptions->m_pgGeneral.m_nStretchTimerDelay);                            
 		} else 		// if the long timer was not checked                   
 			StopLongTimer();
                                        

		// Stay on top?
 		if (m_SetTopmost)				
 			SetWindowPos(&wndTopMost, 1,1,1,1, SWP_NOMOVE | SWP_NOSIZE);   
 		else                                                               
 			SetWindowPos(&wndNoTopMost, 1,1,1,1, SWP_NOMOVE | SWP_NOSIZE); 

		SaveConfig();                                                  
	}

	if (m_pshtOptions->m_pgKeys.m_bEnableHotkeys)
		m_pshtOptions->m_pgKeys.RegisterAllHotkeys();	// call each time, whether OK or Cancel
	else
		m_pshtOptions->m_pgKeys.UnRegisterAllHotkeys();	// call each time, whether OK or Cancel

	return;
}

void CMouseToolDlg::SetTimer(int ms, int ticks)
{
	CString str;
	double x;

	StopTimer();
	
	if (TimerID == UINT(-1))					// first time.  Start timer.
	{
		TimerID = CWnd::SetTimer(SHORT_TIMER_ID, ms, NULL);
	}

//	if (ms != m_Milliseconds)
//	{
//		KillTimer(TimerID);
//		TimerID = CWnd::SetTimer(SHORT_TIMER_ID, ms, NULL);
//	TimerID = 1;
//	}
	m_TicksToWait = ticks;

	m_LStaticControl.SetDelay(ticks);
	m_RStaticControl.SetDelay(ticks);
	m_DStaticControl.SetDelay(ticks);

	x = m_TicksToWait;
	x = x/10;
	m_bMouseToolIsActive = TRUE;
	m_Button1Control.SetBitmap(m_bmpGoBitmap);

	if (m_SetTopmost)
		SetWindowPos(&wndTopMost, 1,1,1,1, SWP_NOMOVE | SWP_NOSIZE);
	else
		SetWindowPos(&wndNoTopMost, 1,1,1,1, SWP_NOMOVE | SWP_NOSIZE);

	GetCursorPos(&m_MousePos);  // set structure.  It gets read in DontClickHere().
	DontClickHere();

	if (TrayIcon.IsInTray())
		TrayIcon.SetIcon(IDR_MAINFRAME);
}

void CMouseToolDlg::SetLongTimer(int minutes)
{
	UINT ms;
	CTimeSpan Delay(0, 0, minutes, 0);

	ms = 30017;						// Odd number so doesn't always fall on other timer
	
	m_LongTimerWait = minutes;

	LongTimerID = CWnd::SetTimer(LONG_TIMER_ID, ms, NULL);
	m_LongTimerElapsed = 0;
	m_LongTimerOn = TRUE;
	m_LongTimerStopTime = CTime::GetCurrentTime();
	m_LongTimerStopTime += Delay;
}

void CMouseToolDlg::StopLongTimer()
{
	KillTimer(LongTimerID);
	m_LongTimerOn = FALSE;
}

void CMouseToolDlg::StopTimer()
{
//	KillTimer(TimerID);
	m_bMouseToolIsActive = FALSE;
	m_Button1Control.SetBitmap(m_bmpStopBitmap);
	if (TrayIcon.IsInTray())
		TrayIcon.SetIcon(IDI_ICON_STOPPED);
}

LONG CMouseToolDlg::OnShutdown(UINT wParam, LONG lParam)
{
	ShutDown();
	return TRUE;
}

void CMouseToolDlg::ShutDown() 
{
	SaveConfig(); 
	m_pshtOptions->m_pgKeys.UnRegisterAllHotkeys();
	
	StopTimer();
	KillTimer(TimerID);

	if (TrayIcon.IsInTray())
		TrayIcon.SetIcon(0);

	delete m_pshtOptions;
	unsetMTHook (m_hWnd);
	m_bitBigSmall.DeleteObject();

	m_bitLeft.DeleteObject();
	m_bitRight.DeleteObject();
	m_bitDbl.DeleteObject();
	m_bmpStopBitmap.DeleteObject();
	m_bmpGoBitmap.DeleteObject();
}

void CMouseToolDlg::OnClose() 
{
	ShowWindow(TRUE);
	CDialog::OnClose();
}

BOOL CMouseToolDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	
	return CDialog::PreCreateWindow(cs);
}				 


int PastDueDate()
{
	CTime today=CTime::GetCurrentTime();
	UINT year,month,day;

	year = 1997;
	month = 10;
	day = 15;

	CTime DueDate(year, month, day, 0, 0, 0);
	CTimeSpan timeSpan = today - DueDate;
	if (timeSpan.GetDays() > 0) 
		return TRUE;
	else
		return FALSE;
}

void CMouseToolDlg::RestoreConfig()
{
	UINT val;
	int x,y;
    CWinApp* pApp = AfxGetApp();

  m_bFirstTime = (0==pApp->GetProfileInt("MouseTool", "AlreadyInitialized", 0));

	val = pApp->GetProfileInt("MouseTool", "AlreadyWarnedAbtSD", 0);
	m_pshtOptions->m_pgGeneral.m_bUserHasBeenWarned = (val==1);

	val = pApp->GetProfileInt("MouseTool", "AlreadyWarnedAbtNC", 0);
	m_pshtOptions->m_pgGeneral.m_bUserHasBeenWarnedNC = (val==1);

	val = pApp->GetProfileInt("MouseTool", "m_bAlreadyWarnedAbtCC", 0);
	m_pshtOptions->m_pgGeneral.m_bUserHasBeenWarnedCC = (val==1);

	val = pApp->GetProfileInt("MouseTool", "CheckIfMouseDown", 0);
	m_bCheckIfMouseDown = (val==1);

	val = pApp->GetProfileInt("MouseTool", "x", 200);
		x = (int) val;
	val = pApp->GetProfileInt("MouseTool", "y", 200);
		y = (int) val;

/////////////////////////////////////////////////////////////////////
	#if defined(READMOUSE)
		x = 827;
		y = 0;
	#endif
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
	#if defined(RECORDMOUSE)
		x = 827;
		y = 0;
	#endif
/////////////////////////////////////////////////////////////////////


	val = pApp->GetProfileInt("MouseTool", "TicksToWait", 5);
	m_TicksToWait = (int) val;
	if (m_TicksToWait < 0)
		m_TicksToWait = 5;

	val = pApp->GetProfileInt("MouseTool", "StayOnTop", TRUE);
	m_SetTopmost = val;

	val = pApp->GetProfileInt("MouseTool", "m_bMouseToolIsActive", FALSE);
	m_bMouseToolIsActive = val;

	val = pApp->GetProfileInt("MouseTool", "DraggingOnly", FALSE);
	m_DragOnly = val;

	val = pApp->GetProfileInt("MouseTool", "AudibleTick", TRUE);
	m_AudibleTick = (BOOL) val;

	val = pApp->GetProfileInt("MouseTool", "LongTimerOn", 0);
	m_LongTimerOn = (BOOL) val;

	// 30 minute delay for stretch timer
	val = pApp->GetProfileInt("MouseTool", "LongTimerWait", 30);
	m_LongTimerWait = val;

	val = pApp->GetProfileInt("MouseTool", "ShowDrag", true);
	m_bShowDrag = (val==TRUE);

	m_nDwellZoneSize = pApp->GetProfileInt("MouseTool", "DwellZoneSize", 2);

	if (m_SetTopmost)
		SetWindowPos(&wndTopMost, x,y,1,1, SWP_NOSIZE);
	else
		SetWindowPos(&wndNoTopMost, x,y,1,1, SWP_NOSIZE);
	
	// window large/small (MT's window can be made the size of four buttons)
	bWindowIsLarge = !!pApp->GetProfileInt("MouseTool", "WindowIsLarge", 1);

	if (!bWindowIsLarge) 
  {
		bWindowIsLarge = !bWindowIsLarge;
		GetWindowRect(&m_rectApp);			// so we can restore things
		OnSmallbutton();
	}

	// get minimized/maximized state of window
	bool bMinimized;
	bMinimized = !!pApp->GetProfileInt("MouseTool", "Minimized", 0);
	if (bMinimized) 
  {
		WINDOWPLACEMENT wp;

		GetWindowRect(&m_rectApp);			// so we can restore things
		wp.rcNormalPosition = m_rectApp;
		wp.length			= sizeof(WINDOWPLACEMENT);
		wp.showCmd			= SW_MINIMIZE;

		SetWindowPlacement(&wp);
	}

	val = pApp->GetProfileInt("MouseTool", "IsInTray", 0);
	if (val)
	{
		WINDOWPLACEMENT placement;
		GetWindowRect(&m_rectApp);			// so we can restore things
		GetWindowPlacement (&placement);
		SetWindowPlacement (&placement);
		TrayIcon.SetIcon(IDR_MAINFRAME);
	}

	// Smart Drag
	m_ProcHandler.m_bSmartDragEnabled = (pApp->GetProfileInt("MouseTool", "SmartDragEnabled", 0)==TRUE);
	m_SmartDragDelay = pApp->GetProfileInt("MouseTool", "SmartDragDelay", 300);

	// Override next only
	m_ProcHandler.m_bOverrideNextOnly = (pApp->GetProfileInt("MouseTool", "OverrideNextOnly", TRUE)==TRUE);

	// Are Contexts Enabled?
	m_pshtOptions->m_pgContext.m_bEnableContext = pApp->GetProfileInt("MouseTool", "EnableContexts", TRUE);

	// values for hotkeys
	m_pshtOptions->m_pgKeys.m_bEnableHotkeys		= (pApp->GetProfileInt("MouseTool", "EnablehotKey", 0)		== TRUE);
	m_pshtOptions->m_pgKeys.m_bWarnLeftHotkey		= (pApp->GetProfileInt("MouseTool", "WarnLeftHotkey", 1)	== TRUE);

	// Mode change hotkeys
	m_pshtOptions->m_pgKeys.m_khDblKey.m_vkey		= pApp->GetProfileInt("MouseTool", "hotKeyDblVal", 0);			
	m_pshtOptions->m_pgKeys.m_khDblKey.m_bShift		= (pApp->GetProfileInt("MouseTool", "hotKeyDblShift", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khDblKey.m_bCtrl		= (pApp->GetProfileInt("MouseTool", "hotKeyDblCtrl", 0)		== TRUE);
	m_pshtOptions->m_pgKeys.m_khDblKey.m_bAlt		= (pApp->GetProfileInt("MouseTool", "hotKeyDblAlt", 0)		== TRUE);

	m_pshtOptions->m_pgKeys.m_khRightKey.m_vkey		= pApp->GetProfileInt("MouseTool", "hotKeyRightVal", 0);
	m_pshtOptions->m_pgKeys.m_khRightKey.m_bShift	= (pApp->GetProfileInt("MouseTool", "hotKeyRightShift", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khRightKey.m_bCtrl	= (pApp->GetProfileInt("MouseTool", "hotKeyRightCtrl", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khRightKey.m_bAlt		= (pApp->GetProfileInt("MouseTool", "hotKeyRightAlt", 0)	== TRUE);

	m_pshtOptions->m_pgKeys.m_khStopKey.m_vkey		= pApp->GetProfileInt("MouseTool", "hotKeyStopVal", 12);			// default: ctrl-clear
	m_pshtOptions->m_pgKeys.m_khStopKey.m_bShift	= (pApp->GetProfileInt("MouseTool", "hotKeyStopShift", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khStopKey.m_bCtrl		= (pApp->GetProfileInt("MouseTool", "hotKeyStopCtrl", 1)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khStopKey.m_bAlt		= (pApp->GetProfileInt("MouseTool", "hotKeyStopAlt", 0)	== TRUE);

	// Mouse button hotkeys
	m_pshtOptions->m_pgKeys.m_khBtnLeft.m_vkey		=  pApp->GetProfileInt("MouseTool", "hotKeyBtnLeftVal", 145);		// default: ScrollLock
	m_pshtOptions->m_pgKeys.m_khBtnLeft.m_bShift	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnLeftShift", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khBtnLeft.m_bCtrl		= (pApp->GetProfileInt("MouseTool", "hotKeyBtnLeftCtrl", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khBtnLeft.m_bAlt		= (pApp->GetProfileInt("MouseTool", "hotKeyBtnLeftAlt", 0)	== TRUE);

	m_pshtOptions->m_pgKeys.m_khBtnRight.m_vkey		=  pApp->GetProfileInt("MouseTool", "hotKeyBtnRightVal", 106);		// default: keypad *
	m_pshtOptions->m_pgKeys.m_khBtnRight.m_bShift	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnRightShift", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khBtnRight.m_bCtrl	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnRightCtrl", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khBtnRight.m_bAlt		= (pApp->GetProfileInt("MouseTool", "hotKeyBtnRightAlt", 0)	== TRUE);

	m_pshtOptions->m_pgKeys.m_khBtnToggleLeft.m_vkey	=  pApp->GetProfileInt("MouseTool", "hotKeyBtnToggleVal", 107);	// default: keypad +
	m_pshtOptions->m_pgKeys.m_khBtnToggleLeft.m_bShift	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnToggleShift", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khBtnToggleLeft.m_bCtrl	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnToggleCtrl", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khBtnToggleLeft.m_bAlt	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnToggleAlt", 0)	== TRUE);

	m_pshtOptions->m_pgKeys.m_khBtnDouble.m_vkey	=  pApp->GetProfileInt("MouseTool", "hotKeyBtnDoubleVal", 109);		// default: keypad -
	m_pshtOptions->m_pgKeys.m_khBtnDouble.m_bShift	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnDoubleShift", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khBtnDouble.m_bCtrl	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnDoubleCtrl", 0)	== TRUE);
	m_pshtOptions->m_pgKeys.m_khBtnDouble.m_bAlt	= (pApp->GetProfileInt("MouseTool", "hotKeyBtnDoubleAlt", 0)	== TRUE);
	
	m_pshtOptions->m_pgKeys.RegisterAllHotkeys();		// this checks if hotkeys are enabled first
}



// add min/max state, and reduce/restore
// sssss
void CMouseToolDlg::SaveConfig()
{
	RECT rect;
    CWinApp* pApp = AfxGetApp();

	pApp->WriteProfileInt("MouseTool", "AlreadyInitialized", 1);

  pApp->WriteProfileInt("MouseTool", "AlreadyWarnedAbtSD", m_pshtOptions->m_pgGeneral.m_bUserHasBeenWarned);
	pApp->WriteProfileInt("MouseTool", "AlreadyWarnedAbtNC", m_pshtOptions->m_pgGeneral.m_bUserHasBeenWarnedNC);
	pApp->WriteProfileInt("MouseTool", "AlreadyWarnedAbtCC", m_pshtOptions->m_pgGeneral.m_bUserHasBeenWarnedCC);

	pApp->WriteProfileInt("MouseTool", "CheckIfMouseDown", m_bCheckIfMouseDown);

	if (IsIconic()) {
		pApp->WriteProfileInt("MouseTool", "x", m_rectApp.left);
		pApp->WriteProfileInt("MouseTool", "y", m_rectApp.top);
	} else {
		GetWindowRect(&rect);
		pApp->WriteProfileInt("MouseTool", "x", rect.left);
		pApp->WriteProfileInt("MouseTool", "y", rect.top);
	}
	pApp->WriteProfileInt("MouseTool", "IsInTray", TrayIcon.IsInTray());
	pApp->WriteProfileInt("MouseTool", "TicksToWait", m_TicksToWait);
	pApp->WriteProfileInt("MouseTool", "StayOnTop", m_SetTopmost);
	pApp->WriteProfileInt("MouseTool", "DraggingOnly", m_DragOnly);

	pApp->WriteProfileInt("MouseTool", "m_bMouseToolIsActive", m_bMouseToolIsActive);
	pApp->WriteProfileInt("MouseTool", "LongTimerOn", m_LongTimerOn);
	pApp->WriteProfileInt("MouseTool", "LongTimerWait", m_LongTimerWait);
	pApp->WriteProfileInt("MouseTool", "AudibleTick", m_AudibleTick);

	pApp->WriteProfileInt("MouseTool", "ShowDrag", m_bShowDrag);

	pApp->WriteProfileInt("MouseTool", "SmartDragEnabled", m_ProcHandler.m_bSmartDragEnabled);
	pApp->WriteProfileInt("MouseTool", "SmartDragDelay", m_SmartDragDelay);

//	pApp->WriteProfileInt("MouseTool", "SlowClickEnabled", m_SlowClickEnabled);
//	pApp->WriteProfileInt("MouseTool", "SlowClickDelay", m_SlowClickDelay);

	pApp->WriteProfileInt("MouseTool", "DwellZoneSize", m_nDwellZoneSize);


	// Override next only
	pApp->WriteProfileInt("MouseTool", "OverrideNextOnly", m_ProcHandler.m_bOverrideNextOnly);

	// Are Contexts Enabled?
	pApp->WriteProfileInt("MouseTool", "EnableContexts", m_pshtOptions->m_pgContext.m_bEnableContext);

	// values for hotkeys
	pApp->WriteProfileInt("MouseTool", "EnablehotKey", m_pshtOptions->m_pgKeys.m_bEnableHotkeys);
	
	// window large/small
	pApp->WriteProfileInt("MouseTool", "WindowIsLarge", bWindowIsLarge);
	// window minimized/restore
	pApp->WriteProfileInt("MouseTool", "Minimized", IsIconic());

	pApp->WriteProfileInt("MouseTool", "WarnLeftHotkey", m_pshtOptions->m_pgKeys.m_bWarnLeftHotkey);

	// Mode change hotkeys
	pApp->WriteProfileInt("MouseTool", "hotKeyDblVal", m_pshtOptions->m_pgKeys.m_khDblKey.m_vkey);
	pApp->WriteProfileInt("MouseTool", "hotKeyDblShift", m_pshtOptions->m_pgKeys.m_khDblKey.m_bShift);
	pApp->WriteProfileInt("MouseTool", "hotKeyDblCtrl", m_pshtOptions->m_pgKeys.m_khDblKey.m_bCtrl);
	pApp->WriteProfileInt("MouseTool", "hotKeyDblAlt", m_pshtOptions->m_pgKeys.m_khDblKey.m_bAlt);

	pApp->WriteProfileInt("MouseTool", "hotKeyRightVal", m_pshtOptions->m_pgKeys.m_khRightKey.m_vkey);
	pApp->WriteProfileInt("MouseTool", "hotKeyRightShift", m_pshtOptions->m_pgKeys.m_khRightKey.m_bShift);
	pApp->WriteProfileInt("MouseTool", "hotKeyRightCtrl", m_pshtOptions->m_pgKeys.m_khRightKey.m_bCtrl);
	pApp->WriteProfileInt("MouseTool", "hotKeyRightAlt", m_pshtOptions->m_pgKeys.m_khRightKey.m_bAlt);

	pApp->WriteProfileInt("MouseTool", "hotKeyStopVal", m_pshtOptions->m_pgKeys.m_khStopKey.m_vkey);
	pApp->WriteProfileInt("MouseTool", "hotKeyStopShift", m_pshtOptions->m_pgKeys.m_khStopKey.m_bShift);
	pApp->WriteProfileInt("MouseTool", "hotKeyStopCtrl", m_pshtOptions->m_pgKeys.m_khStopKey.m_bCtrl);
	pApp->WriteProfileInt("MouseTool", "hotKeyStopAlt", m_pshtOptions->m_pgKeys.m_khStopKey.m_bAlt);

	// Mouse button hotkeys
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnLeftVal", m_pshtOptions->m_pgKeys.m_khBtnLeft.m_vkey);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnLeftShift", m_pshtOptions->m_pgKeys.m_khBtnLeft.m_bShift);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnLeftCtrl", m_pshtOptions->m_pgKeys.m_khBtnLeft.m_bCtrl);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnLeftAlt", m_pshtOptions->m_pgKeys.m_khBtnLeft.m_bAlt);

	pApp->WriteProfileInt("MouseTool", "hotKeyBtnRightVal", m_pshtOptions->m_pgKeys.m_khBtnRight.m_vkey);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnRightShift", m_pshtOptions->m_pgKeys.m_khBtnRight.m_bShift);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnRightCtrl", m_pshtOptions->m_pgKeys.m_khBtnRight.m_bCtrl);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnRightAlt", m_pshtOptions->m_pgKeys.m_khBtnRight.m_bAlt);

	pApp->WriteProfileInt("MouseTool", "hotKeyBtnToggleVal", m_pshtOptions->m_pgKeys.m_khBtnToggleLeft.m_vkey);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnToggleShift", m_pshtOptions->m_pgKeys.m_khBtnToggleLeft.m_bShift);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnToggleCtrl", m_pshtOptions->m_pgKeys.m_khBtnToggleLeft.m_bCtrl);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnToggleAlt", m_pshtOptions->m_pgKeys.m_khBtnToggleLeft.m_bAlt);

	pApp->WriteProfileInt("MouseTool", "hotKeyBtnDoubleVal", m_pshtOptions->m_pgKeys.m_khBtnDouble.m_vkey);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnDoubleShift", m_pshtOptions->m_pgKeys.m_khBtnDouble.m_bShift);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnDoubleCtrl", m_pshtOptions->m_pgKeys.m_khBtnDouble.m_bCtrl);
	pApp->WriteProfileInt("MouseTool", "hotKeyBtnDoubleAlt", m_pshtOptions->m_pgKeys.m_khBtnDouble.m_bAlt);

}

// bbbbbb
void CMouseToolDlg::BeginDrag()
{
	m_bSmartDragIsOn = true;
//	if (!m_bButtonsReversed)
		MouseLDown();
//	else
//		MouseRDown();
}
void CMouseToolDlg::EndDrag()
{
	m_bSmartDragIsOn = false;
//	if (!m_bButtonsReversed)
		MouseLUp();
//	else
//		MouseRUp();
}

// There are four possibilities here.
// 1.  First time through.  Click down, start SmartDragTimer, and return.
// 2.  Normal timer event.  We haven't waited long enough to start drag.  Return.
// 3.  SmartDragTimer event.  If samepoint, click up and return.  Else, start drag.
// 4.  Normal timer event while dragging.  If we've pause long enough, upclick.
//						else, update position info and return.
void CMouseToolDlg::SmartDrag(int nReason) 
{
	static bool bDragging = false;
//	m_Edit1Control.SetWindowText("Begin SD");

	GetCursorPos(&m_MousePos);

	switch (nReason) {
		case SD_CLICKDOWN:
			PlayTickSound();
			BeginDrag();
			m_bWaitingForUpclick = true;
			m_OldMousePos.x = m_MousePos.x;
			m_OldMousePos.y = m_MousePos.y;
			m_StationaryTicks = m_TicksToWait+1;
			SetClickType();
//			SetDragBitmap (THROTTLE_MIN_STEP+1);			// set drag bitmap		
			m_nSmartDragTimerID = CWnd::SetTimer(SLOW_CLICK_TIMER_ID, m_SmartDragDelay*SD_TIMER_SCALE, NULL);
			break;

		case SD_NORMAL_TIMER: 
			if (!bDragging) 
				return;

			if ( SamePoint(m_MousePos, m_OldMousePos) )
				m_StationaryTicks++;
			else
				m_StationaryTicks = 0;

			if (m_StationaryTicks == m_TicksToWait + 2)			// stop counting after the click
				m_StationaryTicks -= 1;


			m_OldMousePos.x = m_MousePos.x;
			m_OldMousePos.y = m_MousePos.y;

			if (m_StationaryTicks == m_TicksToWait) {			// finished the drag
				m_bWaitingForUpclick = false;
				EndDrag();

				SetClickType();
//				SetDragBitmap (0);			// reset drag bitmap		
				bDragging = false;
			}			
			break;

		case SD_SMART_DRAG_TIMER:
			KillTimer(m_nSmartDragTimerID);
			m_nSmartDragTimerID = 0;
			if (SamePoint(m_MousePos, m_OldMousePos)) {
				m_bWaitingForUpclick = false;
				EndDrag();
				SetClickType();
//				SetDragBitmap (0);			// reset drag bitmap		
			}
			else
			// start the drag
			{
				m_StationaryTicks = 0;
				bDragging = true;
		//		MessageBox("m_DraggingByDelay");
			}
			break;
	}
//	m_Edit1Control.SetWindowText("End SD");
}


// void CMouseToolDlg::SlowClick()                                                     
// {                                                                                   
// 	if (m_DraggingByDelay) {                                                           
// 		EndDrag();                                                                     
// 		m_DraggingByDelay = FALSE;                                                     
// 		SetClickType();                                                                
// 		return;                                                                        
// 	}                                                                                  
// 	PlayTickSound();                                                                   
// 	m_nSmartDragTimerID = CWnd::SetTimer(SLOW_CLICK_TIMER_ID, m_SmartDragDelay, NULL); 
// 	if (!m_nSmartDragTimerID) {                                                        
// 		MessageBox("Not enough system Resources!");                                    
// 		exit(0);                                                                       
// 	}                                                                                  
// 	BeginDrag();                                                                       
// 	m_OldMousePos.x = m_MousePos.x;                                                    
// 	m_OldMousePos.y = m_MousePos.y;                                                    
// 	m_StationaryTicks = m_TicksToWait+1;                                               
//                                                                                     
// 	SetClickType();                                                                    
// }                                                                                   

void CMouseToolDlg::SmartDragTimerEvent() 
{
	SmartDrag(SD_SMART_DRAG_TIMER);
	return;

	KillTimer(m_nSmartDragTimerID);
	m_nSmartDragTimerID = 0;
	GetCursorPos(&m_MousePos);
	if (SamePoint(m_MousePos, m_OldMousePos)) {
		EndDrag();
		SetClickType();
//		SetDragBitmap (0);			// reset drag bitmap		
	}
	else 
	{
		m_DraggingByDelay = TRUE;
		MessageBox("m_DraggingByDelay");
	}
	if (!CWnd::SetTimer(SHORT_TIMER_ID, m_Milliseconds, NULL)) {
		MessageBox("Not enough system Resources!");
		exit(0);
	}
}


void CMouseToolDlg::ncLUp(UINT nHitTest, POINTS point)
{
	if (m_bStopDragging)
		m_bNCDragging = false;					// Handle dragging of MT ourselves
	m_bStopDragging = true;
}

// Monitor nonclient mouse messages.
// If the user minimizes or closes, handle it here.
// (Otherwise the program waits on the up click before processing timer...)
// llllll
void CMouseToolDlg::ncLDown(UINT nHitTest, POINTS point)
{
//	CString str;
//	static count=0;
	RECT rect;
	CPoint p;
	WINDOWPLACEMENT placement;


	// point is in screen coordinates.  Convert those to relative coords.
	GetWindowRect(&rect);
	p.x = point.x-rect.left;
	p.y = point.y-rect.top;
	
	// is this in the minimize box?
	if ( (p.x>_ButtonRect.left) && (p.x<_ButtonRect.right) ) 
	{
		if ( (p.y>_ButtonRect.top) && (p.y<=_ButtonRect.bottom) ) {
			GetWindowRect(&m_rectApp);			// so we can restore things
			GetWindowPlacement (&placement);
			SetWindowPlacement (&placement);

			if (m_bMouseToolIsActive)
				TrayIcon.SetIcon(IDR_MAINFRAME);
			else
				TrayIcon.SetIcon(IDI_ICON_STOPPED);

//			TrayIcon.SetIcon(IDR_MAINFRAME);

			ShowWindow(FALSE);
			PostMessage(WM_NCLBUTTONUP);

			return;
			// end modified for testing.  10-6-98
		}
	}

	// is this in the close box?
	if ( (p.x>xButtonRect.left) && (p.x<xButtonRect.right) ) 
	{
		if ( (p.y>xButtonRect.top) && (p.y<=xButtonRect.bottom) ) 
			PostMessage(WM_CLOSE);
	}

	if (p.x<_ButtonRect.left) 
	{
//		CDialog::ncLDown(nHitTest, point)
//		CPoint pt(point.x, point.y);
//		OnNcLButtonDown(nHitTest, pt );
//		return;
//	}

	// if we're not on any button, handle dragging of MT ourselves
		if (p.x<_ButtonRect.left) 
		{
			m_bNCDragging = true;					 
			m_bStopDragging = false;
			MouseLUp();

//			if (m_bToggleButtonOn)
//				m_ProcHandler.IncClickCount();	// a hack to enable dragging of mt window

//			m_bMTSentLastClick = true;		// test


			m_ptDragStartPointMouse.x = point.x;
			m_ptDragStartPointMouse.y = point.y;
			RECT rect;
			GetWindowRect(&rect);
			m_ptDragStartPointApp.x = rect.left;
			m_ptDragStartPointApp.y = rect.top;
		}
	}

}

void CMouseToolDlg::PlayTickSound()
{
//	MessageBox(m_TapWaveFile);
	if (m_AudibleTick)
		PlaySound(m_TapWaveFile, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

void CMouseToolDlg::OnHelpbutton() 
{
	char progfile[MAX_PATH];
	char sPath[MAX_PATH];

	// Get the full path of the MouseTool.exe file
	if ( GetModuleFileName( NULL, sPath, MAX_PATH) != 0) {
		* ( strrchr( sPath, '\\' ) + 1 ) = '\0';
	}
	strcpy (progfile, sPath);

	if (progfile[strlen(progfile)] == '\\')		// append a backslash if needed
		strcat (progfile, "\\");

	strcat (progfile, "MouseTool.hlp>Wnd");		// does the string already end in "\" ?

	::WinHelp(m_hWnd, progfile, HELP_CONTEXT, 0x2066);

//	::WinHelp(0x2066);		// HIDD_MOUSETOOL_DIALOG
//	WinHelp(0);		// HIDD_MOUSETOOL_DIALOG
}

// when MouseTool is turned off, its controls should be disabled.
void CMouseToolDlg::DisableControls()
{
//	m_Edit1Control.SetWindowText("Off");
//	m_Edit1Control.EnableWindow(FALSE);
	m_JoyProgress.EnableWindow(FALSE);
}
void CMouseToolDlg::EnableControls()
{
//	m_Edit1Control.EnableWindow(TRUE);
	m_JoyProgress.EnableWindow(TRUE);
}

void CMouseToolDlg::SetCaptionRects()
{
// Have to get size and position of caption buttons, relative to MouseTool window.
// See "title bar size.txt" for details
	RECT rect;
	GetWindowRect(&rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);

	xButtonRect.left = w - 5 - ncm.iCaptionWidth;
	xButtonRect.top = 5;
	xButtonRect.right = w - 5;
	xButtonRect.bottom = 5 + h;

	_ButtonRect.left = w - 5 - 3*ncm.iCaptionWidth - 2;
	_ButtonRect.top = 5;
	_ButtonRect.right = w - 5 - 2*ncm.iCaptionWidth - 2;
	_ButtonRect.bottom = 5 + h;
}



bool CMouseToolDlg::PtInStatic(const CPoint &point, const CStatic &stat)
{
	RECT strucRect;
	CRect rectStatic, rectClient, rectApp;
	
	stat.GetWindowRect(&strucRect);
	rectStatic = strucRect;

	GetClientRect(&strucRect);
	rectClient = strucRect;

	GetWindowRect(&strucRect);
	rectApp = strucRect;

	int nNCHeight = (rectApp.bottom-rectApp.top) - rectClient.bottom;

	rectStatic.left  -= rectApp.left;
	rectStatic.right -= rectApp.left;
	rectStatic.top    -= (rectApp.top + nNCHeight);
	rectStatic.bottom -= (rectApp.top + nNCHeight);

// point is now relative to the client area, not the app.
// rectStatic is relative to the app.

	if (rectStatic.PtInRect(point)) 
		return true;
	return false;
}



void CMouseToolDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bMouseToolIsActive) 
		return;

	m_bMouseInWindow = true;

	m_bInLStatic = false;
	m_bInRStatic = false;
	m_bInDStatic = false;

	if (PtInStatic(point, m_LStaticControl)) {
		m_bInLStatic = true;
		m_LStaticControl.Up();
	} else
		m_LStaticControl.Activate(true);

	if (PtInStatic(point, m_RStaticControl)) {
		m_bInRStatic = true;
		m_RStaticControl.Up();
	} else
		m_RStaticControl.Activate(true);

	if (PtInStatic(point, m_DStaticControl)) {
		m_bInDStatic = true;
		m_DStaticControl.Up();
	} else
		m_DStaticControl.Activate(true);


	CDialog::OnMouseMove(nFlags, point);
}

// ssss
void CMouseToolDlg::OnSmallbutton() 
{
	RECT rectButton;
	int x, y;

	if (bWindowIsLarge) {
		m_bitBigSmall.DeleteObject();
		m_bitBigSmall.LoadMappedBitmap(IDB_MAKEBIG);
		m_SmallButton.SetBitmap(m_bitBigSmall);

		// we need to resize the window twice.  The user doesn't need to see this.
		ShowWindow(FALSE);

		GetWindowRect(&m_rectApp);			// so we can restore things
		ModifyStyle(WS_CAPTION, 0);
		SetWindowPos(&wndTopMost, 1,1,120, 60, SWP_NOMOVE);

		m_SmallButton.GetWindowRect(&rectButton);
		x = rectButton.right - m_rectApp.left + 5;
		y = rectButton.bottom - m_rectApp.top + 5;
		SetWindowPos(&wndTopMost, 1,1, x, y, SWP_NOMOVE);
	
		ShowWindow(TRUE);
		bWindowIsLarge = false;
	} else {
		m_bitBigSmall.DeleteObject();
		m_bitBigSmall.LoadMappedBitmap(IDB_MAKESMALL);
		m_SmallButton.SetBitmap(m_bitBigSmall);

		ModifyStyle(0, WS_CAPTION);
		x = m_rectApp.right - m_rectApp.left;
		y = m_rectApp.bottom - m_rectApp.top;
		SetWindowPos(&wndTopMost, 1,1, x,y, SWP_NOMOVE);
		bWindowIsLarge = true;
	}		
}

// mmmm
// Called whenever user clicks in MouseTool window
void CMouseToolDlg::CheckModeChangers(CPoint point)
{
	if (!m_bMouseToolIsActive)
		return;

	if (PtInStatic(point, m_LStaticControl)) 
	{
		m_bClickedOnModeChanger = true;
		if (m_bButtonsReversed)
			m_ProcHandler.SetClickType(RIGHTMODE);
		else
			m_ProcHandler.SetClickType(LEFTMODE);

		SetClickType();
	}

	if (PtInStatic(point, m_RStaticControl)) 
	{
		m_bClickedOnModeChanger = true;
		if (m_bButtonsReversed)
			m_ProcHandler.SetClickType(LEFTMODE);
		else
			m_ProcHandler.SetClickType(RIGHTMODE);

		SetClickType();
	}

	if (PtInStatic(point, m_DStaticControl)) 
	{
		m_bClickedOnModeChanger = true;
		m_ProcHandler.SetClickType(DOUBLEMODE);
		SetClickType();
	}
}

void CMouseToolDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CheckModeChangers(point);	

	CDialog::OnLButtonDown(nFlags, point);
}

void CMouseToolDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CheckModeChangers(point);	
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CMouseToolDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CheckModeChangers(point);	
	
	CDialog::OnLButtonDblClk(nFlags, point);
}


// hhhhh
/*---------------------------------------------**
** This event happens whenever the mouse moves **
**---------------------------------------------*/
LONG CMouseToolDlg::OnHook(UINT wParam, LONG lParam)
{
	if (m_bClosing)
		return 0;

	m_pshtOptions->OnHook(wParam, lParam);

	if (m_bNCDragging) {			// If we're dragging the MouseTool window
		CPoint ptNewAppPos;
		GetCursorPos(&ptNewAppPos);

		ptNewAppPos.x -= m_ptDragStartPointMouse.x;			// ptNewAppPos is now the change in position
		ptNewAppPos.y -= m_ptDragStartPointMouse.y;			// ptNewAppPos is now the change in position
		ptNewAppPos += m_ptDragStartPointApp;			// ptNewAppPos is now the new app position

		SetWindowPos(0, ptNewAppPos.x, ptNewAppPos.y, 0,0, SWP_NOSIZE | SWP_NOZORDER);
	}
	return 0;
}

/*------------------------------------------------------**
** This event happens whenever a key down event occurs  **
**------------------------------------------------------*/
LONG CMouseToolDlg::OnKeyHook(UINT wParam, LONG lParam)
{
	if (m_bClosing)
		return 0;

	if (!m_bMouseToolIsActive)
		SetClickType();

	if (!m_pshtOptions->m_pgKeys.m_bEnableHotkeys)			// if hotkeys are disabled, return
		return 0;

	int nKeyType = (m_pshtOptions->m_pgKeys).OnKeyHook(KEY_DOWN, wParam, lParam);
	if (nKeyType)		// If nonzero, then it's a hotkey
	{
		if (nKeyType == HOTKEYS_LEFT_BTN) 
		{
			if (!m_ProcHandler.GetPressingButton())
			{
				MouseLDown();
				m_ProcHandler.SetPressingButton(true);
				SetClickType();
			}
		}
//		if (nKeyType == HOTKEYS_RIGHT_BTN) 
//		{
//			if (!m_ProcHandler.GetPressingButton())
//			{
//				MouseRDown();
//				m_ProcHandler.SetPressingButton(true);
//			}
//		}

//		if (nKeyType == HOTKEYS_STOP) 
//			OnButton1();
//		if (!m_bMouseToolIsActive)
//			return 0;

//		if (nKeyType == HOTKEYS_DBL) {
//			if (m_ProcHandler.GetClickType()==DOUBLEMODE)
//				m_ProcHandler.SetClickType(LEFTMODE);		// if already double mode, reset
//			else
//				m_ProcHandler.SetClickType(DOUBLEMODE);
//		}
//		if (nKeyType == HOTKEYS_RIGHT) {
//			if (m_ProcHandler.GetClickType()==RIGHTMODE)
//				m_ProcHandler.SetClickType(LEFTMODE);		// if already double mode, reset
//			else
//				m_ProcHandler.SetClickType(RIGHTMODE);
//		}
	}
	return 0;
}

LONG CMouseToolDlg::OnKeyUpHook(UINT wParam, LONG lParam)
{
	if (m_bClosing)
		return 0;

	m_bUserIsClicking = false;

	if (!m_bMouseToolIsActive)
		SetClickType();

	if (!m_pshtOptions->m_pgKeys.m_bEnableHotkeys)			// if hotkeys are disabled, return
		return 0;

	int nKeyType = (m_pshtOptions->m_pgKeys).OnKeyHook(KEY_UP, wParam, lParam);
	if (nKeyType) 
	{
		if (nKeyType == HOTKEYS_LEFT_BTN) 
		{
	 		if (m_ProcHandler.GetPressingButton())
			{
				MouseLUp();
			}

			m_ProcHandler.SetPressingButton(false);
			SetClickType();
			m_StationaryTicks = m_TicksToWait + 1;		// Don't click here
		}
//		if (nKeyType == HOTKEYS_RIGHT_BTN) 
//		{
//			MouseRUp();
//
//			m_ProcHandler.SetPressingButton(false);
//			m_StationaryTicks = m_TicksToWait + 1;		// Don't click here
//		}
	}
	return 0;
}


/* ----------------------------------------------------- */
/* ShareLock-handling routines begin                     */
/* ----------------------------------------------------- */

BEGIN_EVENTSINK_MAP(CMouseToolDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMouseToolDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()





// *************************************************************
// From RegTest

int GetLen(unsigned char *str)
{
	int n = 0;

	while (str[n] != '\0')
		n++;
	return n;
}

void EncodeStr(char *cstr)
{
	int n;

	n = 0;
	while (cstr[n] != '\0') {
		cstr[n] = (cstr[n])+1;
		n++;
	}
}
void DecodeStr(char *cstr)
{
	int n;

	n = 0;
	while (cstr[n] != '\0') {
		cstr[n] = (cstr[n])-1;
		n++;
	}
}


void CMouseToolDlg::EnterHelpMode()
{
	m_ProcHandler.EnterHelpMode();
}


// Still to do:
// Add different offsets for different tabs
// If mt is off when user clicks on ? button, let them know it won't work.
// Topic text.
void CMouseToolDlg::CallContextHelp()
{
	m_ProcHandler.ExitHelpMode();
	int nId = m_ProcHandler.GetChildHelpIdAtMouse();
	if (nId==0)
		return;
	long nContext = nId + m_pshtOptions->GetHelpMapOffset();

	char progfile[MAX_PATH];
	char sPath[MAX_PATH];

	// Get the full path of the MouseTool.exe file
	if ( GetModuleFileName( NULL, sPath, MAX_PATH) != 0) 
		* ( strrchr( sPath, '\\' ) + 1 ) = '\0';
	strcpy (progfile, sPath);

	if (progfile[strlen(progfile)] == '\\')		// append a backslash if needed
		strcat (progfile, "\\");

	strcat (progfile, "MouseTool.hlp");
//	strcat (progfile, "\\MouseTool.hlp>Wnd");
		
	::WinHelp(m_hWnd, progfile, HELP_CONTEXTPOPUP, nContext);

	return;
}

// bool CMouseToolDlg::InHelpMode()
//{
//	return m_ProcHandler.
//}

void CMouseToolDlg::OnTrayDouble()
{
	m_ProcHandler.SetClickType(DOUBLEMODE);
	SetClickType();
	return;
}

void CMouseToolDlg::OnTrayLeft()
{
	m_ProcHandler.SetClickType(LEFTMODE);
	SetClickType();
	return;
}

void CMouseToolDlg::OnTrayRight()
{
	m_ProcHandler.SetClickType(RIGHTMODE);
	SetClickType();
	return;
}

void CMouseToolDlg::OnTrayRestore()
{
	TrayIcon.SetIcon(0);
	ShowWindow(TRUE);
	return;
}

void CMouseToolDlg::OnTrayStartStop()
{
	OnButton1();
	return;
}

void CMouseToolDlg::OnTrayNextOnly()
{
	m_ProcHandler.ToggleOverrideNextOnly();
	return;
}

void CMouseToolDlg::OnTrayOpenGeneral()
{
	m_pshtOptions->OpenAtPage(OPT_GENERAL);
	OnOptionsbutton();
	return;
}

void CMouseToolDlg::OnTrayOpenKeys()
{
	m_pshtOptions->OpenAtPage(OPT_KEYS);
	OnOptionsbutton();
	return;
}

void CMouseToolDlg::OnTrayOpenContext()
{
	m_pshtOptions->OpenAtPage(OPT_CONTEXT);
	OnOptionsbutton();
	return;
}

// Routines for managing System Tray
LONG CMouseToolDlg::OnTrayMsg(UINT wParam, LONG lParam)
{
	if (lParam==WM_MOUSEMOVE)
		return 0;

	TrayIcon.SetNotificationWnd(this, UWM_MOUSETOOLTRAY);
	TrayIcon.SetFlags(!!m_bMouseToolIsActive, m_ProcHandler.GetOverrideNextOnly());

	bool bRes = !!unsetMTHook (m_hWnd);

	LRESULT res = TrayIcon.OnTrayNotification(wParam, lParam);
	
	if (!setMTHook(m_hWnd, 487)) {
	}

	return res;
}

// GetAsyncKeyState returns band info about mouse clicks, so
// I have to watch the clicks myself...
LONG CMouseToolDlg::OnClickHook(UINT wParam, LONG lParam)
{
/*
//	m_Edit1Control.SetWindowText("down");
	m_ProcHandler.OnClickHook(KEY_DOWN, wParam, lParam);

	if (m_bToggleButtonOn)			// are we dragging?
	{
		int n = m_ProcHandler.DecClickCount();
	CString str;
	str.Format("%d", n);
	m_Edit1Control.SetWindowText(str);
		if (!n)					// Don't unclick when WE send the click
		{
			m_ProcHandler.SetPressingButton(false);
			MouseLUp();
			m_StationaryTicks = m_TicksToWait + 1;		// Don't click here
			SetDragBitmap (0);			// set drag bitmap		
			m_bToggleButtonOn = false;
		}
	}
*/
//	m_Edit1Control.SetWindowText("Begin OnClickHook");

	m_StationaryTicks = m_TicksToWait + 1;

//	m_nTicksSinceLastClick++;

	if (m_bSentDownUpLastTick)
		return(0);
		
	m_bUserIsClicking = true;

	if (m_bClosing)
		return 0;

	if (m_bDraggingMouseToolWithToggleKey)
		return 0;

	if (m_bToggleButtonOn)			// are we dragging?
	{
		if (m_bMTSentLastClick)					// Don't unclick when WE send the click
			m_bMTSentLastClick = false;
		else
		{
			m_ProcHandler.SetPressingButton(false);
			MouseLUp();
			m_StationaryTicks = m_TicksToWait + 1;		// Don't click here
			SetClickType();
//			SetDragBitmap (0);			// set drag bitmap		
			m_bToggleButtonOn = false;
		}
	}
	
	return 0;
}
LONG CMouseToolDlg::OnClickUpHook(UINT wParam, LONG lParam)
{
/*
	int n = m_ProcHandler.DecClickCount();
	CString str;
	str.Format("%d", n);
	m_Edit1Control.SetWindowText(str);
	if (!n)					// Don't unclick when WE send the click
//	if (!m_ProcHandler.DecClickCount())					// Don't unclick when WE send the click
	{
//		m_Edit1Control.SetWindowText("up");
		m_ProcHandler.OnClickHook(KEY_UP, wParam, lParam);
	}
*/
//	m_Edit1Control.SetWindowText("Begin OnClickUpHook");
	m_StationaryTicks = m_TicksToWait + 1;

	m_bUserIsClicking = false;

	if (m_bClosing)
		return 0;

	if (m_bDraggingMouseToolWithToggleKey)
		return 0;

	if (m_bMTSentLastClick)					// Don't unclick when WE send the click
		m_bMTSentLastClick = false;
	else
	{
//		m_Edit1Control.SetWindowText("up");
		m_ProcHandler.OnClickHook(KEY_UP, wParam, lParam);
	}

	return 0;
}

void CMouseToolDlg::OnTrayClose()
{
	m_bClosing = true;
	PostMessage(WM_CLOSE);
}

// called in OnTimer if GetPressingButton is true (if we've clicked down with any hotkey)
// Left button hotkey gets stuck down in some situations.
// Timer keeps going, though, so this should unstick it.
void CMouseToolDlg::UnstickHotkey()
{
	bool bKeyState;

	int nKey = (m_pshtOptions->m_pgKeys).m_khBtnLeft.GetVKey();
	bKeyState = !!(GetAsyncKeyState(nKey) & 0x8000);

	if (!bKeyState)
	{
		if (!m_bToggleButtonOn)		// don't unstick the toggle button
		{
			MouseLUp();
			m_ProcHandler.SetPressingButton(false);
			SetClickType();
			m_StationaryTicks = m_TicksToWait + 1;		// Don't click here
		}
	}

}

//////////////////////////////////////////////////////////////////
////////  This routine is obsolete.
////////  Toggle key now handled by CheckKeys(), which is called by OnTimer
// Ideally:
// 1. toggle key hasn't been clicked.  m_bToggleButtonOn is false.
// 2. Tk is being clicked.  m_bToggleButtonOn is true.
// 3. tk is up.  m_bToggleButtonOn is true
// 4. tk is down again.  m_bToggleButtonOn is false.
// 5. tk is up.  m_bToggleButtonOn is false.
// 
// but it gets stuck when you click on a control menu.
// It finishes the button down, so m_bToggleButtonOn is true.
// So, if m_bToggleButtonOn is true, and the key is up, set a flag.
// if, after that, m_bToggleButtonOn is true, the flag is set, and the key is pressed, unstick.
void CMouseToolDlg::UnstickToggleKey()
{
	static bool bUnstickNextTime = false;
	bool bKeyState;

	CString str;
//	static int n;

	int nKey = (m_pshtOptions->m_pgKeys).m_khBtnToggleLeft.GetVKey();
	bKeyState = !!(GetAsyncKeyState(nKey) & 0x8000);

	str.Format("unstick: <%d>", (int) bKeyState);
//	m_Edit1Control.SetWindowText(str);

	// Toggle on is active, and we're not pressing the button any more.
	if (m_bToggleButtonOn && !bKeyState)
	{
		bUnstickNextTime = true;
//		m_Edit1Control.SetWindowText("First");
		return;
	}

	// It's stuck.  Send upclick to unstick it.
	if (m_bToggleButtonOn && bKeyState && bUnstickNextTime)
	{
		bUnstickNextTime = false;
		MouseLUp();
		m_ProcHandler.SetPressingButton(false);
		SetClickType();
		m_StationaryTicks = m_TicksToWait + 1;		// Don't click here
//		m_Edit1Control.SetWindowText("second");
	
		return;
	}
}

void CMouseToolDlg::CheckKeys()
{
	static bool bAlreadyProcessedKeyDown = false;

	if (!m_pshtOptions->m_pgKeys.m_bEnableHotkeys)			// if hotkeys are disabled, return
		return;

	// is toggle key pressed?
//	bool bKeyState;
//	int nKey = (m_pshtOptions->m_pgKeys).m_khBtnToggleLeft.GetVKey();
//	bKeyState = (GetAsyncKeyState(nKey) & 0x8000);

//////////////////////////////////////////////////
	// for testing
//	CString str;

//	str.Format("unstick: <%d>", (int) bKeyState);
//	m_Edit1Control.SetWindowText(str);
/////////////////////////////////////////////////

	if ( m_bToggleKeyWasPressed )
	{
		m_bToggleKeyWasPressed = false;

		if (bAlreadyProcessedKeyDown)						// Only change the state the first time through
			return;
		bAlreadyProcessedKeyDown = true;

		if (m_ProcHandler.GetPressingButton())			// if we're already holding mouse button down
		{
			m_bMTSentLastClick = false;
			m_ProcHandler.SetPressingButton(false);
			MouseLUp();
			m_StationaryTicks = m_TicksToWait + 1;		// Don't click here
			SetClickType();
			m_bToggleButtonOn = false;
			m_bDraggingMouseToolWithToggleKey = false;
		}
		else											// if we're not holding mouse button down
		{
			// are we trying to drag the MouseTool window?

			RECT rect;
			CPoint p;
			POINT ptMouse;

			GetCursorPos(&ptMouse);

			// point is in screen coordinates.  Convert those to relative coords.
			GetWindowRect(&rect);
			p.x = ptMouse.x-rect.left;
			p.y = ptMouse.y-rect.top;
			if (p.x<_ButtonRect.left) 
				m_bDraggingMouseToolWithToggleKey = true;

			m_bMTSentLastClick = true;;
			m_ProcHandler.SetPressingButton(true);
			MouseLDown();
			SetClickType();
			m_bToggleButtonOn = true;
		}
	}
	else	// key is up
		bAlreadyProcessedKeyDown = false;
}

void CMouseToolDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
/////////////////////////////////////////////////////////////////////
		#if defined(READMOUSE)
			fclose(infile);
		#endif
/////////////////////////////////////////////////////////////////////
	ShutDown();
}

void CMouseToolDlg::OnWmHotkey(UINT wParam, LONG lParam)
{
	int nID = (int) wParam;

	switch (nID)
	{
		case ID_BTN_DBL_KEY :
			if (m_ProcHandler.GetClickType()==DOUBLEMODE)
				m_ProcHandler.SetClickType(LEFTMODE);		// if already double mode, reset
			else
				m_ProcHandler.SetClickType(DOUBLEMODE);
			break;
		case ID_BTN_RIGHT_KEY:
			if (m_ProcHandler.GetClickType()==RIGHTMODE)
				m_ProcHandler.SetClickType(LEFTMODE);		// if already double mode, reset
			else
				m_ProcHandler.SetClickType(RIGHTMODE);
			break;
		case ID_BTN_STOP:
			OnButton1();
			break;
		case ID_BTN_RIGHT:
//			MouseRDownUp();
			m_nRightClickInNTicks = 2;
			break;
		case ID_BTN_DBL:
			MouseDblClick();
			break;
		case ID_BTN_TOGGLE:
			m_bToggleKeyWasPressed = true;
			break;
	}

//	MouseLDownUp();
}



/*
void CMouseToolDlg::CheckKeys()
{
	static bool bAlreadyProcessedKeyDown = false;

	if (!m_pshtOptions->m_pgKeys.m_bEnableHotkeys)			// if hotkeys are disabled, return
		return;

	// is toggle key pressed?
	bool bKeyState;
	int nKey = (m_pshtOptions->m_pgKeys).m_khBtnToggleLeft.GetVKey();
	bKeyState = (GetAsyncKeyState(nKey) & 0x8000);

//////////////////////////////////////////////////
	// for testing
//	CString str;

//	str.Format("unstick: <%d>", (int) bKeyState);
//	m_Edit1Control.SetWindowText(str);
/////////////////////////////////////////////////

	if ( (m_pshtOptions->m_pgKeys).m_khBtnToggleLeft.IsPressed() )
	{
		if (bAlreadyProcessedKeyDown)						// Only change the state the first time through
			return;
		bAlreadyProcessedKeyDown = true;

		if (m_ProcHandler.GetPressingButton())			// if we're already holding mouse button down
		{
			m_bMTSentLastClick = false;
			m_ProcHandler.SetPressingButton(false);
			MouseLUp();
			m_StationaryTicks = m_TicksToWait + 1;		// Don't click here
			SetClickType();
			m_bToggleButtonOn = false;
			m_bDraggingMouseToolWithToggleKey = false;
		}
		else											// if we're not holding mouse button down
		{
			// are we trying to drag the MouseTool window?

			RECT rect;
			CPoint p;
			POINT ptMouse;

			GetCursorPos(&ptMouse);

			// point is in screen coordinates.  Convert those to relative coords.
			GetWindowRect(&rect);
			p.x = ptMouse.x-rect.left;
			p.y = ptMouse.y-rect.top;
			if (p.x<_ButtonRect.left) 
				m_bDraggingMouseToolWithToggleKey = true;

			m_bMTSentLastClick = true;;
			m_ProcHandler.SetPressingButton(true);
			MouseLDown();
			SetClickType();
			m_bToggleButtonOn = true;
		}
	}
	else	// key is up
		bAlreadyProcessedKeyDown = false;
}
*/
