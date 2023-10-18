


/**
 * fichier: helper_function.c
 * auteur: Rambal Julien
 * description : Fonctions utiles aux communications réseaux (getClient , getServ , send ,recv etc )
 **/



#include "helper_function.h"


void abort_sock(int code,char* fonction,char* error_mss , int sock){
	if(debug)printf("abort_sock \n");
	if(param_print)printf(" PARAM : code_erreur %d ,fonction %s ,error_mss :  %s , socket %d \n",code,fonction,error_mss,sock);
	char str_code [5] ;
	sprintf(str_code,"%d",code);
	size_t taille  = 0;
	
	char * error_message = (char*)malloc(strlen(str_code)+ strlen(fonction) +strlen(error_mss)+4);
	strcpy(error_message,fonction );
	taille+=strlen(fonction);
	error_message[taille++]=':';
	error_message[taille]='\0';//possible en 1 coup ?
	strncat(error_message,str_code,strlen(str_code));
	taille+=strlen(str_code);
	error_message[taille++]='\n';
	error_message[taille]='\t';
	if(strcmp(error_mss,"")!=0){
	strncat(error_message , error_mss,strlen(error_mss));
	taille+=strlen(error_mss);
	}
	perror(error_message);
	print_errno ();
	close(sock);
	exit(1);
}


int err_manager ( const unsigned int  id_fonction , const int result_fonction , int socket  ){
	if(debug)printf("err_manager");
	if(param_print)printf(" PARAM : id_fonction %d , result_fonction %d , socket %d  \n ",id_fonction,result_fonction,socket);
	char * message_erreur = "";
	char * fonction ;
	switch(id_fonction){
	case getSendToID() :
		fonction="SendTo";
		  if (result_fonction < 1){
		  	   
			   message_erreur=(result_fonction  == 0? "serveur deconnecté" :(result_fonction  ==-1 ?erreur_mss_default():erreur_mss_pasFait()));

		  }
		  
		   break;
		   
	case getSendID():
		fonction="Send";
		 if (result_fonction < 1){
		 	  
			   message_erreur=(result_fonction  == 0? "serveur deconnecté" :(result_fonction  ==-1 ?erreur_mss_default():erreur_mss_pasFait()));

		  }
		 
		   //printf("Envoye de %d octets au serveur %s\n", result_fonction, inet_ntoa( s_addr.sin_addr));
		   break;
		  
	case getRecvfromID():
		fonction="RecvFrom";
	  if (result_fonction < 1){
	  		   
			   message_erreur=(result_fonction  == 0? "serveur deconnecté" :(result_fonction  ==-1 ?erreur_mss_default():erreur_mss_pasFait()));

		  }
		   //printf("Recu de %d octets au serveur %s\n", result_fonction, inet_ntoa( s_addr.sin_addr));
		 break;
		   
	case getRecvID(): 
		fonction="Recv";
	 	 if (result_fonction < 1){
	 	 	   
			   message_erreur=(result_fonction  == 0? "serveur deconnecté" :(result_fonction==-1 ?erreur_mss_default():erreur_mss_pasFait()));

		  }
		   //printf("Recu de %d octets au serveur %s\n", result_fonction, inet_ntoa( s_addr.sin_addr));
		 break;
		 
	default:
		message_erreur="pas fait";
	break;
	 
	}
	if(strcmp(message_erreur,"")!=0){
	abort_sock(result_fonction ,fonction,message_erreur,socket);
	}else {
		if(debug)printf("Fonction: %s numbytes :%d \t(socket :%d)  \n",fonction,result_fonction,socket);

	}
return result_fonction;
	  
	  
	 }
	 
