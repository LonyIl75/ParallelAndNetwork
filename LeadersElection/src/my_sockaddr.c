
/**
 * fichier:my_sockaddr.c
 * auteur: Rambal Julien
 * description : fonctions utiles pour gérer notamment les  tableau 1D ,2D de sockaddrs
 **/



#include "my_sockaddr.h"



void print_sockaddrTab (struct sockaddr_in *  tab,size_t taille ){
     if(DEBUG_SOCKA)printf("12\n");
    //printf("tail %ld\n",taille);
    printf("[|");
    for( int i =0; i< taille ; i++)
    {

        printf(" %s|",sockaddrtoStr2 (&tab[i]));
    }
    printf("]\n");


}

void print_sockaddrTabtabtab (struct sockaddr_in ***  tab,size_t taille , int* taille_bis  ){

    for(int i = 0 ; i<taille ; i++){
    printf("[|");
    for( int j =0; j< taille_bis[i] ; j++)
    {

        printf(" %s|",toCharSockaddr(tab[i][j]));
    }
    printf("]\n");

    }
    //printf("PRINT_tabtabtab \n");

}


void print_sockaddrTabtabtab2 (struct sockaddr_in ****  tab,int taille , int * taille_biso , int* taille_bis  ){

	for(int k =0 ; k < taille ; k++){
		printf("[[ ");
    for(int i = 0 ; i<taille_biso[k] ; i++){
    printf("[o");
  

     printf(" %s|",toTabCharSockaddr(tab[k][i],taille_bis[k]));

    printf("o] ; ");

    }
    printf("]] \n ");
}
    //printf("PRINT_tabtabtab 2 \n");

}


struct addrinfo initialize_hintsTCP(){

    struct addrinfo hints ;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; //UNSPEC MARCHE PAS 
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    return hints ;
}



struct sockaddr_in* scki_memcpy (struct sockaddr_in* scki_dest , struct sockaddr_in* scki_src ){
   
   scki_dest=realloc( scki_dest,( sizeof(struct sockaddr_in)));
   //printf("FAMILY %s \n", familyToStr (scki_src->sin_family));
   scki_dest->sin_family = scki_src->sin_family ;
   //printf("FAMILY %s \n", familyToStr (scki_dest->sin_family ));
   scki_dest->sin_port = scki_src->sin_port ;
   scki_dest->sin_addr = scki_src->sin_addr ;
  strcpy(scki_dest->sin_zero,scki_src->sin_zero);
  return scki_dest ;
 
}



void scki_memcpy2 (struct sockaddr_in** scki_dest , struct sockaddr_in* scki_src ){
   
   *scki_dest=realloc( *scki_dest,( sizeof(struct sockaddr_in)));
   //printf("FAMILY %s \n", familyToStr (scki_src->sin_family));
   (*scki_dest)->sin_family = scki_src->sin_family ;
   //printf("FAMILY %s \n", familyToStr ((*scki_dest)->sin_family ));
   (*scki_dest)->sin_port = scki_src->sin_port ;
   (*scki_dest)->sin_addr = scki_src->sin_addr ;
  strcpy((*scki_dest)->sin_zero,scki_src->sin_zero);
  
 
}



void scki_cpy (struct sockaddr_in* scki_dest , struct sockaddr_in* scki_src ){
   //printf("%p POINTER \n",scki_dest);
   //printf("FAMILY2 %s \n", familyToStr (scki_src->sin_family));
   scki_dest->sin_family = scki_src->sin_family ;
   //printf("FAMILY2 %s \n", familyToStr (scki_dest->sin_family ));
   scki_dest->sin_port = scki_src->sin_port ;
   scki_dest->sin_addr = scki_src->sin_addr ;
  strcpy(scki_dest->sin_zero,scki_src->sin_zero);

 
}


/*
struct sockaddr_in *  hintsToScki(struct addrinfo * addinfo , char* port ,char * addr_ip ) {
    struct sockaddr_in *  fatigue = (struct sockaddr_in*) malloc( sizeof(struct sockaddr_in));
    fatigue->sin_family=addinfo->ai_family; // BIZZARE TODO 
    fatigue->sin_port = htons((short)atoi(port));
    fatigue->sin_addr.s_addr =inet_addr(addr_ip);
    return fatigue ; 
}
*/





