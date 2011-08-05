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

		/** The Sun scancode for 'Idle' (meaning all keys are up). Also the maximum value for make codes, and
		 *  the mask to get a make code from a break code. */
		#define SUNKBD_KEY		0x7f

		/** The Sun command from the computer to the keyboard indicating LEDs in the following byte */
		#define SUNKBD_LED		0x0e

		/* HID and SUN specs differ in that Caps and Compose LED bits are swapped. Maybe better if coded in asm */
		#define SUNKBD_LED_NUMLOCK	HID_KEYBOARD_LED_NUMLOCK
		#define SUNKBD_LED_COMPOSE	HID_KEYBOARD_LED_CAPSLOCK
		#define SUNKBD_LED_SCROLLLOCK	HID_KEYBOARD_LED_SCROLLLOCK
		#define SUNKBD_LED_CAPSLOCK	HID_KEYBOARD_LED_COMPOSE

		/** Convert HID LED mask to SUN masks. Perhaps it would be tighter if hand coded in asm. */
		static inline uint8_t HID_LED_TO_SUN(uint8_t x) {
				uint8_t r = x & (HID_KEYBOARD_LED_NUMLOCK | HID_KEYBOARD_LED_SCROLLLOCK);
				if(x & HID_KEYBOARD_LED_CAPSLOCK)
					r |= SUNKBD_LED_CAPSLOCK;
				if(x & HID_KEYBOARD_LED_COMPOSE)
					r |= SUNKBD_LED_COMPOSE;
				return r;
		}

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

		extern const uint8_t EEMEM scancodes[];
#endif

