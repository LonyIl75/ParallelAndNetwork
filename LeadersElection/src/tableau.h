/**
 * fichier: tableau.h
 * auteur: Rambal Julien
 * description : Fonctions utiles pour manipuler les tableaux : print , creer , serializer etc 
 **/




#ifndef TABLEAU_H
#define TABLEAU_H

#include <stdio.h> 
#include <stdlib.h>
#include<string.h>
#include <errno.h>
#include<math.h>
#include"my-util.h"
#include <limits.h>

#define DEBUG_TABLEAU 0
#define debug_tab 0 

int* cst_nbEdges ( int ** adjMatrix , int nb_node ,int nb_limit);


int* cst_nbEdgesAdj ( int ** adjMatrix , int taille_square );


int** toTabTabInt (int* _mat , size_t taille_r ,int* sz_row );



void tabInt_decalH (int* tab ,size_t deb, size_t end , const int shiftH );
void tabInt_decalH2 (int* tab , size_t end , const int shiftH );

void tabInt_decalV(int** tab ,int* taille_c ,size_t taille_r ,size_t deb, size_t end , const int shiftV);

void tabInt_decalV2 (int** tab , int* taille_c ,size_t taille_r,size_t end , const int shiftV );


void tabInt_decalV3 (int** tab , int* taille_c ,size_t taille_r , const int shiftV );


int** tabtabInt_RemoveLine_cpy(int** tab , int * taille_r ,int* taille_c , int nb_rmLine);


void tabtabInt_AppendVal (int*** tab , int * taille_r ,int* taille_c , int* size2D , const int val  );


int intComparator ( const void * first, const void * second ) ;

int isIn ( int* tab , int val , size_t taille  );


void tabSquare(int* tab ,size_t taille, int val );


void freeTabTab(void ** tabtab , size_t taille );

int* cpy_tab_int (int* tab,size_t taille);
int** cpy_tabTab_int (int** tab,int* tab_taille , int  taille);
int** cpy_tabTab_intSq (int** tab, int  taille);

void print_tab_int (int * tab , int taille );
void printTabtab_int( int ** tabtab , size_t taille , int* taille_tab );
void printTabtab_int2( int ** tabtab , size_t taille  );
void printTabtab_int3( int ** tabtab , size_t taille );

void print_tab_double (double * tab , int taille );
void printTabtab_double( double ** tabtab , size_t taille , int* taille_tab );


int maxOfTabInt (int* tab , size_t taille );
void print_tab_int2 (int * tab , int taille );
void* taille_bis (void* valeur , size_t taille ); // TODO : a mettre dans util

int* taille_bisInt (int* valeur , size_t taille ); // TODO : a mettre dans util




char* intTabToString ( int* tab , size_t taille , const char delimiter , int idmax  ,int select  );
char* intTabTabToString ( int** tab , size_t taille2 , int taille , const char * concatEndDelim , int idmax ,int select  );
char* intTabTabToString2 ( int** tabTab , size_t taille2 , int* taille , const char * concatEndDelim , int idmax ,int select  );
int** strToTabTab(char* str,const char* delims);
int* strToTab(char* str,const char delim);
const char endDelimDf();
const char tabDelim();
const char * tabDelim2();
const char* tabTabDelims();


int caraID (  int idmax   );
int regularCara (  size_t taille , int max   );

#endif