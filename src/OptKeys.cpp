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

// OptKeys.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "OptKeys.h"
#include "constants.h"
#include "DlgWarnLeftHotkey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptKeys property page

IMPLEMENT_DYNCREATE(COptKeys, CPropertyPage)

COptKeys::COptKeys() : CPropertyPage(COptKeys::IDD)
{
	m_bGettingHotkey = false;
	m_bWarnLeftHotkey = true;
	//{{AFX_DATA_INIT(COptKeys)
	m_bEnableHotkeys = FALSE;
	//}}AFX_DATA_INIT
}

COptKeys::~COptKeys()
{
}

void COptKeys::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptKeys)
	DDX_Control(pDX, IDC_STAT_TOGGLE_LEFT, m_statToggleLeft);
	DDX_Control(pDX, IDC_EDT_TOGGLE_BTN, m_edtToggleLeft);
	DDX_Control(pDX, IDC_BUTTON_TOGGLE, m_btnToggleLeft);
	DDX_Control(pDX, IDC_STAT_FRAME_BUTTONS, m_statFrameBtns);
	DDX_Control(pDX, IDC_STAT_RIGHT_BUTTON, m_statRightBtn);
	DDX_Control(pDX, IDC_STAT_LEFT_BUTTON, m_statLeftBtn);
	DDX_Control(pDX, IDC_STAT_DOUBLE_BUTTON, m_statDblBtn);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_btnLeftBtn);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_btnRightBtn);
	DDX_Control(pDX, IDC_BUTTON_DOUBLE, m_btnDblBtn);
	DDX_Control(pDX, IDC_EDT_LEFT_BUTTON, m_edtBtnLeft);
	DDX_Control(pDX, IDC_EDT_RIGHT_BUTTON, m_edtBtnRight);
	DDX_Control(pDX, IDC_EDT_DBL_BUTTON, m_edtBtnDouble);
	DDX_Control(pDX, IDC_BUTTON_STOP_KEY, m_btnStopKey);
	DDX_Control(pDX, IDC_EDT_STOP_KEY, m_edtStopKey);
	DDX_Control(pDX, IDC_STAT_STOP_KEY, m_statStopKey);
	DDX_Control(pDX, IDC_STAT_RIGHT_KEY, m_statRightKey);
	DDX_Control(pDX, IDC_STAT_DBL_KEY, m_statDblKey);
	DDX_Control(pDX, IDC_BUTTON_RIGHT_KEY, m_btnRightKey);
	DDX_Control(pDX, IDC_STAT_HOTKEY, m_statHotkeys);
	DDX_Control(pDX, IDC_BUTTON_DBL_KEY, m_btnDblKey);
	DDX_Control(pDX, IDC_EDT_RIGHT_KEY, m_edtRightKey);
	DDX_Control(pDX, IDC_EDT_DBL_KEY, m_edtDblKey);
	DDX_Check(pDX, IDC_CK_ENABLE_HOTKEYS, m_bEnableHotkeys);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptKeys, CPropertyPage)
	//{{AFX_MSG_MAP(COptKeys)
	ON_BN_CLICKED(IDC_BUTTON_DBL_KEY, OnButtonDblKey)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT_KEY, OnButtonRightKey)
	ON_BN_CLICKED(IDC_CK_ENABLE_HOTKEYS, OnCkEnableHotkeys)
	ON_BN_CLICKED(IDC_BUTTON_STOP_KEY, OnButtonStopKey)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DOUBLE, OnButtonDouble)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE, OnButtonToggle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptKeys message handlers
// nKeyDown is 0 if this is a key_up event, 1 if key_down
// (only set new hotkey if it's a key_down)
int COptKeys::OnKeyHook(int nKeyDown, UINT wParam, LONG lParam)
{
	if (m_bGettingHotkey==true && nKeyDown)				// we're getting a new key
		m_dlgGetHotkey.OnKeyHook(wParam, lParam);
	else {
		CKeyHandler kh(wParam);
		if (m_khDblKey.equals(kh))
			return HOTKEYS_DBL;
		if (m_khRightKey.equals(kh))
			return HOTKEYS_RIGHT;
		if (m_khStopKey.equals(kh))
			return HOTKEYS_STOP;

		if (m_khBtnLeft.equals(kh))
			return HOTKEYS_LEFT_BTN;
		if (m_khBtnRight.equals(kh))
			return HOTKEYS_RIGHT_BTN;
		if (m_khBtnToggleLeft.equals(kh))
			return HOTKEYS_TOGGLE_BTN;
		if (m_khBtnDouble.equals(kh))
			return HOTKEYS_DBL_BTN;
	}
	return 0;
}

