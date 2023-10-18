 
/**
 * fichier:my-util.c
 * auteur: Rambal Julien
 * description : Miscellaneous , des fonctions pour les strs notamment
 **/



#include "my-util.h"





void print_errno (){
    printf( "Code_errno :%d , description_sterror :%s \n" ,errno , strerror(errno));
}



char * erreur_mss_pasFait() {return " - erreur_mss - pas implemente";}
char * erreur_mss_default(){return "Erreur";}


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

        
void  my_pause (char* nom_service , char * before_action,char* after_action  ){
          printf("%s après avoir : %s , action a venir :%s \n ",nom_service,before_action,after_action);
          getchar();
          printf("Resume \n");
}
/*
char* fusionstr ( char* str1 ,const char * str2 ,const char sep ){
    size_t sz_str2 = strlen(str2);
    //printf("str1 %s \n",str1);
    str1 = realloc(str1,strlen(str1)+1+sz_str2+1);
    int taille = strlen(str1);
    //printf("taille %d \n",taille);
    str1[taille++]=sep;
    str1[taille]='\0';
    //printf("stre1 %s \n",str1);
    strncat(str1,str2,sz_str2);
    taille+=sz_str2;
    //free(str2);
    //str2=NULL;
    str1[taille]='\0';
    return str1;
}
*/
char* fusionstr ( char* str1 ,const char * str2 ,const char sep ){
    size_t sz_str2 = strlen(str2);
    //printf("str1 %s  str2 %s %d %d \n",str1,str2,strlen(str1),strlen(str2));
    char * buf = (char*)malloc(strlen(str1)+1+sz_str2+1);
    buf[0]='\0';
    strcpy(buf,str1);
    buf[strlen(str1)+1]='\0';
    int taille = strlen( buf);
    //printf("taille %d \n",taille);
    buf[taille++]=sep;
    buf[taille]='\0';
    //printf("stre1 %s \n", buf);
    strncat( buf,str2,sz_str2);
    taille+=sz_str2;
    //free(str2);
    //str2=NULL;
    //printf("str11 %s \n", buf);
    buf[taille]='\0';
    free(str1);
    return buf;
}



void freeToNull(void** ptr){
    if(ptr !=NULL && *ptr !=NULL ){
    free(*ptr);
    *ptr=NULL; 

}

}


int  strTailleInt(int nb ){
    return ((nb!=0?(int)log10((double)abs(nb)):1)+(nb<0))+1;
}





char* intToChar(int nb){
    char* result = (char*)malloc(strTailleInt(nb)); //1 pour le \0
    sprintf(result, "%d", nb);
    return result;

}

int strToInt (char* str){
    return atoi(str);
}

int strToInt_p (char* str){
   
    int nb = atoi(str);
     if(DEBUG_UTIL)printf("STRTOINT %s %d\n",str,nb);

    return nb ;
}

char* floatToChar(float nb){
    int len = snprintf(NULL, 0, "%f");
    char *result = malloc(len + 1);
    sprintf(result, "%f",nb);
    return result;
}

float strToFloat (char* str){
    return atof(str);
}


char* fusionNbStr(char* str , int nb,const char delim ){
    char* nbStr= intToChar(nb);
    if(DEBUG_UTIL)printf("%s Str %s  %d vs chiff %d \n",str,nbStr,strlen(str),strlen(nbStr));
    nbStr=fusionstr(nbStr,str,delim);
    if(DEBUG_UTIL)printf("%s nbStr \n",nbStr);
    free(str);
    return nbStr;
}

char* fusionNbsStr(char* str , int* nbs,size_t taille , const char delim ){

    for(int i =taille-2 ; i < 0 ; i++){
    str=fusionNbStr(str ,nbs[i], delim );
        }

    return str;
}
