

/**
 * fichier: helper_function.h
 * auteur: Rambal Julien
 * description : Boite a outil de fonction Reseau 
 **/



#ifndef helper_function_h
#define helper_function_h

#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h> 
#include<string.h>
#include <errno.h>
#include "my-util.h"
#include "tableau.h"
#include "my_sockaddr.h"
#include "my_poll.h"

#define getSendToID() 0
#define getSendID()  1
#define getRecvfromID()  2 
#define  getRecvID()  3 


int err_manager ( const unsigned int  id_fonction , const int result_fonction , int socket  ); // si erreur : -1  ferme la socket 

#define getSocketID() 0
#define getConnectID() 1
#define getBindID() 2
#define getListenID() 3
#define getAcceptID() 4		
	 
int  err_socket ( unsigned int  id_fonction , int result_fonction ,int socket);  // si erreur : -1  ferme la socket 

void abort_sock(int code,char* fonction,char* error_mss , int sock);

int p_bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);

int p_accept(int sockfd,struct sockaddr *restrict addr,socklen_t * restrict addrlen);

int p_connect(int sockfd,const struct sockaddr * addr,socklen_t addrlen);
	
	
ssize_t p_recvfrom(int sockfd ,  void * buf , size_t len , int flags, struct sockaddr *dest_addr,socklen_t * addrlen);

ssize_t p_recv(int sockfd ,  void * buf , size_t len , int flags);

ssize_t p_sendto(int sockfd , const void * buf , size_t len , int flags,const struct sockaddr *dest_addr,socklen_t addrlen);

ssize_t p_send(int sockfd , const void * buf , size_t len , int flags);



int sec_bind(int sockfd,const struct sockaddr_in *addr);
int sec_accept(int sockfd,struct sockaddr_in *restrict addr);

int sec_connect(int sockfd,const struct sockaddr_in * addr);

int sec_send(int sockfd , const void * buf , size_t len );

int sec_sendto(int sockfd , const void * buf , size_t len ,const struct sockaddr_in *dest_addr);

int sec_recvfrom(int sockfd ,  void * buf , size_t len , struct sockaddr_in *dest_addr);

int sec_recv(int sockfd ,  void * buf , size_t len );
	

int TCPSocket() ; //Creer une socket en TCP si erreur : -1 exit(1) sinon renvoie socket

int UDPSocket() ; //Pareil en UDP  :socket(PF_INET, SOCK_DGRAM, 0)

void designerSocket(struct sockaddr_in * sockfd ,char* port ,char * addr_ip ) ; // Initialise sockfd->sin_family , port , addr_ip ect 

void df_designerSocket(struct sockaddr_in * sockfd ,char* port) ; // pareil mais port : INADDR_ANY 

struct sockaddr_in nommerSocket(int sockfd,char* port ,char * addr_ip ) ; // designer(serv ) + bind(sock,serv)  si erreur_bind : -1 exit(1) sinon return serv qui a été bindé à sockfd

struct sockaddr_in df_nommerSocket(int sockfd,char* port ) ; // pareil mais avec df_designer(serv) 


void connectTCP(int sockfd, struct sockaddr_in * serv_addr) ; // Connect sockfd avec serv_addr , si connect erreur:-1 alors close socket client exit(1)

void listenTCP(int listen_sockfd, size_t nbMaxAttente) ; //  Creer une socket d'ecoute listen_sockfd , si listen erreur :-1  alors exit(1) 


//Envoie le message avec for loop continue tant que nb_envoyer < sizeMsg :

int sendTCP(int fdsock, void* msg, int sizeMsg); // si un des bouts du message n'est pas correctement envoyer alors return -1 sinon return le nombre total de byte envoyer 
//affichage : A chaque bouts envoyer : printf le nombre de byte envoyer 


int send2TCP(int fdsock, void* msg, unsigned int sizeMsg); 
//envoie la (taille du message) via sendTCP +  envoie le (message) via sendTCP 


//Pareil mais avec recv :
int recvTCP(int fdsock, void* msg, unsigned int sizeMsg) ; //
int recv2TCP(int fdsock, void* msg, unsigned int sizeMsg) ;//


int my_sendTCP(int sock , char*  msg , int sizeMsg);// 


int my_recvTCP(int sock , char*  msg , int sizeMsg);//


int recv2TCP2(int fdsock, void** msg, unsigned int sizeMsg);


int get_listenTCP2(struct addrinfo  *hints ,char* port ,char * ip_addr2,  unsigned int backloge );

const char * getWelcomeStr();

int get_listenTCP(struct addrinfo *hints ,char*  port ,  unsigned int backloge );
int get_clientTCP(struct addrinfo *hints , char* port ,  char * ip );

size_t i_send(int sockfd , const int * buf , size_t len , int flags);







#endif /*helper_function_h */
