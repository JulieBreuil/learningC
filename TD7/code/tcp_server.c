#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


/* exemple d'un serveur TCP simple */


int main(int argc, char *argv[])
{
    int sock_serv; 
    int sock_len=sizeof(struct sockaddr_in);
    struct sockaddr_in listen_addr;
    
    /* Creation de la socket */ 
    if ((sock_serv=socket(AF_INET,SOCK_STREAM,0)) == -1)
      {
	perror("Creation de socket impossible"); 
	return -1; 
      } 
    
    /* Preparation de l'adresse d'attachement: 
       l'adresse sur laquelle nous allons nous connecter */ 
    listen_addr.sin_family=AF_INET; 
    
    /* Adresse: localhost, on suppose que le serveur est sur la machine 
       Attention: Conversion (interne) -> (reseau) avec htonl et htons 
       On écoute sur le port 20000 */
    /*INADDR_ANY signifie qu'on écoute sur toutes les interfaces*/
    listen_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    listen_addr.sin_port=htons(20000);

    //associe la socket du serveur à une adresse particulière, en général l'adresse locale
    if ((bind(sock_serv,(struct sockaddr*)&listen_addr,sock_len)) == -1)
    {
        perror("association d'une adresse à la socket du serveur impossible");
        return -1;
    }

    //serveur se met en écoute sur les connexions entrantes
    if(listen(sock_serv, 1) == -1)
    {
        perror("mise en ecoute du serveur impossible");
        return -1;
    }
    
    // accpet permet d'accepter des connexions entrantes
    //cette fonction crée un nouvel socket, qu'on appelle socket_service qui contient les infos sur la connexion
    int socket_service;
    socklen_t sock_serv_len=sizeof(struct sockaddr_in);
    if((socket_service=accept(sock_serv,(struct sockaddr*) &listen_addr, &sock_serv_len)) == -1)
    {
        perror("acceptation des connexions entrantes impossible");
        return -1;
    }

    printf("Connection accepted on port number %d\n", ntohs(listen_addr.sin_port));
    printf("IP Address=%u.%u.%u.%u\n",
        (uint8_t)((listen_addr.sin_addr.s_addr>>24)&255),
        (uint8_t)((listen_addr.sin_addr.s_addr>>16)&255),
        (uint8_t)((listen_addr.sin_addr.s_addr>>8)&255),
        (uint8_t)(listen_addr.sin_addr.s_addr&255));

    while (1){
        char tab [100];
        if(recv(socket_service,tab, 100, 0) == -1){
            perror ("recvimpossible");
            return -1;
        }
        printf("%s\n",tab);
    }

            
    return 0;
}