
/**
 * fichier: client.c
 * auteur: Rambal Julien
**/




#include "clientTropPool.h"



    struct tabScki * cst_tabScki ( struct sockaddr_in** _tabAddr , size_t _taille){
        struct tabScki * _tabScki = (struct tabScki*)malloc( sizeof(struct tabScki));
        _tabScki->tab_addr=_tabAddr;
        _tabScki->taille_tab=_taille;
        return _tabScki;

    }

    struct tabScki * cst_cpy_tabScki( struct sockaddr_in** _tabAddr , size_t _taille){
        struct tabScki * _tabScki = (struct tabScki*)malloc( sizeof(struct tabScki));
        _tabScki->tab_addr=(struct sockaddr_in**)malloc(sizeof(struct sockaddr_in *)*_taille);
        size_t * i = &_tabScki->taille_tab;
        for((*i)=0;(*i)<_taille;(*i)++){
                _tabScki->tab_addr[(*i)]= (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in*)) ;
                _tabScki->tab_addr[(*i)]=scki_memcpy(_tabScki->tab_addr[(*i)],_tabAddr[(*i)]);

        }
        if(DEBUG_CLI)printf("sckicpy  taille %d  %d \n ",(*i),_tabScki->taille_tab);
        return _tabScki;

    }


    int index_parentsocket(){return 0; }
    int index_childsocket(){return 1; }



  int ClientTropPool(char* port_serveur,char* ip_serveur ,char* _inport,char* _outport) 
  {   
       
           
         /* if (argc != 5) {
              printf("Utilisation : %s port_serveur  ip_serveur in_port_client out_port_client  \n", argv[0]);
              exit(1); 
          }*/
          

          int sockfd;     
           int numbytes;
           char* save_ptr;
          char* buf = (char*) malloc( MAXBUFLEN); 
              char* buf2 = (char*) malloc( MAXBUFLEN);

            char * oko = (char*)malloc(3*sizeof(char));
            oko[0]='o';oko[1]='k';oko[2]='\0';

            char * fino = (char*)malloc(4*sizeof(char));
            fino[0]='f';fino[1]='i';fino[2]='n';fino[3]='\0';

       /*   char* port_serveur =argv[1];
          char* ip_serveur = argv[2];
          char* in_port = argv[3];
           char* out_port = argv[4];*/
    struct addrinfo hints ,hints_in,hints_out ;
    struct sockaddr_in ** scki_tab  =(struct sockaddr_in**) malloc(sizeof(struct sockaddr_in*)*2) ;
    for (int i =0 ; i < 2 ;i++) scki_tab[i]= (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in*)) ;

         memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

         memset(&hints_in, 0, sizeof hints_in);
        hints_in.ai_family = AF_INET;//(_inport!=NULL?AF_INET:AI_PASSIVE);
        hints_in.ai_socktype = SOCK_STREAM;
      
        memset(&hints_out, 0, sizeof hints_out);
        hints_out.ai_family = AF_INET ;//(_outport!=NULL?AF_INET:AI_PASSIVE);
        hints_out.ai_socktype = SOCK_STREAM;
          
    /*
        struct ifaddrs * ifap;
        getifaddrs (&ifap);
        char * ipaddr_ =  inet_ntoa(((struct sockaddr_in *) ifap->ifa_addr)->sin_addr);
        printf("Client:%s\n",ipaddr_);*/

        struct ifaddrs *ifap, *ifa;
        struct sockaddr_in *sa;
        char *addr;
        int sz_addrlen =sizeof(struct sockaddr_in);
        getifaddrs (&ifap);
        for (ifa = ifap;   ifa; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) {
                sa = (struct sockaddr_in *) ifa->ifa_addr;
                addr = inet_ntoa(sa->sin_addr);
                if(strcmp(ifa->ifa_name,"lo") )break;
            }
        }
        if(pasPourLinstant ) printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);

     
         int listen_sockfdi = get_listenTCP2(&hints_in,_inport,addr,BACKLOG); //TODO  A CHANGER : nd_node 

         getsockname(listen_sockfdi,(struct sockaddr *)sa,&sz_addrlen);
         char* in_port = (char*)malloc(7);
        sprintf(in_port,"%d",ntohs((short)sa->sin_port));
        if(pasici)printf("Client: Creation de la socket %d d'écoute d'INPUT | port %s et d'addresse %s \n",listen_sockfdi,in_port,ip_serveur);
      
        print_addrinfo(&hints_in);
         scki_tab[0]=scki_memcpy (scki_tab[0],sa);

         scki_tab[0]->sin_family=hints_in.ai_family;
         //printf("%s | %s \n", toCharSockaddr((struct sockaddr_in*)hints_in.ai_addr),toCharSockaddr(scki_tab[0]));
         int listen_sockfdo = get_listenTCP2(&hints_out,_outport,addr,BACKLOG); //TODO  A CHANGER : nd_node 

         getsockname(listen_sockfdo,(struct sockaddr *)sa,&sz_addrlen);
         char* out_port = (char*)malloc(7);
         sprintf(out_port,"%d",ntohs((short)sa->sin_port));

        if(pasici)printf("Client: Creation de la socket %d d'écoute d'OUTPUT | port %s et d'addresse %s \n",listen_sockfdo,out_port,ip_serveur);
      

         scki_tab[1]=scki_memcpy (scki_tab[1],sa);
    print_addrinfo(&hints_out);

    //sleep(10); 
    //POLLHUP ICI  DANS SERV 
        sockfd= get_clientTCP(&hints , port_serveur , ip_serveur );
        if(pasPourLinstant ) printf("Client : Connection via la socket %d sur le ClientHandler de port %s et d'addresse %s \n",sockfd,port_serveur,ip_serveur);
    //sleep(10);  
        //printf("ici0 %s %s\n",sockaddrtoStr2 (scki_tab[0]));
        //printf("ici %s\n",sockaddrtoStr2(scki_tab[1]));
         buf = toTabCharSockaddr(scki_tab,2 ); 
         if(pasPourLinstant ) printf("J'envoie mon addresse d'input et d'output :  %s sz %d  au ClientHandler %s %s \n",buf,strlen(buf),port_serveur , ip_serveur);
         numbytes=send2TCP(sockfd,buf,strlen(buf)+1);//<=> sendto avec NULL x2 



        free_sckimemcpy(scki_tab[0]);
        free_sckimemcpy(scki_tab[1]);
      


        numbytes=recv2TCP(sockfd,buf2,MAXBUFLEN);
        if(pasPourLinstant ) printf("%d numbytes \n ",numbytes);
