/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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
 *  Header file for V2ProtocolParams.c.
 */

#ifndef _V2_PROTOCOL_PARAMS_
#define _V2_PROTOCOL_PARAMS_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/eeprom.h>

		#include <LUFA/Version.h>

		#include "V2Protocol.h"
		#include "V2ProtocolConstants.h"

	/* Macros: */
		#define PARAM_PRIV_READ   (1 << 0)
		#define PARAM_PRIV_WRITE  (1 << 1)

	/* Type Defines: */
		typedef struct
		{
			const uint8_t ParamID;
			uint8_t ParamValue;
			uint8_t ParamPrivellages;
		} ParameterItem_t;

	/* Function Prototypes: */
		void    V2Params_LoadEEPROMParamValues(void);
	
		uint8_t V2Params_GetParameterPrivellages(uint8_t ParamID);
		uint8_t V2Params_GetParameterValue(uint8_t ParamID);
		void    V2Params_SetParameterValue(uint8_t ParamID, uint8_t Value);
		
		#if defined(INCLUDE_FROM_V2PROTOCOL_PARAMS_C)
			static ParameterItem_t* V2Params_GetParamFromTable(uint8_t ParamID);
		#endif

#endif
