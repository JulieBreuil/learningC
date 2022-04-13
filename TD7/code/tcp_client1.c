#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

in_addr_t get_addr_from_string(char *name)
{
  in_addr_t s_addr;
  struct hostent *hp; 
  if ((hp = gethostbyname(name)) == NULL) {
    fprintf(stderr,"Machine %s inconnue\n",name); 
    exit(3); 
  }
  /* l'adresse se trouve dans le champ h_addr de la structure hp */
  /* la fonction htonl a déjà été appliquée par gethostbyname */
  s_addr=*(in_addr_t *) hp->h_addr;
  return (s_addr);
}

/* exemple d'un client TCP simple */


int main(int argc, char *argv[])
{
    int sock_client; 
    int sock_len=sizeof(struct sockaddr_in);
    struct sockaddr_in connect_addr;
    
    /* Creation de la socket */ 
    if ((sock_client=socket(AF_INET,SOCK_STREAM,0)) == -1)
      {
	perror("Creation de socket impossible"); 
	return -1; 
      } 
    
    /* Preparation de l'adresse d'attachement: 
       l'adresse sur laquelle nous allons nous connecter */ 
    connect_addr.sin_family=AF_INET; 
    
    /* Adresse: localhost, on suppose que le serveur est sur la machine 
       Attention: Conversion (interne) -> (reseau) avec htonl et htons 
       On écoute sur le port 20000 */
    connect_addr.sin_addr.s_addr=get_addr_from_string("127.0.0.1");
    connect_addr.sin_port=htons(20000);
    
    /* Demande de connection sur la socket */ 
    if (connect(sock_client,(struct sockaddr*) &connect_addr, sock_len) == -1) {
      perror ("Connect failed"); 
      exit(errno);
    }
    
    printf("Connection OK\n");

    while (1){
      char tab [100];
      strcpy(tab,"coucou");
      if(send (sock_client, tab, 100, 0) == -1){
        perror ("send impossible");
        return -1;
      }
    }

    return 0;
    
}