void free_sckimemcpy(struct sockaddr_in* scki_dest ){
    //freeToNull((void**)&(scki_dest->sin_addr));
    freeToNull((void**)&scki_dest);
}

void  copyaddrinfo(struct addrinfo* dst, struct addrinfo* src ){

    dst->ai_next = NULL;
    dst->ai_flags = 0; 
    dst->ai_family = src->ai_family;
    dst->ai_socktype = src->ai_socktype;
    dst->ai_protocol = src->ai_protocol;
    dst->ai_addrlen = src->ai_addrlen;
    dst->ai_addr = (struct sockaddr *) malloc(src->ai_addrlen); // a free 
    dst->ai_canonname = NULL;
    memcpy(dst->ai_addr, src->ai_addr, src->ai_addrlen);



}

void *get_in_addr(struct sockaddr *sockfd)
{
    if (sockfd->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sockfd)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sockfd)->sin6_addr);
}

in_port_t get_in_port(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return (((struct sockaddr_in*)sa)->sin_port);

    return (((struct sockaddr_in6*)sa)->sin6_port);
}


 int  strtoFamily (char* str ){
    //printf("encore |%s| \n",str);
    if (strcmp(str, "AF_UNIX") == 0){

     return AF_UNIX ;
 }
    else if (strcmp(str, "AF_INET") == 0) {
        //printf("GOOD AF_INET \n");
        return AF_INET; 
    }
    else if (strcmp(str, "AF_INET6") == 0) {return AF_INET6;}         
    else if (strcmp(str, "AF_IPX") == 0) {return AF_IPX;}
    else if (strcmp(str, "AF_NETLINK") == 0) {return AF_NETLINK;} 
    else if (strcmp(str, "AF_X25") == 0) {return AF_X25;}
    else if (strcmp(str, "AF_AX25") == 0) {return AF_AX25;} 
    else if (strcmp(str, "AF_ATMPVC") == 0) {return AF_ATMPVC;} 
    else if (strcmp(str, "AF_ATMPVC") == 0) {return AF_ATMPVC;}
    else if (strcmp(str, "AF_APPLETALK") == 0) {return AF_APPLETALK;} 
    else if (strcmp(str, "AF_PACKET") == 0) {return AF_PACKET;}       
    else if (strcmp(str, "AF_ALG") == 0) { return AF_ALG;}  
    else{ return -1;}



}




const char * familyToStr (int family){

    switch(family){

       case AF_UNIX :
            return "AF_UNIX";
        /*case AF_LOCAL :  
            return "AF_LOCAL";*/
        case AF_INET : 
            return "AF_INET";           
        case AF_INET6  :     
            return "AF_INET6";
        case AF_IPX :         
            return "AF_IPX";
        case AF_NETLINK :         
            return "AF_NETLINK";
        case AF_X25 :              
            return "AF_X25";
        case AF_AX25 :             
            return "AF_AX25";
        case AF_ATMPVC :          
            return "AF_ATMPVC";
        case AF_APPLETALK :        
            return "AF_APPLETALK";
        case AF_PACKET :           
            return "AF_PACKET";
        case AF_ALG :
            return "AF_ALG";
        default : 
            return "AF_UNKNOW";

   }
   return "";

}

