/*
             MyUSB Library
     Copyright (C) Dean Camera, 2008.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com

 Released under the LGPL Licence, Version 3
*/

#ifndef _CONFIGDESCRIPTOR_H_
#define _CONFIGDESCRIPTOR_H_

	/* Includes: */
		#include <MyUSB/Drivers/USB/USB.h>                        // USB Functionality
		#include <MyUSB/Drivers/USB/Class/ConfigDescriptor.h>     // Configuration Descriptor Parser
		
		#include "MouseHost.h"
		
	/* Macros: */
		#define MOUSE_CLASS                 0x03
		#define MOUSE_PROTOCOL              0x02

		#define MAX_CONFIG_DESCRIPTOR_SIZE     512
	
	/* Enums: */
		enum GetConfigDescriptorDataCodes_t
		{
			ControlError         = 0,
			DescriptorTooLarge   = 1,
			NoHIDInterfaceFound  = 2,
			NoEndpointFound      = 3,
			SuccessfulConfigRead = 4,
		};	

	/* Configuration Descriptor Comparison Functions: */
		DESCRIPTOR_COMPARATOR(NextMouseInterface);
		DESCRIPTOR_COMPARATOR(NextInterfaceMouseDataEndpoint);

	/* Function Prototypes: */
		uint8_t ProcessConfigurationDescriptor(void);	

#endif
