
/**
 * fichier: hashAddr.h
 * auteur: Rambal Julien
 * description : Implemente une hash Table grace a utash 
 * arguments :
 *      id : <=> uid du reseau
 *      ai_addr et ai_addrlen : addresse de la socket connecte et taille 
 *      pfds_pos :  position de la socket dans la poll 
 **/


#ifndef HASHADDR_H
#define HASHADDR_H

#include "my-util.h"
#include "uthash.h"
#include "my_poll.h"
#include <stdio.h> 
#include <stdlib.h>
#include<string.h>
#include <errno.h>
#include "helper_function.h"
#include "my_sockaddr.h"

struct hash_linkInfo {
    int id;      //uid ou id_client  
    struct sockaddr_in * ai_addr;
    socklen_t   ai_addrlen;
    int pfds_pos; //position de l'element hasher dans le pfds associer
    UT_hash_handle hh;  
};


void dst_linkInfo(struct hash_linkInfo* link_descri);


void linkInfo_add (struct hash_linkInfo** link_descri  , struct sockaddr_in * scki_addElm, socklen_t addrlen_addElm , unsigned int id_addElm , int pfdsPos_addElm);

struct hash_linkInfo * linkInfo_find (struct hash_linkInfo * link_descri,unsigned int id_findElm);
struct hash_linkInfo * find_byhashValue(struct hash_linkInfo * link_descri,unsigned int pfdsPos_findElm);


void replacePos_elementHash(struct hash_linkInfo** link_descri ,unsigned int pfdsPos_destElm, unsigned int pfdsPos_srcElm );


void print_hashlink(struct hash_linkInfo * link_descri  ) ;

#endif