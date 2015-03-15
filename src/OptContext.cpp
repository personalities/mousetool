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

// OptContext.cpp : implementation file
//

#include "stdafx.h"
#include "MouseTool.h"
#include "OptContext.h"
#include "DlgAlertContexts.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptContext property page

IMPLEMENT_DYNCREATE(COptContext, CPropertyPage)

COptContext::COptContext() : CPropertyPage(COptContext::IDD)
{
	m_bBackupContext = true;

	//{{AFX_DATA_INIT(COptContext)
	m_nRadio = -1;
	m_bEnableContext = FALSE;
	m_bDisableSmartDragInScrollbars = FALSE;
	//}}AFX_DATA_INIT
}

COptContext::~COptContext()
{
}

void COptContext::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptContext)
	DDX_Control(pDX, IDC_CHECK1, m_ckDisableSmartDragInScrollbars);
	DDX_Control(pDX, IDC_STAT_ACTION, m_statAction);
	DDX_Control(pDX, IDC_STAT_WND_TYPES, m_statWndTypes);
	DDX_Control(pDX, IDC_BUTTON_DELETE_CONTEXT, m_btDeleteContext);
	DDX_Control(pDX, IDC_BUTTON_ADD_CONTEXT, m_btAddContext);
	DDX_Control(pDX, IDC_STATIC_PREV_WINDOW, m_statPrevWindow);
	DDX_Control(pDX, IDC_EDT_LAST_CONTEXT, m_edtPrevContext);
	DDX_Control(pDX, IDC_LST_APPS, m_lstApps);
	DDX_Control(pDX, IDC_CK_ENABLE_CONTEXT, m_ckEnableContext);
	DDX_Control(pDX, IDC_RADIO1, m_Radio1);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadio);
	DDX_Check(pDX, IDC_CK_ENABLE_CONTEXT, m_bEnableContext);
	DDX_Check(pDX, IDC_CHECK1, m_bDisableSmartDragInScrollbars);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptContext, CPropertyPage)
	//{{AFX_MSG_MAP(COptContext)
	ON_BN_CLICKED(IDC_CK_ENABLE_CONTEXT, OnCkEnableContext)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_LBN_SELCHANGE(IDC_LST_APPS, OnSelchangeLstApps)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CONTEXT, OnButtonAddContext)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_CONTEXT, OnButtonDeleteContext)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptContext message handlers


// If you call this and DON'T want context backed up,
// set m_bBackupContext=false first (and restore it after)
BOOL COptContext::OnSetActive() 
{
	m_bPopulatingDlg = true;

	// Before we do anything else, let's save current contexts
	if (m_bBackupContext)		// don't do if called by dlg
		m_pProcHandler->MakeBackupContextMap();
	
	m_edtPrevContext.SetWindowText(m_pProcHandler->m_PrevClassUnderMouse);

	m_pProcHandler->AddClassesToListBox(m_lstApps);

	if (m_pProcHandler->m_bEnableContext && m_pProcHandler->m_bOverrideNextOnly)
		m_ckEnableContext.SetCheck(1);
	else
		m_ckEnableContext.SetCheck(0);

	m_ckEnableContext.SetCheck(m_pProcHandler->m_bEnableContext);
	m_bEnableContextsBackup = m_pProcHandler->m_bEnableContext;

	OnCkEnableContext();	

	if (m_pProcHandler->GetNumContexts())
	{
		m_lstApps.SetCurSel(0);
		OnSelchangeLstApps();
		UpdateData(FALSE);
	}

	m_bPopulatingDlg = false;
	return CPropertyPage::OnSetActive();
}


void COptContext::EnableRadios(BOOL val)
{
	HWND hButton;

	if (val) {
		GetDlgItem(IDC_RADIO1, &hButton);
		::Button_Enable(hButton, TRUE);

		GetDlgItem(IDC_RADIO2, &hButton);
		::Button_Enable(hButton, TRUE);

		GetDlgItem(IDC_RADIO3, &hButton);
		::Button_Enable(hButton, TRUE);

		GetDlgItem(IDC_RADIO4, &hButton);
		::Button_Enable(hButton, TRUE);

		GetDlgItem(IDC_RADIO5, &hButton);
		::Button_Enable(hButton, TRUE);
} else {
		GetDlgItem(IDC_RADIO1, &hButton);
		::Button_Enable(hButton, FALSE);

		GetDlgItem(IDC_RADIO2, &hButton);
		::Button_Enable(hButton, FALSE);

		GetDlgItem(IDC_RADIO3, &hButton);
		::Button_Enable(hButton, FALSE);

		GetDlgItem(IDC_RADIO4, &hButton);
		::Button_Enable(hButton, FALSE);

		GetDlgItem(IDC_RADIO5, &hButton);
		::Button_Enable(hButton, FALSE);
	}
}

