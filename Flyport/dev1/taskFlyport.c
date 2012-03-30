#include "taskFlyport.h"


int convert( int val );
void lireDonnee(char* read);


void FlyportTask()
{
	TCP_SOCKET socketServer = INVALID_SOCKET;
	BOOL clconn = FALSE;
	char read[100];
	int tcprxlength = 0;
	
	
    WFConnect(WF_DEFAULT);
    while (WFStatus != CONNECTED);
    UARTWrite(1,"Flyport connected... hello world!\r\n");
	
	char chaine[20];
	IPAddressToString(AppConfig.MyIPAddr, chaine);
	UARTWrite(1,chaine);
	
	/*initialisation pins */
    IOInit(d3out,out);//direction
    PWMInit(1,333,49);
    //PWMOn(d3out,1);
    
	IOInit(d2out,out);//vitesse
    PWMInit(2,333,50);
    //PWMOn(d2out,2);
	
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
				PWMOff(1);
				PWMOff(2);
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
    }
}

int convert( int val )//conversion 0->100 => 20->80
{
	if (val <0)
		val = 0;
		
	if (val > 100)
		val =100;
		
	return val*60/100 +20;
		
}

void lireDonnee(char* read)
{
	char car;
	int val;
	sscanf(read,"%c%i",&car,&val);
	//sscanf(read,"%i",&val);
	//car = 'D';
	if ( car == 'D' || car == 'd' )//commande de direction// droite
	{
		//PWMDuty(convert(val),1);
		PWMOn(d3out,1);
		PWMDuty(61,1);
		//DelayMs(100);
		//PWMOff(1);
	}
	else if ( car == 'G' || car == 'g' )//gauche
	{
		PWMOn(d3out,1);
		PWMDuty(37,1);
	}
	else if ( car == '/' )//avant droit
	{
		PWMOn(d3out,1);
		PWMDuty(55,1);
	}
	else if ( car == '\\' )//avant gauche
	{
		PWMOn(d3out,1);
		PWMDuty(43,1);
	}
	else if ( car == '|' )//tout droit
	{
		PWMOn(d3out,1);
		PWMDuty(49,1);
		vTaskDelay(20);
		PWMOff(1);
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
