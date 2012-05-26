/* Grenoble INP - Phelma			taskFlyport.c
 * Projet de groupe 2012			Wi-Fi controlled car project.
 *
 * Groupe n°22 :
 *
 * 		Florian Castellane		Guillaume Mahieux
 *		Jérémy Fanguède			Florian Tavares
 */

#include "taskFlyport.h"
#include <time.h>
#include <ctype.h>

/* Available pins on the car are (from left to right) :
 *		24 (3.3V)		2	3 (AN_IN_1)		22 (GND)
 *		20(AN_IN_5)		19 (FPT LED 2)		18 (AN_IN_4)
 *		15 (TX)			16 (5V)				13 (RX)
 *		14 (SPI_CS)		12 (SPI_IN)			9 ()
 *		10 (SPI_OUT)	7 ()				8 (SPI_CLK)
 *		5 ()			3 ()				1 ()
 */

/* PWM-compatible pins are :
 * 2, 4, 6, 8, 9, 10, 11, 12, 13,
 * 14, 15, 17, 18, 19, 20, 23, 25.
 */

#define YES 1
#define NO  0
#define Hz

#define LED1 d5out
#define LED2 d4out


/* General settings */
#define RESET_ON_LOST_CONNECTION NO
#define ENABLE_CUSTOM_CONNECTION YES


/* Flyport PWM item number (up to 9). */
#define MODULE_PWM_SERVO  	(1)
#define MODULE_PWM_MOTEUR 	(2)
#define MODULE_PWM_CLIGNO_G (3)
#define MODULE_PWM_CLIGNO_D (4)


/* PWM frequency (Hz). */
#define PWM_SERVO_FREQ    (333)  // Should be lower than 1/(2400E-6) = 416,666 HZ
#define PWM_MOTEUR_FREQ   (20E3)


/* The servo is controled by pulse lenght, not duty cycle. These are maximum values for HiTec servomotor. */
#define SERVO_MIN_PULSE   (600E-6)
#define SERVO_MAX_PULSE   (2400E-6)


/* Motors output pins. */
#define PIN_PWM_SERVO	  (p6)
#define PIN_PWM_1_MOTEUR  (p4)
#define PIN_PWM_2_MOTEUR  (p17)


/* Lights pins */
#define PIN_PHARES		(p14)
#define PIN_CLIGNO_G	(p12)
#define PIN_CLIGNO_D	(p9)


/* Buzzer pin */
#define PIN_BUZZER		(p10)


/* IP adress to 7 segment */
#define PIN_IP_ENABLE 	(p7)
#define PIN_IP_A 		(p8)
#define PIN_IP_B 		(p5)
#define PIN_IP_C 		(p3)
#define PIN_IP_D	 	(p1)


/* Functions declaration */
void InitialiserVoiture(void);
void InterpreterCommandes(char* read);


/* Global variables */
float angleServomoteur = 49;