// Enable or disable controls based on "Enable Context" check box
void COptContext::OnCkEnableContext() 
{
	BOOL bNewState = m_ckEnableContext.GetCheck();

	//if (!m_bPopulatingDlg)
		if (!m_pProcHandler->m_bOverrideNextOnly)
		{
			m_pProcHandler->OnClickHook(KEY_UP, 0,0);
			CDlgAlertContexts dlg;
			dlg.m_pProcHandler = m_pProcHandler;
			dlg.DoModal();
			m_pProcHandler->SetEnableContext(FALSE);
			m_ckEnableContext.SetCheck(0);
			m_bEnableContext = FALSE;
			m_lstApps.EnableWindow(FALSE);				// list box
		//	m_Radio1.EnableWindow(FALSE);
			EnableRadios(FALSE);						// Radio buttons
			m_statPrevWindow.EnableWindow(FALSE);		// "Prev win type" static
			m_statAction.EnableWindow(FALSE);		// "Prev win type" static
			m_statWndTypes.EnableWindow(FALSE);		// "Prev win type" static
			m_btAddContext.EnableWindow(FALSE);			// Add context button
			m_btDeleteContext.EnableWindow(FALSE);		// Del context button
			m_edtPrevContext.EnableWindow(FALSE);		// prev context edit box
//			UpdateData(FALSE);
			return;
		}

	m_pProcHandler->SetEnableContext(bNewState==TRUE);
	m_pProcHandler->SetClickType(LEFTMODE);
	
	m_lstApps.EnableWindow(bNewState);				// list box
//	m_Radio1.EnableWindow(bNewState);
	EnableRadios(bNewState);						// Radio buttons
	m_statPrevWindow.EnableWindow(bNewState);		// "Prev win type" static
	m_statAction.EnableWindow(bNewState);		// "Prev win type" static
	m_statWndTypes.EnableWindow(bNewState);		// "Prev win type" static
	m_btAddContext.EnableWindow(bNewState);			// Add context button
	m_btDeleteContext.EnableWindow(bNewState);		// Del context button
	m_edtPrevContext.EnableWindow(bNewState);		// prev context edit box
}

CString COptContext::GetSelectedApp()
{
	CString str;
	m_lstApps.GetText(m_lstApps.GetCurSel(), str);		// get selected text
	int nIndex = str.Find(" --");
	str = str.Left(nIndex);
//	str = str.SpanExcluding(m_pProcHandler->strSeparator);
//	MessageBox(str);
	return str;
}

void COptContext::UpdateContext() {
	CClickInfo ci;
	CString app=GetSelectedApp();

	bool isValid=m_pProcHandler->GetClassClickInfo(app,ci);
	MTASSERT(isValid);
	if(isValid) {
		ci.bDontDragInScrollbars=!!m_bDisableSmartDragInScrollbars;
		ci.nContext=m_nRadio;
		m_pProcHandler->SetClassClickInfo(app,ci);
	}
}
//{
//	UpdateData(TRUE);
//	m_pProcHandler->SetAppContext(GetSelectedApp(), m_nRadio);
//	m_pProcHandler->SetClassContext(GetSelectedApp(), m_nRadio);
//
//	CString str;
//	str.Format("Class: %s.  Radio: %d", GetSelectedApp(), m_nRadio);
//	MessageBox(str);
//}

void COptContext::OnRadio1() 
{
	m_nRadio = 0;
	UpdateContext();
}

void COptContext::OnRadio2() 
{
	m_nRadio = 1;
	UpdateContext();
}

void COptContext::OnRadio3() 
{
	m_nRadio = 2;
	UpdateContext();
}

void COptContext::OnRadio4() 
{
	m_nRadio = 3;
	UpdateContext();
}

void COptContext::OnSelchangeLstApps() 
{
//	m_nRadio = m_pProcHandler->GetClassContext(GetSelectedApp());
	CClickInfo ci;
	bool foundClass=m_pProcHandler->GetClassClickInfo(GetSelectedApp(),ci);
	MTASSERT(foundClass);
	m_nRadio=ci.nContext;
	m_bDisableSmartDragInScrollbars=ci.bDontDragInScrollbars;
	UpdateData(FALSE);
}

void COptContext::SetClassAtMouse()
{
	m_pProcHandler->SetClassAtMouse();
	if (m_edtPrevContext.m_hWnd)
		m_edtPrevContext.SetWindowText(m_pProcHandler->m_PrevClassUnderMouse);
}

void COptContext::OnButtonAddContext() 
{
	m_pProcHandler->SetClassContext(m_pProcHandler->m_PrevClassUnderMouse, CONTEXT_DEFAULT);
	m_pProcHandler->AddClassesToListBox(m_lstApps);
	m_lstApps.SetCurSel(0);
	OnSelchangeLstApps();
}

void COptContext::OnOK() 
{
	m_pProcHandler->SaveContexts(1);
	CPropertyPage::OnOK();
}

void COptContext::OnButtonDeleteContext() 
{
	if (m_pProcHandler->GetNumContexts()>0)
	{
		m_pProcHandler->DeleteClassContext(GetSelectedApp());
		m_bBackupContext = false;
		OnSetActive();
		m_bBackupContext = true;
	}
}

void COptContext::OnCancel() 
{
	// Restore contexts from backup list
	m_pProcHandler->RestoreContextsFromBackup();
	
//	BOOL bNewState = m_ckEnableContext.GetCheck();
//	m_pProcHandler->SetEnableContext(bNewState==TRUE);
	m_pProcHandler->SetEnableContext(m_bEnableContextsBackup);

	CPropertyPage::OnCancel();
}

void COptContext::OnRadio5() 
{
	m_nRadio = 4;
	UpdateContext();
}

BOOL COptContext::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	::WinHelp(m_hWnd, "MouseTool.hlp", HELP_CONTEXTPOPUP, pHelpInfo->dwContextId);
	
	return TRUE;
}

void COptContext::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_bDisableSmartDragInScrollbars=
		m_ckDisableSmartDragInScrollbars.GetCheck()==BST_CHECKED;
	uti::dprintf("COptContext::OnCheck1: m_bDisableSmartDragInScrollbars=%d\n",
		m_bDisableSmartDragInScrollbars);
	UpdateContext();
}
