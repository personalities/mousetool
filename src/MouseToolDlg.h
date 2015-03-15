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

// MouseToolDlg.h : header file
//

#include <mmsystem.h>
#include "OptionsSheet.h"
#include "constants.h"
#include "ModeChanger.h"
#include "trayicon.h"
//#include "Splash.h"
#include "clicker.h"

//{{AFX_INCLUDES()
//}}AFX_INCLUDES


// Nonclient minimize and close button positions
//#define NC_BUTTON_TOP		4
//#define NC_BUTTON_BOTTOM	16

//#define NC_MIN_LEFT			208
//#define NC_MIN_RIGHT		NC_MIN_LEFT+15

//#define NC_CLOSE_LEFT		NC_MIN_LEFT+34
//#define NC_CLOSE_RIGHT		NC_MIN_LEFT+49

//#define NC_CONTROL_RIGHT	21

//#define UWM_MOUSETOOLHOOK          (WM_USER+1234)
//extern "C" __declspec(dllimport) BOOL WINAPI setMTHook (HWND hwnd) ;
//extern "C" __declspec(dllimport) BOOL WINAPI unsetMTHook (HWND hwnd) ;



/////////////////////////////////////////////////////////////////////////////
// CMouseToolDlg dialog

class CMouseToolDlg : public CDialog
{
//	CSplash 	m_Splash;
//	UINT 		m_SplashTimerID;
	CClicker	m_Clicker;
	CTrayIcon	TrayIcon;
	int			m_nOldClickType;
	int			m_nRightClickInNTicks;
	int			m_nTicksSinceLastClick;

  bool    m_bFirstTime;
	bool		m_bToggleKeyWasPressed;
	bool		m_bBitmapsAreFlat;
	bool		m_bOverrideNextOnly;
	bool		m_bWaitingForUpclick;
	bool		m_bToggleButtonOn;
	bool		m_bMTSentLastClick;
	bool		m_bDraggingMouseToolWithToggleKey;
	bool		m_bSmartDragIsOn;
	bool		m_bClosing;
	bool		m_bClickedOnModeChanger;
	bool		m_bUserIsClicking;
	bool		m_bSentDownUpLastTick;
	bool		m_bCheckIfMouseDown;

	int			TryToGetCode();
	void		SmartDrag(int);
	void 		UnstickHotkey();

// Construction
public:
	void OnWmHotkey(UINT wParam, LONG lParam);
	void CheckKeys();
	void UnstickToggleKey();
	void LeftHotkeyUp();
	CProcessHandler m_ProcHandler;

	int m_nDwellZoneSize;
	bool m_bReturnToLeftMode;
	char m_TapWaveFile[MAX_PATH];
	bool m_bShowDrag;
	bool bWindowIsLarge;
	RECT m_rectApp;
	RECT xButtonRect, _ButtonRect;		// minimize and close button rects
	HINSTANCE hdllModule;
	int MoveCount;
	int m_LongTimerWait, m_LongTimerElapsed, m_LongTimerOn;
	BOOL m_AudibleTick;
	UINT TimerID, LongTimerID, m_nSmartDragTimerID;
	POINT m_MousePos, m_OldMousePos;
	int m_StationaryTicks, m_DragOnly;
	int m_TicksToWait, m_Milliseconds, m_ClickType, m_SmartDragDelay;
	BOOL m_bMouseToolIsActive;
	BOOL m_DraggingByDelay;
	BOOL m_SetTopmost;
	UINT m_Xmin, m_Xmax, m_Ymin, m_Ymax;
	UINT m_wZmin, m_wZmax;
	CTime m_LongTimerStopTime;

	COptionsSheet *m_pshtOptions;
	bool m_bStopDragging;
	bool m_bNCDragging;				// for handling dragging of MT 
	CPoint m_ptDragStartPointMouse, m_ptDragStartPointApp;

	bool m_bMouseInWindow;
	bool m_bInLStatic, m_bInRStatic, m_bInDStatic;
	CBitmap m_bitLeft, m_bitRight, m_bitDbl, m_bitBigSmall;
	BOOL m_bButtonsReversed;

	// for tray-menu messages
	void OnTrayDouble();	
	void OnTrayLeft();	
	void OnTrayRight();	
	void OnTrayRestore();	
	void OnTrayStartStop();	
	void OnTrayNextOnly();	
	void OnTrayOpenGeneral();
	void OnTrayOpenKeys();
	void OnTrayOpenContext();
	void OnTrayClose();

	LONG OnHook(UINT wParam, LONG lParam);
	LONG OnClickHook(UINT wParam, LONG lParam);
	LONG OnClickUpHook(UINT wParam, LONG lParam);
	LONG OnKeyHook(UINT wParam, LONG lParam);
	LONG OnKeyUpHook(UINT wParam, LONG lParam);

	void EnterHelpMode();
	void CallContextHelp();
	LONG OnTrayMsg(UINT wParam, LONG lParam);
	LONG OnShutdown(UINT wParam, LONG lParam);
	void ShutDown();
	bool SamePoint(POINT pt1, POINT pt2);
	void SetBitmaps();
	void EndDrag();
	void BeginDrag();
	void MouseDblClick();
	void GetMouseReversed();
	void MouseLDownUp();
	void MouseRDownUp();
	void MouseLDown();
	void MouseLUp();
	void MouseRDown();
	void MouseRUp();
	void CheckModeChangers(CPoint);
	void CheckMouseInWindow(const CPoint &);
	void DontClickHere();
	void FlattenAllBitmaps(const bool bFlatten);
	void SetDragBitmap(const int throttle);
	bool PtInStatic(const CPoint &point, const CStatic &stat);
	void SetCaptionRects();
	void DisableControls();
	void EnableControls();
	void PlayTickSound();
	void ncLDown(UINT nHitTest, POINTS point);
	void ncLUp(UINT nHitTest, POINTS point);
	void SlowClick(void);
	void SmartDragTimerEvent(void);
	void ClickMouse();
	CMouseToolDlg(CWnd* pParent = NULL);	// standard constructor
	double EditValue(CEdit& ed);
	void SetTimer(int ms, int ticks);
	void StopTimer(void);
	void RestoreConfig(void);
	void SaveConfig(void);
	void ShowContext(int type);
	void SetClickType();
	void SetLongTimer(int);
	void LongTimerEvent(void);
	void StopLongTimer(void);
	CBitmap m_bmpStopBitmap, m_bmpGoBitmap;
	HBITMAP hStopBitmap, hGoBitmap;

// Dialog Data
	//{{AFX_DATA(CMouseToolDlg)
	enum { IDD = IDD_MOUSETOOL_DIALOG };
	CEdit	m_Edit1Control;
	CButton	m_SmallButton;
	CModeChanger	m_DStaticControl;
	CModeChanger	m_RStaticControl;
	CModeChanger	m_LStaticControl;
	CButton	m_LeftButton;
	CButton	m_HelpButtonControl;
	CProgressCtrl	m_JoyProgress;
	CButton	m_OptionsControl;
	CButton	m_Button1Control;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMouseToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOptionsbutton();
	afx_msg void OnClose();
	afx_msg void OnHelpbutton();
	afx_msg void OnSmallbutton();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
//	afx_msg void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp );
	DECLARE_MESSAGE_MAP()
};
