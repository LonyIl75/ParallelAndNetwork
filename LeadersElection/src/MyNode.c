

/**
 * fichier:MyNode.c
 * auteur: Rambal Julien
 * description : Tout ce qui est necessaire pour initialiser la structure d'un noeud (client , serveur , etc) dans le réseau 
 **/


#include "MyNode.h"

struct Machine* cst_Machine(unsigned int uid){
    struct Machine* _mach= (struct Machine*)malloc(sizeof (struct Machine));
    //_mach->my_addr=my_addr;
     _mach->uid=uid;
     _mach->inputs = NULL;
     _mach->outputs = NULL;

     return _mach;

}




struct NetworkMetadata*  cst_networkMetadata (struct GraphData* _graphD){//, size_t _taille){
    int **_adjMatrix = _graphD->matrix;
    unsigned int* _nbEdges = _graphD->tabNbEdges;
    size_t _taille =  _graphD->nodesQuantity;


    struct NetworkMetadata* _nwm = (struct NetworkMetadata*)malloc(sizeof (struct NetworkMetadata));


    _nwm->uids=(int**)malloc(sizeof(int)*_taille);
    for(int i =0 ; i < _taille ; i++){
         _nwm->uids[i]=(int*)malloc(sizeof(int)*_taille );
         for(int k =0; k <  _taille ;k++)_nwm->uids[i][k]=_adjMatrix[i][k];
    }    
    _nwm->nb_edges = _nbEdges;
     _nwm->debug_taille=0;
     _nwm->taille=_taille;
    _nwm->addresses=(struct sockaddr_in***)malloc(sizeof(struct sockaddr_in**)*_nwm->taille);
    for(int i =0;i<_nwm->taille;i++){
        _nwm->addresses[i]= (struct sockaddr_in**)malloc(sizeof(struct sockaddr_in*)*2);
        _nwm->addresses[i][0]=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in)); // JUSTE LE C ENFAIT 
        _nwm->addresses[i][1]=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    }
    _nwm->neightbors = (struct sockaddr_in ****)malloc((sizeof(struct sockaddr_in ***))*_taille);
   for(int i =0 ; i<_taille;i++){
             _nwm->neightbors[i] = (struct sockaddr_in*** )malloc((sizeof(struct sockaddr_in **))*_nbEdges[i]); 
            for(int j = 0 ; j < _nbEdges[i]; j++){
                     _nwm->neightbors[i][j]= (struct sockaddr_in** )malloc((sizeof(struct sockaddr_in *)*2)); 

                      _nwm->neightbors[i][j][0]= (struct sockaddr_in* )malloc((sizeof(struct sockaddr_in ))); 
                      _nwm->neightbors[i][j][1]= (struct sockaddr_in* )malloc((sizeof(struct sockaddr_in ))); 

             }
         }
    _nwm->coloration= NULL;
    _nwm->cluster =NULL ;
  
    _nwm->CRF = NULL;

       return _nwm;
}






struct NameNode2* cst_nameNode2 ( int _pid ,struct Machine *  _mach  , int _fdsck, struct NetworkMetadata* _nwm ){
    struct NameNode2 * _nn =  (struct NameNode2*) malloc(sizeof(struct NameNode2));
    _nn->mach=_mach;
    _nn->metas=_nwm;
    _nn->pid = _pid;
    _nn->fd_sck=_fdsck;

    return _nn;

}


void print_metasAddresses( struct NameNode2* _nn){
     struct sockaddr_in *** iter= _nn->metas->addresses ;
         for(int i =0 ; i<_nn->metas->debug_taille ; i++){
            printf(" [%s\n",toTabCharSockaddr(iter[i],2));

    }
}
/*
void print_metasAddresses2( struct NameNode2* _nn){
     struct sockaddr_in *** iter= _nn->metas->addresses ;
         for(int i =0 ; i<_nn->metas->debug_taille ; i++){
            printf(" [%s\n",toTabCharSockaddr(iter[i],2));

    }
    }*/
void addcouple (struct NameNode2* _nn, int _id , struct sockaddr_in**couple){
    scki_memcpy (_nn->metas->addresses[_id][0],couple[0]);
    scki_memcpy (_nn->metas->addresses[_id][1],couple[1]);
    _nn->metas->debug_taille ++; //JUSTE LE C ENFAIT 

}


void updateServ(struct NetworkMetadata* meta, int idCluster ){
    struct ColorationResult * tabColorCluster = meta->cluster->bestColoring[idCluster] ; 
    struct ColorationParam*  tabColor = meta->coloration;
    int* tabTrad = meta->cluster->cluster2DTrad[idCluster];
    updateBestColor(  tabColor, tabColorCluster , tabTrad  );

}
/*int allDif( int* tab , int val ){
    for(int i =0 ; i <taille ;i++){
        if( tab[i] )
    }
}*/
int  stdTab (int**res , int* tab , size_t taille){//TODO ADEBUG 
    size_t  size_tab =1;
    int* diffTab = (int*)malloc(sizeof(int)*size_tab);
    int* buffhhh = NULL ; 
    *res =  realloc(*res,taille);
    for(int i =0;i<taille;i++)(*res)[i]=tab[i];

    qsort( *res ,taille , sizeof(int), intComparator ); 
    
    int index=0;
    for(int i =0 ; i < taille ;){
         if(size_tab<=index){
                size_tab*=2;
                size_tab++;
                buffhhh =(int*) malloc(size_tab*sizeof(int));
                for(int kiuo =0 ; kiuo <index ;kiuo++){
                    buffhhh[kiuo]=diffTab[kiuo];
                }
                //free(diffTab);//TODO ADEBUG !!!!
                diffTab= buffhhh ;
    }
    diffTab[index]=(*res)[i];
    while( i< taille && (*res)[i]==diffTab[index]){
        i++;
    }
    index++;
}
int j =0; 
for(int i =0; i < taille ; i++){
    for( j =0; j < index ; j++)if(tab[i]==diffTab[j])break;
    (*res)[i]=j;
}
print_tab_int(*res,index);
return index ; 

}



