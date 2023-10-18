


/**
 * fichier:my-poll.h
 * auteur: Rambal Julien
 * description : fonctions pour gérer les polls (pas aboutit )
 **/

#ifndef MYPOLL_H
#define MYPOLL_H


#include<poll.h>
#include <stdlib.h>
#include <errno.h>


void pfds_delete(struct pollfd pfds[], int index_del, nfds_t *nfds);

int pfds_growthSize();

void pfds_add(struct pollfd *pfds[], int sck_addElm, nfds_t *nfds, size_t *fd_size,unsigned int _pollEvent);

void topolle(struct pollfd *pfds[], nfds_t nfds,unsigned int _poll);


#endif