#define getSocketID() 0
#define getConnectID() 1
#define getBindID() 2
#define getListenID() 3
#define getAcceptID() 4
		
	 
int err_socket ( unsigned int  id_fonction , int result_fonction ,int socket){
	
	char * message_erreur = "";
	char * fonction ;
	if(debug)printf("err_socket \n ");
	if(param_print)printf("PARAM : id_fonction %d , result_fonction %d , socket %d \n ",id_fonction,result_fonction,socket);
	switch(id_fonction){
	
	
	case getSocketID():

		  if (result_fonction == -1) {
			  perror("socket ");
			  //close(socket);
			  exit(1);
		}
		   break;
		   
	case getConnectID():
		  fonction="Connect";
		  if (result_fonction == -1) {
			 message_erreur=erreur_mss_default();
		  }
		 
		   break;
		   
	case getBindID():
		  fonction="Bind";
		  if (result_fonction == -1) {
			  message_erreur=erreur_mss_default();
		}
		   break;
	case getListenID():
		 fonction="Listen";
		  if (result_fonction == -1) {
			 message_erreur=erreur_mss_default();
		}
		   break;
		   
	case getAcceptID():
		  fonction="Accept";
		  if (result_fonction == -1) {
			//message_erreur=erreur_mss_default();
		}
		   break;
		   

		   
		  
		 
	default:
	printf("pas fait \n");
	break;
	
	}
	if(strcmp(message_erreur,"")!=0)abort_sock(result_fonction ,fonction,message_erreur,socket);
	else printf("Fonction: %s result :%d \t(socket :%d)  \n",fonction,result_fonction,socket);
	return result_fonction;
	  
	  
	  
	 }




ssize_t p_send(int sockfd , const void * buf , size_t len , int flags){
	if(debug)printf("Send \n");
	if(param_print)printf("PARAM sockfd %d buf %s , len %ld ,flags %d \n",sockfd ,(const char*)buf , len ,flags);
	return send(sockfd,buf,len,flags);
}
ssize_t p_sendto(int sockfd , const void * buf , size_t len , int flags,const struct sockaddr *dest_addr,socklen_t addrlen){
	if(debug)printf("Sendto \n");
	
	if(param_print){
	char* sockaddr_string = sockaddrtoStr(dest_addr);
	printf("PARAM sockfd %d buf %s , len %ld ,flags %d , dest_addr %s , addrlen:%d  \n",sockfd ,(const char*)buf , len ,flags, sockaddr_string, addrlen );
	free(sockaddr_string);
	}
	return sendto(sockfd,buf,len,flags,dest_addr,addrlen);

}

ssize_t p_recv(int sockfd ,  void * buf , size_t len , int flags){
	if(debug)printf("Recv \n");
	if(param_print)printf("PARAM sockfd %d buf %s , len %ld ,flags %d \n",sockfd ,(char*) buf , len ,flags);
	return recv(sockfd,buf,len,flags);
}
ssize_t p_recvfrom(int sockfd ,  void * buf , size_t len , int flags, struct sockaddr *dest_addr,socklen_t * addrlen){
	if(debug)printf("Recvfrom\n");
	if(param_print){
	char* sockaddr_string = sockaddrtoStr(dest_addr);
	printf("PARAM sockfd %d buf %s , len %ld ,flags %d , dest_addr %s , addrlen:%d  \n",sockfd ,(char*)buf , len ,flags, sockaddr_string, *addrlen );
	free(sockaddr_string);
	}
	return recvfrom(sockfd,buf,len,flags,dest_addr,addrlen);

}

int p_connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen){
	if(debug)printf("Connect\n");
	if(param_print){
	char* sockaddr_string = sockaddrtoStr(addr);
	printf("PARAM sockfd %d, addr %s , addrlen:%d  \n",sockfd ,sockaddr_string, addrlen );
	free(sockaddr_string);
	}
	return connect(sockfd,addr,addrlen);

}

int p_accept(int sockfd,struct sockaddr *restrict addr,socklen_t * restrict addrlen){
	if(debug)printf("Accept\n");
	if(param_print){
	char* sockaddr_string = sockaddrtoStr(addr);
	printf("PARAM sockfd %d, addr %s , addrlen:%d  \n",sockfd , sockaddr_string, *addrlen );
	free(sockaddr_string);
	
	}
	return accept (sockfd,addr,addrlen);
}

