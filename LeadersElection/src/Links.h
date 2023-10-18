/**
 * fichier: Links.h
 * auteur: Rambal Julien
 * description : Client (child process : != 0 ) et NodeHandler (father : 0) 
 * params :
 *      port_serveuri1 : port IN du clientHandler (clients et clients-noeuds)
 *      port_serveuro1 : port OUT du clientHandler (Nodes)
 *      port_serveurc1 : port IN/OUT du clientHandler (IN: recoit result de Nodes , OUT : clients  )
 **/


#ifndef LINKS_H
#define LINKS_H

#include "my-util.h"
#include "hashAddr.h"
#include <netinet/in.h>


struct Link {

    //POLL
    struct pollfd * pfds;
    nfds_t  nfds;
    size_t  pfds_size; //TODO : <=> nb_node
    //HASH ASSOCIATE 
     struct hash_linkInfo * descri ; // la hash est une description du pfds 
     size_t sz_hash; //TODO INUTILE <=> nfds 

};

struct Link* cst_Link(unsigned int length_ttPoll);



int link_lastElement(struct Link* _link);

void dst_Link(struct Link *_link);

void link_add2(struct Link* _link,struct sockaddr_in * scki_addElm , socklen_t addrlen_addElm, unsigned int id_addElm , int sck_addElm,unsigned int _pollEvent  );

//pollevent pas normal mettre dans le cst a la creation de la poll 
// creer fonction modifier poll_event dans link qui appelle topolle
void link_add(struct Link* _link,struct addrinfo * ainfo_addElm , unsigned int id_addElm , int sck_addElm,unsigned int _pollEvent  );

void link_addorReplace(struct Link* _link, struct sockaddr_in * scki_addElm , socklen_t addrlen_addElm , unsigned int id_addElm , int sck_addElm,unsigned int _pollEvent   );



int hash_defaultReplacePos(struct Link* _link); // return pos last element 

void link_delete(struct Link* _link, unsigned int pos_todelete   );



struct sockaddr_in * listAddrFromHash( struct Link* _link , int nb_node  );



#endif