/*

int stdTab (int** resTab , int* tab , size_t taille){
    size_t  size_tab =1;

    (*resTab) =  realloc((*resTab) ,taille);
    int* cpyTab = (int*)malloc(sizeof(int)*taille);
    for(int i =0;i<taille;i++)cpyTab[i]=tab[i];
    
    qsort( cpyTab ,taille , sizeof(int), intComparator ); 
    printf("sort fin !\n");
    int index=0;
    int tmp_val =0;

    for(int i =0 ; i < taille ;){
        tmp_val= (*resTab)[i];
        printf("la %d \n",i< taille && (*resTab)[i]==tmp_val);
        while( i< taille && (*resTab)[i]==tmp_val){
            (*resTab)[i]=index;
            i++;
            printf("icic\n");
        }
        index++;
}
for(int i =0;i<taille;i++)(*resTab)[i]=tab[i];

return index;


}*/
struct ColorationResult* stdCR(struct ColorationResult* res){
    int* resTab = (int*)malloc(1);
    int colorCnt =stdTab (&resTab,res->coloring, res->taille);
    //free(res->coloring); //TODO ADEBUG 
    printf("\n Coloration  (FINAL) :"); 
    print_tab_int(resTab,res->taille);
    res->coloring=resTab;
    res->color_cnt= colorCnt;
    return res ; 
    //return cst_colorResult(resTab , colorCnt ,res->taille);

}
struct ColorationResult*  launchColorFinal(struct ColorationResult* res ,struct NetworkMetadata* meta ){
    //printf("Coloration Result :"); 

    struct ColorationParam* metaColor = meta->coloration ;
        struct GraphData * grp = metaColor->graphD ;
    size_t taille =grp->nodesQuantity;
    //print_tab_int(metaColor->fixed, taille );
    printf("\n Coloration Fixed (FINAL) :"); 
    int* fixedAdj =  fixed (grp->matrix ,taille , meta->cluster->cluster1D );
    print_tab_int(fixedAdj, taille );
    metaColor->fixed=andTab(metaColor->fixed , fixedAdj , taille );
    //printf("\n Coloration Result3 (FINAL) :"); 
    //print_tab_int(metaColor->fixed, taille );
    process_graph2( &res,metaColor);
    return stdCR(res);
    //printf("Launch Color Result_Standard : %s \n",CRToStr(*res));


}


void extractNeighbours(struct NameNode2 * _nn ) //int index )
{
     //printf("14\n");
      struct sockaddr_in* ptr ;
        int* taille_bis2 = (int*)malloc(sizeof(int)*_nn->metas->taille );
        //print_tab_int (_nn->metas->nb_edges ,_nn->metas->taille );

     for(int i =0 ; i< _nn->metas->taille  ;i++) taille_bis2[i]=2;
     //print_sockaddrTabtabtab (_nn->metas->addresses,_nn->metas->taille  , taille_bis2  );

      //printTabtab_int2(_nn->metas->uids,_nn->metas->taille );
      //printf("éiupoiip\n\n");
      int cst = 0 ;
        socklen_t addrlen = sizeof(struct sockaddr_in) ;
        for(int i =0 ; i<_nn->metas->taille;i++){
            cst=0;
            //printf("\n\n IIIIII %d TAILLE %d \n\n\n ",i,_nn->metas->taille);
            //for(cst = 0 ; cst < _nn->metas->nb_edges[i];){
                //printf("ij : %d \n",cst);
                for (int j =0; j< _nn->metas->taille ; j++){
                     //printf("ij %d %d %d  \n",i,j , _nn->metas->uids[i][j]);
                 if(0<_nn->metas->uids[i][j] && _nn->metas->uids[i][j]<INT_MAX) {
                    //printf("%d vs %d  EDGES %d vs  %d %p\n",i,_nn->metas->taille,cst,_nn->metas->nb_edges[i],_nn->metas->addresses[j][0]);
                     //printf("%p\n",_nn->metas->neightbors[i][cst][0]);

                     memcpy(_nn->metas->neightbors[i][cst][0]  ,_nn->metas->addresses[j][0],sizeof(struct sockaddr_in ) );
                       memcpy(_nn->metas->neightbors[i][cst][1]  ,_nn->metas->addresses[j][1],sizeof(struct sockaddr_in ) );
                     //memcpy(addrs_node[i][1]  ,addresses[j][1],sizeof(struct sockaddr_in ) );
                     //printf("BONJ %d %s \n",_nn->metas->nb_edges[i],toTabCharSockaddr(_nn->metas->neightbors[i][cst],2));
                    cst++;

                 }
               // }

            }

        }
       // print_sockaddrTabtabtab (_nn->metas->neightbors[0], _nn->metas->nb_edges[0] ,  taille_bis2 );
         //print_sockaddrTabtabtab2 (_nn->metas->neightbors,_nn->metas->taille , _nn->metas->nb_edges  , taille_bis2  );
         //print_sockaddrTabtabtab ( addrs_node ,nb_node,nb_edges  );
        //print_hashlink(_nn->mach->inputs->descri);   

}



struct NameNode1* cst_nameNode1( int _pid ,struct Machine *  _mach  ,  int _fdsck){
    struct NameNode1* _nn =  (struct NameNode1*) malloc(sizeof(struct NameNode1));
    _nn->mach=_mach;
    _nn->pid = _pid;
    _nn->fd_sck=_fdsck;
    _nn->client_serv = NULL;

    return _nn;

}