BOOL COptKeys::OnSetActive() 
{
	// Make backups
	m_khDblBackup		= m_khDblKey;
	m_khRightBackup		= m_khRightKey;
	m_khStopBackup		= m_khStopKey;

	m_khBtnLeftBack		= m_khBtnLeft;
	m_khBtnRightBack	= m_khBtnRight;
	m_khBtnDoubleBack	= m_khBtnDouble;
	m_khBtnToggleBack	= m_khBtnToggleLeft;

	m_bEnableHotkeysBackup = !!m_bEnableHotkeys;


	m_edtDblKey.SetWindowText(m_khDblKey.GetWParamString());
	m_edtRightKey.SetWindowText(m_khRightKey.GetWParamString());
	m_edtStopKey.SetWindowText(m_khStopKey.GetWParamString());

	m_edtBtnLeft.SetWindowText(m_khBtnLeft.GetWParamString());
	m_edtBtnRight.SetWindowText(m_khBtnRight.GetWParamString());
	m_edtToggleLeft.SetWindowText(m_khBtnToggleLeft.GetWParamString());
	m_edtBtnDouble.SetWindowText(m_khBtnDouble.GetWParamString());

	OnCkEnableHotkeys();	
	return CPropertyPage::OnSetActive();
}


void COptKeys::OnCkEnableHotkeys() 
{
	UpdateData(TRUE);
//	m_pProcHandler->SetEnableHotkeys(m_bEnableHotkeys==TRUE);
	
	m_btnDblKey.EnableWindow(m_bEnableHotkeys);
	m_btnRightKey.EnableWindow(m_bEnableHotkeys);				
	m_btnStopKey.EnableWindow(m_bEnableHotkeys);
				
	m_edtDblKey.EnableWindow(m_bEnableHotkeys);				
	m_edtRightKey.EnableWindow(m_bEnableHotkeys);				
	m_edtStopKey.EnableWindow(m_bEnableHotkeys);
				
	m_statDblKey.EnableWindow(m_bEnableHotkeys);	
	m_statRightKey.EnableWindow(m_bEnableHotkeys);				
	m_statStopKey.EnableWindow(m_bEnableHotkeys);
				
	m_statHotkeys.EnableWindow(m_bEnableHotkeys);				

	m_edtBtnLeft.EnableWindow(m_bEnableHotkeys);
	m_edtBtnRight.EnableWindow(m_bEnableHotkeys);
	m_edtToggleLeft.EnableWindow(m_bEnableHotkeys);
	m_edtBtnDouble.EnableWindow(m_bEnableHotkeys);

	m_btnLeftBtn.EnableWindow(m_bEnableHotkeys);
	m_btnRightBtn.EnableWindow(m_bEnableHotkeys);
	m_btnToggleLeft.EnableWindow(m_bEnableHotkeys);
	m_btnDblBtn.EnableWindow(m_bEnableHotkeys);

	m_statLeftBtn.EnableWindow(m_bEnableHotkeys);
	m_statRightBtn.EnableWindow(m_bEnableHotkeys);
	m_statToggleLeft.EnableWindow(m_bEnableHotkeys);
	m_statDblBtn.EnableWindow(m_bEnableHotkeys);

	m_statFrameBtns.EnableWindow(m_bEnableHotkeys);
}



void COptKeys::OnCancel() 
{
	m_bEnableHotkeys = m_bEnableHotkeysBackup;

	m_khDblKey   = m_khDblBackup;
	m_khRightKey = m_khRightBackup;
	m_khStopKey  = m_khStopBackup;

	m_khBtnLeft			= m_khBtnLeftBack;
	m_khBtnRight		= m_khBtnRightBack;
	m_khBtnDouble		= m_khBtnDoubleBack;
	m_khBtnToggleLeft	= m_khBtnToggleBack;

	CPropertyPage::OnCancel();
}

BOOL COptKeys::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	::WinHelp(m_hWnd, "MouseTool.hlp", HELP_CONTEXTPOPUP, pHelpInfo->dwContextId);
	
	return TRUE;
}

