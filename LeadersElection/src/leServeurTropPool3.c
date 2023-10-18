/**
 * fichier: leServeurTropPool3.h
 * auteur: Rambal Julien
 * description : Client (child process : != 0 ) et NodeHandler (father : 0) 
 * params :
 *      port_serveuri1 : port IN du clientHandler (clients et clients-noeuds)
 *      port_serveuro1 : port OUT du clientHandler (Nodes)
 *      port_serveurc1 : port IN/OUT du clientHandler (IN: recoit result de Nodes , OUT : clients  )
 **/


#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/stat.h>
#include<arpa/inet.h>
#include<string.h>

#include <pthread.h>
#include "message.h"
#include "helper_function.h"
//#include "ThreadPool3.h"

#include<poll.h>
#include <netinet/in.h>
/* Programme serveur */
#include <time.h>
#include "Stub.h"
#include"MyNode.h"
#include "ParserJ.h"
#include "Links.h"
#include "my_sockaddr.h"
#include"Cluster.h"
#include"ColorParam.h"

#define BACKLOG 250

#define MAXBUFLEN 100

#define MAX_THREAD_NN_CL 5 
#define MAX_THREAD_NN_ND 15 

#define MAX_TEMPS 7
#define MAX_TEMPS2 40

#define CLIENT_TIMEOUT  35 
#define SERVEUR_TIMEOUT 15
   
#define debug_Serv 0

int barrier(time_t start_time ){
    if(debug_Serv)printf("Barriere 1 %d \n",( time(NULL) - start_time) > MAX_TEMPS2);
    return (( time(NULL) - start_time) > MAX_TEMPS);

}

int barrier2(time_t start_time ){
    if(debug_Serv)printf("Barriere 2 %d \n",( time(NULL) - start_time) > MAX_TEMPS2);
    return (( time(NULL) - start_time) > MAX_TEMPS2);


}

#define pasla 0

time_t startTimer(){return time(NULL);}


int index_parentsocket(){return 0; }
int index_childsocket(){return 1; }
int failureProcedure(){printf("FAILURE " );return 1;}
//int checkInSockaddrinTab (){return 1;}
int main(int argc, char *argv[]) {


    if (argc != 8) {
        printf("utilisation : %s  port_serveuri1 port_serveuro1 port_serveurc1 port_serveuri2 port_serveuro2 path filename \n", argv[0]);
        exit(1);
    }

    
    int listen_sockfd ,new_fd; //=-1 
    int  numbytes=0;
    int incr_idRq=0;
    
    struct sockaddr_in client_addr;
    socklen_t tmp_addrlen = sizeof(struct sockaddr);
    char buf2[MAXBUFLEN] ;
    size_t pfds_size = 5;
    time_t times , times2;
    times=times2=0;
    int  CLcounter =0; 
    int fd[2];
    struct GraphData * graphSansServ =init_graphData ( argv[6],argv[7]);

  /*     for(int i =0 ; i < graphSansServ->nodesQuantity  ;i++){
    printf("i %d \n",i);
     printf("[|");
    for (int j =0; j<graphSansServ->nodesQuantity;j++)printf("%d %d |",j , graphSansServ->matrix[i][j]);
    printf("]\n");

 }*/


    struct GraphData * graphD = includeServGraphData( cpy_graphData ( graphSansServ));

/*
       for(int i =0 ; i < graphD->nodesQuantity  ;i++){
    printf("i %d \n",i);
     printf("[|");
    for (int j =0; j<graphD->nodesQuantity;j++)printf("%d %d |",j , graphD->matrix[i][j]);
    printf("]\n");

 }*/
                            

    unsigned int NB_NODE = graphD->nodesQuantity-1;

    printf(" NB_NODE %d \n", NB_NODE);
    int color_ju = NB_NODE; 
    pid_t pid =0;
    socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);

    int ** matrix  = graphD->matrix;
    int * nb_edges = graphD->tabNbEdges;

    int idClusterrr = 0;


