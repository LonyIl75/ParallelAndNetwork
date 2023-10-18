/**
 * fichier:hashAddr.c
 * auteur: Rambal Julien
 * description : Implemente une hashTable (dictionnaire d'adresse ) pour gérer les connections clients sur un poll notamment (liste de co)
 **/



#include "hashAddr.h"

void dst_linkInfo(struct hash_linkInfo* link_descri){
    for(struct hash_linkInfo* nxt = link_descri->hh.next ;link_descri!=NULL;link_descri=nxt){
        freeToNull((void**)&link_descri->ai_addr);
        freeToNull((void**)&link_descri);
        link_descri=nxt;
        if(nxt!=NULL)nxt=nxt->hh.next;

    }

}





void linkInfo_add (struct hash_linkInfo** link_descri  , struct sockaddr_in * scki_addElm, socklen_t addrlen_addElm , unsigned int id_addElm , int pfdsPos_addElm){
    struct hash_linkInfo  *info_addElm;
    info_addElm = (struct hash_linkInfo  *) malloc(1*sizeof (struct hash_linkInfo ));
    info_addElm->id = id_addElm;
    info_addElm->ai_addr = (struct sockaddr_in *) malloc(1*sizeof (struct sockaddr_in  ));
    info_addElm->ai_addr=scki_memcpy(info_addElm->ai_addr,scki_addElm);
    info_addElm->ai_addrlen =addrlen_addElm;
    info_addElm->pfds_pos=pfdsPos_addElm;
    HASH_ADD_INT(*link_descri, id, info_addElm);  // HASH_ADD"_INT"(hashTable , fieldName of key , elementToAdd) ; INT for type of key field
}


struct hash_linkInfo * linkInfo_find (struct hash_linkInfo * link_descri,unsigned int id_findElm){
    struct hash_linkInfo * info_findElm = NULL;
    HASH_FIND_INT(link_descri, &id_findElm, info_findElm);  /* id already in the hash? */
    return info_findElm ;


}
struct hash_linkInfo * find_byhashValue(struct hash_linkInfo * link_descri,unsigned int pfdsPos_findElm){
    struct hash_linkInfo *info_findElm ; //= malloc(sizeof struct hash_addr );
    for(info_findElm=link_descri;info_findElm!=NULL;info_findElm=info_findElm->hh.next){
        if(info_findElm->pfds_pos==pfdsPos_findElm)break;
    }
    return info_findElm ;

}



void replacePos_elementHash(struct hash_linkInfo** link_descri ,unsigned int pfdsPos_destElm, unsigned int pfdsPos_srcElm ){

    struct hash_linkInfo *ptr_destElm , *ptr_srcElm;

//printf("LLA %d %d \n",pfdsPos_destElm,  pfdsPos_srcElm );
    ptr_destElm = find_byhashValue( *link_descri, pfdsPos_destElm);
  
    ptr_srcElm = find_byhashValue( *link_descri, pfdsPos_srcElm);

//printf("LLA %p %p \n", ptr_destElm,  ptr_srcElm);
    if(ptr_destElm!= NULL  &&ptr_srcElm !=NULL){ HASH_DEL(*link_descri,  ptr_srcElm);
    if(pfdsPos_destElm!=pfdsPos_srcElm )ptr_destElm->pfds_pos=pfdsPos_srcElm;
}



}


void print_hashlink(struct hash_linkInfo * link_descri  ) {

    for ( struct hash_linkInfo  *iter = link_descri ; iter != NULL; iter = iter->hh.next) {
        printf("next hash id %d: pfds %d port_client: %d\n", iter->id,iter->pfds_pos, ntohs(get_in_port((struct sockaddr *)iter->ai_addr)));
    }


}