char * sockaddrtoStr2 (const  struct sockaddr_in * addr){


    char * str ;
    char  champ_title [] = "Family : , Port : , Ip_addr : "; // si pas [] alors segmentation fault
    
    //champ value:
    const char * family = familyToStr (addr->sin_family);
        char  port [7] ;
        sprintf(port,"%d", ntohs(get_in_port((struct sockaddr *)addr )));//max : "65 535" donc 5 
        //printf("pot %s \n",port);
        char ip_addr [INET6_ADDRSTRLEN];
        inet_ntop(addr->sin_family,get_in_addr((struct sockaddr *)addr ),ip_addr,INET6_ADDRSTRLEN);

        size_t taille ,taille_append,taille_final;
        taille_append=taille=0;
        
        taille_final=strlen(family)+strlen(port)+strlen(ip_addr)+strlen(champ_title)+1+3-1;//3-1 pour les 2 virgule de Family port - ip_addr 
        
        
        str=(char*)malloc( taille_final);
        strcpy(str,"");
    const char * sep = ",\n";
    char* save_ptr;
    char * strToken = strtok_r(champ_title,sep,&save_ptr);

    taille_append=strlen(strToken);
    strncat(str,strToken,taille_append);
    taille+=taille_append;

    taille_append=strlen(family);
    strncat(str,family,taille_append);
    taille+=taille_append;
    str[taille++]=',';
    

    strToken = strtok_r(NULL,sep,&save_ptr);
    taille_append=strlen(strToken);
    strncat(str,strToken,strlen(strToken));
    taille+=taille_append;
    
    taille_append=strlen(port);
    strncat(str,port,taille_append);
    taille+=taille_append;
    
    str[taille++]=',';
    
    strToken = strtok_r(NULL,sep,&save_ptr);
    taille_append=strlen(strToken);
    strncat(str,strToken,taille_append);
    taille+=taille_append;
    
    taille_append=strlen(ip_addr);
    strncat(str,ip_addr,taille_append);
    taille+=taille_append;
    
    
    str[taille]='\0';
    
    //printf("SockaddrintoStr :%s \n",str);
    
    return str;
    
    
    
        
}

/*
int order_char0(){

}*/



int equalSockAddr (struct sockaddr_in * eq1 , struct sockaddr_in * eq2){
    return eq1->sin_family == eq2->sin_family && eq1->sin_port== eq2->sin_port 
    &&  eq1->sin_addr.s_addr == eq2->sin_addr.s_addr 
    && !memcmp(eq1->sin_zero ,eq2->sin_zero, sizeof(eq1->sin_zero)); 
}
int isInSockAddr(struct sockaddr_in *** tab ,int index, size_t taille,  struct sockaddr_in * client_addr ){
    for(int i =0 ; i<taille;i++){
        //printf("i %d sockaddr_tab %s \n",i,toCharSockaddr(tab[i][index]));
        if(equalSockAddr (tab[i][index],client_addr)){
            return 1;
        }
    }
    return 0;

}

const char sockAddrDelim(){return ',';} // A CHANGER 
const char* tabSockaddrDelims(){
    char* delims = (char*)malloc(3);
    delims[0]=sockAddrDelim();
    delims[1]=';';
    delims[2]='\0';
    return delims;}

void charToSockAddr(struct sockaddr_in*** tab_sock , char* str , int taille ){


//printf("pot22 %s \n",str);
//struct sockaddr_in** tab_sock = (struct sockaddr_in**)malloc(taille*sizeof(struct sockaddr_in*));
    *tab_sock = realloc(*tab_sock ,taille);
    const char * sep = tabSockaddrDelims();
    //char buf_1[1024], buf_2[1024];
    char *save_ptr1, *save_ptr2;

    char *strToken1 = strtok_r(str,  &(sep[1]), &save_ptr1);


    char* strToken2;

    int i , j ;
    i=j=0;
    do {
        strToken2 = strtok_r(strToken1,&(sep[0]),&save_ptr2);
        (*tab_sock)[i]=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
        j=0;
        do {
            
            switch(j){

            case getFamilyIndex():
            (*tab_sock)[i]->sin_family=strtoFamily (strToken2);
            break;
            case getPortIndex():    
            (*tab_sock)[i]->sin_port = htons((short)atoi(strToken2));
            break;
            case getIpIndex():  
            inet_pton((*tab_sock)[i]->sin_family,strToken2, &((*tab_sock)[i]->sin_addr));
            break;
            default:
            printf("charToSockAddr : soucis !\n");
        }
        j++;
        //printf("Token2 step  %s \n",strToken2);
        strToken2 = strtok_r(NULL, &(sep[0]), &save_ptr2);
        }while(j<getTailleSerial() && strToken2 != NULL);
     
        //printf("Transfo result %s\n",toCharSockaddr(tab_sock [i]));
        i++;
         //printf("Token %s \n",strToken1);
        strToken1 = strtok_r(NULL, &(sep[1]), &save_ptr1);
        //printf("TokenLA %s \n",strToken1);
  
    }while(i< taille && strToken1 != NULL);
    //printf("Token %s \n",strToken1);

    //return tab_sock ;


}


