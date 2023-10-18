
/**
 * fichier: my-util.h
 * auteur: Rambal Julien
 * description : Fonction d'usage divers 
 **/


#ifndef MYUTIL_H
#define MYUTIL_H


#include <limits.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <errno.h>
#include<math.h>

#ifndef debug
#define  debug 0
#endif

#ifndef param_print
#define param_print 0
#endif


#define DEBUG_UTIL 0

char* fusionNbStr(char* str , int nb,const char delim );

char* fusionNbsStr(char* str , int* nbs,size_t taille,const char delim );
int strToInt_p (char* str);
char* intToChar(int nb);

int strToInt (char* str);
char* floatToChar(float nb);

float strToFloat (char* str);

int strTailleInt(int nb );

void print_errno ();


void swap(int *xp, int *yp);

char * erreur_mss_pasFait();
char * erreur_mss_default();
//void  lire_fichier( FILE * fptr , void * buff , size_t size );


        
void  my_pause (char* nom_service , char * before_action,char* after_action  );

char* fusionstr ( char* str1 ,const char * str2 ,const char sep );


void freeToNull(void** ptr);

#endif