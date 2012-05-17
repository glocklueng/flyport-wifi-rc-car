#include "taskFlyport.h"

#define PWM_FREQUENCY 333
#define PIN_SERVO p6

void lireDonnee(char* read);

char angleServomoteur = 49;

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
    IOInit(PIN_SERVO,out);//direction
    PWMInit(1,PWM_FREQUENCY,49);
    //PWMOn(d3out,1);
	
	IOInit(p17,out);
	IOPut(p17,off);
    
	IOInit(p4,out);//vitesse
<<<<<<< .mine
	PWMInit(2,PWM_FREQUENCY,0);
	PWMOn(p4,2);
=======
	IOInit(p17,out);
    PWMInit(2,PWM_FREQUENCY,0);
	IOPut(p17,off);
    PWMOn(p4,2);
>>>>>>> .r179
	
	PWMOn(PIN_SERVO,1);
	PWMDuty(49,1);
	vTaskDelay(20);
	PWMOff(1);
	/*for ( i = 0;  i < 5 ; i++)
	{
		//avancer//
		IOPut(p21,on);
		PWMDuty(40,2);
		DelayMs(500);
		IOPut(p21,off);
		PWMDuty(60,2);
		DelayMs(500);
	}*/
	
	
    while(1)
    {
		if (TCPisConn(socketServer))
		{
			if (clconn == FALSE)
			{
				// Connected, turn on
				clconn = TRUE;
				IOPut(D4Out,on);
			}
		}
		else
		{
			if (clconn == TRUE)
			{
				// Not connected, turn led off
				clconn = FALSE;
<<<<<<< .mine
				IOPut(D4Out,off);
				
				IOPut(p17,off);
=======
				IOPut(p17,off);
				PWMDuty(0,2);
>>>>>>> .r179
				PWMOff(1);
				PWMDuty(0,2);
				PWMOff(2);
				//Reset();
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


void lireDonnee(char* read)
{
	char car;
	int val;
	sscanf(read,"%c%i",&car,&val);
	//sscanf(read,"%i",&val);
	//car = 'D';
	if ( car == 'D' || car == 'd' )//commande de direction// droite
	{
		/*//PWMDuty(convert(val),1);
		PWMOn(PIN_SERVO,1);
		PWMDuty(61,1);
		//DelayMs(100*/
		
		angleServomoteur = 61;
	}
	else if ( car == 'G' || car == 'g' )//gauche
	{
		/*PWMOn(PIN_SERVO,1);
		PWMDuty(37,1);*/
		angleServomoteur = 37;
	}
	else if ( car == '/' )//avant droit
	{
		PWMOn(PIN_SERVO,1);
		PWMDuty(55,1);
	}
	else if ( car == '\\' )//avant gauche
	{
		PWMOn(PIN_SERVO,1);
		PWMDuty(43,1);
	}
	else if ( car == '|' )//tout droit
	{
		/*PWMOn(PIN_SERVO,1);
		PWMDuty(49,1);
		vTaskDelay(9);
		PWMOff(1);*/
		angleServomoteur = 49;
	}
	else if (car == 'V' || car == 'v' || car == 'A' || car == 'a')
	{
		
		IOPut(p17,on);
		PWMDuty(100-val,2);//commande de vitesse
		PWMOn(p4,2);
	}
	else if (car == 'R' || car == 'r')
	{
		
		IOPut(p17,off);
		PWMDuty(val,2);//commande de vitesse
		PWMOn(p4,2);
	}
	else if (car == 's' || car == 'S')
	{
		IOPut(p17,off);
		PWMDuty(0,2);//commande de vitesse
	}
	else 
	{
		UARTWrite(1, "commande non valide\n");
	}
	PWMDuty(angleServomoteur,1);
	PWMOn(PIN_SERVO,1);
	//vTaskDelay(20);
	//PWMOff(1);
}
