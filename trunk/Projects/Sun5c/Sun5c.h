/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Keyboard.c.
 */

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/eeprom.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>
		#include <string.h>

		#include "Descriptors.h"

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/Peripheral/Serial.h>

	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY        LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING     (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY           (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR           (LEDS_LED1 | LEDS_LED3)

		/** The maximum number of simultaneous keys. According to the Sun Keyboard spec, the Type5c implements
		 *  full N-key Rollover (i.e., all key depressions and releases correctly detected in any sequence
		 *  regardless of how many keys are being depressed). For now, we will keep this at 6 to be compatible
		 *  witht the Boot protocol (and the existing code), but in the future, this will increase to 10.  */
		#define MAX_KEYS		6

		/** The Sun scancode for 'Idle' (meaning all keys are up). Also the maximum value for make events */
		#define SUNKBD_KEY		0x7f

	/* Function Prototypes: */
		void SetupHardware(void);
		void HID_Task(void);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);
		void EVENT_USB_Device_StartOfFrame(void);

		void CreateKeyboardReport(USB_KeyboardReport_Data_t* const ReportData);
		void ProcessLEDReport(const uint8_t LEDReport);
		void SendNextReport(void);
		void ReceiveNextReport(void);

		const uint8_t EEMEM scancodes[128] = {
			0,
			HID_KEYBOARD_SC_STOP,                                   // 0x01
			HID_KEYBOARD_SC_VOLUME_DOWN,
			HID_KEYBOARD_SC_AGAIN,
			HID_KEYBOARD_SC_VOLUME_UP,
			HID_KEYBOARD_SC_F1,
			HID_KEYBOARD_SC_F2,
			HID_KEYBOARD_SC_F10,
			HID_KEYBOARD_SC_F3,                                     // 0x08
			HID_KEYBOARD_SC_F11,
			HID_KEYBOARD_SC_F4,
			HID_KEYBOARD_SC_F12,
			HID_KEYBOARD_SC_F5,
			HID_KEYBOARD_SC_RIGHT_ALT,
			HID_KEYBOARD_SC_F6,
			0xf9, // "Macro" has no similar HID code. 0xf9 is Linux's coffee key.
			HID_KEYBOARD_SC_F7,                                     // 0x10
			HID_KEYBOARD_SC_F8,
			HID_KEYBOARD_SC_F9,
			HID_KEYBOARD_SC_LEFT_ALT,
			HID_KEYBOARD_SC_UP_ARROW,
			HID_KEYBOARD_SC_PAUSE,
			HID_KEYBOARD_SC_PRINT_SCREEN,
			HID_KEYBOARD_SC_SCROLL_LOCK,
			HID_KEYBOARD_SC_LEFT_ARROW,                             // 0x18
			HID_KEYBOARD_SC_MANU,
			HID_KEYBOARD_SC_UNDO,
			HID_KEYBOARD_SC_DOWN_ARROW,
			HID_KEYBOARD_SC_RIGHT_ARROW,
			HID_KEYBOARD_SC_ESCAPE,
			HID_KEYBOARD_SC_1_AND_EXCLAMATION,
			HID_KEYBOARD_SC_2_AND_AT,
			HID_KEYBOARD_SC_3_AND_HASHMARK,                         // 0x20
			HID_KEYBOARD_SC_4_AND_DOLLAR,
			HID_KEYBOARD_SC_5_AND_PERCENTAGE,
			HID_KEYBOARD_SC_6_AND_CARET,
			HID_KEYBOARD_SC_7_AND_AND_AMPERSAND,
			HID_KEYBOARD_SC_8_AND_ASTERISK,
			HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS,
			HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS,
			HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE,                   // 0x28
			HID_KEYBOARD_SC_EQUAL_AND_PLUS,
			HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE,
			HID_KEYBOARD_SC_BACKSPACE,
			HID_KEYBOARD_SC_INSERT,
			HID_KEYBOARD_SC_MUTE,
			HID_KEYBOARD_SC_KEYPAD_SLASH,
			HID_KEYBOARD_SC_KEYPAD_ASTERISK,
			HID_KEYBOARD_SC_POWER,                                  // 0x30
			HID_KEYBOARD_SC_SELECT,
			HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE,
			HID_KEYBOARD_SC_COPY,
			HID_KEYBOARD_SC_HOME,
			HID_KEYBOARD_SC_TAB,
			HID_KEYBOARD_SC_Q,
			HID_KEYBOARD_SC_W,
			HID_KEYBOARD_SC_E,                                      // 0x38
			HID_KEYBOARD_SC_R,
			HID_KEYBOARD_SC_T,
			HID_KEYBOARD_SC_Y,
			HID_KEYBOARD_SC_U,
			HID_KEYBOARD_SC_I,
			HID_KEYBOARD_SC_O,
			HID_KEYBOARD_SC_P,
			HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE,      // 0x40
			HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE,
			HID_KEYBOARD_SC_DELETE,
			0x65, // "Compose"
			HID_KEYBOARD_SC_KEYPAD_7_AND_HOME,
			HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW,
			HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP,
			HID_KEYBOARD_SC_KEYPAD_MINUS,
			HID_KEYBOARD_SC_EXECUTE,                                // 0x48
			HID_KEYBOARD_SC_PASTE,
			HID_KEYBOARD_SC_END,
			0,
			HID_KEYBOARD_SC_LEFT_CONTROL,
			HID_KEYBOARD_SC_A,
			HID_KEYBOARD_SC_S,
			HID_KEYBOARD_SC_D,
			HID_KEYBOARD_SC_F,                                      // 0x50
			HID_KEYBOARD_SC_G,
			HID_KEYBOARD_SC_H,
			HID_KEYBOARD_SC_J,
			HID_KEYBOARD_SC_K,
			HID_KEYBOARD_SC_L,
			HID_KEYBOARD_SC_SEMICOLON_AND_COLON,
			HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE,
			HID_KEYBOARD_SC_BACKSLASH_AND_PIPE,                     // 0x58
			HID_KEYBOARD_SC_ENTER,
			HID_KEYBOARD_SC_KEYPAD_ENTER,
			HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW,
			HID_KEYBOARD_SC_KEYPAD_5,
			HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW,
			HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT,
			HID_KEYBOARD_SC_FIND,
			HID_KEYBOARD_SC_PAGE_UP,                                // 0x60
			HID_KEYBOARD_SC_CUT,
			HID_KEYBOARD_SC_NUM_LOCK,
			HID_KEYBOARD_SC_LEFT_SHIFT,
			HID_KEYBOARD_SC_Z,
			HID_KEYBOARD_SC_X,
			HID_KEYBOARD_SC_C,
			HID_KEYBOARD_SC_V,
			HID_KEYBOARD_SC_B,                                      // 0x68
			HID_KEYBOARD_SC_N,
			HID_KEYBOARD_SC_M,
			HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN,
			HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN,
			HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK,
			HID_KEYBOARD_SC_RIGHT_SHIFT,
			0, // "Linefeed" scancode is 0x6f, yet does not correspond to a key
			HID_KEYBOARD_SC_KEYPAD_1_AND_END,                       // 0x70
			HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW,
			HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN,
			0,
			0,
			0,
			HID_KEYBOARD_SC_HELP,
			HID_KEYBOARD_SC_CAPS_LOCK,
			HID_KEYBOARD_SC_LEFT_GUI,                               //0x78
			HID_KEYBOARD_SC_SPACE,
			HID_KEYBOARD_SC_RIGHT_GUI,
			HID_KEYBOARD_SC_PAGE_DOWN,
			0,
			HID_KEYBOARD_SC_KEYPAD_PLUS
		};
#endif

