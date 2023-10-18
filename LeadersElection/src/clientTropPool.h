/**
 * fichier: header-client.h
 * auteur: Rambal Julien
**/



#ifndef ClientTropPool_h
#define ClientTropPool_h


#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h> 
#include<string.h>
#include "helper_function.h"

#include<netinet/in.h>
#include<poll.h>

/* Programme serveur */

#include "Stub.h"
#include"MyNode.h"
#include"ParserJ.h"
#include"my_sockaddr.h"
#include"ColorParam.h"
#include"Cluster.h"
#include"my-util.h"
#include"tableau.h"
#include"my_file.h"
#include"my_poll.h"
#include "message.h"
#include"convert.h"
#include <ifaddrs.h>
#include "Links.h"
#include <errno.h>
/* Programme client */

#define MAXBUFLEN 1000
#define MAX_THREAD_NN_CL 10
 #define BACKLOG 10
#define getSckListenIndex() 0


#define pasPourLinstant 0
#define pasici 0

#define DEBUG_CLI 0
#define debug_client 0 

struct tabScki{
    struct sockaddr_in ** tab_addr;
    size_t taille_tab ;
};

    struct tabScki * cst_tabScki ( struct sockaddr_in** _tabAddr , size_t _taille);

    struct tabScki * cst_cpy_tabScki( struct sockaddr_in** _tabAddr , size_t _taille);


    int index_parentsocket();
    int index_childsocket();



  int ClientTropPool(char* port_serveur,char* ip_serveur ,char* _inport,char* _outport) ;

  #endif