/* //STUB :
   int ** matrix  = allocation_matrix(NB_NODE+1,NB_NODE+1);
    init_bitmatrix(matrix,NB_NODE+1,NB_NODE+1);
    print_matrix(matrix,NB_NODE+1,NB_NODE+1);
    int * nb_edges = cst_nbEdges(matrix ,NB_NODE+1,NB_NODE+1 );

    print_tab_int (nb_edges ,NB_NODE+1 );*/


    struct Machine * _mach = cst_Machine (0);
    struct NameNode1* _nn1 ;
    struct NameNode2* _nn2;

    struct sockaddr_in  ** scki_tab  ;
    struct sockaddr_in  **scki_tab_serv = (struct sockaddr_in  **)malloc(1*sizeof(struct sockaddr_in*));
    scki_tab=(struct sockaddr_in**) malloc(sizeof(struct sockaddr_in*)*2) ;
    for (int i =0 ; i < 2 ;i++) scki_tab[i]= (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in*)) ;
    scki_tab_serv=NULL;
    struct hash_linkInfo * tmp_infos;
    struct Link* _clserv;
    //Initialisation:
    char* mystrs ; 

    struct addrinfo hints ,* res ;
    hints = initialize_hintsTCP();

    int nb_threads_pool=0;
    int init = 1;
int n_id=0;
            int* taille_bis2 = (int*)malloc(sizeof(int)*NB_NODE+1 );
     for(int i =0 ; i< NB_NODE+1  ;i++) taille_bis2[i]=2;

    if(!(pid=fork())){
        _nn1 = cst_nameNode1(pid,_mach,fd[index_childsocket()]);
         _nn1->mach->inputs=cst_Link(NB_NODE) ; //result_input cli  et rq_input NN
        _clserv = _nn1->mach->inputs;

         _nn1->mach->outputs =cst_Link(NB_NODE) ;

         listen_sockfd = get_listenTCP(&hints,argv[2],BACKLOG); //TODO  A CHANGER : nd_node 
        scki_tab[1]=scki_memcpy (scki_tab[1],(struct sockaddr_in*)hints.ai_addr);
        link_add( _nn1->mach->outputs,&hints ,_nn1->mach->outputs->nfds,listen_sockfd ,POLLOUT);

  
        // child_process
        //close(fd[index_parentsocket()]); //POLLHUP 
        listen_sockfd = get_listenTCP(&hints,argv[1],BACKLOG); //TODO  A CHANGER : nd_node 
        nb_threads_pool=MAX_THREAD_NN_ND;
        scki_tab[0]=scki_memcpy (scki_tab[0],(struct sockaddr_in*)hints.ai_addr);

          link_add(_clserv,&hints,_clserv->nfds,listen_sockfd ,POLLIN);
          getaddrinfo(NULL, argv[4], &hints, &res); 

          printf("child : ");
         link_add(_clserv,res,_clserv->nfds,fd[index_childsocket()] ,POLLIN); // donc +1 fd_i 
         printf("%s\n",toTabCharSockaddr(scki_tab,2));


         numbytes=recv2TCP(fd[index_childsocket()],buf2,MAXBUFLEN);
         charToSockAddr(&scki_tab_serv,buf2,2);

       
    }   
    else{
         struct NetworkMetadata*_nwm= cst_networkMetadata( graphD );
         _nwm->coloration= cstdef_ColorationParam(graphSansServ);
         _nwm->cluster = base_ClusterMeta() ;

         print_tab_int (_nwm->nb_edges ,NB_NODE+1 );
         _nn2 = cst_nameNode2(pid,_mach,fd[index_parentsocket()],_nwm);

         _nn2->mach->outputs =cst_Link(NB_NODE) ;

        listen_sockfd = get_listenTCP(&hints,argv[5],BACKLOG);
        scki_tab[1]=scki_memcpy (scki_tab[1],(struct sockaddr_in*)hints.ai_addr);
        link_add( _nn2->mach->outputs,&hints ,_nn2->mach->outputs->nfds,listen_sockfd ,POLLOUT);





         _nn2->mach->inputs=cst_Link(NB_NODE+1) ; //result_input cli  et rq_input NN
         _clserv = _nn2->mach->inputs;
            close(fd[index_childsocket()]);
        listen_sockfd = get_listenTCP(&hints,argv[4],BACKLOG); //TODO  A CHANGER : nd_node 
         nb_threads_pool=MAX_THREAD_NN_ND;
        scki_tab[0]=scki_memcpy (scki_tab[0],(struct sockaddr_in*)hints.ai_addr);
        link_add(_clserv,&hints,_clserv->nfds, listen_sockfd ,POLLIN);
        mystrs = toTabCharSockaddr(scki_tab,2 );

   
       

     
        addcouple( _nn2,0,scki_tab);
        free_sckimemcpy(scki_tab[0]);
        free_sckimemcpy(scki_tab[1]);
        scki_tab[0]=scki_tab[1]=NULL;


   
        
        printf("father ");
      
      getsockname( fd[index_parentsocket()] , (struct sockaddr*)&client_addr, &tmp_addrlen);
      link_add2(_clserv,(struct sockaddr_in *)&client_addr, tmp_addrlen,_clserv->nfds,fd[index_parentsocket()] ,POLLIN);
      send2TCP(fd[index_parentsocket()],mystrs,strlen(mystrs)+1); 
        //print_hashlink(_clserv->descri);

    }



  printf("Serveur : mise en écoute sur la socket réussie \n");


 // struct ThreadPool * serv_threadPool =  cst_ThreadPool(nb_threads_pool);