char * toCharSockaddr(const  struct sockaddr_in * addr){

    char * str ;
        const char * family = familyToStr (addr->sin_family);
        char  port [7] ;
        sprintf(port,"%d", ntohs(get_in_port((struct sockaddr *)addr )));//max : "65 535" donc 5 
        //printf("pot %s \n",port);
        char ip_addr [INET6_ADDRSTRLEN];
        inet_ntop(addr->sin_family,get_in_addr((struct sockaddr *)addr ),ip_addr,INET6_ADDRSTRLEN);
        //printf("ip_addr %s \n",ip_addr);
        size_t taille ,taille_append,taille_final;
        taille_append=taille=0;
        
        taille_final=strlen(family)+strlen(port)+strlen(ip_addr)+1+3-1;//3-1 pour les 2 virgule de Family port - ip_addr 
        //printf("taille finale %d %d %d %d \n",taille_final,strlen(port),strlen(ip_addr),strlen(family));
        port[strlen(port)+1]='\0';
        ip_addr[strlen(ip_addr)+1]='\0';

        str=(char*)malloc( taille_final);
        //printf("%p INC\n\n",str);
        strcpy(str,"\0");
        //printf("INC\n\n");

    taille_append=strlen(family);
    strncat(str,family,taille_append);
    taille+=taille_append;
    str[taille++]=sockAddrDelim();
    str[taille]='\0';
    
    taille_append=strlen(port);
    strncat(str,port,taille_append);
    taille+=taille_append;

    str[taille++]=sockAddrDelim();
        str[taille]='\0';
    
    taille_append=strlen(ip_addr);
    strncat(str,ip_addr,taille_append);
    taille+=taille_append;
    
    str[taille]='\0';
    
    //printf("SockaddrintoStr :%s \n",str);
    
    return str;

}



void toCharSockaddr4(char ** str, const  struct sockaddr_in * addr){

        //printf("addr %p\n ",addr);
        //printf("FAM %d %s \n ",addr->sin_family,familyToStr (addr->sin_family));

        const char * family = familyToStr (addr->sin_family);
        char  port [7] ;
        sprintf(port,"%d", ntohs(get_in_port((struct sockaddr *)addr )));//max : "65 535" donc 5 
        //printf("pot %s \n",port);
        char ip_addr [INET6_ADDRSTRLEN];
        inet_ntop(addr->sin_family,get_in_addr((struct sockaddr *)addr ),ip_addr,INET6_ADDRSTRLEN);
        //printf("ip_addr %s \n",ip_addr);
        size_t taille ,taille_append,taille_final;
        taille_append=taille=0;
        
        taille_final=strlen(family)+strlen(port)+strlen(ip_addr)+1+3-1;//3-1 pour les 2 virgule de Family port - ip_addr 
        //printf("taille finale %d %d %d %d \n",taille_final,strlen(port),strlen(ip_addr),strlen(family));
        port[strlen(port)+1]='\0';
        ip_addr[strlen(ip_addr)+1]='\0';

        *str=realloc( *str ,taille_final);
        //printf("%p INC\n\n",str);
        strcpy(*str,family);
        //printf("INC\n\n");

    taille_append=strlen(family);

    taille+=taille_append;
    (*str)[taille++]=sockAddrDelim();
    (*str)[taille]='\0';
    
    taille_append=strlen(port);
    strncat(*str,port,taille_append);
    taille+=taille_append;

    (*str)[taille++]=sockAddrDelim();
    (*str)[taille]='\0';
    
    taille_append=strlen(ip_addr);
    strncat(*str,ip_addr,taille_append);
    taille+=taille_append;
    
    (*str)[taille]='\0';
    
    //printf("SockaddrintoStr :%s \n",str);


}