int p_bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen){
	if(debug)printf("Bind\n");
	if(param_print){
	char* sockaddr_string = sockaddrtoStr(addr);
	printf("PARAM sockfd %d, addr %s , addrlen:%d  \n",sockfd , sockaddr_string, addrlen );
	free(sockaddr_string);
	}
	return bind(sockfd,addr,addrlen);
}

int sec_bind(int sockfd,const struct sockaddr_in *addr){
	socklen_t addrlen = sizeof(struct sockaddr  );
	return err_socket(getBindID() ,p_bind(sockfd,(struct sockaddr * ) addr,addrlen),sockfd);
}
int sec_accept(int sockfd,struct sockaddr_in *restrict addr){
	socklen_t addrlen = sizeof(struct sockaddr  );
	return err_socket(getAcceptID(),p_accept(sockfd,(struct sockaddr * ) addr,&addrlen),sockfd); 
	}

int sec_connect(int sockfd,const struct sockaddr_in * addr){
	socklen_t addrlen = sizeof(struct sockaddr  );
	return err_socket(getConnectID() ,p_connect(sockfd,(struct sockaddr * ) addr,addrlen),sockfd);
	}

int sec_send(int sockfd , const void * buf , size_t len ){
return err_manager(getSendID(),p_send(sockfd,buf,len,0),sockfd);
}
int sec_sendto(int sockfd , const void * buf , size_t len ,const struct sockaddr_in *dest_addr){
	socklen_t addrlen = sizeof(struct sockaddr  );
	return err_manager(getSendToID(),p_sendto(sockfd,buf,len,0,(struct sockaddr * ) dest_addr,addrlen),sockfd);
	}
int sec_recvfrom(int sockfd ,  void * buf , size_t len , struct sockaddr_in *dest_addr){
	socklen_t addrlen = sizeof(struct sockaddr  );
	return err_manager(getRecvfromID(),p_recvfrom(sockfd,buf,len,0,(struct sockaddr * )dest_addr,&addrlen),sockfd);
	}
int sec_recv(int sockfd ,  void * buf , size_t len ){
	return err_manager(getRecvID(),p_recv(sockfd,buf,len,0),sockfd);
	}
	



int TCPSocket() { 
    if(debug)printf("TCPSocket\n");
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        fprintf(stderr,"Erreur : creation socket %d \n",sockfd);
        if(debug)print_errno ();
        exit(1); 
    }
    printf("Success : creation socket %d \n",sockfd);
    return sockfd;
}

int UDPSocket() {
    if(debug)printf("UDPSocket\n");
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1){
        fprintf(stderr,"Erreur : creation socket %d \n",sockfd);
        if(debug)print_errno ();
        exit(1); 
    }
    printf("Success : creation socket %d \n",sockfd);
    return sockfd;
}


void designerSocket(struct sockaddr_in * sockfd ,char* port ,char * addr_ip ) {
	 if(debug)printf("DesignerSocket\n ");
	 if(param_print)printf("PARAM : port %s , addr_ip %s \n",port , addr_ip );
    sockfd->sin_family = AF_INET;
    sockfd->sin_port = htons((short)atoi(port));
    sockfd->sin_addr.s_addr =inet_addr(addr_ip);
}
void df_designerSocket(struct sockaddr_in * sockfd ,char* port) {
    designerSocket(sockfd,port,"0.0.0.0");
}
struct sockaddr_in nommerSocket(int sockfd,char* port ,char * addr_ip ) {
 	if(debug)printf("nommerSocket\n ");
 	if(param_print)printf("PARAM sockfd %d port %s , addr_ip %s \n",sockfd,port,addr_ip );
    struct sockaddr_in addr; 
    designerSocket(&addr , port , addr_ip);
    int res=0;
    res = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (res == 0) {
    	char str[INET_ADDRSTRLEN];
    	inet_ntop(AF_INET,&addr.sin_addr,str,INET_ADDRSTRLEN);
        printf("Success : Bind (nommage Socket) %d  port :%i addr_ip :%s\n", sockfd ,ntohs((short) addr.sin_port) ,str);
    } else {
        fprintf(stderr,"Erreur : Bind (nommage Socket) %d  port :%i addr_ip :%s\n", sockfd ,ntohs((short) addr.sin_port) ,addr_ip);
        if(debug){ printf("bind : %d\n",res); print_errno (); 
        close(sockfd);
        exit(1);
    }
    }
    return addr;
}

