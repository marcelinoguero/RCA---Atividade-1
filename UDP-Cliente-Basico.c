#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio_ext.h>

/*
 * Cliente UDP
 */
void main(argc, argv)
int argc;
char **argv;
{

   int s;
   unsigned short port;
   int server_address_size;
   struct sockaddr_in server;
   char command[200],received[2000];

   /* 
    * O primeiro argumento (argv[1]) � o endere�o IP do servidor.
    * O segundo argumento (argv[2]) � a porta do servidor.
    */
   if(argc != 3)
   {
      printf("Use: %s enderecoIP porta\n",argv[0]);
      exit(1);
   }
  port = htons(atoi(argv[2]));

   /*
    * Cria um socket UDP (dgram).
    */
   if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }

   /* Define o endere�o IP e a porta do servidor */
   server.sin_family      = PF_INET;            /* Tipo do endere�o         */
   server.sin_port        = port;               /* Porta do servidor        */
   server.sin_addr.s_addr = inet_addr(argv[1]); /* Endere�o IP do servidor  */

   /* Envia a mensagem no buffer para o servidor */
   while(1){

	printf("\n> ");

	__fpurge(stdin);
	gets(command);

	if(strcmp("exit",command) == 0)
	  break;

	if (sendto(s, command, (strlen(command)+1), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("sendto()");
		exit(2);
	}

	if(recvfrom(s, received, sizeof(received), 0, (struct sockaddr *) &server, &server_address_size) <0)
	{
		perror("recvfrom()");
		 exit(1);
	}
	else{
   		printf("Recebida a mensagem\n\n %s \ndo endereco IP %s da porta %d\n",received,inet_ntoa(server.sin_addr),ntohs(server.sin_port));
	}

   }

   /* Fecha o socket */
   close(s);
}