if(numbytes>0){

            buf2[numbytes]='\0';
            if(pasPourLinstant )printf("Je recois un message du ClientHandler %s %s   \n ce message est : %s \n",port_serveur,ip_serveur,buf2);

            char* sep =":\n";
            char * strToken = strtok_r(buf2,sep,&save_ptr);
            if(pasPourLinstant ) printf("L'addresse du NodeHandler %s m'a été envoyé sur la socket %d \n",strToken,sockfd);
            struct sockaddr_in** tab_sockaddr = (struct sockaddr_in**)malloc(1*sizeof(struct sockaddr_in*));
            charToSockAddr(&tab_sockaddr , strToken , 1 );
            strToken =strtok_r(NULL,sep,&save_ptr);

            int n_id = atoi(strToken); 

            char ip_addr [INET6_ADDRSTRLEN];
            inet_ntop( tab_sockaddr[0]->sin_family,get_in_addr((struct sockaddr *) tab_sockaddr[0] ),ip_addr,INET6_ADDRSTRLEN);
            char  port [7] ;
            hints.ai_family = tab_sockaddr[0]->sin_family;
            hints.ai_socktype = SOCK_STREAM;

        //sleep(10);
            sprintf(port,"%d", ntohs(get_in_port((struct sockaddr *)tab_sockaddr[0] )));
            int sockfd2= get_clientTCP(&hints , port , ip_addr ); // je pense qu'il faut conserver cette socket : socket vers NodeHandler et la stocker dans la structure du wokers 

             struct sockaddr_in client_addr4 ;
              int addr_size = sizeof(struct sockaddr);
             getsockname(  sockfd2 , (struct sockaddr*)&client_addr4, &addr_size);
            //if(pasPourLinstant )
             if(pasici)printf("Je me connecte au NodeHandler %s %s  sur la socket %d (addr %s ) \n",port,ip_addr,sockfd2,toCharSockaddr(&client_addr4));

          //my_pause ("client " , "Connect au NodeHandler ","Send id "  );
        sleep(10);

            struct sockaddr_in cl_addr,cl_addr2;
           
            getsockname(  sockfd2 , (struct sockaddr*)&cl_addr, &addr_size);
            getpeername(  sockfd2 , (struct sockaddr*)&cl_addr2, &addr_size);

                 in_port_t  port3 , port2;
                 char ip_addr3[INET6_ADDRSTRLEN];
                  char ip_addr2[INET6_ADDRSTRLEN];

             //P1 : char ok [10];
             //P1 : numbytes=recv2TCP(sockfd2,ok,MAXBUFLEN); //syncrho a modifier 



            strcpy(buf,strToken);
            buf[strlen(strToken)+1]='\0';
             printf("\n\n \n J'envoie  sur la socket %d au NodeHandler : %s  %s \n le message : %s sz %d qui correspond a mon idReseau  \n",sockfd2,port,ip_addr,strToken,strlen(strToken));
            numbytes=send2TCP(sockfd2,buf,strlen(buf)+1);


            strcpy(buf,"\0");
            numbytes=recv2TCP2(sockfd2,(void**)&buf,MAXBUFLEN);
            printf("numbytes %d \n",numbytes);
            buf[numbytes]='\0';
            //printf("\n\n \n J'ai recu (NoeudReseau %d ) ma liste de connexion In/Out : %s \n sur la socket %d correspondant au NodeHandler %s %s \n",n_id,buf,sockfd2,port,ip_addr);
            //my_pause ("client " , "J'ai recu ma liste de connexion ","Ecoute et connexion "  );
            // char* ici = (char*)malloc(1);
        //sleep(10);

            struct sockaddr_in **tmp_tab=(struct sockaddr_in**) malloc(1*sizeof(struct sockaddr_in*));
             struct sockaddr_in *** tab_i1 =(struct sockaddr_in***) malloc(1*sizeof(struct sockaddr_in**));
              struct sockaddr_in *** tab_o1 =(struct sockaddr_in***) malloc(1*sizeof(struct sockaddr_in**));
              struct sockaddr_in ** buffhhh =NULL;

            *tab_i1 =(struct sockaddr_in**) malloc(1*sizeof(struct sockaddr_in*));
            *tab_o1 =(struct sockaddr_in**) malloc(1*sizeof(struct sockaddr_in*));

                sep ="|\n";

                strToken = strtok_r ( buf, sep,&save_ptr);

                int size_tab = 1;
                int zi=0;
                for ( ;strToken != NULL;zi++ ) {
                //printf ( "LARZAC : %s\n", strToken );
                if(size_tab<=zi){
                size_tab*=2;
                size_tab++;
                buffhhh =(struct sockaddr_in**) malloc(size_tab*sizeof(struct sockaddr_in*));
                for(int kiuo =0 ; kiuo <zi ;kiuo++){
                    buffhhh[kiuo]=(struct sockaddr_in*)malloc(1*sizeof(struct sockaddr_in*));
                    scki_memcpy2 (&(buffhhh[kiuo]),(*tab_i1)[kiuo]);
                    //printf("ZI 7777777777777 %d  TAB_I %s FAM %s  TAB_O %s FAM %s \n\n",zi,toCharSockaddr(buffhhh[kiuo]),familyToStr (buffhhh[kiuo]->sin_family),toCharSockaddr((*tab_i1)[kiuo]),familyToStr ((*tab_i1)[kiuo]->sin_family));
         
                }
                free( *tab_i1);

                *tab_i1= buffhhh ;

                 buffhhh =(struct sockaddr_in**) malloc(size_tab*sizeof(struct sockaddr_in*));
                for(int kiuo =0 ; kiuo <zi ;kiuo++){
                    buffhhh[kiuo]=(struct sockaddr_in*)malloc(1*sizeof(struct sockaddr_in*));
                    scki_memcpy2 (&(buffhhh[kiuo]),(*tab_o1)[kiuo]);
                    //printf("ZI 88888888888 %d   TAB_I %s FAM %s  TAB_O %s FAM %s \n\n",zi,toCharSockaddr(buffhhh[kiuo]),familyToStr (buffhhh[kiuo]->sin_family),toCharSockaddr((*tab_o1)[kiuo]),familyToStr ((*tab_o1)[kiuo]->sin_family));
         
                }
                free( *tab_o1);

                *tab_o1= buffhhh ;
                }
                //printf("\n\n %d vs %d TMP %s \n\n",size_tab,zi,strToken);
                charToSockAddr(&tmp_tab,strToken , 2 );
                //printf("DO %s \n",toCharSockaddr(tmp_tab[0]));
                //printf("DI %s \n",toCharSockaddr(tmp_tab[1]));
                (*tab_i1)[zi]=(struct sockaddr_in*) malloc(1*sizeof(struct sockaddr_in));
                (*tab_o1)[zi]=(struct sockaddr_in*) malloc(1*sizeof(struct sockaddr_in));
                scki_cpy ((*tab_i1)[zi],tmp_tab[0]);//TODO deep cpy 
                scki_cpy ((*tab_o1)[zi],tmp_tab[1]);
                //printf("DOOOO %s \n",toCharSockaddr((*tab_i1)[zi]));
                //printf("DIIII %s \n",toCharSockaddr((*tab_o1)[zi]));
                //for(int iy =0; iy <zi ;iy++ ) printf("\n\n TAB_I %s \n TAB_O %s \n\n",toCharSockaddr((*tab_i1)[iy]),toCharSockaddr((*tab_o1)[iy]));
                //printf("\n\n %d vs %d TAB_I %s \n\n",size_tab,zi,toTabCharSockaddr4(  tab_i1 , zi+1 ));
                //for(int iy =0; iy <=zi ;iy++ )printf("ZI %d \n  TAB_I %s FAM %s \n TAB_O %s FAM %s \n\n",zi,toCharSockaddr((*tab_i1)[iy]),familyToStr ((*tab_i1)[iy]->sin_family),toCharSockaddr((*tab_o1)[iy]),familyToStr ((*tab_o1)[iy]->sin_family));
                //printf("Tb %p %p  \n ", (*tab_o1)[zi],(*tab_i1)[zi]);


                strToken = strtok_r ( NULL, sep,&save_ptr);
            }
                
            //assert(zi<size_tab)//ICI REGLER PB TABSOCK
        //if(pasPourLinstant ) 
        //printf("\n\n (NoeudReseau %d ) TAB_I %s \n\n",n_id,toTabCharSockaddr4(  tab_i1 , zi ));
        //printf("\n\n (NoeudReseau %d ) TAB_O %s \n\n",n_id,toTabCharSockaddr4(  tab_o1 , zi ));
        
      
        if(pasPourLinstant ) printf("(NoeudReseau %d ) Tableau des addresses qui vont se connecté à notre socket %d\n",n_id,listen_sockfdi  );
       
         //P1 : 
        int fd[2];
         //P1 : 
        socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);
        strcpy(buf2,"\0");

            // i  | o splitter pour attendre et envoyer
            int pid=0;
            int * sockfd3= (int*)malloc(sizeof(int)*zi);
            
            if(!(pid=fork())){

                close(fd[index_parentsocket()]);
                struct sockaddr_in client_addr;
                getsockname(  listen_sockfdo , (struct sockaddr*)&client_addr, &addr_size);


                //sleep(10);
                 //P1 : numbytes=recv2TCP(fd[0],ok,MAXBUFLEN); //syncrho a modifier 
                 //attends message serveur pour savoir si tous les serv sont à l'écoute  
                 struct Link * outputs=cst_Link(zi) ; //result_input cli  et rq_input NN
                sockfd3[0]=sockfd2;
                getsockname(  sockfd3[0] , (struct sockaddr*)&cl_addr, &addr_size);
                getpeername(  sockfd3[0] , (struct sockaddr*)&cl_addr2, &addr_size);


                printf(" S1  On (%d |  %s ) s'est connecté sur le  NoeudReseau %d : %s vers  %s  \n" ,n_id,toCharSockaddr(&client_addr),0,toCharSockaddr(&cl_addr),toCharSockaddr(&cl_addr2));


                 for(int i =1 ; i<zi ; i++){
                    //sockfd= TCPSocket();
                    //connectTCP(sockfd,&tab_i[i]);
                    hints_out.ai_family = (*tab_i1)[i]->sin_family;
                    hints_out.ai_socktype = SOCK_STREAM;
                    if(DEBUG_CLI)printf("noeud %d FAAAMILY  %s\n\n ",n_id,familyToStr( (*tab_i1)[i]->sin_family));
                    inet_ntop(  (*tab_i1)[i]->sin_family,get_in_addr((struct sockaddr *) (*tab_i1)[i] ),ip_addr,INET6_ADDRSTRLEN);
                    sprintf(port,"%d", ntohs(get_in_port((struct sockaddr *) (*tab_i1)[i] )));
                    sockfd3[i]= get_clientTCP(&hints_out , port , ip_addr );
                          //print_addrinfo(&hints_out);


                    getsockname(  sockfd3[i] , (struct sockaddr*)&cl_addr, &addr_size);
                    getpeername(  sockfd3[i] , (struct sockaddr*)&cl_addr2, &addr_size);


                    printf("S1  On (%d |  %s ) s'est connecté sur le  NoeudReseau %d : %s vers  %s  \n" ,n_id,toCharSockaddr(&client_addr),i,toCharSockaddr(&cl_addr),toCharSockaddr(&cl_addr2));

                   
                    if(pasPourLinstant )shutdown(sockfd3[i],SHUT_RD);
                    link_add(outputs,&hints_out,outputs->nfds,sockfd3[i] ,POLLOUT);
                    send2TCP(sockfd3[i],oko,strlen(oko)+1);
                    //printf("ATTEND RECV \n ");
                    strcpy(buf2,"\0");
                    recv2TCP(sockfd3[i],buf2,MAXBUFLEN);
                    printf("S1 Node J'ai (%d |  %s ) recu le message (Taille : %d ) %s sur la socket  : %d  (Node_addresse %s)\n",n_id,toCharSockaddr(&client_addr),strlen(buf2), buf2,sockfd3[i]);
                               

                 }
  
                strcpy(buf2,"\0");
                numbytes=recv2TCP(fd[index_childsocket()],buf2,MAXBUFLEN);
                if(numbytes>0){
                    buf2[numbytes-1]='\0';
                    printf("j'ai recu %s de mon pair \n",buf2);


                    int codeColorReponse = 8;
                    char caraClusterAsk='7';
                    char* sept = (char*)malloc(2);
                    char* n_idc = intToChar(n_id);
                    sept[0]=caraClusterAsk;//TODO A REMPLACER par fusionNbStr et caraClusterAsk
                    sept[1]='\0';
                    sept=fusionstr(sept,n_idc,idClusterDelim());

                    sept=fusionstr(sept,buf2,messageDelim());
                    numbytes=send2TCP(sockfd3[0],sept,strlen(sept)+1);
                    //char buf3[7]="okeeee";
                    //numbytes=send2TCP(sockfd3[0],buf3,7);
                    strcpy(buf2,"\0");
                    numbytes= recv2TCP2(sockfd3[0],(void**)&buf2,MAXBUFLEN);
                    getpeername(  sockfd3[0] , (struct sockaddr*)&client_addr, &addr_size);
                    printf("S1 Node J'ai (%d |  %s ) recu du NameNode (%s) le message  (Taille : %d vs %d )  %s \n ",n_id,toCharSockaddr(&client_addr),toCharSockaddr(&client_addr),strlen(buf2),numbytes,buf2);
                    //strToken = strtok_r ( buf, sep,&save_ptr);
                    char* save_ptr;//Cluster , * save_ptrColor; 
                    /*char * carCluster[1] ; 
                    carCluster[0]=idClusterDelim() ; */
                    char* idCluster = strtok_r(buf2,idClusterDelim2(),&save_ptr);
                    int idClusterInt = strToInt (idCluster);
                    if(DEBUG_CLI)printf("S1 Node  (%d |  %s ) IdClusterInt %d \n",n_id,toCharSockaddr(&client_addr),idClusterInt );
                    char delimContent = '\n';
                    char* colorCluster = strtok_r(NULL,&delimContent,&save_ptr);
                    if(debug_client)printf(" S1 Node  (%d |  %s )  ColorParam envoye par serv  %s \n",n_id,toCharSockaddr(&client_addr),colorCluster);
                    struct ColorationParam* color_param =  strToColorParam(colorCluster ) ; 
                    struct ColorationResult ** colorResult =(struct ColorationResult **) malloc(sizeof(struct ColorationResult *)*1);
                    color_graph( colorResult ,color_param );
                    
                    char* tmp_colorTab = CRToStr(*colorResult); //intTabToString ( color_param->coloring , color_param->graphD->nodesQuantity , tabDelim(), color_cnt   ,0  );
                    if(DEBUG_CLI)printf("S1 Node  (%d |  %s )  ResultColoring %s \n\n ",n_id,toCharSockaddr(&client_addr),tmp_colorTab);
                    /*char* tmpBud = fusionNbStr(tmp_colorTab , color_cnt,reponseColorDelim());
                    printf("tmpBud1 %s \n\n ",tmpBud);*/
                    char* tmpBud1 = fusionNbStr(tmp_colorTab ,idClusterInt,idClusterDelim());
                    if(DEBUG_CLI)printf("S1 Node  (%d |  %s ) IdCluster:ResultColoring %s \n\n ",n_id,toCharSockaddr(&client_addr),tmpBud1);
                    char * tmpBud2 = fusionNbStr(tmpBud1 ,codeColorReponse,messageDelim()); // A REMPLACER PAR FUNCTION 


                    if(DEBUG_CLI)printf("S1 Node  (%d |  %s ) Code:IdCluster:ResultColoring %s \n",n_id,toCharSockaddr(&client_addr),tmpBud2);
                    numbytes=send2TCP(sockfd3[0],tmpBud2 ,strlen(tmpBud2 )+1);

                    ;

                    char caraColorAsk=9;
                    char* neuf = (char*)malloc(2);
                    neuf[0]='9';//TODO A REMPLACER par fusionNbStr et caraColorAsk
                    neuf[1]='\0';
                    neuf=fusionstr(neuf,n_idc,idClusterDelim());
                    neuf=fusionstr(neuf,oko,messageDelim());

                    sleep(42);

                    numbytes=send2TCP(sockfd3[0],neuf ,strlen(neuf )+1);
                    printf("S1 Node J'ai (%d |  %s ) envoye au NameNode (%s) le message  (Taille : %d vs %d )  %s \n ",n_id,toCharSockaddr(&client_addr),toCharSockaddr(&client_addr),strlen(buf2),numbytes,neuf);
                   
                    strcpy(buf2,"\0");
                    /*numbytes=recv2TCP(sockfd3[0],buf2,MAXBUFLEN);
                    printf("S1 Node J'ai (%d |  %s ) recu du NameNode (%s) le message  (Taille : %d vs %d )  %s \n ",n_id,toCharSockaddr(&client_addr),toCharSockaddr(&client_addr),strlen(buf2),numbytes,buf2);
                    printf("\n\n");*/
                    int couleurrr ;
                    numbytes=recv(sockfd3[0],&couleurrr,sizeof(int),0);
                    if(debug_client)printf("MA COULEUR EST LA NUMERO : %d !!! ",couleurrr);
                    if(debug_client)printf("\n\n");
                  //printf("S1 (%d | %s) Liens d'output du (NoeudReseau %d dont l'adresse est %s ) port_in :%s  \n",n_id,toCharSockaddr(&cl_addr),i,toCharSockaddr(&cl_addr2),in_port);print_hashlink(outputs-> descri);   


                  }


                
            }
                else{
                          
                int compteur_jo =0;
                int new_fd=0;
                socklen_t tmp_addrlen = sizeof(struct sockaddr);
                 struct Link * inputs=cst_Link(zi) ; //result_input cli  et rq_input NN
                struct sockaddr_in serv_addr;
                getsockname(  listen_sockfdi , (struct sockaddr*)&serv_addr, &addr_size);

                 link_add(inputs,&hints_in,inputs->nfds,listen_sockfdi ,POLLIN);
        //print_hashlink(inputs->descri); 
         
        printf("S2  (%d | %s ) \n\n\n\n",n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr));

        close(fd[index_childsocket()]);

                    while (compteur_jo < zi -1){ // moins le listen 
                                     //P1 : send2TCP(sockfd2,oko,strlen(oko)+1);
                                     //P1 : recv2TCP(sockfd2,ok,MAXBUFLEN);
                                     //P1 : send2TCP(fd[1],oko,strlen(oko)+1);
                                    int poll_count = poll(inputs->pfds, inputs->nfds, -1); //attends pour toujours une entree


                                if (inputs->nfds == -1) {
                                    perror("poll");
                                    exit(1);
                                }

                                for(int fd_i = 0; fd_i <= inputs->nfds ; fd_i++) {
                                 
                                            if (inputs->pfds[fd_i].revents & POLLHUP) {
                                                printf("POLLHUP\n");
                                                link_delete(inputs, fd_i);
                                            }
                                            else if (inputs->pfds[fd_i].revents & POLLNVAL) {
                                                printf("POLLNVAL %d \n", fd_i );
                                                link_delete(inputs, fd_i);
                                            }
                                            else if (inputs->pfds[fd_i].revents & POLLERR) {
                                                printf("POLLERR\n");
                                                link_delete(inputs, fd_i);
                                            }else if (inputs->pfds[fd_i].revents & POLLIN) {
                                                     // We got one!!
                                                        if (inputs->pfds[fd_i].fd == listen_sockfdi) { //TODO fd_i ==0 ? ATTENTION
                                                                 
                                                                // handle new connections
                                                                //tmp_addrlen = sizeof cl_addr;
                                                               
                                                                 if(pasPourLinstant )printf("S2 (%d | %s ) \n",n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr));
                                                                  if(inputs->nfds-1 ==zi   ){ // il y a assez de noeud 

                                                                        new_fd = p_accept(listen_sockfdi ,(struct sockaddr *)&cl_addr2,&tmp_addrlen) ;
                                                                        getsockname(  new_fd , (struct sockaddr*)&cl_addr, &addr_size);

                                                                        printf("S2 (%d | %s ) Node j'ai assez de noeud j'accept et je ferme la connection %s vers %s ",n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr),toCharSockaddr(&cl_addr ),toCharSockaddr(&cl_addr2 ));

                                                                        close(new_fd);
                                                            }
                                                                else if ( inputs->nfds-1 < zi ) { // il manque un noeud 
                                                                     if ((new_fd = p_accept(listen_sockfdi ,(struct sockaddr *)&cl_addr2,&tmp_addrlen)) ==-1){
                                                                      perror("accept_error");
                                                                    } else {

                                                            
                                                                    getsockname(  new_fd , (struct sockaddr*)&cl_addr, &addr_size);

                                                         
                                                                    //printf("S2 Client j'ai pas assez de noeud j'accept  la connection %s numero de socket %d  pos_pfds %d \n ",toCharSockaddr(&cl_addr),new_fd,inputs->nfds);
                                                                    printf("S2 (%d | %s ) Node j'ai pas assez de noeud j'accept la connection %s vers  %s  numero de socket %d  pos_pfds %d \n ",n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr),toCharSockaddr(&cl_addr),toCharSockaddr(&cl_addr2),new_fd,inputs->nfds);
                                                                    
                                                                        
                                                                    if(pasPourLinstant )shutdown(new_fd,SHUT_WR);
                                                                    link_add2(inputs,(struct sockaddr_in *)&cl_addr,tmp_addrlen,inputs->nfds, new_fd,POLLIN);
                                                                    //printf("S2 Node hasLink suite a l'ajout de la socket %d\n",new_fd);print_hashlink(inputs->descri);   

                                                                    //(if(inputs->nfds-2 == NB_NODE )){//...} // c'est pas son probleme que l'ensemble des noeuds soient correctement attachés entre eux ,c'est le nameNode qui va lancer l'event 
                                                               



                                                                }
                                                            }
                                                        }
                                                        else{//!= accept 

                                                                 //printf("S2 Node Je recois quelque chose sur la socket : %d \n",inputs->pfds[fd_i].fd);
                                                                 //printf("parent: ");
                                                                // handle data from a client
                                                                  if ((numbytes = recv2TCP(inputs->pfds[fd_i].fd, buf2, MAXBUFLEN)) <= 0) { //si recv fail
                                                                    // erreur ou fermeture connexion par client 
                                                                      getsockname(  inputs->pfds[fd_i].fd , (struct sockaddr*)&cl_addr, &addr_size);
                                                                    getpeername(  inputs->pfds[fd_i].fd , (struct sockaddr*)&cl_addr2, &addr_size);
                                                                    // erreur ou fermeture connexion par client 
                                                                    if (numbytes == 0) {
                                                                        //printf("Serveur : Canal communication  %d  fermé  \n", fd_i);
                                                                    } else {
                                                                        fprintf(stderr, " S2 ( %d | %s ) recv: %s (%d) (Node_addresse %s vers %s ) \n", n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr),strerror(errno), errno,toCharSockaddr(&cl_addr),toCharSockaddr(&cl_addr2));
                                                                        perror("recv2_error");
                                                                    }

                                                               
                                                               
                                                                    getsockname(  inputs->pfds[fd_i].fd , (struct sockaddr*)&cl_addr, &addr_size);
                                                                    getpeername(  inputs->pfds[fd_i].fd , (struct sockaddr*)&cl_addr2, &addr_size);

                                                                    printf("S2 ( %d | %s ) Node J'ai recu une \"déconexion\" sur la socket  : %d  (Node_addresse %s vers %s )\n" ,n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr),inputs->pfds[fd_i].fd,toCharSockaddr(&cl_addr),toCharSockaddr(&cl_addr2));
                                                                    
                                                                    close(inputs->pfds[fd_i].fd);
                                                                    
                                                                    
                                                                     link_delete(inputs, fd_i);
                                                                     strcpy(buf2,"\0");

                                                                    //printf("S2 Node  Update hashlink suite à la deletion du socket deconnecté %d:  ",inputs->pfds[fd_i].fd);print_hashlink(inputs->descri); 
                                                                    // printf("FIN2 %d",_clserv->nfds);
                                                                }
                                                           
                                                               else{

                                                                  
                                                                        getsockname(  inputs->pfds[fd_i].fd , (struct sockaddr*)&cl_addr, &addr_size);
                                                                        getpeername(  inputs->pfds[fd_i].fd , (struct sockaddr*)&cl_addr2, &addr_size);

                                                                        if(pasPourLinstant ){printf("S2 (%d | %s) Node J'ai recu le message %s sur la socket  : %d  (Node_addresse %s vers %s ) \n",n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr), buf2,inputs->pfds[fd_i].fd,toCharSockaddr(&cl_addr),toCharSockaddr(&cl_addr2));
                                                                        }else {
                                                                            compteur_jo++;
                                                                            printf("S2 (%d | %s) Node J'ai recu le message %s sur la socket  : %d   DEBUG RECV : %d / %d  (Node_addresse %s vers %s )\n",n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr),buf2,inputs->pfds[fd_i].fd, compteur_jo , zi-1 ,toCharSockaddr(&cl_addr),toCharSockaddr(&cl_addr2));
                                                                                numbytes=send2TCP(inputs->pfds[fd_i].fd ,oko,strlen(oko)+1);
                                                                            if(compteur_jo== zi -1){
                                                                                
                                                                                numbytes=send2TCP(fd[index_parentsocket()],fino,strlen(fino)+1);
                                                                                //char  fin[4] = "FIN";
                                                                                //fin[4]='\0'; fait automatiquement
                                                                                //struct sockaddr_in cl_addr75;
                                                                                //getpeername(  sockfd2 , (struct sockaddr*)&cl_addr75, &addr_size);
                                                                                //numbytes=send2TCP(fd[index_parentsocket()],fin,strlen(fin)+1);
                                                                                //P1 numbytes = send2TCP(sockfd2,fin,strlen(fin)+1);
                                                                                //printf("\n \n On a envoyé %d bytes / %d au serveur %s   (message : %s ) \n \n",numbytes , strlen(fin)+1 , toCharSockaddr((struct sockaddr_in*)&cl_addr75) ,fin );
                                                                               
                                                                            }
                                                                        }
                                                                        //send2TCP(inputs->pfds[fd_i].fd,buf2,strlen(buf2));
                                                                        
                                                                       
                                                                        //close(inputs->pfds[fd_i].fd);
                                                                        //printf("FIN %d",_clserv->nfds);
                                                                        
                                                                         //link_delete(inputs, fd_i);
                                                                        if(pasPourLinstant ){ printf("S2 (%d | %s) Node On a fini !\n  Update hashlink suite à la deletion du socket %d :  ",n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr),inputs->pfds[fd_i].fd);print_hashlink(inputs->descri); }
                                                                        else if(debug_client){ printf("S2 (%d | %s) Node On a fini !\n  ",n_id,toCharSockaddr((struct sockaddr_in*)&serv_addr));}
                                                                        strcpy(buf2,"\0");

                                                               }

                                                       }//else de fdi==listen (!= accept )

                                                }//if POLLIN 
                                      
                                        }//for sur les fdi 

                            }//while 


                if(debug_client)printf("FIN RECV ATT \n\n");
                strcpy(buf2,"\0");
                numbytes=recv2TCP(fd[index_parentsocket()],buf2,MAXBUFLEN);
               if(debug_client)printf("FINI FINI \n");

            }//else pid 

    }//numbytes  

return 0;
}//fonction clientTrop
