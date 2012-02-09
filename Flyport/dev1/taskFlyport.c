#include "taskFlyport.h"

void lireDonnee(char* read)
{
	char car;
	int val;
	sscanf(read,"%c %i",&car,&val);
	if ( car == 'D' )//commande de direction
	{
		PWMDuty(val, 1);
	}
	else if (car == 'V')
	{
		PWMDuty(val,2);//commande de vitesse
		
	}
	else 
	{
		UARTWrite(1, "commande non valide\n");
	}
	
}

void FlyportTask()
{
	TCP_SOCKET socketServer = INVALID_SOCKET;
	BOOL clconn = FALSE;
	char read[100];
	int tcprxlength = 0;
	
	
    WFConnect(WF_DEFAULT);
    while (WFStatus != CONNECTED);
    UARTWrite(1,"Flyport connected... hello world!\r\n");
	
	/*initialisation pins */
    IOInit(d3out,out);
    PWMInit(1,333,50);
    PWMOn(d3out,1);
    
	IOInit(d2out,out);
    PWMInit(2,333,50);
    PWMOn(d2out,2);
	
    while(1)
    {
		if (TCPisConn(socketServer))
		{
			if (clconn == FALSE)
			{
				clconn = TRUE;
				IOPut(D4Out,on);
			}
		}
		else
		{
			if (clconn == TRUE)
			{
				clconn = FALSE;
				IOPut(D4Out,off);
			}
		}
		
		if(socketServer == INVALID_SOCKET)
		{
			socketServer = TCPServerOpen("2050");
			UARTWrite(1,"Ouvert");
		}
		else
		{
			tcprxlength = TCPRxLen(socketServer);
			if(tcprxlength > 0)
			{
				TCPRead(socketServer,read,tcprxlength);
				lireDonnee(read);
				UARTWrite(1,read);
				
			}
			
		}

		/*	
        if (i==1) 
		{
			i=0;
			PWMDuty(80, 1);
		}
		else if (i==0) 
		{
			i=1;
			PWMDuty(20, 1);
		}
        vTaskDelay(100);*/
    }
}
