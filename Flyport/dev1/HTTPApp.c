 
/****************************************************************************
  SECTION 	Include
****************************************************************************/

#include "TCPIP Stack/TCPIP.h"
#if defined(STACK_USE_HTTP2_SERVER)




/****************************************************************************
  SECTION	Define
****************************************************************************/
#define __HTTPAPP_C


/****************************************************************************
  SECTION 	Authorization Handlers
****************************************************************************/
 

/*****************************************************************************
  FUNCTION	BYTE HTTPNeedsAuth(BYTE* cFile)

  This function is used by the stack to decide if a page is access protected.
  If the function returns 0x00, the page is protected, if returns 0x80, no 
  authentication is required
*****************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPNeedsAuth(BYTE* cFile)
{
	//	If you want to restrict the access to some page, include it in the folder "protect"
	//	here you can change the folder, or add others
	if(memcmppgm2ram(cFile, (ROM void*)"protect", 7) == 0)
		return 0x00;		// Authentication will be needed later

	// You can match additional strings here to password protect other files.
	// You could switch this and exclude files from authentication.
	// You could also always return 0x00 to require auth for all files.
	// You can return different values (0x00 to 0x79) to track "realms" for below.

	return 0x80;			// No authentication required
}
#endif

/*****************************************************************************
  FUNCTION	BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
	
  This function checks if username and password inserted are acceptable

  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
{
	if(strcmppgm2ram((char *)cUser,(ROM char *)"admin") == 0
		&& strcmppgm2ram((char *)cPass, (ROM char *)"flyport") == 0)
		return 0x80;		// We accept this combination
	
	// You can add additional user/pass combos here.
	// If you return specific "realm" values above, you can base this 
	//   decision on what specific file or folder is being accessed.
	// You could return different values (0x80 to 0xff) to indicate 
	//   various users or groups, and base future processing decisions
	//   in HTTPExecuteGet/Post or HTTPPrint callbacks on this value.
	
	return 0x00;			// Provided user/pass is invalid
}
#endif

/****************************************************************************
  SECTION	GET/POST Form Handlers
****************************************************************************/
  
/****************************************************************************
  FUNCTION	HTTP_IO_RESULT HTTPExecuteGet(void)
	
  This function processes every GET request from the pages.
*****************************************************************************/
HTTP_IO_RESULT HTTPExecuteGet(void)
{

	
	return HTTP_IO_DONE;
}


#ifdef HTTP_USE_POST
/****************************************************************************
  FUNCTION	HTTP_IO_RESULT HTTPExecutePost(void)
	
  This function processes every POST request from the pages. 
*****************************************************************************/
HTTP_IO_RESULT HTTPExecutePost(void)
{

	
	return HTTP_IO_DONE;
}
#endif


#endif
