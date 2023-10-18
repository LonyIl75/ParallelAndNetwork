
/**
 * fichier: myQueue.h
 * auteur: Rambal Julien
 * description : Implemente une Queue grace a sys/queue.h
 **/



#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "my-util.h"

struct QueueElement {
    void * data ;
    STAILQ_ENTRY(QueueElement) entries;        /* STAILQ_ENTRY(type) name */
};

STAILQ_HEAD(stailhead, QueueElement); // initialise une structure qui contient ptr vers la fin et le debut de la queue de type myQueue 

  
void   cst_myqueue (struct stailhead* _head);
  
struct QueueElement *  cst_QueueElement (void * _data ,size_t sz_typedata);

void  dst_QueueElement (struct QueueElement * del_elm );

void dst_myqueue(struct stailhead* _head );


void print_myqueue(void  (*_fctPrint)(void* ), struct stailhead* _head);


int push_myqueue (struct stailhead* _head ,void * add_dataElm , size_t sz_typeData );


int locapush_myqueue (struct stailhead* _head ,struct QueueElement * ptr_pos, void * add_dataElm , size_t sz_typeData);


struct stailhead* remove_myqueue(struct stailhead* _head );


struct stailhead* locaremove_myqueue (struct stailhead* _head ,struct QueueElement * ptr_pos );

struct QueueElement * peek_myqueue(struct stailhead* _head);



struct QueueElement * poll_myqueue(struct stailhead* _head);


int isEmpty_myqueue(struct stailhead* _head);

#endif