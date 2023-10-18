/**
 * fichier: ThreadPool3.c
 * auteur: Rambal Julien
 * description : Implemente les fonctions de ThreadPool
 **/


#include "ThreadPool3.h"


typedef void  (*ma_fonction)( void* ) ; 

void * peekAndDoTask(void * args);
void add_tasksToPool(struct ThreadPool *_thsPool, struct ThreadTask *_thT);


struct ThreadPool * cst_ThreadPool (size_t _sz) {

        struct ThreadPool *  nw_tp ;
        if(( nw_tp = (struct ThreadPool *)malloc(sizeof(struct ThreadPool))) == NULL) {
        return NULL;
        }
        nw_tp->sz_pool = _sz;
        cst_myqueue (&nw_tp->q_tasks);
        nw_tp->lock_pool =(pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
        nw_tp->sgn_pool =(pthread_cond_t) PTHREAD_COND_INITIALIZER;
        pthread_mutex_lock(&nw_tp->lock_pool);
        if((nw_tp->ths_pool = (pthread_t *) malloc (sizeof(pthread_t)* nw_tp->sz_pool)) == NULL) {
            return NULL;
        } 

        for(int i =0 ; i < nw_tp->sz_pool; i++){

            pthread_create(&nw_tp->ths_pool[i],NULL,peekAndDoTask,(void*)nw_tp);
        }
        pthread_mutex_unlock(&nw_tp->lock_pool);
    
        nw_tp->add_tasksToPool =  add_tasksToPool;

    

        return nw_tp;

}
/*
void print_queue_computeRequest (struct ThreadPool * _tp){

    print_myqueue((ma_fonction )&print_computeRequest,&_tp->q_tasks);
}*/
/*
void print_queue_computeRequest (struct Queue *queue){
    struct Node *cursor = queue->list.head;
    struct ThreadTask* tt = NULL;
    //struct ComputeRequest * arg2 ;
    for ( int i =0 ; i < queue->list.length ;i++){
            tt = (struct ThreadTask* )cursor->data ;
            //arg2=(struct ComputeRequest *) tt->args ;
            //printf("Task : %s \n ",arg2.str_operation) 
            cursor = cursor->next;
    }
}*/


struct ThreadTask cst_ThreadTask(void  (*_fctTask)(void *args), void *_args)
{
    struct ThreadTask nw_thT;
    nw_thT.fct_task = _fctTask;
    nw_thT.args = _args;
    return nw_thT;
}



void dst_ThreadPool(struct ThreadPool *_thsPool)
{
    for (int i = 0; i < _thsPool->sz_pool; i++)
    {
        pthread_cond_signal(&_thsPool->sgn_pool);
    }
    for (int i = 0; i < _thsPool->sz_pool; i++)
    {
        pthread_join(_thsPool->ths_pool[i], NULL);
    }
    free(_thsPool->ths_pool);
   dst_myqueue(&_thsPool->q_tasks );
}


void executeTask(struct ThreadTask * _task) {

    _task->fct_task(_task->args);
}

void faking_work (unsigned int seconds){
    sleep(seconds);

}

void cst_Tree_fromString (char * str ){ //strlen +1 = size

     printf("Je commence a dessiner un arbre \n");
     faking_work(3);
     printf("J'ai fini de dessiner mon arbre ' \n");

}

void assignAndSend_task (){ 

     printf("Je commence a assigner et envoyer les taches petit a petit \n");
     faking_work(2);
     printf("J'ai fini d'assigner les taches \n");
     

}

   /*struct ComputeRequest * compute_rq = (struct ComputeRequest *) args;
    printf("La requete %d à demander de faire faire l'operation : %s au reseau \n",compute_rq->idRequest,compute_rq->str_operation);
    // struct Tree root = 
    cst_Tree_fromString(compute_rq->str_operation );
    //{ unsigned int [] uids ; ThreadTask [] tts } assigned_workers =
    assignAndSend_task(//root); // sans backtrack : une fois assigner durant processus on peut pas refaire meilleur choix :greedy pipeline
    printf("j'ai fini ma tache ! \n");*/



void handlerMessage(void* args ){

struct ComputeRequest * cp_rq = (struct ComputeRequest *) args;
struct Message * mss = cp_rq->mss;

    if(mss->hd==_CLUSTERING){
        //UNIQUEMENT SUR PLACE FCT TRAD vers CHAR* pas faite
        struct ClusteringParam* clusterParams = (struct ClusteringParam*) mss->content;
        if(checkClusteringParam(clusterParams)){
            (cp_rq->result)=(void*)makeClusters(clusterParams);
            print_tab_int ((int *) cp_rq->result  , clusterParams->graphD->nodesQuantity );
        }
        else{
            printf("Erreur clusterParams not good\n");
             (cp_rq->result)=NULL;
        }
    }
    else if(mss->hd==_COLORATION){
        struct ColorationParam* colorParams = (struct ColorationParam*) mss->content;
        if(checkColorationParam(colorParams)){
            int nbColor=color_graph(colorParams);
            (cp_rq->result)=(void*)&nbColor;
        }
        else{
            printf("Erreur colorParams not good\n");
             (cp_rq->result)=NULL;
        }

    }
    else if(mss->hd==_OPERATION) {
        printf("OPERATION \n");

    }
    else if(mss->hd==_ASK){
        printf("ASK \n");

    }else {
        printf("%s \n",headerToStr(mss->hd));

    }
}




void * peekAndDoTask(void * args){

    struct ThreadPool *param_tp = (struct ThreadPool*)args;
    while(1){
        pthread_mutex_lock (&param_tp->lock_pool);
        while (isEmpty_myqueue(&param_tp ->q_tasks) == 1) {
        pthread_cond_wait(&param_tp->sgn_pool,&param_tp->lock_pool);
        }    
        struct QueueElement *  firstTaskOfTP = (struct QueueElement * )poll_myqueue( &param_tp->q_tasks);
        pthread_mutex_unlock(&param_tp->lock_pool);

        executeTask(firstTaskOfTP->data);

        dst_QueueElement (firstTaskOfTP);

    }

    return NULL;
}




void add_tasksToPool(struct ThreadPool *_tp, struct ThreadTask *_tt)
{
    
    pthread_mutex_lock(&_tp->lock_pool);
    push_myqueue(&_tp->q_tasks, _tt, sizeof(struct ThreadTask ));
    //print_queue_computeRequest(&tp->q_tasks);
    pthread_mutex_unlock(&_tp->lock_pool);
    pthread_cond_signal(&_tp->sgn_pool ); //signale qu'il y a un travaille a faire 
    
}