struct sockaddr_in df_nommerSocket(int sockfd,char* port ) {
	if(debug)printf("df_nommerSocket\n");
	return nommerSocket(sockfd,port,"0.0.0.0");
    
}

void connectTCP(int sockfd, struct sockaddr_in * serv_addr) {
	if(debug)printf("connectTCP \n ");
	if(param_print)printf("PARAM sockfd %d \n " ,sockfd );
	
    int res = connect(sockfd, (struct sockaddr *)serv_addr, sizeof(struct sockaddr));
    if (res  == -1 ) {
        fprintf(stderr,"Erreur :  Connect de %d  sur le serv %p \n",sockfd , serv_addr);
        if(debug)print_errno ();
        close(sockfd);
        exit(1);
    }
     // else  //  0 
     printf("Success : Connect  de %d sur le serv %p \n",sockfd , serv_addr);
}

void listenTCP(int listen_sockfd, size_t nbMaxAttente) {
    if(debug)printf("listenTCP \n ");
    if(param_print)printf("PARAM listen_sockfd %d  nbMaxAttente :%ld \n " ,listen_sockfd ,nbMaxAttente);
    
    int res = listen(listen_sockfd, nbMaxAttente);
    if (res == -1) {
        fprintf(stderr,"Erreur : Listen sock : %d nbMaxConnection: %ld \n", listen_sockfd,  nbMaxAttente );
        if(debug)print_errno ();
        exit(1);    
    }
    // else  //  0 
    printf("Success : listen sock : %d nbMaxConnection: %ld \n", listen_sockfd,  nbMaxAttente );

}



///////////////////////////////////////////////////////////////////////

int sendTCP(int fdsock, void* msg, int sizeMsg) {
 if(debug)printf("sendTCP \n ");
    if(param_print)printf("PARAM fdsock %d msg :%s  sizeMsg: %d \n " ,fdsock ,(char*)msg,sizeMsg);
    
    int numbytes=0;
    int total_bytesEnvoyer=0;
    //boucle d'envoi
    if(debug) printf("SendTCP : \n msg: %s , taille_total : %d \n",(char*)msg,sizeMsg); 
    for(int nb_send=0;total_bytesEnvoyer  < sizeMsg; total_bytesEnvoyer += numbytes,nb_send++) {
        //printf("Reste à envoyer: %i (res %i) envoyé %i\n",sizeMsg-sent, res, sent);
        numbytes= send(fdsock, msg+total_bytesEnvoyer, sizeMsg-total_bytesEnvoyer, 0);
 		//fprintf(stderr, "  send sur socket %d  nb env %d / %d (numbyte %d)  erreur %s nb_err %d \n", fdsock,sizeMsg-total_bytesEnvoyer,total_bytesEnvoyer, numbytes,strerror(errno), errno);
                                        
           switch(numbytes){
        	case -1: 
		printf("Problème lors de l'envoie du message \n");
		if(debug){printf("numbytes : %d\n",numbytes); print_errno ();}
            	return -1;
		default:
			if(debug){
			printf(" Success envoi  : Serveur : %d \n",fdsock);
			printf("\t Taille du paquet %d octet paquet : %s \n", numbytes , (char*)(msg+total_bytesEnvoyer));
			}
	}
    }
    return total_bytesEnvoyer;
}
/*
int input_send2TCP(int fdsock,char * buff ,unsigned int maxSize){
printf("Rentrer une chaine de caractere de max : %d \n" ,maxSize);
fgets(buff,maxSize,stdin);
if(debug)printf("chaine rentrer : %s \n",buff);
int numbytes = send2TCP(fdsock,buff,strlen(buff)+1);

printf("nb_bytes envoyer par Send2TCP : %d \n" ,numbytes);
return numbytes ;

}*/
// envoie la taille du message (peut etre en plusieurs partie ) puis envoie le message ( peut etre en plusieurs partie ) 
int send2TCP(int fdsock, void* msg, unsigned int sizeMsg) {
if(debug)printf("send2TCP \n ");
    sendTCP(fdsock, &sizeMsg, sizeof(unsigned int));
    return sendTCP(fdsock, msg, sizeMsg);
}