char * toTabCharSockaddr( struct sockaddr_in ** addr , int taille_tab ){

    char * str ;
    char **tmp_str = (char**)malloc((taille_tab+1) *(sizeof (char*))) ;
    for(int i=0;i < taille_tab;i++)tmp_str[i]=(char*)malloc(1);

        size_t taille ,taille_append,taille_final;
        taille_append=taille=taille_final=0;
        //printf("addr %p\n ",addr);
        for(int i = 0 ;i<taille_tab;i++ ){
            //printf("addr[i] %p\n ",addr[i]);
            toCharSockaddr4(&(tmp_str[i]),addr[i]);
            //printf("PHTR  %s\n",tmp_str[i]);
            taille_final+=strlen(tmp_str[i]);
        }

        taille_final+=taille_tab;//3-1 pour les 2 virgule de Family port - ip_addr 
        
        
        str=(char*)malloc( taille_final);
        strcpy(str,"\0");
        printf("%ld \n ",taille_final);
    
for(int i = 0 ;i<taille_tab;i++ ){
    taille_append=strlen(tmp_str[i]);
    strncat(str,tmp_str[i],taille_append);
    taille+=taille_append;
    str[taille++]=';';
    str[taille]='\0'; //VITAL VRAIMENT J AI PERDU 4 HEURE COMPORTEMENT PLUS QU INATTENDU 
}
    str[taille-1]='\0';
    



    
    //printf("SockaddrintoStr :%s \n",str);
    
    return str;

}

char* toTabCharSockaddr4(  struct sockaddr_in *** addr , int taille_tab ){

   
        char *str =NULL;
        char* tmp = NULL;


    
        for(int i = 0 ;i<taille_tab;i++ ){
             tmp=toCharSockaddr((*addr)[i]);
              //printf("tmp %s\n ",tmp);
            if(i==0){
                str = (char*)malloc(strlen(tmp)+1+1) ;
                strcpy(str,tmp);
            }else{
            str=fusionstr(str,tmp,tabSockaddrDelims()[1]);
        }
           // printf("result %s\n ",str);

        }
       
        //printf("\n\n TABABABABA %s \n\n",str);

        return str;
        

}


size_t strsockaddrTabtabtab (char ** result , struct sockaddr_in ***  tab,size_t taille , int* taille_bis  ){
     //result = (char**)realloc(result, taille *sizeof(char*));
    char* tmp_str ;
    size_t tt =0;
    for(int i = 0 ; i<taille ; i++){
        tmp_str=toTabCharSockaddr(tab[i],taille_bis[i]);
        result[i] = realloc( result[i], (strlen(tmp_str)+1) );
        tt+=(strlen(tmp_str)+1) ;
        strcpy(result[i],tmp_str);
       //printf(" Resultat strsockaddrTabtabtab  :  %s taille :%ld \n" , result[i], tt);
 
         
    }
   
   
    return tt;

}

char* strsockaddrTabtabtab2(struct sockaddr_in ***  tab,size_t taille , int* taille_bis  ){


char**  tabtab =(char**)malloc(taille *sizeof(char*));
for(int i =0; i < taille;i++)tabtab[i]=(char*)malloc(1);
//printf("Tabtabtab2 taille : %ld\n",taille);

//printf("Tabtabtab2 taille : %ld\n",taille);
 size_t tt = strsockaddrTabtabtab (tabtab,tab,taille ,  taille_bis );
//printf("TABTAB %s \n",tabtab[0]);
char *result_tab = (char*)malloc(strlen(tabtab[0])+1);//tt);
strcpy(result_tab,"");
result_tab[0]='\0';
strcpy(result_tab,tabtab[0]);
int avance =strlen(tabtab[0]);


for(int i = 1 ; i< taille ; i++){
    //printf("INTER :%s et \n  %s\n\n",result_tab,tabtab[i]);
    result_tab=fusionstr ( result_tab ,tabtab[i] ,'|');
    avance+=(strlen(tabtab[i])+1);

    //free(tabtab[i]);
}

 result_tab[avance+1]='\0';

if(debug_sockaddr)printf("Resultat strsockaddrTabtabtab2 :%d vs %d \n",strlen(result_tab),avance );
return result_tab;

}



        ////////////



