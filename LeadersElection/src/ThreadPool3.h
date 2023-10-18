/**
 * fichier: ThreadPool3.h
 * auteur: Rambal Julien
 * description : ThreadPool associe a une file de tache/operation
 **/


#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "myQueue.h"

#include <pthread.h>
#include "message.h"

#include <stdlib.h>
#include <stdio.h>
#include"ColorParam.h"
#include "Cluster.h"

// MARK: DATA TYPES





struct ThreadTask
{
    void  (*fct_task)(void *args); //function pour thread create 
    void *args; // thread args
};

struct ThreadPool
{
    size_t sz_pool;
    struct stailhead q_tasks;
    pthread_t *ths_pool;
    pthread_mutex_t lock_pool;
    pthread_cond_t sgn_pool;
    void (*add_tasksToPool)(struct ThreadPool *,  struct ThreadTask *);
};

// CONSTRUCTORS/DESTRUCTORS


struct ThreadPool * cst_ThreadPool (size_t _sz );
void dst_ThreadPool(struct ThreadPool * _tp );
struct ThreadTask cst_ThreadTask(void  (*fct_task )(void *arg), void *args);
void dst_ThreadTask(struct ThreadTask *);


#endif