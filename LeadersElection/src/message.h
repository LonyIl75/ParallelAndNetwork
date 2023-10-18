
/**
 * fichier:message.h
 * auteur: Rambal Julien
 * description : implemente une requete (pas aboutit TODO )
 **/


#ifndef my_message_h
#define my_message_h

#include <string.h>
#include <stdlib.h>
#define CPRQ_MAXBUFLEN 1000


enum header { _CONNECT_N ,
 _CONNECT_CL
 ,_OPERATION 
, _RESULTAT 
, _ASK 
, _EVENT 
, _OTHER 
, _COLORATION 
, _CLUSTERING
};


enum header  strtoHeader (char* str );


const char * headerToStr (enum header _hd );

struct Message{
    enum header hd;
    void* content ;

};

const char * messageDelim2();
const char messageDelim();

struct ComputeRequest {

    struct Message* mss ;
    void* result ;   // le nom de la fonction de threadTask 
};


/*
void print_computeRequest (struct ComputeRequest * _crq){
        printf("IDRequest :%d , operation: %s \n ",_crq->idRequest,_crq->str_operation) ;
    }*/




#endif /*my_message_h*/