struct Message  * compute_request = (struct Message*)malloc(sizeof(struct Message*));


  while (1){ 
    //printf("HI \n");
    int poll_count = poll(_clserv->pfds, _clserv->nfds, -1); //attends pour toujours une entree

        if (_clserv->nfds == -1) {
            perror("poll");
            exit(1);
        }

  for(int fd_i = 0; fd_i <= _clserv->nfds ; fd_i++) {
        if (_clserv->pfds[fd_i].revents & POLLHUP) {
            printf("POLLHUP\n");
            link_delete(_clserv, fd_i);//PROBLEME EN 250 noeud il faut free je suppose  realloc invalid old size  delete elem non existant je suppose 
        }
        else if (_clserv->pfds[fd_i].revents & POLLNVAL) {
            printf("POLLNVAL %d \n", fd_i );
            link_delete(_clserv, fd_i);
        }
        else if (_clserv->pfds[fd_i].revents & POLLERR) {
            printf("POLLERR\n");
            link_delete(_clserv, fd_i);
        }else if (_clserv->pfds[fd_i].revents & POLLIN) {
                if (_clserv->pfds[fd_i].fd == listen_sockfd) { //fd_i ==0 ? 

                     if(pasla)printf("Demande de connexion : \n");

                        if(pid==0){
                         if(pasla)printf("S1\n");
                          if(_clserv->nfds-2 == NB_NODE  ){ // il y a assez de noeud 
                                new_fd = p_accept(listen_sockfd ,(struct sockaddr *)&client_addr,&tmp_addrlen) ;

                          close(new_fd);
                        }
                        else if ( _clserv->nfds-2 < NB_NODE ) { // il manque un noeud 
                             if ((new_fd = p_accept(listen_sockfd ,(struct sockaddr *)&client_addr,&tmp_addrlen)) ==-1){
                              perror("accept_error");
                              
                            } else {
                            link_add2(_clserv,(struct sockaddr_in *)&client_addr,tmp_addrlen,_clserv->nfds, new_fd,POLLIN); //PROBLEME EN 250 noeud il faut free je suppose  realloc invalid old size 
                            if(pasla)printf("S1 Serveur : connection du Node sur la socket %d | %d\n",new_fd,_clserv->nfds);

                            }
                        }
                        else{ // plus de sortie vers des noeuds que de noeuds 
                            
                            return failureProcedure();
                        }

                    }else if(pid!=0 ){ 
                        if(pasla)printf("S2\n");
                             // si je suis nameNode et je recois demande 
                            //checkInSockaddrinTab
                            //si oui alors accept
                            //sinon close 
                     
                            if ((new_fd = p_accept(listen_sockfd ,(struct sockaddr *)&client_addr,&tmp_addrlen)) ==-1){
                                  perror("accept_error");
                                } else  {
                                    //recv(new_fd,&str_client_addr3,...);s                  // !!! EN HAUT !!!
                                    //sockaddr_in  client_addr3=convert(str_client_addr3);
                                    //if( checkInSockaddrinTab (_nn2 ,0,&client_addr3)){ //si case pas vide dans addresses 
                                    //id_atm= findbyvalue(client_addr3);
                                if(pasla)printf("S2 connexion de la socket : %d  id %d\n",new_fd, _clserv->nfds); // _clserv->nfds => id_recv 
                                //print_hashlink(_clserv->descri);  //DUMP ICI 
                                //link_addorReplace(_clserv,(struct sockaddr_in *)&client_addr3,tmp_addrlen,id_atm, new_fd,POLLIN);
                                getsockname( new_fd , (struct sockaddr*)&client_addr, &tmp_addrlen);
                                 getpeername( new_fd , (struct sockaddr*)&client_addr, &tmp_addrlen);
                                link_add2(_clserv,(struct sockaddr_in *)&client_addr,tmp_addrlen,_clserv->nfds, new_fd,POLLIN); // tmp_addrlen,_clserv->nfds, new_fd,POLLIN => tmp_addrlen,id_recv, new_fd,POLLIN 
                                //print_hashlink(_clserv->descri);   
                      
                                if(init==0){
                                     //P1 : p_send(new_fd,"ok",3,0);
                                    if(debug_Serv)printf("S2 La connexion du noeud a été rétabli avec succés  \n\n");
                                    int ne=recv2TCP(new_fd,buf2, MAXBUFLEN); // a mettre EN HAUT 
                                    buf2[ne]='\0';
                                    printf("On a recu l'id du noeud  nouvellement connecté : %s \n",buf2);
                                    n_id=atoi(buf2);
                                    //printf("NEIGH %p et nid %d \n",_nn2->metas->neightbors[n_id],n_id);
                                    mystrs = strsockaddrTabtabtab2(_nn2->metas->neightbors[n_id],_nn2->metas->nb_edges[n_id],taille_bis2);
                                    
                                     printf("On envoie au noeud  %d (représenté par la socket : %d ) sa liste de connexion  : TAILLE %d  %s \n",n_id,strlen(mystrs),new_fd, mystrs);
                                    
                                    send2TCP(new_fd,mystrs,strlen(mystrs)+1);
                                    //send2TCP(_clserv->pfds[fd_i].fd,"ok",3);//ca marchera pas s'il manque plusieurs noeuds

                                }
                           // } else{ //non autoriser
                            //printf("Serveur :\n");
                             //new_fd = p_accept(listen_sockfd ,(struct sockaddr *)&client_addr,&tmp_addrlen);
                            //close(new_fd);
                            //C STYLE WAOW !

                       // }
                            }
                        }  

                }//si pas demande de co  mais recois donné 
                else {
                    if(pasla)printf("Je recois quelque chose sur la socket : %d \n",_clserv->pfds[fd_i].fd);
                    // Recois donnée 
                      if ((numbytes = recv2TCP(_clserv->pfds[fd_i].fd, buf2, MAXBUFLEN)) <= 0) { //si recv fail
                        // erreur ou fermeture connexion par client 
                        if (numbytes == 0) {
                            printf("Serveur : Canal communication  %d  fermé  (socket %d) \n", fd_i,_clserv->pfds[fd_i].fd);
                        } else {
                            perror("recv2_error");
                        }
                        getpeername( new_fd , (struct sockaddr*)&client_addr, &tmp_addrlen);
                        if(pasla)printf("J'ai recu une \"déconexion\" sur la socket  : %d  (addr %s )  \n",_clserv->pfds[fd_i].fd,toCharSockaddr((struct sockaddr_in*)&client_addr));
                        close(_clserv->pfds[fd_i].fd);
                        link_delete(_clserv, fd_i);
                         if(pasla) {
                            if(pid==0){printf("S1 Update hashlink suite à la deletion du socket deconnecté : ");}
                        else  {printf("S2 Update hashlink suite à la deletion du socket deconnecté %d : ",_clserv->pfds[fd_i].fd);}
                    }

                        //print_hashlink(_clserv->descri); 
                       
                        }//si recv fail pas et que dans 0 
                        else if(pid==0){
                                buf2[numbytes]='\0';
                                printf("S1 J'ai recu le message %s sur la socket %d  \n",buf2,_clserv->pfds[fd_i].fd);
                            if(_clserv->pfds[fd_i].fd==fd[index_childsocket()]){ //child 
                                 printf("S1 Le clientHandler m'a envoyé le message : %s \n",buf2);
                                    // j'ai perdu un noeud pas trop nessaire car deja in_node  dans pid==0
                                //ct pour strategie recois result sur socket pipe 
                            }
                            else if(_clserv->nfds-2 > NB_NODE  ){
                                 printf("S1 ERREUR : Il y a plus de noeud que de noeud permis !\n");
                            }
                            else if (_clserv->nfds-2 <= NB_NODE ){// il manque un noeud    !!! EN BAS !!!
                             // je crois que ce n'est pas neccesaire car p_recv est appelé imperativement apres une demande de connexion donc l'accept recv suffit 
                                 printf("S1 Le noeud manquant m'a envoyé  ses addresses in et out  \n");
                                 charToSockAddr(&scki_tab,buf2 , 2 );
                                if(pasla)printf("icicicci %s \n",toTabCharSockaddr(scki_tab,2));

                                //link_add( _nn1->mach->outputs,&scki_tab[1] ,_nn1->mach->outputs->nfds,listen_sockfd ,POLLOUT);
                                mystrs=toTabCharSockaddr(scki_tab,2 );
                                char short_buff[15] ;
                                sprintf(short_buff, "%d", fd_i-1);
                                mystrs=fusionstr(mystrs,short_buff,':');

                                printf("S1 j'envoie au NodeHandler l'addresse in et out du noeud Manquant et son id %s \n ", mystrs);
                               send2TCP(fd[index_childsocket()],mystrs,strlen(mystrs)+1);
                                getpeername( fd[index_childsocket()], (struct sockaddr*)&client_addr,&tmp_addrlen);
                                mystrs=toTabCharSockaddr(scki_tab_serv,2);
                                mystrs=fusionstr(mystrs,short_buff,':');
                                 
                                printf("S1 J'envoie au noeud manquant l'addresse du NodeHandler et son idReseau %s  \n",mystrs); //idReseau est le numero de la socket dans le poll // RIP poll : si bcp de noeud 
                                send2TCP(_clserv->pfds[fd_i].fd,mystrs,strlen(mystrs)+1);



                            }
                        

                        }//si recv fail pas et que dans 1
                    else if (pid!=0){
                        buf2[numbytes]='\0';
                         printf("S2 J'ai recu le message %s sur la socket %d  \n",buf2,_clserv->pfds[fd_i].fd);
                        
                        if(!init  && _nn2->metas->debug_taille-1 >= NB_NODE  ) { // je recois un ASK node
                         printf("S2 Je recois une demande d'information de la part d'un Noeud \n");
                        if(fd_i==1){
                                 printf("S2 Je recois un message urgent du clientHandler \n");
                            
                        }
                        char* save_ptr;//Code  , *save_ptrCluster , *save_ptrContent ;
                        char*  strTokenCode , *strTokenCluster , *strTokenContent;
                        //save_ptrCode  = save_ptrCluster = save_ptrContent=NULL;
                        if(debug_Serv)printf("BUF2 %s \n",buf2);
                        strTokenCode = strtok_r(buf2,messageDelim2(),&save_ptr);
                        if(debug_Serv)printf("TOKENCode  %s\n",strTokenCode);
                        //strToken =strtok(NULL,":\n");
                        int n_id2=atoi(strTokenCode);
                        char delimContent = '\n';

                        strTokenCluster =strtok_r(NULL,idClusterDelim2(),&save_ptr);
                        if(debug_Serv)printf("TOKENCluster %s \n",strTokenCluster);
                        idClusterrr = strToInt (strTokenCluster);//(strcmp(strTokenCluster," ")!=0?strToInt (strTokenCluster):-1);
                        if(n_id2==7){
                            char * fino = (char*)malloc(4*sizeof(char));
                            fino[0]='f';fino[1]='i';fino[2]='n';fino[3]='\0';
                            strTokenContent =strtok_r(NULL,&delimContent,&save_ptr);
                            if(debug_Serv)printf("TOKENContent  %s \n",strTokenContent);
                            idClusterrr--;
                            //idClusterrr == uid du node //flemme faire 2 var
                            //cluster->cluster2DdjMat[i],cluster->cluster2DTaille[0][i]
                            idClusterrr = _nn2->metas->cluster->cluster1D[idClusterrr];
                            //char* AdjMatClust = idClusterAdjMat (_nn2->metas->cluster->cluster2DdjMat[idClusterrr] ,_nn2->metas->cluster->cluster2DTaille[0][idClusterrr] ,tabTabDelims() ,  idClusterrr , 0 ); //pour Adj par ex
                            //printf("node %d idCluster %d \n  MatAdj : %s \n\n ",fd_i,_nn2->metas->cluster->cluster1D[fd_i],AdjMatClust );
                            struct GraphData* tmp_graph4 = graphDataCpyFromAdj ( _nn2->metas->cluster->cluster2DdjMat[idClusterrr] ,_nn2->metas->cluster->cluster2DTaille[0][idClusterrr]);
                            color_ju = NB_NODE; 
                            
                            struct ColorationParam  * colorParam4 =cstdef_ColorationParam(tmp_graph4  ); // cst_ColorationParam2(tmp_graph4 ,color_ju ,NULL, NULL );
                            colorParam4->timeout = CLIENT_TIMEOUT  ; 
                            char* colorParam4Str = colorParamToStr(colorParam4) ;
                            freeColorParam(colorParam4);
                            char* tmp_coloParam4 =idClusterStr  ( colorParam4Str , idClusterrr   );
                            if(debug_Serv)printf("Color_Param str %s ( %s || %d ) \n",tmp_coloParam4 ,colorParam4Str,idClusterrr);
                           getsockname(  _clserv->pfds[fd_i].fd , (struct sockaddr*)&client_addr, &tmp_addrlen);
                    

                            numbytes=send2TCP(_clserv->pfds[fd_i].fd,tmp_coloParam4,strlen(tmp_coloParam4)+1);
                            printf("S2 J'envoie au noeud  (%d |  %s )  le message  (Taille : %d vs numbytes : %d  )  %s \n ",idClusterrr,toCharSockaddr(&client_addr),strlen(tmp_coloParam4),numbytes,tmp_coloParam4);
                            free(fino);
            
                            if(times==0){
                                times=startTimer();
                            }

                             CLcounter++;
                            //printf("%d 777\n\n ", CLcounter);

                        }
                        else if(n_id2==8 && !barrier(times)){
                             delimContent=colorResultDelim();
                            CLcounter--;

                             strTokenContent =strtok_r(NULL,&delimContent,&save_ptr);
                             color_ju = strToInt (strTokenContent);
                            if(debug_Serv)printf("Color_cnt  %s (%d) \n",strTokenContent , color_ju  );
                             strTokenContent =strtok_r(NULL,&delimContent,&save_ptr);
                             int conflict = strToInt (strTokenContent);
                            if(debug_Serv)printf("Conflict_cnt  %s (%d) \n",strTokenContent , conflict );
                             strTokenContent =strtok_r(NULL,&delimContent,&save_ptr);
                             int* coloringTAB = strToTab(strTokenContent,tabDelim());
                             if(debug_Serv)printf("TAB COLORING de %d cluster : \n TAILLE %d   \n",idClusterrr,_nn2->metas->cluster->cluster2DTaille[0][idClusterrr]);
                             if(debug_Serv)print_tab_int(coloringTAB,_nn2->metas->cluster->cluster2DTaille[0][idClusterrr]);
                             struct ColorationResult * CR = cst_colorResult(coloringTAB , color_ju ,_nn2->metas->cluster->cluster2DTaille[0][idClusterrr] ,conflict);
                             //printf("COLOR RESULT %s \n ",CRToStr(CR));
                             if(conflict==0)updateBestColor( _nn2->metas->coloration, CR , _nn2->metas->cluster->cluster2DTrad[idClusterrr]  );
                             if(times2==0 && times>0 ){
                                if(debug_Serv)printf("\n BAR1 \n");
                                times2=startTimer();
                            }
                            //printf("%d 888\n\n ", CLcounter);

                             /*
                             int taille111;
                             taille111=0;
                             int* color=toTabInt(&taille111,strToken);
                             assert(taille222==taille111);
                             atm_color=accColor(atm_color,color,trad,taille222);*/



                        }else if (n_id2==9 ){
                            //printf("%d 9999\n\n ", CLcounter);
                            if(  CLcounter<=1 || barrier2(times2)){ //times2>0 &&
                                if(debug_Serv)printf("\n BAR2 \n");
                                if( _nn2->metas->CRF ==NULL){
                                    _nn2->metas->CRF= (struct ColorationResult*)malloc(sizeof(struct ColorationResult)*1);
                                    _nn2->metas->coloration->timeout=SERVEUR_TIMEOUT ;
                                    _nn2->metas->CRF =launchColorFinal(_nn2->metas->CRF,_nn2->metas) ;
                                    CLcounter=0;
                                    
                                }
                                
                                idClusterrr--;
                                //for(int  iz = 2; iz<_clserv->nfds; iz++ ){
                                    getsockname( _clserv->pfds[fd_i].fd ,  (struct sockaddr*)&client_addr,&tmp_addrlen );             
                                    /*char * CRFStr = CRToStr(_nn2->metas->CRF);
                                    printf("S2  j 'ai envoye le message %s  à uid reseau : %d  addresse :  %s  \n ",CRFStr,idClusterrr,toCharSockaddr((struct sockaddr_in*)&client_addr));
                                    send2TCP(_clserv->pfds[fd_i].fd,CRFStr,strlen(CRFStr)+1);*/
                                    if(debug_Serv)printf("%d icClustter %p NB  \n",idClusterrr,_nn2->metas->CRF->coloring);
                                    int dcouleur=_nn2->metas->CRF->coloring[idClusterrr];
                                    //char* couleurrr = intToChar(dcouleur);
                                    //printf("S2  j 'ai envoye le message %s  à uid reseau : %d (fd_i - 1 ) addresse :  %s  \n ",dcouleur,idClusterrr,toCharSockaddr((struct sockaddr_in*)&client_addr));
                                    //send2TCP(_clserv->pfds[fd_i].fd,couleurrr,strlen(couleurrr)+1);
                                    if(debug_Serv)printf("dcouleur %d \n",dcouleur);
                                    numbytes=send(_clserv->pfds[fd_i].fd,&dcouleur,sizeof(int),0);
                                     if(debug_Serv)printf("S2 J'envoie au noeud  (%d |  %s )  le message  (Taille : %d vs numbytes : %d  )  %d \n ",idClusterrr,toCharSockaddr(&client_addr),sizeof(int),numbytes,dcouleur);
                           

                                //}
                                
                            
                        }else{

                            }
                        }

                            //RESULT RECU 
                            //buf2[numbytes]='\0';
                            //strcpy(compute_request.str_operation,buf2);
                            //compute_request.idRequest=incr_idRq++;  
                            //printf("Serveur :%s et numbtyes:%d ; \n id_request : %d \n",compute_request.str_operation,numbytes,compute_request.idRequest);
                                                       
                            //struct ThreadTask compute_tt = cst_ThreadTask(&handler_computeRequest, &compute_request);
                            //serv_threadPool->add_tasksToPool(serv_threadPool,  &compute_tt);

                        }
                        else if (_nn2->metas->debug_taille-1 <= NB_NODE )  {// je recois info de co 
                             printf("S2 Je recois les addresses in et out d'un noeud voulant se connecté socket : %d  \n S2 nb_noeud atm : %d , nb_noeud voulu : %d\n",fd_i, _nn2->metas->debug_taille-1 , NB_NODE);
                            if(_clserv->pfds[fd_i].fd==fd[index_parentsocket()]){//parent fd
                                printf("S2 c'est le clientHandler qui m'a envoyé ces addresses \n");
                                //_nameNode->metas.add_inout(fd_i,tab_skci );
                                char* sep =":\n";
         
                                char * strToken = strtok(buf2,":\n");
                                if(debug_Serv)printf("S2 Addresse in et out %s\n",strToken );
                                charToSockAddr(&scki_tab,strToken, 2);

                                strToken =strtok(NULL,":\n");
                                  n_id=atoi(strToken);
                               
                                //printf("str %s id %d \n",toTabCharSockaddr(scki_tab,2),n_id);
                                //new_fd =  get_clientTCP(&hints ,argv[4] ,NULL );
                                //link_add2(_clserv,scki_tab[0],tmp_addrlen,_clserv->nfds, new_fd,POLLIN);
                                //new_fd =  get_clientTCP(&hints ,argv[5] ,NULL );
                                //link_add2(_clserv,scki_tab[1],tmp_addrlen,_clserv->nfds, new_fd,POLLIN);
                                
                                    printf("S2 j'ajoute l'addresse in et out du noeud %d à mon repetoir d'addresse \n",n_id);
                                   addcouple( _nn2,n_id,scki_tab);
                                   free_sckimemcpy(scki_tab[0]);
                                   free_sckimemcpy(scki_tab[1]);
                                
                                    if( init  && _nn2->metas->debug_taille-1 == NB_NODE){

                                   
                                        /*
                                        struct ThreadTask compute_tt = cst_ThreadTask(&handlerMessage, compute_request);
                                        serv_threadPool->add_tasksToPool(serv_threadPool,  &compute_tt);
                                        */    

                                        extractNeighbours(_nn2);
                                 
                                        init = 0 ;
                                        for(int  iz = 2; iz<_clserv->nfds; iz++){
                                                struct sockaddr_in cl_addr8;
                                                getpeername( _clserv->pfds[iz].fd , (struct sockaddr*)&cl_addr8,&tmp_addrlen);
                                                 in_port_t  port3 =ntohs(get_in_port((struct sockaddr *)&cl_addr8)) ; 
                                                    char ip_addr3[INET6_ADDRSTRLEN];
                                                     inet_ntop(cl_addr8.sin_family,get_in_addr((struct sockaddr *)&cl_addr8 ),ip_addr3,INET6_ADDRSTRLEN);
                                                     printf("S2 Le Noeud connecté sur le port : %d et la socket :%d  attends de recevoir sa liste de connexion \n",port3,_clserv->pfds[iz].fd);
                                                    
                                                //struct sockaddr_in cl_addr9;
                                                //getsockname( _clserv->pfds[iz].fd , (struct sockaddr*)&cl_addr9,&tmp_addrlen);
                                                  // port3 =ntohs(get_in_port((struct sockaddr *)&cl_addr9)) ; 
                                                  
                                                    // inet_ntop(cl_addr9.sin_family,get_in_addr((struct sockaddr *)&cl_addr9 ),ip_addr3,INET6_ADDRSTRLEN);
                                                     //printf("S2 je suis sur le port  : %d  \n",port3);

                                                     
                                             //P1 : send2TCP(_clserv->pfds[iz].fd,"ok",3);
                                            recv2TCP(_clserv->pfds[iz].fd,buf2, MAXBUFLEN);
                                            //printf("n_ids %s \n",buf2);
                                            n_id=atoi(buf2);
                                            printf("S2 Le noeud qui attends sur la socket %d m'a envoyé son idReseau %d \n",_clserv->pfds[iz].fd,n_id);

                                               
                                            mystrs = strsockaddrTabtabtab2(_nn2->metas->neightbors[n_id],_nn2->metas->nb_edges[n_id],taille_bis2);
                                            printf("S2 j'envoie au noeud d'id %d  sa liste de connexion : %s \n",n_id,mystrs);
                                            getsockname( _clserv->pfds[iz].fd , (struct sockaddr*)&client_addr,&tmp_addrlen);
                                            printf("S2 J'envoie au noeud  (%d |  %s )  le message  (Taille : %d vs numbytes :%d ) %s   \n ",n_id,toCharSockaddr(&client_addr),strlen(mystrs)+1,numbytes,mystrs);
                           

                                            send2TCP(_clserv->pfds[iz].fd,mystrs,strlen(mystrs)+1);

                                             /*sockfd3[i]= get_clientTCP(&hints_out , port , ip_addr );
                 
                                            link_add(outputs,&hints_out,outputs->nfds,sockfd3[i] ,POLLOUT);*/


                                            //P1 :  recv2TCP(_clserv->pfds[iz].fd,buf2, MAXBUFLEN); //attends ok client 
                                        }
                                        
                                        //P1 : for(int  iz = 2; iz<_clserv->nfds; iz++)send2TCP(_clserv->pfds[iz].fd,"ok",3);

                                        compute_request->hd=_CLUSTERING;
                                        compute_request->content=cstdef_ClusteringParam( graphSansServ );
                                        

                                        initClusterMeta ( compute_request->content ,  _nn2->metas->cluster );
                              
                                        //while(cond)
                                        //ELECTION 

                                        //ENVOIE avec SENDTCP au chef des clusters leur liste d'adjancence calculer par adjCluster ( aDebug.c) 

                                        //ATTENDS LA reponse "ok" des chefs des clusters (avancer: si toutes les reponses ne sont pas percu au bout d'un temps x alors refaire election => horloge message client )
                                        //forall (c : chefs) recv  if(all_message recv before x )cond=true 

                                        //end while 
                                        // 
                                        //FIN P1

                                        }
                                    else{
                                            
                                        if(debug_Serv)printf("\n UPDATE ExtractedNeighbors but not autorized for now ! \n");
                                        //just updateExtractedNeighbors but not autorized for now
                                    }

      
                                    //sendfrom(extractNeighbors) //pour tous les noeuds qui en ont besoins 
                                    //le nameNode envoie la liste si pour l'id considéré l'ensembles des in et out sont renseignés 
                                    //les noeuds attendent une liste de connexion in et out
                                    // la liste n'est liste que pour le noeuds entrant pour les autres c'est souvent le in et out du noeud entrant 
                            }//etait parent fd
                            //!= partent fd 
                            else{
                                if(debug_Serv)printf("\n != parent  \n");


                            }
                            
     

                        }//etait une demande de co 
                        //si != info CO 
                        else{
                            if(debug_Serv)printf("\n != info CO  \n");
                        }

                    }//etait dans pid 1 
                    // appartient à aucun pid 
                   
                  
                }// si ct un recv 
                // si ct pas un recv ni une co 
               
            }//POLLIN
                 
            //printf("boucle  pfds pour iteration \n"); 
        }//for
        //printf("while iteration  \n");
 
    }//while
    


   printf("Serveur : Canal d'écoute  %d fermé  \n", listen_sockfd);

    listen_sockfd=-1;


    memset(&hints, 0, sizeof hints);

    //free pfds 
    //free threadPool 



   return 0;
}