int recvTCP(int fdsock, void* msg, unsigned int sizeMsg) {
	if(debug)printf("recvTCP \n ");
    if(param_print)printf("PARAM fdsock %d msg :%s  sizeMsg: %d \n " ,fdsock ,(char*)msg,sizeMsg);
    
    int numbytes=0;
    int total_bytesRecu=0;
    for(int nb_recv=0;total_bytesRecu< sizeMsg;total_bytesRecu += numbytes,nb_recv++) {
         numbytes = recv(fdsock, msg+total_bytesRecu, sizeMsg-total_bytesRecu, 0);
        switch(numbytes){
        	case -1: 
		    printf("Problème lors de la reception du message \n");
		    if(debug){printf("numbytes : %d\n",numbytes); print_errno ();}
		    return -1 ;
        	case 0 :
		    //Pas sur 
		     if(debug)printf("RecvTCP : recv à renvoyer numbytes = %d \n",numbytes);
		     return 0 ;
		default:
			if(debug){
			printf(" Success Reception : Serveur : %d \n",fdsock);
			printf("\t Taille du paquet %d octet , contenu paquet : %s \n", numbytes , (char*)(msg+total_bytesRecu));
			}
	}
 	 
        }
   
    return total_bytesRecu;
}

// recoit la taille du message (peut etre en plusieurs partie ) puis recoit le message ( peut etre en plusieurs partie ) 
int recv2TCP(int fdsock, void* msg, unsigned int sizeMsg) {
	if(debug)printf(" recv2TCP \n ");
    unsigned int taille;
    int numbytes=0;
    numbytes=recvTCP(fdsock, &taille, sizeof(unsigned int));
    if(numbytes<=0)return numbytes;
    if ( taille > sizeMsg) {
        printf("Problème, buffer trop petit!\n");
        if(debug)print_errno ();
        return -1;
    }
    if(debug)printf("recv2TCP %s \n taille : %d\n",(char*)msg,taille);
    return recvTCP(fdsock, msg, taille);
}

int recv2TCP2(int fdsock, void** msg, unsigned int sizeMsg) {
	if(debug)printf(" recv2TCP \n ");
    unsigned int taille;
    int numbytes=0;
    numbytes=recvTCP(fdsock, &taille, sizeof(unsigned int));
    if(numbytes<=0)return numbytes;
    if ( taille > sizeMsg) {
        *msg=realloc(*msg,taille);

    }
    if(debug)printf("recv2TCP %s \n taille : %d\n",(char*)*msg,taille);
    return recvTCP(fdsock, *msg, taille);
}






int my_sendTCP(int sock , char*  msg , int sizeMsg){
unsigned int total_envoyer =0;
int numbytes=0;
while( total_envoyer < sizeMsg){
numbytes = send(sock , msg+total_envoyer , sizeMsg ,0);
if(numbytes==-1 || numbytes==0){printf("Problème my_sendTCP " );return numbytes;}
total_envoyer+=numbytes;
}
return 1;
}


