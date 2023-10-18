/**
 * fichier:my_sockaddr.h
 * auteur: Rambal Julien
 * description : fonctions utiles pour gérer notamment les  tableau 1D ,2D de sockaddrs
 **/



#ifndef MY_SOCKADDR_H
#define MY_SOCKADDR_H

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
#include"my-util.h"
#include "tableau.h"
#include <limits.h>


#define debug_sockaddr 0
#define DEBUG_SOCKA 0

#define getFamilyIndex() 0
#define getPortIndex() 1
#define getIpIndex() 2
#define getTailleSerial() 3



const char sockAddrDelim();
const char* tabSockaddrDelims();


void charToSockAddr(struct sockaddr_in*** tab_sock , char* str , int taille ); 


void print_sockaddrTab (struct sockaddr_in *  tab,size_t taille );

void print_sockaddrTabtabtab (struct sockaddr_in ***  tab,size_t taille , int* taille_bis  );

void print_sockaddrTabtabtab2 (struct sockaddr_in ****  tab,int taille , int * taille_biso , int* taille_bis  );


struct addrinfo initialize_hintsTCP();


struct sockaddr_in* scki_memcpy (struct sockaddr_in* scki_dest , struct sockaddr_in* scki_src );

void scki_cpy (struct sockaddr_in* scki_dest , struct sockaddr_in* scki_src );

//struct sockaddr_in *  hintsToScki(struct addrinfo * addinfo , char* port ,char * addr_ip ) ;

char* toTabCharSockaddr4(  struct sockaddr_in *** addr , int taille_tab );

void scki_memcpy2 (struct sockaddr_in** scki_dest , struct sockaddr_in* scki_src );

void toCharSockaddr4(char ** str, const  struct sockaddr_in * addr);

void free_sckimemcpy(struct sockaddr_in* scki_dest );

void  copyaddrinfo(struct addrinfo* dst, struct addrinfo* src );

void *get_in_addr(struct sockaddr *sockfd);

in_port_t get_in_port(struct sockaddr *sa);

 int  strtoFamily (char* str );



const char * familyToStr (int family);

char * sockaddrtoStr2 (const  struct sockaddr_in * addr);


char * toCharSockaddr(const  struct sockaddr_in * addr);


char * toTabCharSockaddr( struct sockaddr_in ** addr , int taille_tab );

size_t strsockaddrTabtabtab (char ** result , struct sockaddr_in ***  tab,size_t taille , int* taille_bis  );

char* strsockaddrTabtabtab2(struct sockaddr_in ***  tab,size_t taille , int* taille_bis  );


int equalSockAddr (struct sockaddr_in * eq1 , struct sockaddr_in * eq2);
int isInSockAddr(struct sockaddr_in *** tab ,int index, size_t taille,  struct sockaddr_in * client_addr );

        ////////////



void print_addrinfo(struct addrinfo* address);

char *  sockaddrtoStr(const struct sockaddr * addr);
char * sockaddrintoStr (const  struct sockaddr_in*addr);

#endif