void print_addrinfo(struct addrinfo* address){
     char ip_addr[INET6_ADDRSTRLEN];
    /*getnameinfo(address->ai_addr, address->ai_addrlen,
        address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);*/
    if(debug_sockaddr)printf("\t magique: > %s | %d \n", 
        inet_ntop(address->ai_family,get_in_addr((struct sockaddr *)address->ai_addr ),ip_addr,INET6_ADDRSTRLEN) , 
        ntohs(get_in_port((struct sockaddr *)address->ai_addr )));
  }



/////////////////////////////////////////
char *  sockaddrtoStr(const struct sockaddr * addr){

    //printf("SockaddrtoStr : sa_family: %hu , sa_data[14]:%s \n",addr->sa_family,addr->sa_data); 
    char * str =NULL;
    if((str=sockaddrintoStr ( (struct sockaddr_in*)addr))==NULL){
    
        if(debug_sockaddr)printf("N'est pas AF_INET\n");
        size_t taille ,taille_final,taille_append;
        taille_final=taille=taille_append=0;
        char  family[10];//> strlen("AF_LOCAL")
        sprintf(family,"%hu",addr->sa_family);
        taille_final=strlen(family)+strlen(addr->sa_data)+2+strlen("Family : ")+strlen(" Autre :");
        str=(char*)malloc( taille_final+1);
        strcpy(str,"");

        taille_append=strlen("Family : ");
        strcpy(str,"Family : ");
        taille+=taille_append;
        
        taille_append=strlen(family);
        strncat(str,family,taille_append);
        taille+=taille_append;
        
        str[taille++]=',';
        
        taille_append=strlen(" Autre :");
        strncat(str," Autre :",taille_append);
        taille+=taille_append;
        
        taille_append=strlen(addr->sa_data);
        strncat(str,addr->sa_data,taille_append);
        taille+=taille_append;
        
        str[taille++]='\0';
        if(taille_final!=taille){perror("SockaddrtoStr , taille_final != taille");exit(1);}
    
    }
    //printf("sockaddrtoStr , le str return %s \n",str); 
    
    return str;
}
char * sockaddrintoStr (const  struct sockaddr_in*addr){

    if(addr->sin_family != AF_INET)return NULL;
    
    printf("Est AF_INET \n");
    char * str ;
    char  champ_title [] = "Family : , Port : , Ip_addr : "; // si pas [] alors segmentation fault
    
    //champ value:
    char * family = "AF_INET";
        char  port [7] ;
        sprintf(port,"%d",ntohs((short)addr->sin_port));//max : "65 535" donc 5 
        char ip_addr [INET_ADDRSTRLEN];
        inet_ntop(AF_INET,&addr->sin_addr,ip_addr,INET_ADDRSTRLEN);
        

        size_t taille ,taille_append,taille_final;
        taille_append=taille=0;
        taille_final=strlen(family)+strlen(port)+strlen(ip_addr)+strlen(champ_title)+1+3-1;//3-1 pour les 2 virgule de Family port - ip_addr 
        
        
    str=(char*)malloc( taille_final);
    strcpy(str,"");
    const char * sep = ",\n";
    char* save_ptr;
    char * strToken = strtok_r(champ_title,sep,&save_ptr);
    
    taille_append=strlen(strToken);
    strncat(str,strToken,taille_append);
    taille+=taille_append;
    
    taille_append=strlen(family);
    strncat(str,family,taille_append);
    taille+=taille_append;
    str[taille++]=',';
    
    
    strToken = strtok_r(NULL,sep,&save_ptr);
    taille_append=strlen(strToken);
    strncat(str,strToken,strlen(strToken));
    taille+=taille_append;
    
    taille_append=strlen(port);
    strncat(str,port,taille_append);
    taille+=taille_append;
    
    str[taille++]=',';
    
    strToken = strtok_r(NULL,sep,&save_ptr);
    taille_append=strlen(strToken);
    strncat(str,strToken,taille_append);
    taille+=taille_append;
    
    taille_append=strlen(ip_addr);
    strncat(str,ip_addr,taille_append);
    taille+=taille_append;
    
    
    str[taille]='\0';
    
    //printf("SockaddrintoStr :%s \n",str);
    
    return str;
    
    
    
        
}
        ////////////////////////////////////////////////

