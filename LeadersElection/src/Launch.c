
/**
 * fichier: Launch.c
 * auteur: Rambal Julien
 * description : (Stub) Lance N noeud-clients 
 * params : 
    * port_serveur : port IN du ClientHandler
    * ip_serveur : ip du ClientHandler 
    * nb_node : les N noeuds-clients a lancer 
 **/

#include "clientTropPool.c"
#include<string.h>
#include <stdlib.h>
#include <stdio.h> 




int main(int argc, char *argv[]) {


    if (argc != 4) {
        printf("utilisation : %s  port_serveur  ip_serveur  nb_node \n", argv[0]);
        exit(1);
    }
    int nb_node = atoi(argv[3]);
    //int pid_parent = getpid();

    for( int i =0 ; i < nb_node ;i++){

    	if(!fork()){ //fils
    		break;

    	}

    }
    ClientTropPool(argv[1],argv[2] ,NULL,NULL) ;




return 0;
}