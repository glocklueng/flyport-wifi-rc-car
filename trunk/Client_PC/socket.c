/* Inclusions standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* ConnectivitÃ© TCP/IP */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>		/* close */
#include <netdb.h>		/* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int     SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#define h_addr  h_addr_list[0]	/* pour compatibilitÃ©.  */

/* ParamÃ¨tres de connexion par dÃ©faut */
#define ADDR_IP	"192.168.1.115"
#define PORT	2050
#define BUFFER_SIZE 100

int main(void)
{
	/* CrÃ©ation du socket */
	SOCKET          sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		perror("socket()");
		exit(errno);
	}
	
	/* Connexion au serveur */
	SOCKADDR_IN     sin = {0};	/* initialise la structure avec des 0 */
	const char     *hostname = ADDR_IP;
	struct hostent *hostinfo = gethostbyname(hostname);	/* on rÃ©cupÃ¨re les informations de l'hÃ´te auquel on veut se connecter */

	if (hostinfo == NULL) {	/* l'hÃ´te n'existe pas */
		fprintf(stderr, "Unknown host %s.\n", hostname);
		exit(EXIT_FAILURE);
	}
	sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;	/* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
	sin.sin_port = htons(PORT);	/* choix du port utilisÃ© */
	sin.sin_family = AF_INET;

	if (connect(sock, (SOCKADDR *) & sin, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		perror("connect()");
		exit(errno);
	}
	
	/* Boucle du client TCP / Envoi-RÃ©ception des donnÃ©es */
	char            buffer[100];
	int             duty_cycle, continuer = 1;
	while (continuer) {
		printf("Entrez un rapport cyclique (0-100) : ");
		scanf("%d", &duty_cycle);

		/* Correction des valeurs entrÃ©es */
		if (duty > 100)
			duty_cycle = 100;
		if (duty < 0)
			duty_cycle = 0;

		/* Formattage de la requÃªte Flyport */
		sprintf(buffer, "d=%d\n", duty_cycle);

		if (send(sock, buffer, strlen(buffer), 0) < 0) {
			perror("send()");
			exit(errno);
		}
	}

	/* Cloture de la connexion */
	closesocket(sock);

	return EXIT_SUCCESS;
}



