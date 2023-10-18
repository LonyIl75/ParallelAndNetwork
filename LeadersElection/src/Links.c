
/**
 * fichier:Links.c
 * auteur: Rambal Julien
 * description : Implemente des liaisons entre des machines distinctes notamment grace a une hashTable (dictionnaire addresse )
 **/




#include "Links.h"

struct Link* cst_Link(unsigned int length_ttPoll){
    struct Link* _link = (struct Link*)malloc(sizeof (struct Link));
    _link->pfds_size=length_ttPoll;
    _link->nfds=0;
    _link->sz_hash=0;
    _link->pfds = (struct pollfd *) malloc((sizeof (struct pollfd )) *length_ttPoll);
    _link->descri=NULL;// (struct hash_linkInfo *) malloc((sizeof (struct hash_linkInfo  )) *1);//marche pas avec hash imple (struct hash_linkInfo *) malloc((sizeof (struct hash_linkInfo  )) *length);
    
    return _link;
}
/*
struct Link* cst_Link(struct sockaddr_in ** scki_tab , int * tab_id , size_t taille   ){
    struct Link* _link = (struct Link*)malloc(sizeof (struct Link));
    _link->pfds_size=taille;
    _link->pfds = (struct pollfd *) malloc((sizeof (struct pollfd )) *length_ttPoll);
    _link->descri= NULL;//marche pas avec hash imple (struct hash_linkInfo *) malloc((sizeof (struct hash_linkInfo  )) *length);
   for(int i=0;i<taille;i++){
    link_add2(_link,scki_tab[i] ,taille , tab_id[i] , int sck_addElm,unsigned int _pollEvent  );
    }

    return _link;
}

*/



int link_lastElement(struct Link* _link){return _link->nfds-1 ;}

void dst_Link(struct Link *_link){
    dst_linkInfo(_link->descri);
    freeToNull((void**)&_link->pfds);

}

void link_add2(struct Link* _link,struct sockaddr_in * scki_addElm , socklen_t addrlen_addElm, unsigned int id_addElm , int sck_addElm,unsigned int _pollEvent  ){

    pfds_add(&_link->pfds,sck_addElm,&_link->nfds,&_link->pfds_size,_pollEvent);
    linkInfo_add(&_link->descri,scki_addElm,addrlen_addElm,id_addElm,link_lastElement(_link)) ;  
    _link->sz_hash++;

// TODO faire enum POLLIN , POLLOUT , POLLERR , POLLPRI ,POLLHUP,POLLNVAL 

}

//pollevent pas normal mettre dans le cst a la creation de la poll 
// creer fonction modifier poll_event dans link qui appelle topolle
void link_add(struct Link* _link,struct addrinfo * ainfo_addElm , unsigned int id_addElm , int sck_addElm,unsigned int _pollEvent  ){
   link_add2(_link,(struct sockaddr_in *)ainfo_addElm->ai_addr,ainfo_addElm->ai_addrlen,id_addElm,sck_addElm,_pollEvent); 

}

void link_addorReplace(struct Link* _link, struct sockaddr_in * scki_addElm , socklen_t addrlen_addElm , unsigned int id_addElm , int sck_addElm,unsigned int _pollEvent   ){
     int booli=(linkInfo_find(_link->descri,id_addElm )!=NULL);   
    linkInfo_add(&_link->descri,scki_addElm,addrlen_addElm,id_addElm,link_lastElement(_link)) ;
    if(booli){
       printf("iciLABAS\n");
       replacePos_elementHash(&_link->descri ,id_addElm, link_lastElement(_link) );
   }
   else{
    pfds_add(&_link->pfds,sck_addElm,&_link->nfds,&_link->pfds_size,_pollEvent);
   }


}



int hash_defaultReplacePos(struct Link* _link){return link_lastElement(_link) ;} // return pos last element 

void link_delete(struct Link* _link, unsigned int pos_todelete   ){
       replacePos_elementHash( &_link->descri,pos_todelete,hash_defaultReplacePos(_link));
       pfds_delete(_link->pfds, pos_todelete,&_link->nfds);
       _link->sz_hash--;

}




struct sockaddr_in * listAddrFromHash( struct Link* _link , int nb_node  ){
     printf("13\n");
    if(nb_node > _link->sz_hash) printf("il n'y a pas assez de connecté dans la hash ");
    struct sockaddr_in * tab_addr = (struct sockaddr_in * ) malloc((sizeof(struct sockaddr_in  ))*_link->sz_hash); 
    struct hash_linkInfo   *s = _link->descri ;
     for ( int i =0 ; s != NULL && i < nb_node ; i++ ) {
          memcpy(&tab_addr[i] , s->ai_addr,s->ai_addrlen);
        s = s->hh.next;
         
    }
    return tab_addr;


}
