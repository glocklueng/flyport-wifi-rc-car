/**************************************************************
 * HTTPPrint.h
 * Provides callback headers and resolution for user's custom
 * HTTP Application.
 * 
 * This file is automatically generated by the MPFS Utility
 * ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS GENERATOR
 **************************************************************/

#ifndef __HTTPPRINT_H
#define __HTTPPRINT_H

#include "TCPIP Stack/TCPIP.h"

#if defined(STACK_USE_HTTP2_SERVER)

extern HTTP_CONN curHTTP;
extern HTTP_STUB httpStubs[MAX_HTTP_CONNECTIONS];
extern BYTE curHTTPID;

void HTTPPrint(DWORD callbackID);

void HTTPPrint(DWORD callbackID)
{
	switch(callbackID)
	{
		default:
			// Output notification for undefined values
			TCPPutROMArray(sktHTTP, (ROM BYTE*)"!DEF", 4);
	}

	return;
}

void HTTPPrint_(void)
{
	TCPPut(sktHTTP, '~');
	return;
}

#endif

#endif