int my_recvTCP(int sock , char*  msg , int sizeMsg){
int numbytes=0;
numbytes = recv(sock , msg , sizeMsg,0);
if(numbytes==-1 || numbytes==0){printf("Problème my_recvTCP " );return numbytes;}
else return 1; 
return 1;
}


//--------------------------------------------------------------------------------------------

const char * getWelcomeStr() {
return "Bonjour , je suis à votre écoute \n";
}

//faire une version sans param qui appelle version param avec default param 	





int get_listenTCP2(struct addrinfo  *hints ,char* port ,char * ip_addr2,  unsigned int backloge )
{

    int listen_sockfd ;     
    int reuseBool=1;       
    struct addrinfo * addrinfos ;
	  int tmp_getAddr ;
	  
	  

    if ((tmp_getAddr = getaddrinfo(ip_addr2, port, hints, &addrinfos)) != 0) {
        fprintf(stderr, "getaddrinfo_error: %s\n", gai_strerror(tmp_getAddr));
        exit(1);
    }
    struct addrinfo * ptr_addrinfo;
    
    for(ptr_addrinfo = addrinfos; ptr_addrinfo != NULL; ptr_addrinfo = ptr_addrinfo->ai_next) {
        if ((listen_sockfd = socket(ptr_addrinfo->ai_family, ptr_addrinfo->ai_socktype, ptr_addrinfo->ai_protocol))<0){
        	perror("socket_error ");
            continue;
        }
        
 
       setsockopt(listen_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseBool, sizeof(int));

        if (p_bind(listen_sockfd, ptr_addrinfo->ai_addr, ptr_addrinfo->ai_addrlen) < 0) {
            close(listen_sockfd);
            continue;
        }

        break;
    }


     if (ptr_addrinfo == NULL) {
        return -1;
    }


    copyaddrinfo(hints,ptr_addrinfo);
   
   
	freeaddrinfo(addrinfos);
	

	listenTCP(listen_sockfd, backloge);

    return listen_sockfd;
}


int get_listenTCP(struct addrinfo  *hints ,char* port ,  unsigned int backloge ){
	return get_listenTCP2(hints ,port ,NULL,  backloge );
}


int get_clientTCP(struct addrinfo * hints , char* port ,  char * ip )
{

    int client_sockfd ;     
         
    struct addrinfo  *servinfos ;
	  int tmp_getAddr ;

    if ((tmp_getAddr = getaddrinfo(ip,  port, hints, &servinfos)) != 0) {
        fprintf(stderr, "getaddrinfo_error: %s\n", gai_strerror(tmp_getAddr));
        exit(1);
    }
    struct addrinfo * ptr_addrinfo;
    for(ptr_addrinfo = servinfos; ptr_addrinfo != NULL; ptr_addrinfo = ptr_addrinfo->ai_next) {
        if ((client_sockfd = socket(ptr_addrinfo->ai_family, ptr_addrinfo->ai_socktype, ptr_addrinfo->ai_protocol))==1){
        	perror("client socket");
            continue;
        }

        if (p_connect(client_sockfd, ptr_addrinfo->ai_addr, ptr_addrinfo->ai_addrlen) < 0) {
            close(client_sockfd);
            perror("client connect");
            continue;
        }

        break;
    }
 

    if (ptr_addrinfo == NULL) {
        return -1;
    }

    copyaddrinfo(hints,ptr_addrinfo);
   
   
	freeaddrinfo(servinfos); 


    return client_sockfd;
}


size_t i_send(int sockfd , const int * buf , size_t len , int flags){
	if(debug)printf("Send \n");
	if(param_print)printf("PARAM sockfd %d buf %d , len %ld ,flags %d \n",sockfd ,*buf , len ,flags);
	return send(sockfd,buf,len,flags);
}




