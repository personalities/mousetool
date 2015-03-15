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

#define THROTTLE_MIN_STEP 3
#define SHORT_TIMER_ID 1
#define LONG_TIMER_ID 2
#define DOUBLE_CLICK_TIMER_ID 3
#define SLOW_CLICK_TIMER_ID 4
#define SPLASH_TIMER_ID 5
#define MAX_ENCRYPTED_LEN 200

#define ID_BTN_DBL_KEY		1
#define ID_BTN_RIGHT_KEY	2
#define ID_BTN_STOP			3
#define ID_BTN_RIGHT		4
#define ID_BTN_DBL			5
#define ID_BTN_TOGGLE		6
#define ID_BTN_LEFT			7

#define LEFTMODE	0
#define DOUBLEMODE	1
#define DRAGMODE	2
#define RIGHTMODE	3
#define HELPMODE	4
#define SHOWDRAGICONMODE 5
#define DISABLEMODE	 6

#define REGISTER_FAIL		 0
#define REGISTER_SUCCESS	 1
#define REGISTER_EXTEND		 2
#define REGISTER_CANCEL		 -1

// These correspond to radio buttons in context options page
#define CONTEXT_DEFAULT 0
#define CONTEXT_DISABLE_SMART_DRAG 1
#define CONTEXT_DOUBLE_CLICK 2
#define CONTEXT_RIGHT_CLICK 3
#define CONTEXT_DISABLE_MOUSETOOL 4
#define CONTEXT_HELPMODE 100

#define HOTKEYS_DBL			1
#define HOTKEYS_RIGHT		2
#define HOTKEYS_STOP		3
#define HOTKEYS_LEFT_BTN	4
#define HOTKEYS_RIGHT_BTN	5
#define HOTKEYS_DBL_BTN		6
#define HOTKEYS_TOGGLE_BTN	7

// for CLocker
#define LOCK_BASE -10000
#define LOCK_SHUTDOWN 		LOCK_BASE+1
#define LOCK_REG_ACCESS_ERR LOCK_BASE+2
#define LOCK_FIRST_TIME 	LOCK_BASE+3
#define LOCK_REGS_CHANGED 	LOCK_BASE+4
#define LOCK_REGISTERED		LOCK_BASE+5
#define LOCK_CLOCK_CHANGED	LOCK_BASE+6
#define LOCK_BETA_EXPIRED	LOCK_BASE+7


// Smart Drag 
#define SD_CLICKDOWN		1
#define SD_NORMAL_TIMER		2
#define SD_SMART_DRAG_TIMER	3

#define UWM_MOUSETOOLTRAY     (WM_USER+1500)

#define VERSION	"3.16" 

#define OPT_GENERAL	0
#define OPT_KEYS	1
#define OPT_CONTEXT	2

#define KEY_UP 0
#define KEY_DOWN 1

#define TIMER_INTERVAL_IN_MS 100
#define SD_TIMER_SCALE 1

//////////////////////////////////////////////////////////////////
// version definitions
// #define EYE_TRACKING 1
#define EYE_TRACKING_CHANGEMODE_BITMAP_WIDTH 44
#define CHANGEMODE_BITMAP_SPACING 3
#define EYE_TRACKING_CHANGEMODE_BITMAP_HEIGHT 38
#define EYE_TRACKING_BUTTON_WIDTH 38

#define ABOUT_STRING "If you find MouseTool useful, please send $20 to a charity of your choice."

#define STARTUP_SETSTARTUP		0
#define STARTUP_CHECKSTARTUP	1
#define STARTUP_REMOVESTARTUP	2


// end trial version definitions
//////////////////////////////////////////////////////////////////

