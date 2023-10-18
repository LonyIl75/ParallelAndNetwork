
/**
 * fichier: MyNode.h
 * auteur: Rambal Julien
 * description : Contient les definitions des types de machines constituant le reseau (NodeHandler , ClientHandler , Node) 
 **/


#ifndef MyNode_h
#define MyNode_h


#include <stdio.h> 
#include <unistd.h>
#include"my-util.h"

#include"Cluster.h"
#include <stdlib.h>
#include "Links.h"
#include<string.h>
#include <errno.h>
#include <limits.h>
#include"my_sockaddr.h"


#include "hashAddr.h"
#include "tableau.h"


struct Machine { // pour l' instant Machine <=> Node 

    unsigned int uid ; //id universelle propre au reseau
    struct Link *  inputs , * outputs ; //a la fin du tableau outputs il y a une socket listen elle servira a initialiser les n-1 connections et a se faire écraser par la n ème



};


struct Machine* cst_Machine(unsigned int uid);



struct NetworkMetadata{

    //TRANSFORMER EN GRAPH : TODO  voir enlever car deja dans ColorationParam
    int ** uids ;//matrice 1 0
    unsigned int * nb_edges; // devrait etre nb edges[2] pour chaque uid
    size_t taille ;
    //TR

    struct sockaddr_in *** addresses ;
    struct sockaddr_in **** neightbors ; 
    struct ClusterMeta * cluster ; 
    struct ColorationParam* coloration ;
    struct ColorationResult * CRF ;

    
    size_t debug_taille ; 


};


struct NetworkMetadata*  cst_networkMetadata (struct GraphData* _graphD );

struct NameNode2 {// je suis un NodeHandler
    struct Machine * mach ;
    struct NetworkMetadata * metas;
    
    int pid ;
    int fd_sck;


    };

struct NameNode2* cst_nameNode2 ( int _pid ,struct Machine *  _mach  , int _fdsck, struct NetworkMetadata* _nwm );


void print_metasAddresses( struct NameNode2* _nn);

void addcouple (struct NameNode2* _nn, int _id , struct sockaddr_in**couple);

void extractNeighbours(struct NameNode2 * _nn );


struct NameNode1 {// je suis un ClientHandler
    struct Machine * mach ;


    int pid;
    struct Link *  client_serv   ;
    int fd_sck;



};



void updateServ(struct NetworkMetadata* meta, int idCluster );
int  stdTab (int**res , int* tab , size_t taille);
struct ColorationResult* stdCR(struct ColorationResult* res);
struct ColorationResult*  launchColorFinal(struct ColorationResult* res ,struct NetworkMetadata* meta );

struct NameNode1* cst_nameNode1( int _pid ,struct Machine *  _mach  ,  int _fdsck);

#endif 