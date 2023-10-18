

/**
 * fichier:convert.h
 * auteur: Rambal Julien
 * description : Des fonctions de conversion pour le C 
 **/




#ifndef convert_h
#define convert_h

#define DEBUG_CONVERT 0

int  strTailleInt(int nb );

int caraID (  int idmax   );
int regularCara (  size_t taille , int max   );

char* intTabToString ( int* tab , size_t taille , const char delimiter , int idmax  ,int select  );
char* intTabTabToString ( int** tab , size_t taille2 , int taille , const char * concatEndDelim , int idmax ,int select  );
char* intTabTabToString2 ( int** tabTab , size_t taille2 , int* taille , const char * concatEndDelim , int idmax ,int select  );
int** strToTabTab(char* str,const char* delims);
int* strToTab(char* str,const char delim);
const char endDelimDf();
const char tabDelim();
const char* tabTabDelims();

char* intToChar(int nb);

int strToInt (char* str);
char* floatToChar(float nb);

float strToFloat (char* str);

#endif