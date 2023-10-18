


/**
 * fichier:my-poll.c
 * auteur: Rambal Julien
 * description : fonctions pour gérer les polls
 **/


#include"my_poll.h"


//PFDS :
void pfds_delete(struct pollfd pfds[], int index_del, nfds_t *nfds)
{    
    pfds[index_del] = pfds[(*nfds)--];
}


int pfds_growthSize(){return 2;}

void pfds_add(struct pollfd *pfds[], int sck_addElm, nfds_t *nfds, size_t *fd_size,unsigned int _pollEvent) //nfds nombre d'element dans le tableau != taille totale tableau 
{
    if (*nfds == *fd_size) {
        *fd_size *= pfds_growthSize(); 

        *pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size)); //TODO securize re-alloc voir si pas return ptr vers new location aussi 
    }

    (*pfds)[*nfds].fd = sck_addElm;
    (*pfds)[*nfds].events =  _pollEvent; 
    
    ++(*nfds);
}


void topolle(struct pollfd *pfds[], nfds_t nfds,unsigned int _poll){

    for(int i =0 ; i<nfds;i++ )(*pfds)[i].events = _poll; // Check ready-to-poll

    
}

