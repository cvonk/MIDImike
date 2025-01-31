/*
     dualMocoLUFA Project
     Copyright (C) 2013 by morecat_lab

     2013/09/22
              
     http://morecatlab.akiba.coocan.jp/

     based on LUFA-100807
*/
/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for Descriptors.c.
 */
 
#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/CDC.h>
		#include <LUFA/Drivers/USB/Class/MIDI.h>
		
	/* Product-specific definitions: */
		#define ARDUINO_UNO_PID			0x0043
		#define ARDUINO_MEGA2560_PID		0x0010

	/* Macros for CDC */
		/** Endpoint number of the CDC device-to-host notification IN endpoint. */
		#define CDC_NOTIFICATION_EPNUM         2
		/** Endpoint number of the CDC device-to-host data IN endpoint. */
		#define CDC_TX_EPNUM                   3	
		/** Endpoint number of the CDC host-to-device data OUT endpoint. */
		#define CDC_RX_EPNUM                   4	
		/** Size in bytes of the CDC device-to-host notification IN endpoint. */
		#define CDC_NOTIFICATION_EPSIZE        8
		/** Size in bytes of the CDC data IN and OUT endpoints. */
		#define CDC_TXRX_EPSIZE                64	

	/* Macros for MIDI */
		/** Endpoint number of the MIDI streaming data IN endpoint, for device-to-host data transfers. */
		#define MIDI_STREAM_IN_EPNUM        2
		/** Endpoint number of the MIDI streaming data OUT endpoint, for host-to-device data transfers. */
		#define MIDI_STREAM_OUT_EPNUM       1
		/** Endpoint size in bytes of the Audio isochronous streaming data IN and OUT endpoints. */
		#define MIDI_STREAM_EPSIZE          64
		
	/* Type Defines for CDC */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t    Config;
			USB_Descriptor_Interface_t               CDC_CCI_Interface;
			CDC_FUNCTIONAL_DESCRIPTOR(2)             CDC_Functional_IntHeader;
			CDC_FUNCTIONAL_DESCRIPTOR(1)             CDC_Functional_AbstractControlManagement;
			CDC_FUNCTIONAL_DESCRIPTOR(2)             CDC_Functional_Union;
			USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;
			USB_Descriptor_Interface_t               CDC_DCI_Interface;
			USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
			USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
		} USB_Descriptor_ConfigurationCDC_t;

	/* Type Defines for MIDI */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
			USB_Descriptor_Interface_t            Audio_ControlInterface;
			USB_Audio_Interface_AC_t              Audio_ControlInterface_SPC;
			USB_Descriptor_Interface_t            Audio_StreamInterface;
			USB_MIDI_AudioInterface_AS_t          Audio_StreamInterface_SPC;
			USB_MIDI_In_Jack_t                    MIDI_In_Jack_Emb;
			USB_MIDI_In_Jack_t                    MIDI_In_Jack_Ext;
			USB_MIDI_Out_Jack_t                   MIDI_Out_Jack_Emb;
			USB_MIDI_Out_Jack_t                   MIDI_Out_Jack_Ext;
			USB_Audio_StreamEndpoint_Std_t        MIDI_In_Jack_Endpoint;
			USB_MIDI_Jack_Endpoint_t              MIDI_In_Jack_Endpoint_SPC;
			USB_Audio_StreamEndpoint_Std_t        MIDI_Out_Jack_Endpoint;
			USB_MIDI_Jack_Endpoint_t              MIDI_Out_Jack_Endpoint_SPC;
		} USB_Descriptor_ConfigurationMIDI_t;
		
	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    void** const DescriptorAddress) ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);
#endif