// Get a new hotkey and update the hotkey's edit window
void COptKeys::ChangeHotkey(CKeyHandler *pKey, CEdit *pEdit, int nHotkeyID)
{
	m_bGettingHotkey = true;
	m_dlgGetHotkey.m_khHotkey = *pKey;
	if (m_dlgGetHotkey.DoModal()==IDOK)
	{
		*pKey = m_dlgGetHotkey.m_khHotkey;
		pEdit->SetWindowText(pKey->GetWParamString());
		UnregisterHotKey(m_hwndMouseToolWnd, nHotkeyID);
	}
	m_bGettingHotkey = false;
}

void COptKeys::OnButtonDblKey() 
{
	ChangeHotkey(&m_khDblKey, &m_edtDblKey, ID_BTN_DBL_KEY);
}

void COptKeys::OnButtonRightKey() 
{
	ChangeHotkey(&m_khRightKey, &m_edtRightKey, ID_BTN_RIGHT_KEY);
}

void COptKeys::OnButtonStopKey() 
{
	ChangeHotkey(&m_khStopKey, &m_edtStopKey, ID_BTN_STOP);
}

void COptKeys::OnButtonLeft() 
{
	CDlgWarnLeftHotkey dlg;
	if (m_bWarnLeftHotkey)
	{
		dlg.DoModal();
		m_bWarnLeftHotkey = !dlg.m_bDontShowAgain;
	}

	ChangeHotkey(&m_khBtnLeft, &m_edtBtnLeft, 0);
}

void COptKeys::OnButtonRight() 
{
	ChangeHotkey(&m_khBtnRight, &m_edtBtnRight, ID_BTN_RIGHT);
}

void COptKeys::OnButtonDouble() 
{
	ChangeHotkey(&m_khBtnDouble, &m_edtBtnDouble, ID_BTN_DBL);
}

void COptKeys::OnButtonToggle() 
{
	ChangeHotkey(&m_khBtnToggleLeft, &m_edtToggleLeft, ID_BTN_TOGGLE);
}

void COptKeys::SetMainWnd(HWND hWnd)
{
	m_hwndMouseToolWnd = hWnd;
}

void COptKeys::RegisterHotkey(CKeyHandler *pKey, int nHotkeyID)
{
	if (nHotkeyID)
	{
		// Need to unregister earlier hotkey
		UINT fsModifiers = 0;
		if (pKey->m_bAlt)
			fsModifiers |= MOD_ALT;
		if (pKey->m_bCtrl)
			fsModifiers |= MOD_CONTROL;
		if (pKey->m_bShift)
			fsModifiers |= MOD_SHIFT;
//		if (pKey->m_bAlt)
//			fsModifiers |= MOD_WIN;
		RegisterHotKey(m_hwndMouseToolWnd, nHotkeyID, fsModifiers, pKey->m_vkey);
	}
}


void COptKeys::RegisterAllHotkeys()
{
	if (m_bEnableHotkeys)
	{
		RegisterHotkey(&m_khDblKey, ID_BTN_DBL_KEY);
		RegisterHotkey(&m_khRightKey, ID_BTN_RIGHT_KEY);
		RegisterHotkey(&m_khStopKey, ID_BTN_STOP);
		RegisterHotkey(&m_khBtnRight, ID_BTN_RIGHT);
		RegisterHotkey(&m_khBtnDouble, ID_BTN_DBL);
		RegisterHotkey(&m_khBtnToggleLeft, ID_BTN_TOGGLE);
	}
}


// be a good boy and clean up after yourself...
// (called by mt window when closing)
void COptKeys::UnRegisterAllHotkeys()
{
	UnregisterHotKey(m_hwndMouseToolWnd, ID_BTN_DBL_KEY);
	UnregisterHotKey(m_hwndMouseToolWnd, ID_BTN_RIGHT_KEY);
	UnregisterHotKey(m_hwndMouseToolWnd, ID_BTN_STOP);
	UnregisterHotKey(m_hwndMouseToolWnd, ID_BTN_RIGHT);
	UnregisterHotKey(m_hwndMouseToolWnd, ID_BTN_DBL);
	UnregisterHotKey(m_hwndMouseToolWnd, ID_BTN_TOGGLE);
}
