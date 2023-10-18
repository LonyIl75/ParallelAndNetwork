 
/**
 * fichier:myQueue.c
 * auteur: Rambal Julien
 * description : Ce qui est necessaire poure faire une Queue en C 
 **/




#include "myQueue.h"
void   cst_myqueue (struct stailhead* _head){
   STAILQ_INIT(_head);                
}

  
struct QueueElement *  cst_QueueElement (void * _data ,size_t sz_typedata){
    struct QueueElement* element  = (struct QueueElement*)malloc(sizeof(struct QueueElement));
    element->data = malloc(sz_typedata) ;        
    memcpy(element->data,_data,sz_typedata);         
    return element ; 
}


void  dst_QueueElement (struct QueueElement * del_elm ){
    freeToNull((void**)&del_elm->data);
    freeToNull((void**)&del_elm);
}


void dst_myqueue(struct stailhead* _head ){
    struct QueueElement * iter;
    STAILQ_FOREACH( iter, _head, entries)
    dst_QueueElement (iter);

    freeToNull((void**)&_head);

}


void print_myqueue(void  (*_fctPrint)(void* ), struct stailhead* _head) {
     struct QueueElement * iter;  
    STAILQ_FOREACH( iter, _head, entries)
             _fctPrint(iter->data);
   
    freeToNull((void**)&_head);

}



int push_myqueue (struct stailhead* _head ,void * add_dataElm , size_t sz_typeData ){
    struct QueueElement *add_elm  =cst_QueueElement(add_dataElm,sz_typeData);
    STAILQ_INSERT_HEAD(_head, add_elm, entries);
    return 1;

}


int locapush_myqueue (struct stailhead* _head ,struct QueueElement * ptr_pos, void * add_dataElm , size_t sz_typeData){
    struct QueueElement *add_elm  =cst_QueueElement(add_dataElm,sz_typeData);
    STAILQ_INSERT_AFTER(_head, ptr_pos,add_elm, entries);
    return 1;

}


struct stailhead* remove_myqueue(struct stailhead* _head ){
    struct QueueElement *del_elm = STAILQ_FIRST(_head);
    STAILQ_REMOVE_HEAD(_head, entries); 
    dst_QueueElement (del_elm);
    return _head;
}



struct stailhead* locaremove_myqueue (struct stailhead* _head ,struct QueueElement * ptr_pos ){
    STAILQ_REMOVE(_head, ptr_pos, QueueElement, entries);
    dst_QueueElement (ptr_pos);
    return _head;

}


struct QueueElement * peek_myqueue(struct stailhead* _head){
    return STAILQ_FIRST(_head);

}



struct QueueElement * poll_myqueue(struct stailhead* _head){
    struct QueueElement * poll_elm = STAILQ_FIRST(_head);
    STAILQ_REMOVE_HEAD(_head, entries); 
    return poll_elm;

}

int isEmpty_myqueue(struct stailhead* _head){
    return  STAILQ_EMPTY( _head);
}
