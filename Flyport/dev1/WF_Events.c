/* **************************************************************************																					
 *  Software License Agreement
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  This is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License (version 2) as published by 
 *  the Free Software Foundation AND MODIFIED BY OpenPicus team.
 *  
 *  ***NOTE*** The exception to the GPL is included to allow you to distribute
 *  a combined work that includes OpenPicus code without being obliged to 
 *  provide the source code for proprietary components outside of the OpenPicus
 *  code. 
 *  OpenPicus software is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details. 
 * 
 * 
 * Warranty
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * WE ARE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 **************************************************************************/
#include "WF_Events.h"
/****************************************************************************
  FUNCTIONS TO HANDLE THE WIFI EVENTS
****************************************************************************/

//	CONNECTION SUCCESSFUL
void OnConnectionSuccessful(UINT8 ev, UINT16 evinfo)
{  
	IOPut (o5,on);
	#if defined(STACK_USE_UART)
	UARTWrite(1,"Event: Connection Successful\r\n"); 
	#endif
}

//	CONNECTION FAILED
void OnConnectionFailed(UINT8 ev, UINT16 evinfo)
{
	#if defined(STACK_USE_UART)
	char buf[8];
	UARTWrite(1,"Event: Connection Failed  -- eventInfo = ");
	sprintf(buf, "%d\r\n", evinfo);
	UARTWrite(1,buf);	
	#endif
}

//	CONNECTION TEMPORARLY LOST
void OnConnectionTempLost(UINT8 ev, UINT16 evinfo)
{
	#if defined(STACK_USE_UART)
	char buf[8];
	UARTWrite(1,"Event: Connection Temporarily Lost -- eventInfo = ");
	sprintf(buf, "%d\r\n", evinfo);
	UARTWrite(1,buf);
	#endif
}

//CONNECTION REESTABLISHED
void OnConnectionReestablished(UINT8 ev, UINT16 evinfo)
{
	#if defined(STACK_USE_UART)
	UARTWrite(1,"Event: Connection Reestablished\r\n");
	#endif
}
//	CONNECTION PERMANENTLY LOST
void OnConnectionPermLost(UINT8 ev, UINT16 evinfo)
{
	IOPut (o5,off);
	#if defined(STACK_USE_UART)    
	char buf[8];   
	UARTWrite(1,"Event: Connection Permanently Lost -- eventInfo = ");
	sprintf(buf, "%d\r\n", evinfo);
	UARTWrite(1,buf);
	#endif
}

//	SCAN RESULT
void OnScanResult(UINT8 ev, UINT16 evinfo)
{
	#if defined(STACK_USE_UART)
	char buf[8];
	UARTWrite(1,"Event: Scan Results Ready,");
	sprintf(buf, "%d", evinfo);
	UARTWrite(1,buf);
	UARTWrite(1,"results\r\n");
	#endif
}