void FlyportTask()
{
	/* Variables déclaration */
	
		TCP_SOCKET socketServer = INVALID_SOCKET;
		BOOL clconn = FALSE;
		char read[100];
		int tcprxlength = 0;
		char chaine[20];
	
		DWORD CurrentTick =  TickGet(); // timer related variables
		DWORD StartTime =  TickGet();
		DWORD ElapsedTimeMs = 0;
	
		
		
	/* Iniatialisation de tous les pins de sortie. */
	
		// PWM Servomoteur (Direction)
		IOInit(PIN_PWM_SERVO, out);
		PWMInit(MODULE_PWM_SERVO, PWM_SERVO_FREQ, 49.624);
	
		// PWM 1 (Vitesse, L298)
		IOInit(PIN_PWM_1_MOTEUR, out);
		PWMInit(MODULE_PWM_MOTEUR, PWM_MOTEUR_FREQ, 0);
		PWMOn(PIN_PWM_1_MOTEUR, MODULE_PWM_MOTEUR);
	
		// PWM 2 (Vitesse, L298)
		IOInit(PIN_PWM_2_MOTEUR, out);
		IOPut(PIN_PWM_2_MOTEUR, off);
		
		// Phares avant
		IOInit(PIN_PHARES, out);
		IOPut(PIN_PHARES, on); // Allume les phares
	
		// Clignotant gauche
		IOInit(PIN_CLIGNO_G, out);
		PWMInit(MODULE_PWM_CLIGNO_G, 2 Hz, 50);
	
		// Clignotant droit
		IOInit(PIN_CLIGNO_D, out);
		PWMInit(MODULE_PWM_CLIGNO_D, 2 Hz, 50);

		// Décodeur 4 bits + afficheur 7 segment
		IOInit(PIN_IP_ENABLE, out);
		IOPut(PIN_IP_ENABLE,off); // Enable
		
		IOInit(PIN_IP_A, out);	// Bit A
		IOInit(PIN_IP_B, out);	// Bit B
		IOInit(PIN_IP_C, out);	// Bit C
		IOInit(PIN_IP_D, out);	// Bit D
	
	
	
	/* Met les roues droites. */
	
		InitialiserVoiture();
	
		
	
	/* Wi-Fi connection */
	
		// Connection
		if (ENABLE_CUSTOM_CONNECTION)
		{
			NETSetParam(MY_IP_ADDR, "192.168.1.115");
			NETSetParam(PRIMARY_DNS, "192.168.1.1");
			NETSetParam(SECONDARY_DNS, "192.168.1.1");
			NETSetParam(MY_GATEWAY, "192.168.1.1");
			NETSetParam(SUBNET_MASK, "255.255.255.0");
			NETSetParam(NETBIOS_NAME, "");
			NETSetParam(DHCP_ENABLE, "DISABLED");		// ENABLED ou DISABLED
			NETSetParam(SSID_NAME, "Flyport");
			NETSetParam(NETWORK_TYPE, "INFRASTRUCTURE");// ADHOC ou INFRASTRUCTURE
			WFConnect(WF_CUSTOM);
			while (WFStatus != CONNECTED);
			UARTWrite(1,"Flyport is now connected with custom settings.\r\n");
		}
		else {
			WFConnect(WF_DEFAULT);
			while (WFStatus != CONNECTED);
			UARTWrite(1,"Flyport is now connected with wizard settings.\r\n");
		}
		vTaskDelay(200);
			
	
		// Write IP on UART
		UARTWrite(1, "IP adress: ");
		IPAddressToString(AppConfig.MyIPAddr, chaine);
		UARTWrite(1, chaine);
		UARTWrite(1, ".\r\n");
	
	
	
	/* Affichage de l'adresse IP sur l'afficheur 7 segments */

		int i, number;
		for (i = 0; i<strlen(chaine); i++) {
			if (chaine[i] >= '0' && chaine[i] <= '9') {
				number = (chaine[i]-'0');
				IOPut(PIN_IP_ENABLE, on);
				IOPut(PIN_IP_A, (number & 1)?on:off);
				IOPut(PIN_IP_B, (number & 2)?on:off);
				IOPut(PIN_IP_C, (number & 4)?on:off);
				IOPut(PIN_IP_D, (number & 8)?on:off);
				vTaskDelay(50);
				IOPut(PIN_IP_ENABLE, off);
				vTaskDelay(10);
			}
			else {
				IOPut(PIN_IP_ENABLE, off);
				vTaskDelay(50);
			}
		}
	
	
	/* Boucle principale d'éxecution */
    while(1)
    {
		if (TCPisConn(socketServer)) {
			if (clconn == FALSE) {	// Connecté, LED allumée
				clconn = TRUE;
				IOPut(LED2, on);
			}
		} else {
			if (clconn == TRUE) {	// Connection perdue, LED éteinte
				clconn = FALSE;
				IOPut(LED2, off);
				
				InitialiserVoiture();
				
				if (RESET_ON_LOST_CONNECTION)
					Reset();
			}
		}
		
		if(socketServer == INVALID_SOCKET)
		{
			socketServer = TCPServerOpen("2050");
			UARTWrite(1,"Ouverture de la connexion sur le port 2050.\r\n");
		}
		else
		{
			tcprxlength = TCPRxLen(socketServer);
			if(tcprxlength > 0)
			{
				TCPRead(socketServer,read,tcprxlength);
				InterpreterCommandes(read);
				UARTWrite(1,read);
			}
			
		}
		
		/* Mise à jour de l'angle du servomoteur toutes les 20 ms. */
		ElapsedTimeMs = TickConvertToMilliseconds(TickGet() - StartTime);
		if (ElapsedTimeMs < 20) {
			PWMOff(1);
		} else {
			PWMDuty(angleServomoteur, MODULE_PWM_SERVO);
			PWMOn(PIN_PWM_SERVO, MODULE_PWM_SERVO);
			StartTime = CurrentTick;
		}
		
		/* Clignotant gauche. */
		if (angleServomoteur < 45)
			PWMOn(PIN_CLIGNO_G, MODULE_PWM_CLIGNO_G);
		else
			PWMOff(MODULE_PWM_CLIGNO_G);
		
		/* Clignotant droit. */
		if (angleServomoteur > 53)
			PWMOn(PIN_CLIGNO_D, MODULE_PWM_CLIGNO_D);
		else
			PWMOff(MODULE_PWM_CLIGNO_D);
    }
}

void InitialiserVoiture(void)
{
	PWMDuty(0, MODULE_PWM_MOTEUR);		// (PWM1) Arrêter le moteur (0% duty cycle)
	IOPut(PIN_PWM_2_MOTEUR, off);		// (PWM2) Sortie à 0
	
	PWMDuty(49.624, MODULE_PWM_SERVO);	// mettre les roues droites (50% duty cycle)
	vTaskDelay(5); // Wait 50 ms
	PWMOff(MODULE_PWM_SERVO);
}

void InterpreterCommandes(char* read)
{
	char car = 0;
	int val = 0;
	
	int numberOfItems = sscanf(read,"%c%i",&car,&val);
	
	// One argument commands
	if (numberOfItems == 1)
	{
		if (toupper(car) == 'D') {	//commande de direction / droite 
			angleServomoteur = 61;
		}
		else if (toupper(car) == 'G')//gauche
		{
			angleServomoteur = 37;
		}
		else if ( car == '/' )				//avant droit
		{
			PWMOn(PIN_PWM_SERVO,1);
			PWMDuty(55,1);
		}
		else if ( car == '\\' )				//avant gauche
		{
			PWMOn(PIN_PWM_SERVO,1);
			PWMDuty(43,1);
		}
		else if ( car == '|' )				// 
		{
			angleServomoteur = 49;
		}
		else if (toupper(car) == 'P')		// Toggle front lights
		{
			IOPut(PIN_PHARES, toggle);		// Toggle lights
		}
		else if (toupper(car) == 'S')		// Stopping the car
		{
			IOPut(p17,off);
			PWMDuty(0,2);		//commande de vitesse
		}
		else 
			UARTWrite(1, "Invalid request.\r\n");
	}
	// Two argument commands
	else if (numberOfItems == 2)
	{
		if (toupper(car) == 'T')
		{
			if (val <= 1000 && val >= 0)
				angleServomoteur = 37.+(61.-37.)*val/1000.;
		}
		else if (toupper(car) == 'V' || toupper(car) == 'A') 
		{
			if (val <= 100 && val >= 0)
			{
				IOPut(p17,on);		// PWM 2 à 1
				PWMDuty(100-val,2); //commande de vitesse
				PWMOn(p4,2);
			}
		}
		else if (toupper(car) == 'R')
		{
			if (val <= 100 && val >= 0)
			{
				IOPut(p17,off);		// PWM 2 à 0
				PWMDuty(val,2);		//commande de vitesse
				PWMOn(p4,2);
			}
		}
	}
	// Commande invalide
	else 
		UARTWrite(1, "Invalid request (wrong number of arguments).\r\n");
}
